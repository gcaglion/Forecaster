#include <cuRNN.h>

// Define some error checking macros.
#define cudaErrCheck(stat) { cudaErrCheck_((stat), __FILE__, __LINE__); }
void cudaErrCheck_(cudaError_t stat, const char *file, int line) {
	if (stat != cudaSuccess) {
		fprintf(stderr, "CUDA Error: %s %s %d\n", cudaGetErrorString(stat), file, line);
	}
}

#define cudnnErrCheck(stat) { cudnnErrCheck_((stat), __FILE__, __LINE__); }
void cudnnErrCheck_(cudnnStatus_t stat, const char *file, int line) {
	if (stat != CUDNN_STATUS_SUCCESS) {
		fprintf(stderr, "cuDNN Error: %s %s %d\n", cudnnGetErrorString(stat), file, line);
	}
}

__global__ void initGPUData_ker(float *data, int numElements, float value) {
	int tid = blockIdx.x * blockDim.x + threadIdx.x;
	if (tid < numElements) {
		data[tid] = value;
	}
}

void initGPUData(float *data, int numElements, float value) {
	dim3 gridDim;
	dim3 blockDim;

	blockDim.x = 1024;
	gridDim.x = (numElements + blockDim.x - 1) / blockDim.x;

	initGPUData_ker << < gridDim, blockDim >> > (data, numElements, value);
}

int setupGPU(
	int seqLength, int inputSize, int batchCount, int batchSize, int numLayers, int hiddenSize, bool bidirectional, int mode, float dropout,
	float** hSample, float** hTarget/*,
	void* x, void* hx, void* cx, void* y, void* hy, void* cy, void* dx, void* dhx, void* dcx, void* dy, void* dhy, void* dcy,
	cudnnTensorDescriptor_t* xDesc, cudnnTensorDescriptor_t* yDesc, cudnnTensorDescriptor_t* dxDesc, cudnnTensorDescriptor_t* dyDesc*/
	) {

	//=== 0. Create cudnn context
	cudnnHandle_t cudnnHandle;
	cudnnErrCheck(cudnnCreate(&cudnnHandle));
	//===

	//=== 1. Create Data structures on GPU
	void* x;
	void* hx = NULL;
	void* cx = NULL;

	void* y;
	void* hy = NULL;
	void* cy = NULL;

	void* dx;
	void* dhx = NULL;
	void* dcx = NULL;

	void* dy;
	void* dhy = NULL;
	void* dcy = NULL;

	// Memory allocation. hx, cx, dhx, dcx, hy, cy, dhy and dcy can be NULL.
	cudaErrCheck(cudaMalloc((void**)&x, seqLength * inputSize * batchSize * sizeof(float)));
	cudaErrCheck(cudaMalloc((void**)&hx, numLayers * hiddenSize * batchSize * (bidirectional ? 2 : 1) * sizeof(float)));
	cudaErrCheck(cudaMalloc((void**)&cx, numLayers * hiddenSize * batchSize * (bidirectional ? 2 : 1) * sizeof(float)));

	cudaErrCheck(cudaMalloc((void**)&dx, seqLength * inputSize * batchSize * sizeof(float)));
	cudaErrCheck(cudaMalloc((void**)&dhx, numLayers * hiddenSize * batchSize * (bidirectional ? 2 : 1) * sizeof(float)));
	cudaErrCheck(cudaMalloc((void**)&dcx, numLayers * hiddenSize * batchSize * (bidirectional ? 2 : 1) * sizeof(float)));

	cudaErrCheck(cudaMalloc((void**)&y, seqLength * hiddenSize * batchSize * (bidirectional ? 2 : 1) * sizeof(float)));
	cudaErrCheck(cudaMalloc((void**)&hy, numLayers * hiddenSize * batchSize * (bidirectional ? 2 : 1) * sizeof(float)));
	cudaErrCheck(cudaMalloc((void**)&cy, numLayers * hiddenSize * batchSize * (bidirectional ? 2 : 1) * sizeof(float)));

	cudaErrCheck(cudaMalloc((void**)&dy, seqLength * hiddenSize * batchSize * (bidirectional ? 2 : 1) * sizeof(float)));
	cudaErrCheck(cudaMalloc((void**)&dhy, numLayers * hiddenSize * batchSize * (bidirectional ? 2 : 1) * sizeof(float)));
	cudaErrCheck(cudaMalloc((void**)&dcy, numLayers * hiddenSize * batchSize * (bidirectional ? 2 : 1) * sizeof(float)));

	// Set up tensor descriptors. x/y/dx/dy are arrays, one per time step.
	cudnnTensorDescriptor_t *xDesc, *yDesc, *dxDesc, *dyDesc;
	cudnnTensorDescriptor_t hxDesc, cxDesc;
	cudnnTensorDescriptor_t hyDesc, cyDesc;
	cudnnTensorDescriptor_t dhxDesc, dcxDesc;
	cudnnTensorDescriptor_t dhyDesc, dcyDesc;

	xDesc = (cudnnTensorDescriptor_t*)malloc(seqLength * sizeof(cudnnTensorDescriptor_t));
	yDesc = (cudnnTensorDescriptor_t*)malloc(seqLength * sizeof(cudnnTensorDescriptor_t));
	dxDesc = (cudnnTensorDescriptor_t*)malloc(seqLength * sizeof(cudnnTensorDescriptor_t));
	dyDesc = (cudnnTensorDescriptor_t*)malloc(seqLength * sizeof(cudnnTensorDescriptor_t));

	// In this example dimA[1] is constant across the whole sequence
	// This isn't required, all that is required is that it does not increase.
	int dimA[3];
	int strideA[3];

	for (int i = 0; i < seqLength; i++) {
		cudnnErrCheck(cudnnCreateTensorDescriptor(&xDesc[i]));
		cudnnErrCheck(cudnnCreateTensorDescriptor(&yDesc[i]));
		cudnnErrCheck(cudnnCreateTensorDescriptor(&dxDesc[i]));
		cudnnErrCheck(cudnnCreateTensorDescriptor(&dyDesc[i]));

		dimA[0] = batchSize;
		dimA[1] = inputSize;
		dimA[2] = 1;

		strideA[0] = dimA[2] * dimA[1];
		strideA[1] = dimA[2];
		strideA[2] = 1;

		cudnnErrCheck(cudnnSetTensorNdDescriptor(xDesc[i], CUDNN_DATA_FLOAT, 3, dimA, strideA));
		cudnnErrCheck(cudnnSetTensorNdDescriptor(dxDesc[i], CUDNN_DATA_FLOAT, 3, dimA, strideA));

		dimA[0] = batchSize;
		dimA[1] = bidirectional ? hiddenSize * 2 : hiddenSize;
		dimA[2] = 1;

		strideA[0] = dimA[2] * dimA[1];
		strideA[1] = dimA[2];
		strideA[2] = 1;

		cudnnErrCheck(cudnnSetTensorNdDescriptor(yDesc[i], CUDNN_DATA_FLOAT, 3, dimA, strideA));
		cudnnErrCheck(cudnnSetTensorNdDescriptor(dyDesc[i], CUDNN_DATA_FLOAT, 3, dimA, strideA));
	}


	dimA[0] = numLayers * (bidirectional ? 2 : 1);
	dimA[1] = batchSize;
	dimA[2] = hiddenSize;

	strideA[0] = dimA[2] * dimA[1];
	strideA[1] = dimA[2];
	strideA[2] = 1;

	cudnnErrCheck(cudnnCreateTensorDescriptor(&hxDesc));
	cudnnErrCheck(cudnnCreateTensorDescriptor(&cxDesc));
	cudnnErrCheck(cudnnCreateTensorDescriptor(&hyDesc));
	cudnnErrCheck(cudnnCreateTensorDescriptor(&cyDesc));
	cudnnErrCheck(cudnnCreateTensorDescriptor(&dhxDesc));
	cudnnErrCheck(cudnnCreateTensorDescriptor(&dcxDesc));
	cudnnErrCheck(cudnnCreateTensorDescriptor(&dhyDesc));
	cudnnErrCheck(cudnnCreateTensorDescriptor(&dcyDesc));

	cudnnErrCheck(cudnnSetTensorNdDescriptor(hxDesc, CUDNN_DATA_FLOAT, 3, dimA, strideA));
	cudnnErrCheck(cudnnSetTensorNdDescriptor(cxDesc, CUDNN_DATA_FLOAT, 3, dimA, strideA));
	cudnnErrCheck(cudnnSetTensorNdDescriptor(hyDesc, CUDNN_DATA_FLOAT, 3, dimA, strideA));
	cudnnErrCheck(cudnnSetTensorNdDescriptor(cyDesc, CUDNN_DATA_FLOAT, 3, dimA, strideA));
	cudnnErrCheck(cudnnSetTensorNdDescriptor(dhxDesc, CUDNN_DATA_FLOAT, 3, dimA, strideA));
	cudnnErrCheck(cudnnSetTensorNdDescriptor(dcxDesc, CUDNN_DATA_FLOAT, 3, dimA, strideA));
	cudnnErrCheck(cudnnSetTensorNdDescriptor(dhyDesc, CUDNN_DATA_FLOAT, 3, dimA, strideA));
	cudnnErrCheck(cudnnSetTensorNdDescriptor(dcyDesc, CUDNN_DATA_FLOAT, 3, dimA, strideA));
	
	// -------------------------
	// Set up the dropout descriptor (needed for the RNN descriptor)
	// -------------------------
	unsigned long long seed = 1337ull; // Pick a seed.

	cudnnDropoutDescriptor_t dropoutDesc;
	cudnnErrCheck(cudnnCreateDropoutDescriptor(&dropoutDesc));

	// How much memory does dropout need for states?
	// These states are used to generate random numbers internally
	// and should not be freed until the RNN descriptor is no longer used
	size_t stateSize;
	void *states;
	cudnnErrCheck(cudnnDropoutGetStatesSize(cudnnHandle, &stateSize));
	cudaErrCheck(cudaMalloc(&states, stateSize));
	cudnnErrCheck(cudnnSetDropoutDescriptor(dropoutDesc, cudnnHandle, dropout, states, stateSize, seed));

	// -------------------------   
	// Set up the RNN descriptor
	// -------------------------
	cudnnRNNDescriptor_t rnnDesc;
	cudnnRNNMode_t RNNMode;

	cudnnErrCheck(cudnnCreateRNNDescriptor(&rnnDesc));

	if (mode == 0) RNNMode = CUDNN_RNN_RELU;
	else if (mode == 1) RNNMode = CUDNN_RNN_TANH;
	else if (mode == 2) RNNMode = CUDNN_LSTM;
	else if (mode == 3) RNNMode = CUDNN_GRU;

	cudnnErrCheck(cudnnSetRNNDescriptor(cudnnHandle, rnnDesc,
		hiddenSize,
		numLayers,
		dropoutDesc,
		CUDNN_LINEAR_INPUT, // We can also skip the input matrix transformation
		bidirectional ? CUDNN_BIDIRECTIONAL : CUDNN_UNIDIRECTIONAL,
		RNNMode, CUDNN_RNN_ALGO_STANDARD,
		CUDNN_DATA_FLOAT));

	// -------------------------
	// Set up parameters
	// -------------------------
	// This needs to be done after the rnn descriptor is set as otherwise
	// we don't know how many parameters we have to allocate
	void *w;
	void *dw;

	cudnnFilterDescriptor_t wDesc, dwDesc;

	cudnnErrCheck(cudnnCreateFilterDescriptor(&wDesc));
	cudnnErrCheck(cudnnCreateFilterDescriptor(&dwDesc));

	size_t weightsSize;
	cudnnErrCheck(cudnnGetRNNParamsSize(cudnnHandle, rnnDesc, xDesc[0], &weightsSize, CUDNN_DATA_FLOAT));

	int dimW[3];
	dimW[0] = (int)floor(weightsSize / sizeof(float));
	dimW[1] = 1;
	dimW[2] = 1;

	cudnnErrCheck(cudnnSetFilterNdDescriptor(wDesc, CUDNN_DATA_FLOAT, CUDNN_TENSOR_NCHW, 3, dimW));
	cudnnErrCheck(cudnnSetFilterNdDescriptor(dwDesc, CUDNN_DATA_FLOAT, CUDNN_TENSOR_NCHW, 3, dimW));

	cudaErrCheck(cudaMalloc((void**)&w, weightsSize));
	cudaErrCheck(cudaMalloc((void**)&dw, weightsSize));


	// -------------------------
	// Set up work space and reserved memory
	// -------------------------   
	void *workspace;
	void *reserveSpace;

	size_t workSize;
	size_t reserveSize;

	// Need for every pass
	cudnnErrCheck(cudnnGetRNNWorkspaceSize(cudnnHandle, rnnDesc, seqLength, xDesc, &workSize));
	// Only needed in training, shouldn't be touched between passes.
	cudnnErrCheck(cudnnGetRNNTrainingReserveSize(cudnnHandle, rnnDesc, seqLength, xDesc, &reserveSize));

	cudaErrCheck(cudaMalloc((void**)&workspace, workSize));
	cudaErrCheck(cudaMalloc((void**)&reserveSpace, reserveSize));

	// Weights
	int numLinearLayers = 0;
	if (RNNMode == CUDNN_RNN_RELU || RNNMode == CUDNN_RNN_TANH) {
		numLinearLayers = 2;
	}
	else if (RNNMode == CUDNN_LSTM) {
		numLinearLayers = 8;
	}
	else if (RNNMode == CUDNN_GRU) {
		numLinearLayers = 6;
	}

	for (int layer = 0; layer < numLayers * (bidirectional ? 2 : 1); layer++) {
		for (int linLayerID = 0; linLayerID < numLinearLayers; linLayerID++) {
			cudnnFilterDescriptor_t linLayerMatDesc;
			cudnnErrCheck(cudnnCreateFilterDescriptor(&linLayerMatDesc));
			float *linLayerMat;

			cudnnErrCheck(cudnnGetRNNLinLayerMatrixParams(cudnnHandle, rnnDesc, layer, xDesc[0], wDesc, w, linLayerID, linLayerMatDesc, (void**)&linLayerMat));

			cudnnDataType_t dataType;
			cudnnTensorFormat_t format;
			int nbDims;
			int filterDimA[3];
			cudnnErrCheck(cudnnGetFilterNdDescriptor(linLayerMatDesc, 3, &dataType, &format, &nbDims, filterDimA));

			initGPUData(linLayerMat, filterDimA[0] * filterDimA[1] * filterDimA[2], 1.f / (float)(filterDimA[0] * filterDimA[1] * filterDimA[2]));

			cudnnErrCheck(cudnnDestroyFilterDescriptor(linLayerMatDesc));

			cudnnFilterDescriptor_t linLayerBiasDesc;
			cudnnErrCheck(cudnnCreateFilterDescriptor(&linLayerBiasDesc));
			float *linLayerBias;

			cudnnErrCheck(cudnnGetRNNLinLayerBiasParams(cudnnHandle, rnnDesc, layer, xDesc[0], wDesc, w, linLayerID, linLayerBiasDesc, (void**)&linLayerBias));

			cudnnErrCheck(cudnnGetFilterNdDescriptor(linLayerBiasDesc, 3, &dataType, &format, &nbDims, filterDimA));

			initGPUData(linLayerBias, filterDimA[0] * filterDimA[1] * filterDimA[2], 1.f);

			cudnnErrCheck(cudnnDestroyFilterDescriptor(linLayerBiasDesc));
		}
	}

	// *********************************************************************************************************
	// At this point all of the setup is done. We now need to pass through the RNN (one batch at a time).
	// *********************************************************************************************************
	for (int b = 0; b < batchCount; b++) {
		//-- Load input and output (target) data
		cudaErrCheck(cudaMemcpy(x, hSample[b], (batchSize*seqLength*inputSize) * sizeof(float), cudaMemcpyHostToDevice));
		cudaErrCheck(cudaMemcpy(y, hTarget[b], (batchSize*seqLength*inputSize) * sizeof(float), cudaMemcpyHostToDevice));
		//-- FeedForward
		cudnnErrCheck(cudnnRNNForwardTraining(cudnnHandle, rnnDesc, seqLength, xDesc, x, hxDesc, hx, cxDesc, cx, wDesc, w, yDesc, y, hyDesc, hy, cyDesc, cy, workspace, workSize, reserveSpace, reserveSize));
		//-- Feedback Context
		cudnnErrCheck(cudnnRNNBackwardData(cudnnHandle, rnnDesc, seqLength, yDesc, y, dyDesc, dy, dhyDesc, dhy, dcyDesc, dcy, wDesc, w, hxDesc, hx, cxDesc, cx, dxDesc, dx, dhxDesc, dhx, dcxDesc, dcx, workspace, workSize, reserveSpace, reserveSize));
		//-- calc and apply dW
		cudaErrCheck(cudaMemset(dw, 0, weightsSize));
		cudnnErrCheck(cudnnRNNBackwardWeights(cudnnHandle, rnnDesc, seqLength, xDesc, x, hxDesc, hx, yDesc, y, workspace, workSize, dwDesc, dw, reserveSpace, reserveSize));
		//-- FF to test data
		cudnnErrCheck(cudnnRNNForwardInference(cudnnHandle, rnnDesc, seqLength, xDesc, x, hxDesc, hx, cxDesc, cx, wDesc, w, yDesc, y, hyDesc, hy, cyDesc, cy, workspace, workSize));
		//-- sync (?)
		cudaErrCheck(cudaDeviceSynchronize());
	}

	return 0;
}
EXPORT int RNNtrain(int sqLen, int inputSize, int hiddenSize, int numLayers, int batchCount, int batchSize, bool bidirectional, int mode, float dropout, float** sample, float** target) {
	
	setupGPU(
		sqLen, inputSize, batchCount, batchSize, numLayers, hiddenSize, bidirectional, mode, dropout, sample, target
	);
	//===

	//=== 2. Load Input Data (one batch at a time)

	//-- sample and target are both in OHLC/OHLCV format (inputSize=4/5)
	// sample[batchCount][batchSize][seqLen][inputSize]
	// target[batchCount][batchSize][seqLen][inputSize]

	return 0;
}

int RNNrun() {
	return 0;
}
#include <MyUtils.h>
typedef float numtype;

int cuMbyM(int Ay, int Ax, numtype** A, bool transpose, int By, int Bx, numtype** B, numtype** C) {
	return 0;
}
int cuMcopy(int Ay, int Ax, numtype** A, numtype** B) {
	return 0;
}
int cuMadd(int Ay, int Ax, numtype** A, numtype** B, numtype** C) {
	return 0;
}
int cuMdiff(int Ay, int Ax, numtype** A, numtype** B, numtype** C) {
	return 0;
}
int cuMinit(int Ay, int Ax, numtype** A, numtype initval) {
	return 0;
}
int cuTanh(int Ay, int Ax, numtype** A, numtype** C) {
	return 0;
}

EXPORT int RNNtrain(int seqLen, int inputSize, int miniBatchSize, int hiddenSize, int numLayers, numtype**** sample, numtype**** target) {
	// sample[miniBatchId][seqLen][inputSize]
	// target[miniBatchId][seqLen][outputSize]

	int hSize = hiddenSize;
	int outputSize = inputSize;
	numtype***  x  = MallocArray<numtype>(seqLen, inputSize, 1);
	numtype***  y = MallocArray<numtype>(seqLen, outputSize, 1);
	numtype***  e = MallocArray<numtype>(seqLen, outputSize, 1);
	numtype**  be = MallocArray<numtype>(outputSize, 1);
	numtype***  u = MallocArray<numtype>(seqLen, outputSize, 1);
	numtype** h  = MallocArray<numtype>(hSize, 1);
	numtype** h1 = MallocArray<numtype>(hSize, 1);

	numtype** Whx = MallocArray<numtype>(hSize, inputSize);
	numtype** Whh = MallocArray<numtype>(hSize, hSize);
	numtype** Why = MallocArray<numtype>(hSize, outputSize);

	numtype** tmp1 = MallocArray<numtype>(hSize, 1);
	numtype** tmp2 = MallocArray<numtype>(hSize, 1);
	numtype** tmp  = MallocArray<numtype>(hSize, 1);

	for(int b=0; b<miniBatchSize; b++){
		//-- copy all samples from current batch into x
		//-- .....
		//-- copy all targets from current batch into u
		//-- .....

		//-- initialize error=0 for batch
		cuMinit(seqLen, outputSize, be, 0);

		for(int t=0; t<seqLen; t++){
			//-- save h in h1
			cuMcopy(hSize, 1, h, h1);
			//-- tmp1=Whx*x(t)
			cuMbyM(hSize, inputSize, Whx, false, inputSize, 1, x[t], tmp1);
			//-- tmp2=Whh*h1
			cuMbyM(hSize, hSize, Whh, hSize, false, 1, h1, tmp2);
			//-- tmp=tmp1+tmp2
			cuMadd(hSize, 1, tmp1, tmp2, tmp);
			//-- h=tanh(tmp)
			cuTanh(hSize, 1, tmp, h);
			//-- y(t)=Why*h
			cuMbyM(hSize, outputSize, Why, hSize, true, 1, h, y[t]);

			//-- calc error: e=y-u
			cuMdiff(outputSize, 1, y[t], u[t], e[t]);
			//-- sum up error in batch error
			cuMadd(outputSize, 1, be, e[t], be);

			//-- backpropagation (std)

			//--- y-h

			//--- h-x

		}

	}
	// a1=F0*W10

}
#pragma once

#define SLACK_NORM_L1 1
#define SLACK_NORM_SQUARED 2
#define RESCALING_METHOD_SLACK 1
#define RESCALING_METHOD_MARGIN 2
#define LOSS_FUNCTION_ZEROONE 0
#define LEARNING_ALGO_NSLACK 0
#define LEARNING_ALGO_NSLACK_SHRINK 1
#define LEARNING_ALGO_1SLACK_PRIMAL 2
#define LEARNING_ALGO_1SLACK_DUAL 3
#define LEARNING_ALGO_1SLACK_DUAL_CONSTR 4
#define LEARNING_ALGO_CUSTOM 9
#define KERNEL_TYPE_LINEAR 0
#define KERNEL_TYPE_POLY 1
#define KERNEL_TYPE_RBF 2
#define KERNEL_TYPE_TANH 3
#define KERNEL_TYPE_CUSTOM 4

//-- SVM engine specific parameters
typedef struct sSVMParms{
	int DebugLevel;
	int InputCount;
	//int OutputCount;
	int MaxEpochs;
	//--
	double C;				// -c
	int SlackNorm;			// -p
	int RescalingMethod;	// -o
	int LossFunction;		// -l
	int LearningAlgo;		// -w
	double epsilon;			// -e
	int NewConstrEtrain;	// -k
	int CCacheSize;		// -f
	int BatchSize;			// -b
	int NewVarSinQP;		// -n
	int KernelCacheSize;	// -m
	int svmIterToShrink;	// -h
	//--
	int KernelType;			// -t
	int PolyDegree;			// -d
	double RBFGamma;		// -g
	double CoefLin;			// -s
	double CoefConst;		// -r
	char CustomKernel[50];	// -u
#ifdef __cplusplus
	sSVMParms() {};
	~sSVMParms() {};
#endif
} SVM_Parms;

typedef struct {
	int ProcessId; int ThreadId;  int TimeStep;
	int NeuronLevel; int FromNeuron; int ToNeuron; double Weight; double CtxValue;
} tSVMWeight;

typedef struct {
	int ActualEpochs;		// If training was stopped before reaching MaxEpochs (because TargetMSE was reached, or because of Training Divergence), this saves the actual Epochs run
	tLogMSE* MSEOutput;		// [Epoch]
	tLogRUN* RunOutput;		// [pos]
	//tSVMWeight*** FinalW;	// [NeuronLevel][FromNeuron][ToNeuron] -- this is saved only once at the end of the training
} SVM_Logs;

__declspec(dllexport) void freeSVMLog(tCoreLog* coreLog, int slen);
__declspec(dllexport) int Train_SVM(int pCorePos, int pTotCores, HANDLE pScreenMutex, tDebugInfo* pDebugParms, SVM_Parms* pSVMParms, tCoreLog* pSVMLogs, int pSampleCount, double** pSampleData, double** pTargetData, double** pSampleDataV, double** pTargetDataV);
__declspec(dllexport) int Run_SVM(tDebugInfo* pDebugParms, SVM_Parms* SVMParms, tCoreLog* SVMLogs, tDataShape* pInputData, int pid, int tid, int pSampleCount, double** pSample, double** pTarget);

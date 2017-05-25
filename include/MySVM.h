#pragma once

#include <svm_common.h>
#include <svm_learn.h>

#include <MyDebug.h>
#include <MyDataAbstraction.h>
#include <MyUtils.h>
#include <MyCores.h>

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

//-- SVM Logs
class cSVMLog : public cCoreLog {
public:
	int SVcnt;
	int Varcnt;
	double** FinalW;
	cSVMLog(int pSVcnt, int pVarcnt);
private:
	~cSVMLog();
};

//-- SVM engine
class cSVM : public cCore {
public:
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

	cSVMLog**   SVMLog;	//-- [DatasetId] SVM-specific log (FinalW, IntP)

	//-- virtual functions, common to all cores
	void init();
	void train(int DatasetId, int sampleCnt, int sampleLen, int targetLen, double** S_t, double** T_t, int useValidation, double** S_v, double** T_v);
	void run(int DatasetId, double*** savedW, int sampleCnt, int sampleLen, int targetLen, double** S, double** T);
	int  setParms(tDebugInfo* DebugParms, int pid, int tid, bool load, int iSampleCnt);
	int  LoadImage(tDebugInfo* DebugParms, int pid, int tid);
	void mallocLogs(int dscnt);
	//virtual void getScaleRange(double* oScaleMin, double* oScaleMax);

	//-- SVM-specific functions
	int calcSVcnt(MODEL* model);

};


#pragma once
#include <MyDebug.h>
#include <MyDataAbstraction.h>
#include <math.h>
#include <MyUtils.h>
#include <MyMatrix.h>

#include <MyCores.h>

#define NN_MAXLEVELS 8

//-- Training Protocols
#define TP_STOCHASTIC	0
#define TP_BATCH		1
#define TP_ONLINE		2

//-- Backpropagation algorithms
#define BP_STD   0
#define BP_QING	 1
#define BP_SCGD		 5 // Scaled Conjugate Gradient Descent
#define BP_QUICKPROP 6
//--

//-- Activation Functions
#define NN_ACTIVATION_TANH 1	// y=tanh(x)				=> range is [-1 ÷ 1]
#define NN_ACTIVATION_EXP4 2	// y = 1 / (1+exp(-4*x))	=> range is [ 0 ÷ 1]

//-- NN Weights Logging parameters
/* === OBSOLETE ? ===
typedef struct sNNWeight{
	int ProcessId; int ThreadId;  int TimeStep;
	int NeuronLevel; int FromNeuron; int ToNeuron; double Weight; double CtxValue;
} tNNWeight;
*/

//-- Internals Logging parameters
typedef struct sLogInt {
	int ProcessId; int ThreadId; int TimeStep;
	// Qing stuff
	int sigma10; double ro10; double D10W; double adzev10; int hcp10; int sigma21; double ro21; double adzev21N; double norm_e;
	// SCGD stuff
	int Epoch; int BPid; int K;
	double delta; double mu; double alpha; double beta; double lambda; double lambdau; double rnorm; double enorm; double comp;
} tLogInt;

class cNNLog : public cCoreLog {
public:
	int levelsCnt;
	int* nodesCnt;
	int weightsCntTotal;
	double*** FinalW;
	tLogInt*	 IntP;
	cNNLog(int pLevelsCnt, int* pNodesCnt, int pTimeSteps, int pWeightsCntTotal);

	//-- virtual functions, common to all cores
	int cNNLog::SaveImage(tDebugInfo* pDebugParms, tDBConnection* pDBConn);

private:
	~cNNLog();
};

class cNN: public cCore {
	int pid;
	int tid;
	int dsid;	// dataset id. needs to be set by train() and run(), because NNLog is 
public:
	int levelsCnt;
	int nodesCnt[NN_MAXLEVELS];
	char* levelRatioS;
	double levelRatio[NN_MAXLEVELS];
	int nodesCntTotal;
	int weightsCntTotal;
	int useContext;
	int MaxEpochs;
	double TargetMSE;
	double LearningRate;
	double LearningMomentum;
	double mu;
	double HCPbeta;
	int TrainingProtocol;
	int ActivationFunction;
	int BPAlgo;
	int useValidation;
	int StopAtDivergence;
	//--
	int		BPCount;
	int		SCGD_progK;
	int		ScreenPos;
	HANDLE	ScreenMutex;
	//--
	void setTopology();
	//--
	cNNLog** NNLog;	// [Dataset]

	//-- virtual functions, common to all cores
	void init();
	int  train(tDebugInfo* pDebugParms, int DatasetId, int sampleCnt, int sampleLen, int targetLen, double** S_t, double** T_t, int useValidation, double** S_v, double** T_v);
	int  run(tDebugInfo* pDebugParms, int sampleCnt, int sampleLen, int targetLen, double** S, double** T, void* img);
	int  LoadImage(tDebugInfo* DebugParms, tDBConnection* DBConn, int pid, int tid);
	void mallocLogs(int dscnt);
	virtual void getScaleRange(double* oScaleMin, double* oScaleMax);
	//--
private:
	double** a;
	double** F;
	double** dF;
	double* dk;
	double** edF;
	double** c;
	double*** W;
	double*** dW;
	double*** dJdW;
	double*** prevW;
	double*** prevdW;
	double*** prevdJdW;
	double*** BdW;
	double* e; double norm_e;
	double* u;
	double** LVV_W;
	double** LVV_dW;
	double** LVV_dJdW;
	double** prevLVV_W;
	double** prevLVV_dW;
	double** prevLVV_dJdW;
	double**** H;

	void mallocNNMem();
	void freeNNMem();

	void initdW();
	void train_Batch(int sampleCnt, int sampleLen, int targetLen, double** S, double** T, int useV, double** Sv, double** Tv);
	void train_Stochastic(int sampleCnt, int sampleLen, int targetLen, double** S, double** T, int useV, double** Sv, double** Tv);

	void SaveMSEData(int pEpoch, double pMSE_T, double pMSE_V);
	void SaveRunData(int pPos, double pActual, double* pPredicted);
	void SaveFinalW();
	void SaveCoreData_SCGD(int epoch, int BPid, int k, int timeStep, double delta, double mu, double alpha, double beta, double lambda, double lambdau, double rnorm, double enorm, double comp);

	void SavePrevWeights();

	void Calc_dJdW(bool doFF, bool doCalcH);
	void dEdW_at_w_LVV(double** LVV_W, double* w_new, double* odEdW_at_w);
	double E_at_w_LVV(double** LVV_W, double* w_new);
	void Calc_H();
	void Activate(double a, double* oF, double* odF);
	double Derivate(double INval);
	double Derivate2(double INval);

	void FF();
	void FB();
	void BP_Std();
	void BP_scgd();
	void BP_QuickProp();

	void BP();

public: 
	EXPORT cNN();
	cNN(int ppid, int ptid);
	~cNN();
};


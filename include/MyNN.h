#pragma once
#include <Windows.h>
#include <MyLogDefs.h>	// to define tLogMSE and tLogRUN
#include <DataShape.h>	// to define tDataShape
#include <MyEngines.h>	// to define tEngineHandle

//-- Layers
#define MAX_LEVELS  6

//-- time step
#define TimeSteps  4
#define t0 0 //	(t)
#define t1 1 //	(t - 1)
#define t2 2 //	(t - 2)
#define t3 3 //	(t - 3)

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

//-- NN engine core parameters
typedef struct {
	int InputCount;
	int OutputCount;
	int LevelsCount;
	double LevelRatio[MAX_LEVELS];	// Ratio between # of nodes at current and previous level
	char LevelRatioS[256];			// comma-separated string with level ratios
	int NodesCount[MAX_LEVELS];	// # of nodes at each level
	int NodesCountTotal;		// total # of nodes
	int WeightsCountTotal;		// total # of weights
	int MaxEpochs;
	double TargetMSE;
	int UseContext;
	int BP_Algo;
	int TrainingProtocol;
	int StopAtDivergence;
	double LearningRate;
	double LearningMomentum;
	int ActivationFunction;
	double HCPbeta;
	double mu;	// used by QuickProp
} NN_Parms;

typedef struct {
	//-- node levels -> [Levels][Time]
	double*** a;
	double*** F;
	double*** dF;
	double*** edF;
	double*** c;
	//-- outer node only -> [Time]
	double** e;
	double** u;
	double** Ve;
	double** Vu;
	double norm_e;
	//-- weight levels -> [Levels-1][Time]
	double**** W;
	double**** dW;
	double**** dJdW;
	double**** BdW;
	double**** Q_dJdW;
	//-- temp matrices
	double*** tmpM0;
	double*** tmpM1;
	double*** tmpM2;
	double*** tmpM3;
	//-- Qing stuff
	double** adzev;
	double** uW;
	double* Q_V1;
	double** ux;
	double** ux_inv;
	double** dxdW10;
	double** Q_ExtG;
	int		   Q_sigma[2];
	double	   Q_ro[2];
	double	   Q_adzev21norm;
	double	   Q_D10W;
	int		   Q_gamma;
	double*** Q_M1;
	double*** Q_M2;
	double*** Q_M3;
	double*** Q_M4;
	double*** Q_M5;
	double*** Q_M6;
	//-- SCGD stuff
	double*** LVV_W;
	double*** LVV_dW;
	double*** LVV_dJdW;
} NN_Mem;

typedef struct {	
	NN_Mem NN;

	int		BPCount;
	int		SCGD_progK;
	int		ScreenPos;
	HANDLE	ScreenMutex;
	//FILE*	fIntLog;
} NN_MxData;

__declspec(dllexport) void __stdcall setNNTopology(NN_Parms* NN);
__declspec(dllexport) void __stdcall mallocNNLog(tCoreLog* coreLog, int levelsCnt, int* nodesCnt, int tscnt);
__declspec(dllexport) void __stdcall freeNNLog(tCoreLog* coreLog, int levelsCnt, int* nodesCnt, int tscnt);
__declspec(dllexport) int Train_NN(int pCorePos, int pTotCores, HANDLE pScreenMutex, tDebugInfo* pDebugParms, NN_Parms* pNNParms, tCoreLog* pNNLogs, int pSampleCount, double** pSampleData, double** pTargetData, double** pSampleDataV, double** pTargetDataV);
__declspec(dllexport) void Run_NN(tDebugInfo* pDebugParms, NN_Parms* NNParms, tCoreLog* NNLogs, tDataShape* pInputData, int pid, int tid, int pSampleCount, double** pSample, double** pTarget);

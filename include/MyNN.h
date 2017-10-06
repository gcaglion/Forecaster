#pragma once
#include <Windows.h>
#include <math.h>
#include <MyMatrix.h>
#include <MyUtils.h>
#include <MyLogDefs.h>	// to define tLogMSE and tLogRUN
#include <MyLogger.h>
#include <DataShape.h>	// to define tDataShape
#include <MyEngines.h>	// to define tEngineHandle
#include <MyNN_Parms.h>

typedef struct {
	double*** LVV_W;
	double*** LVV_dW;
	double*** LVV_dJdW;
	double* p;
	double* r;
	double* s;
	double* dW;
	double* TotdW;
	double* newW;
	double* oldW;
	double* prev_r;
	double* alphap;
	double* bp;
	double* lp;
	double* ap;
	double* dE0;
	double* dE1;
	double* dE;
	double* E0;
	double* E1;
	double* E;
	double* sigmap;
	double pnorm;
	double rnorm;
	double dWnorm;
} tSCGDMem;

typedef struct {
	//-- node levels -> [Levels][Time]
	double*** a;
	double*** F;
	double*** dF;
	double*** edF;
	double*** c;
	//-- outer node only -> [TRAINING/VALIDATION][Time][OutNeuron]
	double*** e;
	double*** u;
	//-- error stuff
	double**** se;	// [TRAINING/VALIDATION][Time][Sample][OutNeuron]
	double***  sse;	// [TRAINING/VALIDATION][Time][Sample]
	double***  gse;	// [TRAINING/VALIDATION][Time][OutNeuron]
	double**   tse;	// [TRAINING/VALIDATION][Time]

	//-- weight levels -> [Levels-1][Time]
	double**** W;
	double**** dW;
	double**** dJdW;
	double**** BdW;
	//-- temp matrices
	double*** tmpM0;
	double*** tmpM1;
	double*** tmpM2;
	double*** tmpM3;
	//-- Hessian
	double***** H;
	//-- Qing stuff
	double**** Q_dJdW;
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
	tSCGDMem* scgd;
} NN_Mem;

typedef struct {	
	NN_Mem NN;

	int		BPCount;
	int		SCGD_progK;
	int		sampleid;
	int		ScreenPos;
	HANDLE	ScreenMutex;
	int useValidation;

	int BatchSize;
	int* rsl;	// randomized samples list
	int sampleCnt;
	double** sample[2];
	double** target[2];

} NN_MxData;

__declspec(dllexport) void __stdcall setNNTopology(NN_Parms* NN);
__declspec(dllexport) void __stdcall mallocNNLog(tCoreLog* coreLog, int levelsCnt, int* nodesCnt, bool mallocIntP, int tscnt);
__declspec(dllexport) void __stdcall freeNNLog(tCoreLog* coreLog, int levelsCnt, int* nodesCnt, bool freeIntP, int tscnt);
__declspec(dllexport) int Train_NN(int pCorePos, int pTotCores, HANDLE pScreenMutex, tDebugInfo* pDebugParms, NN_Parms* pNNParms, tCoreLog* pNNLogs, bool loadW, int pSampleCount, double** pSampleData, double** pTargetData, int useValidation, double** pSampleDataV, double** pTargetDataV);
__declspec(dllexport) void Run_NN(tDebugInfo* pDebugParms, NN_Parms* NNParms, tCoreLog* NNLogs, tDataShape* pInputData, int pid, int tid, int pSampleCount, double** pSample, double** pTarget);

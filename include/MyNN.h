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
#include <cuRNN.h>

typedef struct {
	double*** LVV_W;
	double*** LVV_dW;
	double*** LVV_dJdW;
	double*** LVV_GdJdW;
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
	//-- outer node only -> [Time]
	double** e;
	double** u;
	double* norm_e;
	double** ge;
	double* norm_ge;
	double* mse;
	double** Ve;
	double** Vu;
	//-- weight levels -> [Levels-1][Time]
	double**** W;
	double**** dW;
	double**** dJdW;
	double**** GdJdW;
	double**** BdW;
	//-- temp matrices
	double*** tmpM0;
	double*** tmpM1;
	double*** tmpM2;
	double*** tmpM3;
	//-- Hessian
	double***** H;
	//-- Jacobian
	double** J;		// [SampleCount][WeightsCountTotal]
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

	int sampleCnt;
	double** sample;
	double** target;

} NN_MxData;

#undef EXPORT
#define EXPORT __declspec(dllexport)

EXPORT void getNNOutputRange(NN_Parms* NNParms, double* oScaleMin, double* oScaleMax);
EXPORT void setNNTopology(NN_Parms* NN);
EXPORT void mallocNNLog(tCoreLog* coreLog, int levelsCnt, int* nodesCnt, bool mallocIntP, int tscnt);
EXPORT void freeNNLog(tCoreLog* coreLog, int levelsCnt, int* nodesCnt, bool freeIntP, int tscnt);

EXPORT int Train_NN(int pCorePos, int pTotCores, HANDLE pScreenMutex, tDebugInfo* pDebugParms, NN_Parms* pNNParms, tCoreLog* pNNLogs, bool loadW, int pSampleCount, double** pSampleData, double** pTargetData, int useValidation, double** pSampleDataV, double** pTargetDataV);
EXPORT void Run_NN(tDebugInfo* pDebugParms, NN_Parms* NNParms, tCoreLog* NNLogs, tDataShape* pInputData, int pid, int tid, int pSampleCount, double** pSample, double** pTarget);

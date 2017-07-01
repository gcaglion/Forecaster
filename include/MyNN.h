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
	double* norm_e;
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
	//-- Hessian
	double***** H;
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
	int useValidation;
} NN_MxData;

__declspec(dllexport) void __stdcall setNNTopology(NN_Parms* NN);
__declspec(dllexport) void __stdcall mallocNNLog(tCoreLog* coreLog, int levelsCnt, int* nodesCnt, int tscnt);
__declspec(dllexport) void __stdcall freeNNLog(tCoreLog* coreLog, int levelsCnt, int* nodesCnt, int tscnt);
__declspec(dllexport) int Train_NN(int pCorePos, int pTotCores, HANDLE pScreenMutex, tDebugInfo* pDebugParms, NN_Parms* pNNParms, tCoreLog* pNNLogs, int pSampleCount, double** pSampleData, double** pTargetData, int useValidation, double** pSampleDataV, double** pTargetDataV);
__declspec(dllexport) void Run_NN(tDebugInfo* pDebugParms, NN_Parms* NNParms, tCoreLog* NNLogs, tDataShape* pInputData, int pid, int tid, int pSampleCount, double** pSample, double** pTarget);

#pragma once
#include <MyLogDefs.h>	// defines tDebugInfo
#include <DataShape.h>	// defines tDataShape
#include <MyEngines.h>	// defines tEngineHandle
#include <MyGA_Parms.h>

typedef struct {
	int ActualGenerations;	// If training was stopped before reaching MaxEpochs (because TargetMSE was reached, or because of Training Divergence), this saves the actual Epochs run
	tLogMSE* MSEOutput;		// [Epoch]
	tLogRUN* RunOutput;		// [pos]
	tLogInt* IntP;			// [TimeStep]	-- not used yet
} GA_Logs;

__declspec(dllexport) int Train_GA(tDebugInfo* pDebugParms, GA_Parms* pGAParams, GA_Logs* pGALogs, tDataShape* pInputData, int pTestId, int pSampleCount, double*** pSampleData, double*** pTargetData, double*** pSampleDataV, double*** pTargetDataV);


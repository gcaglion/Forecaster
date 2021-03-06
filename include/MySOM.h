#pragma once
#include <MySOM_Parms.h>
#include <DataShape.h>

//-- Decay functions for the Topological Distance
#define TD_DECAY_CONSTANT 0
#define TD_DECAY_LINEAR 1
#define TD_DECAY_STEPPED 2
#define TD_DECAY_EXP 3
//-- Decay Functions for Learning Rate
#define LR_DECAY_CONSTANT 0
#define LR_DECAY_LINEAR 1
#define LR_DECAY_STEPPED 2
#define LR_DECAY_EXP 3

typedef struct {
	int ActualEpochs;		// If training was stopped before reaching MaxEpochs (because TargetMSE was reached, or because of Training Divergence), this saves the actual Epochs run
	tLogMSE* MSEOutput;		// [Epoch]
	tLogRUN* RunOutput;		// [pos]
	tLogInt* IntP;			// [TimeStep]	-- not used yet
	tNNWeight*** FinalW;	// [NeuronLevel][FromNeuron][ToNeuron] -- this is saved only once at the end of the training
} SOM_Logs;

__declspec(dllexport) int Train_SOM(tDebugInfo* pDebugParms, SOM_Parms* pSOMParams, tDataShape* pInputData, int pTestId, int pSampleCount, double*** pSampleData, double*** pTargetData, double*** pSampleDataV, double*** pTargetDataV);
__declspec(dllexport) void Run_SOM(tDebugInfo* pDebugParms, SOM_Parms* pSOMParms, tDataShape* pInputData, int pOOS, int pid, int ptid, int pDatasetId, int pTestId, int pSampleCount, double** pSample, double** pTarget, double* oForecast);
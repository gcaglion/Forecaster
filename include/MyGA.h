#pragma once
#include <MyLogDefs.h>	// defines tDebugInfo
#include <DataShape.h>	// defines tDataShape
#include <MyEngines.h>	// defines tEngineHandle

//-- GA engine specific parameters
typedef struct {
	int InputCount;
	int OutputCount;
	char BestChrPath[MAX_PATH];
	int MaxGenerations;
	int ActualGenerations;
	int BestGen;
	int BestCid;
	double BestFitness;
	double FitnessThreshold;
	int MaxReRuns;
	int PopulationSize;
	int SlidingFactor;
	int Levels;
	int FitnessSkewingFactor;
	double TargetFitness;
	double CrossOverProbability;
	double MutationProbability;
	double CrossSelfRate;
	int RouletteMaxTries;
	int ADF_ForcePresence;
	double ADF_Tree_FixedValues_Ratio;
	double ADF_Tree_DataPoints_Ratio;
	double ADF_Leaf_FixedValues_Ratio;
	int* TrainingTid;		// [DataSet];
} GA_Parms;

typedef struct {
	int ActualGenerations;	// If training was stopped before reaching MaxEpochs (because TargetMSE was reached, or because of Training Divergence), this saves the actual Epochs run
	tLogMSE* MSEOutput;		// [Epoch]
	tLogRUN* RunOutput;		// [pos]
	tLogInt* IntP;			// [TimeStep]	-- not used yet
} GA_Logs;

__declspec(dllexport) int Train_GA(tDebugInfo* pDebugParms, GA_Parms* pGAParams, GA_Logs* pGALogs, tDataShape* pInputData, int pTestId, int pSampleCount, double*** pSampleData, double*** pTargetData, double*** pSampleDataV, double*** pTargetDataV);


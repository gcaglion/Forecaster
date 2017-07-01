#pragma once
#include <Windows.h>

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


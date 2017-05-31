#pragma once
#include <windows.h>	// defines MAX_PATH
#include <MyCores.h>

//-- GA engine specific parameters
class cGA: public cCore {
public:
	int InputCount;
	int OutputCount;
	char BestChrPath[MAX_PATH];
	int MaxEpochs;
	int ActualEpochs;
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

	//-- virtual functions, common to all cores
	void init();
	int  train(tDebugInfo* pDebugParms, int DatasetId, int sampleCnt, int sampleLen, int targetLen, double** S_t, double** T_t, int useValidation, double** S_v, double** T_v);
	int  run(tDebugInfo* pDebugParms, int sampleCnt, int sampleLen, int targetLen, double** S, double** T, void* img);
	int  LoadImage(tDebugInfo* DebugParms, tDBConnection* DBConn, int pid, int tid);
	void mallocLogs(int dscnt);
	virtual void getScaleRange(double* oScaleMin, double* oScaleMax);
	//--
} ;

//__declspec(dllexport) int Train_GA(tDebugInfo* pDebugParms, GA_Parms* pGAParams, GA_Logs* pGALogs, tDataShape* pInputData, int pTestId, int pSampleCount, double*** pSampleData, double*** pTargetData, double*** pSampleDataV, double*** pTargetDataV);


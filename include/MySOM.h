#pragma once
#include <MyCores.h>

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

class cSOMLog : public cCoreLog {
	int levelsCnt;
	int* nodesCnt;
public:
	double*** FinalW;
	cSOMLog(int pLevelsCnt, int* pNodesCnt, int pTimeSteps);
private:
	~cSOMLog();
};

//-- SOM engine specific parameters
class cSOM {
public:
	int InputCount;
	int OutputCount;	// Should be something like 21 (-10÷+10, plus 0)
	double OutputWidth;	// Expected variability; should be proportional to timeframe
	int MaxEpochs;
	int ActualEpochs;
	// Topological Distance
	int TDFunction;	
	double BaseTD;
	// Learning Rate
	int LRFunction;
	double BaseLR;

	cSOMLog**   SOMLog;	//-- [DatasetId] NN-specific log (FinalW, IntP)

};


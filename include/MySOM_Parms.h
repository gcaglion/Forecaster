#pragma once

//-- SOM engine specific parameters
typedef struct {
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
	tLogMSE** MSEOutput;	// [DataSet][Epoch]
	tLogRUN** RunOutput;	// [DataSet][pos]
	tSOMWeight*** FinalW;	// [DataSet][FromNeuron][ToNeuron] -- this is saved only once at the end of the training
	int* TrainingTid;		// [DataSet];
} SOM_Parms;

#pragma once
#include <Windows.h>

//-- Layers
#define MAX_LEVELS  6

//-- time step
#define TimeSteps  6
#define t0 0 //	(t)
#define t1 1 //	(t - 1)
#define t2 2 //	(t - 2)
#define t3 3 //	used for backup
#define t4 4 //	used for backup
#define ttmp 5

//-- Training Protocols
#define TP_STOCHASTIC	0
#define TP_BATCH		1
#define TP_ONLINE		2

//-- Backpropagation algorithms
#define BP_STD   0
#define BP_QING	 1
#define BP_SCGD		 5 // Scaled Conjugate Gradient Descent
#define BP_QUICKPROP 6
//--

//-- Activation Functions
#define NN_ACTIVATION_TANH 1	// y=tanh(x)				=> range is [-1 � 1]
#define NN_ACTIVATION_EXP4 2	// y = 1 / (1+exp(-4*x))	=> range is [ 0 � 1]

//-- NN engine core parameters
typedef struct {
	int InputCount;
	int OutputCount;
	int LevelsCount;
	double LevelRatio[MAX_LEVELS];	// Ratio between # of nodes at current and previous level
	char LevelRatioS[60];			// comma-separated string with level ratios
	int NodesCount[MAX_LEVELS];	// # of nodes at each level
	int NodesCountTotal;		// total # of nodes
	int WeightsCountTotal;		// total # of weights
	int MaxEpochs;
	double TargetMSE;
	int UseContext;
	int BP_Algo;
	int TrainingProtocol;
	int StopAtDivergence;
	double LearningRate;
	double LearningMomentum;
	int ActivationFunction;
	double HCPbeta;		// used by Qing
	double mu;			// used by QuickProp
	int    SCGDmaxK;	// used by SCGD
} NN_Parms;
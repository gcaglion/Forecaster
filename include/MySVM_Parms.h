#pragma once

//-- SVM engine specific parameters
typedef struct sSVMParms{
	int DebugLevel;
	int InputCount;
	//int OutputCount;
	int MaxEpochs;
	//--
	double C;				// -c
	int SlackNorm;			// -p
	int RescalingMethod;	// -o
	int LossFunction;		// -l
	int LearningAlgo;		// -w
	double epsilon;			// -e
	int NewConstrEtrain;	// -k
	int CCacheSize;		// -f
	int BatchSize;			// -b
	int NewVarSinQP;		// -n
	int KernelCacheSize;	// -m
	int svmIterToShrink;	// -h
	//--
	int KernelType;			// -t
	int PolyDegree;			// -d
	double RBFGamma;		// -g
	double CoefLin;			// -s
	double CoefConst;		// -r
	char CustomKernel[50];	// -u
} SVM_Parms;

#pragma once
#include <stdio.h>
#include <Windows.h>
#include <DBConnection.h>
#include <MyUtils.h>

#define LOG_INFO 0
#define LOG_ERROR 1

// Logs Destinations
#define LOG_TO_TEXT   1
#define LOG_TO_ORCL	  2

typedef struct sDebugInfo {
	int DebugLevel;		//-- 0:Nothing ; 1:Screen-Only ; 2:File-Only ; 3:File+Screen
	int DebugDest;		//-- ORCL | TEXT
	tDBConnection* DebugDB;
	char fPath[MAX_PATH];
	char fName[MAX_PATH];
	char FullfName[MAX_PATH];
	FILE* fHandle;
	int  fIsOpen;
	//char* DBUser;
	//char* DBPassword;
	//char* DBConnString;
	void* DBCtx;
	int ThreadSafeLogging;
	int SaveMSE;
	int SaveRun;
	int SaveInternals;
	HANDLE Mtx;		// Mutex handle used by LogWrite()
#ifdef __cplusplus
	sDebugInfo() {
		DebugDB = new tDBConnection();
	}

	~sDebugInfo() {
		delete(DebugDB);
	}
#endif
} tDebugInfo;

//=== tLogMSE and tLogRUN should be common across different Engines
//-- MSE Logging parameters
typedef struct{
	int ProcessId;
	int ThreadId;
	int TestId;
	int LayerId;
	int CoreId;
	int Epoch; 
	double MSE_T;
	double MSE_V;
} tLogMSE;
//-- RUN Logging parameters
typedef struct{
	int ProcessId; 
	int ThreadId; 
	int TestId;
	int LayerId;
	int CoreId;
	int Pos;
	//int Step;	// only Step 0 is used for prediction logging; the rest is needed for multi-layer engines
	double Actual; double Predicted; double Error;
	//double Actual_TR; double Predicted_TR; double Error_TR;	// "_C" stands for "Clean", that is, before any un-transformation or un-scaling
	double Actual_TRS; double Predicted_TRS; double Error_TRS;	
	double BarWidth;
	double ErrorP;
	int NetProcessId; int NetThreadId; 
} tLogRUN;
//-- Internals Logging parameters
typedef struct{
	int ProcessId; int ThreadId; int TimeStep; 
	// Qing stuff
	int sigma10; double ro10; double D10W; double adzev10; int hcp10; int sigma21; double ro21; double adzev21N; double norm_e;
	// SCGD stuff
	int Epoch; int BPid; int K;
	double delta; double mu; double alpha; double beta; double lambda; double lambdau; double rnorm; double enorm; double comp;
} tLogInt;
//===

//-- NN Weights Logging parameters
typedef struct {
	int ProcessId; int ThreadId;  int TimeStep;
	int NeuronLevel; int FromNeuron; int ToNeuron; double Weight; double CtxValue;
} tNNWeight;

//-- Core Logs
typedef struct sCoreLog {
	//-- common
	int				ActualEpochs;		// If training was stopped before reaching MaxEpochs (because TargetMSE was reached, or because of Training Divergence), this saves the actual Epochs run
	tLogMSE*		MSEOutput;		// [Epoch]
	tLogRUN*		RunOutput;		// [pos]
	//-- NN-specific
	tNNWeight***	FinalW;	// [NeuronLevel][FromNeuron][ToNeuron] -- this is saved only once at the end of the training
	int				IntCnt;	// number of IntP elements
	tLogInt*		IntP;	// [TimeStep]
	//-- SVM-specific
	double ThresholdB;
	int SVcount;
	double* alphaY;
	double** SV;
} tCoreLog;


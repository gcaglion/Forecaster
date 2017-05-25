#pragma once

//-- MSE Logging parameters
typedef struct sLogMSE {
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
typedef struct sLogRUN {
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

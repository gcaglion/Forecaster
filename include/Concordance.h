#pragma once

typedef	struct {
	char CurrentData[6 + 1];
	char CurrentStart[12 + 1];			// Date
	char TimeFrame[3 + 1];
	char OutputType[5 + 1];
	char PredictorData[6 + 1];
	char PredictorStart[12 + 1];		// Date
	int   PatternLength;
	int   PatternShift;
	double KTau;
	double SRho;
	double Gini;
	double WeakC;
} tConcordanceRec;

typedef	struct {
	int  PredType;
	char PredStart[12 + 1];
	int  PredLen;
} tPredictor;

typedef	struct {
	tDebugInfo* DebugParms;
	tFXData* FXDBInfo;
	int OutputType;
	int PastDepth;
} tConcCalcParms;

#pragma once

#include <stdlib.h>
#include "stdio.h"
#include "windows.h"
#include "winbase.h"
#include "time.h"
#include <math.h>

#include <MyUtils.h>
#include <MyLogger.h>
#include <FXData.h>
#include <MyOraUtils.h>

#define FH 0
#define FL 1

//-- Concordance Measures
#define SRHO	0
#define KNUMER	1
#define KTAU	2
#define WEAKC	3
#define GINI	4

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
	tFXData* FXParmsC;
	tFXData* FXParmsH;
	tDBConnection* ConcDBParms;
	int InputCount;
	int OutputCount;
	char CurrDate0[12+1];
	int CurrMinLen;
	int CurrMaxLen;
	int HistMaxLen;
	int Measure;
} CONC_Parms;

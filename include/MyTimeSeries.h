#pragma once

#include <stdio.h>
#include <Windows.h>
#include <math.h>
#include <MyUtils.h>
#include <MyDebug.h>
#include <DataShape.h>
#include <FileData.h>
#include <FXData.h>
#include <TSF.h>
#include <ExportDef.h>

//-- History/Validation datasets
#define HD 0
#define VD 1

//-- Data Tranformations
#define DT_NONE		 0
#define DT_DELTA	 1
#define DT_LOG		 2
#define DT_DELTALOG	 3

class cTimeSerie {
public:
	int     TSlen;
	double  BaseVal;
	double* Data;
	double* BarWidth;
	double* Data_TR;
	double* Data_TRS;
	double ScaleMin;
	double ScaleMax;
	double  ScaleM;
	double  ScaleP;
	double MinVal;
	double MaxVal;

	//-- transformation  / scaling
	void TransformScale(int dt, double sMin, double sMax);
	//void UnTransformScale(int dt);
	
	//-- constructors / destructor
	EXPORT cTimeSerie(int len, double* data, double* bw, double bv);	// allocates arrays, anc copies data
	EXPORT cTimeSerie(int len);										// just allocation, no actual data copy
	cTimeSerie(cTimeSerie* ts1, cTimeSerie* ts2);				// creation by concatenation
	~cTimeSerie();
} ;


EXPORT int FXDataCompact(char* INfilename, int INtimeframe, char* OUTfilename, int OUTtimeframe);

//-- Timeseries Statistical Features
EXPORT double TSMean(int VLen, double* V);
EXPORT double TSMeanAbsoluteDeviation(int VLen, double* V);
EXPORT double TSVariance(int VLen, double* V);
EXPORT double TSSkewness(int VLen, double* V);
EXPORT double TSKurtosis(int VLen, double* V);
EXPORT double TSTurningPoints(int VLen, double* V);
EXPORT double TSShannonEntropy(int VLen, double* V);
EXPORT double TSHistoricalVolatility(int VLen, double* V);
EXPORT void   CalcTSF(int TSFcnt, int* TSFid, tDataShape* pDataParms, int pTSLen, double* pTS, double* pTSF);

// newest version -------------------------------------------------------------------------------------------------------------------
EXPORT void dataTransform(int dt, int dlen, double* idata, double baseVal, double* oMinVal, double* odata);
EXPORT void dataUnTransform(int dt, int from_i, int to_i, double* idata, double baseVal, double iMinVal, double* iActual, double* odata);
//-----------------------------------------------------------------------------------------------------------------------------------

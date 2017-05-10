//-- Data Shape parameters
#pragma once

#define MAX_DATASETS 8

//-- Data Tranformations
#define DT_NONE		 0
#define DT_DELTA	 1
#define DT_LOG		 2
#define DT_DELTALOG	 3

typedef struct{
	int DataSourceType;
	void* DataSource;
	int DatasetsCount;
	int HistoryLen;
	int SampleLen;
	int SampleCount;
	int PredictionLen;
	int ValidationShift;
	int DataTransformation;
	double wiggleRoom;
} tDataShape;

//-- Timeseries Statistical Features
typedef struct{
	double Data;
	double Data_S;
	double ScaleMin;
	double ScaleMax;
	double ScaleM;
	double ScaleP;
	double* kaz;
} tTSF;

typedef struct{
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
	tTSF*  TSF;
}tTimeSerie;
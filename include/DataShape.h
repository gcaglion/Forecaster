//-- Data Shape parameters
#pragma once

#define MAX_DATASETS 8

#define SOURCE_DATA_FROM_FXDB 0
#define SOURCE_DATA_FROM_FILE 1
#define SOURCE_DATA_FROM_MT   2

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

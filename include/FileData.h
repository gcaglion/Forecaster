// File Retrieval Properties for File-based DataSources
#pragma once
#include <Windows.h>

#define MAXDATASETS 8
typedef struct sFileData {
	char FileName[MAX_PATH];
	int FileDataSetsCount;
	//int FileDataSet[MAXDATASETS];	// The first value is the number of BarDataTypes that are being used, the rest are the datatype codes	
	int* FileDataSet;
#ifdef __cplusplus
	sFileData() {
		FileDataSet = (int*)malloc(MAXDATASETS*sizeof(int));
	}

	~sFileData() {
		free(FileDataSet);
	}
#endif
} tFileData;

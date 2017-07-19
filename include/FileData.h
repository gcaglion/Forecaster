// File Retrieval Properties for File-based DataSources
#pragma once
#include <Windows.h>

#define MAXDATASETS 8
typedef struct sFileData {
	char FileName[MAX_PATH];
	int FileDataSetsCount;
	int FieldSep;	// COMMA|TAB|SPACE
	int* FileDataSet;
#ifdef __cplusplus
	sFileData() {
		FileDataSet = MallocArray<int>(MAXDATASETS);
	}

	~sFileData() {
		free(FileDataSet);
	}
#endif
} tFileData;

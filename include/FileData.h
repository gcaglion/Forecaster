// File Retrieval Properties for File-based DataSources
#pragma once
#include <Windows.h>

#define MAXDATASETS 8
typedef struct sFileData {
	char FileName[MAX_PATH];
	int FileDataSetsCount;
	int FieldSep;	// COMMA|TAB|SPACE
	int* FileDataSet;
	int CalcFileDataBW;
	int* FileBWDataSet;
#ifdef __cplusplus
	sFileData() {
		FileDataSet = MallocArray<int>(MAXDATASETS);
		FileBWDataSet = MallocArray<int>(MAXDATASETS);
	}

	~sFileData() {
		free(FileDataSet);
		free(FileBWDataSet);
	}
#endif
} tFileData;

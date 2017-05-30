#pragma once
#include <DBConnection.h>

// Bar data
#define MAXBARDATATYPES 6
#define OPEN   0
#define HIGH   1
#define LOW    2
#define CLOSE  3
#define VOLUME 4
#define OTHER  5

// Database retrieval properties
typedef struct sFXData {
	//tDBConnection* FXDB;
	char Symbol[12];
	char TimeFrame[4];
	int IsFilled;
	int BarDataTypeCount;
	int* BarDataType;
#ifdef __cplusplus
	sFXData() {
		//FXDB = new tDBConnection();
		BarDataType = MallocArray<int>(MAXBARDATATYPES);
	}

	~sFXData() {
		//delete(FXDB);
		free(BarDataType);
	}
#endif
} tFXData;

// Bar structure
typedef struct {
	char NewDateTime[12 + 1];
	double Open;
	double High;
	double Low;
	double Close;
	double OpenD;
	double HighD;
	double LowD;
	double CloseD;
	double Volume;
	double VolumeD;
} tBar;

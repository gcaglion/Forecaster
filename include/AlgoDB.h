#pragma once
// Bar data
#define BARDATATYPES 6
#define OPEN   0
#define HIGH   1
#define LOW    2
#define CLOSE  3
#define VOLUME 4
#define OTHER  5

// Database Connection - generic (can be used for both data retrieval and logging)
typedef struct{
	char* DBUser;
	char* DBPassword;
	char* DBConnString;
	void* DBCtx;
} tDBConnection;

// Database retrieval properties
typedef struct{
	tDBConnection FXDB;
	char* Symbol;
	char* TimeFrame;
	int IsFilled;
	int pScale;
	int BarDataTypeCount;
	int BarDataType[BARDATATYPES];	// The first value is the number of BarDataTypes that are being used, the rest are the datatype codes
} tFXDB_Parms;

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

// File Retrieval Properties
typedef struct{
	char* FileName;
	
} tDataFile_Parms;

#pragma once
#include <MyDebug.h>
#include <DBConnection.h>
#include <ExportDef.h>
#include <MyCoreLogs.h>

#define CORE_NN  0
#define CORE_GA  1
#define CORE_SOM 2
#define CORE_SVM 3

class cCore {
	int Type;
	int InputCount;
	int OutputCount;

	int MSECount;
	int TimeStepsCount;

	cCoreLog*** Log;

	virtual void init() = 0;
	virtual int  train(tDebugInfo* pDebugParms, int DatasetId, int sampleCnt, int sampleLen, int targetLen, double** S_t, double** T_t, int useValidation, double** S_v, double** T_v) = 0;
	virtual int  run(tDebugInfo* pDebugParms, int sampleCnt, int sampleLen, int targetLen, double** S, double** T, void* img) = 0;
	virtual int  loadImage(tDebugInfo* DebugParms, tDBConnection* DBConn, int pid, int tid) = 0;

};

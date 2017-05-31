#pragma once

#include <ExportDef.h>
#include <MyCoreLogs.h>
#include <MyDebug.h>

//-- Core types
#define CORE_NN 0
#define CORE_GA 1
#define CORE_SVM 2
#define CORE_SOM 3

class cCore {
public:
	int CoreType;
	int MSECount;
	int TimeStepsCount;
	int SampleLen;
	int TargetLen;
	int RunCount;
	//int InputCount;
	//int OutputCount;

	void* core;			// pointer to cNN | cSVM | ...
	//cCoreLog** coreLog;	// pointer to cCoreLog[datasetscount] ??

	EXPORT virtual void init() =0;
	EXPORT virtual int  train(tDebugInfo* pDebugParms, int DatasetId, int sampleCnt, int sampleLen, int targetLen, double** SampleT, double** TargetT, int useValidation, double** SampleV, double** TargetV) =0;
	EXPORT virtual int  run(tDebugInfo* pDebugParms, int sampleCnt, int sampleLen, int targetLen, double** S, double** T, void* img) =0;	//-- img should be cast inside each core's run(), to the proper weight structure (double**, double***, ...)
	//EXPORT virtual int  setParms(tDebugInfo* DebugParms, int pid, int tid) =0;
	EXPORT virtual int  LoadImage(tDebugInfo* DebugParms, tDBConnection* DBConn, int pid, int tid) =0;
	EXPORT virtual void mallocLogs(int dscnt) =0;
	EXPORT virtual void getScaleRange(double* oScaleMin, double* oScaleMax);	// used only by CORE_NN

	//-- constructors / destructors
	EXPORT cCore(int cType, int dscnt, int inputCnt, int outputCnt);
	EXPORT cCore();
	EXPORT ~cCore();
};
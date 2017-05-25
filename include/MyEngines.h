#pragma once

#include <ExportDef.h>
#include <MyUtils.h>
#include <MyCores.h>
#include <TSF.h>

#define ENGINE_NN	 0
#define ENGINE_GA	 1
#define ENGINE_SVM	 2
#define ENGINE_SOM	 3
#define ENGINE_WNN   4
#define ENGINE_XIE	 5

#define WTypeDescLen 30

//-- Engine Handle for Saving / Retrieval
typedef struct sEngineHandle {
	int ProcessId;
	int TestId;
	int DatasetId;
	int ThreadId;
} tEngineHandle;

class cEngine {
public:
	int EngineType;
	int InputCount;		// Engine-wide
	int OutputCount;	// Engine-wide
	int LayersCount;
	int* CoresCount;
	cCore*** Core;	// [LayerId][CoreId]
	int TotalCoresCount;
	int TSFcnt;
	int* TSFid;
	int WNN_DecompLevel;
	char* WNN_WaveletType;

	EXPORT void setLayout();
	EXPORT void mallocCoresLogs(int dscnt);
	EXPORT int  LoadCoresParms(tDebugInfo* pDebugParms, int pid);
	EXPORT int  LoadCoresImage(tDebugInfo* pDebugParms, int pid);
	EXPORT int  Save(tDebugInfo* DebugParms, int pid, int testid, int dscnt);
	EXPORT int  SaveMSELogs(tDebugInfo* DebugParms, int pid, int dscnt);
	EXPORT int  SaveRunLogs(tDebugInfo* DebugParms, int pid, int dscnt, int pHistoryLen);
	EXPORT int SaveImage(tDebugInfo* DebugParms, int pid, int dscnt, int testid);

	EXPORT cEngine(int DataSampleLen, int DataTargetLen);
	~cEngine();

private:
};
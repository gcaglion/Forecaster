#pragma once
#include <TSF.h>
#include <MyNN.h>	// to define tNNWeight

#define MAX_LAYERS 8

//-- Forecast Engines
#define ENGINE_NN	 0
#define ENGINE_GA	 1
#define ENGINE_SVM	 2
#define ENGINE_SOM	 3
#define ENGINE_WNN   4
#define ENGINE_XIE	 5
//-- Core types
#define CORE_NN 0
#define CORE_GA 1
#define CORE_SVM 2
#define CORE_SOM 3


//-- Engine Handle for Saving / Retrieval
typedef struct {
	int ProcessId;
	int TestId;
	int DatasetId;
	int ThreadId;
	int EngineType;
} tEngineHandle;

typedef struct sCore {
	int   CoreType;
	void* CoreSpecs;	// [pointer-to <XXX>_Parms]
	tCoreLog* CoreLog;		// [Dataset]

	int MSECount;
	int TimeStepsCount;
	int SampleLen;
	int TargetLen;
	int RunCount;
} tCore;

//-- Engine Architecture
typedef struct sEngineDef {
	int EngineType;

	int LayersCount;
	int* CoresCount;
	tCore** Core;	// [LayerId][CoreId]
	int TotalCoresCount;
	int TSFcnt;
	int* TSFid;
	void*   EngineArch;	// only used for multi-layer engines. points to a <XXX>_Arch structure	
#ifdef __cplusplus
	sEngineDef() {
		TSFid = MallocArray<int>(MAX_TSFCOUNT);
	}

	~sEngineDef() {
		free(TSFid);
	}
#endif

} tEngineDef;

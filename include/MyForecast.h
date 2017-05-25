#pragma once
#include <ExportDef.h>
#include <MyDebug.h>
#include <MyParamMgr.h>
#include <MyTimeSeries.h>
#include <MyEngines.h>
#include <MyDataAbstraction.h>
//-- composite engines
#include <MyWNN.h>
#include <MyXIE.h>

typedef struct {
	tDebugInfo* DebugParms;
	cEngine* EngineParms;
	int LayerId; int CoreId; int DatasetId;
	int CorePos; int TotCores; HANDLE ScreenMutex;
	int useValidation;
	int SampleCount;
	int SampleLen;  double** SampleT; double** SampleV;
	int TargetLen;  double** TargetT; double** TargetV;
	tEngineHandle TrainInfo;
	int TrainSuccess;
	int ActualEpochs;
} tTrainParams;

typedef struct {
	tDebugInfo* DebugParms;
	cEngine* EngineParms;
	tDataShape* InputData;
	int LayerId;
	int CoreId;
	int DatasetId;
	int pid;
	int tid;
	int SampleCount;
	int SampleLen; int TargetLen;
	double** Sample;
	double** Target;
} tRunParams;

EXPORT int getForecast(int paramOverrideCnt, char** paramOverride, void* LogDBCtx, int pTestId, double** pHistoryData, double* pHistoryBaseVal, double** pHistoryBW, double** pValidationData, double* pValidationBaseVal, int haveActualFuture, double** pFutureData, double** pFutureBW, double** oPredictedData);

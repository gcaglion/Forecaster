#pragma once
#include <MyParamMgr.h>		// parameters management
#include <MyTimeSeries.h>	// timeseries
#include <MyLogDefs.h>		// defines tDebugInfo
#include <DBConnection.h>	// defines tDBConnection
#include <DataShape.h>		// defines tDataShape
#include <FXData.h>			// defines tFXData
#include <FileData.h>		// defines tFileData
#include <MyLogger.h>		// Logger
//-- Engines --
#include <MyEngines.h>		// defines tEngineHandle
#include <MyNN.h>
#include <MyWNN.h>
#include <MyXIE.h>
#include <MySOM.h>
#include <MySVM.h>
#include <MyGA.h>

#undef EXPORT
#define EXPORT __declspec(dllexport)

#define HD 0
#define VD 1

typedef struct sForecastParms {

	tParamMgr* iniParms;

	int SimulationLength;
	char SimulationStart[12 + 1];
	int HaveFutureData;
	int Action;		// TRAIN_SAVE_RUN | ADD_SAMPLES | JUST_RUN

	tEngineDef EngineParms;
	tDebugInfo DebugParms;
	tDataShape DataParms;
	tFXData FXDBInfo;
	tFileData DataSourceFileInfo;
	tEngineHandle SavedEngine;

	sForecastParms() {
		iniParms = new tParamMgr();
	}
	~sForecastParms() {
		delete iniParms;
	}

} tForecastParms;

EXPORT int  ForecastParamLoader(tForecastParms* ioParms);
EXPORT void ForecastParamFree(tForecastParms* ioParms);

EXPORT int getForecast(int paramOverrideCnt, char** paramOverride, void* LogDBCtx, int pTestId, double** pHistoryData, double* pHistoryBaseVal, double** pHistoryBW, double** pValidationData, double* pValidationBaseVal, int haveActualFuture, double** pFutureData, double** pFutureBW, double** oPredictedData);


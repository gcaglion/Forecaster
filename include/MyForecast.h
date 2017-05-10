#pragma once
#include <MyEnums.h>		// defines tForecastParms
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
#include <MySOM.h>
#include <MySVM.h>
#include <MyGA.h>

#undef EXPORT
#ifdef __cplusplus
#define EXPORT extern "C" __declspec(dllexport)
#else
#define EXPORT __declspec(dllexport)
#endif

__declspec(dllexport) int  ForecastParamLoader(tForecastParms* ioParms);
__declspec(dllexport) void ForecastParamFree(tForecastParms* ioParms);
__declspec(dllexport) int  getForecast(int paramOverrideCnt, char** paramOverride, void* LogDBCtx, int pTestId, double** pHistoryData, double* pHistoryBaseVal, double** pHistoryBW, double** pValidationData, double* pValidationBaseVal, int haveActualFuture, double** pFutureData, double** pFutureBW, double** oPredictedData);
__declspec(dllexport) int  MTgetForecast(int paramOverrideCnt, char** paramOverride, int pTestId, double** pHistoryData, double* pHistoryBaseVal, double** pHistoryBW, double** pValidationData, double* pValidationBaseVal, int haveActualFuture, double** pFutureData, double** pFutureBW, double** oPredictedData);

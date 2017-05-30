#pragma once
#include <stdio.h>
#include <time.h>
#include <Windows.h>
#include <MyDebug.h>
#include <FXData.h>
#include <Concordance.h>
#include <CoreCommonLogs.h>

#undef EXPORT
#ifdef __cplusplus
#define EXPORT extern "C" __declspec(dllexport)
#else
#define EXPORT __declspec(dllexport)
#endif

typedef void * sql_context;
#define MAX_CONTEXTS 6

// Forecast High/Low (replaces OutputType)
#define FH 1	
#define FL 0


//--- DB common functions
EXPORT int  OraConnect(tDebugInfo* DebugInfo, tDBConnection* DBConnInfo);
EXPORT void OraDisconnect(sql_context pCtx);
EXPORT void OraCommit(void* pCtx);

//-- MSE / Run logs
EXPORT int Ora_InsertMSELog(tDebugInfo* DebugParms, tDBConnection* DBConnInfo, int* pInsertCount, tLogMSE* MSEData);
EXPORT int Ora_InsertRunLog(tDebugInfo* DebugParms, tDBConnection* DBConnInfo, int* pInsertCount, int pHistoryLen, tLogRUN* RunData);

//-- Tester / client stuff
EXPORT int Ora_LoadData(tDebugInfo* DebugParms, tDBConnection* DBConnInfo, tFXData* DBParms, int pHistoryLen, int pFutureLen, char* pDate0, int pValidationShift, int pDatasetCount, double** oHistoryData, double** oHistoryBarW, double** oValidationData, double** oFutureData, double** oFutureBarW, double** oWholeData, double** oWholeBarW, double* oPrevValH, double* oPrevValV, double* oPrevBarW);
EXPORT int Ora_GetDates(tDebugInfo* DebugParms, tDBConnection* DBConnInfo, tFXData* SourceParms, char* StartDate, int DatesCount, char** oDate);
EXPORT int Ora_InsertTesterParms(tDebugInfo* DebugParms, tDBConnection* DBConnInfo, int pid, int pSimulationLen, char* pSimulationStart, double pElapsedSecs, int pDoTraining, int pDoRun);
EXPORT int Ora_UpdateTesterDuration(tDebugInfo* DebugParms, tDBConnection* DBConnInfo, int pid, double pElapsedSecs);

//-- Load DataParms, EngineParms
EXPORT int Ora_LoadDataParms(tDebugInfo* DebugParms, tDBConnection* DBConnInfo, int pid, int* oHistoryLen, int* oSampleLen, int* oSampleCount, int* oPRedictionLen, int* oDataTransformation, double* oWiggleRoom);
EXPORT int Ora_LoadEngineParms(tDebugInfo* DebugParms, tDBConnection* DBConnInfo, int pid, int* oEngineType, int* oLayersCount, int* oDecompLevel, char** oWaveletType);
//-- Save DataParms, EngineParms
EXPORT int Ora_InsertDataParms(tDebugInfo* pDebugParms, tDBConnection* DBConnInfo, int pid, int pDatasetId, int pDSType, char* pDSFileName, char* pSymbol, char* pTimeFrame, int pIsFilled, int pBarData, int pDataTransformation, double pwiggleRoom, int pHistoryLen, int pSampleLen, int pPredictionLen);
EXPORT int Ora_InsertEngineParms(tDebugInfo* pDebugParms, tDBConnection* DBConnInfo, int pid, int pEngineType, int pLayersCount, int pWNNDecompLevel, char* pWNNWaveletType);
EXPORT int Ora_InsertEngineThreads(tDebugInfo* pDebugParms, tDBConnection* DBConnInfo, int pid, int testid, int layerid, int coreid, int coretype, int dsid, int tid);

//-- Load CoreParms(s)
EXPORT int Ora_GetCoreThreadId(tDebugInfo* DebugParms, tDBConnection* DBConnInfo, int pid, int testid, int DatasetId, int LayerId, int CoreId);
EXPORT int Ora_LoadCoreParms_NN(tDebugInfo* DebugParms, tDBConnection* DBConnInfo, int pid, int tid,
	int* oInputCount, int* oOutputCount, int* oUseContext, int* oMaxEpochs, int* oBP_Algo, int* oActivationFunction,
	char* oLevelRatioS[256],
	double* oLearningRate, double* oLearningMomentum, double* oHCPBeta, double* oTargetMSE);
EXPORT int Ora_LoadCoreParms_SOM(tDebugInfo* DebugParms, tDBConnection* DBConnInfo, int pid, int tid,
	int* oInputCount, int* oOutputCount, int* oMaxEpochs, int* oTDFunction, int* oLRFunction,
	double* oBaseTD, double* oBaseLR);
EXPORT int Ora_LoadCoreParms_SVM(tDebugInfo* DebugParms, tDBConnection* DBConnInfo, int pid, int tid,
	int* oInputCount, int* oMaxEpochs, int* osvmIterToShrink, int* oKernelType, int* oPolyDegree, int* oKernelCacheSize,
	double* oC, double* oEpsilon, double* oRBFGamma, double* oCoefLin, double* oCoefConst);

//-- Load Core Image(s)
EXPORT int Ora_LoadCoreImage_NN(tDebugInfo* DebugParms, tDBConnection* DBConnInfo, int pid, int tid, double*** oFinalW);
EXPORT int Ora_LoadCoreImage_SOM(tDebugInfo* DebugParms, tDBConnection* DBConnInfo, int pid, int tid, double** oSOMWeight);
EXPORT int Ora_LoadCoreImage_SVM(tDebugInfo* DebugParms, tDBConnection* DBConnInfo, int pid, int tid, double** oSVMWeight);
//-- Save Core Image(s)
EXPORT int Ora_InsertCoreImage_NN(tDebugInfo* DebugParms, tDBConnection* DBConnInfo, int pid, int tid, int levelsCnt, int* nodesCnt, int Wtotalcnt, double*** NNWeight);

//=== Queries
EXPORT int SymbolLookup(tDebugInfo* DebugParms, tDBConnection* DBConnInfo, sql_context pCtx, char* pSymbol, char* oSymbol, int* oScale);
EXPORT int FindBestPredictor(tDebugInfo* DebugParms, tDBConnection* DBConnInfo, sql_context pCtx, char* vCSymbol, char* vHSymbol, char* vTimeFrame, int vIsFilled, char* pCurrentStart, int vTotalBars, char* vMeasure, int vOutputType, int pPredictorsCount, tPredictor* pBestPredictor);
EXPORT int GetCharPFromQuery(tDebugInfo* DebugParms, tDBConnection* DBConnInfo, sql_context pCtx, char* pSQL, char* oRet);
EXPORT int GetStringArrayFromQuery(tDebugInfo* DebugParms, tDBConnection* DBConnInfo, sql_context pCtx, char* pSQL, int ArrLen, char** oRet);
EXPORT int GetIntFromQuery(tDebugInfo* DebugParms, tDBConnection* DBConnInfo, sql_context pCtx, char* pSQL, int* oRet);
EXPORT int GetBarsFromQuery(tDebugInfo* DebugInfo, sql_context pCtx, char* pSQL, int pRecCount, int pSkipFirstN, tBar* oBar);
EXPORT int GetBarsFromQuery2(tDebugInfo* DebugParms, tDBConnection* DBConnInfo, sql_context pCtx, char* pSQL, int* pRecCount, tBar* oBar);

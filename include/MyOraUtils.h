#pragma once
#include <stdio.h>
#include <Windows.h>
#include <time.h>
#include <float.h>
#include <Concordance.h>
#include <FXData.h>
#include <DataShape.h>
#include <MyEngines.h>
#include <MyLogDefs.h>

#include <MyNN_Parms.h>
#include <MySOM_Parms.h>
#include <MySVM_Parms.h>
#include <MyGA_Parms.h>
#include <MyWNN.h>

typedef void * sql_context;
#define MAX_CONTEXTS 6

#undef EXPORT
#ifdef __cplusplus
#define EXPORT extern "C" __declspec(dllexport)
#else
#define EXPORT __declspec(dllexport)
#endif

//=== DB common functions
EXPORT int  __stdcall OraConnect(tDebugInfo* DebugInfo, tDBConnection* DBConnInfo);
EXPORT void __stdcall OraDisconnect(sql_context pCtx);
EXPORT void __stdcall OraCommit(void* pCtx);
//===

//=== Basic Logs
EXPORT int __stdcall Ora_InsertTesterParms(tDebugInfo* DebugParms, int pid, int pSimulationLen, char* pSimulationStart, double pElapsedSecs, int pDoTraining, int pDoRun);
EXPORT int __stdcall Ora_UpdateTesterDuration(tDebugInfo* DebugParms, int pid, double pElapsedSecs);
EXPORT int __stdcall Ora_InsertDataParms(tDebugInfo* pDebugParms, int pid, int pDatasetId, int pDSType, char* pDSFileName, char* pSymbol, char* pTimeFrame, int pIsFilled, int pBarData, int pDataTransformation, double pwiggleRoom, int pHistoryLen, int pSampleLen, int pPredictionLen);
EXPORT int __stdcall Ora_InsertEngineParms(tDebugInfo* DebugParms, int pid, int basepid, int pEngineType, int pInputCount, int pOutputCount, int pAdderCount, int pWNNDecompLevel, char* pWNNWaveletType);
EXPORT int __stdcall Ora_InsertEngineThreads(tDebugInfo* pDebugParms, int aid, int pid, int testid, tEngineDef* pEngineParms, tDataShape* pDataParms);
//--
EXPORT int __stdcall Ora_InsertCoreParms_NN(tDebugInfo* DebugParms, int aid, int pid, int lid, int cid, NN_Parms* NNParms);
EXPORT int __stdcall Ora_InsertCoreParms_SOM(tDebugInfo* DebugParms, int aid, int pid, int lid, int cid, SOM_Parms* SOMParms);
EXPORT int __stdcall Ora_InsertCoreParms_SVM(tDebugInfo* DebugParms, int aid, int pid, int lid, int cid, SVM_Parms* SVMParms);
//--
EXPORT int __stdcall Ora_InsertCoreImage_NN (tDebugInfo* DebugParms, NN_Parms* NNParms, tNNWeight*** NNWeight);
EXPORT int __stdcall Ora_InsertCoreImage_SOM(tDebugInfo* DebugParms, SOM_Parms* SOMParms, tSOMWeight** SOMWeight);
EXPORT int __stdcall Ora_InsertCoreImage_SVM(tDebugInfo* DebugParms, SVM_Parms* SVMParms, tSVMResult* SVMResult, tSVMWeight** SVMWeight);
//--
EXPORT int __stdcall Ora_InsertCoreLogs_NN(tDebugInfo* DebugParms, int BPAlgo, tCoreLog* NNLogs);
EXPORT int __stdcall Ora_InsertCoreLogs_SOM(tDebugInfo* pDebugParms, int BPAlgo, int pInsertCount, tLogInt* IntLogs);
EXPORT int __stdcall Ora_InsertCoreLogs_SVM(tDebugInfo* DebugParms, tSVMResult* SVMResult);
//--
EXPORT int __stdcall Ora_BulkMSEInsert(tDebugInfo* DebugParms, int* pInsertCount, tLogMSE* MSEData);
EXPORT int __stdcall Ora_BulkRunInsert(tDebugInfo* DebugParms, int* pInsertCount, int pHistoryLen, tLogRUN* RunData);
//===

//=== Internals Logs (unused)
EXPORT int __stdcall Ora_BulkInternalsInsert_NN_aF(tDebugInfo* DebugParms, NN_Parms* NN, tCoreLog* NNLogs, int pid, int testid, int pDatasetsCount, int pTimeSteps, double****a, double**** F);
EXPORT int __stdcall Ora_BulkInternalsInsert_NN_W(tDebugInfo* DebugParms, NN_Parms* NN, tCoreLog* NNLogs, int pid, int testid, int pDatasetsCount, int pTimeSteps, double***** W);
EXPORT int __stdcall Ora_BulkInternalsInsert_NN_P(tDebugInfo* DebugParms, NN_Parms* NN, tCoreLog* NNLogs, int pid, int testid, int pDatasetsCount, int pTimeSteps, tLogInt*** IntParms);
//===

//=== Engine Load stuff
EXPORT int __stdcall Ora_LoadDataParms(tDebugInfo* DebugParms, int pid, tDataShape* oDataParms);
EXPORT int __stdcall Ora_LoadEngineParms(tDebugInfo* DebugParms, int pid, tEngineDef* oEngineParms);
//--
EXPORT int __stdcall Ora_LoadCoreParms_NN(tDebugInfo* DebugParms, int pid, int tid, NN_Parms* oNNParms);
EXPORT int __stdcall Ora_LoadCoreParms_SOM(tDebugInfo* DebugParms, int pid, int tid, SOM_Parms* oSOMParms);
EXPORT int __stdcall Ora_LoadCoreParms_SVM(tDebugInfo* DebugParms, int pid, int tid, SVM_Parms* oSVMParms);
//--
EXPORT int __stdcall Ora_getCoreThreadId(tDebugInfo* DebugParms, int pid, int testid, int DatasetId, int LayerId, int CoreId);
//--
EXPORT int __stdcall Ora_LoadCoreImage_NN(tDebugInfo* DebugParms, int pid, int tid, NN_Parms* NNParms, tNNWeight*** oNNWeight);
EXPORT int __stdcall Ora_LoadCoreImage_SOM(tDebugInfo* DebugParms, int pid, int tid, SOM_Parms* SOMParms, tSOMWeight** oSOMWeight);
EXPORT int __stdcall Ora_LoadCoreImage_SVM(tDebugInfo* DebugParms, int pid, int tid, SVM_Parms* SVMParms, tSVMWeight** oSVMWeight);
EXPORT int __stdcall Ora_LoadCoreLogs_SVM(tDebugInfo* DebugParms,  int pid, int tid, SVM_Parms* SVMParms, tSVMResult* oSVMResult);
//===

//=== Queries
EXPORT int __stdcall SymbolLookup(tDebugInfo* DebugParms, sql_context pCtx, char* pSymbol, char* oSymbol, int* oScale);
EXPORT int __stdcall FindBestPredictor(tDebugInfo* DebugParms, sql_context pCtx, char* vCSymbol, char* vHSymbol, char* vTimeFrame, int vIsFilled, char* pCurrentStart, int vTotalBars, char* vMeasure, int vOutputType, int pPredictorsCount, tPredictor* pBestPredictor);
EXPORT int __stdcall GetCharPFromQuery(tDebugInfo* DebugParms, sql_context pCtx, char* pSQL, char* oRet);
EXPORT int __stdcall GetStringArrayFromQuery(tDebugInfo* DebugParms, sql_context pCtx, char* pSQL, int ArrLen, char** oRet);
EXPORT int __stdcall GetIntFromQuery(tDebugInfo* DebugParms, sql_context pCtx, char* pSQL, int* oRet);
EXPORT int __stdcall GetBarsFromQuery(tDebugInfo* DebugInfo, sql_context pCtx, char* pSQL, int pRecCount, int pSkipFirstN, tBar* oBar);
EXPORT int __stdcall GetBarsFromQuery2(tDebugInfo* DebugParms, sql_context pCtx, char* pSQL, int* pRecCount, tBar* oBar);

//=== ConcordanceCalc() stuff ===
EXPORT int __stdcall GetHRecCount(tDebugInfo* DebugParms, void* pCtx, char* pHSymbol, char* pTimeFrame, char* pCFromDate, int pDelta, int pIsFilled, int* HRecCount);
EXPORT int __stdcall LoadCurrentRecord(tDebugInfo* DebugParms, void* pCtx, char* pCSymbol, char* pTimeFrame, char* pCToDate, int pPastDepth, int pDelta, int pIsFilled, int pCRecCount, tBar* oCRec);
EXPORT int __stdcall LoadHistoryRecord(tDebugInfo* DebugParms, void* pCtx, char* pCSymbol, char* pTimeFrame, char* pCFromDate, int pDelta, int pIsFilled, int pHRecCount, tBar* oHRec);
EXPORT int __stdcall LoadTimeSeries(tDebugInfo* DebugParms, void* pCtx, char* pSymbol, char* pTimeFrame, char* pFromDate, int pDelta, int pIsFilled, int pRecCount, tBar* oRec);
//===

//=== OBSOLETE STUFF ===
EXPORT int  __stdcall OraInsert(tDebugInfo* DebugInfo, sql_context pCtx, char* pSQL);
EXPORT void __stdcall OraAllocateCtx(sql_context pCtx[MAX_CONTEXTS]);
EXPORT void __stdcall OraEnableThreads();
EXPORT void __stdcall OraContextFree(sql_context pCtx);
//===


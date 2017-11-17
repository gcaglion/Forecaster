#include <MyOraUtils.h>
#include <MyLogDefs.h>		// tDebugInfo
#include <DBConnection.h>	// tDBConnection
#include <MyEngines.h>		// tEngineHandle
#include <FXData.h>			// tFXData
#include <FileData.h>		// tFileData
#include <DataShape.h>		// tDataShape

#include <MyNN_Parms.h>
#include <MySOM_Parms.h>
#include <MySVM_Parms.h>

//-- Save MSE and Run data should be common across engines
__declspec(dllexport) void __stdcall SaveMSEData(tCoreLog* NNLog, DWORD pid, DWORD tid, int pEpoch, double pMSE_T, double pMSE_V);
__declspec(dllexport) void __stdcall SaveRunData(tCoreLog* NNLog, DWORD pid, DWORD tid, int pPos, double pActual, double* pPredicted);

//=== standard logging, for debug purposes
__declspec(dllexport) void __stdcall LogWrite (tDebugInfo* DebugParms, int LogType, char* msg, int argcount, ...);
__declspec(dllexport) void __stdcall LogClose(tDebugInfo* DebugParms);
__declspec(dllexport) void __stdcall LogCommit(tDebugInfo* pDebugParms);
//===

//=== Log Write functions
__declspec(dllexport) int __stdcall SaveTradeInfo(tDebugInfo* pDebugParms, int pid, int pBarId, char* pLastBarT, double pLastBarO, double pLastBarH, double pLastBarL, double pLastBarC, char* pFirstBarT, double pFirstBarO, double pFirstBarH, double pFirstBarL, double pFirstBarC, double pPrevFH, double pPrevFL, double pCurrBid, double pCurrAsk, double pCurrFH, double pCurrFL, int pTradeType, double pTradeSize, double pTradeTP, double pTradeSL);
__declspec(dllexport) int __stdcall SaveClientInfo(tDebugInfo* pDebugParms, int pid, char* clientName, int pSimulationLen, char* pSimulationStart, double pElapsedS, int pDoTraining, int pDoRun);
__declspec(dllexport) int __stdcall UpdateClientInfo(tDebugInfo* pDebugParms, int pid, double pElapsedS);
__declspec(dllexport) int __stdcall SaveTestLog_DataParms(tDebugInfo* pDebugParms, tDataShape* pDataParms, int pid);
__declspec(dllexport) int __stdcall SaveTestLog_EngineParms(tDebugInfo* pDebugParms, int pid, int basepid, tEngineDef* pEngineParms);
__declspec(dllexport) int __stdcall SaveTestLog_EngineThreads(tDebugInfo* pDebugParms, int aid, int pid, int testid, tEngineDef* pEngineParms, tDataShape* pDataParms);
//--
__declspec(dllexport) int __stdcall InsertCoreParms_NN (tDebugInfo* DebugParms, int aid, int pid, int lid, int cid, NN_Parms* NNParms);
__declspec(dllexport) int __stdcall InsertCoreParms_SOM(tDebugInfo* pDebugParms, int aid, int pid, int lid, int cid, SOM_Parms* SOMParms);
__declspec(dllexport) int __stdcall InsertCoreParms_SVM(tDebugInfo* pDebugParms, int aid, int pid, int lid, int cid, SVM_Parms* SVMParms);
//--
__declspec(dllexport) int __stdcall InsertCoreImage_NN(tDebugInfo* pDebugParms, NN_Parms* NNParms, tNNWeight*** NNWeight0, tNNWeight*** NNWeight1);
__declspec(dllexport) int __stdcall InsertCoreImage_SOM(tDebugInfo* pDebugParms, SOM_Parms* SOMParms, tSOMWeight** SOMWeight);
__declspec(dllexport) int __stdcall InsertCoreImage_SVM(tDebugInfo* pDebugParms, SVM_Parms* SVMParms, tSVMResult* SVMResult, tSVMWeight** SVMWeight);
//--
__declspec(dllexport) int __stdcall InsertCoreLogs_NN(tDebugInfo* pDebugParms, NN_Parms* NNParms, tCoreLog* NNLogs);
__declspec(dllexport) int __stdcall InsertCoreLogs_SOM(tDebugInfo* pDebugParms, SOM_Parms* SOMParms, tCoreLog* SOMLogs);
__declspec(dllexport) int __stdcall InsertCoreLogs_SVM(tDebugInfo* pDebugParms, SVM_Parms* SVMParms, tCoreLog* SVMLogs);
//--
__declspec(dllexport) int __stdcall BulkMSEInsert(tDebugInfo* DebugParms, int pEngineType, int* pInsertCount, tLogMSE* pMSELog);
__declspec(dllexport) int __stdcall BulkRunInsert(tDebugInfo* DebugParms, int* pInsertCount, int pHistoryLen, tLogRUN* RunData);

//=== Log Retrieve functions
__declspec(dllexport) int __stdcall getCoreThreadId(tDebugInfo* DebugParms, int pid, int testid, int DatasetId, int LayerId, int CoreId);
//--
__declspec(dllexport) int __stdcall LoadDataParms(tDebugInfo* DebugParms, int pid, tDataShape* oDataParms);
__declspec(dllexport) int __stdcall LoadEngineParms(tDebugInfo* DebugParms, int pid, tEngineDef* oEngineParms);
//--
__declspec(dllexport) int __stdcall LoadCoreParms_NN(tDebugInfo* DebugParms, int pid, int tid, NN_Parms* oNNParms);
__declspec(dllexport) int __stdcall LoadCoreParms_SOM(tDebugInfo* DebugParms, int pid, int tid, SOM_Parms* oSOMParms);
__declspec(dllexport) int __stdcall LoadCoreParms_SVM(tDebugInfo* DebugParms, int pid, int tid, SVM_Parms* oSVMParms);
//--
__declspec(dllexport) int __stdcall LoadCoreImage_NN(tDebugInfo* DebugParms, int pid, int tid, NN_Parms* NNParms, tNNWeight*** oNNWeight);
__declspec(dllexport) int __stdcall LoadCoreImage_SOM(tDebugInfo* DebugParms, int pid, int tid, SOM_Parms* SOMParms, tSOMWeight** oSOMWeight);
__declspec(dllexport) int __stdcall LoadCoreImage_SVM(tDebugInfo* DebugParms, int pid, int tid, SVM_Parms* SVMParms, tSVMWeight** oSVMWeight);
//--
__declspec(dllexport) int __stdcall LoadCoreLogs_SVM(tDebugInfo* DebugParms, int pid, int tid, SVM_Parms* SVMParms, tSVMResult* oSVMResult);
//===


__declspec(dllexport) int __stdcall WriteTestLog(tDebugInfo* DebugParms, tFXData* FXDataSource, tDataShape* DataInfo, tEngineDef* EngineParms, char* pTrainingStart, char* pTrainingEnd);
__declspec(dllexport) int __stdcall WriteTestLog_EngineInfo(tDebugInfo* pDebugParms, tEngineDef* pEngineParms, int pTestId);
__declspec(dllexport) int __stdcall WriteTestLog_DataInfo(tDebugInfo* pDebugParms, tDataShape* pDataParms, int pTestId);
__declspec(dllexport) int __stdcall BulkMSEInsert(tDebugInfo* DebugParms, int pEngineType, int* pInsertCount, tLogMSE* pMSELog);
__declspec(dllexport) int __stdcall BulkRunInsert(tDebugInfo* DebugParms, int* pInsertCount, int pHistoryLen, tLogRUN* RunData);
__declspec(dllexport) int __stdcall BulkWeightInsert_NN(tDebugInfo* DebugParms, int pLayerId, int pCoreId, int pDatasetId, int pTestId, NN_Parms* NNParms, tNNWeight*** NNWeight);
__declspec(dllexport) int __stdcall WriteTesterLog(tDebugInfo* DebugParms, int pSimulationLen, char* pSimulationStart, double pElapsedSecs, int pTesterEngine, int pDoTraining, int pDoRun, int pDataSourceType, char* pDataSourceFileName);
__declspec(dllexport) int __stdcall BulkInternalsInsert(tDebugInfo* pDebugParms, tEngineDef* pEngineParms, tDataShape* pDataParms, int pid, int tid, int pTestId, int pDatasetsCount);
//-- Engine-specific Loggers
__declspec(dllexport) int __stdcall StoreEngineLogs_NN(tDebugInfo* DebugParms, int pDatasetsCount, NN_Parms* pNNParms, tCoreLog* pNNLogs, int* pRunCount);
__declspec(dllexport) int __stdcall BulkInternalsInsert_NN(tDebugInfo* DebugParms, NN_Parms* NNParms, int pid, int tid, int testid, int pDatasetsCount, int pTimeSteps, int pDataTransformation, tLogInt*** IntData, double**** a, double**** F, double***** W);
//--

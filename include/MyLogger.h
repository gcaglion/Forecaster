#include <MyLogDefs.h>		// tDebugInfo
#include <DBConnection.h>	// tDBConnection
#include <MyEngines.h>		// tEngineHandle
#include <FXData.h>			// tFXData
#include <DataShape.h>		// tDataShape

#include <MyNN.h>	// temporary, to allow saveinternalsdata
#include <MySOM.h>
#include <MySVM.h>


//-- Save MSE and Run data should be common across engines
__declspec(dllexport) void __stdcall SaveMSEData(tCoreLog* NNLog, DWORD pid, DWORD tid, int pEpoch, double pMSE_T, double pMSE_V);
__declspec(dllexport) void __stdcall SaveRunData(tCoreLog* NNLog, DWORD pid, DWORD tid, int pPos, double pActual, double* pPredicted);

//=== standard logging, for debug purposes
__declspec(dllexport) void __stdcall LogWrite (tDebugInfo* DebugParms, int LogType, char* msg, int argcount, ...);
__declspec(dllexport) void __stdcall LogClose(tDebugInfo* DebugParms);
__declspec(dllexport) void __stdcall LogCommit(tDebugInfo* pDebugParms);
//===

//=== Log Write functions
__declspec(dllexport) int __stdcall SaveTestLog_TesterParms(tDebugInfo* pDebugParms, int pSimulationLen, char* pSimulationStart, double pElapsedS, int pTesterEngine, int pDoTraining, int pDoRun, int pDataSourceType, char* pDataSourceFileName);
__declspec(dllexport) int __stdcall SaveTestLog_DataParms(tDebugInfo* pDebugParms, tDataShape* pDataParms, int pid);
__declspec(dllexport) int __stdcall SaveTestLog_EngineParms(tDebugInfo* pDebugParms, int pid, tEngineDef* pEngineParms);
//--
__declspec(dllexport) int __stdcall InsertCoreParms_NN(tDebugInfo* DebugParms, int pid, int pLayerId, int pCoreId, NN_Parms* NNParms);
__declspec(dllexport) int __stdcall InsertCoreParms_SOM(tDebugInfo* pDebugParms, int pid, int pLayerId, int pCoreId, SOM_Parms* SOMParms);
__declspec(dllexport) int __stdcall InsertCoreParms_SVM(tDebugInfo* pDebugParms, int pid, int pLayerId, int pCoreId, SVM_Parms* SVMParms);
//--
__declspec(dllexport) int __stdcall InsertCoreImage_NN(tDebugInfo* pDebugParms, int pLayerId, int pCoreId, int pDatasetId, int pTestId, NN_Parms* NNParms, tNNWeight*** NNWeight);
__declspec(dllexport) int __stdcall InsertCoreImage_SOM(tDebugInfo* pDebugParms, int pLayerId, int pCoreId, int pDatasetId, int pTestId, SOM_Parms* SOMParms, tSOMWeight** SOMWeight);
__declspec(dllexport) int __stdcall InsertCoreImage_SVM(tDebugInfo* pDebugParms, int pLayerId, int pCoreId, int pDatasetId, int pTestId, SVM_Parms* SVMParms, tSVMResult* SVMResult, tSVMWeight** SVMWeight);
//--
__declspec(dllexport) int __stdcall InsertCoreLogs_NN(tDebugInfo* pDebugParms, NN_Parms* NNParms, tCoreLog* NNLogs);
__declspec(dllexport) int __stdcall InsertCoreLogs_SOM(tDebugInfo* pDebugParms, SOM_Parms* SOMParms, SOM_Logs* SOMLogs);
__declspec(dllexport) int __stdcall InsertCoreLogs_SVM(tDebugInfo* pDebugParms, SVM_Parms* SVMParms, tCoreLog* SVMLogs);
//--
__declspec(dllexport) int __stdcall BulkMSEInsert(tDebugInfo* DebugParms, int pEngineType, int* pInsertCount, tLogMSE* pMSELog);
__declspec(dllexport) int __stdcall BulkRunInsert(tDebugInfo* DebugParms, int* pInsertCount, int pHistoryLen, tLogRUN* RunData);

//=== Log Retrieve functions
__declspec(dllexport) int __stdcall		 LoadEngineParms(tDebugInfo* DebugParms, int pEngineType, tEngineHandle* pEngineHandle, int pDatasetsCount, void* oEngineParms);
__declspec(dllexport) int __stdcall		 LoadEngineData(tDebugInfo* DebugParms, int pEngineType, tEngineHandle* pEngineHandle, int pDatasetsCount, void* oEngineParms, void* oEngineLogs);
__declspec(dllexport) int __stdcall		 LoadDataShape(tDebugInfo* pDebugParms, tDBConnection* pLogDB, tEngineHandle* pEngine, tDataShape* oTestData);
__declspec(dllexport) int __stdcall		 GetActualEpochsFromEngine(tEngineDef* pEngineParms, int pLayer, int pCoreId, int pDatasetId);
__declspec(dllexport) tLogMSE* __stdcall GetMSELogFromEngine(tEngineDef* pEngineParms, int pLayer, int pCoreId, int pDatasetId);
__declspec(dllexport) tLogRUN* __stdcall GetRunLogFromEngine(tEngineDef* pEngineParms, int pLayer, int pCoreId, int pDatasetId, int* oStepsCount);
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

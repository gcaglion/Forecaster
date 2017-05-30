#pragma once

//#define _NO_ORCL


// Data Source definition
#ifdef _NO_ORCL
#include <MyTxtUtils.h>
#else
#include <MyOraUtils.h>
#endif

#include <MyDebug.h>
#include <ExportDef.h>
#include <DataShape.h>
#include <FileData.h>
#include <CoreCommonLogs.h>

//-- Tester/Client stuff
EXPORT int GetDates(tDebugInfo* DebugParms, tDBConnection* DBConn, tFXData* SourceParms, char* StartDate, int pDatesCount, char** oDate);
EXPORT int LoadData(tDebugInfo* DebugParms, tDBConnection* DBConn, void* SourceParms, int pHistoryLen, int pFutureLen, char* pDate0, int pValidationShift, int pDatasetCount, double** oHistoryData, double** oHistoryBarW, double** oValidationData, double** oFutureData, double** oFutureBarW, double** oWholeData, double** oWholeBarW, double* oPrevValH, double* oPrevValV, double* oPrevBarW);
EXPORT int SaveTesterParms(tDebugInfo* pDebugParms, tDBConnection* DBConn, int pid, int pSimulationLen, char* pSimulationStart, double pElapsedS, int pDoTraining, int pDoRun);
EXPORT int UpdateTesterDuration(tDebugInfo* DebugParms, tDBConnection* DBConn, int pid, double pElapsedSecs);

//-- Data Parms
EXPORT int LoadDataParms(tDebugInfo* DebugParms, tDBConnection* DBConn, int pid, int* oHistoryLen, int* oSampleLen, int* oSampleCount, int* oPredictionLen, int* oDataTransformation, double* oWiggleRoom);
EXPORT int SaveDataParms(tDebugInfo* DebugParms, tDBConnection* DBConn, tDataShape* DataParms, int pid);

//-- Engine Parms
EXPORT int LoadEngineParms(tDebugInfo* DebugParms, tDBConnection* DBConn, int pid, int* oEngineType, int* oLayersCount, int* oDecompLevel, char** oWaveletType);
EXPORT int InsertEngineParms(tDebugInfo* DebugParms, tDBConnection* DBConn, int pid, int EngineType, int LayersCount, int WNN_DecompLevel, char* WNN_WaveletType);
EXPORT int InsertEngineThreads(tDebugInfo* DebugParms, tDBConnection* DBConn, int pid, int testid, int pLayerId, int pCoreId, int pCoreType, int dsid, int tid);

//-- Cores Parms and Images
EXPORT int GetCoreThreadId(tDebugInfo* DebugParms, tDBConnection* DBConn, int pid, int testid, int DatasetId, int LayerId, int CoreId);
EXPORT int LoadCoreParms_NN(tDebugInfo* DebugParms, tDBConnection* DBConn, int pid, int tid, int* oInputCount, int* oOutputCount, int* ouseContext, int* omaxEpochs, int* oBPAlgo, int* oActivationFunction, char** olevelRatioS, double* oLearningRate, double* oLearningMomentum, double* oHCPbeta, double* oTargetMSE);
EXPORT int LoadCoreImage_NN(tDebugInfo* DebugParms, tDBConnection* DBConn, int pid, int tid, double*** FinalW);
EXPORT int InsertCoreImage_NN(tDebugInfo* DebugParms, tDBConnection* DBConn, int pid, int tid, int levelsCnt, int* nodesCnt, int wcount, double*** FinalW);

//-- Insert Logs - common
EXPORT int InsertMSELog(tDebugInfo* DebugParms, tDBConnection* DBConn, int* epochs, tLogMSE* log);
EXPORT int InsertRunLog(tDebugInfo* DebugParms, tDBConnection* DBConn, int* runcount, int hlen, tLogRUN* log);

EXPORT void LogCommit(tDebugInfo* DebugParms, tDBConnection* DBConn);
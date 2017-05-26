////#include <vld.h>

#include "stdafx.h"

//-- Save MSE and Run data should be common across engines
__declspec(dllexport) void __stdcall SaveMSEData(tCoreLog* coreLog, DWORD pid, DWORD tid, int pEpoch, double pMSE_T, double pMSE_V) {
	coreLog->MSEOutput[pEpoch].ProcessId = pid;
	coreLog->MSEOutput[pEpoch].ThreadId = tid;
	coreLog->MSEOutput[pEpoch].Epoch = pEpoch;
	coreLog->MSEOutput[pEpoch].MSE_T = pMSE_T;
	coreLog->MSEOutput[pEpoch].MSE_V = pMSE_V;
}
__declspec(dllexport) void __stdcall SaveRunData(tCoreLog* coreLog, DWORD pid, DWORD tid, int pPos, double pActual, double* pPredicted) {
	coreLog->RunOutput[pPos].ProcessId = pid;
	coreLog->RunOutput[pPos].ThreadId = tid;
	coreLog->RunOutput[pPos].Pos = pPos;
	coreLog->RunOutput[pPos].Actual_TRS = pActual;
	coreLog->RunOutput[pPos].Predicted_TRS = (pPredicted == NULL) ? 0 : pPredicted[0];
}
//--


//---------------------------------------------------------
//--- Txt Logging Functions
//---------------------------------------------------------
int Txt_BulkMSEInsert(tDebugInfo* DebugParms, int* pInsertCount, tLogMSE* MSEData) {
	int i;
	int vInsertCount;
	char LogFileName[MAX_PATH];
	FILE* LogFileHandler;

	//-- Opens MSE Log file
	strcpy(LogFileName, DebugParms->fPath); strcat(LogFileName, "/"); strcat(LogFileName, "MSELog.csv");
	LogFileHandler = fopen(LogFileName, "a");
	//-- Write File Header
	//fprintf(LogFileHandler, "ProcessId, ThreadId, TestId, LayerId, CoreId, Epoch, MSE_T, MSE_V \n");

	vInsertCount = (*pInsertCount);
	for (i = 0; i < vInsertCount; i++) {
		// simply, fprintf each element of MSEData
		fprintf(LogFileHandler, "%d, %d, %d, %d, %d, %d, %f, %f \n", MSEData[i].ProcessId, MSEData[i].ThreadId, MSEData[i].TestId, MSEData[i].LayerId, MSEData[i].CoreId, MSEData[i].Epoch, MSEData[i].MSE_T, MSEData[i].MSE_V);
	}

	// close MSE Log file
	fclose(LogFileHandler);

	return 0;
}

int Txt_BulkRunInsert(tDebugInfo* DebugParms, int* pInsertCount, int pHistoryLen, tLogRUN* RunData) {
	int i;
	int vInsertCount;
	char LogFileName[MAX_PATH];
	FILE* LogFileHandler;

	//-- Opens Run Log file
	strcpy(LogFileName, DebugParms->fPath); strcat(LogFileName, "/"); strcat(LogFileName, "RunLog.csv");
	LogFileHandler = fopen(LogFileName, "a");

	vInsertCount = (*pInsertCount);
	for (i = 0; i < vInsertCount; i++) {
		// simply, fprintf each element of RunData
		fprintf(LogFileHandler, "%d, %d, %d, %d, %d, %d, %d, %d, %f, %f, %f, %f, %f, %f \n", RunData[i].ProcessId, RunData[i].ThreadId, RunData[i].NetProcessId, RunData[i].NetThreadId, RunData[i].TestId, RunData[i].LayerId, RunData[i].CoreId, RunData[i].Pos, RunData[i].Actual, RunData[i].Predicted, RunData[i].Error, RunData[i].Actual_TRS, RunData[i].Predicted_TRS, RunData[i].Error_TRS);
	}

	// close MSE Log file
	fclose(LogFileHandler);

	return 0;
}

int Txt_BulkWeightInsert_NN(tDebugInfo* DebugParms, int pLayerId, int pCoreId, int pDatasetId, int pTestId, NN_Parms* NNParms, tNNWeight*** NNWeight) {
	return 0;
}


__declspec(dllexport) int __stdcall Txt_WriteTesterLog(tDebugInfo* DebugParms, int pSimulationLen, char* pSimulationStart, double pElapsedS, int pTesterEngine, int pDoTraining, int pDoRun, int pDataSourceType, char* pDataSourceFileName) {
	char LogFileName[MAX_PATH];
	FILE* LogFileHandler;
	int pid = GetCurrentProcessId();

	//-- Opens Tester Log file
	strcpy(LogFileName, DebugParms->fPath); strcat(LogFileName, "/"); strcat(LogFileName, "TesterLog.csv");
	LogFileHandler = fopen(LogFileName, "a");

	fprintf(LogFileHandler, "%d, %s, %f, %d, %d, %d, %d, %s \n", pid, timestamp(), pElapsedS, pTesterEngine, pDoTraining, pDoRun, pDataSourceType, pDataSourceFileName);

	// close Tester Log file
	fclose(LogFileHandler);

	return 0;
}


__declspec(dllexport) int __stdcall Txt_WriteTestLog_EngineInfo(tDebugInfo* pDebugParms, tEngineDef* pEngineParms, int pid, int pTestId, int pDecompLevel, char* pWaveletType) {
	char LogFileName[MAX_PATH];
	FILE* LogFileHandler;
	strcpy(LogFileName, pDebugParms->fPath); strcat(LogFileName, "/");
	sprintf(LogFileName, "%s%d_", LogFileName, pid);

	//-- 1. Insert into EngineParms
	// 1.1. -- Opens EngineParms Logfile
	strcat(LogFileName, "EngineParms.csv");
	LogFileHandler = fopen(LogFileName, "a");
	//-- 1.2. -- Write EngineParms
	fprintf(LogFileHandler, "%d, %d, %d, %d, %d, %s", pid, pTestId, pEngineParms->EngineType, pEngineParms->LayersCount, pDecompLevel, pWaveletType);
	//-- 1.3. -- Close EngineParms Logfile
	fclose(LogFileHandler);

	//-- 2. Insert into CoreParms_XXX
	//---- ..... -----

	return 0;
}

__declspec(dllexport) int __stdcall Txt_GetDataShapeFromStorage(tDebugInfo* pDebugParms, tDBConnection* pLogDB, tEngineHandle* pEngine, tDataShape* oTestData) {
	return 0;
}
//---------------------------------------------------------

//==========================================================================

//=== standard logging, for debug purposes
__declspec(dllexport) void  __stdcall LogWrite(tDebugInfo* DebugParms, int LogType, char* msg, int argcount, ...) {
	// pLogLevel=	0 (No screen, No file) | 1 (Screen, No file) | 2 (Screen AND File)
	int n;
	char*			arg_s;
	int				arg_d;
	double			arg_f;
	va_list			arguments;
	char submsg[MAX_PATH];
	unsigned int	im = 0;
	int				prev_im = 0;

	if (DebugParms->DebugLevel == 0 && LogType == LOG_INFO) return;

	if (DebugParms->ThreadSafeLogging>0) WaitForSingleObject(DebugParms->Mtx, INFINITE);

	//-- Opens Log file only once
	if (DebugParms->fIsOpen != 1) {
		strcpy(DebugParms->FullfName, DebugParms->fPath); strcat(DebugParms->FullfName, "/"); strcat(DebugParms->FullfName, DebugParms->fName);
		DebugParms->fHandle = fopen(DebugParms->FullfName, "w");
		DebugParms->fIsOpen = 1;
	}

	va_start(arguments, argcount);
	n = 0;

	do {
		if (msg[im] == 37) {                // "%"
			memcpy(submsg, &msg[prev_im], (im - prev_im + 2)); submsg[im - prev_im + 2] = '\0';
			n++;
			prev_im = im + 2;
			if (msg[im + 1] == 115) {   // "s"
				arg_s = va_arg(arguments, char*);
				if (DebugParms->DebugLevel == 1 || DebugParms->DebugLevel == 3 || LogType == LOG_ERROR) printf(submsg, arg_s);
				if (DebugParms->DebugLevel == 2 || DebugParms->DebugLevel == 3 || LogType == LOG_ERROR)	fprintf(DebugParms->fHandle, submsg, arg_s);
			}
			else if (msg[im + 1] == 100) {   // "d"
				arg_d = va_arg(arguments, int);
				if (DebugParms->DebugLevel == 1 || DebugParms->DebugLevel == 3 || LogType == LOG_ERROR) printf(submsg, arg_d);
				if (DebugParms->DebugLevel == 2 || DebugParms->DebugLevel == 3 || LogType == LOG_ERROR)	fprintf(DebugParms->fHandle, submsg, arg_d);
			}
			else if (msg[im + 1] == 112) {   // "p"
				arg_d = va_arg(arguments, long);
				if (DebugParms->DebugLevel == 1 || DebugParms->DebugLevel == 3 || LogType == LOG_ERROR) printf(submsg, arg_d);
				if (DebugParms->DebugLevel == 2 || DebugParms->DebugLevel == 3 || LogType == LOG_ERROR)	fprintf(DebugParms->fHandle, submsg, arg_d);
			}
			else {   // this could be 67 ("f") or any mask before "f" -> in any case, it's a double
				arg_f = va_arg(arguments, double);
				if (DebugParms->DebugLevel == 1 || DebugParms->DebugLevel == 3 || LogType == LOG_ERROR) printf(submsg, arg_f);
				if (DebugParms->DebugLevel == 2 || DebugParms->DebugLevel == 3 || LogType == LOG_ERROR)	fprintf(DebugParms->fHandle, submsg, arg_f);
			}
		}
		im++;
	} while (im<strlen(msg));

	memcpy(submsg, &msg[prev_im], (im - prev_im + 2)); submsg[im - prev_im + 2] = '\0';
	if (DebugParms->DebugLevel == 1 || DebugParms->DebugLevel == 3 || LogType == LOG_ERROR) printf(submsg);
	if (DebugParms->DebugLevel == 2 || DebugParms->DebugLevel == 3 || LogType == LOG_ERROR) fprintf(DebugParms->fHandle, submsg);
	if (LogType == LOG_ERROR) printf("Press any key..."); getchar();;

	va_end(arguments);

	if (DebugParms->ThreadSafeLogging>0) ReleaseMutex(DebugParms->Mtx);
}
__declspec(dllexport) void __stdcall LogClose(tDebugInfo* DebugParms) {
	if (DebugParms->fIsOpen == 1) {
		fclose(DebugParms->fHandle);
		DebugParms->fIsOpen = 0;
	}
}
__declspec(dllexport) void __stdcall LogCommit(tDebugInfo* pDebugParms) {
	if (pDebugParms->DebugDest == LOG_TO_ORCL) {
		OraCommit(pDebugParms->DebugDB->DBCtx);
	}
}
//===

//=== Log Write functions, Text 
int Txt_InsertTesterParms(tDebugInfo* pDebugParms, int pid, int pSimulationLen, char* pSimulationStart, double pElapsedS, int pDoTraining, int pDoRun) {
	return 0;
}
int Txt_UpdateTesterDuration(tDebugInfo* pDebugParms, int pid, double pElapsedS) {
	return 0;
}
int Txt_InsertDataParms(tDebugInfo* pDebugParms, int pid, int pDatasetId, int pDSType, char* pDSFileName, char* pSymbol, char* pTimeFrame, int pIsFilled, int pBarData, int pDataTransformation, double pwiggleRoom, int pHistoryLen, int pSampleLen, int pPredictionLen) {
	char LogFileName[MAX_PATH];
	FILE* LogFileHandler;

	//-- Opens DataParms Logfile
	strcpy(LogFileName, pDebugParms->fPath); strcat(LogFileName, "/");
	strcat(LogFileName, "DataParms.csv");
	LogFileHandler = fopen(LogFileName, "a");
	//-- Write File Header
	//fprintf(LogFileHandler, "ProcessId, DatasetId, TestId, DatasourceType, DatasourceFileName, Symbol, Timeframe, IsFilled, BarData, DataTransformation, WiggleRoom, HistoryLen, SampleLen, PredictionLen \n");

	fprintf(LogFileHandler, "%d, %d, %d, %s, %s, %s, %d, %d, %d, %f, %d, %d, %d ", pid, pDatasetId, pDSType, pDSFileName, pSymbol, pTimeFrame, pIsFilled, pBarData, pDataTransformation, pwiggleRoom, pHistoryLen, pSampleLen, pPredictionLen);

	// close DataInfo Log file
	fclose(LogFileHandler);

	return 0;
}
int Txt_InsertEngineParms(tDebugInfo* pDebugParms, int pid, int pEngineType, int pLayersCount, int pWNNDecompLevel, char* pWNNWaveletType) {
	return 0;
}
int Txt_InsertEngineThreads(tDebugInfo* pDebugParms, int pid, int testid, tEngineDef* pEngineParms, tDataShape* pDataParms) {
	return 0;
}
//--
int Txt_InsertCoreParms_NN(tDebugInfo* DebugParms, int pid, int tid, NN_Parms* NNParms) {
	return 0;
}
int Txt_InsertCoreParms_SOM(tDebugInfo* DebugParms, int pid, int tid, SOM_Parms* SOMParms) {
	return 0;
}
int Txt_InsertCoreParms_SVM(tDebugInfo* DebugParms, int pid, int tid, SVM_Parms* SVMParms) {
	return 0;
}
//--
int Txt_InsertCoreImage_NN(tDebugInfo* pDebugParms, NN_Parms* NNParms, tNNWeight*** NNWeight) {
	return 0;
}
int Txt_InsertCoreImage_SOM(tDebugInfo* pDebugParms, SOM_Parms* SOMParms, tSOMWeight** SOMWeight) {
	return 0;
}
int Txt_InsertCoreImage_SVM(tDebugInfo* pDebugParms, SVM_Parms* SVMParms, tSVMResult* SVMResult, tSVMWeight** pCoreLog) {
	return 0;
}
//--
int Txt_InsertCoreLogs_NN(tDebugInfo* DebugParms, int BPAlgo, tCoreLog* NNLogs) {
	return 0;
}
int Txt_InsertCoreLogs_SOM(tDebugInfo* DebugParms, int BPAlgo, int pInsertCount, tLogInt* IntLogs) {
	return 0;
}
int Txt_InsertCoreLogs_SVM(tDebugInfo* DebugParms, tSVMResult* SVMResult) {
	return 0;
}

//===

//=== Log Retrieve functions, Text
int Txt_getCoreThreadId(tDebugInfo* DebugParms, int pid, int testid, int DatasetId, int LayerId, int CoreId) {
	return 0;
}
//--
int Txt_LoadDataParms(tDebugInfo* DebugParms, int pid, tDataShape* oDataParms) {
	return 0;
}
int Txt_LoadEngineParms(tDebugInfo* DebugParms, int pid, tEngineDef* oEngineParms) {
	return 0;
}
//--
int Txt_LoadCoreParms_NN(tDebugInfo* DebugParms, int pid, int tid, NN_Parms* oNNParms) {
	return 0;
}
int Txt_LoadCoreParms_SOM(tDebugInfo* DebugParms, int pid, int tid, SOM_Parms* oSOMParms) {
	return 0;
}
int Txt_LoadCoreParms_SVM(tDebugInfo* DebugParms, int pid, int tid, SVM_Parms* oSVMParms) {
	return 0;
}
//--
int Txt_LoadCoreImage_NN(tDebugInfo* DebugParms, int pid, int tid, NN_Parms* NNParms, tNNWeight*** oNNWeight) {
	return 0;
}
int Txt_LoadCoreImage_SOM(tDebugInfo* DebugParms, int pid, int tid, SOM_Parms* SOMParms, tSOMWeight** oSOMWeight) {
	return 0;
}
int Txt_LoadCoreImage_SVM(tDebugInfo* DebugParms, int pid, int tid, SVM_Parms* SVMParms, tSVMWeight** oSVMWeight) {
	return 0;
}
//--
int Txt_LoadCoreLogs_SVM(tDebugInfo* DebugParms, int pid, int tid, SVM_Parms* SVMParms, tSVMResult* oSVMResult) {
	return 0;
}
//===

//=== Log Write functions, Generic 
__declspec(dllexport) int __stdcall SaveTestLog_TesterParms(tDebugInfo* pDebugParms, int pid, int pSimulationLen, char* pSimulationStart, double pElapsedS, int pDoTraining, int pDoRun) {
	if (pDebugParms->DebugDest == LOG_TO_ORCL) {
		return Ora_InsertTesterParms(pDebugParms, pid, pSimulationLen, pSimulationStart, pElapsedS, pDoTraining, pDoRun);
	}
	else {
		return Txt_InsertTesterParms(pDebugParms, pid, pSimulationLen, pSimulationStart, pElapsedS, pDoTraining, pDoRun);
	}
}
__declspec(dllexport) int __stdcall UpdateTestLog_Duration(tDebugInfo* pDebugParms, int pid, double pElapsedS) {
	if (pDebugParms->DebugDest == LOG_TO_ORCL) {
		return Ora_UpdateTesterDuration(pDebugParms, pid, pElapsedS);
	}
	else {
		return Txt_UpdateTesterDuration(pDebugParms, pid, pElapsedS);
	}
}
__declspec(dllexport) int __stdcall SaveTestLog_DataParms(tDebugInfo* pDebugParms, tDataShape* pDataParms, int pid) {
	int d;
	char vDSFileName[MAX_PATH];
	char vSymbol[10];
	char vTimeFrame[6];
	int vIsFilled;
	int* vBarData = (int*)malloc(pDataParms->DatasetsCount * sizeof(int));
	int ret = 0;

	tFXData* vFXData = nullptr;
	tFileData* vFileData = nullptr;
	switch (pDataParms->DataSourceType) {
	case SOURCE_DATA_FROM_FXDB:
		vFXData = (tFXData*)pDataParms->DataSource;
		strcpy(vDSFileName, "\0");
		strcpy(vSymbol, vFXData->Symbol);
		strcpy(vTimeFrame, vFXData->TimeFrame);
		vIsFilled = vFXData->IsFilled;
		for (d = 0; d<pDataParms->DatasetsCount; d++) vBarData[d] = vFXData->BarDataType[d];

		break;
	case SOURCE_DATA_FROM_FILE:
		vFileData = (tFileData*)pDataParms->DataSource;
		strcpy(vDSFileName, vFileData->FileName);
		strcpy(vSymbol, "\0");
		strcpy(vTimeFrame, "\0");
		vIsFilled = 0;
		for (d = 0; d<pDataParms->DatasetsCount; d++) vBarData[d] = vFileData->FileDataSet[d];
		break;
	case SOURCE_DATA_FROM_MT:
		vBarData[0] = HIGH;
		vBarData[1] = LOW;
		break;
	}

	for (d = 0; d<pDataParms->DatasetsCount; d++) {
		if (pDebugParms->DebugDest == LOG_TO_ORCL) {
			if (ret == 0) ret = Ora_InsertDataParms(pDebugParms, pid, d, pDataParms->DataSourceType, vDSFileName, vSymbol, vTimeFrame, vIsFilled, vBarData[d], pDataParms->DataTransformation, pDataParms->wiggleRoom, pDataParms->HistoryLen, pDataParms->SampleLen, pDataParms->PredictionLen);
		}
		else {
			if (ret == 0) ret = Txt_InsertDataParms(pDebugParms, pid, d, pDataParms->DataSourceType, vDSFileName, vSymbol, vTimeFrame, vIsFilled, vBarData[d], pDataParms->DataTransformation, pDataParms->wiggleRoom, pDataParms->HistoryLen, pDataParms->SampleLen, pDataParms->PredictionLen);
		}
	}
	free(vBarData);
	return ret;
}
__declspec(dllexport) int __stdcall SaveTestLog_EngineParms(tDebugInfo* pDebugParms, int pid, tEngineDef* pEngineParms) {
	if (pDebugParms->DebugDest == LOG_TO_ORCL) {
		return Ora_InsertEngineParms(pDebugParms, pid, pEngineParms->EngineType, pEngineParms->LayersCount, pEngineParms->WNN_DecompLevel, pEngineParms->WNN_WaveletType);
	}
	else {
		return Txt_InsertEngineParms(pDebugParms, pid, pEngineParms->EngineType, pEngineParms->LayersCount, pEngineParms->WNN_DecompLevel, pEngineParms->WNN_WaveletType);
	}
}
__declspec(dllexport) int __stdcall SaveTestLog_EngineThreads(tDebugInfo* pDebugParms, int pid, int testid, tEngineDef* pEngineParms, tDataShape* pDataParms) {
	if (pDebugParms->DebugDest == LOG_TO_ORCL) {
		return Ora_InsertEngineThreads(pDebugParms, pid, testid, pEngineParms, pDataParms);
	}
	else {
		return Txt_InsertEngineThreads(pDebugParms, pid, testid, pEngineParms, pDataParms);
	}
}
//--
__declspec(dllexport) int __stdcall InsertCoreParms_NN(tDebugInfo* pDebugParms, int pid, int tid, NN_Parms* NNParms) {
	if (pDebugParms->DebugDest == LOG_TO_ORCL) {
		return Ora_InsertCoreParms_NN(pDebugParms, pid, tid, NNParms);
	}
	else {
		return Txt_InsertCoreParms_NN(pDebugParms, pid, tid, NNParms);
	}
}
__declspec(dllexport) int __stdcall InsertCoreParms_SOM(tDebugInfo* pDebugParms, int pid, int tid, SOM_Parms* SOMParms) {
	if (pDebugParms->DebugDest == LOG_TO_ORCL) {
		return Ora_InsertCoreParms_SOM(pDebugParms, pid, tid, SOMParms);
	}
	else {
		return Txt_InsertCoreParms_SOM(pDebugParms, pid, tid, SOMParms);
	}
}
__declspec(dllexport) int __stdcall InsertCoreParms_SVM(tDebugInfo* pDebugParms, int pid, int tid, SVM_Parms* SVMParms) {
	if (pDebugParms->DebugDest == LOG_TO_ORCL) {
		return Ora_InsertCoreParms_SVM(pDebugParms, pid, tid, SVMParms);
	}
	else {
		return Txt_InsertCoreParms_SVM(pDebugParms, pid, tid, SVMParms);
	}
}
//--
__declspec(dllexport) int __stdcall InsertCoreImage_NN(tDebugInfo* pDebugParms, NN_Parms* NNParms, tNNWeight*** NNWeight) {
	if (pDebugParms->DebugDest == LOG_TO_ORCL) {
		return Ora_InsertCoreImage_NN(pDebugParms, NNParms, NNWeight);
	}
	else {
		return Txt_InsertCoreImage_NN(pDebugParms, NNParms, NNWeight);
	}
}
__declspec(dllexport) int __stdcall InsertCoreImage_SOM(tDebugInfo* pDebugParms, SOM_Parms* SOMParms, tSOMWeight** SOMWeight) {
	if (pDebugParms->DebugDest == LOG_TO_ORCL) {
		return Ora_InsertCoreImage_SOM(pDebugParms, SOMParms, SOMWeight);
	}
	else {
		return Txt_InsertCoreImage_SOM(pDebugParms, SOMParms, SOMWeight);
	}
}
__declspec(dllexport) int __stdcall InsertCoreImage_SVM(tDebugInfo* pDebugParms, SVM_Parms* SVMParms, tSVMResult* SVMResult, tSVMWeight** SVMWeight) {
	if (pDebugParms->DebugDest == LOG_TO_ORCL) {
		return Ora_InsertCoreImage_SVM(pDebugParms, SVMParms, SVMResult, SVMWeight);
	} else {
		return Txt_InsertCoreImage_SVM(pDebugParms, SVMParms, SVMResult, SVMWeight);
	}
}
//--
__declspec(dllexport) int __stdcall InsertCoreLogs_NN(tDebugInfo* pDebugParms, NN_Parms* NNParms, tCoreLog* NNLogs) {
	if (pDebugParms->DebugDest == LOG_TO_ORCL) {
		return Ora_InsertCoreLogs_NN(pDebugParms, NNParms->BP_Algo, NNLogs);
	}
	else {
		return Txt_InsertCoreLogs_NN(pDebugParms, NNParms->BP_Algo, NNLogs);
	}
}
__declspec(dllexport) int __stdcall InsertCoreLogs_SOM(tDebugInfo* pDebugParms, SOM_Parms* SOMParms, tCoreLog* SOMLogs) {
	if (pDebugParms->DebugDest == LOG_TO_ORCL) {
		return Ora_InsertCoreLogs_SOM(pDebugParms, NULL, SOMLogs->ActualEpochs, SOMLogs->IntP);
	}
	else {
		return Txt_InsertCoreLogs_SOM(pDebugParms, NULL, SOMLogs->ActualEpochs, SOMLogs->IntP);
	}
}
__declspec(dllexport) int __stdcall InsertCoreLogs_SVM(tDebugInfo* pDebugParms, SVM_Parms* SVMParms, tCoreLog* SVMLogs) {
	if (pDebugParms->DebugDest == LOG_TO_ORCL) {
		return Ora_InsertCoreLogs_SVM(pDebugParms, &SVMLogs->SVMResult);
	}
	else {
		return Txt_InsertCoreLogs_SVM(pDebugParms, &SVMLogs->SVMResult);
	}
}
//--
__declspec(dllexport) int __stdcall BulkMSEInsert(tDebugInfo* DebugParms, int pEngineType, int* pInsertCount, tLogMSE* pMSELog) {
	if (DebugParms->DebugDest == LOG_TO_ORCL) {
		return Ora_BulkMSEInsert(DebugParms, pInsertCount, pMSELog);
	}
	else {
		return(Txt_BulkMSEInsert(DebugParms, pInsertCount, pMSELog));
	}
}
__declspec(dllexport) int __stdcall BulkRunInsert(tDebugInfo* DebugParms, int* pInsertCount, int pHistoryLen, tLogRUN* RunData) {
	if (DebugParms->DebugDest == LOG_TO_ORCL) {
		return Ora_BulkRunInsert(DebugParms, pInsertCount, pHistoryLen, RunData);
	}
	else {
		return Txt_BulkRunInsert(DebugParms, pInsertCount, pHistoryLen, RunData);
	}
}

//===

//=== Log Retrieve functions, Generic
__declspec(dllexport) int __stdcall getCoreThreadId(tDebugInfo* DebugParms, int pid, int testid, int DatasetId, int LayerId, int CoreId) {
	if (DebugParms->DebugDest == LOG_TO_ORCL) {
		return(Ora_getCoreThreadId(DebugParms, pid, testid, DatasetId, LayerId, CoreId));
	}
	else {
		return(Txt_getCoreThreadId(DebugParms, pid, testid, DatasetId, LayerId, CoreId));
	}
}
//--
__declspec(dllexport) int __stdcall LoadDataParms(tDebugInfo* DebugParms, int pid, tDataShape* oDataParms) {
	if (DebugParms->DebugDest == LOG_TO_ORCL) {
		return(Ora_LoadDataParms(DebugParms, pid, oDataParms));
	} else {
		return(Txt_LoadDataParms(DebugParms, pid, oDataParms));
	}
}
__declspec(dllexport) int __stdcall LoadEngineParms(tDebugInfo* DebugParms, int pid, tEngineDef* oEngineParms) {
	if (DebugParms->DebugDest == LOG_TO_ORCL) {
		return(Ora_LoadEngineParms(DebugParms, pid, oEngineParms));
	}
	else {
		return(Txt_LoadEngineParms(DebugParms, pid, oEngineParms));
	}
}
//--
__declspec(dllexport) int __stdcall LoadCoreParms_NN(tDebugInfo* DebugParms, int pid, int tid, NN_Parms* oNNParms) {
	if (DebugParms->DebugDest == LOG_TO_ORCL) {
		return(Ora_LoadCoreParms_NN(DebugParms, pid, tid, oNNParms));
	}
	else {
		return(Txt_LoadCoreParms_NN(DebugParms, pid, tid, oNNParms));
	}
}
__declspec(dllexport) int __stdcall LoadCoreParms_SOM(tDebugInfo* DebugParms, int pid, int tid, SOM_Parms* oSOMParms) {
	if (DebugParms->DebugDest == LOG_TO_ORCL) {
		return(Ora_LoadCoreParms_SOM(DebugParms, pid, tid, oSOMParms));
	}
	else {
		return(Txt_LoadCoreParms_SOM(DebugParms, pid, tid, oSOMParms));
	}
}
__declspec(dllexport) int __stdcall LoadCoreParms_SVM(tDebugInfo* DebugParms, int pid, int tid, SVM_Parms* oSVMParms) {
	if (DebugParms->DebugDest == LOG_TO_ORCL) {
		return(Ora_LoadCoreParms_SVM(DebugParms, pid, tid, oSVMParms));
	}
	else {
		return(Txt_LoadCoreParms_SVM(DebugParms, pid, tid, oSVMParms));
	}
}
//--
__declspec(dllexport) int __stdcall LoadCoreImage_NN(tDebugInfo* DebugParms, int pid, int tid, NN_Parms* NNParms, tNNWeight*** oNNWeight) {
	if (DebugParms->DebugDest == LOG_TO_ORCL) {
		return(Ora_LoadCoreImage_NN(DebugParms, pid, tid, NNParms, oNNWeight));
	}
	else {
		return(Txt_LoadCoreImage_NN(DebugParms, pid, tid, NNParms, oNNWeight));
	}
}
__declspec(dllexport) int __stdcall LoadCoreImage_SOM(tDebugInfo* DebugParms, int pid, int tid, SOM_Parms* SOMParms, tSOMWeight** oSOMWeight) {
	if (DebugParms->DebugDest == LOG_TO_ORCL) {
		return(Ora_LoadCoreImage_SOM(DebugParms, pid, tid, SOMParms, oSOMWeight));
	}
	else {
		return(Txt_LoadCoreImage_SOM(DebugParms, pid, tid, SOMParms, oSOMWeight));
	}
}
__declspec(dllexport) int __stdcall LoadCoreImage_SVM(tDebugInfo* DebugParms, int pid, int tid, SVM_Parms* SVMParms, tSVMWeight** oSVMWeight) {
	if (DebugParms->DebugDest == LOG_TO_ORCL) {
		return(Ora_LoadCoreImage_SVM(DebugParms, pid, tid, SVMParms, oSVMWeight));
	}
	else {
		return(Txt_LoadCoreImage_SVM(DebugParms, pid, tid, SVMParms, oSVMWeight));
	}
}
//--
__declspec(dllexport) int __stdcall LoadCoreLogs_SVM(tDebugInfo* DebugParms, int pid, int tid, SVM_Parms* SVMParms, tSVMResult* oSVMResult) {
	if (DebugParms->DebugDest == LOG_TO_ORCL) {
		return(Ora_LoadCoreLogs_SVM(DebugParms, pid, tid, SVMParms, oSVMResult));
	}
	else {
		return(Txt_LoadCoreLogs_SVM(DebugParms, pid, tid, SVMParms, oSVMResult));
	}
}
/*
__declspec(dllexport) int		__stdcall LoadEngineParms(tDebugInfo* DebugParms, int pEngineType, tEngineHandle* pEngineHandle, int pDatasetsCount, void* oEngineParms) {
	if (DebugParms->DebugDest == LOG_TO_ORCL) {
		return Ora_LoadEngineParms(DebugParms, pEngineType, pEngineHandle, pDatasetsCount, oEngineParms);
	}
	else {
		return Txt_LoadEngineParms(DebugParms, pEngineType, pEngineHandle, pDatasetsCount, oEngineParms);
	}
}
__declspec(dllexport) int		__stdcall LoadEngineData(tDebugInfo* DebugParms, int pEngineType, tEngineHandle* pEngineHandle, int pDatasetsCount, void* oEngineParms, void* oEngineLogs) {
	if (DebugParms->DebugDest == LOG_TO_ORCL) {
		return Ora_LoadEngineData(DebugParms, pEngineType, pEngineHandle, pDatasetsCount, oEngineParms, oEngineLogs);
	}
	else {
		return Txt_LoadEngineData(DebugParms, pEngineType, pEngineHandle, pDatasetsCount, oEngineParms, oEngineLogs);
	}
}
__declspec(dllexport) int		__stdcall LoadDataShape(tDebugInfo* pDebugParms, tDBConnection* pLogDB, tEngineHandle* pEngine, tDataShape* oTestData) {
	if (pDebugParms->DebugDest == LOG_TO_ORCL) {
		return Ora_LoadDataShape(pDebugParms, pLogDB, pEngine, oTestData);
	}
	else {
		return Txt_LoadDataShape(pDebugParms, pLogDB, pEngine, oTestData);
	}
}
*/
/*
__declspec(dllexport) tLogRUN*	__stdcall GetRunLogFromEngine(tEngineDef* pEngineParms, int pLayer, int pCoreId, int pDatasetId, int* oStepsCount) {
	tLogRUN* RunLog = nullptr;
	NN_Parms* NNParms;		NN_Logs* NNLogs;
	GA_Parms* GAParms;		GA_Logs* GALogs;
	SOM_Parms* SOMParms;	SOM_Logs* SOMLogs;
	SVM_Parms* SVMParms;	SVM_Logs* SVMLogs;
	tLogRUN* ret = nullptr;

	switch (pEngineParms->EngineType) {
	case ENGINE_NN:
		NNParms = (NN_Parms*)pEngineParms->CoreSpecs[pLayer][pCoreId];
		(*oStepsCount) = NNParms->OutputCount;
		NNLogs = (NN_Logs*)pEngineParms->CoreLogs[pLayer][pCoreId][pDatasetId];
		ret = NNLogs->RunOutput;
		break;
	case ENGINE_WNN:
		NNParms = (NN_Parms*)pEngineParms->CoreSpecs[pLayer][pCoreId];
		(*oStepsCount) = NNParms->OutputCount;
		NNLogs = (NN_Logs*)pEngineParms->CoreLogs[pLayer][pCoreId][pDatasetId];
		ret = NNLogs->RunOutput;
		break;
	case ENGINE_GA:
		GAParms = (GA_Parms*)pEngineParms->CoreSpecs[pLayer][pCoreId];
		(*oStepsCount) = GAParms->OutputCount;
		GALogs = (GA_Logs*)pEngineParms->CoreLogs[pLayer][pCoreId][pDatasetId];
		ret = GALogs->RunOutput;
		break;
	case ENGINE_SOM:
		SOMParms = (SOM_Parms*)pEngineParms->CoreSpecs[pLayer][pCoreId];
		(*oStepsCount) = SOMParms->OutputCount;
		SOMLogs = (SOM_Logs*)pEngineParms->CoreLogs[pLayer][pCoreId][pDatasetId];
		ret = SOMLogs->RunOutput;
		break;
	case ENGINE_SVM:
		SVMParms = (SVM_Parms*)pEngineParms->CoreSpecs[pLayer][pCoreId];
		(*oStepsCount) = 1;	// SVMParms->OutputBuckets;
		SVMLogs = (SVM_Logs*)pEngineParms->CoreLogs[pLayer][pCoreId][pDatasetId];
		ret = SVMLogs->RunOutput;
		break;
	}
	return ret;
}

*/
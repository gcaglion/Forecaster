#include <MyDataAbstraction.h>

#ifdef _NO_ORCL
#else
#endif

//-- Tester/Client stuff
EXPORT int GetDates(tDebugInfo* DebugParms, tDBConnection* DBConn, tFXData* SourceParms, char* StartDate, int pDatesCount, char** oDate) {
#ifdef _NO_ORCL
	return( Txt_GetDates(DebugParms, SourceParms, StartDate, pDatesCount, oDate) );
#else
	return( Ora_GetDates(DebugParms, DBConn, SourceParms, StartDate, pDatesCount, oDate) );
#endif
}
EXPORT int LoadData(tDebugInfo* DebugParms, tDBConnection* DBConn, void* SourceParms, int pHistoryLen, int pFutureLen, char* pDate0, int pValidationShift, int pDatasetCount, double** oHistoryData, double** oHistoryBarW, double** oValidationData, double** oFutureData, double** oFutureBarW, double** oWholeData, double** oWholeBarW, double* oPrevValH, double* oPrevValV, double* oPrevBarW) {
#ifdef _NO_ORCL
	return( Txt_LoadData(DebugParms, (tFileData*)SourceParms, pHistoryLen, pFutureLen, pDate0, pValidationShift, pDatasetCount, oHistoryData, oHistoryBarW, oValidationData, oFutureData, oFutureBarW, oWholeData, oWholeBarW, oPrevValH, oPrevValV, oPrevBarW) );
#else
	return( Ora_LoadData(DebugParms, DBConn, (tFXData*)SourceParms, pHistoryLen, pFutureLen, pDate0, pValidationShift, pDatasetCount, oHistoryData, oHistoryBarW, oValidationData, oFutureData, oFutureBarW, oWholeData, oWholeBarW, oPrevValH, oPrevValV, oPrevBarW) );
#endif
}
EXPORT int SaveTesterParms(tDebugInfo* pDebugParms, tDBConnection* DBConn, int pid, int pSimulationLen, char* pSimulationStart, double pElapsedS, int pDoTraining, int pDoRun) {
#ifdef _NO_ORCL
	return(Txt_InsertTesterParms(pDebugParms, pid, pSimulationLen, pSimulationStart, pElapsedS, pDoTraining, pDoRun));
#else
	return( Ora_InsertTesterParms(pDebugParms, DBConn, pid, pSimulationLen, pSimulationStart, pElapsedS, pDoTraining, pDoRun) );
#endif
}
EXPORT int UpdateTesterDuration(tDebugInfo* DebugParms, tDBConnection* DBConn, int pid, double pElapsedSecs) {
	#ifdef _NO_ORCL
	return (Txt_UpdateTesterDuration(DebugParms, pid, pElapsedSecs));
#else
	return ( Ora_UpdateTesterDuration(DebugParms, DBConn, pid, pElapsedSecs) );
	#endif
}

//-- Data Parms
EXPORT int LoadDataParms(tDebugInfo* DebugParms, tDBConnection* DBConn, int pid, int* oHistoryLen, int* oSampleLen, int* oSampleCount, int* oPredictionLen, int* oDataTransformation, double* oWiggleRoom) {
#ifdef _NO_ORCL
	return(Txt_LoadDataParms(DebugParms, pid, oHistoryLen, oSampleLen, oSampleCount, oPredictionLen, oDataTransformation, oWiggleRoom));
#else
	return( Ora_LoadDataParms(DebugParms, DBConn, pid, oHistoryLen, oSampleLen, oSampleCount, oPredictionLen, oDataTransformation, oWiggleRoom) );
#endif
}
EXPORT int SaveDataParms(tDebugInfo* DebugParms, tDBConnection* DBConn, tDataShape* DataParms, int pid) {
	int d;
	char vDSFileName[MAX_PATH];
	char vSymbol[10];
	char vTimeFrame[6];
	int vIsFilled;
	int* vBarData = (int*)malloc(DataParms->DatasetsCount * sizeof(int));
	int ret = 0;

	tFXData* vFXData = nullptr;
	tFileData* vFileData = nullptr;
	switch (DataParms->DataSourceType) {
	case SOURCE_DATA_FROM_FXDB:
		vFXData = (tFXData*)DataParms->DataSource;
		strcpy(vDSFileName, "\0");
		strcpy(vSymbol, vFXData->Symbol);
		strcpy(vTimeFrame, vFXData->TimeFrame);
		vIsFilled = vFXData->IsFilled;
		for (d = 0; d<DataParms->DatasetsCount; d++) vBarData[d] = vFXData->BarDataType[d];

		break;
	case SOURCE_DATA_FROM_FILE:
		vFileData = (tFileData*)DataParms->DataSource;
		strcpy(vDSFileName, vFileData->FileName);
		strcpy(vSymbol, "\0");
		strcpy(vTimeFrame, "\0");
		vIsFilled = 0;
		for (d = 0; d<DataParms->DatasetsCount; d++) vBarData[d] = vFileData->FileDataSet[d];
		break;
	case SOURCE_DATA_FROM_MT:
		vBarData[0] = HIGH;
		vBarData[1] = LOW;
		break;
	}

	for (d = 0; d<DataParms->DatasetsCount; d++) {
#ifdef _NO_ORCL
		ret = Txt_InsertDataParms(pDebugParms, pid, d, pDataParms->DataSourceType, vDSFileName, vSymbol, vTimeFrame, vIsFilled, vBarData[d], pDataParms->DataTransformation, pDataParms->wiggleRoom, pDataParms->HistoryLen, pDataParms->SampleLen, pDataParms->PredictionLen);
#else
		ret = Ora_InsertDataParms(DebugParms, DBConn, pid, d, DataParms->DataSourceType, vDSFileName, vSymbol, vTimeFrame, vIsFilled, vBarData[d], DataParms->DataTransformation, DataParms->wiggleRoom, DataParms->HistoryLen, DataParms->SampleLen, DataParms->PredictionLen);
#endif
	}

	free(vBarData);
	return ret;
}

//-- Engine Parms
EXPORT int LoadEngineParms(tDebugInfo* DebugParms, tDBConnection* DBConn, int pid, int* oEngineType, int* oLayersCount, int* oDecompLevel, char** oWaveletType) {
#ifdef _NO_ORCL
	return( Txt_LoadEngineParms(DebugParms, DBConn, pid, oEngineType, oLayersCount, oDecompLevel, oWaveletType) );
#else
	return( Ora_LoadEngineParms(DebugParms, DBConn, pid, oEngineType, oLayersCount, oDecompLevel, oWaveletType) );
#endif
}
EXPORT int InsertEngineParms(tDebugInfo* DebugParms, tDBConnection* DBConn, int pid, int EngineType, int LayersCount, int WNN_DecompLevel, char* WNN_WaveletType) {
#ifdef _NO_ORCL
	if (Txt_InsertEngineParms(DebugParms, DBConn, pid, EngineType, LayersCount, WNN_DecompLevel, WNN_WaveletType) <0) return -1;
#else
	if (Ora_InsertEngineParms(DebugParms, DBConn, pid, EngineType, LayersCount, WNN_DecompLevel, WNN_WaveletType) <0) return -1;
#endif
	return 0;
}
EXPORT int InsertEngineThreads(tDebugInfo* DebugParms, tDBConnection* DBConn, int pid, int testid, int pLayerId, int pCoreId, int pCoreType, int dsid, int tid) {
#ifdef _NO_ORCL
	if (Txt_InsertEngineThreads(DebugParms, DBConn, pid, testid, l, c, EngineParms->Core[l][c]->CoreType, d, EngineParms->Core[l][c]->ThreadId) <0) return -1;
#else
	if (Ora_InsertEngineThreads(DebugParms, DBConn, pid, testid, pLayerId, pCoreId, pCoreType, dsid, tid) <0) return -1;
#endif
	return 0;
}

//-- Cores Parms and Images
EXPORT int GetCoreThreadId(tDebugInfo* DebugParms, tDBConnection* DBConn, int pid, int testid, int DatasetId, int LayerId, int CoreId) {
#ifdef _NO_ORCL
	return( Txt_GetCoreThreadId(DebugParms, DBConn, pid, testid, DatasetId, LayerId, CoreId) );
#else
	return( Ora_GetCoreThreadId(DebugParms, DBConn, pid, testid, DatasetId, LayerId, CoreId) );
#endif
}
EXPORT int LoadCoreParms_NN(tDebugInfo* DebugParms, tDBConnection* DBConn, int pid, int tid,	int* oInputCount, int* oOutputCount, int* ouseContext, int* omaxEpochs, int* oBPAlgo, int* oActivationFunction, char** olevelRatioS, double* oLearningRate, double* oLearningMomentum, double* oHCPbeta, double* oTargetMSE) {
#ifdef _NO_ORCL
	return (Txt_LoadCoreParms_NN(DebugParms, DBConn, pid, tid, oInputCount, oOutputCount, ouseContext, omaxEpochs, oBPAlgo, oActivationFunction, olevelRatioS, oLearningRate, oLearningMomentum, oHCPbeta, oTargetMSE));
#else
	return ( Ora_LoadCoreParms_NN(DebugParms, DBConn, pid, tid, oInputCount, oOutputCount, ouseContext, omaxEpochs, oBPAlgo, oActivationFunction, olevelRatioS, oLearningRate, oLearningMomentum, oHCPbeta, oTargetMSE) );
#endif
}
EXPORT int LoadCoreImage_NN(tDebugInfo* DebugParms, tDBConnection* DBConn, int pid, int tid, double*** FinalW) {
#ifdef _NO_ORCL
	return( Txt_LoadCoreImage_NN(DebugParms, DBConn, pid, tid, FinalW) );
#else
	return( Ora_LoadCoreImage_NN(DebugParms, DBConn, pid, tid, FinalW) );
#endif
}
EXPORT int InsertCoreImage_NN(tDebugInfo* DebugParms, tDBConnection* DBConn, int pid, int tid, int levelsCnt, int* nodesCnt, int wcount, double*** FinalW) {
#ifdef _NO_ORCL
	return(Txt_InsertCoreImage_NN(DebugParms, DBConn, pid, tid, levelsCnt, nodesCnt, wcount, FinalW));
#else
	return(Ora_InsertCoreImage_NN(DebugParms, DBConn, pid, tid, levelsCnt, nodesCnt, wcount, FinalW));
#endif
	return 0;
}

//-- Insert Logs - common
EXPORT int InsertMSELog(tDebugInfo* DebugParms, tDBConnection* DBConn, int* epochs, tLogMSE* log) {
	#ifdef _NO_ORCL
	if (Txt_InsertMSELog(DebugParms, epochs, log) <0) return -1;
	#else
	if( Ora_InsertMSELog(DebugParms, DBConn, epochs, log) <0) return -1;
	#endif
	return 0;
}
EXPORT int InsertRunLog(tDebugInfo* DebugParms, tDBConnection* DBConn, int* runcount, int hlen, tLogRUN* log) {
	#ifdef _NO_ORCL
	if (Txt_InsertRunLog(DebugParms, runcount, hlen, log) <0) return -1;
	#else
	if (Ora_InsertRunLog(DebugParms, DBConn, runcount, hlen, log) <0) return -1;
	#endif
	return 0;
}

EXPORT void LogCommit(tDebugInfo* DebugParms, tDBConnection* DBConn) {
#ifdef _NO_ORCL
	fclose(DebugParms->fHandle);
#else
	OraCommit(DBConn->DBCtx);
#endif
}
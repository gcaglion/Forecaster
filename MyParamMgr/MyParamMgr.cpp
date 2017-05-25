//#include <vld.h>

#include <MyParamMgr.h>

//-- enumerators
int cParamsSource::getEnumVal(char* edesc, char* eval){
	UpperCase(edesc);

	if (strcmp(edesc, "FORECASTER.ENGINE") == 0) {
		if (strcmp(eval, "ENGINE_NN") == 0) return ENGINE_NN;
		if (strcmp(eval, "ENGINE_GA") == 0) return ENGINE_GA;
		if (strcmp(eval, "ENGINE_SVM") == 0) return ENGINE_SVM;
		if (strcmp(eval, "ENGINE_SOM") == 0) return ENGINE_SOM;
		if (strcmp(eval, "ENGINE_WNN") == 0) return ENGINE_WNN;
		if (strcmp(eval, "ENGINE_XIE") == 0) return ENGINE_XIE;
		return -1;
	}
	else if (strcmp(edesc, "RESULTS.DESTINATION") == 0) {
		if (strcmp(eval, "LOG_TO_TEXT") == 0) return LOG_TO_TEXT;
		if (strcmp(eval, "LOG_TO_ORCL") == 0) return LOG_TO_ORCL;
		return -1;
	}
	else if (strcmp(edesc, "DATASOURCE.SOURCETYPE") == 0) {
		if (strcmp(eval, "SOURCE_DATA_FROM_FXDB") == 0) return SOURCE_DATA_FROM_FXDB;
		if (strcmp(eval, "SOURCE_DATA_FROM_FILE") == 0) return SOURCE_DATA_FROM_FILE;
		if (strcmp(eval, "SOURCE_DATA_FROM_MT") == 0) return SOURCE_DATA_FROM_MT;
		return -1;
	}
	else if (strcmp(edesc, "DATASOURCE.SOURCETYPE") == 0) {
	}
	else if (strcmp(edesc, "DATAPARMS.DATATRANSFORMATION") == 0) {
		if (strcmp(eval, "DT_NONE") == 0) return DT_NONE;
		if (strcmp(eval, "DT_DELTA") == 0) return DT_DELTA;
		if (strcmp(eval, "DT_LOG") == 0) return DT_LOG;
		if (strcmp(eval, "DT_DELTALOG") == 0) return DT_DELTALOG;
		return -1;
	}
	else if (strcmp(edesc, "DATASOURCE.BARDATATYPES") == 0) {
		if (strcmp(eval, "OPEN") == 0) return OPEN;
		if (strcmp(eval, "HIGH") == 0) return HIGH;
		if (strcmp(eval, "LOW") == 0) return LOW;
		if (strcmp(eval, "CLOSE") == 0) return CLOSE;
		if (strcmp(eval, "VOLUME") == 0) return VOLUME;
		if (strcmp(eval, "OTHER") == 0) return OTHER;
	}
	else if (strcmp(edesc, "DATAPARMS.TSFEATURES") == 0) {
		if (strcmp(eval, "TSF_MEAN") == 0) return TSF_MEAN;
		if (strcmp(eval, "TSF_MAD") == 0) return TSF_MAD;
		if (strcmp(eval, "TSF_VARIANCE") == 0) return TSF_VARIANCE;
		if (strcmp(eval, "TSF_SKEWNESS") == 0) return TSF_SKEWNESS;
		if (strcmp(eval, "TSF_KURTOSIS") == 0) return TSF_KURTOSIS;
		if (strcmp(eval, "TSF_TURNINGPOINTS") == 0) return TSF_TURNINGPOINTS;
		if (strcmp(eval, "TSF_SHE") == 0) return TSF_SHE;
		if (strcmp(eval, "TSF_HISTVOL") == 0) return TSF_HISTVOL;
		return -1;
	}
	else if (strcmp(right(edesc, 7), "BP_ALGO") == 0) {
		if (strcmp(eval, "BP_STD") == 0) return BP_STD;
		if (strcmp(eval, "BP_QING") == 0) return BP_QING;
		if (strcmp(eval, "BP_SCGD") == 0) return BP_SCGD;
		if (strcmp(eval, "BP_QUICKPROP") == 0) return BP_QUICKPROP;
		return -1;
	}
	else if (strcmp(right(edesc, 16), "TRAININGPROTOCOL") == 0) {
		if (strcmp(eval, "TP_STOCHASTIC") == 0) return TP_STOCHASTIC;
		if (strcmp(eval, "TP_BATCH") == 0) return TP_BATCH;
		if (strcmp(eval, "TP_ONLINE") == 0) return TP_ONLINE;
		return -1;
	}
	else if (strcmp(right(edesc, 18), "ACTIVATIONFUNCTION") == 0) {
		if (strcmp(eval, "NN_ACTIVATION_TANH") == 0) return NN_ACTIVATION_TANH;
		if (strcmp(eval, "NN_ACTIVATION_EXP4") == 0) return NN_ACTIVATION_EXP4;
	}
	else if (strcmp(edesc, "SOMINFO.TDFUNCTION") == 0) {
		if (strcmp(eval, "TD_DECAY_CONSTANT") == 0) return TD_DECAY_CONSTANT;
		if (strcmp(eval, "TD_DECAY_LINEAR") == 0) return TD_DECAY_LINEAR;
		if (strcmp(eval, "TD_DECAY_STEPPED") == 0) return TD_DECAY_STEPPED;
		if (strcmp(eval, "TD_DECAY_EXP") == 0) return TD_DECAY_EXP;
		return -1;
	}
	else if (strcmp(edesc, "SOMINFO.LRFUNCTION") == 0) {
		if (strcmp(eval, "LR_DECAY_CONSTANT") == 0) return LR_DECAY_CONSTANT;
		if (strcmp(eval, "LR_DECAY_LINEAR") == 0) return LR_DECAY_LINEAR;
		if (strcmp(eval, "LR_DECAY_STEPPED") == 0) return LR_DECAY_STEPPED;
		if (strcmp(eval, "LR_DECAY_EXP") == 0) return LR_DECAY_EXP;
		return -1;
	}
	else if (strcmp(right(edesc, 10), "KERNELTYPE") == 0) {
		if (strcmp(eval, "KERNEL_TYPE_LINEAR") == 0) return KERNEL_TYPE_LINEAR;
		if (strcmp(eval, "KERNEL_TYPE_POLY") == 0) return KERNEL_TYPE_POLY;
		if (strcmp(eval, "KERNEL_TYPE_RBF") == 0) return KERNEL_TYPE_RBF;
		if (strcmp(eval, "KERNEL_TYPE_TANH") == 0) return KERNEL_TYPE_TANH;
		if (strcmp(eval, "KERNEL_TYPE_CUSTOM") == 0) return KERNEL_TYPE_CUSTOM;
		return -1;
	}
	else if (strcmp(right(edesc, 9), "SLACKNORM") == 0) {
		if (strcmp(eval, "SLACK_NORM_L1") == 0) return SLACK_NORM_L1;
		if (strcmp(eval, "SLACK_NORM_SQUARED") == 0) return SLACK_NORM_SQUARED;
		return -1;
	}
	else if (strcmp(right(edesc, 15), "RESCALINGMETHOD") == 0) {
		if (strcmp(eval, "RESCALING_METHOD_SLACK") == 0) return RESCALING_METHOD_SLACK;
		if (strcmp(eval, "RESCALING_METHOD_MARGIN") == 0) return RESCALING_METHOD_MARGIN;
		return -1;
	}
	else if (strcmp(right(edesc, 12), "LOSSFUNCTION") == 0) {
		if (strcmp(eval, "LOSS_FUNCTION_ZEROONE") == 0) return LOSS_FUNCTION_ZEROONE;
		return -1;
	}
	else if (strcmp(right(edesc, 12), "LEARNINGALGO") == 0) {
		if (strcmp(eval, "LEARNING_ALGO_NSLACK") == 0) return LEARNING_ALGO_NSLACK;
		if (strcmp(eval, "LEARNING_ALGO_NSLACK_SHRINK") == 0) return LEARNING_ALGO_NSLACK_SHRINK;
		if (strcmp(eval, "LEARNING_ALGO_1SLACK_PRIMAL") == 0) return LEARNING_ALGO_1SLACK_PRIMAL;
		if (strcmp(eval, "LEARNING_ALGO_1SLACK_DUAL") == 0) return LEARNING_ALGO_1SLACK_DUAL;
		if (strcmp(eval, "LEARNING_ALGO_1SLACK_DUAL_CONSTR") == 0) return LEARNING_ALGO_1SLACK_DUAL_CONSTR;
		if (strcmp(eval, "LEARNING_ALGO_CUSTOM") == 0) return LEARNING_ALGO_CUSTOM;
		return -1;
	}
	return 0;
}

//-- single-value parameters
int	cParamsSource::ReadParamFromFile(char* pFileName, char* pParamName, int* oParamValue){
	FILE* ParamFile;
	char vParamName[1000];
	char vParamValue[1000];

	ParamFile = fopen(pFileName, "r");
	if (ParamFile == NULL) {
		printf("ReadParamFromFile() could not open Parameter file: %s . Exiting.\n", pFileName);
		printf("Press any key to continue...\n"); getchar();;
		return -1;
	}
	while (fscanf(ParamFile, "%s = %s ", &vParamName[0], &vParamValue[0]) != EOF) {
		Trim(vParamName);
		if (strcmp(&vParamName[0], &pParamName[0]) == 0) {
			(*oParamValue) = atoi(vParamValue);
			fclose(ParamFile);
			return 0;
		}
	}
	fclose(ParamFile);
	printf("ReadParamFromFile() could not find Parameter: %s . Exiting.\n", pParamName);
	printf("Press any key to continue...\n"); getchar();;
	return -1;
}
int	cParamsSource::ReadParamFromFile(char* pFileName, char* pParamName, double* oParamValue){
	FILE* ParamFile;
	char vParamName[1000];
	char vParamValue[1000];

	ParamFile = fopen(pFileName, "r");
	if (ParamFile == NULL) {
		printf("ReadParamFromFile() could not open Parameter file: %s . Exiting.\n", pFileName);
		return -1;
	}
	while (fscanf(ParamFile, "%s = %s ", &vParamName[0], &vParamValue[0]) != EOF) {
		Trim(vParamName);
		//if (strcmp(Trim(&vParamName[0]), &pParamName[0]) == 0){
		if (strcmp(&vParamName[0], &pParamName[0]) == 0) {
			(*oParamValue) = atof(vParamValue);
			fclose(ParamFile);
			return 0;
		}
	}
	fclose(ParamFile);
	printf("ReadParamFromFile() could not find Parameter: %s . Exiting.\n", pParamName);
	printf("Press any key to continue...\n"); getchar();;
	return -1;
}
int	cParamsSource::ReadParamFromFile(char* pFileName, char* pParamName, char* oParamValue){
	FILE* ParamFile;
	char vParamName[1000];
	char vParamValue[1000];

	ParamFile = fopen(pFileName, "r");
	if (ParamFile == NULL) {
		printf("ReadParamFromFile() could not open Parameter file: %s . Exiting.\n", pFileName);
		printf("Press any key to continue...\n"); getchar();;
		return -1;
	}
	while (fscanf(ParamFile, "%s = %[^\n]", &vParamName[0], &vParamValue[0]) != EOF) {
		Trim(vParamName);
		if (strcmp(&vParamName[0], &pParamName[0]) == 0) {
			strcpy(oParamValue, vParamValue);
			fclose(ParamFile);
			return 0;
		}
	}
	printf("ReadParamFromFile() could not find Parameter: %s . Exiting.\n", pParamName);
	printf("Press any key to continue...\n"); getchar();;
	fclose(ParamFile);
	return -1;
}
EXPORT int cParamsSource::getParam(char* paramName, int* oparamVal) {
	char* vparamName = _strdup(paramName);
	UpperCase(vparamName);
	for (int p = 1; p < CLparamCount; p++) {
		if (strcmp(CLparamName[p], vparamName) == 0) {
			(*oparamVal) = atoi(CLparamVal[p]);
			free(vparamName);
			return 0;
		}
	}
	free(vparamName);
	return ReadParamFromFile(IniFileName, paramName, oparamVal);
}
EXPORT int cParamsSource::getParam(char* paramName, double* oparamVal) {
	char* vparamName = _strdup(paramName);
	for (int p = 1; p < CLparamCount; p++) {
		if (strcmp(CLparamName[p], vparamName) == 0) {
			(*oparamVal) = atof(CLparamVal[p]);
			free(vparamName);
			return 0;
		}
	}
	free(vparamName);
	return ReadParamFromFile(IniFileName, paramName, oparamVal);
}
EXPORT int cParamsSource::getParam(char* paramName, char* oparamVal) {
	char* vparamName = _strdup(paramName);
	for (int p = 1; p < CLparamCount; p++) {
		if (strcmp(CLparamName[p], vparamName) == 0) {
			strcpy(oparamVal, CLparamVal[p]);
			free(vparamName);
			return 0;
		}
	}
	free(vparamName);
	return ReadParamFromFile(IniFileName, paramName, oparamVal);
}
EXPORT int cParamsSource::getParam(char* paramName, int* oparamVal, bool isenum) {
	char* vparamName = _strdup(paramName);
	char evals[100];
	for (int p = 1; p < CLparamCount; p++) {
		if (strcmp(CLparamName[p], vparamName) == 0) {
			strcpy(evals, CLparamVal[p]);
			(*oparamVal) = getEnumVal(vparamName, evals);
			free(vparamName);
			return 0;
		}
	}
	if (ReadParamFromFile(IniFileName, vparamName, evals) != 0) return -1;
	(*oparamVal) = getEnumVal(vparamName, evals);
	free(vparamName);
	return 0;
}

//-- array parameters
int	cParamsSource::ReadParamFromFile(char* pFileName, char* pParamName, int** oParamValue){
	char vParamValue[1000];
	int i;
	int ArrayLen;
	char** subP = (char**)malloc(ARRAY_PARAMETER_MAX_LEN * sizeof(char*)); for (i = 0; i<ARRAY_PARAMETER_MAX_LEN; i++) subP[i] = (char*)malloc(256);

	if (ReadParamFromFile(pFileName, pParamName, &vParamValue[0]) != 0) return -1;
	//-- now, vParamValue has the '|'-separated list of values
	ArrayLen = cslToArray(vParamValue, ',', subP);
	for (i = 0; i < ArrayLen; i++) {
		(*oParamValue)[i] = atoi(subP[i]);
	}
	for (i = 0; i<ARRAY_PARAMETER_MAX_LEN; i++) free(subP[i]);
	free(subP);
	return ArrayLen;
}
int	cParamsSource::ReadParamFromFile(char* pFileName, char* pParamName, double** oParamValue){
	char vParamValue[1000];
	int i;
	int ArrayLen;
	char** subP = (char**)malloc(ARRAY_PARAMETER_MAX_LEN * sizeof(char*)); for (i = 0; i<ARRAY_PARAMETER_MAX_LEN; i++) subP[i] = (char*)malloc(256);

	if (ReadParamFromFile(pFileName, pParamName, &vParamValue[0]) != 0) return -1;
	//-- now, vParamValue has the '|'-separated list of values
	ArrayLen = cslToArray(vParamValue, ',', subP);
	for (i = 0; i < ArrayLen; i++) {
		(*oParamValue)[i] = atof(subP[i]);
	}
	for (i = 0; i<ARRAY_PARAMETER_MAX_LEN; i++) free(subP[i]);
	free(subP);
	return ArrayLen;
}
int	cParamsSource::ReadParamFromFile(char* pFileName, char* pParamName, char*** oParamValue){
	char vParamValue[1000];
	int i;
	int ArrayLen;
	char** subP = (char**)malloc(ARRAY_PARAMETER_MAX_LEN * sizeof(char*)); for (i = 0; i<ARRAY_PARAMETER_MAX_LEN; i++) subP[i] = (char*)malloc(256);

	if (ReadParamFromFile(pFileName, pParamName, &vParamValue[0]) != 0) return -1;
	//-- now, vParamValue has the '|'-separated list of values
	ArrayLen = cslToArray(vParamValue, ',', subP);
	for (i = 0; i < ArrayLen; i++) {
		strcpy((*oParamValue)[i], subP[i]);
	}
	for (i = 0; i<ARRAY_PARAMETER_MAX_LEN; i++) free(subP[i]);
	free(subP);
	return ArrayLen;
}
EXPORT int cParamsSource::getParam(char* paramName, int** oparamVal) {
	//-- TODO: look in command-line parameters first
	return ReadParamFromFile(IniFileName, paramName, oparamVal);
}
EXPORT int cParamsSource::getParam(char* paramName, double** oparamVal) {
	//-- TODO: look in command-line parameters first
	return ReadParamFromFile(IniFileName, paramName, oparamVal);
}
EXPORT int cParamsSource::getParam(char* paramName, char*** oparamVal) {
	//-- TODO: look in command-line parameters first
	return ReadParamFromFile(IniFileName, paramName, oparamVal);
}
EXPORT int cParamsSource::getParam(char* paramName, int** oparamVal, bool isenum) {
	char pname[100]; strcpy(pname, paramName);
	char** carr = MallocArray<char>(100, 100);
	int elemCnt = ReadParamFromFile(IniFileName, pname, &carr);
	if (elemCnt < 0) return -1;
	for (int i = 0; i < elemCnt; i++) {
		(*oparamVal)[i] = getEnumVal(pname, carr[i]);
	}
	FreeArray(100, 100, carr);
	return elemCnt;
}

//-- command-line parameters processing
int cParamsSource::CLFail(int p){
	printf("Command Line Fail on parameter %d !\nExiting...\n", p);
	printf("Press any key to continue...\n"); getchar();;
	return -1;
}
int	cParamsSource::CLProcess(int argc, char* argv[]){
	bool altIniFile = false;
	CLparamCount = argc;
	for (int p = 1; p < CLparamCount; p++) {
		char* pch = strchr(argv[p], '=');
		if (pch == NULL || argv[p][0] != '-' || argv[p][1] != '-') return CLFail(p);
		memcpy(&CLparamName[p][0], &argv[p][2], (pch - argv[p] - 2)); CLparamName[p][pch - argv[p] - 2] = '\0';
		memcpy(&CLparamVal[p][0], &argv[p][pch - argv[p] + 1], strlen(argv[p]));

		//-- if --IniFileName is specified, then set IniFileName global variable
		UpperCase(CLparamName[p]);
		if (strcmp(CLparamName[p], "INIFILE") == 0) {
			altIniFile = true;
			//... should check for path ...
			strcpy(IniFileName, CLparamVal[p]);
		}
	}

	//-- if --IniFileName is not specified, then set look for default ini file in current directory
	if (!altIniFile) {
		strcpy(IniFileName, MyGetCurrentDirectory());
		strcat(IniFileName, "\\"); strcat(IniFileName, "Tester.ini");
	}

	return 0;
}

//-- main processing
EXPORT int cParamsSource::Process(int section) {
	//-- 1. get Debug Parameters (needs to be before LoadXXXParms)
	DebugParms = new tDebugInfo();
	if (getParam("Forecaster.DebugLevel", &DebugParms->DebugLevel) < 0)					return -1;
	if (getParam("Forecaster.DebugFileName", DebugParms->fName) < 0)					return -1;
	if (getParam("Forecaster.DebugFilePath", DebugParms->fPath) < 0)					return -1;
	if (getParam("Forecaster.ThreadSafeLogging", &DebugParms->ThreadSafeLogging) < 0)	return -1;
	if (getParam("Results.SaveMSE", &DebugParms->SaveMSE) < 0)							return -1;
	if (getParam("Results.SaveRUN", &DebugParms->SaveRun) < 0)							return -1;
	if (getParam("Results.SaveInternals", &DebugParms->SaveInternals) < 0)				return -1;
	if (getParam("Results.Destination", &DebugParms->DebugDest, enumlist) < 0)			return -1;
	if (getParam("Results.DBUser", DebugParms->DebugDB->DBUser) < 0)					return -1;
	if (getParam("Results.DBPassword", DebugParms->DebugDB->DBPassword) < 0)			return -1;
	if (getParam("Results.DBConnString", DebugParms->DebugDB->DBConnString) < 0)		return -1;
	DebugParms->DebugDB->DBCtx = NULL;

	//-- 2. Tester Data Source parameters (DatasetsCount needed before LoadXXXImage)
	DataParms = new tDataShape();
	FXDBInfo = new tFXData();
	DataSourceFileInfo = new tFileData();
	if (getParam("DataSource.SourceType", &DataParms->DataSourceType, enumlist) < 0)		return -1;
	if (DataParms->DataSourceType == SOURCE_DATA_FROM_FXDB) {
		if (getParam("DataSource.DBConn.DBUser", FXDBInfo->FXDB->DBUser) < 0)				return -1;
		if (getParam("DataSource.DBConn.DBPassword", FXDBInfo->FXDB->DBPassword) < 0)		return -1;
		if (getParam("DataSource.DBConn.DBConnString", FXDBInfo->FXDB->DBConnString) < 0)	return -1;
		FXDBInfo->FXDB->DBCtx = NULL;
		if (getParam("DataSource.Symbol", FXDBInfo->Symbol) < 0)							return -1;
		if (getParam("DataSource.TimeFrame", FXDBInfo->TimeFrame) < 0)						return -1;
		if (getParam("DataSource.IsFilled", &FXDBInfo->IsFilled) < 0)						return -1;
		//-- bardatatypes, DataParms->DatasetsCount...
		DataParms->DatasetsCount = getParam("DataSource.BarDataTypes", &FXDBInfo->BarDataType, enumlist); if (DataParms->DatasetsCount < 0) return -1;
		FXDBInfo->BarDataTypeCount = DataParms->DatasetsCount;
		strcpy(DataSourceFileInfo->FileName, "");
		DataParms->DataSource = &FXDBInfo;
	} else {
		if (getParam("DataSource.FileName", DataSourceFileInfo->FileName) < 0)	return -1;
		DataParms->DatasetsCount = getParam("DataSource.FileDatasets", &DataSourceFileInfo->FileDataSet);
		strcpy(FXDBInfo->Symbol, "");
		strcpy(FXDBInfo->TimeFrame, "");
		FXDBInfo->IsFilled = 0;
		FXDBInfo->BarDataTypeCount = 0;
		DataSourceFileInfo->FileDataSetsCount = DataParms->DatasetsCount;
		DataParms->DataSource = &DataSourceFileInfo;
	}

	//-- 3. DoTraining and HaveFutureData
	if (getParam("Forecaster.DoTraining", &DoTraining) < 0)			return -1;
	if (getParam("Forecaster.HaveFutureData", &HaveFutureData) < 0)	return -1;

	//-- 4. set Engine properties
	Engine = new cEngine(DataParms->SampleLen, DataParms->PredictionLen);

	//-- 4.1. set TSFs
	int useTSF;
	if (getParam("DataParms.UseTSFeatures", &useTSF) < 0) return -1;
	if (useTSF > 0) {
		Engine->TSFcnt = getParam("DataParms.TSFeatures", &Engine->TSFid, enumlist); if (Engine->TSFcnt < 0) return -1;
	} else {
		Engine->TSFcnt = 0;
	}

	//-- 5a. if using a saved engine, get Engine and DataShape here
	SavedEngine = new tEngineHandle();
	if (DoTraining == 0) {
		if (getParam("SavedEngine.ProcessId", &SavedEngine->ProcessId) < 0)	return -1;
		if (getParam("SavedEngine.TestId", &SavedEngine->TestId) < 0)			return -1;
		if (getParam("SavedEngine.DatasetId", &SavedEngine->DatasetId) < 0)	return -1;
		DataParms->ValidationShift = 0;

		if (LoadDataParms(DebugParms, SavedEngine->ProcessId, &DataParms->HistoryLen, &DataParms->SampleLen, &DataParms->PredictionLen, &DataParms->SampleCount, &DataParms->DataTransformation, &DataParms->wiggleRoom) != 0)	return -1;
		if (LoadEngineParms(DebugParms, SavedEngine->ProcessId, &Engine->EngineType, &Engine->LayersCount, &Engine->WNN_DecompLevel, &Engine->WNN_WaveletType) != 0)														return -1;
		//-- before loading cores, we need to set layout based on EngineType just loaded
		Engine->setLayout();
		//-- Cores Parameters.
		if (Engine->LoadCoresParms(DebugParms, SavedEngine->ProcessId) != 0) return -1;
		//-- Core Logs
		Engine->mallocCoresLogs(DataParms->DatasetsCount);
		// Finally, Core Images
		if (Engine->LoadCoresImage(DebugParms, SavedEngine->ProcessId) != 0) return -1;
	} else {
		//-- 5b
		if (getParam("Forecaster.Engine", &Engine->EngineType, enumlist) < 0)	return -1;
		Engine->setLayout();

		//-- Data Shape parameters 		
		if (getParam("DataParms->HistoryLen", &DataParms->HistoryLen) < 0)								return -1;
		if (getParam("DataParms->SampleLen", &DataParms->SampleLen) < 0)								return -1;
		if (getParam("DataParms->PredictionLen", &DataParms->PredictionLen) < 0)						return -1;
		if (getParam("DataParms->ValidationShift", &DataParms->ValidationShift) < 0)					return -1;
		if (getParam("DataParms->DataTransformation", &DataParms->DataTransformation, enumlist) < 0)	return -1;
		if (getParam("DataParms->WiggleRoom", &DataParms->wiggleRoom) < 0)								return -1;
		DataParms->SampleCount = DataParms->HistoryLen - DataParms->SampleLen;

		//-- Engine-specific parameters
		cNN*  NNInfo = nullptr;
		cGA*  GAInfo = nullptr;
		cSOM* SOMInfo = nullptr;
		cSVM* SVMInfo = nullptr;
		int l;

		switch (Engine->EngineType) {

		case ENGINE_NN:
			NNInfo = (cNN*)Engine->Core[0][0]->core;
			if (getParam("NNInfo.UseContext", &NNInfo->useContext) < 0)								return -1;
			if (getParam("NNInfo.TrainingProtocol", &NNInfo->TrainingProtocol, enumlist) < 0)		return -1;
			if (getParam("NNInfo.BP_Algo", &NNInfo->BPAlgo, enumlist) < 0)							return -1;
			if (getParam("NNInfo.ActivationFunction", &NNInfo->ActivationFunction, enumlist) < 0)	return -1;
			if (getParam("NNInfo.StopAtDivergence", &NNInfo->StopAtDivergence) < 0)					return -1;
			if (getParam("NNInfo.MaxEpochs", &NNInfo->maxEpochs) < 0)								return -1;
			if (getParam("NNInfo.LearningRate", &NNInfo->LearningRate) < 0)							return -1;
			if (getParam("NNInfo.LearningMomentum", &NNInfo->LearningMomentum) < 0)					return -1;
			if (getParam("NNInfo.TargetMSE", &NNInfo->TargetMSE) < 0)								return -1;
			if (getParam("NNInfo.HCPbeta", &NNInfo->HCPbeta) < 0)									return -1;
			if (getParam("NNInfo.mu", &NNInfo->mu) < 0)												return -1;
			if (getParam("NNInfo.LevelRatios", &NNInfo->levelRatioS[0]) < 0)						return -1;
			break;

		case ENGINE_GA:
			GAInfo = (cGA*)Engine->Core[0][0]->core;
			if (getParam("GAInfo.SlidingFactor", &GAInfo->SlidingFactor) < 0)								return -1;
			if (getParam("GAInfo.Levels", &GAInfo->Levels) < 0)												return -1;
			if (getParam("GAInfo.PopulationSize", &GAInfo->PopulationSize) < 0)								return -1;
			if (getParam("GAInfo.MaxGenerations", &GAInfo->MaxGenerations) < 0)								return -1;
			if (getParam("GAInfo.TargetFitness", &GAInfo->TargetFitness) < 0)								return -1;
			if (getParam("GAInfo.FitnessSkewingFactor", &GAInfo->FitnessSkewingFactor) < 0)					return -1;
			if (getParam("GAInfo.FitnessThreshold", &GAInfo->FitnessThreshold) < 0)							return -1;
			if (getParam("GAInfo.CrossOverProbability", &GAInfo->CrossOverProbability) < 0)					return -1;
			if (getParam("GAInfo.MutationProbability", &GAInfo->MutationProbability) < 0)					return -1;
			if (getParam("GAInfo.CrossSelfRate", &GAInfo->CrossSelfRate) < 0)								return -1;
			if (getParam("GAInfo.RouletteMaxTries", &GAInfo->RouletteMaxTries) < 0)							return -1;
			if (getParam("GAInfo.ADF_Tree_FixedValues_Ratio", &GAInfo->ADF_Tree_FixedValues_Ratio) < 0)		return -1;
			if (getParam("GAInfo.ADF_Tree_DataPoints_Ratio", &GAInfo->ADF_Tree_DataPoints_Ratio) < 0)		return -1;
			if (getParam("GAInfo.ADF_Leaf_FixedValues_Ratio", &GAInfo->ADF_Leaf_FixedValues_Ratio) < 0)		return -1;
			if (getParam("GAInfo.MaxReRuns", &GAInfo->MaxReRuns) < 0)										return -1;
			if (getParam("GAInfo.BestChrPath", GAInfo->BestChrPath) < 0)									return -1;
			break;
		
		case ENGINE_SOM:
			SOMInfo = (cSOM*)Engine->Core[0][0]->core;
			if (getParam("SOMInfo.OutputCount", &SOMInfo->OutputCount) < 0)			return -1;
			if (getParam("SOMInfo.OutputWidth", &SOMInfo->OutputWidth) < 0)			return -1;
			if (getParam("SOMInfo.MaxEpochs", &SOMInfo->MaxEpochs) < 0)				return -1;
			if (getParam("SOMInfo.TDFunction", &SOMInfo->TDFunction, enumlist) < 0)	return -1;
			if (getParam("SOMInfo.BaseLR", &SOMInfo->BaseLR) < 0)						return -1;
			if (getParam("SOMInfo.LRFunction", &SOMInfo->LRFunction, enumlist) < 0)	return -1;
			break;

		case ENGINE_SVM:
			SVMInfo = (cSVM*)Engine->Core[0][0]->core;
			if (getParam("SVMInfo.DebugLevel", &SVMInfo->DebugLevel) < 0)				return -1;
			if (getParam("SVMInfo.C", &SVMInfo->C) < 0)								return -1;
			if (getParam("SVMInfo.IterToShrink", &SVMInfo->svmIterToShrink) < 0)		return -1;
			if (getParam("SVMInfo.MaxEpochs", &SVMInfo->MaxEpochs) < 0)				return -1;
			if (getParam("SVMInfo.epsilon", &SVMInfo->epsilon) < 0)					return -1;
			if (getParam("SVMInfo.KernelType", &SVMInfo->KernelType, enumlist) < 0)	return -1;
			if (getParam("SVMInfo.PolyDegree", &SVMInfo->PolyDegree) < 0)				return -1;
			if (getParam("SVMInfo.RBFGamma", &SVMInfo->RBFGamma) < 0)					return -1;
			if (getParam("SVMInfo.CoefLin", &SVMInfo->CoefLin) < 0)					return -1;
			if (getParam("SVMInfo.CoefConst", &SVMInfo->CoefConst) < 0)				return -1;
			if (getParam("SVMInfo.KernelCacheSize", &SVMInfo->KernelCacheSize) < 0)	return -1;
			if (getParam("SVMInfo.CustomKernel", SVMInfo->CustomKernel) < 0)			return -1;
			//--
			if (getParam("SVMInfo.SlackNorm", &SVMInfo->SlackNorm, enumlist) < 0)				return -1;
			if (getParam("SVMInfo.RescalingMethod", &SVMInfo->RescalingMethod, enumlist) < 0)	return -1;
			if (getParam("SVMInfo.LossFunction", &SVMInfo->LossFunction, enumlist) < 0)		return -1;
			if (getParam("SVMInfo.LearningAlgo", &SVMInfo->LearningAlgo, enumlist) < 0)		return -1;
			if (getParam("SVMInfo.NewConstrEtrain", &SVMInfo->NewConstrEtrain) < 0)			return -1;
			if (getParam("SVMINfo.CCacheSize", &SVMInfo->CCacheSize) < 0)						return -1;
			if (getParam("SVMInfo.BatchSize", &SVMInfo->BatchSize) < 0)						return -1;
			if (getParam("SVMInfo.NewVarSinQP", &SVMInfo->NewVarSinQP) < 0)					return -1;
			break;
		case ENGINE_WNN:
			l = 0;
			for (int c = 0; c < Engine->CoresCount[l]; c++) {
				NNInfo = (cNN*)Engine->Core[l][c]->core;
				if (getParam("WNNInfo.L0.UseContext", &NNInfo->useContext) <0)								return -1;
				if (getParam("WNNInfo.L0.TrainingProtocol", &NNInfo->TrainingProtocol, enumlist) <0)		return -1;
				if (getParam("WNNInfo.L0.BP_Algo", &NNInfo->BPAlgo, enumlist) <0)							return -1;
				if (getParam("WNNInfo.L0.ActivationFunction", &NNInfo->ActivationFunction, enumlist) <0)	return -1;
				if (getParam("WNNInfo.L0.StopAtDivergence", &NNInfo->StopAtDivergence) <0)					return -1;
				if (getParam("WNNInfo.L0.MaxEpochs", &NNInfo->maxEpochs) <0)								return -1;
				if (getParam("WNNInfo.L0.LearningRate", &NNInfo->LearningRate) <0)							return -1;
				if (getParam("WNNInfo.L0.LearningMomentum", &NNInfo->LearningMomentum) <0)					return -1;
				if (getParam("WNNInfo.L0.TargetMSE", &NNInfo->TargetMSE) <0)								return -1;
				if (getParam("WNNInfo.L0.HCPbeta", &NNInfo->HCPbeta) <0)									return -1;
				if (getParam("WNNInfo.L0.mu", &NNInfo->mu) <0)												return -1;
				if (getParam("WNNInfo.L0.LevelRatios", &NNInfo->levelRatioS[0]) <0)							return -1;
			}
			l = 1;
			NNInfo = (cNN*)Engine->Core[l][0]->core;
			if (getParam("WNNInfo.L1.UseContext", &NNInfo->useContext) <0)								return -1;
			if (getParam("WNNInfo.L1.TrainingProtocol", &NNInfo->TrainingProtocol, enumlist) <0)		return -1;
			if (getParam("WNNInfo.L1.BP_Algo", &NNInfo->BPAlgo, enumlist) <0)							return -1;
			if (getParam("WNNInfo.L1.ActivationFunction", &NNInfo->ActivationFunction, enumlist) <0)	return -1;
			if (getParam("WNNInfo.L1.StopAtDivergence", &NNInfo->StopAtDivergence) <0)					return -1;
			if (getParam("WNNInfo.L1.MaxEpochs", &NNInfo->maxEpochs) <0)								return -1;
			if (getParam("WNNInfo.L1.LearningRate", &NNInfo->LearningRate) <0)							return -1;
			if (getParam("WNNInfo.L1.LearningMomentum", &NNInfo->LearningMomentum) <0)					return -1;
			if (getParam("WNNInfo.L1.TargetMSE", &NNInfo->TargetMSE) <0)								return -1;
			if (getParam("WNNInfo.L1.HCPbeta", &NNInfo->HCPbeta) <0)									return -1;
			if (getParam("WNNInfo.L1.mu", &NNInfo->mu) <0)												return -1;
			if (getParam("WNNInfo.L1.LevelRatios", &NNInfo->levelRatioS[0]) <0)							return -1;
			break;
		case ENGINE_XIE:
			SVMInfo = (cSVM*)Engine->Core[0][0]->core;
			if (getParam("XIEInfo.SVM.DebugLevel", &SVMInfo->DebugLevel) < 0)				return -1;
			if (getParam("XIEInfo.SVM.C", &SVMInfo->C) < 0)								return -1;
			if (getParam("XIEInfo.SVM.IterToShrink", &SVMInfo->svmIterToShrink) < 0)		return -1;
			if (getParam("XIEInfo.SVM.MaxEpochs", &SVMInfo->MaxEpochs) < 0)				return -1;
			if (getParam("XIEInfo.SVM.epsilon", &SVMInfo->epsilon) < 0)					return -1;
			if (getParam("XIEInfo.SVM.KernelType", &SVMInfo->KernelType, enumlist) < 0)	return -1;
			if (getParam("XIEInfo.SVM.PolyDegree", &SVMInfo->PolyDegree) < 0)				return -1;
			if (getParam("XIEInfo.SVM.RBFGamma", &SVMInfo->RBFGamma) < 0)					return -1;
			if (getParam("XIEInfo.SVM.CoefLin", &SVMInfo->CoefLin) < 0)					return -1;
			if (getParam("XIEInfo.SVM.CoefConst", &SVMInfo->CoefConst) < 0)				return -1;
			if (getParam("XIEInfo.SVM.KernelCacheSize", &SVMInfo->KernelCacheSize) < 0)	return -1;
			if (getParam("XIEInfo.SVM.CustomKernel", SVMInfo->CustomKernel) < 0)			return -1;
			//--
			if (getParam("XIEInfo.SVM.SlackNorm", &SVMInfo->SlackNorm, enumlist) < 0)				return -1;
			if (getParam("XIEInfo.SVM.RescalingMethod", &SVMInfo->RescalingMethod, enumlist) < 0)	return -1;
			if (getParam("XIEInfo.SVM.LossFunction", &SVMInfo->LossFunction, enumlist) < 0)		return -1;
			if (getParam("XIEInfo.SVM.LearningAlgo", &SVMInfo->LearningAlgo, enumlist) < 0)		return -1;
			if (getParam("XIEInfo.SVM.NewConstrEtrain", &SVMInfo->NewConstrEtrain) < 0)			return -1;
			if (getParam("XIEInfo.SVM.CCacheSize", &SVMInfo->CCacheSize) < 0)						return -1;
			if (getParam("XIEInfo.SVM.BatchSize", &SVMInfo->BatchSize) < 0)						return -1;
			if (getParam("XIEInfo.SVM.NewVarSinQP", &SVMInfo->NewVarSinQP) < 0)					return -1;

			NNInfo = (cNN*)Engine->Core[0][1]->core;
			if (getParam("XIEInfo.NN0.UseContext", &NNInfo->useContext) < 0)							return -1;
			if (getParam("XIEInfo.NN0.TrainingProtocol", &NNInfo->TrainingProtocol, enumlist) < 0)		return -1;
			if (getParam("XIEInfo.NN0.BP_Algo", &NNInfo->BPAlgo, enumlist) < 0)						return -1;
			if (getParam("XIEInfo.NN0.ActivationFunction", &NNInfo->ActivationFunction, enumlist) < 0)	return -1;
			if (getParam("XIEInfo.NN0.StopAtDivergence", &NNInfo->StopAtDivergence) < 0)				return -1;
			if (getParam("XIEInfo.NN0.MaxEpochs", &NNInfo->maxEpochs) < 0)								return -1;
			if (getParam("XIEInfo.NN0.LearningRate", &NNInfo->LearningRate) < 0)						return -1;
			if (getParam("XIEInfo.NN0.LearningMomentum", &NNInfo->LearningMomentum) < 0)				return -1;
			if (getParam("XIEInfo.NN0.TargetMSE", &NNInfo->TargetMSE) < 0)								return -1;
			if (getParam("XIEInfo.NN0.HCPbeta", &NNInfo->HCPbeta) < 0)									return -1;
			if (getParam("XIEInfo.NN0.mu", &NNInfo->mu) < 0)											return -1;
			if (getParam("XIEInfo.NN0.LevelRatios", &NNInfo->levelRatioS[0]) < 0)						return -1;

			NNInfo = (cNN*)Engine->Core[1][0]->core;
			if (getParam("XIEInfo.NN1.UseContext", &NNInfo->useContext) < 0)							return -1;
			if (getParam("XIEInfo.NN1.TrainingProtocol", &NNInfo->TrainingProtocol, enumlist) < 0)		return -1;
			if (getParam("XIEInfo.NN1.BP_Algo", &NNInfo->BPAlgo, enumlist) < 0)						return -1;
			if (getParam("XIEInfo.NN1.ActivationFunction", &NNInfo->ActivationFunction, enumlist) < 0)	return -1;
			if (getParam("XIEInfo.NN1.StopAtDivergence", &NNInfo->StopAtDivergence) < 0)				return -1;
			if (getParam("XIEInfo.NN1.MaxEpochs", &NNInfo->maxEpochs) < 0)								return -1;
			if (getParam("XIEInfo.NN1.LearningRate", &NNInfo->LearningRate) < 0)						return -1;
			if (getParam("XIEInfo.NN1.LearningMomentum", &NNInfo->LearningMomentum) < 0)				return -1;
			if (getParam("XIEInfo.NN1.TargetMSE", &NNInfo->TargetMSE) < 0)								return -1;
			if (getParam("XIEInfo.NN1.HCPbeta", &NNInfo->HCPbeta) < 0)									return -1;
			if (getParam("XIEInfo.NN1.mu", &NNInfo->mu) < 0)											return -1;
			if (getParam("XIEInfo.NN1.LevelRatios", &NNInfo->levelRatioS[0]) < 0)						return -1;

			break;
		}
		//-- Core Logs
		Engine->mallocCoresLogs(DataParms->DatasetsCount);
	}
	return 0;
}

//-- constructor / destructor
EXPORT cParamsSource::cParamsSource(int argc, char* argv[]){
	CLProcess(argc, argv);
}
EXPORT cParamsSource::~cParamsSource(){}

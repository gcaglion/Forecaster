//#include <vld.h>

#include <MyEnums.h>

//=============== ENUMS ============================
__declspec(dllexport) int __stdcall getEnumVal(char* edesc, char* eval) {
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
//==================================================

//============ SINGLE-VALUE VERSIONS ===============
__declspec(dllexport) int __stdcall	ReadParamFromFile(char* pFileName, char* pParamName, int* oParamValue) {
	FILE* ParamFile;
	char vParamName[1000];
	char vParamValue[1000];

	ParamFile = fopen(pFileName, "r");
	if (ParamFile == NULL) {
		printf("ReadParamFromFile() could not open Parameter file: %s . Exiting.\n", pFileName);
		printf("Press any key..."); getchar();;
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
	printf("Press any key..."); getchar();;
	return -1;
}
__declspec(dllexport) int __stdcall	ReadParamFromFile(char* pFileName, char* pParamName, double* oParamValue) {
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
	printf("Press any key..."); getchar();;
	return -1;
}
__declspec(dllexport) int __stdcall	ReadParamFromFile(char* pFileName, char* pParamName, char* oParamValue) {
	FILE* ParamFile;
	char vParamName[1000];
	char vParamValue[1000];

	ParamFile = fopen(pFileName, "r");
	if (ParamFile == NULL) {
		printf("ReadParamFromFile() could not open Parameter file: %s . Exiting.\n", pFileName);
		printf("Press any key..."); getchar();;
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
	printf("Press any key..."); getchar();;
	fclose(ParamFile);
	return -1;
}
//==================================================

//=============== ARRAY VERSIONS ===================
__declspec(dllexport) int __stdcall	ReadParamFromFile(char* pFileName, char* pParamName, int** oParamValue) {
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
__declspec(dllexport) int __stdcall	ReadParamFromFile(char* pFileName, char* pParamName, double** oParamValue) {
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
__declspec(dllexport) int __stdcall	ReadParamFromFile(char* pFileName, char* pParamName, char*** oParamValue) {
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
//==================================================

//============ WNN VERSIONS - OBSOLETE ===============
/*
__declspec(dllexport) int __stdcall	ReadParamArrayFromFile(char* pFileName, char* pParamName, int* oParamValue) {
	char vParamValue[1000];
	int i;
	int ArrayLen;
	char** subP = (char**)malloc(MAX_LAYERS * sizeof(char*)); for (i = 0; i<MAX_LAYERS; i++) subP[i] = (char*)malloc(256);

	if (ReadParamFromFile(pFileName, pParamName, &vParamValue[0]) != 0) return -1;
	//-- now, vParamValue has the '|'-separated list of values
	ArrayLen = cslToArray(vParamValue, 124, subP);
	for (i = 0; i<ArrayLen; i++) oParamValue[i] = atoi(subP[i]);

	for (i = 0; i<MAX_LAYERS; i++) free(subP[i]);
	free(subP);
	return 0;
}
__declspec(dllexport) int __stdcall	ReadParamArrayFromFile(char* pFileName, char* pParamName, double* oParamValue) {
	char vParamValue[1000];
	int i;
	int ArrayLen;
	char** subP = (char**)malloc(MAX_LAYERS * sizeof(char*)); for (i = 0; i<MAX_LAYERS; i++) subP[i] = (char*)malloc(256);

	if (ReadParamFromFile(pFileName, pParamName, &vParamValue[0]) != 0) return -1;
	//-- now, vParamValue has the '|'-separated list of values
	ArrayLen = cslToArray(vParamValue, 124, subP);
	for (i = 0; i<ArrayLen; i++) oParamValue[i] = atof(subP[i]);

	for (i = 0; i<MAX_LAYERS; i++) free(subP[i]);
	free(subP);
	return 0;
}
__declspec(dllexport) int __stdcall	ReadParamArrayFromFile(char* pFileName, char* pParamName, char** oParamValue) {
	char vParamValue[1000];
	int i;
	int ArrayLen;
	char** subP = (char**)malloc(MAX_LAYERS * sizeof(char*)); for (i = 0; i<MAX_LAYERS; i++) subP[i] = (char*)malloc(256);

	if (ReadParamFromFile(pFileName, pParamName, &vParamValue[0]) != 0) return -1;
	//-- now, vParamValue has the '|'-separated list of values
	ArrayLen = cslToArray(vParamValue, 124, subP);
	for (i = 0; i<ArrayLen; i++) strcpy(oParamValue[i], subP[i]);

	for (i = 0; i<MAX_LAYERS; i++) free(subP[i]);
	free(subP);
	return 0;
}
*/
//==================================================

/*static int CLparamCount;
static char CLparamName[1000][100];	// 1000 parameters max. Parameter name must bel less than 100 characters long
static char CLparamVal[1000][100];		// 1000 parameters max. Parameter name must bel less than 100 characters long
*/


//-- command-line parameters processing
int CLFail(int p) {
	printf("Command Line Fail on parameter %d !\nExiting...\n", p);
	printf("Press any key..."); getchar();;
	return -1;
}
__declspec(dllexport) int __stdcall	CLProcess(int argc, char* argv[], tForecastParms* iniParms) {
	bool altIniFile = false;
	iniParms->CLparamCount = argc;
	for (int p = 1; p < iniParms->CLparamCount; p++) {
		char* pch = strchr(argv[p], '=');
		if (pch == NULL || argv[p][0] != '-' || argv[p][1] != '-') return CLFail(p);
		memcpy(&iniParms->CLparamName[p][0], &argv[p][2], (pch - argv[p] - 2)); iniParms->CLparamName[p][pch - argv[p] - 2] = '\0';
		memcpy(&iniParms->CLparamVal[p][0], &argv[p][pch - argv[p] + 1], strlen(argv[p]));

		//-- if --IniFileName is specified, then set IniFileName global variable
		UpperCase(iniParms->CLparamName[p]);
		if (strcmp(iniParms->CLparamName[p], "INIFILE") == 0) {
			altIniFile = true;
			//... should check for path ...
			strcpy(iniParms->IniFileName, iniParms->CLparamVal[p]);
		}
	}

	//-- if --IniFileName is not specified, then set look for default ini file in current directory
	if (!altIniFile) {
		strcpy(iniParms->IniFileName, MyGetCurrentDirectory());
		strcat(iniParms->IniFileName, "\\"); strcat(iniParms->IniFileName, "Tester.ini");
	}

	return 0;
}


//-- single value (int, double, char*, enum)
__declspec(dllexport) int __stdcall getParam(tForecastParms* iniParms, char* paramName, int* oparamVal) {
	char* vparamName = _strdup(paramName);
	UpperCase(vparamName);
	for (int p = 1; p < iniParms->CLparamCount; p++) {
		if (strcmp(iniParms->CLparamName[p], vparamName) == 0) {
			(*oparamVal) = atoi(iniParms->CLparamVal[p]);
			free(vparamName);
			return 0;
		}
	}
	free(vparamName);
	return ReadParamFromFile(iniParms->IniFileName, paramName, oparamVal);
}
__declspec(dllexport) int __stdcall getParam(tForecastParms* iniParms, char* paramName, double* oparamVal) {
	char* vparamName = _strdup(paramName);
	for (int p = 1; p < iniParms->CLparamCount; p++) {
		if (strcmp(iniParms->CLparamName[p], vparamName) == 0) {
			(*oparamVal) = atof(iniParms->CLparamVal[p]);
			free(vparamName);
			return 0;
		}
	}
	free(vparamName);
	return ReadParamFromFile(iniParms->IniFileName, paramName, oparamVal);
}
__declspec(dllexport) int __stdcall getParam(tForecastParms* iniParms, char* paramName, char* oparamVal) {
	char* vparamName = _strdup(paramName);
	for (int p = 1; p < iniParms->CLparamCount; p++) {
		if (strcmp(iniParms->CLparamName[p], vparamName) == 0) {
			strcpy(oparamVal, iniParms->CLparamVal[p]);
			free(vparamName);
			return 0;
		}
	}
	free(vparamName);
	return ReadParamFromFile(iniParms->IniFileName, paramName, oparamVal);
}
__declspec(dllexport) int __stdcall getParam(tForecastParms* iniParms, char* paramName, int* oparamVal, bool isenum) {
	char* vparamName = _strdup(paramName);
	char evals[100];
	for (int p = 1; p < iniParms->CLparamCount; p++) {
		if (strcmp(iniParms->CLparamName[p], vparamName) == 0) {
			strcpy(evals, iniParms->CLparamVal[p]);
			(*oparamVal) = getEnumVal(vparamName, evals);
			free(vparamName);
			return 0;
		}
	}
	if (ReadParamFromFile(iniParms->IniFileName, vparamName, evals) != 0) return -1;
	(*oparamVal) = getEnumVal(vparamName, evals);
	free(vparamName);
	return 0;
}

//-- array value (int[], double[], char**, enum
__declspec(dllexport) int __stdcall getParam(tForecastParms* iniParms, char* paramName, int** oparamVal) {
	//-- TODO: look in command-line parameters first
	return ReadParamFromFile(iniParms->IniFileName, paramName, oparamVal);
}
__declspec(dllexport) int __stdcall getParam(tForecastParms* iniParms, char* paramName, double** oparamVal) {
	//-- TODO: look in command-line parameters first
	return ReadParamFromFile(iniParms->IniFileName, paramName, oparamVal);
}
__declspec(dllexport) int __stdcall getParam(tForecastParms* iniParms, char* paramName, char*** oparamVal) {
	//-- TODO: look in command-line parameters first
	return ReadParamFromFile(iniParms->IniFileName, paramName, oparamVal);
}
__declspec(dllexport) int __stdcall getParam(tForecastParms* iniParms, char* paramName, int** oparamVal, bool isenum) {
	char pname[100]; strcpy(pname, paramName);
	char** carr = MallocArray<char>(100, 100);
	int elemCnt = ReadParamFromFile(iniParms->IniFileName, pname, &carr);
	if (elemCnt < 0) return -1;
	for (int i = 0; i < elemCnt; i++) {
		(*oparamVal)[i] = getEnumVal(pname, carr[i]);
	}
	FreeArray(100, 100, carr);
	return elemCnt;
}


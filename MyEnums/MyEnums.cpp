//#include <vld.h>

#include <MyEnums.h>

//=============== ENUMS ============================
__declspec(dllexport) int __stdcall getEnumVal(tDebugInfo* pDebugParms, char* edesc, char* eVal, int* oVal) {
	int ret=-1;

	UpperCase(edesc);

	if(strcmp(edesc, "FORECASTER.ACTION")==0){
		if (strcmp(eVal, "TRAIN_SAVE_RUN")==0) { (*oVal)=TRAIN_SAVE_RUN; ret=0;}
		if (strcmp(eVal, "ADD_SAMPLES")==0) { (*oVal)=ADD_SAMPLES; ret=0;}
		if (strcmp(eVal, "JUST_RUN")==0) { (*oVal)=JUST_RUN; ret=0;}
	}
	else if (strcmp(edesc, "FORECASTER.ENGINE") == 0) {
		if (strcmp(eVal, "ENGINE_NN") == 0) { (*oVal)=ENGINE_NN; ret=0;}
		if (strcmp(eVal, "ENGINE_GA") == 0) { (*oVal)=ENGINE_GA; ret=0;}
		if (strcmp(eVal, "ENGINE_SVM") == 0) { (*oVal)=ENGINE_SVM; ret=0;}
		if (strcmp(eVal, "ENGINE_SOM") == 0) { (*oVal)=ENGINE_SOM; ret=0;}
		if (strcmp(eVal, "ENGINE_WNN") == 0) { (*oVal)=ENGINE_WNN; ret=0;}
		if (strcmp(eVal, "ENGINE_XIE") == 0) { (*oVal)=ENGINE_XIE; ret=0;}
	}
	else if (strcmp(edesc, "RESULTS.DESTINATION") == 0) {
		if (strcmp(eVal, "LOG_TO_TEXT") == 0) { (*oVal)=LOG_TO_TEXT; ret=0;}
		if (strcmp(eVal, "LOG_TO_ORCL") == 0) { (*oVal)=LOG_TO_ORCL; ret=0;}
	}
	else if (strcmp(edesc, "DATASOURCE.SOURCETYPE") == 0) {
		if (strcmp(eVal, "SOURCE_DATA_FROM_FXDB") == 0) { (*oVal)=SOURCE_DATA_FROM_FXDB; ret=0;}
		if (strcmp(eVal, "SOURCE_DATA_FROM_FILE") == 0) { (*oVal)=SOURCE_DATA_FROM_FILE; ret=0;}
		if (strcmp(eVal, "SOURCE_DATA_FROM_MT") == 0) { (*oVal)=SOURCE_DATA_FROM_MT; ret=0;}
	}
	else if (strcmp(edesc, "DATASOURCE.SOURCETYPE") == 0) {
	}
	else if (strcmp(edesc, "DATASOURCE.TEXTFIELDSEPARATOR") == 0) {
		if (strcmp(eVal, "COMMA") == 0) { (*oVal)=(int)COMMA; ret=0;}
		if (strcmp(eVal, "TAB") == 0) { (*oVal)=(int)TAB; ret=0;}
		if (strcmp(eVal, "SPACE") == 0) { (*oVal)=(int)SPACE; ret=0;}
	}
	else if (strcmp(edesc, "DATAPARMS.DATATRANSFORMATION") == 0) {
		if (strcmp(eVal, "DT_NONE") == 0) { (*oVal)=DT_NONE; ret=0;}
		if (strcmp(eVal, "DT_DELTA") == 0) { (*oVal)=DT_DELTA; ret=0;}
		if (strcmp(eVal, "DT_LOG") == 0) { (*oVal)=DT_LOG; ret=0;}
		if (strcmp(eVal, "DT_DELTALOG") == 0) { (*oVal)=DT_DELTALOG; ret=0;}
	}
	else if (strcmp(edesc, "DATASOURCE.BARDATATYPES") == 0) {
		if (strcmp(eVal, "OPEN") == 0) { (*oVal)=OPEN; ret=0;}
		if (strcmp(eVal, "HIGH") == 0) { (*oVal)=HIGH; ret=0;}
		if (strcmp(eVal, "LOW") == 0) { (*oVal)=LOW; ret=0;}
		if (strcmp(eVal, "CLOSE") == 0) { (*oVal)=CLOSE; ret=0;}
		if (strcmp(eVal, "VOLUME") == 0) { (*oVal)=VOLUME; ret=0;}
		if (strcmp(eVal, "OTHER") == 0) { (*oVal)=OTHER; ret=0;}
	}
	else if (strcmp(edesc, "DATAPARMS.TSFEATURES") == 0) {
		if (strcmp(eVal, "TSF_MEAN") == 0) { (*oVal)=TSF_MEAN; ret=0;}
		if (strcmp(eVal, "TSF_MAD") == 0) { (*oVal)=TSF_MAD; ret=0;}
		if (strcmp(eVal, "TSF_VARIANCE") == 0) { (*oVal)=TSF_VARIANCE; ret=0;}
		if (strcmp(eVal, "TSF_SKEWNESS") == 0) { (*oVal)=TSF_SKEWNESS; ret=0;}
		if (strcmp(eVal, "TSF_KURTOSIS") == 0) { (*oVal)=TSF_KURTOSIS; ret=0;}
		if (strcmp(eVal, "TSF_TURNINGPOINTS") == 0) { (*oVal)=TSF_TURNINGPOINTS; ret=0;}
		if (strcmp(eVal, "TSF_SHE") == 0) { (*oVal)=TSF_SHE; ret=0;}
		if (strcmp(eVal, "TSF_HISTVOL") == 0) { (*oVal)=TSF_HISTVOL; ret=0;}
	}
	else if (strcmp(right(edesc, 7), "BP_ALGO") == 0) {
		if (strcmp(eVal, "BP_STD") == 0) { (*oVal)=BP_STD; ret=0;}
		if (strcmp(eVal, "BP_QING") == 0) { (*oVal)=BP_QING; ret=0;}
		if (strcmp(eVal, "BP_SCGD") == 0) { (*oVal)=BP_SCGD; ret=0;}
		if (strcmp(eVal, "BP_QUICKPROP") == 0) { (*oVal)=BP_QUICKPROP; ret=0;}
	}
	else if (strcmp(right(edesc, 16), "TRAININGPROTOCOL") == 0) {
		if (strcmp(eVal, "TP_STOCHASTIC") == 0) { (*oVal)=TP_STOCHASTIC; ret=0;}
		if (strcmp(eVal, "TP_BATCH") == 0) { (*oVal)=TP_BATCH; ret=0;}
	}
	else if (strcmp(right(edesc, 18), "ACTIVATIONFUNCTION") == 0) {
		if (strcmp(eVal, "NN_ACTIVATION_TANH") == 0) { (*oVal)=NN_ACTIVATION_TANH; ret=0;}
		if (strcmp(eVal, "NN_ACTIVATION_EXP4") == 0) { (*oVal)=NN_ACTIVATION_EXP4; ret=0;}
	}
	else if (strcmp(edesc, "SOMINFO.TDFUNCTION") == 0) {
		if (strcmp(eVal, "TD_DECAY_CONSTANT") == 0) { (*oVal)=TD_DECAY_CONSTANT; ret=0;}
		if (strcmp(eVal, "TD_DECAY_LINEAR") == 0) { (*oVal)=TD_DECAY_LINEAR; ret=0;}
		if (strcmp(eVal, "TD_DECAY_STEPPED") == 0) { (*oVal)=TD_DECAY_STEPPED; ret=0;}
		if (strcmp(eVal, "TD_DECAY_EXP") == 0) { (*oVal)=TD_DECAY_EXP; ret=0;}
	}
	else if (strcmp(edesc, "SOMINFO.LRFUNCTION") == 0) {
		if (strcmp(eVal, "LR_DECAY_CONSTANT") == 0) { (*oVal)=LR_DECAY_CONSTANT; ret=0;}
		if (strcmp(eVal, "LR_DECAY_LINEAR") == 0) { (*oVal)=LR_DECAY_LINEAR; ret=0;}
		if (strcmp(eVal, "LR_DECAY_STEPPED") == 0) { (*oVal)=LR_DECAY_STEPPED; ret=0;}
		if (strcmp(eVal, "LR_DECAY_EXP") == 0) { (*oVal)=LR_DECAY_EXP; ret=0;}
	}
	else if (strcmp(right(edesc, 10), "KERNELTYPE") == 0) {
		if (strcmp(eVal, "KERNEL_TYPE_LINEAR") == 0) { (*oVal)=KERNEL_TYPE_LINEAR; ret=0;}
		if (strcmp(eVal, "KERNEL_TYPE_POLY") == 0) { (*oVal)=KERNEL_TYPE_POLY; ret=0;}
		if (strcmp(eVal, "KERNEL_TYPE_RBF") == 0) { (*oVal)=KERNEL_TYPE_RBF; ret=0;}
		if (strcmp(eVal, "KERNEL_TYPE_TANH") == 0) { (*oVal)=KERNEL_TYPE_TANH; ret=0;}
		if (strcmp(eVal, "KERNEL_TYPE_CUSTOM") == 0) { (*oVal)=KERNEL_TYPE_CUSTOM; ret=0;}
	}
	else if (strcmp(right(edesc, 9), "SLACKNORM") == 0) {
		if (strcmp(eVal, "SLACK_NORM_L1") == 0) { (*oVal)=SLACK_NORM_L1; ret=0;}
		if (strcmp(eVal, "SLACK_NORM_SQUARED") == 0) { (*oVal)=SLACK_NORM_SQUARED; ret=0;}
	}
	else if (strcmp(right(edesc, 15), "RESCALINGMETHOD") == 0) {
		if (strcmp(eVal, "RESCALING_METHOD_SLACK") == 0) { (*oVal)=RESCALING_METHOD_SLACK; ret=0;}
		if (strcmp(eVal, "RESCALING_METHOD_MARGIN") == 0) { (*oVal)=RESCALING_METHOD_MARGIN; ret=0;}
	}
	else if (strcmp(right(edesc, 12), "LOSSFUNCTION") == 0) {
		if (strcmp(eVal, "LOSS_FUNCTION_ZEROONE") == 0) { (*oVal)=LOSS_FUNCTION_ZEROONE; ret=0;}
	}
	else if (strcmp(right(edesc, 12), "LEARNINGALGO") == 0) {
		if (strcmp(eVal, "LEARNING_ALGO_NSLACK") == 0) { (*oVal)=LEARNING_ALGO_NSLACK; ret=0;}
		if (strcmp(eVal, "LEARNING_ALGO_NSLACK_SHRINK") == 0) { (*oVal)=LEARNING_ALGO_NSLACK_SHRINK; ret=0;}
		if (strcmp(eVal, "LEARNING_ALGO_1SLACK_PRIMAL") == 0) { (*oVal)=LEARNING_ALGO_1SLACK_PRIMAL; ret=0;}
		if (strcmp(eVal, "LEARNING_ALGO_1SLACK_DUAL") == 0) { (*oVal)=LEARNING_ALGO_1SLACK_DUAL; ret=0;}
		if (strcmp(eVal, "LEARNING_ALGO_1SLACK_DUAL_CONSTR") == 0) { (*oVal)=LEARNING_ALGO_1SLACK_DUAL_CONSTR; ret=0;}
		if (strcmp(eVal, "LEARNING_ALGO_CUSTOM") == 0) { (*oVal)=LEARNING_ALGO_CUSTOM; ret=0;}
	}

	if(ret<0) LogWrite(pDebugParms, LOG_ERROR, "Invalid %s value: %s\n", 2, edesc, eVal);
	return ret;
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
		Trim(vParamName); UpperCase(vParamName);
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
		Trim(vParamName); UpperCase(vParamName);
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
		Trim(vParamName); UpperCase(vParamName);
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
		memcpy(&iniParms->CLparamVal[p][0], &argv[p][pch - argv[p] + 1], strlen(pch));

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
	char* vparamName = _strdup(paramName); UpperCase(vparamName);
	for (int p = 1; p < iniParms->CLparamCount; p++) {
		if (strcmp(iniParms->CLparamName[p], vparamName) == 0) {
			(*oparamVal) = atoi(iniParms->CLparamVal[p]);
			free(vparamName);
			return 0;
		}
	}
	int ret = ReadParamFromFile(iniParms->IniFileName, vparamName, oparamVal);
	free(vparamName);
	return ret;
}
__declspec(dllexport) int __stdcall getParam(tForecastParms* iniParms, char* paramName, double* oparamVal) {
	char* vparamName = _strdup(paramName); UpperCase(vparamName);
	for (int p = 1; p < iniParms->CLparamCount; p++) {
		if (strcmp(iniParms->CLparamName[p], vparamName) == 0) {
			(*oparamVal) = atof(iniParms->CLparamVal[p]);
			free(vparamName);
			return 0;
		}
	}
	int ret = ReadParamFromFile(iniParms->IniFileName, vparamName, oparamVal);
	free(vparamName);
	return ret;
}
__declspec(dllexport) int __stdcall getParam(tForecastParms* iniParms, char* paramName, char* oparamVal) {
	char* vparamName = _strdup(paramName); UpperCase(vparamName);
	for (int p = 1; p < iniParms->CLparamCount; p++) {
		if (strcmp(iniParms->CLparamName[p], vparamName) == 0) {
			strcpy(oparamVal, iniParms->CLparamVal[p]);
			free(vparamName);
			return 0;
		}
	}
	int ret = ReadParamFromFile(iniParms->IniFileName, vparamName, oparamVal);
	free(vparamName);
	return ret;
}
__declspec(dllexport) int __stdcall getParam(tForecastParms* iniParms, char* paramName, int* oparamVal, bool isenum) {
	char* vparamName = _strdup(paramName); UpperCase(vparamName);
	char evals[100];
	int ret = 0;
	for (int p = 1; p < iniParms->CLparamCount; p++) {
		if (strcmp(iniParms->CLparamName[p], vparamName) == 0) {
			strcpy(evals, iniParms->CLparamVal[p]);
			ret = getEnumVal(&iniParms->DebugParms, vparamName, evals, oparamVal);
			free(vparamName);
			return ret;
		}
	}
	if (ReadParamFromFile(iniParms->IniFileName, vparamName, evals) != 0) return -1;
	ret = getEnumVal(&iniParms->DebugParms, vparamName, evals, oparamVal);
	free(vparamName);
	return ret;
}

//-- array value (int[], double[], char**, enum
__declspec(dllexport) int __stdcall getParam(tForecastParms* iniParms, char* paramName, int** oparamVal) {
	char* vparamName = _strdup(paramName); UpperCase(vparamName);
	//-- TODO: look in command-line parameters first
	int ret = ReadParamFromFile(iniParms->IniFileName, vparamName, oparamVal);
	free(vparamName); return ret;
}
__declspec(dllexport) int __stdcall getParam(tForecastParms* iniParms, char* paramName, double** oparamVal) {
	char* vparamName = _strdup(paramName); UpperCase(vparamName);
	//-- TODO: look in command-line parameters first
	int ret = ReadParamFromFile(iniParms->IniFileName, vparamName, oparamVal);
	free(vparamName); return ret;
}
__declspec(dllexport) int __stdcall getParam(tForecastParms* iniParms, char* paramName, char*** oparamVal) {
	char* vparamName = _strdup(paramName); UpperCase(vparamName);
	//-- TODO: look in command-line parameters first
	int ret = ReadParamFromFile(iniParms->IniFileName, vparamName, oparamVal);
	free(vparamName); return ret;
}
__declspec(dllexport) int __stdcall getParam(tForecastParms* iniParms, char* paramName, int** oparamVal, bool isenum) {
	char* vparamName = _strdup(paramName); UpperCase(vparamName);
	char pname[100]; strcpy(pname, vparamName);
	char** carr = MallocArray<char>(100, 100);
	int ret;
	int elemCnt = ReadParamFromFile(iniParms->IniFileName, pname, &carr);
	if (elemCnt < 0) return -1;
	for (int i = 0; i < elemCnt; i++) {
		ret = getEnumVal(&iniParms->DebugParms, pname, carr[i], &(*oparamVal)[i]);
		if (ret<0) break;
	}
	FreeArray(100, 100, carr);
	free(vparamName);
	return (ret<0)?ret:elemCnt;
}

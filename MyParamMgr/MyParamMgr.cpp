#include <MyParamMgr.h>

//============ SINGLE-VALUE VERSIONS ===============
//==================================================

//=============== ARRAY VERSIONS ===================
//==================================================

//================================================== COMMAND-LINE PARAMETERS PROCESSING ==================================================
int CLFail(int p) {
	printf("Command Line Fail on parameter %d !\nExiting...\n", p);
	printf("Press any key..."); getchar();;
	return -1;
}
EXPORT int CLProcess(int argc, char* argv[], tParamMgr* iniParms) {
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
//=============================================================================================================================================

//-- single value (int, double, char*, enum)
EXPORT int getParam(tParamMgr* iniParms, char* paramName, int* oparamVal) {
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
EXPORT int getParam(tParamMgr* iniParms, char* paramName, double* oparamVal) {
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
EXPORT int getParam(tParamMgr* iniParms, char* paramName, char* oparamVal) {
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
EXPORT int getParam(tParamMgr* iniParms, char* paramName, int* oparamVal, bool isenum) {
	char* vparamName = _strdup(paramName); UpperCase(vparamName);
	char evals[100];
	int ret = 0;
	for (int p = 1; p < iniParms->CLparamCount; p++) {
		if (strcmp(iniParms->CLparamName[p], vparamName) == 0) {
			strcpy(evals, iniParms->CLparamVal[p]);
			ret = getEnumVal(vparamName, evals, oparamVal);
			free(vparamName);
			return ret;
		}
	}
	if (ReadParamFromFile(iniParms->IniFileName, vparamName, evals) != 0) return -1;
	ret = getEnumVal(vparamName, evals, oparamVal);
	free(vparamName);
	return ret;
}
EXPORT int ReadParamFromFile(char* pFileName, char* pParamName, int* oParamValue) {
	FILE* ParamFile;
	char vParamName[1000];
	char vParamValue[1000];

	ParamFile = fopen(pFileName, "r");
	if (ParamFile == NULL) {
		printf("ReadParamFromFile() could not open Parameter file: %s . Exiting.\n", pFileName);
		printf("Press any key..."); getchar();
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
	printf("Press any key..."); getchar();
	return -1;
}
EXPORT int ReadParamFromFile(char* pFileName, char* pParamName, double* oParamValue) {
	FILE* ParamFile;
	char vParamName[1000];
	char vParamValue[1000];

	ParamFile = fopen(pFileName, "r");
	if (ParamFile == NULL) {
		printf("ReadParamFromFile() could not open Parameter file: %s . Exiting.\n", pFileName);
		printf("Press any key..."); getchar();
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
	printf("Press any key..."); getchar();
	return -1;
}
EXPORT int ReadParamFromFile(char* pFileName, char* pParamName, char* oParamValue) {
	FILE* ParamFile;
	char vParamName[1000];
	char vParamValue[1000];

	ParamFile = fopen(pFileName, "r");
	if (ParamFile == NULL) {
		printf("ReadParamFromFile() could not open Parameter file: %s . Exiting.\n", pFileName);
		printf("Press any key..."); getchar();
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
	printf("Press any key..."); getchar();
	fclose(ParamFile);
	return -1;
}

//-- array value (int[], double[], char**, enum
EXPORT int getParam(tParamMgr* iniParms, char* paramName, int** oparamVal) {
	char* vparamName = _strdup(paramName); UpperCase(vparamName);
	//-- TODO: look in command-line parameters first
	int ret = ReadParamFromFile(iniParms->IniFileName, vparamName, oparamVal);
	free(vparamName); return ret;
}
EXPORT int getParam(tParamMgr* iniParms, char* paramName, double** oparamVal) {
	char* vparamName = _strdup(paramName); UpperCase(vparamName);
	//-- TODO: look in command-line parameters first
	int ret = ReadParamFromFile(iniParms->IniFileName, vparamName, oparamVal);
	free(vparamName); return ret;
}
EXPORT int getParam(tParamMgr* iniParms, char* paramName, char*** oparamVal) {
	char* vparamName = _strdup(paramName); UpperCase(vparamName);
	//-- TODO: look in command-line parameters first
	int ret = ReadParamFromFile(iniParms->IniFileName, vparamName, oparamVal);
	free(vparamName); return ret;
}
EXPORT int getParam(tParamMgr* iniParms, char* paramName, int** oparamVal, bool isenum) {
	char* vparamName = _strdup(paramName); UpperCase(vparamName);
	char pname[100]; strcpy(pname, vparamName);
	char** carr = MallocArray<char>(100, 100);
	int ret;
	char evals[100];
	int elemCnt;
	//--
	for (int p = 1; p < iniParms->CLparamCount; p++) {
		if (strcmp(iniParms->CLparamName[p], vparamName) == 0) {
			strcpy(evals, iniParms->CLparamVal[p]);
			elemCnt = cslToArray(evals, ',', carr);
			for (int i = 0; i < elemCnt; i++) {
				ret = getEnumVal(pname, carr[i], &(*oparamVal)[i]);
				if (ret<0) break;
			}
			FreeArray(100, 100, carr);
			free(vparamName);
			return (ret<0) ? ret : elemCnt;
		}
	}
	//--
	elemCnt = ReadParamFromFile(iniParms->IniFileName, pname, &carr);
	if (elemCnt < 0) return -1;
	for (int i = 0; i < elemCnt; i++) {
		ret = getEnumVal(pname, carr[i], &(*oparamVal)[i]);
		if (ret<0) break;
	}
	FreeArray(100, 100, carr);
	free(vparamName);
	return (ret<0) ? ret : elemCnt;
}
EXPORT int ReadParamFromFile(char* pFileName, char* pParamName, int** oParamValue) {
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
EXPORT int ReadParamFromFile(char* pFileName, char* pParamName, double** oParamValue) {
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
EXPORT int ReadParamFromFile(char* pFileName, char* pParamName, char*** oParamValue) {
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

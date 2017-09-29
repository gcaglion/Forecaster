#pragma once
#include <MyUtils.h>
#include <MyEnums.h>

typedef struct sParamMgr {
	//-- ini file and command-line overrides
	char IniFileName[MAX_PATH];
	int  CLparamCount;
	char CLparamName[1000][100];
	char CLparamVal[1000][100];
} tParamMgr;



#undef EXPORT
#define EXPORT __declspec(dllexport)

//-- command-line parameters processing
int CLFail(int p);
EXPORT int	CLProcess(int argc, char* argv[], tParamMgr* iniParms);

//-- single value (int, double, char*, enum)
EXPORT int ReadParamFromFile(char* pFileName, char* pParamName, int* oParamValue);
EXPORT int ReadParamFromFile(char* pFileName, char* pParamName, double* oParamValue);
EXPORT int ReadParamFromFile(char* pFileName, char* pParamName, char* oParamValue);
EXPORT int getParam(tParamMgr* iniParms, char* paramName, int* oparamVal);
EXPORT int getParam(tParamMgr* iniParms, char* paramName, double* oparamVal);
EXPORT int getParam(tParamMgr* iniParms, char* paramName, char* oparamVal);
EXPORT int getParam(tParamMgr* iniParms, char* paramName, int* oparamVal, bool isenum);

//-- array value (int[], double[], char**, enum
EXPORT int ReadParamFromFile(char* pFileName, char* pParamName, int** oParamValue);
EXPORT int ReadParamFromFile(char* pFileName, char* pParamName, double** oParamValue);
EXPORT int ReadParamFromFile(char* pFileName, char* pParamName, char*** oParamValue);
EXPORT int getParam(tParamMgr* iniParms, char* paramName, int** oparamVal);
EXPORT int getParam(tParamMgr* iniParms, char* paramName, double** oparamVal);
EXPORT int getParam(tParamMgr* iniParms, char* paramName, char*** oparamVal);
EXPORT int getParam(tParamMgr* iniParms, char* paramName, int** oparamVal, bool isenum);

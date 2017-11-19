#pragma once
#include <MyUtils.h>
#include <DataShape.h>
#include <FXData.h>
#include <FileData.h>
#include <Tester.h>
#include <MyEngines.h>
#include <MyNN.h>
#include <TSF.h>
#include <MySOM.h>
#include <MySVM.h>

typedef struct sParamMgr {
	//-- ini file and command-line overrides
	char IniFileName[MAX_PATH];
	int  CLparamCount;
	char CLparamName[1000][100];
	char CLparamVal[1000][100];
} tParamMgr;




#define MAXPARAMDESCLEN 20	// Max length for comma-separated lists of descriptions
#define ARRAY_PARAMETER_MAX_LEN	100
#define enumlist true

//-- Forecaster Actions
#define TRAIN_SAVE_RUN 0
#define ADD_SAMPLES 1
#define JUST_RUN 2

//-- DataFile field separators
#define COMMA ','
#define TAB '\t'
#define SPACE ' '

#undef EXPORT
#define EXPORT __declspec(dllexport)

//-- command-line parameters processing
int CLFail(int p);
EXPORT int	CLProcess(int argc, char* argv[], tParamMgr* iniParms);

//-- enumerator-type values decoder
EXPORT int getEnumVal(char* edesc, char* eVal, int* oVal);

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


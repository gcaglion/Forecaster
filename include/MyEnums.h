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

#define MAXPARAMDESCLEN 20	// Max length for comma-separated lists of descriptions
#define ARRAY_PARAMETER_MAX_LEN	100

#define enumlist true

#define PARAM_TYPE_INT		0
#define PARAM_TYPE_DOUBLE	1
#define PARAM_TYPE_STRING	2
#define PARAM_TYPE_ENUM		3
#define PARAM_TYPE_INTp		4
#define PARAM_TYPE_DOUBLEp	5
#define PARAM_TYPE_STRINGp	6
#define PARAM_TYPE_ENUMp	7

//-- Data Tranformations
#define DT_NONE		 0
#define DT_DELTA	 1
#define DT_LOG		 2
#define DT_DELTALOG	 3

//-- DataFile field separators
#define COMMA ','
#define TAB '\t'
#define SPACE ' '

typedef struct sForecastParms {
	//-- ini file and command-line overrides
	char IniFileName[MAX_PATH];
	int  CLparamCount;
	char CLparamName[1000][100];
	char CLparamVal[1000][100];

	int SimulationLength;
	char SimulationStart[12 + 1];
	int DoTraining;
	int HaveFutureData;

	tEngineDef EngineParms;
	tDebugInfo DebugParms;
	tDataShape DataParms;
	tFXData FXDBInfo;
	tFileData DataSourceFileInfo;
	tEngineHandle SavedEngine;
} tForecastParms;

__declspec(dllexport) int __stdcall getEnumVal(char* edesc, char* eval);
__declspec(dllexport) int __stdcall	ReadParamFromFile(char* pFileName, char* pParamName, int* oParamValue);
__declspec(dllexport) int __stdcall	ReadParamFromFile(char* pFileName, char* pParamName, double* oParamValue);
__declspec(dllexport) int __stdcall	ReadParamFromFile(char* pFileName, char* pParamName, char* oParamValue);

__declspec(dllexport) int __stdcall	ReadParamFromFile(char* pFileName, char* pParamName, int** oParamValue);
__declspec(dllexport) int __stdcall	ReadParamFromFile(char* pFileName, char* pParamName, double** oParamValue);
__declspec(dllexport) int __stdcall	ReadParamFromFile(char* pFileName, char* pParamName, char*** oParamValue);



//-- command-line parameters processing
int CLFail(int p);
__declspec(dllexport) int __stdcall	CLProcess(int argc, char* argv[], tForecastParms* iniParms);

//-- single value (int, double, char*, enum)
__declspec(dllexport) int __stdcall getParam(tForecastParms* iniParms, char* paramName, int* oparamVal);
__declspec(dllexport) int __stdcall getParam(tForecastParms* iniParms, char* paramName, double* oparamVal);
__declspec(dllexport) int __stdcall getParam(tForecastParms* iniParms, char* paramName, char* oparamVal);
__declspec(dllexport) int __stdcall getParam(tForecastParms* iniParms, char* paramName, int* oparamVal, bool isenum);

//-- array value (int[], double[], char**, enum
__declspec(dllexport) int __stdcall getParam(tForecastParms* iniParms, char* paramName, int** oparamVal);
__declspec(dllexport) int __stdcall getParam(tForecastParms* iniParms, char* paramName, double** oparamVal);
__declspec(dllexport) int __stdcall getParam(tForecastParms* iniParms, char* paramName, char*** oparamVal);
__declspec(dllexport) int __stdcall getParam(tForecastParms* iniParms, char* paramName, int** oparamVal, bool isenum);

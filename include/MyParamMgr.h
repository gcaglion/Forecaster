#pragma once

#include <MyUtils.h>
#include <MyEngines.h>
#include <MyNN.h>
#include <MyGA.h>
#include <MySVM.h>
#include <MySOM.h>
#include <DataShape.h>
#include <MyDebug.h>
#include <FileData.h>
#include <FXData.h>
#include <MyTimeSeries.h>
#include <Client.h>

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

#define FPALL 0	// process All parameters
#define FPCLI 1	// process Client parameters only
#define FPSRV 2	// process Server parameters only

class cParamsSource {
public:
	tClientParms* ClientParms;
	tDebugInfo* DebugParms;
	tDBConnection* ResultsDB;
	tDataShape* DataParms;
	tDBConnection* FXDB;
	tFXData* FXDataInfo;
	tFileData* DataSourceFileInfo;
	cEngine* Engine;
	tEngineHandle* SavedEngine;

	//-- constructor / destructor
	EXPORT cParamsSource(int argc, char* argv[]);
	EXPORT ~cParamsSource();

	EXPORT int Process(int section);
	EXPORT int Process_DebugParms();
	EXPORT int Process_DataSourceParms();
	EXPORT int Process_DataShapeParms();
	EXPORT int Process_ClientParms();

	//-- single value (int, double, char*, enum)
	EXPORT int getParam(char* paramName, int* oparamVal);
	EXPORT int getParam(char* paramName, double* oparamVal);
	EXPORT int getParam(char* paramName, char* oparamVal);
	EXPORT int getParam(char* paramName, int* oparamVal, bool isenum);
	//-- array value (int[], double[], char**, enum
	EXPORT int getParam(char* paramName, int** oparamVal);
	EXPORT int getParam(char* paramName, double** oparamVal);
	EXPORT int getParam(char* paramName, char*** oparamVal);
	EXPORT int getParam(char* paramName, int** oparamVal, bool isenum);

private:
	char IniFileName[MAX_PATH];
	int  CLparamCount;
	char CLparamName[1000][100];
	char CLparamVal[1000][100];

	int getEnumVal(char* edesc, char* eval);
	int	ReadParamFromFile(char* pFileName, char* pParamName, int* oParamValue);
	int	ReadParamFromFile(char* pFileName, char* pParamName, double* oParamValue);
	int	ReadParamFromFile(char* pFileName, char* pParamName, char* oParamValue);

	int	ReadParamFromFile(char* pFileName, char* pParamName, int** oParamValue);
	int	ReadParamFromFile(char* pFileName, char* pParamName, double** oParamValue);
	int	ReadParamFromFile(char* pFileName, char* pParamName, char*** oParamValue);

	//-- command-line parameters processing
	int CLFail(int p);
	int	CLProcess(int argc, char* argv[]);


} ;

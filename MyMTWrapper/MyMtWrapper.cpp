#include <MyForecast.h>
#include <MyOraUtils.h>

extern "C" __declspec(dllexport) int  MTOraConnect(int paramCnt, char* paramOverride, char* oCtxS) {
	
	tForecastParms fParms;
	char** param = (char**)malloc(ARRAY_PARAMETER_MAX_LEN * sizeof(char*)); for (int i = 0; i<ARRAY_PARAMETER_MAX_LEN; i++) param[i] = (char*)malloc(256);

	//-- a. set overrides from full string in paramOverride parameter
	paramCnt = cslToArray(paramOverride, ' ', param);
	if (CLProcess(paramCnt, param, &fParms) <0) return -4;
	//-- b. process ini file
	if (ForecastParamLoader(&fParms) <0) return -3;

	if( OraConnect(&fParms.DebugParms, fParms.DebugParms.DebugDB) !=0) return -1;

	sprintf(oCtxS, "%p", fParms.DebugParms.DebugDB->DBCtx);

/*	FILE* kfd = fopen("C:/temp/MTOraConnect.log", "w");
	fprintf(kfd, "DBCtx=%p\noCtxS=---%p---\n", fParms.DebugParms.DebugDB->DBCtx, oCtxS);
	fclose(kfd);
*/	

	for (int i = 0; i<ARRAY_PARAMETER_MAX_LEN; i++) free(param[i]);
	free(param);
	return 0;
}
extern "C" __declspec(dllexport) void MTOraDisconnect(int paramCnt, char* paramOverride, char* pLogDBCtxS, int pCommit) {
	void* ctx = nullptr;
	sscanf(pLogDBCtxS, "%p", &ctx);
	OraDisconnect(ctx, pCommit);
}
extern "C" __declspec(dllexport) void MTOraCommit(int paramCnt, char* paramOverride, char* pLogDBCtxS) {
	void* ctx = nullptr;
	sscanf(pLogDBCtxS, "%p", &ctx);
	OraCommit(ctx);
}
extern "C" __declspec(dllexport) int  MTSaveClientInfo(int paramCnt, char* paramOverride, char* pDBCtx, char* pCurrentBar, int pDoTraining, int pDoRun) {
	//=== We have to duplicate parameters handling, just to read debug parameters === 

	tForecastParms fParms;
	char** param = (char**)malloc(ARRAY_PARAMETER_MAX_LEN * sizeof(char*)); for (int i = 0; i<ARRAY_PARAMETER_MAX_LEN; i++) param[i] = (char*)malloc(256);
	char vCurrentBar[20+1];
	int ret = 0;

	//-- a. set overrides from full string in paramOverride parameter
	paramCnt = cslToArray(paramOverride, ' ', param);
	if (CLProcess(paramCnt, param, &fParms) <0) return -3;
	//-- b. process ini file
	if (ForecastParamLoader(&fParms) <0) return -2;

	//-- set DBCtx
	sscanf(pDBCtx, "%p", &fParms.DebugParms.DebugDB->DBCtx);

	//-- convert Bar date format
	int j = 0;
	for (unsigned int i = 0; i<strlen(pCurrentBar); i++) {
		if (pCurrentBar[i]!=':' && pCurrentBar[i]!='.') {
			vCurrentBar[j] = pCurrentBar[i];
			j++;
		}
	}
	vCurrentBar[j] = '\0';

	ret = SaveClientInfo(&fParms.DebugParms, GetCurrentProcessId(), "MetaTrader", 1, vCurrentBar, 0, pDoTraining, pDoRun);

	for (int i = 0; i<ARRAY_PARAMETER_MAX_LEN; i++) free(param[i]);
	free(param);
	return ret;
}
extern "C" __declspec(dllexport) int  MTgetForecast(
	int paramCnt, char* paramOverride,
	char* pLogDBCtxS,
	int progId,	//-- equivalent to Tester.cpp's testid. needed to avoid duplication in DataParms
	double* pHistoryDataH, double pHistoryBaseValH,
	double* pHistoryDataL, double pHistoryBaseValL,
	double* pHistoryBW,
	double* pValidationDataH, double pValidationBaseValH,
	double* pValidationDataL, double pValidationBaseValL,
	double* pFutureDataH,
	double* pFutureDataL,
	double* pFutureBW,
	double* oPredictedDataH, double* oPredictedDataL
) {
	int ret;
	//-- High and Low arrays are put together in double arrays, with High in 0, Low in 1. BarWidth is duplicated
	double* vHistoryData[2];
	double  vHistoryBaseVal[2];
	double* vHistoryBW[2];
	double* vValidationData[2];
	double  vValidationBaseVal[2];
	double* vFutureData[2];
	double* vFutureBW[2];
	double* vPredictedData[2];
	//--
	vHistoryData[0] = pHistoryDataH;				vHistoryData[1] = pHistoryDataL;
	vHistoryBaseVal[0] = pHistoryBaseValH;			vHistoryBaseVal[1] = pHistoryBaseValL;
	vHistoryBW[0] = pHistoryBW;						vHistoryBW[1] = pHistoryBW;
	vValidationData[0] = pValidationDataH;			vValidationData[1] = pValidationDataL;
	vValidationBaseVal[0] = pValidationBaseValH;	vValidationBaseVal[1] = pValidationBaseValL;
	vFutureData[0] = pFutureDataH;					vFutureData[1] = pFutureDataL;
	vFutureBW[0] = pFutureBW;						vFutureBW[1] = pFutureBW;
	vPredictedData[0] = oPredictedDataH;			vPredictedData[1] = oPredictedDataL;

	// Forecasting Parameters initialization. 
	tForecastParms fParms;
	char** param = (char**)malloc(ARRAY_PARAMETER_MAX_LEN * sizeof(char*)); for (int i = 0; i<ARRAY_PARAMETER_MAX_LEN; i++) param[i] = (char*)malloc(256);

	//-- a. set overrides from full string in paramOverride parameter
	paramCnt = cslToArray(paramOverride, ' ', param);
	if (CLProcess(paramCnt, param, &fParms) <0) return -3;
	//-- b. process ini file
	if (ForecastParamLoader(&fParms) <0) return -2;

	//-- set DBCtx
	sscanf(pLogDBCtxS, "%p", &fParms.DebugParms.DebugDB->DBCtx);

	//DumpArrayD(fParms.DataParms.HistoryLen, vHistoryData[0], "c:/temp/hd0.txt");
	//DumpArrayD(fParms.DataParms.HistoryLen, vHistoryData[1], "c:/temp/hd1.txt");

	LogWrite(&fParms.DebugParms, LOG_INFO, "BEFORE: oPredictedDataH[0]=%f \t oPredictedDataL[0]=%f \t vPredictedData[0][0]=%f \t vPredictedData[1][0]=%f\n", 4, oPredictedDataH[0], oPredictedDataL[0], vPredictedData[0][0], vPredictedData[1][0]);
	ret= getForecast(paramCnt, param, fParms.DebugParms.DebugDB->DBCtx, progId, vHistoryData, vHistoryBaseVal, vHistoryBW, vValidationData, vValidationBaseVal, 0, vFutureData, vFutureBW, vPredictedData);
	LogWrite(&fParms.DebugParms, LOG_INFO, "AFTER : oPredictedDataH[0]=%f \t oPredictedDataL[0]=%f \t vPredictedData[0][0]=%f \t vPredictedData[1][0]=%f\n", 4, oPredictedDataH[0], oPredictedDataL[0], vPredictedData[0][0], vPredictedData[1][0]);

	for (int i = 0; i<ARRAY_PARAMETER_MAX_LEN; i++) free(param[i]);
	free(param);
	return ret;
}

/*
//-- parameters log
FILE* fp = fopen("C:/temp/MT4parms.txt", "w");
fprintf(fp, "%d\n%s\n", paramCnt, paramOverride);

//===
for (int p = 1; p<paramCnt; p++) fprintf(fp, "%d: %s = %s\n", p, fParms.CLparamName[p], fParms.CLparamVal[p]);
fclose(fp);
//===

*/

/*
FILE* f = fopen("c:/temp/sss.log", "w");
fprintf(f, "%d: %s\n", paramCnt, paramOverride);
fprintf(f, "%d\n", fParms.DebugParms.SaveNothing);

*/
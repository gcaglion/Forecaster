
#include <MyLogger.h>
#include <TSF.h>
#include <DataShape.h>
#include <FileData.h>

#define SOURCE_DATA_FROM_FXDB 0
#define SOURCE_DATA_FROM_FILE 1
#define SOURCE_DATA_FROM_MT   2

//-- Data Tranformations
#define DT_NONE		 0
#define DT_DELTA	 1
#define DT_LOG		 2
#define DT_DELTALOG	 3

#undef EXPORT
#define EXPORT __declspec(dllexport)

EXPORT int __stdcall LoadData_FXDB(tDebugInfo* DebugParms, tFXData* DBParms, int pHistoryLen, int pFutureLen, char* pDate0, int pValidationShift, int pDatasetCount, double** oHistoryData, double** oHistoryBarW, double** oValidationData, double** oFutureData, double** oFutureBarW, double** oWholeData, double** oWholeBarW, double* oPrevValH, double* oPrevValV, double* oPrevBarW);
EXPORT int __stdcall LoadData_CSV(tDebugInfo* DebugParms, tFileData* pDataFile, int pHistoryLen, int pFutureLen, char* pDate0, int pValidationShift, int pDatasetCount, double** oHistoryData, double** oHistoryBarW, double** oValidationData, double** oFutureData, double** oFutureBarW, double** oWholeData, double** oWholeBarW, double* oPrevValH, double* oPrevValV, double* oPrevBarW);
EXPORT int __stdcall GetDates_CSV(tDebugInfo* DebugParms, tFileData* pDataFile, char* StartDate, int DatesCount, char** oDate);
EXPORT int __stdcall GetDates_FXDB(tDebugInfo* DebugParms, tFXData* SourceParms, char* StartDate, int DatesCount, char** oDate);
EXPORT int __stdcall LoadHistoryData(int pHistoryLen, char* pDate0, int pBarDataType, double* oHistoryData, tFXData* DBParms, tDebugInfo* DebugParms);
//EXPORT void __stdcall DataTransform(int Transformation, int iFromItem, int iToItem, double* InData, double* OutData, double* oMinVal, double pBaseVal);
//EXPORT void __stdcall DataUnTransform(int Transformation, int iFromItem, int iToItem, double* InData, double* OutData, double* ActualData, double oMinVal, double pBaseVal);
// newest version -------------------------------------------------------------------------------------------------------------------
EXPORT void __stdcall dataTransform(int dt, int dlen, double* idata, double baseVal, double* oMinVal, double* odata);
EXPORT void __stdcall dataUnTransform(int dt, int from_i, int to_i, double* idata, double baseVal, double iMinVal, double* iActual, double* odata);
//-----------------------------------------------------------------------------------------------------------------------------------
EXPORT void __stdcall TSfromSamples(int sampleCnt, int sampleLen, double** iSample, double* oTS);
EXPORT int __stdcall FXDataCompact(char* INfilename, int INtimeframe, char* OUTfilename, int OUTtimeframe);

//-- Timeseries Statistical Features
EXPORT double __stdcall TSMean(int VLen, double* V);
EXPORT double __stdcall TSMeanAbsoluteDeviation(int VLen, double* V);
EXPORT double __stdcall TSVariance(int VLen, double* V);
EXPORT double __stdcall TSSkewness(int VLen, double* V);
EXPORT double __stdcall TSKurtosis(int VLen, double* V);
EXPORT double __stdcall TSTurningPoints(int VLen, double* V);
EXPORT double __stdcall TSShannonEntropy(int VLen, double* V);
EXPORT double __stdcall TSHistoricalVolatility(int VLen, double* V);
EXPORT void   __stdcall CalcTSF(int TSFcnt, int* TSFid, tDataShape* pDataParms, int pTSLen, double* pTS, double* pTSF);

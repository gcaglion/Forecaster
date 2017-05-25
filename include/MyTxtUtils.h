#pragma once

#include <ExportDef.h>
#include <MyDebug.h>
#include <FileData.h>
#include <MyUtils.h>

EXPORT int Txt_GetDates(tDebugInfo* DebugParms, tFileData* pDataFile, char* StartDate, int pDatesCount, char** oDate);
EXPORT int Txt_LoadData(tDebugInfo* DebugParms, tFileData* pDataFile, int pHistoryLen, int pFutureLen, char* pDate0, int pValidationShift, int pDatasetCount, double** oHistoryData, double** oHistoryBarW, double** oValidationData, double** oFutureData, double** oFutureBarW, double** oWholeData, double** oWholeBarW);

EXPORT int Txt_LoadDataParms(tDebugInfo* DebugParms, int pid, int* oHistoryLen, int* oSampleLen, int* oSampleCount, int* oPRedictionLen, int* oDataTransformation, double* oWiggleRoom);
EXPORT int Txt_LoadEngineParms(tDebugInfo* DebugParms, int pid, int* oEngineType, int* oLayersCount, int* oDecompLevel, char** oWaveletType);

//-- Load CoreParms(s)
EXPORT int Txt_GetCoreThreadId(tDebugInfo* DebugParms, int pid, int testid, int DatasetId, int LayerId, int CoreId);
EXPORT int Txt_LoadCoreParms_NN(tDebugInfo* DebugParms, int pid, int tid,
	int* oInputCount, int* oOutputCount, int* oUseContext, int* oMaxEpochs, int* oBP_Algo, int* oActivationFunction,
	char* oLevelRatioS[256],
	double* oLearningRate, double* oLearningMomentum, double* oHCPBeta, double* oTargetMSE);
EXPORT int Txt_LoadCoreParms_SOM(tDebugInfo* DebugParms, int pid, int tid,
	int* oInputCount, int* oOutputCount, int* oMaxEpochs, int* oTDFunction, int* oLRFunction,
	double* oBaseTD, double* oBaseLR);
EXPORT int Txt_LoadCoreParms_SVM(tDebugInfo* DebugParms, int pid, int tid,
	int* oInputCount, int* oMaxEpochs, int* osvmIterToShrink, int* oKernelType, int* oPolyDegree, int* oKernelCacheSize,
	double* oC, double* oEpsilon, double* oRBFGamma, double* oCoefLin, double* oCoefConst);

//-- Load Core Image
EXPORT int Txt_LoadCoreImage_NN(tDebugInfo* DebugParms, int pid, int tid, double*** oFinalW);
EXPORT int Txt_LoadCoreImage_SOM(tDebugInfo* DebugParms, int pid, int tid, double** oSOMWeight);
EXPORT int Txt_LoadCoreImage_SVM(tDebugInfo* DebugParms, int pid, int tid, double** oSVMWeight);

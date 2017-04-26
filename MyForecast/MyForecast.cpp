#include <vld.h>

#include "stdafx.h"

#define HD 0
#define VD 1

typedef struct {
	tDebugInfo* DebugParms;
	tEngineDef* EngineParms;
	int LayerId; int CoreId; int DatasetId;
	int CorePos; int TotCores; HANDLE ScreenMutex;
	int SampleCount; double** SampleT; double** TargetT; double** SampleV; double** TargetV;
	tEngineHandle TrainInfo;
	int TrainSuccess;
	int ActualEpochs;
} tTrainParams;

void freeCoreParms(tForecastParms* ioParms) {
	switch (ioParms->EngineParms.EngineType) {
	case ENGINE_WNN:
		free(ioParms->EngineParms.EngineArch);
		for (int c = 0; c < ioParms->EngineParms.CoresCount[1]; c++) free(ioParms->EngineParms.Core[1][c].CoreSpecs);
		free(ioParms->EngineParms.Core[1]);
		break;
	case ENGINE_XIE:
		free(ioParms->EngineParms.Core[1]->CoreSpecs);
		free(ioParms->EngineParms.Core[1]);
		break;
	default:
		break;
	}
	for (int c = 0; c < ioParms->EngineParms.CoresCount[0]; c++) free(ioParms->EngineParms.Core[0][c].CoreSpecs);
	FreeArray(1, 1, ioParms->EngineParms.Core);
	free(ioParms->EngineParms.CoresCount);
	//free(ioParms->EngineParms.Core[0]);
	//free(ioParms->EngineParms.Core);
}

void mallocCoreLogs(tForecastParms* ioParms){
	int l, c, d;
	for (l = 0; l < ioParms->EngineParms.LayersCount; l++) {
		for (c = 0; c < ioParms->EngineParms.CoresCount[l]; c++) {
			ioParms->EngineParms.Core[l][c].CoreLog = MallocArray<tCoreLog>(ioParms->DataParms.DatasetsCount);
			for (d = 0; d < ioParms->DataParms.DatasetsCount; d++) {
				//-- Engine-indipendent 
				ioParms->EngineParms.Core[l][c].CoreLog[d].MSEOutput = MallocArray<tLogMSE>(ioParms->EngineParms.Core[l][c].MSECount);
				ioParms->EngineParms.Core[l][c].CoreLog[d].RunOutput = MallocArray<tLogRUN>(ioParms->EngineParms.Core[l][c].RunCount);
				//-- NN-specific
				if (ioParms->EngineParms.Core[l][c].CoreType == ENGINE_NN) {
					setNNTopology((NN_Parms*)ioParms->EngineParms.Core[l][c].CoreSpecs);
					mallocNNLog(&ioParms->EngineParms.Core[l][c].CoreLog[d], ((NN_Parms*)ioParms->EngineParms.Core[l][c].CoreSpecs)->LevelsCount, ((NN_Parms*)ioParms->EngineParms.Core[l][c].CoreSpecs)->NodesCount, ioParms->EngineParms.Core[l][c].TimeStepsCount);
				}
				//-- GA-specific
				//-- SVM-specific is called from SVMTrain()
				//-- SOM-specific
			}
		}
	}
}
void freeCoreLogs(tForecastParms* ioParms){
	int l, c, d;
	for (l = 0; l < ioParms->EngineParms.LayersCount; l++) {
		for (c = 0; c < ioParms->EngineParms.CoresCount[l]; c++) {
			for (d = 0; d < ioParms->DataParms.DatasetsCount; d++) {
				//-- Engine-indipendent 
				free(ioParms->EngineParms.Core[l][c].CoreLog[d].MSEOutput);
				free(ioParms->EngineParms.Core[l][c].CoreLog[d].RunOutput);
				//-- NN-specific
				if (ioParms->EngineParms.Core[l][c].CoreType == ENGINE_NN) {
					freeNNLog(&ioParms->EngineParms.Core[l][c].CoreLog[d], ((NN_Parms*)ioParms->EngineParms.Core[l][c].CoreSpecs)->LevelsCount, ((NN_Parms*)ioParms->EngineParms.Core[l][c].CoreSpecs)->NodesCount, ioParms->EngineParms.Core[l][c].TimeStepsCount);
				}
				//-- GA-specific
				//-- SVM-specific
				if (ioParms->EngineParms.Core[l][c].CoreType == ENGINE_SVM) {
					freeSVMLog(&ioParms->EngineParms.Core[l][c].CoreLog[d], ioParms->EngineParms.Core[l][c].SampleLen);
				}
				//-- SOM-specific
			}
			free(ioParms->EngineParms.Core[l][c].CoreLog);
		}
	}
}

__declspec(dllexport) int  ForecastParamLoader(tForecastParms* ioParms) {
	int l, c;
	WNN_Arch* WNNArch;
	tCore* CoreInfo;	// generic core. used to set core counters
	NN_Parms* NNInfo;	// not malloced. just used as a shortcut inside engine case
	GA_Parms* GAInfo;
	SOM_Parms* SOMInfo;
	SVM_Parms* SVMInfo;

	//-- 1. set Engine Type
	if (getParam(ioParms, "Forecaster.Engine", &ioParms->EngineParms.EngineType, enumlist) < 0)	return -1;

	//-- 2. set LayersCount, CoresCount[], Core[][]
	switch (ioParms->EngineParms.EngineType) {
	case ENGINE_WNN:
		ioParms->EngineParms.EngineArch = new WNN_Arch;
		WNNArch = (WNN_Arch*)ioParms->EngineParms.EngineArch;
		if (getParam(ioParms, "WNNInfo.WaveletType", WNNArch->WaveletType) < 0)		return -1;
		if (getParam(ioParms, "WNNInfo.DecompLevel", &WNNArch->DecompLevel) < 0)	return -1;

		ioParms->EngineParms.LayersCount = 2;
		ioParms->EngineParms.CoresCount = MallocArray<int>(ioParms->EngineParms.LayersCount);
		ioParms->EngineParms.CoresCount[0] = WNNArch->DecompLevel + 1;
		ioParms->EngineParms.CoresCount[1] = 1;
		ioParms->EngineParms.Core = (tCore**)malloc(ioParms->EngineParms.LayersCount * sizeof(tCore*));
		ioParms->EngineParms.Core[0] = MallocArray<tCore>(WNNArch->DecompLevel + 1);
		ioParms->EngineParms.Core[1] = MallocArray<tCore>(1);

		break;
	case ENGINE_XIE:
		ioParms->EngineParms.LayersCount = 2;
		ioParms->EngineParms.CoresCount = MallocArray<int>(ioParms->EngineParms.LayersCount);
		ioParms->EngineParms.CoresCount[0] = 2;
		ioParms->EngineParms.CoresCount[1] = 1;
		ioParms->EngineParms.Core = (tCore**)malloc(ioParms->EngineParms.LayersCount * sizeof(tCore*));
		ioParms->EngineParms.Core[0] = MallocArray<tCore>(2);
		ioParms->EngineParms.Core[1] = MallocArray<tCore>(1);
		break;
	default:
		ioParms->EngineParms.LayersCount = 1;
		ioParms->EngineParms.CoresCount = MallocArray<int>(1);
		ioParms->EngineParms.CoresCount[0] = 1;
		ioParms->EngineParms.Core = (tCore**)malloc(ioParms->EngineParms.LayersCount * sizeof(tCore*));
		ioParms->EngineParms.Core[0] = MallocArray<tCore>(1);
		ioParms->EngineParms.Core[0]->CoreType = ioParms->EngineParms.EngineType;
		break;
	}

	//-- 3. set TotalCoresCount
	ioParms->EngineParms.TotalCoresCount = 0;
	for (int l = 0; l < ioParms->EngineParms.LayersCount; l++) {
		for (c = 0; c < ioParms->EngineParms.CoresCount[l]; c++) {
			ioParms->EngineParms.TotalCoresCount++;
		}
	}

	//-- 4. set TSFs
	int useTSF;
	//ioParms->EngineParms.TSFid = MallocArray<int>(MAX_TSFCOUNT);
	if (getParam(ioParms, "DataParms.UseTSFeatures", &useTSF) < 0) return -1;
	if (useTSF > 0) {
		ioParms->EngineParms.TSFcnt = getParam(ioParms, "DataParms.TSFeatures", &ioParms->EngineParms.TSFid, enumlist); if (ioParms->EngineParms.TSFcnt < 0) return -1;
	}
	else {
		ioParms->EngineParms.TSFcnt = 0;
	}

	//-- 5. set Forecaster Log Parameters
	if (getParam(ioParms, "Forecaster.DebugLevel", &ioParms->DebugParms.DebugLevel) < 0)				return -1;
	if (getParam(ioParms, "Forecaster.DebugFileName", ioParms->DebugParms.fName) < 0)					return -1;
	if (getParam(ioParms, "Forecaster.DebugFilePath", ioParms->DebugParms.fPath) < 0)					return -1;
	if (getParam(ioParms, "Forecaster.ThreadSafeLogging", &ioParms->DebugParms.ThreadSafeLogging) < 0)	return -1;

	//-- 6. DoTraining and HaveFutureData
	if (getParam(ioParms, "Forecaster.DoTraining", &ioParms->DoTraining) < 0)					return -1;
	if (getParam(ioParms, "Forecaster.HaveFutureData", &ioParms->HaveFutureData) < 0)			return -1;

	//-- 7. Tester Results (MSE,Run) destination DB parameters
	if (getParam(ioParms, "Results.SaveMSE", &ioParms->DebugParms.SaveMSE) < 0)					return -1;
	if (getParam(ioParms, "Results.SaveRUN", &ioParms->DebugParms.SaveRun) < 0)					return -1;
	if (getParam(ioParms, "Results.SaveInternals", &ioParms->DebugParms.SaveInternals) < 0)		return -1;
	if (getParam(ioParms, "Results.Destination", &ioParms->DebugParms.DebugDest, enumlist) < 0)	return -1;
	if (getParam(ioParms, "Results.DBUser", ioParms->DebugParms.DebugDB->DBUser) < 0)								return -1;
	if (getParam(ioParms, "Results.DBPassword", ioParms->DebugParms.DebugDB->DBPassword) < 0)						return -1;
	if (getParam(ioParms, "Results.DBConnString", ioParms->DebugParms.DebugDB->DBConnString) < 0)					return -1;
	ioParms->DebugParms.DebugDB->DBCtx = NULL;

	//-- 8. Tester Data Source parameters
	if (getParam(ioParms, "DataSource.SourceType", &ioParms->DataParms.DataSourceType, enumlist) < 0)		return -1;
	if (ioParms->DataParms.DataSourceType == SOURCE_DATA_FROM_FXDB) {
		if (getParam(ioParms, "DataSource.DBConn.DBUser", ioParms->FXDBInfo.FXDB->DBUser) < 0)				return -1;
		if (getParam(ioParms, "DataSource.DBConn.DBPassword", ioParms->FXDBInfo.FXDB->DBPassword) < 0)		return -1;
		if (getParam(ioParms, "DataSource.DBConn.DBConnString", ioParms->FXDBInfo.FXDB->DBConnString) < 0)	return -1;
		ioParms->FXDBInfo.FXDB->DBCtx = NULL;
		if (getParam(ioParms, "DataSource.Symbol", ioParms->FXDBInfo.Symbol) < 0)							return -1;
		if (getParam(ioParms, "DataSource.TimeFrame", ioParms->FXDBInfo.TimeFrame) < 0)						return -1;
		if (getParam(ioParms, "DataSource.IsFilled", &ioParms->FXDBInfo.IsFilled) < 0)						return -1;
		//-- bardatatypes, ioParms->DataParms->DatasetsCount...
		ioParms->DataParms.DatasetsCount = getParam(ioParms, "DataSource.BarDataTypes", &ioParms->FXDBInfo.BarDataType, enumlist); if (ioParms->DataParms.DatasetsCount < 0) return -1;
		ioParms->FXDBInfo.BarDataTypeCount = ioParms->DataParms.DatasetsCount;
		strcpy(ioParms->DataSourceFileInfo.FileName, "");
		ioParms->DataParms.DataSource = &ioParms->FXDBInfo;
	}
	else {
		if (getParam(ioParms, "DataSource.FileName", ioParms->DataSourceFileInfo.FileName) < 0)			return -1;
		ioParms->DataParms.DatasetsCount = getParam(ioParms, "DataSource.FileDatasets", &ioParms->DataSourceFileInfo.FileDataSet);
		strcpy(ioParms->FXDBInfo.Symbol, "");
		strcpy(ioParms->FXDBInfo.TimeFrame, "");
		ioParms->FXDBInfo.IsFilled = 0;
		ioParms->FXDBInfo.BarDataTypeCount = 0;
		ioParms->DataSourceFileInfo.FileDataSetsCount = ioParms->DataParms.DatasetsCount;
		ioParms->DataParms.DataSource = &ioParms->DataSourceFileInfo;
	}

	//-- 9. Tester Data Shape parameters 		
	if (ioParms->DoTraining == 1) {
		//-- If I'm Training, then I need these as input
		if (getParam(ioParms, "DataParms.HistoryLen", &ioParms->DataParms.HistoryLen) < 0)								return -1;
		if (getParam(ioParms, "DataParms.SampleLen", &ioParms->DataParms.SampleLen) < 0)								return -1;
		if (getParam(ioParms, "DataParms.PredictionLen", &ioParms->DataParms.PredictionLen) < 0)						return -1;
		if (getParam(ioParms, "DataParms.ValidationShift", &ioParms->DataParms.ValidationShift) < 0)					return -1;
		if (getParam(ioParms, "DataParms.DataTransformation", &ioParms->DataParms.DataTransformation, enumlist) < 0)	return -1;
		if (getParam(ioParms, "DataParms.WiggleRoom", &ioParms->DataParms.wiggleRoom) < 0)								return -1;
	}
	else {
		//-- If I'm using a saved engine, then I get these from DB
		ioParms->SavedEngine.EngineType = ioParms->EngineParms.EngineType;
		if (getParam(ioParms, "SavedEngine.ProcessId", &ioParms->SavedEngine.ProcessId) < 0)	return -1;
		if (getParam(ioParms, "SavedEngine.ThreadId", &ioParms->SavedEngine.ThreadId) < 0)	return -1;
		//if (LoadDataShape(&ioParms->DebugParms, &LogDBInfo, &ioParms->SavedEngine, &ioParms->DataParms) != 0)	return -1;
		ioParms->DataParms.ValidationShift = 0;
	}
	ioParms->DataParms.SampleCount = ioParms->DataParms.HistoryLen - ioParms->DataParms.SampleLen;

	//-- 10. Engine-specific parameters
	switch (ioParms->EngineParms.EngineType) {
	case ENGINE_NN:
		CoreInfo = &ioParms->EngineParms.Core[0][0];
		CoreInfo->CoreSpecs = new NN_Parms();
		NNInfo = (NN_Parms*)ioParms->EngineParms.Core[0][0].CoreSpecs;
		if (NNInfo->BP_Algo == BP_QING) ioParms->DataParms.PredictionLen = ioParms->DataParms.SampleLen;
		NNInfo->InputCount = ioParms->DataParms.SampleLen;
		NNInfo->OutputCount = ioParms->DataParms.PredictionLen;

		if (getParam(ioParms, "NNInfo.UseContext", &NNInfo->UseContext) < 0)							return -1;
		if (getParam(ioParms, "NNInfo.TrainingProtocol", &NNInfo->TrainingProtocol, enumlist) < 0)		return -1;
		if (getParam(ioParms, "NNInfo.BP_Algo", &NNInfo->BP_Algo, enumlist) < 0)						return -1;
		if (getParam(ioParms, "NNInfo.ActivationFunction", &NNInfo->ActivationFunction, enumlist) < 0)	return -1;
		if (getParam(ioParms, "NNInfo.StopAtDivergence", &NNInfo->StopAtDivergence) < 0)				return -1;
		if (getParam(ioParms, "NNInfo.MaxEpochs", &NNInfo->MaxEpochs) < 0)								return -1;
		if (getParam(ioParms, "NNInfo.LearningRate", &NNInfo->LearningRate) < 0)						return -1;
		if (getParam(ioParms, "NNInfo.LearningMomentum", &NNInfo->LearningMomentum) < 0)				return -1;
		if (getParam(ioParms, "NNInfo.TargetMSE", &NNInfo->TargetMSE) < 0)								return -1;
		if (getParam(ioParms, "NNInfo.HCPbeta", &NNInfo->HCPbeta) < 0)									return -1;
		if (getParam(ioParms, "NNInfo.mu", &NNInfo->mu) < 0)											return -1;
		if (getParam(ioParms, "NNInfo.LevelRatios", &NNInfo->LevelRatioS[0]) < 0)						return -1;

		CoreInfo->TimeStepsCount = NNInfo->MaxEpochs;
		CoreInfo->SampleLen = NNInfo->InputCount;
		CoreInfo->TargetLen = NNInfo->OutputCount;
		CoreInfo->MSECount = NNInfo->MaxEpochs;
		CoreInfo->RunCount = ioParms->DataParms.HistoryLen + ioParms->DataParms.PredictionLen;

		break;
	case ENGINE_GA:
		CoreInfo = &ioParms->EngineParms.Core[0][0];
		CoreInfo->CoreSpecs = new GA_Parms();
		CoreInfo->CoreLog = MallocArray<tCoreLog>(ioParms->DataParms.DatasetsCount);
		GAInfo = (GA_Parms*)ioParms->EngineParms.Core[0][0].CoreSpecs;
		GAInfo->InputCount = ioParms->DataParms.SampleLen;
		GAInfo->OutputCount = ioParms->DataParms.PredictionLen;
		if (getParam(ioParms, "GAInfo.SlidingFactor", &GAInfo->SlidingFactor) < 0)							return -1;
		if (getParam(ioParms, "GAInfo.Levels", &GAInfo->Levels) < 0)											return -1;
		if (getParam(ioParms, "GAInfo.PopulationSize", &GAInfo->PopulationSize) < 0)							return -1;
		if (getParam(ioParms, "GAInfo.MaxGenerations", &GAInfo->MaxGenerations) < 0)							return -1;
		if (getParam(ioParms, "GAInfo.TargetFitness", &GAInfo->TargetFitness) < 0)							return -1;
		if (getParam(ioParms, "GAInfo.FitnessSkewingFactor", &GAInfo->FitnessSkewingFactor) < 0)				return -1;
		if (getParam(ioParms, "GAInfo.FitnessThreshold", &GAInfo->FitnessThreshold) < 0)						return -1;
		if (getParam(ioParms, "GAInfo.CrossOverProbability", &GAInfo->CrossOverProbability) < 0)				return -1;
		if (getParam(ioParms, "GAInfo.MutationProbability", &GAInfo->MutationProbability) < 0)				return -1;
		if (getParam(ioParms, "GAInfo.CrossSelfRate", &GAInfo->CrossSelfRate) < 0)							return -1;
		if (getParam(ioParms, "GAInfo.RouletteMaxTries", &GAInfo->RouletteMaxTries) < 0)						return -1;
		if (getParam(ioParms, "GAInfo.ADF_Tree_FixedValues_Ratio", &GAInfo->ADF_Tree_FixedValues_Ratio) < 0)	return -1;
		if (getParam(ioParms, "GAInfo.ADF_Tree_DataPoints_Ratio", &GAInfo->ADF_Tree_DataPoints_Ratio) < 0)	return -1;
		if (getParam(ioParms, "GAInfo.ADF_Leaf_FixedValues_Ratio", &GAInfo->ADF_Leaf_FixedValues_Ratio) < 0)	return -1;
		if (getParam(ioParms, "GAInfo.MaxReRuns", &GAInfo->MaxReRuns) < 0)									return -1;
		if (getParam(ioParms, "GAInfo.BestChrPath", GAInfo->BestChrPath) < 0)								return -1;
		break;
	case ENGINE_SOM:
		CoreInfo = &ioParms->EngineParms.Core[0][0];
		CoreInfo->CoreSpecs = new SOM_Parms();
		SOMInfo = (SOM_Parms*)ioParms->EngineParms.Core[0][0].CoreSpecs;
		SOMInfo->InputCount = ioParms->DataParms.SampleLen;
		SOMInfo->OutputCount = ioParms->DataParms.PredictionLen;
		if (getParam(ioParms, "SOMInfo.OutputCount", &SOMInfo->OutputCount) < 0)			return -1;
		if (getParam(ioParms, "SOMInfo.OutputWidth", &SOMInfo->OutputWidth) < 0)			return -1;
		if (getParam(ioParms, "SOMInfo.MaxEpochs", &SOMInfo->MaxEpochs) < 0)				return -1;
		if (getParam(ioParms, "SOMInfo.TDFunction", &SOMInfo->TDFunction, enumlist) < 0)	return -1;
		if (getParam(ioParms, "SOMInfo.BaseLR", &SOMInfo->BaseLR) < 0)						return -1;
		if (getParam(ioParms, "SOMInfo.LRFunction", &SOMInfo->LRFunction, enumlist) < 0)	return -1;
		SOMInfo->BaseTD = SOMInfo->OutputCount;
		break;
	case ENGINE_SVM:
		CoreInfo = &ioParms->EngineParms.Core[0][0];
		CoreInfo->CoreSpecs = new SVM_Parms();
		SVMInfo = (SVM_Parms*)ioParms->EngineParms.Core[0][0].CoreSpecs;
		SVMInfo->InputCount = ioParms->DataParms.SampleLen;
		//SVMInfo->OutputCount = ioParms->DataParms.PredictionLen;
		if (getParam(ioParms, "SVMInfo.DebugLevel", &SVMInfo->DebugLevel) < 0)				return -1;
		if (getParam(ioParms, "SVMInfo.C", &SVMInfo->C) < 0)									return -1;
		if (getParam(ioParms, "SVMInfo.IterToShrink", &SVMInfo->svmIterToShrink) < 0)		return -1;
		if (getParam(ioParms, "SVMInfo.MaxEpochs", &SVMInfo->MaxEpochs) < 0)					return -1;
		if (getParam(ioParms, "SVMInfo.epsilon", &SVMInfo->epsilon) < 0)						return -1;
		if (getParam(ioParms, "SVMInfo.KernelType", &SVMInfo->KernelType, enumlist) < 0)		return -1;
		if (getParam(ioParms, "SVMInfo.PolyDegree", &SVMInfo->PolyDegree) < 0)				return -1;
		if (getParam(ioParms, "SVMInfo.RBFGamma", &SVMInfo->RBFGamma) < 0)					return -1;
		if (getParam(ioParms, "SVMInfo.CoefLin", &SVMInfo->CoefLin) < 0)						return -1;
		if (getParam(ioParms, "SVMInfo.CoefConst", &SVMInfo->CoefConst) < 0)					return -1;
		if (getParam(ioParms, "SVMInfo.KernelCacheSize", &SVMInfo->KernelCacheSize) < 0)		return -1;
		if (getParam(ioParms, "SVMInfo.CustomKernel", SVMInfo->CustomKernel) < 0)			return -1;
		//--
		if (getParam(ioParms, "SVMInfo.SlackNorm", &SVMInfo->SlackNorm, enumlist) < 0)				return -1;
		if (getParam(ioParms, "SVMInfo.RescalingMethod", &SVMInfo->RescalingMethod, enumlist) < 0)	return -1;
		if (getParam(ioParms, "SVMInfo.LossFunction", &SVMInfo->LossFunction, enumlist) < 0)			return -1;
		if (getParam(ioParms, "SVMInfo.LearningAlgo", &SVMInfo->LearningAlgo, enumlist) < 0)			return -1;
		if (getParam(ioParms, "SVMInfo.NewConstrEtrain", &SVMInfo->NewConstrEtrain) < 0)				return -1;
		if (getParam(ioParms, "SVMINfo.CCacheSize", &SVMInfo->CCacheSize) < 0)						return -1;
		if (getParam(ioParms, "SVMInfo.BatchSize", &SVMInfo->BatchSize) < 0)							return -1;
		if (getParam(ioParms, "SVMInfo.NewVarSinQP", &SVMInfo->NewVarSinQP) < 0)						return -1;

		CoreInfo->TimeStepsCount = SVMInfo->MaxEpochs;
		CoreInfo->SampleLen = SVMInfo->InputCount;
		CoreInfo->TargetLen = ioParms->DataParms.PredictionLen;
		CoreInfo->MSECount = SVMInfo->MaxEpochs;
		CoreInfo->RunCount = ioParms->DataParms.HistoryLen + ioParms->DataParms.PredictionLen;

		break;
	case ENGINE_WNN:
		l = 0;
		for (c = 0; c < ioParms->EngineParms.CoresCount[l]; c++) {
			CoreInfo = &ioParms->EngineParms.Core[l][c];
			CoreInfo->CoreSpecs = new NN_Parms();
			CoreInfo->CoreType = ENGINE_NN;
			NNInfo = (NN_Parms*)ioParms->EngineParms.Core[l][c].CoreSpecs;
			if (NNInfo->BP_Algo == BP_QING) ioParms->DataParms.PredictionLen = ioParms->DataParms.SampleLen;
			NNInfo->InputCount = ioParms->DataParms.SampleLen;
			NNInfo->OutputCount = ioParms->DataParms.PredictionLen;

			if (getParam(ioParms, "WNNInfo.L0.UseContext", &NNInfo->UseContext) <0)							return -1;
			if (getParam(ioParms, "WNNInfo.L0.TrainingProtocol", &NNInfo->TrainingProtocol, enumlist) <0)		return -1;
			if (getParam(ioParms, "WNNInfo.L0.BP_Algo", &NNInfo->BP_Algo, enumlist) <0)						return -1;
			if (getParam(ioParms, "WNNInfo.L0.ActivationFunction", &NNInfo->ActivationFunction, enumlist) <0)	return -1;
			if (getParam(ioParms, "WNNInfo.L0.StopAtDivergence", &NNInfo->StopAtDivergence) <0)				return -1;
			if (getParam(ioParms, "WNNInfo.L0.MaxEpochs", &NNInfo->MaxEpochs) <0)								return -1;
			if (getParam(ioParms, "WNNInfo.L0.LearningRate", &NNInfo->LearningRate) <0)						return -1;
			if (getParam(ioParms, "WNNInfo.L0.LearningMomentum", &NNInfo->LearningMomentum) <0)				return -1;
			if (getParam(ioParms, "WNNInfo.L0.TargetMSE", &NNInfo->TargetMSE) <0)								return -1;
			if (getParam(ioParms, "WNNInfo.L0.HCPbeta", &NNInfo->HCPbeta) <0)									return -1;
			if (getParam(ioParms, "WNNInfo.L0.mu", &NNInfo->mu) <0)											return -1;
			if (getParam(ioParms, "WNNInfo.L0.LevelRatios", &NNInfo->LevelRatioS[0]) <0)						return -1;

			CoreInfo->TimeStepsCount = NNInfo->MaxEpochs;
			CoreInfo->SampleLen = NNInfo->InputCount;
			CoreInfo->TargetLen = NNInfo->OutputCount;
			CoreInfo->MSECount = NNInfo->MaxEpochs;
			CoreInfo->RunCount = ioParms->DataParms.HistoryLen + ioParms->DataParms.PredictionLen;
		}

		l = 1;
		CoreInfo = &ioParms->EngineParms.Core[l][0];
		CoreInfo->CoreSpecs = new NN_Parms();
		CoreInfo->CoreType = ENGINE_NN;
		NNInfo = (NN_Parms*)ioParms->EngineParms.Core[l][0].CoreSpecs;
		NNInfo->InputCount = (ioParms->DataParms.PredictionLen*ioParms->EngineParms.CoresCount[0]) + ioParms->EngineParms.TSFcnt;
		NNInfo->OutputCount = ioParms->DataParms.PredictionLen;

		if (getParam(ioParms, "WNNInfo.L1.UseContext", &NNInfo->UseContext) <0)							return -1;
		if (getParam(ioParms, "WNNInfo.L1.TrainingProtocol", &NNInfo->TrainingProtocol, enumlist) <0)		return -1;
		if (getParam(ioParms, "WNNInfo.L1.BP_Algo", &NNInfo->BP_Algo, enumlist) <0)						return -1;
		if (getParam(ioParms, "WNNInfo.L1.ActivationFunction", &NNInfo->ActivationFunction, enumlist) <0)	return -1;
		if (getParam(ioParms, "WNNInfo.L1.StopAtDivergence", &NNInfo->StopAtDivergence) <0)				return -1;
		if (getParam(ioParms, "WNNInfo.L1.MaxEpochs", &NNInfo->MaxEpochs) <0)								return -1;
		if (getParam(ioParms, "WNNInfo.L1.LearningRate", &NNInfo->LearningRate) <0)						return -1;
		if (getParam(ioParms, "WNNInfo.L1.LearningMomentum", &NNInfo->LearningMomentum) <0)				return -1;
		if (getParam(ioParms, "WNNInfo.L1.TargetMSE", &NNInfo->TargetMSE) <0)								return -1;
		if (getParam(ioParms, "WNNInfo.L1.HCPbeta", &NNInfo->HCPbeta) <0)									return -1;
		if (getParam(ioParms, "WNNInfo.L1.mu", &NNInfo->mu) <0)											return -1;
		if (getParam(ioParms, "WNNInfo.L1.LevelRatios", &NNInfo->LevelRatioS[0]) <0)						return -1;

		CoreInfo->TimeStepsCount = NNInfo->MaxEpochs;
		CoreInfo->SampleLen = NNInfo->InputCount;
		CoreInfo->TargetLen = NNInfo->OutputCount;
		CoreInfo->MSECount = NNInfo->MaxEpochs;
		CoreInfo->RunCount = ioParms->DataParms.HistoryLen + ioParms->DataParms.PredictionLen;

		break;
	case ENGINE_XIE:
		CoreInfo = &ioParms->EngineParms.Core[0][0];
		CoreInfo->CoreSpecs = new SVM_Parms();
		CoreInfo->CoreType = ENGINE_SVM;
		SVMInfo = (SVM_Parms*)ioParms->EngineParms.Core[0][0].CoreSpecs;
		SVMInfo->InputCount = ioParms->DataParms.SampleLen;
		if (getParam(ioParms, "XIEInfo.SVM.DebugLevel", &SVMInfo->DebugLevel) < 0)				return -1;
		if (getParam(ioParms, "XIEInfo.SVM.C", &SVMInfo->C) < 0)									return -1;
		if (getParam(ioParms, "XIEInfo.SVM.IterToShrink", &SVMInfo->svmIterToShrink) < 0)		return -1;
		if (getParam(ioParms, "XIEInfo.SVM.MaxEpochs", &SVMInfo->MaxEpochs) < 0)					return -1;
		if (getParam(ioParms, "XIEInfo.SVM.epsilon", &SVMInfo->epsilon) < 0)						return -1;
		if (getParam(ioParms, "XIEInfo.SVM.KernelType", &SVMInfo->KernelType, enumlist) < 0)		return -1;
		if (getParam(ioParms, "XIEInfo.SVM.PolyDegree", &SVMInfo->PolyDegree) < 0)				return -1;
		if (getParam(ioParms, "XIEInfo.SVM.RBFGamma", &SVMInfo->RBFGamma) < 0)					return -1;
		if (getParam(ioParms, "XIEInfo.SVM.CoefLin", &SVMInfo->CoefLin) < 0)						return -1;
		if (getParam(ioParms, "XIEInfo.SVM.CoefConst", &SVMInfo->CoefConst) < 0)					return -1;
		if (getParam(ioParms, "XIEInfo.SVM.KernelCacheSize", &SVMInfo->KernelCacheSize) < 0)		return -1;
		if (getParam(ioParms, "XIEInfo.SVM.CustomKernel", SVMInfo->CustomKernel) < 0)			return -1;
		//--
		if (getParam(ioParms, "XIEInfo.SVM.SlackNorm", &SVMInfo->SlackNorm, enumlist) < 0)				return -1;
		if (getParam(ioParms, "XIEInfo.SVM.RescalingMethod", &SVMInfo->RescalingMethod, enumlist) < 0)	return -1;
		if (getParam(ioParms, "XIEInfo.SVM.LossFunction", &SVMInfo->LossFunction, enumlist) < 0)			return -1;
		if (getParam(ioParms, "XIEInfo.SVM.LearningAlgo", &SVMInfo->LearningAlgo, enumlist) < 0)			return -1;
		if (getParam(ioParms, "XIEInfo.SVM.NewConstrEtrain", &SVMInfo->NewConstrEtrain) < 0)				return -1;
		if (getParam(ioParms, "XIEInfo.SVM.CCacheSize", &SVMInfo->CCacheSize) < 0)						return -1;
		if (getParam(ioParms, "XIEInfo.SVM.BatchSize", &SVMInfo->BatchSize) < 0)							return -1;
		if (getParam(ioParms, "XIEInfo.SVM.NewVarSinQP", &SVMInfo->NewVarSinQP) < 0)						return -1;

		CoreInfo->TimeStepsCount = SVMInfo->MaxEpochs;
		CoreInfo->SampleLen = SVMInfo->InputCount;
		CoreInfo->TargetLen = ioParms->DataParms.PredictionLen;
		CoreInfo->MSECount = SVMInfo->MaxEpochs;
		CoreInfo->RunCount = ioParms->DataParms.HistoryLen + ioParms->DataParms.PredictionLen;

		CoreInfo = &ioParms->EngineParms.Core[0][1];
		CoreInfo->CoreSpecs = new NN_Parms();
		CoreInfo->CoreType = ENGINE_NN;
		CoreInfo->CoreLog = MallocArray<tCoreLog>(ioParms->DataParms.DatasetsCount);
		NNInfo = (NN_Parms*)ioParms->EngineParms.Core[0][1].CoreSpecs;
		if (NNInfo->BP_Algo == BP_QING) ioParms->DataParms.PredictionLen = ioParms->DataParms.SampleLen;
		NNInfo->InputCount = ioParms->DataParms.SampleLen;
		NNInfo->OutputCount = ioParms->DataParms.PredictionLen;
		if (getParam(ioParms, "XIEInfo.NN0.UseContext", &NNInfo->UseContext) < 0)								return -1;
		if (getParam(ioParms, "XIEInfo.NN0.TrainingProtocol", &NNInfo->TrainingProtocol, enumlist) < 0)		return -1;
		if (getParam(ioParms, "XIEInfo.NN0.BP_Algo", &NNInfo->BP_Algo, enumlist) < 0)							return -1;
		if (getParam(ioParms, "XIEInfo.NN0.ActivationFunction", &NNInfo->ActivationFunction, enumlist) < 0)	return -1;
		if (getParam(ioParms, "XIEInfo.NN0.StopAtDivergence", &NNInfo->StopAtDivergence) < 0)					return -1;
		if (getParam(ioParms, "XIEInfo.NN0.MaxEpochs", &NNInfo->MaxEpochs) < 0)								return -1;
		if (getParam(ioParms, "XIEInfo.NN0.LearningRate", &NNInfo->LearningRate) < 0)							return -1;
		if (getParam(ioParms, "XIEInfo.NN0.LearningMomentum", &NNInfo->LearningMomentum) < 0)					return -1;
		if (getParam(ioParms, "XIEInfo.NN0.TargetMSE", &NNInfo->TargetMSE) < 0)								return -1;
		if (getParam(ioParms, "XIEInfo.NN0.HCPbeta", &NNInfo->HCPbeta) < 0)									return -1;
		if (getParam(ioParms, "XIEInfo.NN0.mu", &NNInfo->mu) < 0)												return -1;
		if (getParam(ioParms, "XIEInfo.NN0.LevelRatios", &NNInfo->LevelRatioS[0]) < 0)						return -1;
		
		CoreInfo->TimeStepsCount = NNInfo->MaxEpochs;
		CoreInfo->SampleLen = NNInfo->InputCount;
		CoreInfo->TargetLen = NNInfo->OutputCount;
		CoreInfo->MSECount = NNInfo->MaxEpochs;
		CoreInfo->RunCount = ioParms->DataParms.HistoryLen + ioParms->DataParms.PredictionLen;

		//--
		CoreInfo = &ioParms->EngineParms.Core[1][0];
		CoreInfo->CoreSpecs = new NN_Parms();
		CoreInfo->CoreType = ENGINE_NN;
		NNInfo = (NN_Parms*)ioParms->EngineParms.Core[1][0].CoreSpecs;
		if (NNInfo->BP_Algo == BP_QING) ioParms->DataParms.PredictionLen = ioParms->DataParms.SampleLen;
		NNInfo->InputCount = 2 * ioParms->DataParms.PredictionLen;
		NNInfo->OutputCount = ioParms->DataParms.PredictionLen;
		if (getParam(ioParms, "XIEInfo.NN1.UseContext", &NNInfo->UseContext) < 0)								return -1;
		if (getParam(ioParms, "XIEInfo.NN1.TrainingProtocol", &NNInfo->TrainingProtocol, enumlist) < 0)		return -1;
		if (getParam(ioParms, "XIEInfo.NN1.BP_Algo", &NNInfo->BP_Algo, enumlist) < 0)							return -1;
		if (getParam(ioParms, "XIEInfo.NN1.ActivationFunction", &NNInfo->ActivationFunction, enumlist) < 0)	return -1;
		if (getParam(ioParms, "XIEInfo.NN1.StopAtDivergence", &NNInfo->StopAtDivergence) < 0)					return -1;
		if (getParam(ioParms, "XIEInfo.NN1.MaxEpochs", &NNInfo->MaxEpochs) < 0)								return -1;
		if (getParam(ioParms, "XIEInfo.NN1.LearningRate", &NNInfo->LearningRate) < 0)							return -1;
		if (getParam(ioParms, "XIEInfo.NN1.LearningMomentum", &NNInfo->LearningMomentum) < 0)					return -1;
		if (getParam(ioParms, "XIEInfo.NN1.TargetMSE", &NNInfo->TargetMSE) < 0)								return -1;
		if (getParam(ioParms, "XIEInfo.NN1.HCPbeta", &NNInfo->HCPbeta) < 0)									return -1;
		if (getParam(ioParms, "XIEInfo.NN1.mu", &NNInfo->mu) < 0)												return -1;
		if (getParam(ioParms, "XIEInfo.NN1.LevelRatios", &NNInfo->LevelRatioS[0]) < 0)						return -1;

		CoreInfo->TimeStepsCount = NNInfo->MaxEpochs;
		CoreInfo->SampleLen = NNInfo->InputCount;
		CoreInfo->TargetLen = NNInfo->OutputCount;
		CoreInfo->MSECount = NNInfo->MaxEpochs;
		CoreInfo->RunCount = ioParms->DataParms.HistoryLen + ioParms->DataParms.PredictionLen;

		break;
	}

	//-- 11. Core Logs
	mallocCoreLogs(ioParms);

	return 0;
}
__declspec(dllexport) void ForecastParamFree(tForecastParms* ioParms) {
	freeCoreLogs(ioParms);
	freeCoreParms(ioParms);
}

double****** mallocSample(tEngineDef* pEngineParms, tDataShape* pDataParms) {
	int slen;
	double****** ret = (double******)malloc(2 * sizeof(double*****));
	for (int hdvd = 0; hdvd < 2; hdvd++) {
		ret[hdvd] = (double*****)malloc(pDataParms->DatasetsCount * sizeof(double****));
		for (int d = 0; d < pDataParms->DatasetsCount; d++) {
			ret[hdvd][d] = (double****)malloc(pEngineParms->LayersCount * sizeof(double***));
			for (int l = 0; l < pEngineParms->LayersCount; l++) {
				ret[hdvd][d][l] = (double***)malloc(pEngineParms->CoresCount[l] * sizeof(double**));
				for (int c = 0; c < pEngineParms->CoresCount[l]; c++) {
					ret[hdvd][d][l][c] = (double**)malloc(pDataParms->SampleCount * sizeof(double*));
					slen = pEngineParms->Core[l][c].SampleLen;
					for (int s = 0; s < pDataParms->SampleCount; s++) {
						ret[hdvd][d][l][c][s] = (double*)malloc(slen * sizeof(double));
					}
				}
			}
		}
	}
	return ret;
}
double****** mallocTarget(tEngineDef* pEngineParms, tDataShape* pDataParms) {
	int tlen;
	double****** ret = (double******)malloc(2 * sizeof(double*****));
	for (int hdvd = 0; hdvd < 2; hdvd++) {
		ret[hdvd] = (double*****)malloc(pDataParms->DatasetsCount * sizeof(double****));
		for (int d = 0; d < pDataParms->DatasetsCount; d++) {
			ret[hdvd][d] = (double****)malloc(pEngineParms->LayersCount * sizeof(double***));
			for (int l = 0; l < pEngineParms->LayersCount; l++) {
				ret[hdvd][d][l] = (double***)malloc(pEngineParms->CoresCount[l] * sizeof(double**));
				for (int c = 0; c < pEngineParms->CoresCount[l]; c++) {
					ret[hdvd][d][l][c] = (double**)malloc(pDataParms->SampleCount * sizeof(double*));
					tlen = pEngineParms->Core[l][c].TargetLen;
					for (int s = 0; s < pDataParms->SampleCount; s++) {
						ret[hdvd][d][l][c][s] = (double*)malloc(tlen * sizeof(double));
					}
				}
			}
		}
	}
	return ret;
}
void freeSampleTarget(tEngineDef* pEngineParms, tDataShape* pDataParms, double****** S, double****** T) {
	for (int hdvd = 0; hdvd < 2; hdvd++) {
		for (int d = 0; d < pDataParms->DatasetsCount; d++) {
			for (int l = 0; l < pEngineParms->LayersCount; l++) {
				for (int c = 0; c < pEngineParms->CoresCount[l]; c++) {
					for (int s = 0; s < pDataParms->SampleCount; s++) {
						free(S[hdvd][d][l][c][s]);
						free(T[hdvd][d][l][c][s]);
					}
					free(S[hdvd][d][l][c]);
					free(T[hdvd][d][l][c]);
				}
				free(S[hdvd][d][l]);
				free(T[hdvd][d][l]);
			}
			free(S[hdvd][d]);
			free(T[hdvd][d]);
		}
		free(S[hdvd]);
		free(T[hdvd]);
	}
	free(S);
	free(T);
}

//--
int LogSave_Data(tDebugInfo* pDebugParms, tDataShape* pDataParms, int pid, int pTestId) {
	if (SaveTestLog_DataParms(pDebugParms, pDataParms, pid, pTestId) != 0) return -1;
	return 0;
}
int LogSave_MSE  (tDebugInfo* pDebugParms, tEngineDef* pEngineParms, tDataShape* pDataParms, int pTestId) {
	int l, n, d, i;
	tLogMSE* vMSELog;
	int vActualEpochs;

	for (l = 0; l<pEngineParms->LayersCount; l++) {
		for (n = 0; n<pEngineParms->CoresCount[l]; n++) {
			for (d = 0; d<pDataParms->DatasetsCount; d++) {
				//-- Fill Logs with missing info (Test, LayerId, CoreId,...)
				vMSELog = pEngineParms->Core[l][n].CoreLog[d].MSEOutput;
				vActualEpochs = pEngineParms->Core[l][n].CoreLog[d].ActualEpochs;
				if (vActualEpochs == 0) return -1;
				for (i = 0; i<vActualEpochs; i++) {
					vMSELog[i].TestId = pTestId;
					vMSELog[i].LayerId = l;
					vMSELog[i].CoreId = n;
				}
				//-- Actual Save
				if (BulkMSEInsert(pDebugParms, pEngineParms->EngineType, &vActualEpochs, vMSELog) != 0) return -1;
			}
		}
	}
	return 0;
}
int LogSave_Run  (tDebugInfo* pDebugParms, tEngineDef* pEngineParms, tDataShape* pDataParms, int pTestId, tLogRUN** R) {
	int rc = pDataParms->SampleLen + pDataParms->SampleCount + pDataParms->PredictionLen;

	for (int d = 0; d<pDataParms->DatasetsCount; d++) {
		if (BulkRunInsert(pDebugParms, &rc, pDataParms->HistoryLen, R[d]) != 0) return -1;
	}

	return 0;
}
int LogSave_Engine(tDebugInfo* pDebugParms, tEngineDef* pEngineParms, int pid, int pTestId){
	if (SaveTestLog_EngineParms(pDebugParms, pid, pTestId, pEngineParms) != 0) return -1;
	return 0;
}
int LogSave_Cores(tDebugInfo* pDebugParms, tEngineDef* pEngineParms, tDataShape* pDataParms, int pid, int pTestId) {

	//-- for each core, this performs 3 separate operations:
	//-- 1. save cores parameters into CoreParms_<XXX>
	//-- 2. save cores images     into CoreImage_<XXX> . For NN, image is defined by tNNWeight info; for SVM, image is defined by alphaY[] and SV[][]
	//-- 3. save cores logs       into CoreLogs_<XXX>

	tCore* core;
	NN_Parms* NNParms = nullptr;	tNNWeight*** NNWeight = nullptr;
	SOM_Parms* SOMParms = nullptr;	tSOMWeight** SOMWeight = nullptr;
	GA_Parms* GAParms = nullptr;	//tGAWeight*** GAWeight=nullptr;
	SVM_Parms* SVMParms = nullptr;	

	for (int l = 0; l < pEngineParms->LayersCount; l++) {
		for (int n = 0; n < pEngineParms->CoresCount[l]; n++) {
			core = &pEngineParms->Core[l][n];
			switch (core->CoreType) {
			case ENGINE_NN:
				NNParms = (NN_Parms*)core->CoreSpecs;
				//-- 1. save engine parameters
				if (InsertCoreParms_NN(pDebugParms, pid, pTestId, l, n, NNParms) != 0) return -1;
				//-- 2. save final image (weights) , for each dataset
				for (int d = 0; d < pDataParms->DatasetsCount; d++) {
					NNWeight = core->CoreLog[d].NNFinalW;
					if (InsertCoreImage_NN(pDebugParms, l, n, d, pTestId, NNParms, NNWeight) != 0) return -1;
					if (InsertCoreLogs_NN(pDebugParms, (NN_Parms*)core->CoreSpecs, &core->CoreLog[d]) != 0) return -1;
				}
				break;
			case ENGINE_GA:
				break;
			case ENGINE_SOM:
				SOMParms = (SOM_Parms*)core->CoreSpecs;
				//-- 1. save engine parameters
				if (InsertCoreParms_SOM(pDebugParms, pid, pTestId, l, n, SOMParms) != 0) return -1;
				//-- 2. save final image (weights) , for each dataset
				for (int d = 0; d < pDataParms->DatasetsCount; d++) {
					SOMWeight = core->CoreLog[d].SOMFinalW;
					if (InsertCoreImage_SOM(pDebugParms, l, n, d, pTestId, SOMParms, SOMWeight) != 0) return -1;
				}
				break;
			case ENGINE_SVM:
				SVMParms = (SVM_Parms*)core->CoreSpecs;
				//-- 1. save engine parameters
				if (InsertCoreParms_SVM(pDebugParms, pid, pTestId, l, n, SVMParms) != 0) return -1;
				//-- 2. save final image (weights) , for each dataset
				for (int d = 0; d < pDataParms->DatasetsCount; d++) {
					if (InsertCoreImage_SVM(pDebugParms, l, n, d, pTestId, SVMParms, &core->CoreLog[d].SVMResult, core->CoreLog[d].SVMWeight) != 0) return -1;
					if (InsertCoreLogs_SVM(pDebugParms, (SVM_Parms*)core->CoreSpecs, &core->CoreLog[d]) != 0) return -1;
				}
				break;
			}
		}
	}
	return 0;
}
//--

void SetTSScaleRange(int pEngineType, void* pCoreSpecs, double* oScaleMin, double* oScaleMax) {
	NN_Parms* NNParms;
	GA_Parms* GAParms;
	SOM_Parms* SOMParms;
	SVM_Parms* SVMParms;

	switch (pEngineType) {
	case ENGINE_NN:
		NNParms = (NN_Parms*)pCoreSpecs;
		switch (NNParms->ActivationFunction) {
		case NN_ACTIVATION_TANH:
			(*oScaleMin) = -1;
			(*oScaleMax) = 1;
			break;
		case NN_ACTIVATION_EXP4:
			(*oScaleMin) = 0;
			(*oScaleMax) = 1;
			break;
		default:
			(*oScaleMin) = -1;
			(*oScaleMax) = 1;
			break;
		}
		break;
	case ENGINE_WNN:
		//-- identical to ENGINE_NN
		NNParms = (NN_Parms*)pCoreSpecs;
		switch (NNParms->ActivationFunction) {
		case NN_ACTIVATION_TANH:
			(*oScaleMin) = -1;
			(*oScaleMax) = 1;
			break;
		case NN_ACTIVATION_EXP4:
			(*oScaleMin) = 0;
			(*oScaleMax) = 1;
			break;
		default:
			(*oScaleMin) = -1;
			(*oScaleMax) = 1;
			break;
		}
		break;
	case ENGINE_GA:
		GAParms = (GA_Parms*)pCoreSpecs;
		(*oScaleMin) = -1;
		(*oScaleMax) = 1;
		break;
	case ENGINE_SOM:
		SOMParms = (SOM_Parms*)pCoreSpecs;
		(*oScaleMin) = -1;
		(*oScaleMax) = 1;
		break;
	case ENGINE_SVM:
		SVMParms = (SVM_Parms*)pCoreSpecs;
		(*oScaleMin) = -1;
		(*oScaleMax) = 1;
		break;
	case ENGINE_XIE:
		(*oScaleMin) = -1;
		(*oScaleMax) = 1;
		break;
	}
}

//--
void Train_XXX(tTrainParams* tp) {
	NN_Parms* NNParms;
	GA_Parms* GAParms;
	SOM_Parms* SOMParms;
	SVM_Parms* SVMParms;

	tCoreLog* coreLog= &tp->EngineParms->Core[tp->LayerId][tp->CoreId].CoreLog[tp->DatasetId];

	switch (tp->EngineParms->Core[tp->LayerId][tp->CoreId].CoreType) {
	case ENGINE_NN:
		NNParms = (NN_Parms*)tp->EngineParms->Core[tp->LayerId][tp->CoreId].CoreSpecs;
		tp->TrainSuccess = Train_NN(tp->CorePos, tp->TotCores, tp->ScreenMutex, tp->DebugParms, NNParms, coreLog, tp->SampleCount, tp->SampleT, tp->TargetT, tp->SampleV, tp->TargetV);
		tp->ActualEpochs = coreLog->ActualEpochs;
		break;
	case ENGINE_GA:
		GAParms = (GA_Parms*)tp->EngineParms->Core[tp->LayerId][tp->CoreId].CoreSpecs;
		//-- tp->TrainSuccess= Train_GA(...);
		tp->ActualEpochs = coreLog->ActualEpochs;
		break;
	case ENGINE_SOM:
		SOMParms = (SOM_Parms*)tp->EngineParms->Core[tp->LayerId][tp->CoreId].CoreSpecs;
		//-- tp->TrainSuccess= Train_SOM(...);
		tp->ActualEpochs = coreLog->ActualEpochs;
		break;
	case ENGINE_SVM:
		SVMParms = (SVM_Parms*)tp->EngineParms->Core[tp->LayerId][tp->CoreId].CoreSpecs;
		tp->TrainSuccess = Train_SVM(tp->CorePos, tp->TotCores, tp->ScreenMutex, tp->DebugParms, SVMParms, coreLog, tp->SampleCount, tp->SampleT, tp->TargetT, tp->SampleV, tp->TargetV);
		tp->ActualEpochs = coreLog->ActualEpochs;
		break;
	}
	//-- update EngineParms->MSECount
	tp->EngineParms->Core[tp->LayerId][tp->CoreId].MSECount = tp->ActualEpochs;
}
void Run_XXX(tDebugInfo* pDebugParms, tEngineDef* pEngineParms, tDataShape* pInputData, int pLayerId, int pCoreId, int pDatasetId, int pid, int tid, int pNetId, int pTestId, int pSampleCount, double** pSample, double** pTarget, int usefd, double** pFD_TRS) {

	tCoreLog* coreLog = &pEngineParms->Core[pLayerId][pCoreId].CoreLog[pDatasetId];

	int engtype = pEngineParms->Core[pLayerId][pCoreId].CoreType;
	if (engtype == ENGINE_NN || engtype == ENGINE_WNN) {
		NN_Parms* NNParms = (NN_Parms*)pEngineParms->Core[pLayerId][pCoreId].CoreSpecs;
		//-- Actual Run sets ProcessId, ThreadId, Pos, Actual, Predicted
		Run_NN(pDebugParms, NNParms, coreLog, pInputData, pid, tid, pSampleCount, pSample, pTarget);
	} else if (engtype == ENGINE_SVM) {
		SVM_Parms* SVMParms = (SVM_Parms*)pEngineParms->Core[pLayerId][pCoreId].CoreSpecs;
		//-- Actual Run sets ProcessId, ThreadId, Pos, Actual, Predicted
		Run_SVM(pDebugParms, SVMParms, coreLog, pInputData, pid, tid, pSampleCount, pSample, pTarget);
		int kaz = 0;
	} else {
		//-- other engine core types ...
	}
}
void Train_Layer(tDebugInfo* pDebugParms, tEngineDef* pEngineParms, tDataShape* pDataParms, int pid, int pTestId, int pLayer, tTrainParams* tp, double****** pSampleData, double****** pTargetData) {
	int t;
	int ThreadCount = pDataParms->DatasetsCount*pEngineParms->TotalCoresCount;
	HANDLE* HTrain = (HANDLE*)malloc(ThreadCount * sizeof(HANDLE));
	DWORD* kaz = (DWORD*)malloc(ThreadCount * sizeof(DWORD));
	LPDWORD* tid = (LPDWORD*)malloc(ThreadCount * sizeof(LPDWORD)); for (int i = 0; i < ThreadCount; i++) tid[i] = &kaz[i];
	HANDLE SMutex = CreateMutex(NULL, FALSE, NULL);

	gotoxy(0, 2 + pLayer + ((pLayer>0) ? pDataParms->DatasetsCount*pEngineParms->CoresCount[pLayer - 1] : 0));  printf("Training Layer %d\n", pLayer);
	t = 0;
	for (int n = 0; n<pEngineParms->CoresCount[pLayer]; n++) {
		for (int d = 0; d<pDataParms->DatasetsCount; d++) {
			tp[t].LayerId = pLayer;
			tp[t].CoreId = n;
			tp[t].DatasetId = d;
			tp[t].CorePos = 2 + t + pLayer + ((pLayer>0) ? pDataParms->DatasetsCount*pEngineParms->CoresCount[pLayer - 1] : 0);
			tp[t].ScreenMutex = SMutex;
			tp[t].TotCores = pEngineParms->CoresCount[pLayer] * pDataParms->DatasetsCount;
			tp[t].DebugParms = pDebugParms;
			tp[t].EngineParms = pEngineParms;
			tp[t].SampleCount = pDataParms->SampleCount;

			//-- SampleData, TargetData
			tp[t].SampleT = pSampleData[HD][d][pLayer][n]; tp[t].SampleV = pSampleData[VD][d][pLayer][n];
			tp[t].TargetT = pTargetData[HD][d][pLayer][n]; tp[t].TargetV = pTargetData[VD][d][pLayer][n];

			//-- Create Thread
			HTrain[t] = CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE)Train_XXX, &tp[t], 0, tid[t]);

			//-- Store Engine Handler
			tp[t].TrainInfo.DatasetId = d;
			tp[t].TrainInfo.ProcessId = pid;
			tp[t].TrainInfo.ThreadId = (*tid[t]);
			tp[t].TrainInfo.TestId = pTestId;

			// workaround needed because somehow SVM engine fucks up when multi-threading. TO BE FIXED !!!!
			//if(tp[t].EngineParms->Core[n]->CoreType==ENGINE_SVM) WaitForSingleObject(HTrain[t], INFINITE);

			t++;
		}
	}
	//-- we need to train all the nets in one layer, in order to have the inputs to the next layer
	WaitForMultipleObjects(t, HTrain, TRUE, INFINITE);

	//-- free(s)
	free(HTrain); free(kaz); free(tid);
}
void Run_Layer(tDebugInfo* pDebugParms, tEngineDef* pEngineParms, tDataShape* pDataParms, int pLayer, int pid, tTrainParams* tp, double****** SampleData, double****** TargetData, int usefd, double** pFD_TRS) {
	int i = 0;
	for (int n = 0; n<pEngineParms->CoresCount[pLayer]; n++) {
		for (int d = 0; d<pDataParms->DatasetsCount; d++) {
			Run_XXX(pDebugParms, pEngineParms, pDataParms, pLayer, n, d, pid, tp[i].TrainInfo.ThreadId, n, tp[i].TrainInfo.TestId, pDataParms->SampleCount, SampleData[HD][d][pLayer][n], TargetData[HD][d][pLayer][n], usefd, pFD_TRS);
			i++;
		}
	}
}
//--

void SetNetPidTid(tEngineDef* pEngineParms, int pLayer, int pDatasetsCount, int pDoTraining, tEngineHandle* pSavedEngine) {
	//-- from pSavedEngine we need pid and ONE tid.
	//-- from pTrainParms we get an array of threads from current training session
	int n, d, i, j;

	tLogMSE* MSELog = nullptr;
	tLogRUN* RunLog = nullptr;

	i = 0;
	for (n = 0; n<pEngineParms->CoresCount[pLayer]; n++) {
		for (d = 0; d<pDatasetsCount; d++) {

			MSELog = pEngineParms->Core[pLayer][n].CoreLog[d].MSEOutput;
			RunLog = pEngineParms->Core[pLayer][n].CoreLog[d].RunOutput;

			for (j = 0; j<pEngineParms->Core[pLayer][n].RunCount; j++) {
				if (pDoTraining>0) {
					RunLog[j].NetProcessId = RunLog[j].ProcessId;
					RunLog[j].NetThreadId = RunLog[j].ThreadId;
				}
				else {
					RunLog[j].NetProcessId = pSavedEngine->ProcessId;
					RunLog[j].NetThreadId = pSavedEngine->ThreadId + i;
				}
			}
		}
		i++;
	}
}

void CalcTSF(tEngineDef* pEngineParms, tDataShape* pDataParms, int pTSLen, double* pTS, double* pTSF) {

	double scaleM, scaleP;	// unused!

	for (int t = 0; t < pEngineParms->TSFcnt; t++) {
		switch (pEngineParms->TSFid[t]) {
		case TSF_MEAN:
			pTSF[pEngineParms->TSFid[t]] = TSMean(pTSLen, pTS);
			break;
		case TSF_MAD:
			pTSF[pEngineParms->TSFid[t]] = TSMeanAbsoluteDeviation(pTSLen, pTS);
			break;
		case TSF_VARIANCE:
			pTSF[pEngineParms->TSFid[t]] = TSVariance(pTSLen, pTS);
			break;
		case TSF_SKEWNESS:
			pTSF[pEngineParms->TSFid[t]] = TSSkewness(pTSLen, pTS);
			break;
		case TSF_KURTOSIS:
			pTSF[pEngineParms->TSFid[t]] = TSKurtosis(pTSLen, pTS);
			break;
		case TSF_TURNINGPOINTS:
			pTSF[pEngineParms->TSFid[t]] = TSTurningPoints(pTSLen, pTS);
			break;
		case TSF_SHE:
			pTSF[pEngineParms->TSFid[t]] = TSShannonEntropy(pTSLen, pTS);
			break;
		case TSF_HISTVOL:
			pTSF[pEngineParms->TSFid[t]] = TSHistoricalVolatility(pTSLen, pTS);
			break;
		}
	}

	//-- TSF Scaling - Scaling across different TSFs ; REVIEW!!
	if (pEngineParms->TSFcnt>0) {
		DataScale(pEngineParms->TSFcnt, pTSF, -1, 1, pTSF, &scaleM, &scaleP);
	}

}

void CalcForecastFromEngineOutput(tEngineDef* pEngineParms, tDataShape* pDataParms, int pTestId, double* scaleM, double* scaleP, double* baseVal, double* minVal, double** hd_trs, double** wd_bw, int pOOS, double** fd_trs, tLogRUN** runLog_o, double** oPredictedData) {
	int d, i;

	int sl0 = pDataParms->SampleLen;			// SampleLen from original data
	int sl1 = pEngineParms->Core[pEngineParms->LayersCount-1][0].SampleLen;	// SampleLen from last layer, core 0 
	int sc = pDataParms->SampleCount;
	int pl = pDataParms->PredictionLen;
	int rc = sl0 + sc + pl;

	tLogRUN* runLog_i=nullptr;

	double*  act		= MallocArray<double>(rc);
	double*  prd		= MallocArray<double>(rc);
	double*  act_tr		= MallocArray<double>(rc);
	double*  prd_tr		= MallocArray<double>(rc);
	double*  act_trs	= MallocArray<double>(rc);
	double*  prd_trs	= MallocArray<double>(rc);
	double*  err		= MallocArray<double>(rc);
	double*  err_trs	= MallocArray<double>(rc);

	for (d = 0; d < pDataParms->DatasetsCount; d++) {

		runLog_i = pEngineParms->Core[pEngineParms->LayersCount - 1][0].CoreLog[d].RunOutput;

		//-- Actual_TRS
		for (i = 0; i < sl0; i++) act_trs[i]			= hd_trs[d][i];
		for (i = 0; i < sc ; i++) act_trs[sl0 + i]		= hd_trs[d][sl0 + i];
		for (i = 0; i < pl ; i++) act_trs[sl0 + sc + i] = (pOOS == 0) ? NULL : fd_trs[d][i];

		//-- Predicted_TRS
		for (i = 0; i < sl0; i++) prd_trs[i]			= NULL;
		for (i = 0; i < sc ; i++) prd_trs[sl0 + i]		= runLog_i[sl1 + i].Predicted_TRS;
		for (i = 0; i < pl ; i++) prd_trs[sl0 + sc + i]	= runLog_i[sl1 + sc + i].Predicted_TRS;

		//-- UnScale/UnTransform act
		DataUnScale(rc, 0, rc, act_trs, scaleM[d], scaleP[d], act_tr);
		dataUnTransform(pDataParms->DataTransformation, 0, rc, act_tr, baseVal[d], minVal[d], act, act);
		//-- UnScale/UnTransform prd
		DataUnScale(rc, sl0, rc, prd_trs, scaleM[d], scaleP[d], prd_tr);
		dataUnTransform(pDataParms->DataTransformation, sl0, rc, prd_tr, act[sl0-1], minVal[d], act, prd);	// baseVal should be actual[sampleLen-1], and we skip the first <sampleLen> elements
		//-- prd elements need to be shifted back...
		//--.....

		//-- calc err, err_trs
		for (i = 0; i < sl0; i++) {
			prd[i]		= 0;
			err[i]		= 0;
			err_trs[i]	= 0;
		}
		for (i = sl0; i < (sl0+sc); i++) {
			err[i] = fabs(prd[i] - act[i]);
			err_trs[i] = fabs(prd_trs[i] - act_trs[i]);
		}
		for (i = (sl0 + sc); i < rc; i++) {
			err[i] = (pOOS == 0) ? 0 : fabs(prd[i] - act[i]);
			err_trs[i] = (pOOS == 0) ? 0 : fabs(prd_trs[i] - act_trs[i]);
		}

		//-- fill runLog_o[d]
		for (i = 0; i<rc; i++) {
			runLog_o[d][i].ProcessId = runLog_i[0].ProcessId;
			runLog_o[d][i].NetProcessId = runLog_i[0].NetProcessId;
			runLog_o[d][i].ThreadId = runLog_i[0].ThreadId;
			runLog_o[d][i].NetThreadId = runLog_i[0].NetThreadId;
			runLog_o[d][i].TestId = pTestId;
			runLog_o[d][i].LayerId = pEngineParms->LayersCount - 1;
			runLog_o[d][i].CoreId = 0;

			runLog_o[d][i].Pos = i;
			runLog_o[d][i].Actual = act[i];
			runLog_o[d][i].Actual_TRS = act_trs[i];
			runLog_o[d][i].Predicted = prd[i];
			runLog_o[d][i].Predicted_TRS = prd_trs[i];
			runLog_o[d][i].Error = err[i];
			runLog_o[d][i].Error_TRS = err_trs[i];

			runLog_o[d][i].BarWidth = wd_bw[d][i];
			runLog_o[d][i].ErrorP = (runLog_o[d][i].BarWidth==0)?0:(runLog_o[d][i].Error / runLog_o[d][i].BarWidth);
		}

		//-- finally, set oPredictedData
		for (i = 0; i < pl; i++) oPredictedData[d][i] = prd[sl0 + sc + i];
	}

	FreeArray(rc, act);
	FreeArray(rc, prd);
	FreeArray(rc, act_tr);
	FreeArray(rc, prd_tr);
	FreeArray(rc, act_trs);
	FreeArray(rc, prd_trs);
	FreeArray(rc, err);
	FreeArray(rc, err_trs);

}

__declspec(dllexport) int getForecast(int paramOverrideCnt, char** paramOverride, int pTestId, double** pHistoryData, double* pHistoryBaseVal, double** pHistoryBW, double** pValidationData, double* pValidationBaseVal, int haveActualFuture, double** pFutureData, double** pFutureBW, double** oPredictedData) {

	HANDLE FMutex = CreateMutex(NULL, FALSE, NULL);

	// Forecasting Parameters initialization. 
	tForecastParms fp;
	//-- a. set overrides from Command Line 
	if (CLProcess(paramOverrideCnt, paramOverride, &fp) != 0) return -1;
	//-- b. process ini file
	if (ForecastParamLoader(&fp) <0) return -1;

	fp.DebugParms.Mtx = FMutex;
	int pid = GetCurrentProcessId();

	int dscnt = fp.DataParms.DatasetsCount;
	int hlen = fp.DataParms.HistoryLen;
	double** hd = pHistoryData;
	double** vd = pValidationData;
	int flen = fp.DataParms.PredictionLen;
	double** fd = pFutureData;
	int layersCnt = fp.EngineParms.LayersCount;
	int* coresCnt = fp.EngineParms.CoresCount;

	int i, l, d;

	int sampleCnt  = fp.DataParms.SampleCount;
	int sampleLen0 = fp.DataParms.SampleLen;
	int rc = sampleLen0 + sampleCnt + flen;

	//-- Transform and Scale History, Validation, Future Data
	int wlen = hlen + flen;

	double** wd			= MallocArray<double>(dscnt, wlen);
	double** wd_tr		= MallocArray<double>(dscnt, wlen);
	double** wd_trs		= MallocArray<double>(dscnt, wlen);
	double** wd_bw		= MallocArray<double>(dscnt, wlen);
	double** hd_trs		= MallocArray<double>(dscnt, hlen);
	double** vd_tr		= MallocArray<double>(dscnt, hlen);
	double** vd_trs		= MallocArray<double>(dscnt, hlen);
	double** fd_trs		= MallocArray<double>(dscnt, flen);

	double* hd_min = MallocArray<double>(dscnt);
	double* vd_min = MallocArray<double>(dscnt);
	double* wd_min = MallocArray<double>(dscnt);

	double scaleMin, scaleMax;
	double*  wd_scaleM = MallocArray<double>(dscnt);
	double*  wd_scaleP = MallocArray<double>(dscnt);
	double*  vd_scaleM = MallocArray<double>(dscnt);
	double*  vd_scaleP = MallocArray<double>(dscnt);
	double** hd_tsf		= MallocArray<double>(dscnt, fp.EngineParms.TSFcnt);
	double** vd_tsf		= MallocArray<double>(dscnt, fp.EngineParms.TSFcnt);

	double*****		ts			= MallocArray<double>(2, dscnt, layersCnt, ArrayMax<int>(layersCnt, coresCnt), hlen);
	double*****		ts_tr		= MallocArray<double>(2, dscnt, layersCnt, ArrayMax<int>(layersCnt, coresCnt), hlen);
	double*****		ts_trs		= MallocArray<double>(2, dscnt, layersCnt, ArrayMax<int>(layersCnt, coresCnt), hlen);
	double****		ts_scaleM	= MallocArray<double>(2, dscnt, layersCnt, ArrayMax<int>(layersCnt, coresCnt));
	double****		ts_scaleP	= MallocArray<double>(2, dscnt, layersCnt, ArrayMax<int>(layersCnt, coresCnt));
	double****		bv			= MallocArray<double>(2, dscnt, layersCnt, ArrayMax<int>(layersCnt, coresCnt));
	double****		mv			= MallocArray<double>(2, dscnt, layersCnt, ArrayMax<int>(layersCnt, coresCnt));
	tTrainParams*	tp			= MallocArray<tTrainParams>(fp.DataParms.DatasetsCount*fp.EngineParms.TotalCoresCount);
	tLogRUN**		runLog		= MallocArray<tLogRUN>(dscnt, rc);

	double****** Sample = mallocSample(&fp.EngineParms, &fp.DataParms);
	double****** Target = mallocTarget(&fp.EngineParms, &fp.DataParms);

	/*
		ts		[HD/VD][Dataset][Layer][Core][item]
		Sample	[HD/VD][Dataset][Layer][Core][Sample][item]
		Target	[HD/VD][Dataset][Layer][Core][Sample][item]
	*/

	//----- Base TimeSerie s-----------------------------------------------------------
	for (d = 0; d < dscnt; d++) {

		//-- build wd from hd, fd
		for (i = 0; i < hlen; i++) {
			wd[d][i] = hd[d][i];
			wd_bw[d][i] = pHistoryBW[d][i];
		}
		for (i = 0; i < flen; i++) {
			wd[d][hlen + i] = fd[d][i];
			wd_bw[d][hlen + i] = pFutureBW[d][i];
		}
		SetTSScaleRange(fp.EngineParms.EngineType, fp.EngineParms.Core[0][0].CoreSpecs, &scaleMin, &scaleMax);
		//-- transform/scale wd
		dataTransform(fp.DataParms.DataTransformation, wlen, wd[d], pHistoryBaseVal[d], &wd_min[d], wd_tr[d]);
		DataScale(wlen, wd_tr[d], scaleMin, scaleMax, wd_trs[d], &wd_scaleM[d], &wd_scaleP[d]);
		//-- transform/scale vd
		dataTransform(fp.DataParms.DataTransformation, hlen, vd[d], pValidationBaseVal[d], &vd_min[d], vd_tr[d]);
		DataScale(hlen, vd_tr[d], scaleMin, scaleMax, vd_trs[d], &vd_scaleM[d], &vd_scaleP[d]);

		//-- derive hd_trs, fd_trs from wd_trs
		for (int i = 0; i < hlen; i++) hd_trs[d][i] = wd_trs[d][i];
		for (int i = 0; i < flen; i++) fd_trs[d][i] = wd_trs[d][hlen + i];

		// regardless of the engine, we slide base timeserie. If needed by specific engine, this will get overwritten
		SlideArray(hlen, hd_trs[d], sampleCnt, fp.EngineParms.Core[0][0].SampleLen, Sample[HD][d][0][0], flen, Target[HD][d][0][0], 0);
		SlideArray(hlen, vd_trs[d], sampleCnt, fp.EngineParms.Core[0][0].SampleLen, Sample[VD][d][0][0], flen, Target[VD][d][0][0], 0);

		CalcTSF(&fp.EngineParms, &fp.DataParms, hlen, hd[d], hd_tsf[d]);
		CalcTSF(&fp.EngineParms, &fp.DataParms, hlen, vd[d], vd_tsf[d]);
	}

	DumpArrayD(wlen, wd[0], "c:/temp/wd0.txt");
	DumpArrayD(wlen, wd_trs[0], "c:/temp/wd_trs0.txt");

	for (l = 0; l < fp.EngineParms.LayersCount; l++) {
		for (d = 0; d < dscnt; d++) {
			switch (fp.EngineParms.EngineType) {
			case ENGINE_WNN:
				BuildLayerInput_WNN(l, &fp.EngineParms, fp.DataParms.DataTransformation, d, sampleCnt, hlen, hd[d], pHistoryBaseVal[d], ts[HD][d][l], bv[HD][d][l], hd_tsf[d], fp.EngineParms.Core[0], Target[HD][d][0][0], Sample[HD][d][1][0], Target[HD][d][1][0]);
				BuildLayerInput_WNN(l, &fp.EngineParms, fp.DataParms.DataTransformation, d, sampleCnt, hlen, vd[d], pHistoryBaseVal[d], ts[VD][d][l], bv[VD][d][l], vd_tsf[d], fp.EngineParms.Core[0], Target[VD][d][0][0], Sample[VD][d][1][0], Target[VD][d][1][0]);
				if (l == 0) {
					for (int n = 0; n < coresCnt[0]; n++) {
						SetTSScaleRange(fp.EngineParms.EngineType, fp.EngineParms.Core[l][n].CoreSpecs, &scaleMin, &scaleMax);
						// HD
						dataTransform(fp.DataParms.DataTransformation, hlen, ts[HD][d][l][n], bv[HD][d][l][n], &mv[HD][d][l][n], ts_tr[HD][d][l][n]);
						DataScale(hlen, ts_tr[HD][d][l][n], scaleMin, scaleMax, ts_trs[HD][d][l][n], &ts_scaleM[HD][d][l][n], &ts_scaleP[HD][d][l][n]);
						SlideArray(hlen, ts_trs[HD][d][l][n], sampleCnt, fp.EngineParms.Core[l][0].SampleLen, Sample[HD][d][l][n], flen, Target[HD][d][l][n], 0);
						// VD
						dataTransform(fp.DataParms.DataTransformation, hlen, ts[VD][d][l][n], bv[VD][d][l][n], &mv[HD][d][l][n], ts_tr[VD][d][l][n]);
						DataScale(hlen, ts_tr[VD][d][l][n], scaleMin, scaleMax, ts_trs[VD][d][l][n], &ts_scaleM[VD][d][l][n], &ts_scaleP[VD][d][l][n]);
						SlideArray(hlen, ts_trs[VD][d][l][n], sampleCnt, fp.EngineParms.Core[l][0].SampleLen, Sample[VD][d][l][n], flen, Target[VD][d][l][n], 0);
					}
				}
				break;
			case ENGINE_XIE:
				BuildLayerInput_XIE(l, d, sampleCnt, fp.DataParms.PredictionLen, Sample[HD], Target[HD], fp.EngineParms.Core);
				BuildLayerInput_XIE(l, d, sampleCnt, fp.DataParms.PredictionLen, Sample[VD], Target[VD], fp.EngineParms.Core);
				break;
			default:
				break;
			}
		}

		Train_Layer(&fp.DebugParms, &fp.EngineParms, &fp.DataParms, pid, pTestId, l, tp, Sample, Target);
		Run_Layer(&fp.DebugParms, &fp.EngineParms, &fp.DataParms, l, pid, tp, Sample, Target, haveActualFuture, fd_trs);
		SetNetPidTid(&fp.EngineParms, l, dscnt, fp.DoTraining, &fp.SavedEngine);
	}

	CalcForecastFromEngineOutput(&fp.EngineParms, &fp.DataParms, pTestId, wd_scaleM, wd_scaleP, pHistoryBaseVal, wd_min, hd_trs, wd_bw, haveActualFuture, fd_trs, runLog, oPredictedData);

	if (LogSave_Data(&fp.DebugParms, &fp.DataParms, pid, pTestId) != 0) return -1;
	if (LogSave_MSE (&fp.DebugParms, &fp.EngineParms, &fp.DataParms, pTestId) !=0) return -1;
	if (LogSave_Run(&fp.DebugParms, &fp.EngineParms, &fp.DataParms, pTestId, runLog) != 0) return -1;
	if (LogSave_Engine(&fp.DebugParms, &fp.EngineParms, pid, pTestId) != 0) return -1;
	if (LogSave_Cores(&fp.DebugParms, &fp.EngineParms, &fp.DataParms, pid, pTestId) != 0) return -1;
	LogCommit(&fp.DebugParms);

	//-- free(s) 
	FreeArray(dscnt, wlen, wd);
	FreeArray(dscnt, wlen, wd_tr);
	FreeArray(dscnt, wlen, wd_trs);
	FreeArray(dscnt, wlen, wd_bw);
	FreeArray(dscnt, hlen, hd_trs);
	FreeArray(dscnt, hlen, vd_tr);
	FreeArray(dscnt, hlen, vd_trs);
	FreeArray(dscnt, flen, fd_trs);
	FreeArray(dscnt, hd_min);
	FreeArray(dscnt, vd_min);
	FreeArray(dscnt, wd_min);
	FreeArray(dscnt, wd_scaleM);
	FreeArray(dscnt, wd_scaleP);
	FreeArray(dscnt, vd_scaleM);
	FreeArray(dscnt, vd_scaleP);
	FreeArray(dscnt, fp.EngineParms.TSFcnt, hd_tsf);
	FreeArray(dscnt, fp.EngineParms.TSFcnt, vd_tsf);
	FreeArray(2, dscnt, layersCnt, ArrayMax<int>(layersCnt, coresCnt), wlen, ts);
	FreeArray(2, dscnt, layersCnt, ArrayMax<int>(layersCnt, coresCnt), wlen, ts_tr);
	FreeArray(2, dscnt, layersCnt, ArrayMax<int>(layersCnt, coresCnt), wlen, ts_trs);
	FreeArray(2, dscnt, layersCnt, ArrayMax<int>(layersCnt, coresCnt), ts_scaleM);
	FreeArray(2, dscnt, layersCnt, ArrayMax<int>(layersCnt, coresCnt), ts_scaleP);
	FreeArray(2, dscnt, layersCnt, ArrayMax<int>(layersCnt, coresCnt), bv);
	FreeArray(2, dscnt, layersCnt, ArrayMax<int>(layersCnt, coresCnt), mv);
	FreeArray(fp.DataParms.DatasetsCount*fp.EngineParms.TotalCoresCount, tp);
	FreeArray(dscnt, rc, runLog);

	freeSampleTarget(&fp.EngineParms, &fp.DataParms, Sample, Target);

	LogClose(&fp.DebugParms);

	ForecastParamFree(&fp);

	return 0;

}

extern "C" __declspec(dllexport) int MTgetForecast(int paramOverrideCnt, char** paramOverride, int pTestId, double** pHistoryData, double* pHistoryBaseVal, double** pHistoryBW, double** pValidationData, double* pValidationBaseVal, int haveActualFuture, double** pFutureData, double** pFutureBW, double** oPredictedData) {
	return 0;
}

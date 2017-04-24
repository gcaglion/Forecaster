#include <vld.h>

#include <MyTimeSeries.h>
#include <MyEnums.h>
#include <Windows.h>
#include <math.h>
#include <MyUtils.h>
#include <MyLogger.h>
#include <MyForecast.h>
#include <MyOraUtils.h>
#include <MyNN.h>
#include <MyWNN.h>
#include <MyGA.h>
#include <MySOM.h>
#include <MySVM.h>
#include <MyUtils.h>

#define PARAM_INT 0
#define PARAM_STRING 1
#define PARAM_DOUBLE 2
/*
int  CLparamCount;
char CLparamName[200][100];		// 200 parameters max. Parameter name must bel less than 100 characters long
char CLparamVal[200][100];		// 200 parameters max. Parameter name must bel less than 100 characters long
int CLFail(int p) {
	printf("Command Line Fail on parameter %d !\nExiting...\n", p);
	system("pause");
	return -1;
}
int CLProcess(int argc, char* argv[]) {
	CLparamCount = argc;
	for (int p = 1; p < CLparamCount; p++) {
		char* pch = strchr(argv[p], '=');
		if (pch == NULL || argv[p][0] != '-' || argv[p][1] != '-') return CLFail(p);
		memcpy(&CLparamName[p][0], &argv[p][2], (pch - argv[p] - 2)); CLparamName[p][pch - argv[p] - 2] = '\0';
		memcpy(&CLparamVal[p][0], &argv[p][pch - argv[p] + 1], strlen(argv[p]));
	}
	return 0;
}
*/
void*** Malloc_CoreSpecs(int LayerCnt, int* NetCnt) {
	void*** ES = (void***)malloc(LayerCnt * sizeof(void**));
	for (int l = 0; l<LayerCnt; l++) {
		ES[l] = (void**)malloc(NetCnt[l] * sizeof(void*));
		//for (int n = 0; n < NetCnt[l]; n++) {
		//	ES[l][n] = (void*)malloc(1 * sizeof(void*));
		//}
	}
	return ES;
}
void Free_CoreSpecs(int LayerCnt, int* NetCnt, void*** cs) {
	for (int l = 0; l < LayerCnt; l++) {
		//for (int n = 0; n < NetCnt[l]; n++) {
		//	free(cs[l][n]);
		//}
		free(cs[l]);
	}
	free(cs);
}

NN_Parms*** Malloc_WNN_NNInfo(int LayerCnt, int* NetCnt) {
	NN_Parms*** NNP = (NN_Parms***)malloc(LayerCnt * sizeof(NN_Parms**));
	for (int l = 0; l<LayerCnt; l++) {
		NNP[l] = (NN_Parms**)malloc(NetCnt[l] * sizeof(NN_Parms*));
		for (int n = 0; n<NetCnt[l]; n++) {
			NNP[l][n] = (NN_Parms*)malloc(1 * sizeof(NN_Parms));
		}
	}
	return NNP;
}
void Free_WNNInfo(int LayerCnt, int* NetCnt, NN_Parms*** wnn) {
	for (int l = 0; l<LayerCnt; l++) {
		for (int n = 0; n < NetCnt[l]; n++) {
			free(wnn[l][n]);
		}
		free(wnn[l]);
	}
	free(wnn);
}
/*
int getParam(char* fileName, char* paramName, int* oparamVal) {
	for (int p = 1; p < CLparamCount; p++) {
		if (strcmp(CLparamName[p], paramName) == 0) {
			(*oparamVal) = atoi(CLparamVal[p]);
			return 0;
		}
	}
	return ReadParamFromFile(fileName, paramName, oparamVal);
}
int getParam(char* fileName, char* paramName, double* oparamVal) {
	for (int p = 1; p < CLparamCount; p++) {
		if (strcmp(CLparamName[p], paramName) == 0) {
			(*oparamVal) = atof(CLparamVal[p]);
			return 0;
		}
	}
	return ReadParamFromFile(fileName, paramName, oparamVal);
}
int getParam(char* fileName, char* paramName, char* oparamVal) {
	for (int p = 1; p < CLparamCount; p++) {
		if (strcmp(CLparamName[p], paramName) == 0) {
			strcpy(oparamVal, CLparamVal[p]);
			return 0;
		}
	}
	return ReadParamFromFile(fileName, paramName, oparamVal);
}
*/
int main(int argc, char* argv[]) {
	int i;
	/*
	printf("size of long: %d\n", sizeof(long));
	printf("size of float: %d\n", sizeof(float));
	printf("size of double: %d\n\n", sizeof(double));
	printf("size of long*: %d\n", sizeof(long*));
	printf("size of float*: %d\n", sizeof(float*));
	printf("size of double*: %d\n", sizeof(double*));
	system("pause");
	*/
	//-- timer init
	LARGE_INTEGER frequency;			// ticks per second
	LARGE_INTEGER time_start, time_end; // ticks
	double elapsedTime; char elapsedTimeS[30];
	// get ticks per second
	QueryPerformanceFrequency(&frequency);
	// start timer
	QueryPerformanceCounter(&time_start);
	//--
/*
	char IniFileName[MAX_PATH];
	char** ParamValC = (char**)malloc(MAX_LAYERS * sizeof(char*)); for (i = 0; i<MAX_LAYERS; i++) ParamValC[i] = (char*)malloc(1000);
	int*    ParamValI = (int*)malloc(MAX_LAYERS * sizeof(int));
	double* ParamValD = (double*)malloc(MAX_LAYERS * sizeof(double));
*/
	tEngineDef EngineInfo;
//	tDebugInfo fParms.DebugParms;
//	tDataShape TestData;
	static tFXData FXDBInfo;
	static tFileData DataSourceFileInfo;
	tEngineHandle SavedEngine;
	NN_Parms NNInfo[2];
	GA_Parms GAInfo;
	SOM_Parms SOMInfo;
	SVM_Parms SVMInfo;
	WNN_Arch WNNInfo;
	NN_Parms*** WNN_NNInfo = nullptr;

	// Forecasting Parameters initialization. 
	tForecastParms fParms;
	//-- a. set overrides from Command Line 
	if (CLProcess(argc, argv, fParms) != 0) return -1;

	//-- default values for single-engines
	EngineInfo.LayersCount = 1;
	EngineInfo.CoresCount[0] = 1;
	EngineInfo.TotalCoresCount = 1;

	/*
	//-- determine parameter file name
	if (argc>1) {
	strcpy(IniFileName, argv[1]);
	}
	else {
	strcpy(IniFileName, "Tester.ini");
	}
	strcpy(IniFullName, MyGetCurrentDirectory());
	strcat(IniFullName, "\\");
	strcat(IniFullName, IniFileName);
	*/

	//strcpy(IniFileName, MyGetCurrentDirectory()); strcat(IniFileName, "\\"); strcat(IniFileName, "Tester.ini");

	//-- Load Parameters

	//-- Tester parameters 
	if (getParam(fParms, "Tester.SimulationLength", &fParms.SimulationLength) < 0)	return -1;
	if (getParam(fParms, "Tester.SimulationStart", fParms.SimulationStart) < 0)		return -1;
	if (getParam(fParms, "Forecaster.Engine", &EngineInfo.EngineType, enumlist) < 0)	return -1;


	if (getParam(fParms, "Tester.DoTraining", &fParms.DoTraining) < 0)			return -1;
	if (getParam(fParms, "Tester.HaveFutureData", &fParms.HaveFutureData) < 0)		return -1;

	//-- Tester Log Parameters
	if (getParam(fParms, "Forecaster.DebugLevel", &fParms.DebugParms.DebugLevel) < 0)				return -1;
	if (getParam(fParms, "Forecaster.DebugFileName", fParms.DebugParms.fName) < 0)					return -1;
	if (getParam(fParms, "Forecaster.DebugFilePath", fParms.DebugParms.fPath) < 0)					return -1;
	if (getParam(fParms, "Forecaster.ThreadSafeLogging", &fParms.DebugParms.ThreadSafeLogging) < 0)	return -1;

	//-- Tester Results (MSE,Run) destination DB parameters
	tDBConnection LogDBInfo;
	if (getParam(fParms, "Results.SaveMSE", &fParms.DebugParms.SaveMSE) < 0)					return -1;
	if (getParam(fParms, "Results.SaveRUN", &fParms.DebugParms.SaveRun) < 0)					return -1;
	if (getParam(fParms, "Results.SaveInternals", &fParms.DebugParms.SaveInternals) < 0)		return -1;
	if (getParam(fParms, "Results.Destination", &fParms.DebugParms.DebugDest, enumlist) < 0)	return -1;
	if (getParam(fParms, "Results.DBUser", LogDBInfo.DBUser) < 0)								return -1;
	if (getParam(fParms, "Results.DBPassword", LogDBInfo.DBPassword) < 0)						return -1;
	if (getParam(fParms, "Results.DBConnString", LogDBInfo.DBConnString) < 0)					return -1;
	LogDBInfo.DBCtx = NULL;
	fParms.DebugParms.DebugDB = &LogDBInfo;

	//-- Tester Data Source parameters
	fParms.FXDBInfo.BarDataType = MallocArray<int>(BARDATATYPES);
	fParms.DataSourceFileInfo.FileDataSet = MallocArray<int>(MAXDATASETS);
	if (getParam(fParms, "DataSource.SourceType", &fParms.DataParms.DataSourceType, enumlist) < 0)		return -1;
	if (fParms.DataParms.DataSourceType == SOURCE_DATA_FROM_FXDB) {
		if (getParam(fParms, "DataSource.DBConn.DBUser", fParms.FXDBInfo.FXDB.DBUser) < 0)				return -1;
		if (getParam(fParms, "DataSource.DBConn.DBPassword", fParms.FXDBInfo.FXDB.DBPassword) < 0)		return -1;
		if (getParam(fParms, "DataSource.DBConn.DBConnString", fParms.FXDBInfo.FXDB.DBConnString) < 0)	return -1;
		fParms.FXDBInfo.FXDB.DBCtx = NULL;
		if (getParam(fParms, "DataSource.Symbol", fParms.FXDBInfo.Symbol) < 0)							return -1;
		if (getParam(fParms, "DataSource.TimeFrame", fParms.FXDBInfo.TimeFrame) < 0)						return -1;
		if (getParam(fParms, "DataSource.IsFilled", &fParms.FXDBInfo.IsFilled) < 0)						return -1;
		//-- bardatatypes, fParms.DataParms->DatasetsCount...
		fParms.DataParms.DatasetsCount = getParam(fParms, "DataSource.BarDataTypes", &fParms.FXDBInfo.BarDataType, enumlist); if (fParms.DataParms.DatasetsCount < 0) return -1;
		fParms.FXDBInfo.BarDataTypeCount = fParms.DataParms.DatasetsCount;
		strcpy(fParms.DataSourceFileInfo.FileName, "");
		fParms.DataParms.DataSource = &fParms.FXDBInfo;
	}
	else {
		if (getParam(fParms, "DataSource.FileName", fParms.DataSourceFileInfo.FileName) < 0)			return -1;
		fParms.DataParms.DatasetsCount = getParam(fParms, "DataSource.FileDatasets", &fParms.DataSourceFileInfo.FileDataSet);
		strcpy(fParms.FXDBInfo.Symbol, "");
		strcpy(fParms.FXDBInfo.TimeFrame, "");
		fParms.FXDBInfo.IsFilled = 0;
		fParms.FXDBInfo.BarDataTypeCount = 0;
		fParms.DataSourceFileInfo.FileDataSetsCount = fParms.DataParms.DatasetsCount;
		fParms.DataParms.DataSource = &fParms.DataSourceFileInfo;
	}
	
	//-- Tester Data Shape parameters 		
	if (fParms.DoTraining == 1) {
		//-- If I'm Training, then I need these as input
		if (getParam(fParms, "DataParms.HistoryLen", &fParms.DataParms.HistoryLen) < 0)								return -1;
		if (getParam(fParms, "DataParms.SampleLen", &fParms.DataParms.SampleLen) < 0)								return -1;
		if (getParam(fParms, "DataParms.PredictionLen", &fParms.DataParms.PredictionLen) < 0)						return -1;
		if (getParam(fParms, "DataParms.ValidationShift", &fParms.DataParms.ValidationShift) < 0)					return -1;
		if (getParam(fParms, "DataParms.DataTransformation", &fParms.DataParms.DataTransformation, enumlist) < 0)	return -1;
		if (getParam(fParms, "DataParms.WiggleRoom", &fParms.DataParms.wiggleRoom) < 0)								return -1;
	}
	else {
		//-- If I'm using a saved engine, then I get these from DB
		fParms.SavedEngine.EngineType = fParms.EngineParms.EngineType;
		if (getParam(fParms, "SavedEngine.ProcessId", &fParms.SavedEngine.ProcessId) < 0)	return -1;
		if (getParam(fParms, "SavedEngine.ThreadId", &fParms.SavedEngine.ThreadId) < 0)	return -1;
		if (LoadDataShape(&fParms.DebugParms, &LogDBInfo, &fParms.SavedEngine, &fParms.DataParms) != 0)	return -1;
		fParms.DataParms.ValidationShift = 0;
	}
	fParms.DataParms.SampleCount = fParms.DataParms.HistoryLen - fParms.DataParms.SampleLen;

	
	//-- 4. set TSFs
	int useTSF;
	if (getParam(fParms, "TestData.UseTSFeatures", &useTSF) < 0) return -1;
	if (useTSF > 0) {
		if (getParam(fParms, "TestData.TSFcnt", &fParms.EngineParms.TSFcnt) < 0)						return -1;
		if (getParam(fParms, "TestData.TSFeatures", fParms.EngineParms.TSFid, enumlist) < 0)			return -1;
	}
	else {
		fParms.EngineParms.TSFcnt = 0;
	}

	//-- Load Engine Parameters
	switch (EngineInfo.EngineType) {
	case ENGINE_NN:
		EngineInfo.CoreSpecs = Malloc_CoreSpecs(EngineInfo.LayersCount, EngineInfo.CoresCount);

		NNInfo[0].InputCount = fParms.DataParms.SampleLen;
		NNInfo[0].OutputCount = fParms.DataParms.PredictionLen;

		if (getParam(fParms, "NNInfo.UseContext", &NNInfo[0].UseContext) < 0)							return -1;
		if (getParam(fParms, "NNInfo.TrainingProtocol", &NNInfo[0].TrainingProtocol, enumlist) < 0)		return -1;
		if (getParam(fParms, "NNInfo.BP_Algo", &NNInfo[0].BP_Algo, enumlist) < 0)						return -1;
		if (getParam(fParms, "NNInfo.ActivationFunction", &NNInfo[0].ActivationFunction, enumlist) < 0)	return -1;
		if (getParam(fParms, "NNInfo.StopAtDivergence", &NNInfo[0].StopAtDivergence) < 0)				return -1;
		if (getParam(fParms, "NNInfo.MaxEpochs", &NNInfo[0].MaxEpochs) < 0)								return -1;
		if (getParam(fParms, "NNInfo.LearningRate", &NNInfo[0].LearningRate) < 0)						return -1;
		if (getParam(fParms, "NNInfo.LearningMomentum", &NNInfo[0].LearningMomentum) < 0)				return -1;
		if (getParam(fParms, "NNInfo.TargetMSE", &NNInfo[0].TargetMSE) < 0)								return -1;
		if (getParam(fParms, "NNInfo.HCPbeta", &NNInfo[0].HCPbeta) < 0)									return -1;
		if (getParam(fParms, "NNInfo.mu", &NNInfo[0].mu) < 0)											return -1;
		if (getParam(fParms, "NNInfo.LevelRatios", &NNInfo[0].LevelRatioS[0]) < 0)						return -1;
		setNNTopology(NNInfo);

		EngineInfo.CoreSpecs[0][0] = &NNInfo;

		break;
	case ENGINE_WNN:

		if (getParam(fParms, "WNNInfo.WaveletType", WNNInfo.WaveletType) < 0)		return -1;
		if (getParam(fParms, "WNNInfo.DecompLevel", &WNNInfo.DecompLevel) < 0)		return -1;
		EngineInfo.EngineParms = (void*)&WNNInfo;

		EngineInfo.LayersCount = 2;
		EngineInfo.CoresCount[0] = WNNInfo.DecompLevel + 1;
		EngineInfo.CoresCount[1] = 1;
		EngineInfo.TotalCoresCount = WNNInfo.DecompLevel + 2;

		EngineInfo.CoreSpecs = Malloc_CoreSpecs(EngineInfo.LayersCount, EngineInfo.CoresCount);
		WNN_NNInfo = Malloc_WNN_NNInfo(EngineInfo.LayersCount, EngineInfo.CoresCount);

		WNN_NNInfo[0][0]->InputCount = fParms.DataParms.SampleLen;
		WNN_NNInfo[0][0]->OutputCount = fParms.DataParms.PredictionLen;
		if (getParam(fParms, "WNNInfo.L0.UseContext", &WNN_NNInfo[0][0]->UseContext) <0)							return -1;
		if (getParam(fParms, "WNNInfo.L0.TrainingProtocol", &WNN_NNInfo[0][0]->TrainingProtocol, enumlist) <0)		return -1;
		if (getParam(fParms, "WNNInfo.L0.BP_Algo", &WNN_NNInfo[0][0]->BP_Algo, enumlist) <0)						return -1;
		if (getParam(fParms, "WNNInfo.L0.ActivationFunction", &WNN_NNInfo[0][0]->ActivationFunction, enumlist) <0)	return -1;
		if (getParam(fParms, "WNNInfo.L0.StopAtDivergence", &WNN_NNInfo[0][0]->StopAtDivergence) <0)				return -1;
		if (getParam(fParms, "WNNInfo.L0.MaxEpochs", &WNN_NNInfo[0][0]->MaxEpochs) <0)								return -1;
		if (getParam(fParms, "WNNInfo.L0.LearningRate", &WNN_NNInfo[0][0]->LearningRate) <0)						return -1;
		if (getParam(fParms, "WNNInfo.L0.LearningMomentum", &WNN_NNInfo[0][0]->LearningMomentum) <0)				return -1;
		if (getParam(fParms, "WNNInfo.L0.TargetMSE", &WNN_NNInfo[0][0]->TargetMSE) <0)								return -1;
		if (getParam(fParms, "WNNInfo.L0.HCPbeta", &WNN_NNInfo[0][0]->HCPbeta) <0)									return -1;
		if (getParam(fParms, "WNNInfo.L0.mu", &WNN_NNInfo[0][0]->mu) <0)											return -1;
		if (getParam(fParms, "WNNInfo.L0.LevelRatios", &WNN_NNInfo[0][0]->LevelRatioS[0]) <0)						return -1;
		setNNTopology(WNN_NNInfo[0][0]);

		//-- at level 0, copy core0 into all other cores
		for (int c = 0; c < EngineInfo.CoresCount[0]; c++) {
			EngineInfo.CoreSpecs[0][c] = WNN_NNInfo[0][0];
		}

		WNN_NNInfo[1][0]->InputCount = EngineInfo.CoresCount[0] * fParms.DataParms.PredictionLen + EngineInfo.TSFcnt;
		WNN_NNInfo[1][0]->OutputCount = fParms.DataParms.PredictionLen;
		if (getParam(fParms, "WNNInfo.L0.UseContext", &WNN_NNInfo[0][0]->UseContext) <0)							return -1;
		if (getParam(fParms, "WNNInfo.L0.TrainingProtocol", &WNN_NNInfo[0][0]->TrainingProtocol, enumlist) <0)		return -1;
		if (getParam(fParms, "WNNInfo.L0.BP_Algo", &WNN_NNInfo[0][0]->BP_Algo, enumlist) <0)						return -1;
		if (getParam(fParms, "WNNInfo.L0.ActivationFunction", &WNN_NNInfo[0][0]->ActivationFunction, enumlist) <0)	return -1;
		if (getParam(fParms, "WNNInfo.L0.StopAtDivergence", &WNN_NNInfo[0][0]->StopAtDivergence) <0)				return -1;
		if (getParam(fParms, "WNNInfo.L0.MaxEpochs", &WNN_NNInfo[0][0]->MaxEpochs) <0)								return -1;
		if (getParam(fParms, "WNNInfo.L0.LearningRate", &WNN_NNInfo[0][0]->LearningRate) <0)						return -1;
		if (getParam(fParms, "WNNInfo.L0.LearningMomentum", &WNN_NNInfo[0][0]->LearningMomentum) <0)				return -1;
		if (getParam(fParms, "WNNInfo.L0.TargetMSE", &WNN_NNInfo[0][0]->TargetMSE) <0)								return -1;
		if (getParam(fParms, "WNNInfo.L0.HCPbeta", &WNN_NNInfo[0][0]->HCPbeta) <0)									return -1;
		if (getParam(fParms, "WNNInfo.L0.mu", &WNN_NNInfo[0][0]->mu) <0)											return -1;
		if (getParam(fParms, "WNNInfo.L0.LevelRatios", &WNN_NNInfo[0][0]->LevelRatioS[0]) <0)						return -1;
		setNNTopology(WNN_NNInfo[1][0]);

		break;
	case ENGINE_GA:
		EngineInfo.CoreSpecs = Malloc_CoreSpecs(EngineInfo.LayersCount, EngineInfo.CoresCount);

		GAInfo.OutputCount = fParms.DataParms.PredictionLen;
		if (getParam(fParms, "GAInfo.SlidingFactor", &GAInfo.SlidingFactor) < 0)							return -1;
		if (getParam(fParms, "GAInfo.Levels", &GAInfo.Levels) < 0)											return -1;
		if (getParam(fParms, "GAInfo.PopulationSize", &GAInfo.PopulationSize) < 0)							return -1;
		if (getParam(fParms, "GAInfo.MaxGenerations", &GAInfo.MaxGenerations) < 0)							return -1;
		if (getParam(fParms, "GAInfo.TargetFitness", &GAInfo.TargetFitness) < 0)							return -1;
		if (getParam(fParms, "GAInfo.FitnessSkewingFactor", &GAInfo.FitnessSkewingFactor) < 0)				return -1;
		if (getParam(fParms, "GAInfo.FitnessThreshold", &GAInfo.FitnessThreshold) < 0)						return -1;
		if (getParam(fParms, "GAInfo.CrossOverProbability", &GAInfo.CrossOverProbability) < 0)				return -1;
		if (getParam(fParms, "GAInfo.MutationProbability", &GAInfo.MutationProbability) < 0)				return -1;
		if (getParam(fParms, "GAInfo.CrossSelfRate", &GAInfo.CrossSelfRate) < 0)							return -1;
		if (getParam(fParms, "GAInfo.RouletteMaxTries", &GAInfo.RouletteMaxTries) < 0)						return -1;
		if (getParam(fParms, "GAInfo.ADF_Tree_FixedValues_Ratio", &GAInfo.ADF_Tree_FixedValues_Ratio) < 0)	return -1;
		if (getParam(fParms, "GAInfo.ADF_Tree_DataPoints_Ratio", &GAInfo.ADF_Tree_DataPoints_Ratio) < 0)	return -1;
		if (getParam(fParms, "GAInfo.ADF_Leaf_FixedValues_Ratio", &GAInfo.ADF_Leaf_FixedValues_Ratio) < 0)	return -1;
		if (getParam(fParms, "GAInfo.MaxReRuns", &GAInfo.MaxReRuns) < 0)									return -1;
		if (getParam(fParms, "GAInfo.BestChrPath", GAInfo.BestChrPath) < 0)								return -1;

		EngineInfo.CoreSpecs[0][0] = (void*)&GAInfo;
		break;
	case ENGINE_SOM:
		EngineInfo.CoreSpecs = Malloc_CoreSpecs(EngineInfo.LayersCount, EngineInfo.CoresCount);
		if (getParam(fParms, "SOMInfo.OutputCount", &SOMInfo.OutputCount) < 0)			return -1;
		if (getParam(fParms, "SOMInfo.OutputWidth", &SOMInfo.OutputWidth) < 0)			return -1;
		if (getParam(fParms, "SOMInfo.MaxEpochs", &SOMInfo.MaxEpochs) < 0)				return -1;
		if (getParam(fParms, "SOMInfo.TDFunction", &SOMInfo.TDFunction, enumlist) < 0)	return -1;
		if (getParam(fParms, "SOMInfo.BaseLR", &SOMInfo.BaseLR) < 0)						return -1;
		if (getParam(fParms, "SOMInfo.LRFunction", &SOMInfo.LRFunction, enumlist) < 0)	return -1;
		SOMInfo.InputCount = fParms.DataParms.SampleLen;
		SOMInfo.BaseTD = SOMInfo.OutputCount;

		EngineInfo.CoreSpecs[0][0] = (void*)&SOMInfo;
		break;
	case ENGINE_SVM:

		SVMInfo.InputCount = fParms.DataParms.SampleLen;
		//SVMInfo.OutputCount = oParms->DataParms.PredictionLen;
		if (getParam(fParms, "SVMInfo.DebugLevel", &SVMInfo.DebugLevel) < 0)				return -1;
		if (getParam(fParms, "SVMInfo.C", &SVMInfo.C) < 0)									return -1;
		if (getParam(fParms, "SVMInfo.IterToShrink", &SVMInfo.svmIterToShrink) < 0)		return -1;
		if (getParam(fParms, "SVMInfo.MaxEpochs", &SVMInfo.MaxEpochs) < 0)					return -1;
		if (getParam(fParms, "SVMInfo.epsilon", &SVMInfo.epsilon) < 0)						return -1;
		if (getParam(fParms, "SVMInfo.KernelType", &SVMInfo.KernelType, enumlist) < 0)		return -1;
		if (getParam(fParms, "SVMInfo.PolyDegree", &SVMInfo.PolyDegree) < 0)				return -1;
		if (getParam(fParms, "SVMInfo.RBFGamma", &SVMInfo.RBFGamma) < 0)					return -1;
		if (getParam(fParms, "SVMInfo.CoefLin", &SVMInfo.CoefLin) < 0)						return -1;
		if (getParam(fParms, "SVMInfo.CoefConst", &SVMInfo.CoefConst) < 0)					return -1;
		if (getParam(fParms, "SVMInfo.KernelCacheSize", &SVMInfo.KernelCacheSize) < 0)		return -1;
		if (getParam(fParms, "SVMInfo.CustomKernel", SVMInfo.CustomKernel) < 0)			return -1;
		//--
		if (getParam(fParms, "SVMInfo.SlackNorm", &SVMInfo.SlackNorm, enumlist) < 0)				return -1;
		if (getParam(fParms, "SVMInfo.RescalingMethod", &SVMInfo.RescalingMethod, enumlist) < 0)	return -1;
		if (getParam(fParms, "SVMInfo.LossFunction", &SVMInfo.LossFunction, enumlist) < 0)			return -1;
		if (getParam(fParms, "SVMInfo.LearningAlgo", &SVMInfo.LearningAlgo, enumlist) < 0)			return -1;
		if (getParam(fParms, "SVMInfo.NewConstrEtrain", &SVMInfo.NewConstrEtrain) < 0)				return -1;
		if (getParam(fParms, "SVMINfo.CCacheSize", &SVMInfo.CCacheSize) < 0)						return -1;
		if (getParam(fParms, "SVMInfo.BatchSize", &SVMInfo.BatchSize) < 0)							return -1;
		if (getParam(fParms, "SVMInfo.NewVarSinQP", &SVMInfo.NewVarSinQP) < 0)						return -1;

		EngineInfo.CoreSpecs = Malloc_CoreSpecs(EngineInfo.LayersCount, EngineInfo.CoresCount);
		EngineInfo.CoreSpecs[0][0] = (void*)&SVMInfo;
		break;
	case ENGINE_XIE:
		SVMInfo.InputCount = fParms.DataParms.SampleLen;

		if (getParam(fParms, "XIEInfo.SVM.DebugLevel", &SVMInfo.DebugLevel) < 0)				return -1;
		if (getParam(fParms, "XIEInfo.SVM.C", &SVMInfo.C) < 0)									return -1;
		if (getParam(fParms, "XIEInfo.SVM.IterToShrink", &SVMInfo.svmIterToShrink) < 0)		return -1;
		if (getParam(fParms, "XIEInfo.SVM.MaxEpochs", &SVMInfo.MaxEpochs) < 0)					return -1;
		if (getParam(fParms, "XIEInfo.SVM.epsilon", &SVMInfo.epsilon) < 0)						return -1;
		if (getParam(fParms, "XIEInfo.SVM.KernelType", &SVMInfo.KernelType, enumlist) < 0)		return -1;
		if (getParam(fParms, "XIEInfo.SVM.PolyDegree", &SVMInfo.PolyDegree) < 0)				return -1;
		if (getParam(fParms, "XIEInfo.SVM.RBFGamma", &SVMInfo.RBFGamma) < 0)					return -1;
		if (getParam(fParms, "XIEInfo.SVM.CoefLin", &SVMInfo.CoefLin) < 0)						return -1;
		if (getParam(fParms, "XIEInfo.SVM.CoefConst", &SVMInfo.CoefConst) < 0)					return -1;
		if (getParam(fParms, "XIEInfo.SVM.KernelCacheSize", &SVMInfo.KernelCacheSize) < 0)		return -1;
		if (getParam(fParms, "XIEInfo.SVM.CustomKernel", SVMInfo.CustomKernel) < 0)			return -1;
		//--
		if (getParam(fParms, "XIEInfo.SVM.SlackNorm", &SVMInfo.SlackNorm, enumlist) < 0)				return -1;
		if (getParam(fParms, "XIEInfo.SVM.RescalingMethod", &SVMInfo.RescalingMethod, enumlist) < 0)	return -1;
		if (getParam(fParms, "XIEInfo.SVM.LossFunction", &SVMInfo.LossFunction, enumlist) < 0)			return -1;
		if (getParam(fParms, "XIEInfo.SVM.LearningAlgo", &SVMInfo.LearningAlgo, enumlist) < 0)			return -1;
		if (getParam(fParms, "XIEInfo.SVM.NewConstrEtrain", &SVMInfo.NewConstrEtrain) < 0)				return -1;
		if (getParam(fParms, "XIEInfo.SVM.CCacheSize", &SVMInfo.CCacheSize) < 0)						return -1;
		if (getParam(fParms, "XIEInfo.SVM.BatchSize", &SVMInfo.BatchSize) < 0)							return -1;
		if (getParam(fParms, "XIEInfo.SVM.NewVarSinQP", &SVMInfo.NewVarSinQP) < 0)						return -1;
		//--
		NNInfo[0].InputCount = fParms.DataParms.SampleLen;
		NNInfo[0].OutputCount = fParms.DataParms.PredictionLen;
		if (getParam(fParms, "XIEInfo.NN0.UseContext", &NNInfo[0].UseContext) < 0)								return -1;
		if (getParam(fParms, "XIEInfo.NN0.TrainingProtocol", &NNInfo[0].TrainingProtocol, enumlist) < 0)		return -1;
		if (getParam(fParms, "XIEInfo.NN0.BP_Algo", &NNInfo[0].BP_Algo, enumlist) < 0)							return -1;
		if (getParam(fParms, "XIEInfo.NN0.ActivationFunction", &NNInfo[0].ActivationFunction, enumlist) < 0)	return -1;
		if (getParam(fParms, "XIEInfo.NN0.StopAtDivergence", &NNInfo[0].StopAtDivergence) < 0)					return -1;
		if (getParam(fParms, "XIEInfo.NN0.MaxEpochs", &NNInfo[0].MaxEpochs) < 0)								return -1;
		if (getParam(fParms, "XIEInfo.NN0.LearningRate", &NNInfo[0].LearningRate) < 0)							return -1;
		if (getParam(fParms, "XIEInfo.NN0.LearningMomentum", &NNInfo[0].LearningMomentum) < 0)					return -1;
		if (getParam(fParms, "XIEInfo.NN0.TargetMSE", &NNInfo[0].TargetMSE) < 0)								return -1;
		if (getParam(fParms, "XIEInfo.NN0.HCPbeta", &NNInfo[0].HCPbeta) < 0)									return -1;
		if (getParam(fParms, "XIEInfo.NN0.mu", &NNInfo[0].mu) < 0)												return -1;
		if (getParam(fParms, "XIEInfo.NN0.LevelRatios", &NNInfo[0].LevelRatioS[0]) < 0)						return -1;
		setNNTopology(&NNInfo[0]);
		//--
		NNInfo[1].InputCount = 2 * fParms.DataParms.PredictionLen;
		NNInfo[1].OutputCount = fParms.DataParms.PredictionLen;
		if (getParam(fParms, "XIEInfo.NN1.UseContext", &NNInfo[1].UseContext) < 0)								return -1;
		if (getParam(fParms, "XIEInfo.NN1.TrainingProtocol", &NNInfo[1].TrainingProtocol, enumlist) < 0)		return -1;
		if (getParam(fParms, "XIEInfo.NN1.BP_Algo", &NNInfo[1].BP_Algo, enumlist) < 0)							return -1;
		if (getParam(fParms, "XIEInfo.NN1.ActivationFunction", &NNInfo[1].ActivationFunction, enumlist) < 0)	return -1;
		if (getParam(fParms, "XIEInfo.NN1.StopAtDivergence", &NNInfo[1].StopAtDivergence) < 0)					return -1;
		if (getParam(fParms, "XIEInfo.NN1.MaxEpochs", &NNInfo[1].MaxEpochs) < 0)								return -1;
		if (getParam(fParms, "XIEInfo.NN1.LearningRate", &NNInfo[1].LearningRate) < 0)							return -1;
		if (getParam(fParms, "XIEInfo.NN1.LearningMomentum", &NNInfo[1].LearningMomentum) < 0)					return -1;
		if (getParam(fParms, "XIEInfo.NN1.TargetMSE", &NNInfo[1].TargetMSE) < 0)								return -1;
		if (getParam(fParms, "XIEInfo.NN1.HCPbeta", &NNInfo[1].HCPbeta) < 0)									return -1;
		if (getParam(fParms, "XIEInfo.NN1.mu", &NNInfo[1].mu) < 0)												return -1;
		if (getParam(fParms, "XIEInfo.NN1.LevelRatios", &NNInfo[1].LevelRatioS[0]) < 0)						return -1;
		setNNTopology(&NNInfo[1]);
		//--
		EngineInfo.LayersCount = 2;
		EngineInfo.CoresCount[0] = 2;
		EngineInfo.CoresCount[1] = 1;
		EngineInfo.TotalCoresCount = 3;

		EngineInfo.CoreSpecs = Malloc_CoreSpecs(EngineInfo.LayersCount, EngineInfo.CoresCount);
		EngineInfo.CoreSpecs[0][0] = &SVMInfo;
		EngineInfo.CoreSpecs[0][1] = &NNInfo[0];
		EngineInfo.CoreSpecs[1][0] = &NNInfo[1];

		break;
	}



	//-- I - if BP_QING, override PredictionLen. This is needed to load the correct amount of future data, so not to screw up Scaling of WholeData in GetForecast()
	if (NNInfo[0].BP_Algo == BP_QING) fParms.DataParms.PredictionLen = fParms.DataParms.SampleLen;
	if (NNInfo[1].BP_Algo == BP_QING) fParms.DataParms.PredictionLen = fParms.DataParms.SampleLen;

	//-- 0. mallocs - Datasource
	double*  BaseValH = (double*)malloc(fParms.DataParms.DatasetsCount * sizeof(double));	//-- needed for DELTA transformation
	double*  BaseValV = (double*)malloc(fParms.DataParms.DatasetsCount * sizeof(double));	//-- needed for DELTA transformation
	double*  BaseBW = (double*)malloc(fParms.DataParms.DatasetsCount * sizeof(double));	//-- needed for DELTA transformation
	double** HistoryData = (double**)malloc(fParms.DataParms.DatasetsCount * sizeof(double*)); for (i = 0; i < fParms.DataParms.DatasetsCount; i++) (double*)HistoryData[i] = (double*)malloc(fParms.DataParms.HistoryLen * sizeof(double));
	double** HistoryBarW = (double**)malloc(fParms.DataParms.DatasetsCount * sizeof(double*)); for (i = 0; i < fParms.DataParms.DatasetsCount; i++) (double*)HistoryBarW[i] = (double*)malloc(fParms.DataParms.HistoryLen * sizeof(double));
	double** FutureData = (double**)malloc(fParms.DataParms.DatasetsCount * sizeof(double*)); for (i = 0; i < fParms.DataParms.DatasetsCount; i++) (double*)FutureData[i] = (double*)malloc(fParms.DataParms.PredictionLen * sizeof(double));
	double** FutureBarW = (double**)malloc(fParms.DataParms.DatasetsCount * sizeof(double*)); for (i = 0; i < fParms.DataParms.DatasetsCount; i++) (double*)FutureBarW[i] = (double*)malloc(fParms.DataParms.PredictionLen * sizeof(double));
	double** WholeData = (double**)malloc(fParms.DataParms.DatasetsCount * sizeof(double*)); for (i = 0; i < fParms.DataParms.DatasetsCount; i++) (double*)WholeData[i] = (double*)malloc((fParms.DataParms.HistoryLen + fParms.DataParms.PredictionLen) * sizeof(double));
	double** WholeBarW = (double**)malloc(fParms.DataParms.DatasetsCount * sizeof(double*)); for (i = 0; i < fParms.DataParms.DatasetsCount; i++) (double*)WholeBarW[i] = (double*)malloc((fParms.DataParms.HistoryLen + fParms.DataParms.PredictionLen) * sizeof(double));
	double** ForecastData = (double**)malloc(fParms.DataParms.DatasetsCount * sizeof(double*)); for (i = 0; i < fParms.DataParms.DatasetsCount; i++) (double*)ForecastData[i] = (double*)malloc(fParms.DataParms.PredictionLen * sizeof(double));
	double** ValidationData = (double**)malloc(fParms.DataParms.DatasetsCount * sizeof(double*)); for (i = 0; i < fParms.DataParms.DatasetsCount; i++) (double*)ValidationData[i] = (double*)malloc(fParms.DataParms.HistoryLen * sizeof(double));

	//BOOL f = HeapSetInformation(NULL, HeapEnableTerminationOnCorruption, NULL, 0);

	//-- 1. Load Training_Start[]
	char** TrainingStart = (char**)malloc(fParms.SimulationLength * sizeof(char*)); for (i = 0; i < fParms.SimulationLength; i++) TrainingStart[i] = (char*)malloc(12 + 1);
	if (fParms.DataParms.DataSourceType == SOURCE_DATA_FROM_FXDB) {
		if (GetDates_FXDB(&fParms.DebugParms, &FXDBInfo, fParms.SimulationStart, fParms.SimulationLength, TrainingStart) != 0) return -1;
	}
	else {
		if (GetDates_CSV(&fParms.DebugParms, &DataSourceFileInfo, fParms.SimulationStart, fParms.SimulationLength, TrainingStart) != 0) return -1;
	}

	//-- 3. Prepare, Train, Run for each Training_Start
	int pid = GetCurrentProcessId();
	for (i = 0; i < fParms.SimulationLength; i++) {

		//-- 3.1. Get raw data.
		if (fParms.DataParms.DataSourceType == SOURCE_DATA_FROM_FXDB) {
			if (LoadData_FXDB(&fParms.DebugParms, &FXDBInfo, fParms.DataParms.HistoryLen, fParms.DataParms.PredictionLen, TrainingStart[i], fParms.DataParms.ValidationShift, fParms.DataParms.DatasetsCount, HistoryData, HistoryBarW, ValidationData, FutureData, FutureBarW, WholeData, WholeBarW, BaseValH, BaseValV, BaseBW) != 0) return -1;
		}
		else {
			if (LoadData_CSV(&fParms.DebugParms, &DataSourceFileInfo, fParms.DataParms.HistoryLen, fParms.DataParms.PredictionLen, TrainingStart[i], fParms.DataParms.ValidationShift, fParms.DataParms.DatasetsCount, HistoryData, HistoryBarW, ValidationData, FutureData, FutureBarW, WholeData, WholeBarW) != 0) return -1;
		}

		//-- 3.2 Do the Training, and get the Forecast
		system("cls");
		printf("\nProcessId=%d ; TestId=%d, TrainingStart=%s ; Start Time: %s\n", pid, i, TrainingStart[i], timestamp());

		if (getForecast(&fParms.DebugParms, &LogDBInfo, i, &fParms.DataParms, fParms.DoTraining, &SavedEngine, &EngineInfo, HistoryData, BaseValH, HistoryBarW, ValidationData, BaseValV, fParms.HaveFutureData, FutureData, FutureBarW, ForecastData) != 0) return -1;
		//__declspec(dllexport) int getForecast(tDebugInfo* pDebugParms, tDBConnection* pLogDB, int pTestId, tDataShape* pDataParms, int pDoTraining, tEngineHandle* pSavedEngine, tEngineDef* pEngineParms, double** pHistoryData, double* pHistoryBaseVal, double** pHistoryBW, double** pValidationData, double* pValidationBaseVal, int haveActualFuture, double** pFutureData, double** pFutureBW, double** oPredictedData)
	}

	// stop timer, compute the elapsed time
	QueryPerformanceCounter(&time_end);
	elapsedTime = (time_end.QuadPart - time_start.QuadPart) * 1000.0 / frequency.QuadPart;
	ms2ts(elapsedTime, elapsedTimeS);

	//-- 2. Save Tester Log
	//if (WritefParms.DebugParms(&fParms.DebugParms, SimulationLength, SimulationStart, elapsedTime/1000, EngineInfo.EngineType, DoTraining, HaveFutureData, DSrcType, DataSourceFileInfo.FileName) != 0) return -1;
	if (SaveTestLog_TesterParms(&fParms.DebugParms, fParms.SimulationLength, fParms.SimulationStart, elapsedTime, EngineInfo.EngineType, fParms.DoTraining, fParms.HaveFutureData, fParms.DataParms.DataSourceType, ((tFileData*)fParms.DataParms.DataSource)->FileName) != 0) return -1;
	LogCommit(&fParms.DebugParms);



	//-- free(s)

	Free_CoreSpecs(EngineInfo.LayersCount, EngineInfo.CoresCount, EngineInfo.CoreSpecs);

	if (WNN_NNInfo != nullptr) Free_WNNInfo(EngineInfo.LayersCount, EngineInfo.CoresCount, WNN_NNInfo);

	free(BaseValH); free(BaseValV); free(BaseBW);
	for (i = 0; i < fParms.DataParms.DatasetsCount; i++) {
		free(HistoryData[i]);
		free(HistoryBarW[i]);
		free(FutureData[i]);
		free(FutureBarW[i]);
		free(WholeData[i]);
		free(WholeBarW[i]);
		free(ForecastData[i]);
		free(ValidationData[i]);
	}
	free(HistoryData);
	free(HistoryBarW);
	free(FutureData);
	free(FutureBarW);
	free(WholeData);
	free(WholeBarW);
	free(ForecastData);
	free(ValidationData);
	for (i = 0; i < fParms.SimulationLength; i++) free(TrainingStart[i]);
	free(TrainingStart);

	//--
	gotoxy(0, EngineInfo.TotalCoresCount*fParms.DataParms.DatasetsCount + i + 4);
	printf("Elapsed Time: %s\n", elapsedTimeS);
	system("pause");

	return 0;
}


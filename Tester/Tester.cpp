#include <vld.h>

#include "stdafx.h"

int main(int argc, char** argv) {
	int i;

	//	char IniFileName[MAX_PATH];
	char** TrainingStart;

	//-- timer init
	LARGE_INTEGER frequency;			// ticks per second
	LARGE_INTEGER time_start, time_end; // ticks
	double elapsedTime; char elapsedTimeS[30];
	// get ticks per second
	QueryPerformanceFrequency(&frequency);
	// start timer
	QueryPerformanceCounter(&time_start);
	//--

	// Forecasting Parameters initialization. 
	tForecastParms fParms;
	//-- a. set overrides from Command Line 
	if (CLProcess(argc, argv, &fParms) != 0) return -1;
	//-- b. process ini file
	if (ForecastParamLoader(&fParms) <0) return -1;

	//-- Tester-specific parameters
	if (getParam(&fParms, "Tester.SimulationLength", &fParms.SimulationLength) < 0)		return -1;
	if (getParam(&fParms, "Tester.SimulationStart", &fParms.SimulationStart[0]) < 0)		return -1;

	//-- 0. mallocs
	double*  BaseValH = MallocArray<double>(fParms.DataParms.DatasetsCount);	//-- needed for DELTA transformation
	double*  BaseValV = MallocArray<double>(fParms.DataParms.DatasetsCount);	//-- needed for DELTA transformation
	double*  BaseBW = MallocArray<double>(fParms.DataParms.DatasetsCount);	//-- needed for DELTA transformation
	double** HistoryData = MallocArray<double>(fParms.DataParms.DatasetsCount, fParms.DataParms.HistoryLen);
	double** HistoryBarW = MallocArray<double>(fParms.DataParms.DatasetsCount, fParms.DataParms.HistoryLen);
	double** FutureData = MallocArray<double>(fParms.DataParms.DatasetsCount, fParms.DataParms.PredictionLen);
	double** FutureBarW = MallocArray<double>(fParms.DataParms.DatasetsCount, fParms.DataParms.PredictionLen);
	double** WholeData = MallocArray<double>(fParms.DataParms.DatasetsCount, fParms.DataParms.HistoryLen + fParms.DataParms.PredictionLen);
	double** WholeBarW = MallocArray<double>(fParms.DataParms.DatasetsCount, fParms.DataParms.HistoryLen + fParms.DataParms.PredictionLen);
	double** ForecastData = MallocArray<double>(fParms.DataParms.DatasetsCount, fParms.DataParms.PredictionLen);
	double** ValidationData = MallocArray<double>(fParms.DataParms.DatasetsCount, fParms.DataParms.HistoryLen);

	//BOOL f = HeapSetInformation(NULL, HeapEnableTerminationOnCorruption, NULL, 0);

	//-- 1. Load Training_Start[]
	TrainingStart = (char**)malloc(fParms.SimulationLength * sizeof(char*)); for (i = 0; i < fParms.SimulationLength; i++) TrainingStart[i] = (char*)malloc(12 + 1);
	if (fParms.DataParms.DataSourceType == SOURCE_DATA_FROM_FXDB) {
		if (GetDates_FXDB(&fParms.DebugParms, &fParms.FXDBInfo, fParms.SimulationStart, fParms.SimulationLength, TrainingStart) != 0) return -1;
	}
	else {
		if (GetDates_CSV(&fParms.DebugParms, &fParms.DataSourceFileInfo, fParms.SimulationStart, fParms.SimulationLength, TrainingStart) != 0) return -1;
	}

	//-- 3. Prepare, Train, Run for each Training_Start
	int pid = GetCurrentProcessId();
	for (i = 0; i < fParms.SimulationLength; i++) {

		//-- 3.1. Get raw data.
		if (fParms.DataParms.DataSourceType == SOURCE_DATA_FROM_FXDB) {
			if (LoadData_FXDB(&fParms.DebugParms, &fParms.FXDBInfo, fParms.DataParms.HistoryLen, fParms.DataParms.PredictionLen, TrainingStart[i], fParms.DataParms.ValidationShift, fParms.DataParms.DatasetsCount, HistoryData, HistoryBarW, ValidationData, FutureData, FutureBarW, WholeData, WholeBarW, BaseValH, BaseValV, BaseBW) != 0) return -1;
		}
		else {
			if (LoadData_CSV(&fParms.DebugParms, &fParms.DataSourceFileInfo, fParms.DataParms.HistoryLen, fParms.DataParms.PredictionLen, TrainingStart[i], fParms.DataParms.ValidationShift, fParms.DataParms.DatasetsCount, HistoryData, HistoryBarW, ValidationData, FutureData, FutureBarW, WholeData, WholeBarW) != 0) return -1;
		}

		//-- 3.2 Do the Training, and get the Forecast
		system("cls");
		printf("\nProcessId=%d ; TestId=%d, TrainingStart=%s ; Start Time: %s\n", pid, i, TrainingStart[i], timestamp());

		if (getForecast(argc, argv, i, HistoryData, BaseValH, HistoryBarW, ValidationData, BaseValV, fParms.HaveFutureData, FutureData, FutureBarW, ForecastData) != 0) return -1;

	}

	// stop timer, compute the elapsed time
	QueryPerformanceCounter(&time_end);
	elapsedTime = (time_end.QuadPart - time_start.QuadPart) * 1000.0 / frequency.QuadPart;
	ms2ts(elapsedTime, elapsedTimeS);

	//-- 2. Save Tester Log
	//if (WriteTesterLog(&TesterLog, SimulationLength, SimulationStart, elapsedTime/1000, EngineInfo.EngineType, DoTraining, HaveFutureData, DSrcType, DataSourceFileInfo.FileName) != 0) return -1;
	if (SaveTestLog_TesterParms(&fParms.DebugParms, fParms.SimulationLength, fParms.SimulationStart, elapsedTime, fParms.EngineParms.EngineType, fParms.DoTraining, fParms.HaveFutureData, fParms.DataParms.DataSourceType, ((tFileData*)fParms.DataParms.DataSource)->FileName) != 0) return -1;
	LogCommit(&fParms.DebugParms);



	//-- free(s)
	ForecastParamFree(&fParms);

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
	gotoxy(0, fParms.EngineParms.TotalCoresCount*fParms.DataParms.DatasetsCount + i + 4);
	printf("Elapsed Time: %s\n", elapsedTimeS);
	system("pause");

	return 0;
}

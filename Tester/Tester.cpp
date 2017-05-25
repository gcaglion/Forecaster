//#include <vld.h>

#include <Windows.h>
#include <MyParamMgr.h>
#include <MyTimeSeries.h>
#include <MyForecast.h>

int main(int argc, char** argv) {
	int i;

	//	char IniFileName[MAX_PATH];
	char** TrainingStart;

	//-- timer init
	LARGE_INTEGER frequency;			// ticks per second
	LARGE_INTEGER time_start, time_end; // ticks
	double elapsedTime=0; char elapsedTimeS[30];
	// get ticks per second
	QueryPerformanceFrequency(&frequency);
	// start timer
	QueryPerformanceCounter(&time_start);
	//--

	// Forecasting Parameters initialization. 
	cParamsSource* fp = new cParamsSource(argc, argv);
	if (fp->Process(FPCLI) <0) return -1;

	//-- 0. mallocs
	double*  BaseValH = MallocArray<double>(fp->DataParms->DatasetsCount);	//-- needed for DELTA transformation
	double*  BaseValV = MallocArray<double>(fp->DataParms->DatasetsCount);	//-- needed for DELTA transformation
	double*  BaseBW = MallocArray<double>(fp->DataParms->DatasetsCount);	//-- needed for DELTA transformation
	double** HistoryData = MallocArray<double>(fp->DataParms->DatasetsCount, fp->DataParms->HistoryLen);
	double** HistoryBarW = MallocArray<double>(fp->DataParms->DatasetsCount, fp->DataParms->HistoryLen);
	double** FutureData = MallocArray<double>(fp->DataParms->DatasetsCount, fp->DataParms->PredictionLen);
	double** FutureBarW = MallocArray<double>(fp->DataParms->DatasetsCount, fp->DataParms->PredictionLen);
	double** WholeData = MallocArray<double>(fp->DataParms->DatasetsCount, fp->DataParms->HistoryLen + fp->DataParms->PredictionLen);
	double** WholeBarW = MallocArray<double>(fp->DataParms->DatasetsCount, fp->DataParms->HistoryLen + fp->DataParms->PredictionLen);
	double** ForecastData = MallocArray<double>(fp->DataParms->DatasetsCount, fp->DataParms->PredictionLen);
	double** ValidationData = MallocArray<double>(fp->DataParms->DatasetsCount, fp->DataParms->HistoryLen);

	//BOOL f = HeapSetInformation(NULL, HeapEnableTerminationOnCorruption, NULL, 0);

	int pid = GetCurrentProcessId();

	//-- 1. Load Training_Start[]
	TrainingStart = (char**)malloc(fp->SimulationLength * sizeof(char*)); for (i = 0; i < fp->SimulationLength; i++) TrainingStart[i] = (char*)malloc(12 + 1);
	if (GetDates(fp->DebugParms, fp->FXDBInfo, fp->SimulationStart, fp->SimulationLength, TrainingStart) != 0) return -1;

	//-- 2. Save Tester Log (elapsedTime is 0)
	if (SaveTesterParms(fp->DebugParms, pid, fp->SimulationLength, fp->SimulationStart, elapsedTime, fp->DoTraining, fp->HaveFutureData) != 0) return -1;

	//-- 3. Prepare, Train, Run for each Training_Start
	for (i = 0; i < fp->SimulationLength; i++) {

		//-- 3.1. Get raw data.
		if (LoadData(fp->DebugParms, fp->FXDBInfo, fp->DataParms->HistoryLen, fp->DataParms->PredictionLen, TrainingStart[i], fp->DataParms->ValidationShift, fp->DataParms->DatasetsCount, HistoryData, HistoryBarW, ValidationData, FutureData, FutureBarW, WholeData, WholeBarW, BaseValH, BaseValV, BaseBW) != 0) return -1;

		//-- 3.2 Do the Training, and get the Forecast
		system("cls");
		printf("\nProcessId=%d ; TestId=%d, TrainingStart=%s ; Start Time: %s\n", pid, i, TrainingStart[i], timestamp());

		if (getForecast(argc, argv, fp->DebugParms->DebugDB->DBCtx, i, HistoryData, BaseValH, HistoryBarW, ValidationData, BaseValV, fp->HaveFutureData, FutureData, FutureBarW, ForecastData) != 0) return -1;

	}

	//-- stop timer, compute the elapsed time
	QueryPerformanceCounter(&time_end);
	elapsedTime = (time_end.QuadPart - time_start.QuadPart) * 1000.0 / frequency.QuadPart;
	ms2ts(elapsedTime, elapsedTimeS);

	//-- update elapsed time in test record, then commit
	if (UpdateTesterDuration(fp->DebugParms, pid, elapsedTime) != 0) return -1;
	LogCommit(fp->DebugParms);



	//-- free(s)
	delete(fp);

	free(BaseValH); free(BaseValV); free(BaseBW);
	for (i = 0; i < fp->DataParms->DatasetsCount; i++) {
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
	for (i = 0; i < fp->SimulationLength; i++) free(TrainingStart[i]);
	free(TrainingStart);

	//--
	gotoxy(0, fp->Engine->TotalCoresCount*fp->DataParms->DatasetsCount + i + 4);
	printf("Elapsed Time: %s\n", elapsedTimeS);
	system("pause");

	return 0;
}


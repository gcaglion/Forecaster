// kaz.cpp : Defines the entry point for the console application.
//

#include <Windows.h>
#include <stdio.h>
#include <MyDebug.h>
#include <MyOraUtils.h>
#include <DBConnection.h>
#include <MyDataAbstraction.h>

int main() {

	tDebugInfo DebugParms;
	DebugParms.DebugLevel = 2;
	strcpy(DebugParms.fPath, "C:/temp");
	strcpy(DebugParms.fName, "kaz.log");

	tDBConnection fxDB;
	strcpy(fxDB.DBUser, "History");
	strcpy(fxDB.DBPassword, "HistoryPwd");
	strcpy(fxDB.DBConnString, "Algo");
	fxDB.DBCtx = NULL;

	tFXData fxData;
	strcpy(fxData.Symbol, "EURUSD");
	strcpy(fxData.TimeFrame, "H1");
	fxData.IsFilled = 0;
	fxData.BarDataTypeCount = 2; fxData.BarDataType[0] = 1; fxData.BarDataType[1] = 3;

	tDBConnection resultsDB;
	strcpy(resultsDB.DBUser, "LogUser");
	strcpy(resultsDB.DBPassword, "LogPwd");
	strcpy(resultsDB.DBConnString, "Algo");
	resultsDB.DBCtx = NULL;

	char* SimulationStart = "201503010000";
	int SimulationLength = 2;

	char** TrainingStart = (char**)malloc(SimulationLength * sizeof(char*)); for (int i = 0; i < SimulationLength; i++) TrainingStart[i] = (char*)malloc(12 + 1);
	if (GetDates(&DebugParms, &fxDB, &fxData, SimulationStart, SimulationLength, TrainingStart) != 0) return -1;

	//printf("OraConnect() returns %d\n", OraConnect(&DebugParms, &fxDB) );

	printf("Press any key to continue..."); getchar();
    return 0;
}


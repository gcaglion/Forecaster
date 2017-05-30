// kaz.cpp : Defines the entry point for the console application.
//

#include <Windows.h>
#include <stdio.h>
#include <MyDebug.h>
#include <MyOraUtils.h>
#include <DBConnection.h>
#include <MyDataAbstraction.h>


class Shape {
	double Area;
public:
	virtual double calcArea();

};
double Shape::calcArea() {
	return 0;
}

class Circle : public Shape {
	double calcArea();
};

double Circle::calcArea() {
	return 5;
}

class Box : public Shape {
	double calcArea();
};

double Box::calcArea() {
	return 5;
}

class Puzzle {
	double puzzleArea;
public:
	int pieces;
	Shape** piece;
	void calcArea();

	Puzzle(int n);
};

Puzzle::Puzzle(int n) {
	pieces = n;
	piece = (Shape**)malloc(pieces*sizeof(Shape*));
	for(int p=0; p<pieces; p++) piece[p] = new Shape();
	puzzleArea = 0;
}

void Puzzle::calcArea() {
	for (int p = 0; p<pieces; p++) puzzleArea += piece[p]->calcArea();
}


int main() {

	Puzzle* p = new Puzzle(4);
	p->calcArea();


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


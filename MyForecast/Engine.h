#pragma once
#include <MyDebug.h>
#include <DBConnection.h>
#include <ExportDef.h>
#include <MyCores.h>
#include <MyCoreLogs.h>

#define ENGINE_NN  0
#define ENGINE_GA  1
#define ENGINE_SOM 2
#define ENGINE_SVM 3
#define ENGINE_WNN 4
#define ENGINE_XIE 5

class cEngine
{
	int Type;
	int InputCount;
	int OutputCount;
	int LayersCount;
	int* CoresCount;
	int RunCount;

	int** CoreType;
	void*** Core;
	void**** CoreLog;

public:
	EXPORT cEngine();
	EXPORT cEngine(int engType, int WNNDecompLevel, int inputCnt, int outputCnt);
	~cEngine();
};


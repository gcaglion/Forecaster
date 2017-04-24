#pragma once
#include <MyNN.h>		//-- to define NN_Parms

//-- Net Layers
#define L_WFE 0
#define L_OUT 1


//-- WNN engine Architecture
typedef struct {
	int DecompLevel;
	char WaveletType[8];
} WNN_Arch;

#include <MyNN.h>
#include <MyLogDefs.h>

__declspec(dllexport) void BuildLayer0Input_WNN(int dataSet, int decompLevel, char* wtype, int tslen, double* its, double ibv, double** ots, double* obv);
__declspec(dllexport) void BuildLayer1Input_WNN(int dataSet, int sampleCnt, int l0sampleLen, int l1sampleLen, int tsfcnt, double* tsf, int l0cores, int l0predlen, int l1predlen, tCore* l0log, double** l1target, double** oSample, double** oTarget);
__declspec(dllexport) void BuildLayerInput_WNN(int layer, tEngineDef* pEngineParms, int dataTrx, int dataSet, int sampleCnt, int l0tslen, double* l0its, double l0ibv, double** l0ots, double* l0obv, double* tsf, tCore* l0log, double** l1target, double** oSample, double** oTarget);
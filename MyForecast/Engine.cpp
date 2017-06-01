#include "stdafx.h"
#include "Engine.h"

#include <MyNN.h>

cEngine::cEngine()
{
}

cEngine::cEngine(int engType, int WNNDecompLevel, int inputCnt, int outputCnt) {
	int l, c;

	Type = engType;
	InputCount = inputCnt;
	OutputCount = outputCnt;
	//--
	if (engType==ENGINE_XIE) {
		LayersCount = 2;
	} else if(engType==ENGINE_WNN){
		LayersCount = 2;
	} else {
		LayersCount = 1;
	}
	//--
	CoresCount = MallocArray<int>(LayersCount);
	CoreType = MallocArray<int*>(LayersCount);
	//--
	if (engType==ENGINE_XIE) {
		CoresCount[0] = 2; CoresCount[1] = 1;
		for (l = 0; l<LayersCount; l++) CoreType[l] = MallocArray<int>(CoresCount[l]);
		CoreType[0] = MallocArray<int>(CoresCount[0]);
		CoreType[1] = MallocArray<int>(CoresCount[1]);
		CoreType[0][0] = CORE_SVM; CoreType[0][1] = CORE_NN;
		CoreType[1][0] = CORE_NN;
	} else if (engType==ENGINE_WNN) {
		CoresCount[0] = WNNDecompLevel+1; CoresCount[1] = 1;
		CoreType[0] = MallocArray<int>(CoresCount[0]);
		CoreType[1] = MallocArray<int>(CoresCount[1]);
		for (c = 0; c<CoresCount[0]; c++) CoreType[0][c] = CORE_NN;
		CoreType[1][0] = CORE_NN;
	} else {
		CoresCount[0] = 1; CoresCount[1] = 1;
		CoreType[0] = MallocArray<int>(CoresCount[0]);
		CoreType[0][0] = engType;
	}

	//-- create cores
	Core = MallocArray<void**>(LayersCount);
	for (l = 0; l<LayersCount; l++) {
		Core[l] = MallocArray<void*>(CoresCount[l]);
		for (c = 0; c<CoresCount[l]; c++) {
			switch (CoreType[l][c]) {
			case CORE_NN:
				Core[l][c] = new cNN();
				break;
			case CORE_GA:
		//		Core[l][c] = new cNN();
				break;
			case CORE_SOM:
	//			Core[l][c] = new cNN();
				break;
			case CORE_SVM:
//				Core[l][c] = new cNN();
				break;
			}
		}
	}

}

cEngine::~cEngine()
{
	free(CoresCount);
}


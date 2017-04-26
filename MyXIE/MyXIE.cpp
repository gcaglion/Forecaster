// MyXIE.cpp : Defines the exported functions for the DLL application.
//

#include <vld.h>

#include "stdafx.h"

#define HD 0
#define VD 1

__declspec(dllexport) void BuildLayerInput_XIE(int layer, int dataSet, int sampleCnt, int predLen, double***** pSample, double***** pTarget, tCore** XIECore){
	int i, s;

	if (layer == 0) {
		//-- we simply need to duplicate the base sample/target data from core=0 to core=1
		for (int s = 0; s < sampleCnt; s++) {
			//[HD/VD][Dataset][Layer][Core][Sample][item]
			for (i = 0; i < XIECore[layer][0].SampleLen; i++) {
				pSample[dataSet][0][1][s][i] = pSample[dataSet][0][0][s][i];
			}
			for (i = 0; i < predLen; i++) {
				pTarget[dataSet][0][1][s][i] = pTarget[dataSet][0][0][s][i];
			}
		}
	} else {
		tLogRUN* runLog_SVM = XIECore[0][0].CoreLog[dataSet].RunOutput;
		tLogRUN* runLog_NN0 = XIECore[0][1].CoreLog[dataSet].RunOutput;
		double*  R = MallocArray<double>(2 * predLen);	// we only need the last (prediction) from runlog for each of the 2 cores in l0

		for (s = 0; s < sampleCnt; s++) {

			// 0. "extract" Predicted items from RunLog of each l0 core
			for (i = 0; i < predLen; i++) {
				R[i] = runLog_SVM[XIECore[0][0].SampleLen + s + i].Predicted_TRS;
				R[i + predLen] = runLog_NN0[XIECore[0][0].SampleLen + s + i].Predicted_TRS;
			}

			// 1. Fill Sample for layer=1
			for(i=0; i<XIECore[layer][0].SampleLen; i++) pSample[dataSet][layer][0][s][i] = R[i];	// only 1 core in layer 1, so coreid=0
			// 2. Fill Target for layer=1
			for (i = 0; i < predLen; i++) pTarget[dataSet][layer][0][s][i] = pTarget[dataSet][0][0][s][i];	// target for layer 1 is the same as in layer 0
		}

		free(R);
	}
}


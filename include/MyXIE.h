#pragma once

#include <MyNN.h>
#include <MySVM.h>
#include <MyLogDefs.h>

__declspec(dllexport) void BuildLayerInput_XIE(int layer, int dataSet, int sampleCnt, int predLen, double***** pSample, double***** pTarget, tCore** XIECore);

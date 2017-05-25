#pragma once

#include <MyNN.h>
#include <MySVM.h>

EXPORT void BuildLayerInput_XIE(int layer, int dataSet, int sampleCnt, int predLen, double***** pSample, double***** pTarget, cCore** XIECore);

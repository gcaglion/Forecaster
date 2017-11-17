#include <cudnn.h>
#include <cuda.h>
#include <stdio.h>
#include <math.h>

#ifndef EXPORT
#define EXPORT __declspec(dllexport)
#endif

EXPORT int RNNtrain(int sqLen, int inputSize, int hiddenSize, int numLayers, int batchCount, int batchSize, bool bidirectional, int mode, float dropout, float** sample, float** target);

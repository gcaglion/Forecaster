#pragma once
#include <MySVM_Parms.h>
#include <DataShape.h>

#define SLACK_NORM_L1 1
#define SLACK_NORM_SQUARED 2
#define RESCALING_METHOD_SLACK 1
#define RESCALING_METHOD_MARGIN 2
#define LOSS_FUNCTION_ZEROONE 0
#define LEARNING_ALGO_NSLACK 0
#define LEARNING_ALGO_NSLACK_SHRINK 1
#define LEARNING_ALGO_1SLACK_PRIMAL 2
#define LEARNING_ALGO_1SLACK_DUAL 3
#define LEARNING_ALGO_1SLACK_DUAL_CONSTR 4
#define LEARNING_ALGO_CUSTOM 9

#define KERNEL_TYPE_LINEAR 0
#define KERNEL_TYPE_POLY 1
#define KERNEL_TYPE_RBF 2
#define KERNEL_TYPE_TANH 3
#define KERNEL_TYPE_CUSTOM 4

__declspec(dllexport) void mallocSVMLog(tCoreLog* coreLog, int SVcnt, int slen);
__declspec(dllexport) void freeSVMLog(tCoreLog* coreLog, int slen);
__declspec(dllexport) int Train_SVM(int pCorePos, int pTotCores, HANDLE pScreenMutex, tDebugInfo* pDebugParms, SVM_Parms* pSVMParms, tCoreLog* pSVMLogs, int pSampleCount, double** pSampleData, double** pTargetData, int useValidation, double** pSampleDataV, double** pTargetDataV);
__declspec(dllexport) int Run_SVM(tDebugInfo* pDebugParms, SVM_Parms* SVMParms, tCoreLog* SVMLogs, tDataShape* pInputData, int pid, int tid, int pSampleCount, double** pSample, double** pTarget);

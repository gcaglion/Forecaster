
#include "stdafx.h"

typedef struct{
	tDebugInfo* DebugParms; SOM_Parms* SOMParms; 
	int SampleCount; double** Sample; double** Target;
	int NetId; 
	int TestId; int DataSetId;
	double** W; double* D; int* WinnerNode; 
	tEngineHandle TrainInfo;
	tDataShape* InputData;
	HANDLE thMutex;
} tSOMTrainParams;

void SaveMSEData(SOM_Parms* SOMParms, int pNetId, DWORD pid, DWORD tid, int pDataSet, int pTestId, int pEpoch, double pMSE_T, double pMSE_V){
	SOMParms->MSEOutput[pDataSet][pEpoch].ProcessId = pid;
	SOMParms->MSEOutput[pDataSet][pEpoch].ThreadId = tid;
	SOMParms->MSEOutput[pDataSet][pEpoch].TestId = pTestId;
	SOMParms->MSEOutput[pDataSet][pEpoch].Epoch = pEpoch;
	SOMParms->MSEOutput[pDataSet][pEpoch].MSE_T = pMSE_T;
	SOMParms->MSEOutput[pDataSet][pEpoch].MSE_V = pMSE_V;
}

void SaveRunData(SOM_Parms* SOMParms, int pNetId, DWORD pid, DWORD tid, int pDataSet, int pTestId, int pPos, int pOOSPos, double pActual, double pPredicted){
	SOMParms->RunOutput[pDataSet][pPos].ProcessId = pid;
	SOMParms->RunOutput[pDataSet][pPos].ThreadId = tid;
	SOMParms->RunOutput[pDataSet][pPos].TestId = pTestId;
	SOMParms->RunOutput[pDataSet][pPos].Pos = pPos;
	SOMParms->RunOutput[pDataSet][pPos].Actual = pActual;
	SOMParms->RunOutput[pDataSet][pPos].Predicted = pPredicted;
}

void SOMSave(SOM_Parms* pSOMParms, int pNetId, int pid, int tid, int pDataSetId, int pTestId, double** W){
	int i, o;
	int idx = 0;
	for (o = 0; o < pSOMParms->OutputCount; o++){
		for (i = 0; i < pSOMParms->InputCount; i++){
			pSOMParms->FinalW[pDataSetId][o][i].ProcessId = pid;
			pSOMParms->FinalW[pDataSetId][o][i].ThreadId = tid;
			pSOMParms->FinalW[pDataSetId][o][i].TestId = pTestId;
			pSOMParms->FinalW[pDataSetId][o][i].FromNeuron = o;
			pSOMParms->FinalW[pDataSetId][o][i].ToNeuron = i;
			pSOMParms->FinalW[pDataSetId][o][i].Weight = W[o][i];
		}
	}
}

int CalcTD(int node1, int node2){
	//-- Calculates Topological Distance between 2 nodes.

	//-- For now, let's keep it simple, and consider output space to be 1D, so topological distance is simply the difference between the two nodes' ID
	return (abs(node1 - node2));
}

double GetMaxTD(int epoch, int MaxEpochs, double BaseTD, int TDFunction){
	double ret;
	switch (TDFunction){
	case TD_DECAY_CONSTANT:
		ret = BaseTD;
		break;
	case TD_DECAY_STEPPED:
		ret = (epoch <= 5)?1:0;
		break;
	case TD_DECAY_EXP:
		ret = BaseTD*exp(-0.01*epoch);
		break;
	default:
		ret = 0;
		break;
	}
	return ret;
}

double GetLR(int epoch, int MaxEpochs, double BaseLR, int LRFunction){
	double ret;
	switch (LRFunction){
	case LR_DECAY_CONSTANT:
		ret = BaseLR;
		break;
	case LR_DECAY_STEPPED:
		if (epoch <= 5)			{ ret = 0.6; }
		else if (epoch <= 12)	{ ret = 0.25; }
		else                    { ret = 0.1; }
		break;
	case LR_DECAY_LINEAR:
		ret = -BaseLR / MaxEpochs + BaseLR;
	default:
	case LR_DECAY_EXP:
		ret = BaseLR*exp(-0.01*epoch);
		break;
	}
	return ret;
}

void SOMInit(int pInputCount, int pOutputCount, double** pW){
	//-- Initialize random Weights
	for (int o = 0; o<pOutputCount; o++){
		for (int i = 0; i < pInputCount; i++){
			pW[o][i] = MyRndDbl(-1, 1);
		}
	}
}

int SOMTrain(tDebugInfo* pDebugParms, SOM_Parms* pSOMParms, int pNetId, int pDatasetId, int pTestId, HANDLE pMutex, int InputCount, int OutputCount, int SampleCount, int MaxEpochs, double BaseTD, int TDFunction, double** Sample, double** Target, double BaseLR, int LRFunction, double** W, double* D, int* WinnerNode){
	//-- Target is only used to build the association between WinnerNode and actual result
	int i, e, s, o;
	double d;
	double MinD;	// Minimum Euclidean Distance between Output node and Input nodes, among all output nodes;
	double MaxTD;	// Maximum Topological Distance between WinnerNode and another Output node at which the second node gets updated
	double LR;		// Learning Rate for the current epoch
	int pid = GetCurrentProcessId();
	int tid = GetCurrentThreadId();

	//-- Training Loop
	for (e = 0; e < MaxEpochs; e++){
		for (s = 0; s<SampleCount; s++){
			MinD = 100000;
			//-- At every epoch, re-evaluate MaxTD and LearningRate
			MaxTD = GetMaxTD(e, MaxEpochs, BaseTD, TDFunction);
			LR = GetLR(e, MaxEpochs, BaseLR, LRFunction);
			//-- for each TrainingSample
			for (o = 0; o<OutputCount; o++){
				D[o] = 0;
				for (i = 0; i < InputCount; i++){
					//-- compute Euclidean distance between output node and weight
					d = Sample[s][i] - W[o][i];
					D[o] += pow(d, 2);
				}
				//-- Is this o the output node that has weight vector with minimum value?
				if (D[o]<MinD){
					//-- We have a winner!
					WinnerNode[s] = o;
					MinD = D[o];
				}
			}
			//-- Update Weights for all the Output nodes within a certain Topological Distance from the Winner node. Winner node has TD=0, so it surely gets updated
			for (o = 0; o < OutputCount; o++){
				if (CalcTD(o, WinnerNode[s]) <= MaxTD){
					// Node <o> is within the influence radius, so it gets updated
					for (i = 0; i < InputCount; i++) W[o][i] += LR*(Sample[s][i] - W[o][i]);
				}
			}
		}
		WaitForSingleObject(pMutex, INFINITE);
		gotoxy(0, 1 + pDatasetId); printf("\rProcess %5d, Thread %5d, Dataset %d , TestId %d , Epoch %6d , MaxTD=%f, LR=%f", pid, tid, pDatasetId, pTestId, e, MaxTD, LR);
		ReleaseMutex(pMutex);
		//-- Save (fake?) MSE Data
		if (pDebugParms->DebugLevel>0) SaveMSEData(pSOMParms, pNetId, pid, tid, pDatasetId, pTestId, e, 0, 0);
	}
	return 0;
}

void TrainSave_SOM(tSOMTrainParams* tparms){
	DWORD pid = GetCurrentProcessId();
	DWORD tid = GetCurrentThreadId();
	//-- Init Weights
	SOMInit(tparms->SOMParms->InputCount, tparms->SOMParms->OutputCount, tparms->W);
	//-- Train
	SOMTrain(tparms->DebugParms, tparms->SOMParms, tparms->NetId, tparms->DataSetId, tparms->TestId, tparms->thMutex, tparms->SOMParms->InputCount, tparms->SOMParms->OutputCount, tparms->SampleCount, tparms->SOMParms->MaxEpochs, tparms->SOMParms->BaseTD, tparms->SOMParms->TDFunction, tparms->Sample, tparms->Target, tparms->SOMParms->BaseLR, tparms->SOMParms->LRFunction, tparms->W, tparms->D, tparms->WinnerNode);
	//-- Save
	SOMSave(tparms->SOMParms, tparms->NetId, pid, tid, tparms->DataSetId, tparms->TestId, tparms->W);
	//-- Run
	//Run_SOM(tparms->DebugParms, tparms->SOMParms, tparms->InputData, tparms->OOS, pid, tid, tparms->DataSetId, tparms->TestId, tparms->SampleCount, tparms->Sample, tparms->Target, tparms->Forecast);

/*	//-- Now that weights have been trained, let's feed the same training data to the network (In-Sample Run)
	FILE* fRun = fopen("C:/temp/SOMRun.csv", "w");
	fprintf(fRun, "Sample, Result, Actual\n");
	for (s = 0; s < tparms->SampleCount; s++){
		ret = SOMRun(tparms->SampleLen, tparms->SOMParms->OutputCount, tparms->Sample[s], tparms->W, tparms->D);
		// What did this sample lead to, in reality?
		// That is, what was the delta between its last value, and the first value of the next sample? (the opposite, of course)
		if (s == (tparms->SampleCount-1) ){
			vActual = 0;
		}
		else {
			vActual = tparms->Sample[s + 1][0] - tparms->Sample[s][tparms->SampleLen - 1];
		}
		if (tparms->DebugParms->DebugLevel>0) SaveRunData(tparms->SOMParms, pid, tid, tparms->DataSetId, tparms->TestId, s, 0, vActual, ret, (ret - vActual), tparms->)
		fprintf(fRun, "%d, %d, %f\n", s, ret, delta);
	}
	fclose(fRun);
	gotoxy(0, 20 + 5 * tparms->DataSetId);  printf("Forecast[%d]=%f\n", tparms->DataSetId, tparms->Forecast[0]);
	printf("\n");
*/
}

__declspec(dllexport) void Run_SOM(tDebugInfo* pDebugParms, SOM_Parms* pSOMParms, tDataShape* pInputData, int pOOS, int pid, int ptid, int pDatasetId, int pTestId, int pSampleCount, double** pSample, double** pTarget, double* oForecast){
	int s, i, o;
	double d;
	double MinD;
	int vNetId = 0;
	//-- 0. mallocs
	double** W = (double**)malloc(pSOMParms->OutputCount*sizeof(double*)); for (o = 0; o < pSOMParms->OutputCount; o++) W[o] = (double*)malloc(pSOMParms->InputCount*sizeof(double));	// ( [OutputCount][InputCount] )
	double*  D = (double*)malloc(pSOMParms->OutputCount*sizeof(double));																												// ( [OutputCount] )
	int*     WinnerNode = (int*)malloc(pSampleCount*sizeof(int));																														// ( [SampleCount] )
	//double*  vActual = (double*)malloc(pSampleCount*sizeof(double));
	double vActual;
	double vPrediction;
	//-- 1. Load W** from pSOMParms->FinalW[DataSet][FromN][ToN]
	for (o = 0; o < pSOMParms->OutputCount; o++){
		for (i = 0; i < pSOMParms->InputCount; i++){
			W[o][i] = pSOMParms->FinalW[pDatasetId][o][i].Weight;
		}
	}
	//-- 2. Write First window of data, with no prediction (that is, write the first sample)
	for (i = 0; i<pInputData->SampleLen; i++){
		if (pDebugParms->DebugLevel>0) SaveRunData(pSOMParms, vNetId, pid, ptid, pDatasetId, pTestId, i, (pInputData->HistoryLen - i), pSample[0][i], NULL);
	}
	//-- 3. Run all the samples
	for (s = 0; s < pSampleCount; s++){
		//for (s = 0; s < (pInputData->HistoryLen + pInputData->PredictionLen - pInputData->SampleLen); s++){
		MinD = 100000;
		for (o = 0; o<pSOMParms->OutputCount; o++){
			D[o] = 0;
			for (i = 0; i < pSOMParms->InputCount; i++){
				//-- compute Euclidean distance between output node and weight
				d = pSample[s][i] - W[o][i];
				D[o] += pow(d, 2);
			}
			//-- Is this o the output node that has weight vector with minimum value?
			if (D[o]<MinD){
				//-- We have a winner!
				(WinnerNode[s]) = o;
				MinD = D[o];
			}
		}
		//-- No Weight update; Sample falls into <WinnerNode> output

/*		//-- Now we build the association between WinnerNode and actual result. Actual Result is intended as the delta between Target[s][0] and last element of Sample[s]
		vActual = pTarget[s][0] - pSample[s][pInputData->SampleLen - 1];
		vPrediction = pSample[s][pInputData->SampleLen - 1] + vActual;
*/
		
		//-- Now we build the association between WinnerNode and actual result:
		//---- 
		vActual = pTarget[s][0];
		//vPrediction = WinnerNode[s] * (pInputData->ScaleMax - pInputData->ScaleMin) / pSOMParms->OutputCount;	//-- WinnerNode position is relative to the width of scaled data
		
		//m = (pInputData->ScaleMax - pInputData->ScaleMin) / pSOMParms->OutputCount;
		//p = pInputData->ScaleMax - m*pSOMParms->OutputCount;
		vPrediction = WinnerNode[s];// *m + p;	//-- WinnerNode position is relative to the width of scaled data

		//--
		if (pDebugParms->DebugLevel>0) SaveRunData(pSOMParms, vNetId, pid, ptid, pDatasetId, pTestId, pInputData->SampleLen + s, (s - pInputData->HistoryLen + pInputData->SampleLen + 1), vActual, vPrediction);
	}
	//-- 4. Returned Forecast is calculated by adding the vActual from the last sample to the last element of the last sample
	//oForecast[0] = pSample[pSampleCount - 1][pInputData->SampleLen - 1] + vActual[pSampleCount - 1];
	oForecast[0] = vPrediction;
	//-- TBD: oForecast[1], ... , oForecast[pPredictionLen]

}

__declspec(dllexport) int Train_SOM(tDebugInfo* pDebugParms, SOM_Parms* pSOMParams, tDataShape* pInputData, int pTestId, int pSampleCount, double*** pSampleData, double*** pTargetData, double*** pSampleDataV, double*** pTargetDataV){
	int i, d;
	int pid = GetCurrentProcessId();

	// srand() and mallocs
	srand((unsigned int)time(NULL));

	double***	Weight = (double***)malloc(pInputData->DatasetsCount*sizeof(double**));				// ( [DatasetsCount][OutputCount][InputCount] )
	double**	D = (double**)malloc(pInputData->DatasetsCount*sizeof(double*));					// ( [DatasetsCount][OutputCount] )
	int** WinnerNode = (int**)malloc(pInputData->DatasetsCount*sizeof(int*));						// ( [DatasetsCount][SampleCount]
	for (d = 0; d < pInputData->DatasetsCount; d++){
		Weight[d] = (double**)malloc(pSOMParams->OutputCount*sizeof(double*)); for (i = 0; i < pSOMParams->OutputCount; i++) Weight[d][i] = (double*)malloc(pInputData->SampleLen*sizeof(double));
		D[d] = (double*)malloc(pSOMParams->OutputCount*sizeof(double));
		WinnerNode[d] = (int*)malloc(pSampleCount*sizeof(int));
	}

	double wiggleRoom = 0;
	HANDLE* HTrain = (HANDLE*)malloc(pInputData->DatasetsCount*sizeof(HANDLE));
	tSOMTrainParams* tp = (tSOMTrainParams*)malloc(pInputData->DatasetsCount*sizeof(tSOMTrainParams));
	DWORD* kaz = (DWORD*)malloc(pInputData->DatasetsCount*sizeof(DWORD));
	LPDWORD* tid = (LPDWORD*)malloc(pInputData->DatasetsCount*sizeof(LPDWORD)); for (i = 0; i < pInputData->DatasetsCount; i++) tid[i] = &kaz[i];
	HANDLE dsMutex = CreateMutex(NULL, FALSE, NULL);

	//-- Do the following for each dataset; each Dataset is handled by one separate thread
	for (d = 0; d < pInputData->DatasetsCount; d++){
		//-- prepare Training parameters
		tp[d].DebugParms = pDebugParms; 
		tp[d].SOMParms = pSOMParams; 
		tp[d].NetId = 0;
		tp[d].TestId = pTestId; 
		tp[d].DataSetId = d;
		tp[d].thMutex = dsMutex;
		tp[d].SampleCount = pSampleCount; 
		tp[d].Sample = pSampleData[d]; 
		tp[d].Target = pTargetData[d];
		tp[d].InputData = pInputData;
		tp[d].W = Weight[d]; tp[d].D = D[d]; tp[d].WinnerNode = WinnerNode[d];
		//-- Train, and get forecast from output neurons
		HTrain[d] = CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE)TrainSave_SOM, &tp[d], 0, tid[d]);
		//-- Store Engine Handler
		//tp[d].TrainInfo.DatasetId = d; 
		//tp[d].TrainInfo.ProcessId = pid; 
		//tp[d].TrainInfo.ThreadId = (*tid[d]); 
		//tp[d].TrainInfo.TestId = pTestId;
	}
	WaitForMultipleObjects(pInputData->DatasetsCount, HTrain, TRUE, INFINITE);

	//-- free(s)
	for (d = 0; d < pInputData->DatasetsCount; d++){
		for (i = 0; i < pSOMParams->OutputCount; i++) free(Weight[d][i]);
		free(Weight[d]);
		free(D[d]);
		free(WinnerNode[d]);
	}
	free(HTrain); free(tp); free(kaz); free(tid); 
	ReleaseMutex(dsMutex);

	return 0;
}
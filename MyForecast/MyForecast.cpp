//#include <vld.h>

#include <MyForecast.h>

typedef struct {
	tDebugInfo* DebugParms;
	tEngineDef* EngineParms;
	int LayerId; int CoreId; int DatasetId;
	int CorePos; int TotCores; HANDLE ScreenMutex;
	int useValidation;
	bool useExistingW;
	int SampleCount; double** SampleT; double** TargetT; double** SampleV; double** TargetV;
	tEngineHandle TrainInfo;
	int TrainSuccess;
	int ActualEpochs;
} tTrainParams;

typedef struct {
	tDebugInfo* DebugParms;
	tEngineDef* EngineParms;
	tDataShape* InputData;
	int LayerId;
	int CoreId;
	int DatasetId;
	int pid;
	int tid;
	int SampleCount;
	double** Sample;
	double** Target;
} tRunParams;

void freeCoreParms(tForecastParms* fParms) {
	switch (fParms->EngineParms.EngineType) {
	case ENGINE_WNN:
		for (int c = 0; c < fParms->EngineParms.CoresCount[1]; c++) free(fParms->EngineParms.Core[1][c].CoreSpecs);
		free(fParms->EngineParms.Core[1]);
		break;
	case ENGINE_XIE:
		free(fParms->EngineParms.Core[1]->CoreSpecs);
		free(fParms->EngineParms.Core[1]);
		break;
	default:
		break;
	}
	for (int c = 0; c < fParms->EngineParms.CoresCount[0]; c++) free(fParms->EngineParms.Core[0][c].CoreSpecs);
	FreeArray(1, 1, fParms->EngineParms.Core);
	free(fParms->EngineParms.CoresCount);
	//free(fParms->EngineParms.Core[0]);
	//free(fParms->EngineParms.Core);
}

void mallocCoreLogs(tForecastParms* fParms) {
	int l, c, d;
	for (l = 0; l < fParms->EngineParms.LayersCount; l++) {
		for (c = 0; c < fParms->EngineParms.CoresCount[l]; c++) {
			fParms->EngineParms.Core[l][c].CoreLog = MallocArray<tCoreLog>(fParms->DataParms.DatasetsCount);
			for (d = 0; d < fParms->DataParms.DatasetsCount; d++) {
				//-- Engine-indipendent 
				fParms->EngineParms.Core[l][c].CoreLog[d].MSEOutput = MallocArray<tLogMSE>(fParms->EngineParms.Core[l][c].MSECount);
				fParms->EngineParms.Core[l][c].CoreLog[d].RunOutput = MallocArray<tLogRUN>(fParms->EngineParms.Core[l][c].RunCount);
				//-- NN-specific
				if (fParms->EngineParms.Core[l][c].CoreType == ENGINE_NN) {
					setNNTopology((NN_Parms*)fParms->EngineParms.Core[l][c].CoreSpecs);
					mallocNNLog(&fParms->EngineParms.Core[l][c].CoreLog[d], ((NN_Parms*)fParms->EngineParms.Core[l][c].CoreSpecs)->LevelsCount, ((NN_Parms*)fParms->EngineParms.Core[l][c].CoreSpecs)->NodesCount, (fParms->DebugParms.SaveInternals>0), fParms->EngineParms.Core[l][c].TimeStepsCount);
				}
				//-- GA-specific
				//-- SVM-specific is called from SVMTrain() because we don't know SVMcount until the end of training
				//-- SOM-specific
			}
		}
	}
}
void freeCoreLogs(tForecastParms* fParms) {
	int l, c, d;
	for (l = 0; l < fParms->EngineParms.LayersCount; l++) {
		for (c = 0; c < fParms->EngineParms.CoresCount[l]; c++) {
			for (d = 0; d < fParms->DataParms.DatasetsCount; d++) {
				//-- Engine-indipendent 
				free(fParms->EngineParms.Core[l][c].CoreLog[d].MSEOutput);
				free(fParms->EngineParms.Core[l][c].CoreLog[d].RunOutput);
				//-- NN-specific
				if (fParms->EngineParms.Core[l][c].CoreType == ENGINE_NN) {
					freeNNLog(&fParms->EngineParms.Core[l][c].CoreLog[d], ((NN_Parms*)fParms->EngineParms.Core[l][c].CoreSpecs)->LevelsCount, ((NN_Parms*)fParms->EngineParms.Core[l][c].CoreSpecs)->NodesCount, (fParms->DebugParms.SaveInternals>0), fParms->EngineParms.Core[l][c].TimeStepsCount);
				}
				//-- GA-specific
				//-- SVM-specific
				if (fParms->EngineParms.Core[l][c].CoreType == ENGINE_SVM) {
					freeSVMLog(&fParms->EngineParms.Core[l][c].CoreLog[d], fParms->EngineParms.Core[l][c].SampleLen);
				}
				//-- SOM-specific
			}
			free(fParms->EngineParms.Core[l][c].CoreLog);
		}
	}
}

int setEngineLayout(tForecastParms* fParms) {
	//-- 1. set LayersCount, CoresCount, Core[]
	switch (fParms->EngineParms.EngineType) {
	case ENGINE_WNN:
		if (getParam(fParms->iniParms, "WNNInfo.WaveletType", fParms->EngineParms.WNN_WaveletType) < 0)		return -1;
		if (getParam(fParms->iniParms, "WNNInfo.DecompLevel", &fParms->EngineParms.WNN_DecompLevel) < 0)	return -1;
		fParms->EngineParms.LayersCount = 2;
		fParms->EngineParms.CoresCount = MallocArray<int>(fParms->EngineParms.LayersCount);
		fParms->EngineParms.CoresCount[0] = fParms->EngineParms.WNN_DecompLevel + 1;
		fParms->EngineParms.CoresCount[1] = 1;
		fParms->EngineParms.Core = (tCore**)malloc(fParms->EngineParms.LayersCount * sizeof(tCore*));
		fParms->EngineParms.Core[0] = MallocArray<tCore>(fParms->EngineParms.WNN_DecompLevel + 1);
		fParms->EngineParms.Core[1] = MallocArray<tCore>(1);

		break;
	case ENGINE_XIE:
		fParms->EngineParms.LayersCount = 2;
		fParms->EngineParms.CoresCount = MallocArray<int>(fParms->EngineParms.LayersCount);
		fParms->EngineParms.CoresCount[0] = 2;
		fParms->EngineParms.CoresCount[1] = 1;
		fParms->EngineParms.Core = (tCore**)malloc(fParms->EngineParms.LayersCount * sizeof(tCore*));
		fParms->EngineParms.Core[0] = MallocArray<tCore>(2);
		fParms->EngineParms.Core[1] = MallocArray<tCore>(1);
		break;
	default:
		fParms->EngineParms.LayersCount = 1;
		fParms->EngineParms.CoresCount = MallocArray<int>(1);
		fParms->EngineParms.CoresCount[0] = 1;
		fParms->EngineParms.Core = (tCore**)malloc(fParms->EngineParms.LayersCount * sizeof(tCore*));
		fParms->EngineParms.Core[0] = MallocArray<tCore>(1);
		fParms->EngineParms.Core[0]->CoreType = fParms->EngineParms.EngineType;
		break;
	}

	//-- 2. set TotalCoresCount
	fParms->EngineParms.TotalCoresCount = 0;
	for (int l = 0; l < fParms->EngineParms.LayersCount; l++) {
		for (int c = 0; c < fParms->EngineParms.CoresCount[l]; c++) {
			fParms->EngineParms.TotalCoresCount++;
		}
	}
	return 0;
}

double****** mallocSample(tEngineDef* pEngineParms, tDataShape* pDataParms) {
	int slen;
	double****** ret = (double******)malloc(2 * sizeof(double*****));
	for (int hdvd = 0; hdvd < 2; hdvd++) {
		ret[hdvd] = (double*****)malloc(pDataParms->DatasetsCount * sizeof(double****));
		for (int d = 0; d < pDataParms->DatasetsCount; d++) {
			ret[hdvd][d] = (double****)malloc(pEngineParms->LayersCount * sizeof(double***));
			for (int l = 0; l < pEngineParms->LayersCount; l++) {
				ret[hdvd][d][l] = (double***)malloc(pEngineParms->CoresCount[l] * sizeof(double**));
				for (int c = 0; c < pEngineParms->CoresCount[l]; c++) {
					ret[hdvd][d][l][c] = (double**)malloc(pDataParms->SampleCount * sizeof(double*));
					slen = pEngineParms->Core[l][c].SampleLen;
					for (int s = 0; s < pDataParms->SampleCount; s++) {
						ret[hdvd][d][l][c][s] = (double*)malloc(slen * sizeof(double));
					}
				}
			}
		}
	}
	return ret;
}
double****** mallocTarget(tEngineDef* pEngineParms, tDataShape* pDataParms) {
	int tlen;
	double****** ret = (double******)malloc(2 * sizeof(double*****));
	for (int hdvd = 0; hdvd < 2; hdvd++) {
		ret[hdvd] = (double*****)malloc(pDataParms->DatasetsCount * sizeof(double****));
		for (int d = 0; d < pDataParms->DatasetsCount; d++) {
			ret[hdvd][d] = (double****)malloc(pEngineParms->LayersCount * sizeof(double***));
			for (int l = 0; l < pEngineParms->LayersCount; l++) {
				ret[hdvd][d][l] = (double***)malloc(pEngineParms->CoresCount[l] * sizeof(double**));
				for (int c = 0; c < pEngineParms->CoresCount[l]; c++) {
					ret[hdvd][d][l][c] = (double**)malloc(pDataParms->SampleCount * sizeof(double*));
					tlen = pEngineParms->Core[l][c].TargetLen;
					for (int s = 0; s < pDataParms->SampleCount; s++) {
						ret[hdvd][d][l][c][s] = (double*)malloc(tlen * sizeof(double));
					}
				}
			}
		}
	}
	return ret;
}
void freeSampleTarget(tEngineDef* pEngineParms, tDataShape* pDataParms, double****** S, double****** T) {
	for (int hdvd = 0; hdvd < 2; hdvd++) {
		for (int d = 0; d < pDataParms->DatasetsCount; d++) {
			for (int l = 0; l < pEngineParms->LayersCount; l++) {
				for (int c = 0; c < pEngineParms->CoresCount[l]; c++) {
					for (int s = 0; s < pDataParms->SampleCount; s++) {
						free(S[hdvd][d][l][c][s]);
						free(T[hdvd][d][l][c][s]);
					}
					free(S[hdvd][d][l][c]);
					free(T[hdvd][d][l][c]);
				}
				free(S[hdvd][d][l]);
				free(T[hdvd][d][l]);
			}
			free(S[hdvd][d]);
			free(T[hdvd][d]);
		}
		free(S[hdvd]);
		free(T[hdvd]);
	}
	free(S);
	free(T);
}

//--
int LogSave_MSE(tDebugInfo* pDebugParms, tEngineDef* pEngineParms, tDataShape* pDataParms, int pTestId) {
	int l, n, d, i;
	tLogMSE* vMSELog;
	int vActualEpochs;

	for (l = 0; l<pEngineParms->LayersCount; l++) {
		for (n = 0; n<pEngineParms->CoresCount[l]; n++) {
			for (d = 0; d<pDataParms->DatasetsCount; d++) {
				//-- Fill Logs with missing info (Test, LayerId, CoreId,...)
				vMSELog = pEngineParms->Core[l][n].CoreLog[d].MSEOutput;
				vActualEpochs = pEngineParms->Core[l][n].CoreLog[d].ActualEpochs;
				if (vActualEpochs == 0) return -1;
				for (i = 0; i<vActualEpochs; i++) {
					vMSELog[i].TestId = pTestId;
					vMSELog[i].LayerId = l;
					vMSELog[i].CoreId = n;
				}
				//-- Actual Save
				if (BulkMSEInsert(pDebugParms, pEngineParms->EngineType, &vActualEpochs, vMSELog) != 0) return -1;
			}
		}
	}
	return 0;
}
int LogSave_Run(tDebugInfo* pDebugParms, tEngineDef* pEngineParms, tDataShape* pDataParms, int pTestId, tLogRUN** R) {
	int rc = pDataParms->SampleLen + pDataParms->SampleCount + pDataParms->PredictionLen;

	for (int d = 0; d<pDataParms->DatasetsCount; d++) {
		if (BulkRunInsert(pDebugParms, &rc, pDataParms->HistoryLen, R[d]) != 0) return -1;
	}

	return 0;
}
int LogSave_Cores(tDebugInfo* pDebugParms, tEngineDef* pEngineParms, tDataShape* pDataParms, int pid, int pTestId) {

	//-- for each core, this performs 3 separate operations:
	//-- 1. save cores parameters into CoreParms_<XXX>
	//-- 2. save cores images     into CoreImage_<XXX> . For NN, image is defined by tNNWeight info; for SVM, image is defined by alphaY[] and SV[][]
	//-- 3. save cores logs       into CoreLogs_<XXX>

	tCore* core;
	NN_Parms* NNParms = nullptr;	tNNWeight*** NNWeight0 = nullptr; tNNWeight*** NNWeight1 = nullptr;
	SOM_Parms* SOMParms = nullptr;	tSOMWeight** SOMWeight = nullptr;
	GA_Parms* GAParms = nullptr;	//tGAWeight*** GAWeight=nullptr;
	SVM_Parms* SVMParms = nullptr;

	for (int l = 0; l < pEngineParms->LayersCount; l++) {
		for (int n = 0; n < pEngineParms->CoresCount[l]; n++) {
			core = &pEngineParms->Core[l][n];
			switch (core->CoreType) {
			case ENGINE_NN:
				NNParms = (NN_Parms*)core->CoreSpecs;
				//-- 1. save engine parameters. We save it once for dataset even if it's useless, just because we need a threadid for the cores
				if (pTestId == 0) {
					if (InsertCoreParms_NN(pDebugParms, pEngineParms->AdderCount, pid, l, n, NNParms) != 0) return -1;
				}
				for (int d = 0; d < pDataParms->DatasetsCount; d++) {
					//-- 2. save initial and final image (weights) , for each dataset
					NNWeight0 = core->CoreLog[d].NNInitW;
					NNWeight1 = core->CoreLog[d].NNFinalW;
					if (InsertCoreImage_NN(pDebugParms, NNParms, NNWeight0, NNWeight1) != 0) return -1;
					if (InsertCoreLogs_NN(pDebugParms, (NN_Parms*)core->CoreSpecs, &core->CoreLog[d]) != 0) return -1;
				}
				break;
			case ENGINE_GA:
				break;
			case ENGINE_SOM:
				SOMParms = (SOM_Parms*)core->CoreSpecs;
				//-- 1. save engine parameters
				if (pTestId == 0) {
					if (InsertCoreParms_SOM(pDebugParms, pEngineParms->AdderCount, pid, l, n, SOMParms) != 0) return -1;
				}
				for (int d = 0; d < pDataParms->DatasetsCount; d++) {
					//-- 2. save final image (weights) , for each dataset
					SOMWeight = core->CoreLog[d].SOMFinalW;
					if (InsertCoreImage_SOM(pDebugParms, SOMParms, SOMWeight) != 0) return -1;
				}
				break;
			case ENGINE_SVM:
				SVMParms = (SVM_Parms*)core->CoreSpecs;
				//-- 1. save engine parameters. We save it once for dataset even if it's useless, just because we need a threadid for the cores
				if (pTestId == 0) {
					if (InsertCoreParms_SVM(pDebugParms, pEngineParms->AdderCount, pid, l, n, SVMParms) != 0) return -1;
				}
				for (int d = 0; d < pDataParms->DatasetsCount; d++) {
					//-- 2. save final image (weights) , for each dataset
					if (InsertCoreLogs_SVM(pDebugParms, (SVM_Parms*)core->CoreSpecs, &core->CoreLog[d]) != 0) return -1;
					if (pDebugParms->SaveImages>0) {
						//QueryPerformanceCounter(&time_start);		// start timer
						LogWrite(pDebugParms, LOG_INFO, "%s(): SVCount=%d\n", 3, __func__, core->CoreLog[d].SVMResult.SVcount);
						if (InsertCoreImage_SVM(pDebugParms, SVMParms, &core->CoreLog[d].SVMResult, core->CoreLog[d].SVMFinalW) != 0) return -1;										//===== THIS IS CREATING SYSTEM-WIDE CONTENTION / WAIT !!! ====					
																																														//QueryPerformanceCounter(&time_end); elapsedTime = (time_end.QuadPart - time_start.QuadPart) * 1000.0 / frequency.QuadPart; ms2ts(elapsedTime, elapsedTimeS);	//-- stop timer, compute the elapsed time
																																														//fprintf(fPerf, "InsertCoreImage_SVM(), %d, %f, %s\n", core->CoreLog[d].SVMResult.SVcount*pDataParms->SampleLen, elapsedTime, elapsedTimeS);											//-- print elapsed time in perf file
					}
				}
				break;
			}
		}
	}
	return 0;
}
//--
int LoadCoreParms(tDebugInfo* pDebugParms, int pid, tEngineDef* pEngineParms, tDataShape* pDataParms) {
	tCore* core;
	int tid;

	for (int l = 0; l < pEngineParms->LayersCount; l++) {
		for (int n = 0; n < pEngineParms->CoresCount[l]; n++) {
			core = &pEngineParms->Core[l][n];
			//-- first, get ThreadId for this core. Use Dataset=0 and TestId=0, as core parameters are the same for every dataset/Test
			tid = getCoreThreadId(pDebugParms, pid, 0, 0, l, n);
			//-- then,  load core
			switch (core->CoreType) {
			case ENGINE_NN:
				if (LoadCoreParms_NN(pDebugParms, pid, tid, (NN_Parms*)core->CoreSpecs) != 0) return -1;
				break;
			case ENGINE_GA:
				break;
			case ENGINE_SOM:
				if (LoadCoreParms_SOM(pDebugParms, pid, tid, (SOM_Parms*)core->CoreSpecs) != 0) return -1;
				break;
			case ENGINE_SVM:
				if (LoadCoreParms_SVM(pDebugParms, pid, tid, (SVM_Parms*)core->CoreSpecs) != 0) return -1;
				break;
			}
		}
	}
	return 0;

}
int LoadCoreImage(tDebugInfo* pDebugParms, int pid, int testid, int DSid, tEngineDef* pEngineParms, tDataShape* pDataParms, tEngineHandle* pSavedEngine) {
	tCore* core;
	int tid;
	//-- 

	for (int l = 0; l < pEngineParms->LayersCount; l++) {
		for (int n = 0; n < pEngineParms->CoresCount[l]; n++) {
			core = &pEngineParms->Core[l][n];
			//-- first, get ThreadId for this core
			tid = getCoreThreadId(pDebugParms, pid, testid, DSid, l, n);
			//-- store threadid that will be needed by SetNetPid() as NetThreadId
			pSavedEngine->ThreadId = tid;
			//-- then,  load core
			switch (core->CoreType) {
			case ENGINE_NN:
				for (int d = 0; d < pDataParms->DatasetsCount; d++) {
					if (LoadCoreImage_NN(pDebugParms, pid, tid, (NN_Parms*)core->CoreSpecs, core->CoreLog[d].NNFinalW) != 0) return -1;
				}
				break;
			case ENGINE_GA:
				break;
			case ENGINE_SOM:
				for (int d = 0; d < pDataParms->DatasetsCount; d++) {
					if (LoadCoreImage_SOM(pDebugParms, pid, tid, (SOM_Parms*)core->CoreSpecs, core->CoreLog[d].SOMFinalW) != 0) return -1;
				}
				break;
			case ENGINE_SVM:
				for (int d = 0; d < pDataParms->DatasetsCount; d++) {
					//-- first, load SVM results from CoreLogs_SVM. This is needed here to set SVcnt
					if (LoadCoreLogs_SVM(pDebugParms, pid, tid, (SVM_Parms*)core->CoreSpecs, &core->CoreLog[d].SVMResult) != 0) return -1;
					//-- allocate SVMWeight (when Dotraining, this is called directly from SVMTrain)
					mallocSVMLog(&core->CoreLog[d], core->CoreLog[d].SVMResult.SVcount, core->SampleLen);
					//-- then, load SVs
					if (LoadCoreImage_SVM(pDebugParms, pid, tid, (SVM_Parms*)core->CoreSpecs, core->CoreLog[d].SVMFinalW) != 0) return -1;
				}
				break;
			}
		}
	}
	return 0;

}

//--
void setCoreInfo_Pre(tEngineDef* pEngineParms, tDataShape* pDataParms, NN_Parms** NNInfo, GA_Parms** GAInfo, SOM_Parms** SOMInfo, SVM_Parms** SVMInfo) {
	pEngineParms->InputCount = pDataParms->SampleLen;
	pEngineParms->OutputCount = pDataParms->PredictionLen;
	switch (pEngineParms->EngineType) {
	case ENGINE_NN:
		pEngineParms->Core[0][0].CoreSpecs = new NN_Parms();
		(*NNInfo) = (NN_Parms*)pEngineParms->Core[0][0].CoreSpecs;
		(*NNInfo)->InputCount = pDataParms->SampleLen;
		(*NNInfo)->OutputCount = pDataParms->PredictionLen;
		break;
	case ENGINE_GA:
		pEngineParms->Core[0][0].CoreSpecs = new GA_Parms();
		(*GAInfo) = (GA_Parms*)pEngineParms->Core[0][0].CoreSpecs;
		(*GAInfo)->InputCount = pDataParms->SampleLen;
		(*GAInfo)->OutputCount = pDataParms->PredictionLen;
		break;
	case ENGINE_SOM:
		pEngineParms->Core[0][0].CoreSpecs = new SOM_Parms();
		(*SOMInfo) = (SOM_Parms*)pEngineParms->Core[0][0].CoreSpecs;
		(*SOMInfo)->InputCount = pDataParms->SampleLen;
		(*SOMInfo)->OutputCount = pDataParms->PredictionLen;
		break;
	case ENGINE_SVM:
		pEngineParms->Core[0][0].CoreSpecs = new SVM_Parms();
		(*SVMInfo) = (SVM_Parms*)pEngineParms->Core[0][0].CoreSpecs;
		(*SVMInfo)->InputCount = pDataParms->SampleLen;
		//(*SVMInfo)->OutputCount = pDataParms->PredictionLen;
		break;
	case ENGINE_WNN:
		//-- L0
		for (int c = 0; c < pEngineParms->CoresCount[0]; c++) {
			pEngineParms->Core[0][c].CoreSpecs = new NN_Parms();
			pEngineParms->Core[0][c].CoreType = ENGINE_NN;
			(*NNInfo) = (NN_Parms*)pEngineParms->Core[0][c].CoreSpecs;
			if ((*NNInfo)->BP_Algo == BP_QING) pDataParms->PredictionLen = pDataParms->SampleLen;
			(*NNInfo)->InputCount = pDataParms->SampleLen;
			(*NNInfo)->OutputCount = pDataParms->PredictionLen;
		}
		//-- L1
		pEngineParms->Core[1][0].CoreSpecs = new NN_Parms();
		pEngineParms->Core[1][0].CoreType = ENGINE_NN;
		(*NNInfo) = (NN_Parms*)pEngineParms->Core[1][0].CoreSpecs;
		(*NNInfo)->InputCount = (pDataParms->PredictionLen*pEngineParms->CoresCount[0]) + pEngineParms->TSFcnt;
		(*NNInfo)->OutputCount = pDataParms->PredictionLen;
		break;
	case ENGINE_XIE:
		pEngineParms->Core[0][0].CoreSpecs = new SVM_Parms();
		pEngineParms->Core[0][0].CoreType = ENGINE_SVM;
		(*SVMInfo) = (SVM_Parms*)pEngineParms->Core[0][0].CoreSpecs;
		(*SVMInfo)->InputCount = pDataParms->SampleLen;
		//--
		pEngineParms->Core[0][1].CoreSpecs = new NN_Parms();
		pEngineParms->Core[0][1].CoreType = ENGINE_NN;
		(*NNInfo) = (NN_Parms*)pEngineParms->Core[0][1].CoreSpecs;
		if ((*NNInfo)->BP_Algo == BP_QING) pDataParms->PredictionLen = pDataParms->SampleLen;
		(*NNInfo)->InputCount = pDataParms->SampleLen;
		(*NNInfo)->OutputCount = pDataParms->PredictionLen;
		//--
		pEngineParms->Core[1][0].CoreSpecs = new NN_Parms();
		pEngineParms->Core[1][0].CoreType = ENGINE_NN;
		(*NNInfo) = (NN_Parms*)pEngineParms->Core[1][0].CoreSpecs;
		if ((*NNInfo)->BP_Algo == BP_QING) pDataParms->PredictionLen = pDataParms->SampleLen;
		(*NNInfo)->InputCount = 2 * pDataParms->PredictionLen;
		(*NNInfo)->OutputCount = pDataParms->PredictionLen;
		break;
	}
}
void setCoreInfo_Post(tEngineDef* pEngineParms, tDataShape* pDataParms, NN_Parms** NNInfo, GA_Parms** GAInfo, SOM_Parms** SOMInfo, SVM_Parms** SVMInfo) {
	switch (pEngineParms->EngineType) {
	case ENGINE_NN:
		if ((*NNInfo)->BP_Algo == BP_QING) pDataParms->PredictionLen = pDataParms->SampleLen;
		pEngineParms->Core[0][0].TimeStepsCount = pDataParms->SampleCount * ( ((*NNInfo)->BP_Algo==BP_SCGD)? (*NNInfo)->SCGDmaxK : (*NNInfo)->MaxEpochs );
		pEngineParms->Core[0][0].SampleLen = (*NNInfo)->InputCount;
		pEngineParms->Core[0][0].TargetLen = (*NNInfo)->OutputCount;
		pEngineParms->Core[0][0].MSECount = (*NNInfo)->MaxEpochs;
		pEngineParms->Core[0][0].RunCount = pDataParms->HistoryLen + pDataParms->PredictionLen;
		break;
	case ENGINE_GA:
		break;
	case ENGINE_SOM:
		(*SOMInfo)->BaseTD = (*SOMInfo)->OutputCount;
		break;
	case ENGINE_SVM:
		pEngineParms->Core[0][0].TimeStepsCount = (*SVMInfo)->MaxEpochs;
		pEngineParms->Core[0][0].SampleLen = (*SVMInfo)->InputCount;
		pEngineParms->Core[0][0].TargetLen = pDataParms->PredictionLen;
		pEngineParms->Core[0][0].MSECount = (*SVMInfo)->MaxEpochs;
		pEngineParms->Core[0][0].RunCount = pDataParms->HistoryLen + pDataParms->PredictionLen;
		break;
	case ENGINE_WNN:
		//-- L0
		for (int c = 0; c < pEngineParms->CoresCount[0]; c++) {
			(*NNInfo) = (NN_Parms*)pEngineParms->Core[0][c].CoreSpecs;
			pEngineParms->Core[0][c].TimeStepsCount = (*NNInfo)->MaxEpochs * pDataParms->SampleCount * (((*NNInfo)->BP_Algo == BP_SCGD) ? (*NNInfo)->SCGDmaxK : 1);
			pEngineParms->Core[0][c].SampleLen = (*NNInfo)->InputCount;
			pEngineParms->Core[0][c].TargetLen = (*NNInfo)->OutputCount;
			pEngineParms->Core[0][c].MSECount = (*NNInfo)->MaxEpochs;
			pEngineParms->Core[0][c].RunCount = pDataParms->HistoryLen + pDataParms->PredictionLen;
		}
		//-- L1
		(*NNInfo) = (NN_Parms*)pEngineParms->Core[1][0].CoreSpecs;
		pEngineParms->Core[1][0].TimeStepsCount = (*NNInfo)->MaxEpochs * pDataParms->SampleCount * (((*NNInfo)->BP_Algo == BP_SCGD) ? (*NNInfo)->SCGDmaxK : 1);
		pEngineParms->Core[1][0].SampleLen = pEngineParms->Core[0][0].TargetLen*pEngineParms->CoresCount[0] + pEngineParms->TSFcnt;	//(*NNInfo)->InputCount;
		pEngineParms->Core[1][0].TargetLen = (*NNInfo)->OutputCount;
		pEngineParms->Core[1][0].MSECount = (*NNInfo)->MaxEpochs;
		pEngineParms->Core[1][0].RunCount = pDataParms->HistoryLen + pDataParms->PredictionLen;
		break;
	case ENGINE_XIE:
		//-- L0svm
		pEngineParms->Core[0][0].TimeStepsCount = (*SVMInfo)->MaxEpochs;
		pEngineParms->Core[0][0].SampleLen = (*SVMInfo)->InputCount;
		pEngineParms->Core[0][0].TargetLen = pDataParms->PredictionLen;
		pEngineParms->Core[0][0].MSECount = (*SVMInfo)->MaxEpochs;
		pEngineParms->Core[0][0].RunCount = pDataParms->HistoryLen + pDataParms->PredictionLen;
		//-- L0nn
		(*NNInfo) = (NN_Parms*)pEngineParms->Core[0][1].CoreSpecs;
		pEngineParms->Core[0][1].TimeStepsCount = (*NNInfo)->MaxEpochs * pDataParms->SampleCount * (((*NNInfo)->BP_Algo == BP_SCGD) ? (*NNInfo)->SCGDmaxK : 1);
		pEngineParms->Core[0][1].SampleLen = (*NNInfo)->InputCount;
		pEngineParms->Core[0][1].TargetLen = (*NNInfo)->OutputCount;
		pEngineParms->Core[0][1].MSECount = (*NNInfo)->MaxEpochs;
		pEngineParms->Core[0][1].RunCount = pDataParms->HistoryLen + pDataParms->PredictionLen;
		//-- L1nn
		(*NNInfo) = (NN_Parms*)pEngineParms->Core[1][0].CoreSpecs;
		pEngineParms->Core[1][0].TimeStepsCount = (*NNInfo)->MaxEpochs * pDataParms->SampleCount * (((*NNInfo)->BP_Algo == BP_SCGD) ? (*NNInfo)->SCGDmaxK : 1);
		pEngineParms->Core[1][0].SampleLen = pEngineParms->Core[0][0].TargetLen + pEngineParms->Core[0][1].TargetLen;	//(*NNInfo)->InputCount;
		pEngineParms->Core[1][0].TargetLen = (*NNInfo)->OutputCount;
		pEngineParms->Core[1][0].MSECount = (*NNInfo)->MaxEpochs;
		pEngineParms->Core[1][0].RunCount = pDataParms->HistoryLen + pDataParms->PredictionLen;
		break;
	}
}

EXPORT int  ForecastParamLoader(tForecastParms* fParms) {
	int l, c;
	NN_Parms* NNInfo = nullptr;	// not malloced. just used as a shortcut inside engine case
	GA_Parms* GAInfo = nullptr;
	SOM_Parms* SOMInfo = nullptr;
	SVM_Parms* SVMInfo = nullptr;

	//-- 1. get Debug Parameters (needs to be before LoadXXXParms)
	if (getParam(fParms->iniParms, "Forecaster.DebugLevel", &fParms->DebugParms.DebugLevel) < 0)				return -1;
	if (getParam(fParms->iniParms, "Forecaster.PauseOnError", &fParms->DebugParms.PauseOnError) < 0)			return -1;
	if (getParam(fParms->iniParms, "Forecaster.DebugFileName", fParms->DebugParms.fName) < 0)					return -1;
	if (getParam(fParms->iniParms, "Forecaster.DebugFilePath", fParms->DebugParms.fPath) < 0)					return -1;
	if (getParam(fParms->iniParms, "Forecaster.ThreadSafeLogging", &fParms->DebugParms.ThreadSafeLogging) < 0)	return -1;
	if (getParam(fParms->iniParms, "Forecaster.DumpSampleData", &fParms->DebugParms.DumpSampleData) < 0)		return -1;
	if (getParam(fParms->iniParms, "Results.SaveNothing", &fParms->DebugParms.SaveNothing) < 0)					return -1;
	if (getParam(fParms->iniParms, "Results.SaveMSE", &fParms->DebugParms.SaveMSE) < 0)							return -1;
	if (getParam(fParms->iniParms, "Results.SaveRUN", &fParms->DebugParms.SaveRun) < 0)							return -1;
	if (getParam(fParms->iniParms, "Results.SaveImages", &fParms->DebugParms.SaveImages) < 0)					return -1;
	if (getParam(fParms->iniParms, "Results.SaveInternals", &fParms->DebugParms.SaveInternals) < 0)				return -1;
	if (getParam(fParms->iniParms, "Results.Destination", &fParms->DebugParms.DebugDest, enumlist) < 0)			return -1;
	if (getParam(fParms->iniParms, "Results.DBUser", fParms->DebugParms.DebugDB->DBUser) < 0)					return -1;
	if (getParam(fParms->iniParms, "Results.DBPassword", fParms->DebugParms.DebugDB->DBPassword) < 0)			return -1;
	if (getParam(fParms->iniParms, "Results.DBConnString", fParms->DebugParms.DebugDB->DBConnString) < 0)		return -1;
	//fParms->DebugParms.DebugDB->DBCtx = NULL;

	//-- 2. Tester Data Source parameters (DatasetsCount needed before LoadXXXImage)
	if (getParam(fParms->iniParms, "DataSource.SourceType", &fParms->DataParms.DataSourceType, enumlist) < 0)		return -1;
	if (fParms->DataParms.DataSourceType == SOURCE_DATA_FROM_FXDB) {
		if (getParam(fParms->iniParms, "DataSource.DBConn.DBUser", fParms->FXDBInfo.FXDB->DBUser) < 0)				return -1;
		if (getParam(fParms->iniParms, "DataSource.DBConn.DBPassword", fParms->FXDBInfo.FXDB->DBPassword) < 0)		return -1;
		if (getParam(fParms->iniParms, "DataSource.DBConn.DBConnString", fParms->FXDBInfo.FXDB->DBConnString) < 0)	return -1;
		//fParms->FXDBInfo.FXDB->DBCtx = NULL;
		if (getParam(fParms->iniParms, "DataSource.Symbol", fParms->FXDBInfo.Symbol) < 0)							return -1;
		if (getParam(fParms->iniParms, "DataSource.TimeFrame", fParms->FXDBInfo.TimeFrame) < 0)						return -1;
		if (getParam(fParms->iniParms, "DataSource.IsFilled", &fParms->FXDBInfo.IsFilled) < 0)						return -1;
		//-- bardatatypes, fParms->DataParms->DatasetsCount...
		fParms->DataParms.DatasetsCount = getParam(fParms->iniParms, "DataSource.BarDataTypes", &fParms->FXDBInfo.BarDataType, enumlist); if (fParms->DataParms.DatasetsCount < 0) return -1;
		fParms->FXDBInfo.BarDataTypeCount = fParms->DataParms.DatasetsCount;
		strcpy(fParms->DataSourceFileInfo.FileName, "");
		fParms->DataParms.DataSource = &fParms->FXDBInfo;
	} else {
		if (getParam(fParms->iniParms, "DataSource.FileName", fParms->DataSourceFileInfo.FileName) < 0)										return -1;
		if (getParam(fParms->iniParms, "DataSource.TextFieldSeparator", &fParms->DataSourceFileInfo.FieldSep, enumlist) < 0)				return -1;
		fParms->DataParms.DatasetsCount = getParam(fParms->iniParms, "DataSource.FileDatasets", &fParms->DataSourceFileInfo.FileDataSet);
		if (fParms->DataParms.DatasetsCount<0)																						return -1;
		if (getParam(fParms->iniParms, "DataSource.CalcFileDataBW", &fParms->DataSourceFileInfo.CalcFileDataBW) < 0)						return -1;
		if (fParms->DataSourceFileInfo.CalcFileDataBW>0) {
			int kaz = getParam(fParms->iniParms, "DataSource.DStoCalcBWFrom", &fParms->DataSourceFileInfo.FileBWDataSet);
			if (kaz<0)																												return -1;
		}
		strcpy(fParms->FXDBInfo.Symbol, "");
		strcpy(fParms->FXDBInfo.TimeFrame, "");
		fParms->FXDBInfo.IsFilled = 0;
		fParms->FXDBInfo.BarDataTypeCount = 0;
		fParms->DataSourceFileInfo.FileDataSetsCount = fParms->DataParms.DatasetsCount;
		fParms->DataParms.DataSource = &fParms->DataSourceFileInfo;
	}

	//-- 3. set TSFs
	int useTSF;
	if (getParam(fParms->iniParms, "DataParms.UseTSFeatures", &useTSF) < 0) return -1;
	if (useTSF > 0) {
		fParms->EngineParms.TSFcnt = getParam(fParms->iniParms, "DataParms.TSFeatures", &fParms->EngineParms.TSFid, enumlist); if (fParms->EngineParms.TSFcnt < 0) return -1;
	} else {
		fParms->EngineParms.TSFcnt = 0;
	}

	//-- 4. DoTraining and HaveFutureData

	//if (getParam(fParms->iniParms, "Forecaster.DoTraining", &fParms->DoTraining) < 0)					return -1;
	if (getParam(fParms->iniParms, "Forecaster.Action", &fParms->Action, enumlist) <0)					return -1;
	if (getParam(fParms->iniParms, "Forecaster.HaveFutureData", &fParms->HaveFutureData) < 0)			return -1;

	//-- 5a. if using a saved engine, get EngineParms and DataShape here
	if (fParms->Action != TRAIN_SAVE_RUN) {
		if (getParam(fParms->iniParms, "SavedEngine.ProcessId", &fParms->SavedEngine.ProcessId) < 0)	return -1;
		if (getParam(fParms->iniParms, "SavedEngine.TestId", &fParms->SavedEngine.TestId) < 0)			return -1;
		if (getParam(fParms->iniParms, "SavedEngine.DatasetId", &fParms->SavedEngine.DatasetId) < 0)	return -1;
		fParms->DataParms.ValidationShift = 0;

		int dscnt_from_file = fParms->DataParms.DatasetsCount;
		if (LoadDataParms(&fParms->DebugParms, fParms->SavedEngine.ProcessId, &fParms->DataParms) != 0) return -1;
		fParms->DataParms.SampleCount = fParms->DataParms.HistoryLen - fParms->DataParms.SampleLen;
		if (LoadEngineParms(&fParms->DebugParms, fParms->SavedEngine.ProcessId, &fParms->EngineParms) != 0) return -1;

		if (fParms->Action==ADD_SAMPLES) {
			// if ADD_SAMPLES, we must have the same DatasetsCount of the original Training (we could do otherwise, this is the simplest way...)
			if (fParms->DataParms.DatasetsCount!=dscnt_from_file) {
				LogWrite(&fParms->DebugParms, LOG_ERROR, "When adding samples to an existing engine, DatasetsCount must be the same. We have %d in original engine, and %d from parameter file...\n", 2, fParms->DataParms.DatasetsCount, dscnt_from_file);
				return -1;
			}
			// we also need ro retrieve the last AdderId from, to increase it
			fParms->EngineParms.AdderCount++;
		}

		//-- before loading cores, we need to set layout based on EngineType just loaded
		if (setEngineLayout(fParms) != 0) return -1;
		setCoreInfo_Pre(&fParms->EngineParms, &fParms->DataParms, &NNInfo, &GAInfo, &SOMInfo, &SVMInfo);
		//-- Core Parameters.
		if (LoadCoreParms(&fParms->DebugParms, fParms->SavedEngine.ProcessId, &fParms->EngineParms, &fParms->DataParms) != 0) return -1;
		setCoreInfo_Post(&fParms->EngineParms, &fParms->DataParms, &NNInfo, &GAInfo, &SOMInfo, &SVMInfo);
		//-- Core Logs
		mallocCoreLogs(fParms);
		// Finally, Core Image
		if (LoadCoreImage(&fParms->DebugParms, fParms->SavedEngine.ProcessId, fParms->SavedEngine.TestId, fParms->SavedEngine.DatasetId, &fParms->EngineParms, &fParms->DataParms, &fParms->SavedEngine) != 0) return -1;
	} else {
		//-- 5b
		if (getParam(fParms->iniParms, "Forecaster.Engine", &fParms->EngineParms.EngineType, enumlist) < 0)	return -1;
		fParms->EngineParms.AdderCount = 0;
		if (setEngineLayout(fParms) != 0) return -1;

		//-- Data Shape parameters 		
		if (getParam(fParms->iniParms, "DataParms.HistoryLen", &fParms->DataParms.HistoryLen) < 0)								return -1;
		if (getParam(fParms->iniParms, "DataParms.SampleLen", &fParms->DataParms.SampleLen) < 0)								return -1;
		if (getParam(fParms->iniParms, "DataParms.PredictionLen", &fParms->DataParms.PredictionLen) < 0)						return -1;
		if (getParam(fParms->iniParms, "DataParms.ValidationShift", &fParms->DataParms.ValidationShift) < 0)					return -1;
		if (getParam(fParms->iniParms, "DataParms.DataTransformation", &fParms->DataParms.DataTransformation, enumlist) < 0)	return -1;
		if (getParam(fParms->iniParms, "DataParms.WiggleRoom", &fParms->DataParms.wiggleRoom) < 0)								return -1;
		fParms->DataParms.SampleCount = fParms->DataParms.HistoryLen - fParms->DataParms.SampleLen;

		//-- Engine-specific parameters
		setCoreInfo_Pre(&fParms->EngineParms, &fParms->DataParms, &NNInfo, &GAInfo, &SOMInfo, &SVMInfo);

		switch (fParms->EngineParms.EngineType) {
		case ENGINE_NN:
			NNInfo = (NN_Parms*)fParms->EngineParms.Core[0][0].CoreSpecs;
			if (getParam(fParms->iniParms, "NNInfo.UseContext", &NNInfo->UseContext) < 0)							return -1;
			if (getParam(fParms->iniParms, "NNInfo.TrainingBatchCount", &NNInfo->TrainingBatchCount) < 0)			return -1;
			if (getParam(fParms->iniParms, "NNInfo.BP_Algo", &NNInfo->BP_Algo, enumlist) < 0)						return -1;
			if (getParam(fParms->iniParms, "NNInfo.ActivationFunction", &NNInfo->ActivationFunction, enumlist) < 0)	return -1;
			if (getParam(fParms->iniParms, "NNInfo.StopAtDivergence", &NNInfo->StopAtDivergence) < 0)				return -1;
			if (getParam(fParms->iniParms, "NNInfo.MaxEpochs", &NNInfo->MaxEpochs) < 0)								return -1;
			if (getParam(fParms->iniParms, "NNInfo.LearningRate", &NNInfo->LearningRate) < 0)						return -1;
			if (getParam(fParms->iniParms, "NNInfo.Std.LearningMomentum", &NNInfo->LearningMomentum) < 0)			return -1;
			if (getParam(fParms->iniParms, "NNInfo.TargetMSE", &NNInfo->TargetMSE) < 0)								return -1;
			if (getParam(fParms->iniParms, "NNInfo.Qing.HCPbeta", &NNInfo->HCPbeta) < 0)							return -1;
			if (getParam(fParms->iniParms, "NNInfo.Qprop.mu", &NNInfo->mu) < 0)										return -1;
			if (getParam(fParms->iniParms, "NNInfo.Rprop.d0", &NNInfo->d0) < 0)										return -1;
			if (getParam(fParms->iniParms, "NNInfo.SCGD.maxK", &NNInfo->SCGDmaxK) < 0)								return -1;
			if (getParam(fParms->iniParms, "NNInfo.LevelRatios", &NNInfo->LevelRatioS[0]) < 0)						return -1;
			break;
		case ENGINE_GA:
			GAInfo = (GA_Parms*)fParms->EngineParms.Core[0][0].CoreSpecs;
			if (getParam(fParms->iniParms, "GAInfo.SlidingFactor", &GAInfo->SlidingFactor) < 0)								return -1;
			if (getParam(fParms->iniParms, "GAInfo.Levels", &GAInfo->Levels) < 0)											return -1;
			if (getParam(fParms->iniParms, "GAInfo.PopulationSize", &GAInfo->PopulationSize) < 0)							return -1;
			if (getParam(fParms->iniParms, "GAInfo.MaxGenerations", &GAInfo->MaxGenerations) < 0)							return -1;
			if (getParam(fParms->iniParms, "GAInfo.TargetFitness", &GAInfo->TargetFitness) < 0)								return -1;
			if (getParam(fParms->iniParms, "GAInfo.FitnessSkewingFactor", &GAInfo->FitnessSkewingFactor) < 0)				return -1;
			if (getParam(fParms->iniParms, "GAInfo.FitnessThreshold", &GAInfo->FitnessThreshold) < 0)						return -1;
			if (getParam(fParms->iniParms, "GAInfo.CrossOverProbability", &GAInfo->CrossOverProbability) < 0)				return -1;
			if (getParam(fParms->iniParms, "GAInfo.MutationProbability", &GAInfo->MutationProbability) < 0)					return -1;
			if (getParam(fParms->iniParms, "GAInfo.CrossSelfRate", &GAInfo->CrossSelfRate) < 0)								return -1;
			if (getParam(fParms->iniParms, "GAInfo.RouletteMaxTries", &GAInfo->RouletteMaxTries) < 0)						return -1;
			if (getParam(fParms->iniParms, "GAInfo.ADF_Tree_FixedValues_Ratio", &GAInfo->ADF_Tree_FixedValues_Ratio) < 0)	return -1;
			if (getParam(fParms->iniParms, "GAInfo.ADF_Tree_DataPoints_Ratio", &GAInfo->ADF_Tree_DataPoints_Ratio) < 0)		return -1;
			if (getParam(fParms->iniParms, "GAInfo.ADF_Leaf_FixedValues_Ratio", &GAInfo->ADF_Leaf_FixedValues_Ratio) < 0)	return -1;
			if (getParam(fParms->iniParms, "GAInfo.MaxReRuns", &GAInfo->MaxReRuns) < 0)										return -1;
			if (getParam(fParms->iniParms, "GAInfo.BestChrPath", GAInfo->BestChrPath) < 0)									return -1;
			break;
		case ENGINE_SOM:
			SOMInfo = (SOM_Parms*)fParms->EngineParms.Core[0][0].CoreSpecs;
			if (getParam(fParms->iniParms, "SOMInfo.OutputCount", &SOMInfo->OutputCount) < 0)			return -1;
			if (getParam(fParms->iniParms, "SOMInfo.OutputWidth", &SOMInfo->OutputWidth) < 0)			return -1;
			if (getParam(fParms->iniParms, "SOMInfo.MaxEpochs", &SOMInfo->MaxEpochs) < 0)				return -1;
			if (getParam(fParms->iniParms, "SOMInfo.TDFunction", &SOMInfo->TDFunction, enumlist) < 0)	return -1;
			if (getParam(fParms->iniParms, "SOMInfo.BaseLR", &SOMInfo->BaseLR) < 0)						return -1;
			if (getParam(fParms->iniParms, "SOMInfo.LRFunction", &SOMInfo->LRFunction, enumlist) < 0)	return -1;
			break;
		case ENGINE_SVM:
			SVMInfo = (SVM_Parms*)fParms->EngineParms.Core[0][0].CoreSpecs;
			if (getParam(fParms->iniParms, "SVMInfo.DebugLevel", &SVMInfo->DebugLevel) < 0)				return -1;
			if (getParam(fParms->iniParms, "SVMInfo.C", &SVMInfo->C) < 0)								return -1;
			if (getParam(fParms->iniParms, "SVMInfo.IterToShrink", &SVMInfo->svmIterToShrink) < 0)		return -1;
			if (getParam(fParms->iniParms, "SVMInfo.MaxEpochs", &SVMInfo->MaxEpochs) < 0)				return -1;
			if (getParam(fParms->iniParms, "SVMInfo.epsilon", &SVMInfo->epsilon) < 0)					return -1;
			if (getParam(fParms->iniParms, "SVMInfo.KernelType", &SVMInfo->KernelType, enumlist) < 0)	return -1;
			if (getParam(fParms->iniParms, "SVMInfo.PolyDegree", &SVMInfo->PolyDegree) < 0)				return -1;
			if (getParam(fParms->iniParms, "SVMInfo.RBFGamma", &SVMInfo->RBFGamma) < 0)					return -1;
			if (getParam(fParms->iniParms, "SVMInfo.CoefLin", &SVMInfo->CoefLin) < 0)					return -1;
			if (getParam(fParms->iniParms, "SVMInfo.CoefConst", &SVMInfo->CoefConst) < 0)				return -1;
			if (getParam(fParms->iniParms, "SVMInfo.KernelCacheSize", &SVMInfo->KernelCacheSize) < 0)	return -1;
			if (getParam(fParms->iniParms, "SVMInfo.CustomKernel", SVMInfo->CustomKernel) < 0)			return -1;
			//--
			if (getParam(fParms->iniParms, "SVMInfo.SlackNorm", &SVMInfo->SlackNorm, enumlist) < 0)				return -1;
			if (getParam(fParms->iniParms, "SVMInfo.RescalingMethod", &SVMInfo->RescalingMethod, enumlist) < 0)	return -1;
			if (getParam(fParms->iniParms, "SVMInfo.LossFunction", &SVMInfo->LossFunction, enumlist) < 0)		return -1;
			if (getParam(fParms->iniParms, "SVMInfo.LearningAlgo", &SVMInfo->LearningAlgo, enumlist) < 0)		return -1;
			if (getParam(fParms->iniParms, "SVMInfo.NewConstrEtrain", &SVMInfo->NewConstrEtrain) < 0)			return -1;
			if (getParam(fParms->iniParms, "SVMINfo.CCacheSize", &SVMInfo->CCacheSize) < 0)						return -1;
			if (getParam(fParms->iniParms, "SVMInfo.BatchSize", &SVMInfo->BatchSize) < 0)						return -1;
			if (getParam(fParms->iniParms, "SVMInfo.NewVarSinQP", &SVMInfo->NewVarSinQP) < 0)					return -1;
			break;
		case ENGINE_WNN:
			l = 0;
			for (c = 0; c < fParms->EngineParms.CoresCount[l]; c++) {
				NNInfo = (NN_Parms*)fParms->EngineParms.Core[l][c].CoreSpecs;
				if (getParam(fParms->iniParms, "WNNInfo.L0.UseContext", &NNInfo->UseContext) <0)							return -1;
				if (getParam(fParms->iniParms, "WNNInfo.L0.TrainingBatchCount", &NNInfo->TrainingBatchCount) < 0)			return -1;
				if (getParam(fParms->iniParms, "WNNInfo.L0.BP_Algo", &NNInfo->BP_Algo, enumlist) <0)						return -1;
				if (getParam(fParms->iniParms, "WNNInfo.L0.ActivationFunction", &NNInfo->ActivationFunction, enumlist) <0)	return -1;
				if (getParam(fParms->iniParms, "WNNInfo.L0.StopAtDivergence", &NNInfo->StopAtDivergence) <0)				return -1;
				if (getParam(fParms->iniParms, "WNNInfo.L0.MaxEpochs", &NNInfo->MaxEpochs) <0)								return -1;
				if (getParam(fParms->iniParms, "WNNInfo.L0.LearningRate", &NNInfo->LearningRate) <0)						return -1;
				if (getParam(fParms->iniParms, "WNNInfo.L0.TargetMSE", &NNInfo->TargetMSE) <0)								return -1;
				if (getParam(fParms->iniParms, "WNNInfo.L0.Std.LearningMomentum", &NNInfo->LearningMomentum) <0)			return -1;
				if (getParam(fParms->iniParms, "WNNInfo.L0.Qing.HCPbeta", &NNInfo->HCPbeta) <0)								return -1;
				if (getParam(fParms->iniParms, "WNNInfo.L0.QProp.mu", &NNInfo->mu) <0)										return -1;
				if (getParam(fParms->iniParms, "WNNInfo.L0.RProp.d0", &NNInfo->d0) <0)										return -1;
				if (getParam(fParms->iniParms, "WNNInfo.L0.SCGDmaxK", &NNInfo->SCGDmaxK) < 0)								return -1;
				if (getParam(fParms->iniParms, "WNNInfo.L0.LevelRatios", &NNInfo->LevelRatioS[0]) <0)						return -1;
			}
			l = 1;
			NNInfo = (NN_Parms*)fParms->EngineParms.Core[l][0].CoreSpecs;
			if (getParam(fParms->iniParms, "WNNInfo.L1.UseContext", &NNInfo->UseContext) <0)							return -1;
			if (getParam(fParms->iniParms, "WNNInfo.L1.TrainingBatchCount", &NNInfo->TrainingBatchCount) < 0)			return -1;
			if (getParam(fParms->iniParms, "WNNInfo.L1.BP_Algo", &NNInfo->BP_Algo, enumlist) <0)						return -1;
			if (getParam(fParms->iniParms, "WNNInfo.L1.ActivationFunction", &NNInfo->ActivationFunction, enumlist) <0)	return -1;
			if (getParam(fParms->iniParms, "WNNInfo.L1.StopAtDivergence", &NNInfo->StopAtDivergence) <0)				return -1;
			if (getParam(fParms->iniParms, "WNNInfo.L1.MaxEpochs", &NNInfo->MaxEpochs) <0)								return -1;
			if (getParam(fParms->iniParms, "WNNInfo.L1.LearningRate", &NNInfo->LearningRate) <0)						return -1;
			if (getParam(fParms->iniParms, "WNNInfo.L1.Std.LearningMomentum", &NNInfo->LearningMomentum) <0)			return -1;
			if (getParam(fParms->iniParms, "WNNInfo.L1.TargetMSE", &NNInfo->TargetMSE) <0)								return -1;
			if (getParam(fParms->iniParms, "WNNInfo.L1.Qing.HCPbeta", &NNInfo->HCPbeta) <0)								return -1;
			if (getParam(fParms->iniParms, "WNNInfo.L1.QProp.mu", &NNInfo->mu) <0)										return -1;
			if (getParam(fParms->iniParms, "WNNInfo.L1.RProp.d0", &NNInfo->d0) <0)										return -1;
			if (getParam(fParms->iniParms, "WNNInfo.L1.SCGDmaxK", &NNInfo->SCGDmaxK) < 0)								return -1;
			if (getParam(fParms->iniParms, "WNNInfo.L1.LevelRatios", &NNInfo->LevelRatioS[0]) <0)						return -1;
			break;
		case ENGINE_XIE:
			SVMInfo = (SVM_Parms*)fParms->EngineParms.Core[0][0].CoreSpecs;
			if (getParam(fParms->iniParms, "XIEInfo.SVM.DebugLevel", &SVMInfo->DebugLevel) < 0)				return -1;
			if (getParam(fParms->iniParms, "XIEInfo.SVM.C", &SVMInfo->C) < 0)								return -1;
			if (getParam(fParms->iniParms, "XIEInfo.SVM.IterToShrink", &SVMInfo->svmIterToShrink) < 0)		return -1;
			if (getParam(fParms->iniParms, "XIEInfo.SVM.MaxEpochs", &SVMInfo->MaxEpochs) < 0)				return -1;
			if (getParam(fParms->iniParms, "XIEInfo.SVM.epsilon", &SVMInfo->epsilon) < 0)					return -1;
			if (getParam(fParms->iniParms, "XIEInfo.SVM.KernelType", &SVMInfo->KernelType, enumlist) < 0)	return -1;
			if (getParam(fParms->iniParms, "XIEInfo.SVM.PolyDegree", &SVMInfo->PolyDegree) < 0)				return -1;
			if (getParam(fParms->iniParms, "XIEInfo.SVM.RBFGamma", &SVMInfo->RBFGamma) < 0)					return -1;
			if (getParam(fParms->iniParms, "XIEInfo.SVM.CoefLin", &SVMInfo->CoefLin) < 0)					return -1;
			if (getParam(fParms->iniParms, "XIEInfo.SVM.CoefConst", &SVMInfo->CoefConst) < 0)				return -1;
			if (getParam(fParms->iniParms, "XIEInfo.SVM.KernelCacheSize", &SVMInfo->KernelCacheSize) < 0)	return -1;
			if (getParam(fParms->iniParms, "XIEInfo.SVM.CustomKernel", SVMInfo->CustomKernel) < 0)			return -1;
			//--
			if (getParam(fParms->iniParms, "XIEInfo.SVM.SlackNorm", &SVMInfo->SlackNorm, enumlist) < 0)				return -1;
			if (getParam(fParms->iniParms, "XIEInfo.SVM.RescalingMethod", &SVMInfo->RescalingMethod, enumlist) < 0)	return -1;
			if (getParam(fParms->iniParms, "XIEInfo.SVM.LossFunction", &SVMInfo->LossFunction, enumlist) < 0)		return -1;
			if (getParam(fParms->iniParms, "XIEInfo.SVM.LearningAlgo", &SVMInfo->LearningAlgo, enumlist) < 0)		return -1;
			if (getParam(fParms->iniParms, "XIEInfo.SVM.NewConstrEtrain", &SVMInfo->NewConstrEtrain) < 0)			return -1;
			if (getParam(fParms->iniParms, "XIEInfo.SVM.CCacheSize", &SVMInfo->CCacheSize) < 0)						return -1;
			if (getParam(fParms->iniParms, "XIEInfo.SVM.BatchSize", &SVMInfo->BatchSize) < 0)						return -1;
			if (getParam(fParms->iniParms, "XIEInfo.SVM.NewVarSinQP", &SVMInfo->NewVarSinQP) < 0)					return -1;

			NNInfo = (NN_Parms*)fParms->EngineParms.Core[0][1].CoreSpecs;
			if (getParam(fParms->iniParms, "XIEInfo.NN0.UseContext", &NNInfo->UseContext) < 0)								return -1;
			if (getParam(fParms->iniParms, "XIEInfo.NN0.TrainingBatchCount", &NNInfo->TrainingBatchCount) < 0)				return -1;
			if (getParam(fParms->iniParms, "XIEInfo.NN0.BP_Algo", &NNInfo->BP_Algo, enumlist) < 0)							return -1;
			if (getParam(fParms->iniParms, "XIEInfo.NN0.ActivationFunction", &NNInfo->ActivationFunction, enumlist) < 0)	return -1;
			if (getParam(fParms->iniParms, "XIEInfo.NN0.StopAtDivergence", &NNInfo->StopAtDivergence) < 0)					return -1;
			if (getParam(fParms->iniParms, "XIEInfo.NN0.MaxEpochs", &NNInfo->MaxEpochs) < 0)								return -1;
			if (getParam(fParms->iniParms, "XIEInfo.NN0.LearningRate", &NNInfo->LearningRate) < 0)							return -1;
			if (getParam(fParms->iniParms, "XIEInfo.NN0.Std.LearningMomentum", &NNInfo->LearningMomentum) < 0)				return -1;
			if (getParam(fParms->iniParms, "XIEInfo.NN0.TargetMSE", &NNInfo->TargetMSE) < 0)								return -1;
			if (getParam(fParms->iniParms, "XIEInfo.NN0.Qing.HCPbeta", &NNInfo->HCPbeta) <0)								return -1;
			if (getParam(fParms->iniParms, "XIEInfo.NN0.QProp.mu", &NNInfo->mu) <0)											return -1;
			if (getParam(fParms->iniParms, "XIEInfo.NN0.RProp.d0", &NNInfo->d0) <0)											return -1;
			if (getParam(fParms->iniParms, "XIEInfo.NN0.SCGDmaxK", &NNInfo->SCGDmaxK) < 0)									return -1;
			if (getParam(fParms->iniParms, "XIEInfo.NN0.LevelRatios", &NNInfo->LevelRatioS[0]) < 0)							return -1;

			NNInfo = (NN_Parms*)fParms->EngineParms.Core[1][0].CoreSpecs;
			if (getParam(fParms->iniParms, "XIEInfo.NN1.UseContext", &NNInfo->UseContext) < 0)								return -1;
			if (getParam(fParms->iniParms, "XIEInfo.NN1.TrainingBatchCount", &NNInfo->TrainingBatchCount) < 0)				return -1;
			if (getParam(fParms->iniParms, "XIEInfo.NN1.BP_Algo", &NNInfo->BP_Algo, enumlist) < 0)							return -1;
			if (getParam(fParms->iniParms, "XIEInfo.NN1.ActivationFunction", &NNInfo->ActivationFunction, enumlist) < 0)	return -1;
			if (getParam(fParms->iniParms, "XIEInfo.NN1.StopAtDivergence", &NNInfo->StopAtDivergence) < 0)					return -1;
			if (getParam(fParms->iniParms, "XIEInfo.NN1.MaxEpochs", &NNInfo->MaxEpochs) < 0)								return -1;
			if (getParam(fParms->iniParms, "XIEInfo.NN1.LearningRate", &NNInfo->LearningRate) < 0)							return -1;
			if (getParam(fParms->iniParms, "XIEInfo.NN1.Std.LearningMomentum", &NNInfo->LearningMomentum) < 0)				return -1;
			if (getParam(fParms->iniParms, "XIEInfo.NN1.TargetMSE", &NNInfo->TargetMSE) < 0)								return -1;
			if (getParam(fParms->iniParms, "XIEInfo.NN1.Qing.HCPbeta", &NNInfo->HCPbeta) <0)								return -1;
			if (getParam(fParms->iniParms, "XIEInfo.NN1.QProp.mu", &NNInfo->mu) <0)											return -1;
			if (getParam(fParms->iniParms, "XIEInfo.NN1.RProp.d0", &NNInfo->d0) <0)											return -1;
			if (getParam(fParms->iniParms, "XIEInfo.NN1.SCGDmaxK", &NNInfo->SCGDmaxK) < 0)									return -1;
			if (getParam(fParms->iniParms, "XIEInfo.NN1.LevelRatios", &NNInfo->LevelRatioS[0]) < 0)							return -1;

			break;
		}

		setCoreInfo_Post(&fParms->EngineParms, &fParms->DataParms, &NNInfo, &GAInfo, &SOMInfo, &SVMInfo);

		//-- Core Logs
		mallocCoreLogs(fParms);
	}

	return 0;
}
EXPORT void ForecastParamFree(tForecastParms* fParms) {
	freeCoreLogs(fParms);
	freeCoreParms(fParms);
}
//--

void SetTSScaleRange(int pEngineType, void* pCoreSpecs, double* oScaleMin, double* oScaleMax) {
	NN_Parms* NNParms;
	GA_Parms* GAParms;
	SOM_Parms* SOMParms;
	SVM_Parms* SVMParms;

	switch (pEngineType) {
	case ENGINE_NN:
		NNParms = (NN_Parms*)pCoreSpecs;
		switch (NNParms->ActivationFunction) {
		case NN_ACTIVATION_TANH:
			(*oScaleMin) = -1;
			(*oScaleMax) = 1;
			break;
		case NN_ACTIVATION_EXP4:
			(*oScaleMin) = 0;
			(*oScaleMax) = 1;
			break;
		default:
			(*oScaleMin) = -1;
			(*oScaleMax) = 1;
			break;
		}
		break;
	case ENGINE_WNN:
		//-- identical to ENGINE_NN
		NNParms = (NN_Parms*)pCoreSpecs;
		switch (NNParms->ActivationFunction) {
		case NN_ACTIVATION_TANH:
			(*oScaleMin) = -1;
			(*oScaleMax) = 1;
			break;
		case NN_ACTIVATION_EXP4:
			(*oScaleMin) = 0;
			(*oScaleMax) = 1;
			break;
		default:
			(*oScaleMin) = -1;
			(*oScaleMax) = 1;
			break;
		}
		break;
	case ENGINE_GA:
		GAParms = (GA_Parms*)pCoreSpecs;
		(*oScaleMin) = -1;
		(*oScaleMax) = 1;
		break;
	case ENGINE_SOM:
		SOMParms = (SOM_Parms*)pCoreSpecs;
		(*oScaleMin) = -1;
		(*oScaleMax) = 1;
		break;
	case ENGINE_SVM:
		SVMParms = (SVM_Parms*)pCoreSpecs;
		(*oScaleMin) = -1;
		(*oScaleMax) = 1;
		break;
	case ENGINE_XIE:
		(*oScaleMin) = -1;
		(*oScaleMax) = 1;
		break;
	}
}

//--
void Train_XXX(tTrainParams* tp) {
	NN_Parms* NNParms;
	GA_Parms* GAParms;
	SOM_Parms* SOMParms;
	SVM_Parms* SVMParms;

	tCoreLog* coreLog = &tp->EngineParms->Core[tp->LayerId][tp->CoreId].CoreLog[tp->DatasetId];

	switch (tp->EngineParms->Core[tp->LayerId][tp->CoreId].CoreType) {
	case ENGINE_NN:
		NNParms = (NN_Parms*)tp->EngineParms->Core[tp->LayerId][tp->CoreId].CoreSpecs;
		tp->TrainSuccess = Train_NN(tp->CorePos, tp->TotCores, tp->ScreenMutex, tp->DebugParms, NNParms, coreLog, tp->useExistingW, tp->SampleCount, tp->SampleT, tp->TargetT, tp->useValidation, tp->SampleV, tp->TargetV);
		tp->ActualEpochs = coreLog->ActualEpochs;
		break;
	case ENGINE_GA:
		GAParms = (GA_Parms*)tp->EngineParms->Core[tp->LayerId][tp->CoreId].CoreSpecs;
		//-- tp->TrainSuccess= Train_GA(...);
		tp->ActualEpochs = coreLog->ActualEpochs;
		break;
	case ENGINE_SOM:
		SOMParms = (SOM_Parms*)tp->EngineParms->Core[tp->LayerId][tp->CoreId].CoreSpecs;
		//-- tp->TrainSuccess= Train_SOM(...);
		tp->ActualEpochs = coreLog->ActualEpochs;
		break;
	case ENGINE_SVM:
		SVMParms = (SVM_Parms*)tp->EngineParms->Core[tp->LayerId][tp->CoreId].CoreSpecs;
		tp->TrainSuccess = Train_SVM(tp->CorePos, tp->TotCores, tp->ScreenMutex, tp->DebugParms, SVMParms, coreLog, tp->useExistingW, tp->SampleCount, tp->SampleT, tp->TargetT, tp->useValidation, tp->SampleV, tp->TargetV);
		tp->ActualEpochs = coreLog->ActualEpochs;
		break;
	}
	//-- update EngineParms->MSECount
	tp->EngineParms->Core[tp->LayerId][tp->CoreId].MSECount = tp->ActualEpochs;
}
void Run_XXX(tRunParams* rp) {

	tCoreLog* coreLog = &rp->EngineParms->Core[rp->LayerId][rp->CoreId].CoreLog[rp->DatasetId];

	int coretype = rp->EngineParms->Core[rp->LayerId][rp->CoreId].CoreType;
	if (coretype == ENGINE_NN) {
		NN_Parms* NNParms = (NN_Parms*)rp->EngineParms->Core[rp->LayerId][rp->CoreId].CoreSpecs;
		//-- Actual Run sets ProcessId, ThreadId, Pos, Actual, Predicted
		Run_NN(rp->DebugParms, NNParms, coreLog, rp->InputData, rp->pid, rp->tid, rp->SampleCount, rp->Sample, rp->Target);
	} else if (coretype == ENGINE_SVM) {
		SVM_Parms* SVMParms = (SVM_Parms*)rp->EngineParms->Core[rp->LayerId][rp->CoreId].CoreSpecs;
		//-- Actual Run sets ProcessId, ThreadId, Pos, Actual, Predicted
		Run_SVM(rp->DebugParms, SVMParms, coreLog, rp->InputData, rp->pid, rp->tid, rp->SampleCount, rp->Sample, rp->Target);
	} else {
		//-- other engine core types ...
	}
}
int Train_Layer(tDebugInfo* pDebugParms, tEngineDef* pEngineParms, tDataShape* pDataParms, int pid, int pTestId, int pLayer, bool loadW, tTrainParams* tp, double****** pSampleData, double****** pTargetData) {
	int t;
	int ret = 0;
	int ThreadCount = pDataParms->DatasetsCount*pEngineParms->TotalCoresCount;
	HANDLE* HTrain = (HANDLE*)malloc(ThreadCount * sizeof(HANDLE));
	DWORD* kaz = (DWORD*)malloc(ThreadCount * sizeof(DWORD));
	LPDWORD* tid = (LPDWORD*)malloc(ThreadCount * sizeof(LPDWORD)); for (int i = 0; i < ThreadCount; i++) tid[i] = &kaz[i];
	HANDLE SMutex = CreateMutex(NULL, FALSE, NULL);

	gotoxy(0, 2 + pLayer + ((pLayer>0) ? pDataParms->DatasetsCount*pEngineParms->CoresCount[pLayer - 1] : 0));  printf("Training Layer %d\n", pLayer);
	t = 0;
	for (int n = 0; n<pEngineParms->CoresCount[pLayer]; n++) {
		for (int d = 0; d<pDataParms->DatasetsCount; d++) {
			tp[t].LayerId = pLayer;
			tp[t].CoreId = n;
			tp[t].DatasetId = d;
			tp[t].CorePos = 2 + t + pLayer + ((pLayer>0) ? pDataParms->DatasetsCount*pEngineParms->CoresCount[pLayer - 1] : 0);
			tp[t].ScreenMutex = SMutex;
			tp[t].TotCores = pEngineParms->CoresCount[pLayer] * pDataParms->DatasetsCount;
			tp[t].DebugParms = pDebugParms;
			tp[t].EngineParms = pEngineParms;
			tp[t].SampleCount = pDataParms->SampleCount;
			tp[t].useValidation = (pDataParms->ValidationShift != 0) ? 1 : 0;
			tp[t].useExistingW = loadW;

			//-- SampleData, TargetData
			tp[t].SampleT = pSampleData[HD][d][pLayer][n];
			tp[t].TargetT = pTargetData[HD][d][pLayer][n];
			if (tp[t].useValidation>0) {
				tp[t].SampleV = pSampleData[VD][d][pLayer][n];
				tp[t].TargetV = pTargetData[VD][d][pLayer][n];
			}
			//-- Create Thread
			HTrain[t] = CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE)Train_XXX, &tp[t], 0, tid[t]);

			//-- Store Engine Handler
			tp[t].TrainInfo.ProcessId = pid;
			tp[t].TrainInfo.TestId = pTestId;
			tp[t].TrainInfo.DatasetId = d;
			tp[t].TrainInfo.ThreadId = (*tid[t]);
			pEngineParms->Core[pLayer][n].CoreLog[d].ThreadId = (*tid[t]);
			t++;
		}
	}
	//-- we need to train all the nets in one layer, in order to have the inputs to the next layer
	WaitForMultipleObjects(t, HTrain, TRUE, INFINITE);

	//-- check for training failure
	for (int ti = 0; ti<t; ti++) if (tp[ti].TrainSuccess!=0) ret = -1;

	//-- free(s)
	free(HTrain); free(kaz); free(tid);

	return ret;
}
void Run_Layer(tDebugInfo* pDebugParms, tEngineDef* pEngineParms, tDataShape* pDataParms, int pDoTraining, int pLayer, int pid, tTrainParams* tp, tRunParams* rp, double****** SampleData, double****** TargetData) {
	//-- The only reason why we make this multi-thread is to have different ThreadIds, so not to violate pk on MyLog_Run
	int ThreadCount = pDataParms->DatasetsCount*pEngineParms->TotalCoresCount;
	HANDLE* HRun = (HANDLE*)malloc(ThreadCount * sizeof(HANDLE));
	DWORD* kaz = (DWORD*)malloc(ThreadCount * sizeof(DWORD));
	LPDWORD* tid = (LPDWORD*)malloc(ThreadCount * sizeof(LPDWORD)); for (int i = 0; i < ThreadCount; i++) tid[i] = &kaz[i];

	int t = 0;
	for (int n = 0; n<pEngineParms->CoresCount[pLayer]; n++) {
		for (int d = 0; d<pDataParms->DatasetsCount; d++) {
			rp[t].DebugParms = pDebugParms;
			rp[t].EngineParms = pEngineParms;
			rp[t].InputData = pDataParms;
			rp[t].LayerId = pLayer;
			rp[t].CoreId = n;
			rp[t].DatasetId = d;
			rp[t].pid = pid;
			rp[t].SampleCount = pDataParms->SampleCount;
			rp[t].Sample = SampleData[HD][d][pLayer][n];
			rp[t].Target = TargetData[HD][d][pLayer][n];

			//-- create Thread
			HRun[t] = CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE)Run_XXX, &rp[t], 0, tid[t]);

			//-- set ThreadId
			rp[t].tid = (pDoTraining>0) ? tp[t].TrainInfo.ThreadId : (*tid[t]);
			pEngineParms->Core[pLayer][n].CoreLog[d].ThreadId = rp[t].tid;
			t++;
		}
	}
	WaitForMultipleObjects(t, HRun, TRUE, INFINITE);

	free(HRun); free(kaz); free(tid);
}
//--

void SetNetPidTid(tEngineDef* pEngineParms, int pLayer, int pDatasetsCount, int pAction, int pAdderId, tEngineHandle* pSavedEngine) {
	//-- from pSavedEngine we need pid and ONE tid.
	//-- from pTrainParms we get an array of threads from current training session
	int n, d, i, j;

	tLogMSE* MSELog;
	tLogRUN* RunLog;

	i = 0;
	for (n = 0; n<pEngineParms->CoresCount[pLayer]; n++) {
		for (d = 0; d<pDatasetsCount; d++) {

			MSELog = pEngineParms->Core[pLayer][n].CoreLog[d].MSEOutput;
			RunLog = pEngineParms->Core[pLayer][n].CoreLog[d].RunOutput;


			//-- MSE: we kee the same pid,tid from original Training session,
			for (j = 0; j<pEngineParms->Core[pLayer][n].MSECount; j++) {
				MSELog[j].BaseProcessId = (pAction==TRAIN_SAVE_RUN) ? MSELog[j].ProcessId : pSavedEngine->ProcessId;
				MSELog[j].BaseThreadId = (pAction==TRAIN_SAVE_RUN) ? MSELog[j].ThreadId : pSavedEngine->ThreadId;
				MSELog[j].AdderId = pAdderId;
			}

			//-- Run
			for (j = 0; j<pEngineParms->Core[pLayer][n].RunCount; j++) {
				if (pAction==JUST_RUN) {
					RunLog[j].NetProcessId = pSavedEngine->ProcessId;
					RunLog[j].NetThreadId = pSavedEngine->ThreadId + i;
				} else {
					RunLog[j].NetProcessId = RunLog[j].ProcessId;
					RunLog[j].NetThreadId = RunLog[j].ThreadId;
				}
			}
		}
		i++;
	}
}

void CalcForecastFromEngineOutput(tEngineDef* pEngineParms, tDataShape* pDataParms, int pTestId, double* scaleM, double* scaleP, double* baseVal, double** hd_trs, double** hd_bw, int pOOS, double** fd_trs, double** fd_bw, tLogRUN** runLog_o, double** oPredictedData) {
	int d, i;

	int sl0 = pDataParms->SampleLen;			// SampleLen from original data
	int sl1 = pEngineParms->Core[pEngineParms->LayersCount-1][0].SampleLen;	// SampleLen from last layer, core 0 
	int sc = pDataParms->SampleCount;
	int pl = pDataParms->PredictionLen;
	int rc = sl0 + sc + pl;

	tLogRUN* runLog_i = nullptr;

	double*  act = MallocArray<double>(rc);
	double*  prd = MallocArray<double>(rc);
	double*  act_tr = MallocArray<double>(rc);
	double*  prd_tr = MallocArray<double>(rc);
	double*  act_trs = MallocArray<double>(rc);
	double*  prd_trs = MallocArray<double>(rc);
	double*  err = MallocArray<double>(rc);
	double*  err_trs = MallocArray<double>(rc);

	for (d = 0; d < pDataParms->DatasetsCount; d++) {

		runLog_i = pEngineParms->Core[pEngineParms->LayersCount - 1][0].CoreLog[d].RunOutput;

		//-- Actual_TRS
		for (i = 0; i < sl0; i++) act_trs[i] = hd_trs[d][i];
		for (i = 0; i < sc; i++) act_trs[sl0 + i] = hd_trs[d][sl0 + i];
		for (i = 0; i < pl; i++) act_trs[sl0 + sc + i] = (pOOS == 0) ? EMPTY_VALUE : fd_trs[d][i];	//-- Run_<XXX> always writes Actual as the forecast from last step, so here we simply overwrite it if we have Future Data

																									//-- Predicted_TRS
		for (i = 0; i < sl0; i++) prd_trs[i] = EMPTY_VALUE;
		for (i = 0; i < sc; i++) prd_trs[sl0 + i] = runLog_i[sl1 + i].Predicted_TRS;
		for (i = 0; i < pl; i++) prd_trs[sl0 + sc + i] = runLog_i[sl1 + sc + i].Predicted_TRS;

		//-- UnScale/UnTransform act
		DataUnScale(rc, 0, (pOOS>0) ? rc : (sl0+sc), act_trs, scaleM[d], scaleP[d], act_tr);
		dataUnTransform(pDataParms->DataTransformation, rc, 0, (pOOS>0) ? rc : (sl0+sc), act_tr, baseVal[d], act, act);

		//-- UnScale/UnTransform prd
		DataUnScale(rc, 0, rc, prd_trs, scaleM[d], scaleP[d], prd_tr);
		dataUnTransform(pDataParms->DataTransformation, rc, sl0, rc, prd_tr, act[sl0-1], act, prd);	// baseVal should be actual[sampleLen-1], and we skip the first <sampleLen> elements

																												//-- calc err, err_trs
		for (i = 0; i < sl0; i++) {
			prd[i] = 0;
			err[i] = 0;
			err_trs[i] = 0;
		}
		for (i = sl0; i < (sl0+sc); i++) {
			err[i] = fabs(prd[i] - act[i]);
			err_trs[i] = fabs(prd_trs[i] - act_trs[i]);
		}
		for (i = (sl0 + sc); i < rc; i++) {
			err[i] = fabs(prd[i] - act[i]);
			err_trs[i] = fabs(prd_trs[i] - act_trs[i]);
		}

		//-- fill runLog_o[d]
		for (i = 0; i<rc; i++) {
			runLog_o[d][i].ProcessId = runLog_i[0].ProcessId;
			runLog_o[d][i].NetProcessId = runLog_i[0].NetProcessId;
			runLog_o[d][i].ThreadId = runLog_i[0].ThreadId;
			runLog_o[d][i].NetThreadId = runLog_i[0].NetThreadId;
			runLog_o[d][i].TestId = pTestId;
			runLog_o[d][i].LayerId = pEngineParms->LayersCount - 1;
			runLog_o[d][i].CoreId = 0;

			runLog_o[d][i].Pos = i;
			runLog_o[d][i].Actual = act[i];
			runLog_o[d][i].Actual_TRS = act_trs[i];
			runLog_o[d][i].Predicted = prd[i];
			runLog_o[d][i].Predicted_TRS = prd_trs[i];
			runLog_o[d][i].Error = err[i];
			runLog_o[d][i].Error_TRS = err_trs[i];

			runLog_o[d][i].BarWidth = (i<pDataParms->HistoryLen) ? hd_bw[d][i] : fd_bw[d][i-pDataParms->HistoryLen];	// =====!!!=====
			runLog_o[d][i].ErrorP = (runLog_o[d][i].BarWidth==0) ? 0 : (runLog_o[d][i].Error / runLog_o[d][i].BarWidth);
		}

		//-- finally, set oPredictedData
		for (i = 0; i < pl; i++) oPredictedData[d][i] = prd[sl0 + sc + i];
	}

	FreeArray(rc, act);
	FreeArray(rc, prd);
	FreeArray(rc, act_tr);
	FreeArray(rc, prd_tr);
	FreeArray(rc, act_trs);
	FreeArray(rc, prd_trs);
	FreeArray(rc, err);
	FreeArray(rc, err_trs);

}

void dataDump(int pHistoryLen, double** pHistoryData, double* pHistoryBaseVal, double** pHistoryBW, double** pValidationData, double* pValidationBaseVal, int pFutureLen, double** pFutureData, double** pFutureBW) {
	//-- data log
	FILE* fd = fopen("C:/temp/MT4data.csv", "w");
	fprintf(fd, "High, Low, BarWidth \n");
	//--- BaseVal
	fprintf(fd, "%f, %f, %f \n", pHistoryBaseVal[0], pHistoryBaseVal[1], 0.0);
	//---HistoryData
	for (int i = 0; i<pHistoryLen; i++) fprintf(fd, "%f, %f, %f \n", pHistoryData[0][i], pHistoryData[1][i], pHistoryBW[0][i]);
	//---
	//--- FutureData
	for (int i = 0; i<pFutureLen; i++) fprintf(fd, "%f, %f, %f \n", pFutureData[0][i], pFutureData[1][i], pFutureBW[0][i]);
	//---
	fclose(fd);

}

EXPORT int getForecast(int paramOverrideCnt, char** paramOverride, void* LogDBCtx, int pTestId, double** pHistoryData, double* pHistoryBaseVal, double** pHistoryBW, double** pValidationData, double* pValidationBaseVal, int haveActualFuture, double** pFutureData, double** pFutureBW, double** oPredictedData) {

	int pid = GetCurrentProcessId();
	int tid = GetCurrentThreadId();
	HANDLE FMutex = CreateMutex(NULL, FALSE, NULL);

	// Forecasting Parameters initialization. 
	tForecastParms* fp = new tForecastParms;
	//-- a. set overrides from Command Line 
	if (CLProcess(paramOverrideCnt, paramOverride, fp->iniParms) != 0) return -1;
	//-- b. process ini file
	if (ForecastParamLoader(fp) <0) return -1;
	//-- c. restore Ctx for LogDB, if the caller has already opened a session
	if (LogDBCtx != NULL) fp->DebugParms.DebugDB->DBCtx = LogDBCtx;

	//dataDump(fp->DataParms.HistoryLen, pHistoryData, pHistoryBaseVal, pHistoryBW, pValidationData, pValidationBaseVal, fp->DataParms.PredictionLen, pFutureData, pFutureBW);
	//DumpArrayD(fp->DataParms.HistoryLen, pHistoryData[0], "c:/temp/High.csv");
	LogWrite(&fp->DebugParms, LOG_INFO, "%s %s started. ProcessId=%d ; ThreadId=%d\n", 4, timestamp(), __func__, pid, tid);

	fp->DebugParms.Mtx = FMutex;

	int dscnt = fp->DataParms.DatasetsCount;
	int hlen = fp->DataParms.HistoryLen;
	double** hd = pHistoryData;
	double** vd = pValidationData;
	int flen = fp->DataParms.PredictionLen;
	double** fd = pFutureData;
	int layersCnt = fp->EngineParms.LayersCount;
	int* coresCnt = fp->EngineParms.CoresCount;

	int l, d;

	int sampleCnt = fp->DataParms.SampleCount;
	int sampleLen0 = fp->DataParms.SampleLen;
	int rc = sampleLen0 + sampleCnt + flen;

	double** hd_tr = MallocArray<double>(dscnt, hlen);
	double** hd_trs = MallocArray<double>(dscnt, hlen);
	double** vd_tr = MallocArray<double>(dscnt, hlen);
	double** vd_trs = MallocArray<double>(dscnt, hlen);
	double** fd_tr = MallocArray<double>(dscnt, flen);
	double** fd_trs = MallocArray<double>(dscnt, flen);

	double scaleMin, scaleMax;
	double*  hd_scaleM = MallocArray<double>(dscnt);
	double*  hd_scaleP = MallocArray<double>(dscnt);
	double*  vd_scaleM = MallocArray<double>(dscnt);
	double*  vd_scaleP = MallocArray<double>(dscnt);
	double*  fd_scaleM = MallocArray<double>(dscnt);
	double*  fd_scaleP = MallocArray<double>(dscnt);
	double** hd_tsf = MallocArray<double>(dscnt, fp->EngineParms.TSFcnt);
	double** vd_tsf = MallocArray<double>(dscnt, fp->EngineParms.TSFcnt);

	double*****		ts = MallocArray<double>(2, dscnt, layersCnt, ArrayMax<int>(layersCnt, coresCnt), hlen);
	double*****		ts_tr = MallocArray<double>(2, dscnt, layersCnt, ArrayMax<int>(layersCnt, coresCnt), hlen);
	double*****		ts_trs = MallocArray<double>(2, dscnt, layersCnt, ArrayMax<int>(layersCnt, coresCnt), hlen);
	double****		ts_scaleM = MallocArray<double>(2, dscnt, layersCnt, ArrayMax<int>(layersCnt, coresCnt));
	double****		ts_scaleP = MallocArray<double>(2, dscnt, layersCnt, ArrayMax<int>(layersCnt, coresCnt));
	double****		bv = MallocArray<double>(2, dscnt, layersCnt, ArrayMax<int>(layersCnt, coresCnt));
	tTrainParams*	tp = MallocArray<tTrainParams>(fp->DataParms.DatasetsCount*fp->EngineParms.TotalCoresCount);
	tRunParams*		rp = MallocArray<tRunParams>(fp->DataParms.DatasetsCount*fp->EngineParms.TotalCoresCount);
	tLogRUN**		runLog = MallocArray<tLogRUN>(dscnt, rc);

	double****** Sample = mallocSample(&fp->EngineParms, &fp->DataParms);
	double****** Target = mallocTarget(&fp->EngineParms, &fp->DataParms);


	/*
	ts		[HD/VD][Dataset][Layer][Core][item]
	Sample	[HD/VD][Dataset][Layer][Core][Sample][item]
	Target	[HD/VD][Dataset][Layer][Core][Sample][item]
	*/

	//----- Base TimeSerie s-----------------------------------------------------------
	for (d = 0; d < dscnt; d++) {

		SetTSScaleRange(fp->EngineParms.EngineType, fp->EngineParms.Core[0][0].CoreSpecs, &scaleMin, &scaleMax);
		//-- transform/scale hd
		dataTransform(fp->DataParms.DataTransformation, hlen, hd[d], pHistoryBaseVal[d], hd_tr[d]);
		DataScale(hlen, hd_tr[d], scaleMin, scaleMax, hd_trs[d], &hd_scaleM[d], &hd_scaleP[d]);
		//-- transform/scale vd
		if (fp->DataParms.ValidationShift != 0) {
			dataTransform(fp->DataParms.DataTransformation, hlen, vd[d], pValidationBaseVal[d], vd_tr[d]);
			DataScale(hlen, vd_tr[d], scaleMin, scaleMax, vd_trs[d], &vd_scaleM[d], &vd_scaleP[d]);
		}
		//-- fill fd_trs
		dataTransform(fp->DataParms.DataTransformation, flen, pFutureData[d], hd[d][hlen-1], fd_tr[d]);	//-- Transformation of FutureData uses the last element of HistoryData as Base Val
		DataScale(flen, fd_tr[d], scaleMin, scaleMax, fd_trs[d], hd_scaleM[d], hd_scaleP[d]);						//-- scaling FD using M/P from HD

																													// regardless of the engine, we slide base timeserie. If needed by specific engine, this will get overwritten
		SlideArray(hlen, hd_trs[d], sampleCnt, fp->EngineParms.Core[0][0].SampleLen, Sample[HD][d][0][0], flen, Target[HD][d][0][0], fp->DebugParms.DumpSampleData);
		if (fp->DataParms.ValidationShift != 0) SlideArray(hlen, vd_trs[d], sampleCnt, fp->EngineParms.Core[0][0].SampleLen, Sample[VD][d][0][0], flen, Target[VD][d][0][0], fp->DebugParms.DumpSampleData);

		CalcTSF(fp->EngineParms.TSFcnt, fp->EngineParms.TSFid, &fp->DataParms, hlen, hd[d], hd_tsf[d]);
		if (fp->DataParms.ValidationShift != 0) CalcTSF(fp->EngineParms.TSFcnt, fp->EngineParms.TSFid, &fp->DataParms, hlen, vd[d], vd_tsf[d]);
	}

	int trainret;
	for (l = 0; l < fp->EngineParms.LayersCount; l++) {
		for (d = 0; d < dscnt; d++) {
			//-- for multi-layer engines, we need to define how each layer is defined
			switch (fp->EngineParms.EngineType) {
			case ENGINE_WNN:
				BuildLayerInput_WNN(l, &fp->EngineParms, fp->DataParms.DataTransformation, d, sampleCnt, hlen, hd[d], pHistoryBaseVal[d], ts[HD][d][l], bv[HD][d][l], hd_tsf[d], fp->EngineParms.Core[0], Target[HD][d][0][0], Sample[HD][d][1][0], Target[HD][d][1][0]);
				if (fp->DataParms.ValidationShift != 0) BuildLayerInput_WNN(l, &fp->EngineParms, fp->DataParms.DataTransformation, d, sampleCnt, hlen, vd[d], pHistoryBaseVal[d], ts[VD][d][l], bv[VD][d][l], vd_tsf[d], fp->EngineParms.Core[0], Target[VD][d][0][0], Sample[VD][d][1][0], Target[VD][d][1][0]);
				if (l == 0) {
					for (int n = 0; n < coresCnt[0]; n++) {
						SetTSScaleRange(fp->EngineParms.EngineType, fp->EngineParms.Core[l][n].CoreSpecs, &scaleMin, &scaleMax);
						// HD
						dataTransform(fp->DataParms.DataTransformation, hlen, ts[HD][d][l][n], bv[HD][d][l][n], ts_tr[HD][d][l][n]);
						DataScale(hlen, ts_tr[HD][d][l][n], scaleMin, scaleMax, ts_trs[HD][d][l][n], &ts_scaleM[HD][d][l][n], &ts_scaleP[HD][d][l][n]);
						SlideArray(hlen, ts_trs[HD][d][l][n], sampleCnt, fp->EngineParms.Core[l][0].SampleLen, Sample[HD][d][l][n], flen, Target[HD][d][l][n], fp->DebugParms.DumpSampleData);
						// VD
						if (fp->DataParms.ValidationShift != 0) {
							dataTransform(fp->DataParms.DataTransformation, hlen, ts[VD][d][l][n], bv[VD][d][l][n], ts_tr[VD][d][l][n]);
							DataScale(hlen, ts_tr[VD][d][l][n], scaleMin, scaleMax, ts_trs[VD][d][l][n], &ts_scaleM[VD][d][l][n], &ts_scaleP[VD][d][l][n]);
							SlideArray(hlen, ts_trs[VD][d][l][n], sampleCnt, fp->EngineParms.Core[l][0].SampleLen, Sample[VD][d][l][n], flen, Target[VD][d][l][n], fp->DebugParms.DumpSampleData);
						}
					}
				}
				break;
			case ENGINE_XIE:
				BuildLayerInput_XIE(l, d, sampleCnt, fp->DataParms.PredictionLen, Sample[HD], Target[HD], fp->EngineParms.Core);	// TargetData
				if (fp->DataParms.ValidationShift != 0) BuildLayerInput_XIE(l, d, sampleCnt, fp->DataParms.PredictionLen, Sample[VD], Target[VD], fp->EngineParms.Core);	// ValidationData
				break;
			default:
				break;
			}
		}
		switch (fp->Action) {
		case TRAIN_SAVE_RUN:
			trainret = Train_Layer(&fp->DebugParms, &fp->EngineParms, &fp->DataParms, pid, pTestId, l, false, tp, Sample, Target);
			Run_Layer(&fp->DebugParms, &fp->EngineParms, &fp->DataParms, 1, l, pid, tp, rp, Sample, Target);
			break;
		case ADD_SAMPLES:
			//-- LoadEngine has already been done
			trainret = Train_Layer(&fp->DebugParms, &fp->EngineParms, &fp->DataParms, pid, pTestId, l, true, tp, Sample, Target);
			break;
		case JUST_RUN:
			//-- LoadEngine has already been done
			Run_Layer(&fp->DebugParms, &fp->EngineParms, &fp->DataParms, 0, l, pid, tp, rp, Sample, Target);
			break;
		}
		SetNetPidTid(&fp->EngineParms, l, dscnt, fp->Action, fp->EngineParms.AdderCount, &fp->SavedEngine);

	}

	//-- check for training failure
	if (trainret!=0) {
		LogWrite(&fp->DebugParms, LOG_ERROR, "Training Failed!\n", 0);
	} else {
		//-- if training succeded, calc Forecast, and save logs.
		CalcForecastFromEngineOutput(&fp->EngineParms, &fp->DataParms, pTestId, hd_scaleM, hd_scaleP, pHistoryBaseVal, hd_trs, pHistoryBW, haveActualFuture, fd_trs, pFutureBW, runLog, oPredictedData);
		LogWrite(&fp->DebugParms, LOG_INFO, "%s(): oPredictedData[0][0]=%f\n", 2, __func__, oPredictedData[0][0]);
		LogWrite(&fp->DebugParms, LOG_INFO, "%s(): oPredictedData[0][1]=%f\n", 2, __func__, oPredictedData[0][1]);
		if (fp->DataParms.DatasetsCount>1) {
			LogWrite(&fp->DebugParms, LOG_INFO, "%s(): oPredictedData[1][0]=%f\n", 2, __func__, oPredictedData[1][0]);
			LogWrite(&fp->DebugParms, LOG_INFO, "%s(): oPredictedData[1][1]=%f\n", 2, __func__, oPredictedData[1][1]);
		}
		//-- Save Logs
		if (fp->DebugParms.SaveNothing==0) {
			LogWrite(&fp->DebugParms, LOG_INFO, "pTestId=%d\n", 1, pTestId);
			if (pTestId == 0) {
				printf("\nSaveTestLog_DataParams()...\n"); if (SaveTestLog_DataParms(&fp->DebugParms, &fp->DataParms, pid) != 0) return -1;
				printf("SaveTestLog_EngineParms()...\n"); if (SaveTestLog_EngineParms(&fp->DebugParms, pid, (fp->Action==ADD_SAMPLES) ? fp->SavedEngine.ProcessId : pid, &fp->EngineParms) != 0) return -1;
			}

			printf("SaveTestLog_EngineThreads()...\n"); if (SaveTestLog_EngineThreads(&fp->DebugParms, fp->EngineParms.AdderCount, pid, pTestId, &fp->EngineParms, &fp->DataParms) != 0) return -1;

			if (fp->Action !=JUST_RUN) {
				printf("LogSave_MSE()...\n"); if (LogSave_MSE(&fp->DebugParms, &fp->EngineParms, &fp->DataParms, pTestId) != 0) return -1;
				printf("LogSave_Cores()...\n"); if (LogSave_Cores(&fp->DebugParms, &fp->EngineParms, &fp->DataParms, pid, pTestId) != 0) return -1;
			}
			if (fp->Action!=ADD_SAMPLES) {
				printf("LogSave_Run()...\n"); if (LogSave_Run(&fp->DebugParms, &fp->EngineParms, &fp->DataParms, pTestId, runLog) != 0) return -1;
			}
		}
	}

	//-- free(s) 
	FreeArray(dscnt, hlen, hd_tr);
	FreeArray(dscnt, hlen, hd_trs);
	FreeArray(dscnt, hlen, vd_tr);
	FreeArray(dscnt, hlen, vd_trs);
	FreeArray(dscnt, flen, fd_trs);
	FreeArray(dscnt, vd_scaleM);
	FreeArray(dscnt, vd_scaleP);
	FreeArray(dscnt, fp->EngineParms.TSFcnt, hd_tsf);
	FreeArray(dscnt, fp->EngineParms.TSFcnt, vd_tsf);
	FreeArray(2, dscnt, layersCnt, ArrayMax<int>(layersCnt, coresCnt), hlen, ts);
	FreeArray(2, dscnt, layersCnt, ArrayMax<int>(layersCnt, coresCnt), hlen, ts_tr);
	FreeArray(2, dscnt, layersCnt, ArrayMax<int>(layersCnt, coresCnt), hlen, ts_trs);
	FreeArray(2, dscnt, layersCnt, ArrayMax<int>(layersCnt, coresCnt), ts_scaleM);
	FreeArray(2, dscnt, layersCnt, ArrayMax<int>(layersCnt, coresCnt), ts_scaleP);
	FreeArray(2, dscnt, layersCnt, ArrayMax<int>(layersCnt, coresCnt), bv);
	FreeArray(fp->DataParms.DatasetsCount*fp->EngineParms.TotalCoresCount, tp);
	FreeArray(fp->DataParms.DatasetsCount*fp->EngineParms.TotalCoresCount, rp);
	FreeArray(dscnt, rc, runLog);

	freeSampleTarget(&fp->EngineParms, &fp->DataParms, Sample, Target);
	ForecastParamFree(fp);

	LogWrite(&fp->DebugParms, LOG_INFO, "%s %s completed.\n", 2, timestamp(), __func__);

	LogClose(&fp->DebugParms);

	return 0;

}

#include <vld.h>

#include <MyForecast.h>

//--

//--
double****** mallocSample(cEngine* pEngineParms, tDataShape* pDataParms) {
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
					slen = pEngineParms->Core[l][c]->SampleLen;
					for (int s = 0; s < pDataParms->SampleCount; s++) {
						ret[hdvd][d][l][c][s] = (double*)malloc(slen * sizeof(double));
					}
				}
			}
		}
	}
	return ret;
}
double****** mallocTarget(cEngine* pEngineParms, tDataShape* pDataParms) {
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
					tlen = pEngineParms->Core[l][c]->TargetLen;
					for (int s = 0; s < pDataParms->SampleCount; s++) {
						ret[hdvd][d][l][c][s] = (double*)malloc(tlen * sizeof(double));
					}
				}
			}
		}
	}
	return ret;
}
void freeSampleTarget(cEngine* pEngineParms, tDataShape* pDataParms, double****** S, double****** T) {
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

cTimeSerie***** mallocTS(cParamsSource* fp){
	cTimeSerie***** ret = (cTimeSerie*****)malloc(2*sizeof(cTimeSerie****));
	for (int s = 0; s<2; s++) {
		ret[s] = (cTimeSerie****)malloc(fp->DataParms->DatasetsCount*sizeof(cTimeSerie***));
		for (int d = 0; d<fp->DataParms->DatasetsCount; d++) {
			ret[s][d] = (cTimeSerie***)malloc(fp->Engine->LayersCount*sizeof(cTimeSerie**));
			for (int l = 0; l<fp->Engine->LayersCount; l++) {
				ret[s][d][l] = (cTimeSerie**)malloc(fp->Engine->CoresCount[l]*sizeof(cTimeSerie*));
				for (int c = 0; c<fp->Engine->CoresCount[l]; c++) {
					ret[s][d][l][c] = new cTimeSerie(fp->DataParms->HistoryLen);
				}
			}
		}
	}
	return ret;
}
void freeTS(cParamsSource* fp, cTimeSerie***** ret){
	for (int s = 0; s<2; s++) {
		for (int d = 0; d<fp->DataParms->DatasetsCount; d++) {
			for (int l = 0; l<fp->Engine->LayersCount; l++) {
				for (int c = 0; c<fp->Engine->CoresCount[l]; c++) {
					free(ret[s][d][l][c]);
				}
				free(ret[s][d][l]);
			}
			free(ret[s][d]);
		}
		free(ret[s]);
	}
	free(ret);
}
//--

//--
void Train_XXX(tTrainParams* tp) {
/*	cCore*		core = tp->EngineParms->Core[tp->LayerId][tp->CoreId];
	cCoreLog*	coreLog = tp->EngineParms->Core[tp->LayerId][tp->CoreId]->coreLog[tp->DatasetId];

	tp->TrainSuccess = core->train(tp->DebugParms, tp->DatasetId, tp->SampleCount, tp->SampleLen, tp->TargetLen, tp->SampleT, tp->TargetT, tp->useValidation, tp->SampleV, tp->TargetV);
	tp->ActualEpochs = coreLog->ActualEpochs;
*/
	switch (tp->EngineParms->Core[tp->LayerId][tp->CoreId]->CoreType) {
	case CORE_NN:
		(cNN*)(tp->EngineParms->Core[tp->LayerId][tp->CoreId])->
		NNParms = (NN_Parms*)tp->EngineParms->Core[tp->LayerId][tp->CoreId].CoreSpecs;
		tp->TrainSuccess = Train_NN(tp->CorePos, tp->TotCores, tp->ScreenMutex, tp->DebugParms, NNParms, coreLog, tp->SampleCount, tp->SampleT, tp->TargetT, tp->useValidation, tp->SampleV, tp->TargetV);
		tp->ActualEpochs = coreLog->ActualEpochs;
		break;
	case CORE_GA:
		GAParms = (GA_Parms*)tp->EngineParms->Core[tp->LayerId][tp->CoreId].CoreSpecs;
		//-- tp->TrainSuccess= Train_GA(...);
		tp->ActualEpochs = coreLog->ActualEpochs;
		break;
	case CORE_SOM:
		SOMParms = (SOM_Parms*)tp->EngineParms->Core[tp->LayerId][tp->CoreId].CoreSpecs;
		//-- tp->TrainSuccess= Train_SOM(...);
		tp->ActualEpochs = coreLog->ActualEpochs;
		break;
	case CORE_SVM:
		SVMParms = (SVM_Parms*)tp->EngineParms->Core[tp->LayerId][tp->CoreId].CoreSpecs;
		tp->TrainSuccess = Train_SVM(tp->CorePos, tp->TotCores, tp->ScreenMutex, tp->DebugParms, SVMParms, coreLog, tp->SampleCount, tp->SampleT, tp->TargetT, tp->useValidation, tp->SampleV, tp->TargetV);
		tp->ActualEpochs = coreLog->ActualEpochs;
		break;
	}
	//-- update EngineParms->MSECount
	tp->EngineParms->Core[tp->LayerId][tp->CoreId].MSECount = tp->ActualEpochs;
*/
}
void Run_XXX(tRunParams* rp) {
	cCore*		core = rp->EngineParms->Core[rp->LayerId][rp->CoreId];
	//cCoreLog*	coreLog = rp->EngineParms->Core[rp->LayerId][rp->CoreId]->coreLog[rp->DatasetId];

	core->run(rp->DebugParms, rp->SampleCount, rp->SampleLen, rp->TargetLen, rp->Sample, rp->Target);

}
void Train_Layer(tDebugInfo* pDebugParms, cEngine* pEngineParms, tDataShape* pDataParms, int pid, int pTestId, int pLayer, tTrainParams* tp, double****** pSampleData, double****** pTargetData) {
	int t;
	int ThreadCount = pDataParms->DatasetsCount*pEngineParms->TotalCoresCount;
	HANDLE* HTrain = (HANDLE*)malloc(ThreadCount * sizeof(HANDLE));
	DWORD* kaz = (DWORD*)malloc(ThreadCount * sizeof(DWORD));
	LPDWORD* tid = (LPDWORD*)malloc(ThreadCount * sizeof(LPDWORD)); for (int i = 0; i < ThreadCount; i++) tid[i] = &kaz[i];

	gotoxy(0, 2 + pLayer + ((pLayer>0) ? pDataParms->DatasetsCount*pEngineParms->CoresCount[pLayer - 1] : 0));  printf("Training Layer %d\n", pLayer);
	t = 0;
	for (int n = 0; n<pEngineParms->CoresCount[pLayer]; n++) {
		for (int d = 0; d<pDataParms->DatasetsCount; d++) {
			tp[t].LayerId = pLayer;
			tp[t].CoreId = n;
			tp[t].DatasetId = d;
			tp[t].CorePos = 2 + t + pLayer + ((pLayer>0) ? pDataParms->DatasetsCount*pEngineParms->CoresCount[pLayer - 1] : 0);
			tp[t].ScreenMutex = pDebugParms->Mtx;
			tp[t].TotCores = pEngineParms->CoresCount[pLayer] * pDataParms->DatasetsCount;
			tp[t].DebugParms = pDebugParms;
			tp[t].EngineParms = pEngineParms;
			tp[t].SampleCount = pDataParms->SampleCount;
			tp[t].SampleLen = pEngineParms->Core[pLayer][n]->SampleLen;
			tp[t].TargetLen = pEngineParms->Core[pLayer][n]->TargetLen;
			tp[t].useValidation = (pDataParms->ValidationShift != 0) ? 1 : 0;

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
			pEngineParms->Core[pLayer][n]->coreLog[d]->ProcessId = pid;
			pEngineParms->Core[pLayer][n]->coreLog[d]->ThreadId = (*tid[t]);
			t++;
		}
	}
	//-- we need to train all the nets in one layer, in order to have the inputs to the next layer
	WaitForMultipleObjects(t, HTrain, TRUE, INFINITE);

	//-- free(s)
	free(HTrain); free(kaz); free(tid);
}
void Run_Layer(tDebugInfo* pDebugParms, cEngine* pEngineParms, tDataShape* pDataParms, int pDoTraining, int pLayer, int pid, tTrainParams* tp, tRunParams* rp, double****** SampleData, double****** TargetData) {
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
			pEngineParms->Core[pLayer][n]->coreLog[d]->ThreadId = rp[t].tid;
			t++;
		}
	}
	WaitForMultipleObjects(t, HRun, TRUE, INFINITE);

	free(HRun); free(kaz); free(tid);
}
void SetNetPidTid(cEngine* pEngineParms, int pLayer, int pDatasetsCount, int pDoTraining, tEngineHandle* pSavedEngine) {
	//-- from pSavedEngine we need pid and ONE tid.
	//-- from pTrainParms we get an array of threads from current training session
	int n, d, i, j;

	tLogMSE* MSELog = nullptr;
	tLogRUN* RunLog = nullptr;

	i = 0;
	for (n = 0; n<pEngineParms->CoresCount[pLayer]; n++) {
		for (d = 0; d<pDatasetsCount; d++) {

			MSELog = pEngineParms->Core[pLayer][n]->coreLog[d]->MSEOutput;
			RunLog = pEngineParms->Core[pLayer][n]->coreLog[d]->RunOutput;

			for (j = 0; j<pEngineParms->Core[pLayer][n]->RunCount; j++) {
				if (pDoTraining>0) {
					RunLog[j].NetProcessId = RunLog[j].ProcessId;
					RunLog[j].NetThreadId = RunLog[j].ThreadId;
				}
				else {
					RunLog[j].NetProcessId = pSavedEngine->ProcessId;
					RunLog[j].NetThreadId = pSavedEngine->ThreadId + i;
				}
			}
		}
		i++;
	}
}
//--

void CalcForecastFromEngineOutput(cEngine* pEngineParms, tDataShape* pDataParms, int pTestId, double* scaleM, double* scaleP, double* baseVal, double* minVal, double** hd_trs, double** wd_bw, int pOOS, double** fd_trs, tLogRUN** runLog_o, double** oPredictedData) {
	int d, i;

	int sl0 = pDataParms->SampleLen;			// SampleLen from original data
	int sl1 = pEngineParms->Core[pEngineParms->LayersCount-1][0]->SampleLen;	// SampleLen from last layer, core 0 
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

		runLog_i = pEngineParms->Core[pEngineParms->LayersCount-1][0]->coreLog[d]->RunOutput;

		//-- Actual_TRS
		for (i = 0; i < sl0; i++) act_trs[i] = hd_trs[d][i];
		for (i = 0; i < sc; i++) act_trs[sl0 + i] = hd_trs[d][sl0 + i];
		for (i = 0; i < pl; i++) act_trs[sl0 + sc + i] = (pOOS == 0) ? NULL : fd_trs[d][i];

		//-- Predicted_TRS
		for (i = 0; i < sl0; i++) prd_trs[i] = NULL;
		for (i = 0; i < sc; i++) prd_trs[sl0 + i] = runLog_i[sl1 + i].Predicted_TRS;
		for (i = 0; i < pl; i++) prd_trs[sl0 + sc + i] = runLog_i[sl1 + sc + i].Predicted_TRS;

		//-- UnScale/UnTransform act
		DataUnScale(rc, 0, rc, act_trs, scaleM[d], scaleP[d], act_tr);
		dataUnTransform(pDataParms->DataTransformation, 0, rc, act_tr, baseVal[d], minVal[d], act, act);
		//-- UnScale/UnTransform prd
		DataUnScale(rc, sl0, rc, prd_trs, scaleM[d], scaleP[d], prd_tr);
		dataUnTransform(pDataParms->DataTransformation, sl0, rc, prd_tr, act[sl0-1], minVal[d], act, prd);	// baseVal should be actual[sampleLen-1], and we skip the first <sampleLen> elements
		//-- prd elements need to be shifted back...
		//--.....

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
			err[i] = (pOOS == 0) ? 0 : fabs(prd[i] - act[i]);
			err_trs[i] = (pOOS == 0) ? 0 : fabs(prd_trs[i] - act_trs[i]);
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

			runLog_o[d][i].BarWidth = wd_bw[d][i];
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

EXPORT int getForecast(int paramOverrideCnt, char** paramOverride, void* LogDBCtx, int pTestId, double** pHistoryData, double* pHistoryBaseVal, double** pHistoryBW, double** pValidationData, double* pValidationBaseVal, int haveActualFuture, double** pFutureData, double** pFutureBW, double** oPredictedData) {
	int d;
	int pid = GetCurrentProcessId();

	cParamsSource* fp = new cParamsSource(paramOverrideCnt, paramOverride);
	if (fp->Process(FPALL) <0) return -1;
/*
	double scaleMin, scaleMax;

	fp->DebugParms->Mtx = CreateMutex(NULL, FALSE, NULL);



	cTimeSerie** hd = MallocArray<cTimeSerie*>(fp->DataParms->DatasetsCount);
	cTimeSerie** vd = MallocArray<cTimeSerie*>(fp->DataParms->DatasetsCount);
	cTimeSerie** fd = MallocArray<cTimeSerie*>(fp->DataParms->DatasetsCount);
	cTimeSerie** wd = MallocArray<cTimeSerie*>(fp->DataParms->DatasetsCount);

	fp->Engine->Core[0][0]->getScaleRange(&scaleMin, &scaleMax);	// scale range depends on Core parameters (activation functions)

	for (d = 0; d<fp->DataParms->DatasetsCount; d++) {
		hd[d] = new cTimeSerie(fp->DataParms->HistoryLen, pHistoryData[d], pHistoryBW[d], pHistoryBaseVal[d]);
		vd[d] = new cTimeSerie(fp->DataParms->HistoryLen, pHistoryData[d], NULL, pHistoryBaseVal[d]);			// Validation data does not need BarWidth
		fd[d] = new cTimeSerie(fp->DataParms->PredictionLen, pFutureData[d], pFutureBW[d], NULL);				// Future data does not have a Base val
		wd[d] = new cTimeSerie(hd[d], fd[d]);	// concatenation constructor

		hd[d]->TransformScale(fp->DataParms->DataTransformation, scaleMin, scaleMax);
		vd[d]->TransformScale(fp->DataParms->DataTransformation, scaleMin, scaleMax);
		fd[d]->TransformScale(fp->DataParms->DataTransformation, scaleMin, scaleMax);
		wd[d]->TransformScale(fp->DataParms->DataTransformation, scaleMin, scaleMax);

	}

	cTimeSerie***** ts=mallocTS(fp);
*/

	int dscnt = fp->DataParms->DatasetsCount;
	int hlen = fp->DataParms->HistoryLen;
	double** hd = pHistoryData;
	double** vd = pValidationData;
	int flen = fp->DataParms->PredictionLen;
	double** fd = pFutureData;
	int layersCnt = fp->Engine->LayersCount;
	int* coresCnt = fp->Engine->CoresCount;
	int sampleCnt = fp->DataParms->SampleCount;
	int sampleLen0 = fp->DataParms->SampleLen;
	int rc = sampleLen0 + sampleCnt + flen;			//int runCnt = fp->DataParms->SampleLen+fp->DataParms->SampleCount+fp->DataParms->PredictionLen;

	//-- Transform and Scale History, Validation, Future Data
	int wlen = hlen + flen;

	double** wd = MallocArray<double>(dscnt, wlen);
	double** wd_tr = MallocArray<double>(dscnt, wlen);
	double** wd_trs = MallocArray<double>(dscnt, wlen);
	double** wd_bw = MallocArray<double>(dscnt, wlen);
	double** hd_trs = MallocArray<double>(dscnt, hlen);
	double** vd_tr = MallocArray<double>(dscnt, hlen);
	double** vd_trs = MallocArray<double>(dscnt, hlen);
	double** fd_trs = MallocArray<double>(dscnt, flen);

	double* hd_min = MallocArray<double>(dscnt);
	double* vd_min = MallocArray<double>(dscnt);
	double* wd_min = MallocArray<double>(dscnt);

	double scaleMin, scaleMax;
	double*  wd_scaleM = MallocArray<double>(dscnt);
	double*  wd_scaleP = MallocArray<double>(dscnt);
	double*  vd_scaleM = MallocArray<double>(dscnt);
	double*  vd_scaleP = MallocArray<double>(dscnt);
	double** hd_tsf = MallocArray<double>(dscnt, fp->Engine->TSFcnt);
	double** vd_tsf = MallocArray<double>(dscnt, fp->Engine->TSFcnt);

	double*****		ts = MallocArray<double>(2, dscnt, layersCnt, ArrayMax<int>(layersCnt, coresCnt), hlen);
	double*****		ts_tr = MallocArray<double>(2, dscnt, layersCnt, ArrayMax<int>(layersCnt, coresCnt), hlen);
	double*****		ts_trs = MallocArray<double>(2, dscnt, layersCnt, ArrayMax<int>(layersCnt, coresCnt), hlen);
	double****		ts_scaleM = MallocArray<double>(2, dscnt, layersCnt, ArrayMax<int>(layersCnt, coresCnt));
	double****		ts_scaleP = MallocArray<double>(2, dscnt, layersCnt, ArrayMax<int>(layersCnt, coresCnt));
	double****		bv = MallocArray<double>(2, dscnt, layersCnt, ArrayMax<int>(layersCnt, coresCnt));
	double****		mv = MallocArray<double>(2, dscnt, layersCnt, ArrayMax<int>(layersCnt, coresCnt));

	tTrainParams*	tp = MallocArray<tTrainParams>(fp->DataParms->DatasetsCount*fp->Engine->TotalCoresCount);
	tRunParams*		rp = MallocArray<tRunParams>(fp->DataParms->DatasetsCount*fp->Engine->TotalCoresCount);
	tLogRUN**		runLog = MallocArray<tLogRUN>(dscnt, rc);

	double****** Sample = mallocSample(fp->Engine, fp->DataParms);
	double****** Target = mallocTarget(fp->Engine, fp->DataParms);

	/*
	ts		[HD/VD][Dataset][Layer][Core][item]
	Sample	[HD/VD][Dataset][Layer][Core][Sample][item]
	Target	[HD/VD][Dataset][Layer][Core][Sample][item]
	*/

	//----- Base TimeSerie s-----------------------------------------------------------
	for (d = 0; d < dscnt; d++) {

		fp->Engine->Core[0][0]->getScaleRange(&scaleMin, &scaleMax);
		//-- merge hd and fd into wd
		VExtend(fp->DataParms->HistoryLen, hd[d], fp->DataParms->PredictionLen, fd[d], wd[d]);
		//-- transform/scale wd
		dataTransform(fp->DataParms->DataTransformation, wlen, wd[d], pHistoryBaseVal[d], &wd_min[d], wd_tr[d]);
		DataScale(wlen, wd_tr[d], scaleMin, scaleMax, wd_trs[d], &wd_scaleM[d], &wd_scaleP[d]);
		//-- transform/scale vd
		if (fp->DataParms->ValidationShift != 0) {
			dataTransform(fp->DataParms->DataTransformation, hlen, vd[d], pValidationBaseVal[d], &vd_min[d], vd_tr[d]);
			DataScale(hlen, vd_tr[d], scaleMin, scaleMax, vd_trs[d], &vd_scaleM[d], &vd_scaleP[d]);
		}
		//-- derive hd_trs, fd_trs from wd_trs
		for (int i = 0; i < hlen; i++) hd_trs[d][i] = wd_trs[d][i];
		for (int i = 0; i < flen; i++) fd_trs[d][i] = wd_trs[d][hlen + i];

		// regardless of the engine, we slide base timeserie. If needed by specific engine, this will get overwritten
		SlideArray(hlen, hd_trs[d], sampleCnt, fp->Engine->Core[0][0]->SampleLen, Sample[HD][d][0][0], flen, Target[HD][d][0][0], 0);
		if (fp->DataParms->ValidationShift != 0) SlideArray(hlen, vd_trs[d], sampleCnt, fp->Engine->Core[0][0]->SampleLen, Sample[VD][d][0][0], flen, Target[VD][d][0][0], 0);

		CalcTSF(fp->Engine->TSFcnt, fp->Engine->TSFid, fp->DataParms, hlen, hd[d], hd_tsf[d]);
		if (fp->DataParms->ValidationShift != 0) CalcTSF(fp->Engine->TSFcnt, fp->Engine->TSFid, fp->DataParms, hlen, vd[d], vd_tsf[d]);
	}

	for (int l = 0; l < fp->Engine->LayersCount; l++) {
		for (d = 0; d < dscnt; d++) {
			//-- for multi-layer engines, we need to define how each layer is defined
			//fp->Engine->BuildLayerInput(l, d, sampleCnt, Sample[HD][d], Target[HD][d]);

			switch (fp->Engine->EngineType) {
			case ENGINE_WNN:
				BuildLayerInput_WNN(l, fp->Engine, fp->DataParms->DataTransformation, d, sampleCnt, hlen, hd[d], pHistoryBaseVal[d], ts[HD][d][l], bv[HD][d][l], hd_tsf[d], fp->Engine->Core[0], Target[HD][d][0][0], Sample[HD][d][1][0], Target[HD][d][1][0]);
				if (fp->DataParms->ValidationShift != 0) BuildLayerInput_WNN(l, fp->Engine, fp->DataParms->DataTransformation, d, sampleCnt, hlen, vd[d], pHistoryBaseVal[d], ts[VD][d][l], bv[VD][d][l], vd_tsf[d], fp->Engine->Core[0], Target[VD][d][0][0], Sample[VD][d][1][0], Target[VD][d][1][0]);
				if (l == 0) {
					for (int n = 0; n < coresCnt[0]; n++) {
						fp->Engine->Core[l][n]->getScaleRange(&scaleMin, &scaleMax);
						// HD
						dataTransform(fp->DataParms->DataTransformation, hlen, ts[HD][d][l][n], bv[HD][d][l][n], &mv[HD][d][l][n], ts_tr[HD][d][l][n]);
						DataScale(hlen, ts_tr[HD][d][l][n], scaleMin, scaleMax, ts_trs[HD][d][l][n], &ts_scaleM[HD][d][l][n], &ts_scaleP[HD][d][l][n]);
						SlideArray(hlen, ts_trs[HD][d][l][n], sampleCnt, fp->Engine->Core[l][0]->SampleLen, Sample[HD][d][l][n], flen, Target[HD][d][l][n], 0);
						// VD
						if (fp->DataParms->ValidationShift != 0) {
							dataTransform(fp->DataParms->DataTransformation, hlen, ts[VD][d][l][n], bv[VD][d][l][n], &mv[HD][d][l][n], ts_tr[VD][d][l][n]);
							DataScale(hlen, ts_tr[VD][d][l][n], scaleMin, scaleMax, ts_trs[VD][d][l][n], &ts_scaleM[VD][d][l][n], &ts_scaleP[VD][d][l][n]);
							SlideArray(hlen, ts_trs[VD][d][l][n], sampleCnt, fp->Engine->Core[l][0]->SampleLen, Sample[VD][d][l][n], flen, Target[VD][d][l][n], 0);
						}
					}
				}
				break;
			case ENGINE_XIE:
				BuildLayerInput_XIE(l, d, sampleCnt, fp->DataParms->PredictionLen, Sample[HD], Target[HD], (*fp->Engine->Core));	// TargetData
				if (fp->DataParms->ValidationShift != 0) BuildLayerInput_XIE(l, d, sampleCnt, fp->DataParms->PredictionLen, Sample[VD], Target[VD], (*fp->Engine->Core));	// ValidationData
				break;
			default:
				break;
			}

		}

		if (fp->ClientParms->DoTraining) Train_Layer(fp->DebugParms, fp->Engine, fp->DataParms, pid, pTestId, l, tp, Sample, Target);
		Run_Layer(fp->DebugParms, fp->Engine, fp->DataParms, fp->ClientParms->DoTraining, l, pid, tp, rp, Sample, Target);
		SetNetPidTid(fp->Engine, l, dscnt, fp->ClientParms->DoTraining, fp->SavedEngine);
	}

	CalcForecastFromEngineOutput(fp->Engine, fp->DataParms, pTestId, wd_scaleM, wd_scaleP, pHistoryBaseVal, wd_min, hd_trs, wd_bw, haveActualFuture, fd_trs, runLog, oPredictedData);

	if (pTestId == 0) {
		if (SaveDataParms(fp->DebugParms, fp->ResultsDB, fp->DataParms, pid) != 0) return -1;
		if (fp->Engine->Save(fp->DebugParms, fp->ResultsDB, pid, pTestId, fp->DataParms->DatasetsCount) != 0) return -1;
	}
	if (fp->ClientParms->DoTraining == 1) {
		if (fp->Engine->SaveMSELogs(fp->DebugParms, fp->ResultsDB, pid, fp->DataParms->DatasetsCount) != 0) return -1;
		if (fp->Engine->SaveImage(fp->DebugParms, pid, fp->DataParms->DatasetsCount, pTestId) != 0) return -1;
	}
	if (fp->Engine->SaveRunLogs(fp->DebugParms, fp->ResultsDB, pid, fp->DataParms->DatasetsCount, hlen) != 0) return -1;
	LogCommit(fp->DebugParms, fp->ResultsDB);

	//-- free(s) 
	FreeArray(dscnt, wlen, wd);
	FreeArray(dscnt, wlen, wd_tr);
	FreeArray(dscnt, wlen, wd_trs);
	FreeArray(dscnt, wlen, wd_bw);
	FreeArray(dscnt, hlen, hd_trs);
	FreeArray(dscnt, hlen, vd_tr);
	FreeArray(dscnt, hlen, vd_trs);
	FreeArray(dscnt, flen, fd_trs);
	FreeArray(dscnt, hd_min);
	FreeArray(dscnt, vd_min);
	FreeArray(dscnt, wd_min);
	FreeArray(dscnt, wd_scaleM);
	FreeArray(dscnt, wd_scaleP);
	FreeArray(dscnt, vd_scaleM);
	FreeArray(dscnt, vd_scaleP);
	FreeArray(dscnt, fp->Engine->TSFcnt, hd_tsf);
	FreeArray(dscnt, fp->Engine->TSFcnt, vd_tsf);
	FreeArray(2, dscnt, layersCnt, ArrayMax<int>(layersCnt, coresCnt), wlen, ts);
	FreeArray(2, dscnt, layersCnt, ArrayMax<int>(layersCnt, coresCnt), wlen, ts_tr);
	FreeArray(2, dscnt, layersCnt, ArrayMax<int>(layersCnt, coresCnt), wlen, ts_trs);
	FreeArray(2, dscnt, layersCnt, ArrayMax<int>(layersCnt, coresCnt), ts_scaleM);
	FreeArray(2, dscnt, layersCnt, ArrayMax<int>(layersCnt, coresCnt), ts_scaleP);
	FreeArray(2, dscnt, layersCnt, ArrayMax<int>(layersCnt, coresCnt), bv);
	FreeArray(2, dscnt, layersCnt, ArrayMax<int>(layersCnt, coresCnt), mv);
	FreeArray(fp->DataParms->DatasetsCount*fp->Engine->TotalCoresCount, tp);
	FreeArray(fp->DataParms->DatasetsCount*fp->Engine->TotalCoresCount, rp);
	//FreeArray(dscnt, rc, runLog);

	freeSampleTarget(fp->Engine, fp->DataParms, Sample, Target);

	LogClose(fp->DebugParms);

	//delete(fp);


	return 0;
}
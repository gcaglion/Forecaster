//#include <vld.h>

#include <MyNN.h>

EXPORT void getNNOutputRange(NN_Parms* NNParms, double* oScaleMin, double* oScaleMax) {
	switch (NNParms->ActivationFunction) {
	case NN_ACTIVATION_TANH:
		(*oScaleMin) = -1;
		(*oScaleMax) = 1;
		break;
	case NN_ACTIVATION_EXP4:
		(*oScaleMin) = 0;
		(*oScaleMax) = 1;
		break;
	case NN_ACTIVATION_RELU:
		(*oScaleMin) = 0;
		(*oScaleMax) = 1;
		break;
	case NN_ACTIVATION_SOFTPLUS:
		(*oScaleMin) = 0;
		(*oScaleMax) = 1;
		break;
	default:
		(*oScaleMin) = -1;
		(*oScaleMax) = 1;
		break;
	}
}
EXPORT void setNNTopology(NN_Parms* NN) {
	int i, nl;
	int Levcnt;	// Levels count
	char** DescList = MallocArray<char>(MAX_LEVELS, 256);

	//-- 1. Put the comma-separated string values into an array of strings. Max desc length=10
	Levcnt = cslToArray(NN->LevelRatioS, ',', DescList);

	//-- 2. For Network Topology, convert string to float
	for (i = 0; i <= Levcnt; i++) NN->LevelRatio[i] = atof(DescList[i]);
	
	// set LevelsCount
	NN->LevelsCount = (Levcnt + 2);

	// set NodesCount
	NN->NodesCount[DATANODE][0] = NN->InputCount;
	NN->NodesCount[DATANODE][NN->LevelsCount - 1] = NN->OutputCount;
	
	//-- calc nodescount[] (DATANODEs only)
	for (nl = 0; nl<(NN->LevelsCount - 2); nl++) NN->NodesCount[DATANODE][nl+1] = (int)floor(NN->NodesCount[DATANODE][nl] * NN->LevelRatio[nl]);
	
	//-- add context neurons
	for(nl=0; nl<NN->LevelsCount; nl++) NN->NodesCount[CTXNODE][nl] = 0;
	if (NN->UseContext>0) {
		for (nl = NN->LevelsCount-1; nl>=0; nl--) NN->NodesCount[CTXNODE][nl-1] += NN->NodesCount[DATANODE][nl]+NN->NodesCount[CTXNODE][nl];
	}
	//-- add one bias neurons for each layer, except output layer
	for (nl = 0; nl<(NN->LevelsCount-1); nl++) NN->NodesCount[BIASNODE][nl] = 1;
	
	//-- calc total nodes for each layer, plus NodesCountTotal
	NN->NodesCountTotal = 0;
	for (nl = 0; nl<NN->LevelsCount; nl++) {
		NN->NodesCount[TOTNODE][nl] = NN->NodesCount[DATANODE][nl]+NN->NodesCount[CTXNODE][nl]+NN->NodesCount[BIASNODE][nl];
		NN->NodesCountTotal += NN->NodesCount[TOTNODE][nl];
	}

	//-- calc WeightsCountTotal
	NN->WeightsCountTotal = 0;
	for (nl = 0; nl<(NN->LevelsCount - 1); nl++) {
		for (int nn1 = 0; nn1<NN->NodesCount[TOTNODE][nl+1]; nn1++) {
			for (int nn0 = 0; nn0<NN->NodesCount[TOTNODE][nl]; nn0++) {
				NN->WeightsCountTotal++;
			}
		}
	}

	FreeArray(MAX_LEVELS, 100, DescList);
}
EXPORT void mallocNNLog(tCoreLog* coreLog, int levelsCnt, int* nodesCnt, bool mallocIntP, int tscnt) {
	//-- mallocs specific portions of coreLog (FinalW, IntP)

	//-- InitW, FinalW
	coreLog->NNFinalW = (tNNWeight***)malloc((levelsCnt - 1) * sizeof(tNNWeight**));
	coreLog->NNInitW = (tNNWeight***)malloc((levelsCnt - 1) * sizeof(tNNWeight**));
	for (int l = 0; l < (levelsCnt - 1); l++) {
		coreLog->NNFinalW[l] = (tNNWeight**)malloc(nodesCnt[l+1] * sizeof(tNNWeight*));
		coreLog->NNInitW[l] = (tNNWeight**)malloc(nodesCnt[l+1] * sizeof(tNNWeight*));
		for (int fn = 0; fn < nodesCnt[l+1]; fn++) {
			coreLog->NNFinalW[l][fn] = (tNNWeight*)malloc(nodesCnt[l] * sizeof(tNNWeight));
			coreLog->NNInitW[l][fn] = (tNNWeight*)malloc(nodesCnt[l] * sizeof(tNNWeight));
		}
	}
	//-- IntP
	if (mallocIntP) coreLog->IntP = MallocArray<tLogInt>(tscnt);
}
EXPORT void freeNNLog(tCoreLog* coreLog, int levelsCnt, int* nodesCnt, bool freeIntP, int tscnt) {
	//-- InitW, FinalW
	for (int l = 0; l < (levelsCnt - 1); l++) {
		for (int fn = 0; fn < nodesCnt[l + 1]; fn++) {
			free(coreLog->NNFinalW[l][fn]);
			free(coreLog->NNInitW[l][fn]);
		}
		free(coreLog->NNFinalW[l]);
		free(coreLog->NNInitW[l]);
	}
	free(coreLog->NNFinalW);
	free(coreLog->NNInitW);
	//-- IntP
	if (freeIntP) free(coreLog->IntP);
}

void SaveFinalW(NN_Parms* NNParms, NN_Mem* NN, tCoreLog* NNLog, DWORD pid, DWORD tid) {
	//-- This should be called only once at the end of training
	int i, j, l;
	for (l = 0; l<(NNParms->LevelsCount-1); l++) {
		for (j = 0; j < NNParms->NodesCount[TOTNODE][l+1]; j++) {
			for (i = 0; i < NNParms->NodesCount[TOTNODE][l]; i++) {
				NNLog->NNFinalW[l][j][i].ProcessId = pid;
				NNLog->NNFinalW[l][j][i].ThreadId = tid;
				NNLog->NNFinalW[l][j][i].NeuronLevel = l;
				NNLog->NNFinalW[l][j][i].FromNeuron = j;
				NNLog->NNFinalW[l][j][i].ToNeuron = i;
				NNLog->NNFinalW[l][j][i].Weight = NN->W[l][t0][j][i];
				NNLog->NNFinalW[l][j][i].dW = NN->dW[l][t0][j][i];
				NNLog->NNFinalW[l][j][i].dJdW = NN->dJdW[l][t0][j][i];
			}
		}
	}
}
void SaveInitW(NN_Parms* NNParms, NN_Mem* NN, tCoreLog* NNLog, DWORD pid, DWORD tid) {
	//-- This should be called only once at the beginning of training
	int i, j, l;
	for (l = 0; l<(NNParms->LevelsCount-1); l++) {
		for (j = 0; j < NNParms->NodesCount[TOTNODE][l+1]; j++) {
			for (i = 0; i < NNParms->NodesCount[TOTNODE][l]; i++) {
				NNLog->NNInitW[l][j][i].ProcessId = pid;
				NNLog->NNInitW[l][j][i].ThreadId = tid;
				NNLog->NNInitW[l][j][i].NeuronLevel = l;
				NNLog->NNInitW[l][j][i].FromNeuron = j;
				NNLog->NNInitW[l][j][i].ToNeuron = i;
				NNLog->NNInitW[l][j][i].Weight = NN->W[l][t0][j][i];
				NNLog->NNInitW[l][j][i].dW = NN->dW[l][t0][j][i];
				NNLog->NNInitW[l][j][i].dJdW = NN->dJdW[l][t0][j][i];
			}
		}
	}
}
void SaveCoreData_SCGD(tCoreLog* NNLog, int pid, int tid, int epoch, int sampleid, int BPid, int k, int timeStep, double delta, double mu, double alpha, double beta, double lambda, double lambdau, double pnorm, double rnorm, double enorm, double dWnorm, double comp) {
	NNLog->IntP[timeStep].ProcessId = pid;
	NNLog->IntP[timeStep].ThreadId = tid;
	NNLog->IntP[timeStep].Epoch = epoch;
	NNLog->IntP[timeStep].SampleId = sampleid;
	NNLog->IntP[timeStep].BPid = BPid;
	NNLog->IntP[timeStep].K = k;
	NNLog->IntP[timeStep].delta = delta;
	NNLog->IntP[timeStep].mu = mu;
	NNLog->IntP[timeStep].alpha = alpha;
	NNLog->IntP[timeStep].beta = beta;
	NNLog->IntP[timeStep].lambda = lambda;
	NNLog->IntP[timeStep].lambdau = lambdau;
	NNLog->IntP[timeStep].pnorm = pnorm;
	NNLog->IntP[timeStep].rnorm = rnorm;
	NNLog->IntP[timeStep].enorm = enorm;
	NNLog->IntP[timeStep].dWnorm = dWnorm;
	NNLog->IntP[timeStep].comp = comp;
}

void	InitNeurons(NN_Parms* NN, NN_MxData* Mx) {
	double vScaleMin, vScaleMax;
	getNNOutputRange(NN, &vScaleMin, &vScaleMax);

	for (int t = 0; t<TimeSteps; t++) {
		for (int l = 0; l < NN->LevelsCount; l++) {
			//-- Bias node (except for output layer)
			if (l<(NN->LevelsCount-1)) Mx->NN.F[l][t][0] = 1;
			//-- Data nodes
			for (int i = 0; i < NN->NodesCount[DATANODE][l]; i++) {
				Mx->NN.F[l][t][i+NN->NodesCount[BIASNODE][l]] = 0;
				Mx->NN.dF[l][t][i+NN->NodesCount[BIASNODE][l]] = 0;
				Mx->NN.c[l][t][i+NN->NodesCount[BIASNODE][l]] = 1;
			}
			//-- Context nodes
			for (int i = 0; i < NN->NodesCount[CTXNODE][l]; i++) {
				Mx->NN.F[l][t][1+NN->NodesCount[DATANODE][l]+i] = (vScaleMax+vScaleMin)/2;	// see Elman.pdf, p.182
			}
		}
	}
}
void	NNInit(NN_Parms* NN, NN_MxData* Mx, bool loadW, tCoreLog* NNLogs) {
	int i, k, l, x, y;

	for (int t = 0; t<TimeSteps; t++) {

		InitNeurons(NN, Mx);

		//-- Weights
		k = 0;
		//FILE* fw = fopen("c:/temp/W.init", "r");
		//float w, dw;
		for (l = 0; l < (NN->LevelsCount-1); l++) {
			for (i = 0; i < (NN->NodesCount[TOTNODE][l+1] * NN->NodesCount[TOTNODE][l]); i++) {
				y = (int)(i / NN->NodesCount[TOTNODE][l]);
				x = i%NN->NodesCount[TOTNODE][l];

				if (loadW) {
					//-- load weights as we do in Run_NN():
					Mx->NN.W[l][t][y][x] = NNLogs->NNFinalW[l][y][x].Weight;
					Mx->NN.dW[l][t][y][x] = NNLogs->NNFinalW[l][y][x].dW;
					Mx->NN.dJdW[l][t][y][x] = NNLogs->NNFinalW[l][y][x].dJdW;
				} else {
					Mx->NN.W[l][t][y][x] = MyRndDbl(-1 / sqrt((double)NN->NodesCount[TOTNODE][l]), 1 / sqrt((double)NN->NodesCount[TOTNODE][l]));
					Mx->NN.dW[l][t][y][x] = 0;
					Mx->NN.dJdW[l][t][y][x] = 0;
				}

				//fprintf(fw, "%2.10f %2.10f\n", Mx->NN.W[l][t][y][x], Mx->NN.dW[l][t][y][x]);
				//fscanf(fw, "%f %f\n", &w, &dw); Mx->NN.W[l][t][y][x] = w; Mx->NN.dW[l][t][y][x]=dw;

				Mx->NN.scgd->LVV_W[t][k] = &Mx->NN.W[l][t][y][x];
				Mx->NN.scgd->LVV_dW[t][k] = &Mx->NN.dW[l][t][y][x];
				Mx->NN.scgd->LVV_dJdW[t][k] = &Mx->NN.dJdW[l][t][y][x];
				Mx->NN.scgd->LVV_GdJdW[t][k] = &Mx->NN.GdJdW[l][t][y][x];
				k++;
			}
		}
	}
	//fclose(fw);
	Mx->BPCount = 0; Mx->SCGD_progK = 0;

}
NN_Mem	Malloc_NNMem(NN_Parms* pNNParms, int pSampleCount) {
	int i, l, t;
	NN_Mem ret;

	//-- node levels -> [Levels][Time]
	ret.a = (double***)malloc(pNNParms->LevelsCount * sizeof(double**));					// Core
	ret.F = (double***)malloc(pNNParms->LevelsCount * sizeof(double**));					// Core
	ret.dF = (double***)malloc(pNNParms->LevelsCount * sizeof(double**));				// Core
	ret.edF = (double***)malloc(pNNParms->LevelsCount * sizeof(double**));				// Core
	ret.c = (double***)malloc(pNNParms->LevelsCount * sizeof(double**));					// CFR/AG
	for (l = 0; l < pNNParms->LevelsCount; l++) {
		ret.a[l] = (double**)malloc(TimeSteps * sizeof(double*));
		ret.F[l] = (double**)malloc(TimeSteps * sizeof(double*));
		ret.dF[l] = (double**)malloc(TimeSteps * sizeof(double*));
		ret.edF[l] = (double**)malloc(TimeSteps * sizeof(double*));
		ret.c[l] = (double**)malloc(TimeSteps * sizeof(double*));
		for (t = 0; t < TimeSteps; t++) {
			ret.a[l][t] = (double*)malloc(pNNParms->NodesCount[TOTNODE][l] * sizeof(double));
			ret.F[l][t] = (double*)malloc(pNNParms->NodesCount[TOTNODE][l] * sizeof(double));
			ret.dF[l][t] = (double*)malloc(pNNParms->NodesCount[TOTNODE][l] * sizeof(double));
			ret.edF[l][t] = (double*)malloc(pNNParms->NodesCount[TOTNODE][l] * sizeof(double));
			ret.c[l][t] = (double*)malloc(pNNParms->NodesCount[TOTNODE][l] * sizeof(double));
		}
	}
	//-- outer node only -> [Time]
	ret.e = (double**)malloc(TimeSteps * sizeof(double*));
	ret.u = (double**)malloc(TimeSteps * sizeof(double*));
	ret.ge = (double**)malloc(TimeSteps * sizeof(double*));
	ret.Ve = (double**)malloc(TimeSteps * sizeof(double*));
	ret.Vu = (double**)malloc(TimeSteps * sizeof(double*));
	for (t = 0; t < TimeSteps; t++) {
		ret.e[t] = (double*)malloc(pNNParms->NodesCount[TOTNODE][pNNParms->LevelsCount-1] * sizeof(double));
		ret.u[t] = (double*)malloc(pNNParms->NodesCount[TOTNODE][pNNParms->LevelsCount-1] * sizeof(double));
		ret.ge[t] = (double*)malloc(pNNParms->NodesCount[TOTNODE][pNNParms->LevelsCount-1] * sizeof(double));
		ret.Ve[t] = (double*)malloc(pNNParms->NodesCount[TOTNODE][pNNParms->LevelsCount-1] * sizeof(double));
		ret.Vu[t] = (double*)malloc(pNNParms->NodesCount[TOTNODE][pNNParms->LevelsCount-1] * sizeof(double));
	}
	ret.norm_e = (double*)malloc(TimeSteps * sizeof(double));
	ret.norm_ge = (double*)malloc(TimeSteps * sizeof(double));
	ret.mse = (double*)malloc(TimeSteps * sizeof(double));

	//-- weight levels -> [Levels-1][Time]
	ret.W = (double****)malloc((pNNParms->LevelsCount - 1) * sizeof(double***));					// Core
	ret.dW = (double****)malloc((pNNParms->LevelsCount - 1) * sizeof(double***));				// Core
	ret.dJdW = (double****)malloc((pNNParms->LevelsCount - 1) * sizeof(double***));				// Core
	ret.GdJdW = (double****)malloc((pNNParms->LevelsCount - 1) * sizeof(double***));				// Core
	ret.BdW = (double****)malloc((pNNParms->LevelsCount - 1) * sizeof(double***));				// Core - Batch Training
	for (l = 0; l < (pNNParms->LevelsCount - 1); l++) {
		ret.W[l] = (double***)malloc(TimeSteps * sizeof(double**));
		ret.dW[l] = (double***)malloc(TimeSteps * sizeof(double**));
		ret.dJdW[l] = (double***)malloc(TimeSteps * sizeof(double**));
		ret.GdJdW[l] = (double***)malloc(TimeSteps * sizeof(double**));
		ret.BdW[l] = (double***)malloc(TimeSteps * sizeof(double**));
		for (t = 0; t < TimeSteps; t++) {
			ret.W[l][t] = (double**)malloc(pNNParms->NodesCount[TOTNODE][l+1] * sizeof(double*));
			ret.dW[l][t] = (double**)malloc(pNNParms->NodesCount[TOTNODE][l+1] * sizeof(double*));
			ret.dJdW[l][t] = (double**)malloc(pNNParms->NodesCount[TOTNODE][l+1] * sizeof(double*));
			ret.GdJdW[l][t] = (double**)malloc(pNNParms->NodesCount[TOTNODE][l+1] * sizeof(double*));
			ret.BdW[l][t] = (double**)malloc(pNNParms->NodesCount[TOTNODE][l+1] * sizeof(double*));
			for (i = 0; i < pNNParms->NodesCount[TOTNODE][l+1]; i++) {
				ret.W[l][t][i] = (double*)malloc(pNNParms->NodesCount[TOTNODE][l] * sizeof(double));
				ret.dW[l][t][i] = (double*)malloc(pNNParms->NodesCount[TOTNODE][l] * sizeof(double));
				ret.dJdW[l][t][i] = (double*)malloc(pNNParms->NodesCount[TOTNODE][l] * sizeof(double));
				ret.GdJdW[l][t][i] = (double*)malloc(pNNParms->NodesCount[TOTNODE][l] * sizeof(double));
				ret.BdW[l][t][i] = (double*)malloc(pNNParms->NodesCount[TOTNODE][l] * sizeof(double));
			}
		}
	}
	//-- SCGD stuff
	ret.scgd = new tSCGDMem;
	ret.scgd->p = (double*)malloc(pNNParms->WeightsCountTotal*sizeof(double));
	ret.scgd->r = (double*)malloc(pNNParms->WeightsCountTotal*sizeof(double));
	ret.scgd->s = (double*)malloc(pNNParms->WeightsCountTotal*sizeof(double));
	ret.scgd->dW = (double*)malloc(pNNParms->WeightsCountTotal*sizeof(double));
	ret.scgd->TotdW = (double*)malloc(pNNParms->WeightsCountTotal*sizeof(double));
	ret.scgd->newW = (double*)malloc(pNNParms->WeightsCountTotal*sizeof(double));
	ret.scgd->oldW = (double*)malloc(pNNParms->WeightsCountTotal*sizeof(double));
	ret.scgd->prev_r = (double*)malloc(pNNParms->WeightsCountTotal*sizeof(double));
	ret.scgd->alphap = (double*)malloc(pNNParms->WeightsCountTotal*sizeof(double));
	ret.scgd->bp = (double*)malloc(pNNParms->WeightsCountTotal*sizeof(double));
	ret.scgd->lp = (double*)malloc(pNNParms->WeightsCountTotal*sizeof(double));
	ret.scgd->ap = (double*)malloc(pNNParms->WeightsCountTotal*sizeof(double));
	ret.scgd->dE0 = (double*)malloc(pNNParms->WeightsCountTotal*sizeof(double));
	ret.scgd->dE1 = (double*)malloc(pNNParms->WeightsCountTotal*sizeof(double));
	ret.scgd->dE = (double*)malloc(pNNParms->WeightsCountTotal*sizeof(double));
	ret.scgd->E0 = (double*)malloc(pNNParms->WeightsCountTotal*sizeof(double));
	ret.scgd->E1 = (double*)malloc(pNNParms->WeightsCountTotal*sizeof(double));
	ret.scgd->E = (double*)malloc(pNNParms->WeightsCountTotal*sizeof(double));
	ret.scgd->sigmap = (double*)malloc(pNNParms->WeightsCountTotal*sizeof(double));
	ret.scgd->LVV_W = (double***)malloc(TimeSteps * sizeof(double**)); for (t = 0; t < TimeSteps; t++) ret.scgd->LVV_W[t] = (double**)malloc(pNNParms->WeightsCountTotal * sizeof(double*));
	ret.scgd->LVV_dW = (double***)malloc(TimeSteps * sizeof(double**)); for (t = 0; t < TimeSteps; t++) ret.scgd->LVV_dW[t] = (double**)malloc(pNNParms->WeightsCountTotal * sizeof(double*));
	ret.scgd->LVV_dJdW = (double***)malloc(TimeSteps * sizeof(double**)); for (t = 0; t < TimeSteps; t++) ret.scgd->LVV_dJdW[t] = (double**)malloc(pNNParms->WeightsCountTotal * sizeof(double*));
	ret.scgd->LVV_GdJdW = (double***)malloc(TimeSteps * sizeof(double**)); for (t = 0; t < TimeSteps; t++) ret.scgd->LVV_GdJdW[t] = (double**)malloc(pNNParms->WeightsCountTotal * sizeof(double*));

	//-- Jacobian
	//ret.J = MallocArray<double>(pSampleCount, pNNParms->WeightsCountTotal);

	return ret;
}
void	Free_NNMem(NN_Parms* pNNParms, NN_Mem NN, int pSampleCount) {
	int l, t, i;
	//-- node levels -> [Levels][Time]
	for (l = 0; l < pNNParms->LevelsCount; l++) {
		for (t = 0; t < TimeSteps; t++) {
			free(NN.a[l][t]);
			free(NN.F[l][t]);
			free(NN.dF[l][t]);
			free(NN.edF[l][t]);
			free(NN.c[l][t]);
		}
		free(NN.a[l]);
		free(NN.F[l]);
		free(NN.dF[l]);
		free(NN.edF[l]);
		free(NN.c[l]);
	}
	free(NN.a);
	free(NN.F);
	free(NN.dF);
	free(NN.edF);
	free(NN.c);
	//-- outer node only -> [Time]
	for (t = 0; t < TimeSteps; t++) {
		free(NN.e[t]);
		free(NN.u[t]);
		free(NN.ge[t]);
		free(NN.Ve[t]);
		free(NN.Vu[t]);
	}
	free(NN.e);
	free(NN.u);
	free(NN.ge);
	free(NN.Ve);
	free(NN.Vu);
	free(NN.norm_e);
	free(NN.norm_ge);
	free(NN.mse);

	//-- weight levels -> [Levels-1][Time]
	for (l = 0; l < (pNNParms->LevelsCount - 1); l++) {
		for (t = 0; t < TimeSteps; t++) {
			for (i = 0; i < pNNParms->NodesCount[TOTNODE][l+1]; i++) {
				free(NN.W[l][t][i]);
				free(NN.dW[l][t][i]);
				free(NN.dJdW[l][t][i]);
				free(NN.GdJdW[l][t][i]);
				free(NN.BdW[l][t][i]);
			}
			free(NN.W[l][t]);
			free(NN.dW[l][t]);
			free(NN.dJdW[l][t]);
			free(NN.GdJdW[l][t]);
			free(NN.BdW[l][t]);
		}
		free(NN.W[l]);
		free(NN.dW[l]);
		free(NN.dJdW[l]);
		free(NN.GdJdW[l]);
		free(NN.BdW[l]);
	}
	free(NN.W);
	free(NN.dW);
	free(NN.dJdW);
	free(NN.GdJdW);
	free(NN.BdW);

	//-- SCGD stuff
	for (t = 0; t < TimeSteps; t++) {
		free(NN.scgd->LVV_W[t]);
		free(NN.scgd->LVV_dW[t]);
		free(NN.scgd->LVV_dJdW[t]);
		free(NN.scgd->LVV_GdJdW[t]);
	}
	free(NN.scgd->LVV_W);
	free(NN.scgd->LVV_dW);
	free(NN.scgd->LVV_dJdW);
	free(NN.scgd->LVV_GdJdW);
	//--
	free(NN.scgd->p);
	free(NN.scgd->r);
	free(NN.scgd->s);
	free(NN.scgd->dW);
	free(NN.scgd->TotdW);
	free(NN.scgd->newW);
	free(NN.scgd->oldW);
	free(NN.scgd->prev_r);
	free(NN.scgd->alphap);
	free(NN.scgd->bp);
	free(NN.scgd->lp);
	free(NN.scgd->ap);
	free(NN.scgd->dE0);
	free(NN.scgd->dE1);
	free(NN.scgd->dE);
	free(NN.scgd->E0);
	free(NN.scgd->E1);
	free(NN.scgd->E);
	free(NN.scgd->sigmap);

	//-- Jacobian
	//FreeArray(pSampleCount, pNNParms->WeightsCountTotal, NN.J);
}

double	Derivate(int ActivationFunction, double INval) {
	double ret;
	switch (ActivationFunction) {
	case NN_ACTIVATION_TANH:
		ret = (1 - tanh(INval)*tanh(INval));
		break;
	case NN_ACTIVATION_EXP4:
		ret = 4 * exp(4 * INval) / (pow(exp(4 * INval) + 1, 2));
		break;
	case NN_ACTIVATION_RELU:
		ret = (INval > 0) ? 1 : 0;
		break;
	case NN_ACTIVATION_SOFTPLUS:
		ret = 1 / (1 + exp(-INval));
		break;
	default:
		ret = (1 - tanh(INval)*tanh(INval));
		break;
	}
	return ret;
}
double	Derivate2(int ActivationFunction, double INval) {
	double ret;
	switch (ActivationFunction) {
	case NN_ACTIVATION_TANH:
		ret = -(8*(exp(2*INval)-1)*exp(2*INval))/pow((exp(2*INval)+1), 3);
		break;
	case NN_ACTIVATION_EXP4:
		ret = -16*((exp(4*INval)-1)*exp(4*INval))/pow((exp(4*INval)+1), 3);
		break;
	default:
		ret = (1 - tanh(INval)*tanh(INval));
		break;
	}
	return ret;
}
void	Activate(int ActivationFunction, int NeuronCount, double* gain, double* INval, double* OUTval, double* dOUTval) {
	for (int n = 0; n < NeuronCount; n++) {
		switch (ActivationFunction) {
		case NN_ACTIVATION_TANH:
			OUTval[n] = tanh(INval[n]);
			break;
		case NN_ACTIVATION_EXP4:
			OUTval[n] = 1 / (1 + exp(-4 * INval[n]));
			break;
		case NN_ACTIVATION_RELU:
			OUTval[n] = (INval[n] > 0) ? INval[n] : 0;
			break;
		case NN_ACTIVATION_SOFTPLUS:
			OUTval[n] = log(1 + exp(INval[n]));
			break;
		default:
			OUTval[n] = tanh(INval[n]);
			break;
		}
		dOUTval[n] = Derivate(ActivationFunction, INval[n]);
	}
}

void SumUpW(NN_Parms* NN, NN_MxData* Mx, double**** baseW, double**** addedW) {
	//-- baseW = baseW + addedW
	for (int l = 0; l < (NN->LevelsCount - 1); l++) {
		MplusM(NN->NodesCount[TOTNODE][l+1], NN->NodesCount[TOTNODE][l], baseW[l][t0], addedW[l][t0], baseW[l][t0]);
	}
}

void	FeedBack(NN_Parms* NNParms, NN_Mem* NN) {
	//-- Sets values for Context Neurons.

	for (int l = NNParms->LevelsCount-1; l>0; l--) {
		for (int i = 0; i<(NNParms->NodesCount[DATANODE][l]+NNParms->NodesCount[CTXNODE][l]); i++) {
			NN->F[l-1][t0][NNParms->NodesCount[BIASNODE][l-1]+NNParms->NodesCount[DATANODE][l-1]+i] = NN->F[l][t0][NNParms->NodesCount[BIASNODE][l]+i];
		}
	}

}
double	FF(NN_Parms* NNParms, NN_Mem* NN) {

	//-- 1. Feed-Forward and Activation
	for (int l = 0; l<(NNParms->LevelsCount-1); l++) {
		//-- a[l+1] = F[l] * W[l]
		MbyV(NNParms->NodesCount[TOTNODE][l+1], NNParms->NodesCount[TOTNODE][l], NN->W[l][t0], false, NN->F[l][t0], NN->a[l+1][t0]);
		//-- Activation 
		Activate(NNParms->ActivationFunction, NNParms->NodesCount[TOTNODE][l+1], NN->c[l+1][t0], NN->a[l+1][t0], NN->F[l+1][t0], NN->dF[l+1][t0]);
		//-- reset bias neuron at each level (except output level). they should always be 1
		if(l<(NNParms->LevelsCount-2)) NN->F[l+1][t0][0] = 1;
	}

	//-- 1. Feedback to Context Neurons
	if(NNParms->UseContext>0) FeedBack(NNParms, NN);

	//-- Regardless of the method, here we update the network error, and calc eT (1xL2)matrix of e , and ||e|| (norm of e)
	VminusV(NNParms->NodesCount[DATANODE][NNParms->LevelsCount-1], NN->F[NNParms->LevelsCount-1][t0], NN->u[t0], NN->e[t0]);
	NN->norm_e[t0] = Vnorm(NNParms->NodesCount[DATANODE][NNParms->LevelsCount-1], NN->e[t0]);
	//-- the same goes for Validation error
	VminusV(NNParms->NodesCount[DATANODE][NNParms->LevelsCount-1], NN->F[NNParms->LevelsCount-1][t0], NN->Vu[t0], NN->Ve[t0]);

	return NN->norm_e[t0];

}

void   BackupW(NN_Parms* NNParms, double**** w, int timebin) {
	for (int l = 0; l<(NNParms->LevelsCount-1); l++) {
		for (int fn = 0; fn<NNParms->NodesCount[TOTNODE][l+1]; fn++) {
			for (int tn = 0; tn<NNParms->NodesCount[TOTNODE][l]; tn++) {
				w[l][timebin][fn][tn] = w[l][t0][fn][tn];
			}
		}
	}
}
void   RestoreW(NN_Parms* NNParms, double**** w, int timebin) {
	//-- Restore W
	for (int l = 0; l<(NNParms->LevelsCount-1); l++) {
		for (int fn = 0; fn<NNParms->NodesCount[TOTNODE][l+1]; fn++) {
			for (int tn = 0; tn<NNParms->NodesCount[TOTNODE][l]; tn++) {
				w[l][t0][fn][tn] = w[l][timebin][fn][tn];
			}
		}
	}
}
double Ecalc(NN_Parms* NN, NN_MxData* Mx, int pSampleId = -1, double* atW = nullptr) {
	double tse = 0;

	//-- 0. if a specific W is supplied, first copy that into W
	if (atW!=nullptr) {
		BackupW(NN, Mx->NN.W, t5);
		VCopy(NN->WeightsCountTotal, atW, Mx->NN.scgd->LVV_W[t0]);
	}

	//-- if pSampleId is not specified, that's because we need the Global Error to be calculated
	if (pSampleId==-1) {

		//-- 1. reset gse for each neuron
		for (int o = 0; o<NN->OutputCount; o++) Mx->NN.ge[t0][o] = 0;

		for (int s = 0; s<Mx->sampleCnt; s++) {
			//-- 2. Load SampleData into Input Neurons OUT values , and TargetData into u[]
			Mx->NN.F[0][t0][0] = 1;	//-- F[0] is the bias neuron for L0
			for (int i = 0; i<NN->InputCount; i++) Mx->NN.F[0][t0][i+1] = Mx->sample[s][i];
			for (int i = 0; i<NN->OutputCount; i++) Mx->NN.u[t0][i] = Mx->target[s][i];
			//-- 3. Feed Forward (also calcs e[], norm_e)
			FF(NN, &Mx->NN);
			//-- 4. sum up global error for each output neuron
			for (int o = 0; o<NN->OutputCount; o++) Mx->NN.ge[t0][o] += Mx->NN.e[t0][o];
		}

		//-- 5. calc ge norm and tse
		Mx->NN.norm_ge[t0] = Vnorm(NN->OutputCount, Mx->NN.ge[t0]);
		//-- 6. MSE = sum(GSE) / <number of output neurons> / <samples count>
		for (int o = 0; o<NN->OutputCount; o++) tse += pow(Mx->NN.ge[t0][o],2);

	} else {

		//-- 1. Load SampleData into Input Neurons OUT values , and TargetData into u[]
		Mx->NN.F[0][t0][0] = 1;	//-- F[0] is the bias neuron for L0
		for (int i = 0; i<NN->InputCount; i++) Mx->NN.F[0][t0][i+1] = Mx->sample[pSampleId][i];
		for (int i = 0; i<NN->OutputCount; i++) Mx->NN.u[t0][i] = Mx->target[pSampleId][i];
		//-- 2. Feed Forward, and calc squared error on output layer
		FF(NN, &Mx->NN);
		for (int o = 0; o < NN->OutputCount; o++) tse += pow(Mx->NN.e[t0][o], 2);
	}

	//-- 3. if a specific W is supplied, restore W
	if (atW!=nullptr) {
		RestoreW(NN, Mx->NN.W, t5);
	}

	return tse;
}
void   dEcalcCore(NN_Parms* NNParms, NN_MxData* Mx) {
	for (int l = NNParms->LevelsCount-1; l>0; l--) {
		if (l==(NNParms->LevelsCount-1)) {
			//-- top level only
			VbyV2V(NNParms->NodesCount[TOTNODE][l], Mx->NN.e[t0], Mx->NN.dF[l][t0], Mx->NN.edF[l][t0]);											// edF(l) = e * F'(l)
		} else {
			//-- lower levels
			MbyV(NNParms->NodesCount[TOTNODE][l+1], NNParms->NodesCount[TOTNODE][l], Mx->NN.W[l][t0], true, Mx->NN.edF[l+1][t0], Mx->NN.edF[l][t0]);		// edF(l) = edF(l+1) * WT(l+1)
			VbyV2V(NNParms->NodesCount[TOTNODE][l], Mx->NN.edF[l][t0], Mx->NN.dF[l][t0], Mx->NN.edF[l][t0]);										// edF(l) = edF(l)   * F'(l)
		}
		//-- common
		VbyV2M(NNParms->NodesCount[TOTNODE][l], Mx->NN.edF[l][t0], NNParms->NodesCount[TOTNODE][l-1], Mx->NN.F[l-1][t0], false, Mx->NN.dJdW[l-1][t0]);	// dJdW(l) = edF(l) * F(l-1)
	}
}
void   dEcalc(NN_Parms* NNParms, NN_MxData* Mx, bool global = false, bool recalcErr = false, bool calcJacobian=false, double* atW = nullptr, double* odE = nullptr) {

	if (recalcErr) Ecalc(NNParms, Mx, -1);

	//-- 1. if a specific W is supplied, first copy that into W
	if (atW!=nullptr) {
		BackupW(NNParms, Mx->NN.W, t5);
		VCopy(NNParms->WeightsCountTotal, atW, Mx->NN.scgd->LVV_W[t0]);
	}

	//-- 2. actual calc (sets dJdW)
	if (global) {
		//-- 2.1. zero global dE
		for (int l = 0; l<(NNParms->LevelsCount-1); l++) MInit(NNParms->NodesCount[TOTNODE][l+1], NNParms->NodesCount[TOTNODE][l], Mx->NN.GdJdW[l][t0], 0);
		//-- 2.2. calc dJdW after presenting every sample, and sum it up into GdJdW
		for (int s = 0; s<Mx->sampleCnt; s++) {
			//-- 2.2.1. Load SampleData into Input Neurons OUT values , and TargetData into u[]
			Mx->NN.F[0][t0][0] = 1;	//-- F[0] is the bias neuron for L0
			for (int i = 0; i<NNParms->InputCount; i++) Mx->NN.F[0][t0][i+1] = Mx->sample[s][i];
			for (int i = 0; i<NNParms->OutputCount; i++) Mx->NN.u[t0][i] = Mx->target[s][i];
			//-- 2.2.2. Feed Forward (also calcs e[], norm_e)
			FF(NNParms, &Mx->NN);
			//-- 2.2.3. calc dEdW for each sample error
			dEcalcCore(NNParms, Mx);
			//-- 2.2.4 GdJdW = GdJdW + dJdW
			SumUpW(NNParms, Mx, Mx->NN.GdJdW, Mx->NN.dJdW);

			//-- calc Jacobian
			if (calcJacobian) {
				for (int i = 0; i<NNParms->WeightsCountTotal; i++) Mx->NN.J[s][i] = (*Mx->NN.scgd->LVV_dJdW[t0][i]);
			}
		}
	} else {
		dEcalcCore(NNParms, Mx);
	}

	//-- 3. if a specific W is supplied, copy dJdW into output dE, then restore W
	if (atW!=nullptr) {
		VCopy(NNParms->WeightsCountTotal, Mx->NN.scgd->LVV_GdJdW[t0], odE);
		RestoreW(NNParms, Mx->NN.W, t5);
	}

}

void Calc_H(NN_Parms* NN, NN_MxData* Mx) {
	// Hessian matrices for the whole network. There is one matrix for each neuron (n)
	int l, n, j, i;

	for (l = 0; l<(NN->LevelsCount-1); l++) {
		for (n = 0; n < NN->NodesCount[TOTNODE][l+1]; n++) {
			for (j = 0; j < NN->NodesCount[TOTNODE][l]; j++) {
				for (i = 0; i < NN->NodesCount[TOTNODE][l]; i++) {
					Mx->NN.H[l][t0][n][j][i] = Mx->NN.F[l][t0][j] * Mx->NN.F[l][t0][i] * Derivate2(NN->ActivationFunction, Mx->NN.a[l+1][t0][n]);
				}
			}
		}
	}

}
int BP_lm(int pid, int tid, int pEpoch, tDebugInfo* DebugParms, NN_Parms* NN, tCoreLog* NNLogs, NN_MxData* Mx) {

	return 0;
}
int	BP_scgd(int pid, int tid, int pEpoch, tDebugInfo* DebugParms, NN_Parms* NN, tCoreLog* NNLogs, NN_MxData* Mx) {

	int k;

	double sigma, delta, mu, alpha, beta = 0, b1, b2;
	double lambda, lambdau;
	double pnorm, pnorm2;
	double e_old=0, e_new=0, comp;
	bool success;
	double epsilon = NN->TargetMSE / NN->OutputCount;

	//BackupW(NN, Mx->NN.W, t4);
	VInit(NN->WeightsCountTotal, Mx->NN.scgd->TotdW, 0);

	dEcalc(NN, Mx, true);

	//-- 1. Choose initial vector w ; p=r=-E'(w)
	VCopy(NN->WeightsCountTotal, Mx->NN.scgd->LVV_GdJdW[t0], Mx->NN.scgd->p); VbyS(NN->WeightsCountTotal, Mx->NN.scgd->p, -1, Mx->NN.scgd->p);
	VCopy(NN->WeightsCountTotal, Mx->NN.scgd->p, Mx->NN.scgd->r);

	success = true;
	sigma = 1e-4;
	lambda = 1e-6; lambdau = 0;

	k = 0;
	do {
		Mx->NN.scgd->rnorm = Vnorm(NN->WeightsCountTotal, Mx->NN.scgd->r);
		pnorm = Vnorm(NN->WeightsCountTotal, Mx->NN.scgd->p);
		pnorm2 = pow(pnorm, 2);

		//-- 2. if success=true Calculate second-order  information (s and delta)
		if (success) {

			//-- non-Hessian approximation
			sigma = sigma / pnorm;
			//-- get dE0 (dJdW at current W)
			VCopy(NN->WeightsCountTotal, Mx->NN.scgd->LVV_GdJdW[t0], Mx->NN.scgd->dE0);
			//-- get dE1 (dJdW at W+sigma*p)
			VbyS(NN->WeightsCountTotal, Mx->NN.scgd->p, sigma, Mx->NN.scgd->sigmap);
			VplusV(NN->WeightsCountTotal, Mx->NN.scgd->LVV_W[t0], Mx->NN.scgd->sigmap, Mx->NN.scgd->newW);
			//=================================
			dEcalc(NN, Mx, true, true, false, Mx->NN.scgd->newW, Mx->NN.scgd->dE1);
			//-- calc s
			VminusV(NN->WeightsCountTotal, Mx->NN.scgd->dE1, Mx->NN.scgd->dE0, Mx->NN.scgd->dE);
			VdivS(NN->WeightsCountTotal, Mx->NN.scgd->dE, sigma, Mx->NN.scgd->s);
			//-- calc delta
			delta = VdotV(NN->WeightsCountTotal, Mx->NN.scgd->p, Mx->NN.scgd->s);
		}

		//-- 3. scale s and delta

		//--- 3.1 s=s+(lambda-lambdau)*p
		VbyS(NN->WeightsCountTotal, Mx->NN.scgd->p, (lambda-lambdau), Mx->NN.scgd->lp);
		VplusV(NN->WeightsCountTotal, Mx->NN.scgd->s, Mx->NN.scgd->lp, Mx->NN.scgd->s);
		//--- 3.2 delta=delta+(lambda-lambdau)*|p|^2
		delta += (lambda-lambdau)*pnorm2;

		//-- 4. if delta<=0 (i.e. Hessian is not positive definite) , then make it positive
		if (delta <= 0) {
			//-- adjust s
			VbyS(NN->WeightsCountTotal, Mx->NN.scgd->p, (lambda-2*delta/pnorm2), Mx->NN.scgd->lp);
			VplusV(NN->WeightsCountTotal, Mx->NN.scgd->s, Mx->NN.scgd->lp, Mx->NN.scgd->s);
			//-- adjust lambdau
			lambdau = 2 * (lambda - delta / pnorm2);
			//-- adjust delta
			delta = -delta + lambda*pnorm2;
			//-- adjust lambda
			lambda = lambdau;
		}

		//-- 5. Calculate step size
		mu = VdotV(NN->WeightsCountTotal, Mx->NN.scgd->p, Mx->NN.scgd->r);
		alpha = mu / delta;

		//-- 6. Comparison parameter

		//--- 6.1 calc newW=w+alpha*p , which will also be used in (7)
		VbyS(NN->WeightsCountTotal, Mx->NN.scgd->p, alpha, Mx->NN.scgd->dW);
		VplusV(NN->WeightsCountTotal, Mx->NN.scgd->LVV_W[t0], Mx->NN.scgd->dW, Mx->NN.scgd->newW);

		if(success) VCopy(NN->WeightsCountTotal, Mx->NN.scgd->LVV_W[t0], Mx->NN.scgd->oldW);
		//--- 6.2 E(w)
		e_old = Ecalc(NN, Mx, -1, Mx->NN.scgd->oldW);
		//--- 6.3 E(w+dw) is calculated by E_at_w()
		e_new = Ecalc(NN, Mx, -1 ,Mx->NN.scgd->newW);

		//--- 6.4 comp=2*delta*(e_old-e_new)/mu^2
		comp = 2 * delta*(e_old - e_new) / pow(mu, 2);

		if (comp >= 0) {
			//-- 7. Update weight vector

			//-- dW = alpha * p
			VbyS(NN->WeightsCountTotal, Mx->NN.scgd->p, alpha, Mx->NN.scgd->dW);
			//-- W = W + dW
			VplusV(NN->WeightsCountTotal, Mx->NN.scgd->LVV_W[t0], Mx->NN.scgd->dW, Mx->NN.scgd->LVV_W[t0]);
			//-- TotdW = TotdW + dW
			VplusV(NN->WeightsCountTotal, Mx->NN.scgd->TotdW, Mx->NN.scgd->dW, Mx->NN.scgd->TotdW);
			//-- 7.1 recalc  dJdW
			dEcalc(NN, Mx, true, true);

			//-- save r, and calc new r
			VCopy(NN->WeightsCountTotal, Mx->NN.scgd->r, Mx->NN.scgd->prev_r);
			VCopy(NN->WeightsCountTotal, Mx->NN.scgd->LVV_GdJdW[t0], Mx->NN.scgd->r); VbyS(NN->WeightsCountTotal, Mx->NN.scgd->r, -1, Mx->NN.scgd->r);

			//-- reset lambdau
			lambdau = 0; success = true;

			//-- 7a. if k mod N = 0 then restart algorithm, else create new conjugate direction
			if (((k + 1) % NN->NodesCountTotal) == 0) {
				VCopy(NN->WeightsCountTotal, Mx->NN.scgd->r, Mx->NN.scgd->p);
			} else {
				b1 = pow(Vnorm(NN->WeightsCountTotal, Mx->NN.scgd->r), 2);
				b2 = VdotV(NN->WeightsCountTotal, Mx->NN.scgd->r, Mx->NN.scgd->prev_r);
				beta = (b1 - b2) / mu;
				//-- p = r + beta*p
				VbyS(NN->WeightsCountTotal, Mx->NN.scgd->p, beta, Mx->NN.scgd->bp);
				VplusV(NN->WeightsCountTotal, Mx->NN.scgd->bp, Mx->NN.scgd->r, Mx->NN.scgd->p);
			}
			//-- 7b. if comp>=0.75 reduce scale parameter
			if (comp >= 0.75) lambda = lambda / 2;

		} else {
			//-- a reduction in error is not possible.
			lambdau = lambda;
			success = false;
		}

		//-- 8. if comp<0.25 then increase scale parameter
		if (comp<0.25) lambda = lambda * 4;

		//-- 9. if the steepest descent direction r>epsilon and success=true, then set k=k+1 and go to 2, else terminate and return w as the desired minimum
		Mx->NN.scgd->rnorm = Vnorm(NN->WeightsCountTotal, Mx->NN.scgd->r);
		//-- display progress
		WaitForSingleObject(Mx->ScreenMutex, 10);
		gotoxy(0, Mx->ScreenPos); printf("\rProcess %6d, Thread %6d, Iteration %6d , success=%s, rnorm=%f , norm_ge=%f", pid, tid, k, (success)?"TRUE ":"FALSE", Mx->NN.scgd->rnorm, Mx->NN.norm_ge[t0]);
		ReleaseMutex(Mx->ScreenMutex);

		if (DebugParms->SaveInternals>0) SaveCoreData_SCGD(NNLogs, pid, tid, pEpoch, Mx->sampleid, Mx->BPCount, k, Mx->SCGD_progK, delta, mu, alpha, beta, lambda, lambdau, pnorm, Mx->NN.scgd->rnorm, Mx->NN.norm_ge[t0], Vnorm(NN->WeightsCountTotal, Mx->NN.scgd->dW), comp);

		k++; Mx->SCGD_progK++;
	} while ((Mx->NN.scgd->rnorm>0) && (k<NN->SCGDmaxK));

	//RestoreW(NN, Mx->NN.W, t4);

	return(0);
}
int BP_QuickProp(int pid, int tid, int pEpoch, tDebugInfo* DebugParms, NN_Parms* pNNParms, NN_MxData* Mx) {
	//-- as per QuickProp2.pdf, 2.6.3	
	int l, j, i;

	//-- save dJdW[t0]->dJdW[t1]
	for (l = 0; l<(pNNParms->LevelsCount-1); l++) MCopy(pNNParms->NodesCount[TOTNODE][l+1], pNNParms->NodesCount[TOTNODE][l+1], Mx->NN.dJdW[l][t0], Mx->NN.dJdW[l][t1]); 

	//-- calc dJdW
	dEcalc(pNNParms, Mx);

	for (l = 0; l<(pNNParms->LevelsCount-1); l++) {
		for (j = 0; j < pNNParms->NodesCount[TOTNODE][l+1]; j++) {
			for (i = 0; i < pNNParms->NodesCount[TOTNODE][l]; i++) {

				Mx->NN.dW[l][t0][j][i] = pNNParms->LearningRate*Mx->NN.dJdW[l][t0][j][i];

				if (Mx->NN.dW[l][t0][j][i]>0) {

					if (Mx->NN.dJdW[l][t0][j][i]>(pNNParms->mu / (1 + pNNParms->mu)*Mx->NN.dJdW[l][t1][j][i])) {
						Mx->NN.dW[l][t0][j][i] = -pNNParms->mu*Mx->NN.dW[l][t0][j][i];
					} else {
						Mx->NN.dW[l][t0][j][i] = Mx->NN.dJdW[l][t0][j][i] / (Mx->NN.dJdW[l][t1][j][i] - Mx->NN.dJdW[l][t0][j][i])*Mx->NN.dW[l][t0][j][i];
					}
					if (Mx->NN.dJdW[l][t0][j][i]>0) Mx->NN.dW[l][t0][j][i] += pNNParms->LearningRate*Mx->NN.dJdW[l][t0][j][i];
				
				} else if (Mx->NN.dW[l][t0][j][i]<0) {
					if (Mx->NN.dJdW[l][t0][j][i]<(pNNParms->mu / (1 + pNNParms->mu)*Mx->NN.dJdW[l][t1][j][i])) {
						Mx->NN.dW[l][t0][j][i] = -pNNParms->mu*Mx->NN.dW[l][t0][j][i];
					} else {
						Mx->NN.dW[l][t0][j][i] = Mx->NN.dJdW[l][t0][j][i] / (Mx->NN.dJdW[l][t1][j][i] - Mx->NN.dJdW[l][t0][j][i])*Mx->NN.dW[l][t0][j][i];
					}
					if (Mx->NN.dJdW[l][t0][j][i]<0) Mx->NN.dW[l][t0][j][i] += pNNParms->LearningRate*Mx->NN.dJdW[l][t0][j][i];
				
				} else if (Mx->NN.dW[l][t0][j][i] == 0) {
					Mx->NN.dW[l][t0][j][i] -= pNNParms->LearningRate*Mx->NN.dJdW[l][t0][j][i];
				}
			}
		}
	}
	return 0;
}
int BP_Std(int pid, int tid, int pEpoch, tDebugInfo* DebugParms, NN_Parms* NN, NN_MxData* Mx) {
	/*
	int i, h, o;
	double sk;
	double BPdW;
	//-- 2 -> 1
	for (h = 0; h < NN->HiddenCount; h++){
	for (o = 0; o < NN->NodesCount[2]; o++){
	Mx->dk[t0][o] = Mx->e[t0][o] * Mx->dF[2][t0][o];
	BPdW = NN->LearningRate*Mx->dk[t0][o] * Mx->F[1][t0][h];
	Mx->dW[1][t0][o][h] = (1 - NN->LearningMomentum)*BPdW + NN->LearningMomentum*Mx->dW[1][t1][o][h];
	//Mx->W[1][t0][o][h] += Mx->dW[1][t0][o][h];
	}
	}
	//-- 1 -> 0
	for (i = 0; i < (NN->InputCount + NN->ContextCount); i++){
	for (h = 0; h < NN->HiddenCount; h++){
	sk = 0;
	for (o = 0; o < NN->NodesCount[2]; o++) sk += Mx->W[1][t0][o][h] * Mx->dk[t0][o];
	BPdW = NN->LearningRate*sk*Mx->dF[1][t0][h] * Mx->F[0][t0][i];
	Mx->dW[0][t0][h][i] = (1 - NN->LearningMomentum)*BPdW + NN->LearningMomentum*Mx->dW[0][t1][h][i];
	//Mx->W[0][t0][h][i] += Mx->dW[0][t0][h][i];
	}
	}
	*/

	dEcalc(NN, Mx);

	//-- calc dW 
	for (int l = 0; l<(NN->LevelsCount-1); l++) {
		for (int j = 0; j < NN->NodesCount[TOTNODE][l+1]; j++) {
			for (int i = 0; i < NN->NodesCount[TOTNODE][l]; i++) {
				Mx->NN.dW[l][t0][j][i] = (1-NN->LearningMomentum) * (-NN->LearningRate * Mx->NN.dJdW[l][t0][j][i]) +NN->LearningMomentum * Mx->NN.dW[l][t1][j][i];
			}
		}
	}
	return 0;
}
int BP_Rprop(int pid, int tid, int pEpoch, tDebugInfo* DebugParms, NN_Parms* pNNParms, NN_MxData* Mx) {

	double d0 = pNNParms->d0;
	double dmax = 50;
	double dmin = 1e-6;
	double nuplus = 1.2;
	double numinus = 0.5;

	double d[2] = { 0,0 };

	dEcalc(pNNParms, Mx);

	for (int l = 0; l<(pNNParms->LevelsCount-1); l++) {
		for (int j = 0; j < pNNParms->NodesCount[TOTNODE][l+1]; j++) {
			for (int i = 0; i < pNNParms->NodesCount[TOTNODE][l]; i++) {

				if ((Mx->NN.dJdW[l][t1][j][i] * Mx->NN.dJdW[l][t0][j][i]) >0) {
					d[t0] = min(d[t1]*nuplus, dmax);
					Mx->NN.dW[l][t0][j][i] = -sgn(Mx->NN.dJdW[l][t0][j][i])*d[0];
					Mx->NN.W[l][t0][j][i] += Mx->NN.dW[l][t0][j][i];
					Mx->NN.dJdW[l][t1][j][i] = Mx->NN.dJdW[l][t0][j][i];
				} else if ((Mx->NN.dJdW[l][t1][j][i] * Mx->NN.dJdW[l][t0][j][i]) <0) {
					d[t0] = max(d[t1]*numinus, dmin);
					Mx->NN.dJdW[l][t1][j][i] = 0;
				} else {
					Mx->NN.dW[l][t0][j][i] = -sgn(Mx->NN.dJdW[l][t0][j][i])*d[0];
					Mx->NN.W[l][t0][j][i] += Mx->NN.dW[l][t0][j][i];
					Mx->NN.dJdW[l][t1][j][i] = Mx->NN.dJdW[l][t0][j][i];
				}

			}
		}
	}

	return(1);
}

int Calc_dW(int pid, int tid, int pEpoch, tDebugInfo* pDebugParms, NN_Parms* NN, tCoreLog* NNLogs, NN_MxData* Mx) {
	//-- All the BP routines should only set Mx->dW , and NOT change Mx->W

	int ret;	//-- see CalcdWType in NNTrain()

	//-- common to all BP variants
	//if (NN->BP_Algo!=BP_RPROP) SavePrevWeights(NN, Mx);

	switch (NN->BP_Algo) {
	case BP_STD:
		ret = BP_Std(pid, tid, pEpoch, pDebugParms, NN, Mx);
		break;
	case BP_QUICKPROP:
		ret = BP_QuickProp(pid, tid, pEpoch, pDebugParms, NN, Mx);
		break;
	case BP_RPROP:
		ret = BP_Rprop(pid, tid, pEpoch, pDebugParms, NN, Mx);
		break;
	case BP_SCGD:
		ret = BP_scgd(pid, tid, pEpoch, pDebugParms, NN, NNLogs, Mx);
	case BP_LM:
		ret = BP_lm(pid, tid, pEpoch, pDebugParms, NN, NNLogs, Mx);
		break;
	}
	Mx->BPCount++;

	return ret;
}

int NNTrain_Global(tDebugInfo* pDebugParms, NN_Parms* NNParms, tCoreLog* NNLogs, NN_MxData* Mx, int pSampleCount, double** pSampleData, double** pTargetData, double** pSampleDataV, double** pTargetDataV) {

	int pid = GetCurrentProcessId();
	int tid = GetCurrentThreadId();

	int BatchCount, BatchSize, BatchExtras;
	switch (NNParms->TrainingBatchCount) {
	case 0:
		//-- stochastic
		LogWrite(pDebugParms, LOG_ERROR, "Stochastic Training cannot be used with a Global Optimization Training method.\n", 0);
		return -1;
	case 1:
		//-- batch
		BatchCount = 1;
		BatchSize = pSampleCount;
		BatchExtras = 0;
		break;
	default:
		//-- mini-batch
		BatchCount = NNParms->TrainingBatchCount;
		BatchSize = (int)floor(pSampleCount/BatchCount);
		BatchExtras = pSampleCount-(BatchCount*BatchSize);
		break;
	}

	double tse0 = Ecalc(NNParms, Mx, -1);
	double mse0 = tse0 / pSampleCount / NNParms->OutputCount;
	if (NNParms->BP_Algo==BP_SCGD) {
		BP_scgd(pid, tid, 0, pDebugParms, NNParms, NNLogs, Mx);
	} else {
		BP_lm(pid, tid, 0, pDebugParms, NNParms, NNLogs, Mx);
	}
	double tse1 = Ecalc(NNParms, Mx, -1);
	double mse1 = tse1 / pSampleCount / NNParms->OutputCount;

	NNLogs->ActualEpochs = 2;
	NNLogs->IntCnt = Mx->SCGD_progK;
	SaveMSEData(NNLogs, pid, tid, 0, mse0, 0);
	SaveMSEData(NNLogs, pid, tid, 1, mse1, 0);

	return 0;
}
int NNTrain(tDebugInfo* pDebugParms, NN_Parms* NNParms, tCoreLog* NNLogs, NN_MxData* Mx, int pSampleCount, double** pSampleData, double** pTargetData, double** pSampleDataV, double** pTargetDataV) {
	int s, si;
	int epoch;
	double MSE_T = 1000, MSE_V = 1000;
	double TSE_T, TSE_V;
	double prevMSE_T;
	int pid = GetCurrentProcessId();
	int tid = GetCurrentThreadId();
	int CalcdWType;	//-- 0: update BdW=BdW+dW after every sample, and W=W+BdW after every batch

	//-- Samples shuffle
	int* sl = (int*)malloc(pSampleCount*sizeof(int)); for (int i = 0; i<pSampleCount; i++) sl[i] = i;
	if(NNParms->UseContext==0) ShuffleArray(sl, pSampleCount);

	int BatchCount, BatchSize, BatchExtras;
	switch (NNParms->TrainingBatchCount) {
	case 0:
		//-- stochastic
		BatchCount = pSampleCount;
		BatchSize = 1;
		BatchExtras = 0;
		break;
	case 1:
		//-- batch
		BatchCount = 1;
		BatchSize = pSampleCount;
		BatchExtras = 0;
		break;
	default:
		//-- mini-batch
		BatchCount = NNParms->TrainingBatchCount;
		BatchSize = (int)floor(pSampleCount/BatchCount);
		BatchExtras = pSampleCount-(BatchCount*BatchSize);
		break;
	}

	for (epoch = 0; epoch < NNParms->MaxEpochs; epoch++) {
		//-- reset sample id, and set tse=0
		si = 0;
		TSE_T = 0; TSE_V = 0;
		for (int b = 0; b<BatchCount; b++) {

			//-- 0. for each batch, BdW=0
			for (int l = 0; l < (NNParms->LevelsCount - 1); l++) MInit(NNParms->NodesCount[TOTNODE][l+1], NNParms->NodesCount[TOTNODE][l], Mx->NN.BdW[l][t0], 0);
			
			for (int i = 0; i < BatchSize; i++) {

				//-- 1. present every sample in the batch, and sum up total error in tse
				s = sl[si];
				//if (Mx->useValidation>0) TSE_V += CalcNetworkTSE(NNParms, Mx, pSampleDataV[s], pTargetDataV[s]);
				TSE_T += Ecalc(NNParms, Mx, si);

				//-- next sample id
				si++;
			}

			//-- 1.2 Calc dW for every batch based on BP algorithm
			Mx->sampleid = si;
			CalcdWType = Calc_dW(pid, tid, epoch, pDebugParms, NNParms, NNLogs, Mx);

			//-- 1.3 BdW = BdW + dW (only if specific Algo does not do it internally)
			if (CalcdWType==0) SumUpW(NNParms, Mx, Mx->NN.BdW, Mx->NN.dW);


			//-- 2. Weight update after every batch: W = W + BdW			
			if (CalcdWType==0) SumUpW(NNParms, Mx, Mx->NN.W, Mx->NN.BdW);

		}

		//-- 4. Calc MSE for epoch , and exit if less than TargetMSE
		prevMSE_T = MSE_T;	// save previous MSE
		MSE_T = TSE_T / pSampleCount / NNParms->OutputCount;
		if (Mx->useValidation>0) {
			MSE_V = TSE_V / pSampleCount / NNParms->OutputCount;
			if (NNParms->StopAtDivergence == 1 && MSE_T > prevMSE_T) break;
		}

		//-- display progress
		WaitForSingleObject(Mx->ScreenMutex, 10);
		gotoxy(0, Mx->ScreenPos); printf("\rProcess %6d, Thread %6d, Epoch %6d , Training MSE=%f , Validation MSE=%f", pid, tid, epoch, MSE_T, MSE_V);
		ReleaseMutex(Mx->ScreenMutex);

		SaveMSEData(NNLogs, pid, tid, epoch, MSE_T, (Mx->useValidation>0) ? MSE_V : 0);

		if (MSE_T < NNParms->TargetMSE) {
			epoch++;
			break;
		}
	}
	NNLogs->ActualEpochs = epoch;
	NNLogs->IntCnt = epoch;

	LogWrite(pDebugParms, LOG_INFO, "NNTrain() CheckPoint 4 - Thread=%d ; Final MSE_T=%f ; Final MSE_V=%f\n", 2, tid, MSE_T, MSE_V);
	return 0;
}

EXPORT void Run_NN(tDebugInfo* pDebugParms, NN_Parms* NNParms, tCoreLog* NNLogs, tDataShape* pInputData, int pid, int tid, int pSampleCount, double** pSample, double** pTarget) {
	int i, s, l, j;
	int vTSCount = 1, d = 0;
	double vActual;
	double* vPrediction = nullptr;

	//-- 0. mallocs
	NN_MxData MxData;
	MxData.NN = Malloc_NNMem(NNParms, pSampleCount);
	double* tmpSample = (double*)malloc(NNParms->InputCount * sizeof(double));

	//-- 1. Load W*** from NNParms->NNFinalW[Level][FromN][ToN] 
	for (l = 0; l<(NNParms->LevelsCount-1); l++) {
		for (j = 0; j<NNParms->NodesCount[TOTNODE][l+1]; j++) {
			for (i = 0; i<NNParms->NodesCount[TOTNODE][l]; i++) {
				MxData.NN.W[l][t0][j][i] = NNLogs->NNFinalW[l][j][i].Weight;
				MxData.NN.dW[l][t0][j][i] = NNLogs->NNFinalW[l][j][i].dW;
				MxData.NN.dJdW[l][t0][j][i] = NNLogs->NNFinalW[l][j][i].dJdW;
			}
		}
	}

	//-- 2. Init Neurons
	InitNeurons(NNParms, &MxData);

	//-- 3. Write First window of data, with no prediction (that is, write the first sample)
	for (i = 0; i<NNParms->InputCount; i++) SaveRunData(NNLogs, pid, tid, i, pSample[0][i], NULL);

	//-- 4. Write Training Set data, with next-step prediction

	//-- 4.1 In-Sample
	for (s = 0; s<pSampleCount; s++) {
		for (i = 0; i < NNParms->InputCount; i++) {
			tmpSample[i] = pSample[s][i];				//-- Only used for the last sample ( pSample[pSampleCount-1] )
			MxData.NN.F[0][t0][i+1] = tmpSample[i];		//-- Present each sample to input neurons (+1 to skip bias neuron at level 0)
		}
		//-- initialize context neurons (???)
		//for (i = NNParms->InputCount; i< NNParms->NodesCount[0]; i++) {
		//	MxData.NN.F[0][t0][i] = 0;	// Initiali
		//}
		FF(NNParms, &MxData.NN);							//-- Feed-Forward the network;
		vPrediction = MxData.NN.F[NNParms->LevelsCount-1][t0];	//-- Predicted  Data. All steps
		vActual = pTarget[s][0];
		//-- Write RunLog structure
		SaveRunData(NNLogs, pid, tid, NNParms->InputCount + s, vActual, vPrediction);
	}

	//-- 4.2 Out-of-Sample . This always uses predicted value from previous step as actual value. if we do have actual future data, this is updated in CalcForecastFromEngineOutput()
	for (s = 0; s < pInputData->PredictionLen; s++) {
		ShiftArray(SHIFT_BACKWARD, NNParms->InputCount, tmpSample, vActual);

		for (i = 0; i < NNParms->InputCount; i++) MxData.NN.F[0][t0][i+1] = tmpSample[i];	//-- Present each sample to input neurons
		FF(NNParms, &MxData.NN);															//-- Feed-Forward the network;
		vPrediction = MxData.NN.F[NNParms->LevelsCount-1][t0];								//-- Predicted  Data. All steps

		SaveRunData(NNLogs, pid, tid, (s + pSampleCount+NNParms->InputCount), NULL, vPrediction);
		vActual = vPrediction[0];
	}
	/*
	for (s = 0; s < pInputData->PredictionLen; s++) {

	// Target[s] only exist while s<SampleCount. Beyond that, Actual is prediction from previous step
	vActual = vPrediction[0];

	//-- Sample beyond SampleCount must be build, regardless of pOOS
	ShiftArray(SHIFT_BACKWARD, NNParms->InputCount, tmpSample, vActual);

	for (i = 0; i < NNParms->InputCount; i++) MxData.NN.F[0][t0][i] = tmpSample[i];	//-- Present each sample to input neurons
	FF(NNParms, &MxData);																//-- Feed-Forward the network;
	vPrediction = MxData.NN.F[NNParms->LevelsCount-1][t0];								//-- Predicted  Data. All steps

	SaveRunData(NNLogs, pid, tid, (s + pSampleCount+NNParms->InputCount), vActual, vPrediction);
	}
	*/
	//-- 5. frees()
	free(tmpSample);
	Free_NNMem(NNParms, MxData.NN, pSampleCount);

}
EXPORT int  Train_NN(int pCorePos, int pTotCores, HANDLE pScreenMutex, tDebugInfo* pDebugParms, NN_Parms* pNNParms, tCoreLog* pNNLogs, bool loadW, int pSampleCount, double** pSampleData, double** pTargetData, int useValidation, double** pSampleDataV, double** pTargetDataV) {
	int pid = GetCurrentProcessId();
	int tid = GetCurrentThreadId();
	int ret;

	// srand()
	srand((unsigned int)time(NULL));

	// mallocs
	NN_MxData MxData;
	MxData.NN = Malloc_NNMem(pNNParms, pSampleCount);
	MxData.ScreenPos = pCorePos+1;
	MxData.ScreenMutex = pScreenMutex;
	MxData.useValidation = useValidation;
	MxData.sampleCnt = pSampleCount;
	MxData.sample = pSampleData;
	MxData.target = pTargetData;

	//-- Init Weights and Neurons
	NNInit(pNNParms, &MxData, loadW, pNNLogs);
	//-- Save Initial Weights
	SaveInitW(pNNParms, &MxData.NN, pNNLogs, pid, tid);
	//-- Train 
	
	if(pNNParms->BP_Algo==BP_SCGD || pNNParms->BP_Algo==BP_LM){
		ret = NNTrain_Global(pDebugParms, pNNParms, pNNLogs, &MxData, pSampleCount, pSampleData, pTargetData, pSampleDataV, pTargetDataV);
	} else {
		ret = NNTrain(pDebugParms, pNNParms, pNNLogs, &MxData, pSampleCount, pSampleData, pTargetData, pSampleDataV, pTargetDataV);
	}
	
	//-- Save Final Weights
	SaveFinalW(pNNParms, &MxData.NN, pNNLogs, pid, tid);

	//-- free()s
	Free_NNMem(pNNParms, MxData.NN, pSampleCount);

	return ret;
}

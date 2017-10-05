//#include <vld.h>

#include <MyNN.h>

__declspec(dllexport) void __stdcall setNNTopology(NN_Parms* NN) {
	int i, nl;
	int Levcnt;	// Levels count
				//char** DescList = (char**)malloc(MAX_LEVELS * sizeof(char*)); for (i = 0; i < MAX_LEVELS; i++) DescList[i] = (char*)malloc(100);
	char** DescList = MallocArray<char>(MAX_LEVELS, 256);

	//-- 1. Put the comma-separated string values into an array of strings. Max desc length=10
	Levcnt = cslToArray(NN->LevelRatioS, ',', DescList);

	//-- 2. For Network Topology, convert string to float
	for (i = 0; i <= Levcnt; i++) {
		NN->LevelRatio[i] = atof(DescList[i]);
	}
	// set LevelsCount
	NN->LevelsCount = (Levcnt + 2);

	// set NodesCount, NodesCountTotal
	NN->NodesCount[0] = NN->InputCount;
	NN->NodesCount[NN->LevelsCount - 1] = NN->OutputCount;
	NN->NodesCountTotal = NN->InputCount + NN->OutputCount;
	//-- calc nodescount[], totalnodescount
	for (nl = 0; nl<(NN->LevelsCount - 2); nl++) {
		NN->NodesCount[nl + 1] = (int)floor(NN->NodesCount[nl] * NN->LevelRatio[nl]);
		NN->NodesCountTotal += NN->NodesCount[nl + 1];
	}
	//-- add context neurons
	if (NN->UseContext>0) {
		for (nl = NN->LevelsCount-1; nl>=0; nl--) {
			NN->NodesCount[nl-1] += NN->NodesCount[nl];
		}
	}
	//-- add bias neurons one for each layer, except output layer
	for (nl = 0; nl<(NN->LevelsCount-1); nl++) {
		NN->NodesCount[nl] += 1;
	}
	//-- calc totalweightscount
	NN->WeightsCountTotal = 0;
	for (nl = 0; nl<(NN->LevelsCount - 1); nl++) {
		for (int nn1 = 0; nn1<NN->NodesCount[nl + 1]; nn1++) {
			for (int nn0 = 0; nn0<NN->NodesCount[nl]; nn0++) {
				NN->WeightsCountTotal++;
			}
		}
	}

	FreeArray(MAX_LEVELS, 100, DescList);
}
__declspec(dllexport) void __stdcall mallocNNLog(tCoreLog* coreLog, int levelsCnt, int* nodesCnt, bool mallocIntP, int tscnt) {
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
__declspec(dllexport) void __stdcall freeNNLog(tCoreLog* coreLog, int levelsCnt, int* nodesCnt, bool freeIntP, int tscnt) {
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
		for (j = 0; j < NNParms->NodesCount[l+1]; j++) {
			for (i = 0; i < NNParms->NodesCount[l]; i++) {
				NNLog->NNFinalW[l][j][i].ProcessId = pid;
				NNLog->NNFinalW[l][j][i].ThreadId = tid;
				NNLog->NNFinalW[l][j][i].NeuronLevel = l;
				NNLog->NNFinalW[l][j][i].FromNeuron = j;
				NNLog->NNFinalW[l][j][i].ToNeuron = i;
				NNLog->NNFinalW[l][j][i].Weight = NN->W[l][t0][j][i];
				NNLog->NNFinalW[l][j][i].dW = NN->dW[l][t0][j][i];
				NNLog->NNFinalW[l][j][i].dJdW = NN->dJdW[l][t0][j][i];
				//-- Context neurons
				//if (l==0) NNLog->NNFinalW[l][j][i].CtxValue = (i >= NNParms->InputCount) ? NN->F[0][t0][i] : 0;
			}
		}
	}
}
void SaveInitW(NN_Parms* NNParms, NN_Mem* NN, tCoreLog* NNLog, DWORD pid, DWORD tid) {
	//-- This should be called only once at the beginning of training
	int i, j, l;
	for (l = 0; l<(NNParms->LevelsCount-1); l++) {
		for (j = 0; j < NNParms->NodesCount[l+1]; j++) {
			for (i = 0; i < NNParms->NodesCount[l]; i++) {
				NNLog->NNInitW[l][j][i].ProcessId = pid;
				NNLog->NNInitW[l][j][i].ThreadId = tid;
				NNLog->NNInitW[l][j][i].NeuronLevel = l;
				NNLog->NNInitW[l][j][i].FromNeuron = j;
				NNLog->NNInitW[l][j][i].ToNeuron = i;
				NNLog->NNInitW[l][j][i].Weight = NN->W[l][t0][j][i];
				NNLog->NNInitW[l][j][i].dW = NN->dW[l][t0][j][i];
				NNLog->NNInitW[l][j][i].dJdW = NN->dJdW[l][t0][j][i];
				//-- Context neurons
				//if (l==0) NNLog->NNInitW[l][j][i].CtxValue = (i >= NNParms->InputCount) ? F0[t0][i] : 0;
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

void BackupNeurons(NN_Parms* NNParms, NN_Mem* NN) {
	//-- Backup current neurons (into t4)
	for (int l = 0; l<NNParms->LevelsCount; l++) {
		for (int i = 0; i<NNParms->NodesCount[l]; i++) {
			NN->a[l][t4][i] = NN->a[l][t0][i];
			NN->F[l][t4][i] = NN->F[l][t0][i];
			NN->dF[l][t4][i] = NN->dF[l][t0][i];
			NN->c[l][t4][i] = NN->c[l][t0][i];
		}
	}
}
void RestoreNeurons(NN_Parms* NNParms, NN_Mem* NN) {
	//-- Restore neurons
	for (int l = 0; l<NNParms->LevelsCount; l++) {
		for (int i = 0; i<NNParms->NodesCount[l]; i++) {
			NN->a[l][t0][i] = NN->a[l][t4][i];
			NN->F[l][t0][i] = NN->F[l][t4][i];
			NN->dF[l][t0][i] = NN->dF[l][t4][i];
			NN->c[l][t0][i] = NN->c[l][t4][i];
		}
	}
}
void BackupWeights(NN_Parms* NNParms, NN_Mem* NN) {
	//-- Backup current W (into t4)
	for (int l = 0; l<(NNParms->LevelsCount-1); l++) {
		for (int fn = 0; fn<NNParms->NodesCount[l+1]; fn++) {
			for (int tn = 0; tn<NNParms->NodesCount[l]; tn++) {
				NN->W[l][t4][fn][tn] = NN->W[l][t0][fn][tn];
			}
		}
	}
}
void RestoreWeights(NN_Parms* NNParms, NN_Mem* NN) {
	//-- Restore W
	for (int l = 0; l<(NNParms->LevelsCount-1); l++) {
		for (int fn = 0; fn<NNParms->NodesCount[l+1]; fn++) {
			for (int tn = 0; tn<NNParms->NodesCount[l]; tn++) {
				NN->W[l][t0][fn][tn] = NN->W[l][t4][fn][tn];
			}
		}
	}
}
void SavePrevWeights(NN_Parms* NNParms, NN_MxData* Mx) {
	int l, j, i;

	for (l = 0; l<(NNParms->LevelsCount-1); l++) {
		for (j = 0; j < NNParms->NodesCount[l+1]; j++) {
			for (i = 0; i < NNParms->NodesCount[l]; i++) {
				//-- (t-2)
				Mx->NN.W[l][t2][j][i] = Mx->NN.W[l][t1][j][i];
				Mx->NN.dW[l][t2][j][i] = Mx->NN.dW[l][t1][j][i];
				Mx->NN.dJdW[l][t2][j][i] = Mx->NN.dJdW[l][t1][j][i];
				Mx->NN.Q_dJdW[l][t2][j][i] = Mx->NN.Q_dJdW[l][t1][j][i];
				//-- (t-1)
				Mx->NN.W[l][t1][j][i] = Mx->NN.W[l][t0][j][i];
				Mx->NN.dW[l][t1][j][i] = Mx->NN.dW[l][t0][j][i];
				Mx->NN.dJdW[l][t1][j][i] = Mx->NN.dJdW[l][t0][j][i];
				Mx->NN.Q_dJdW[l][t1][j][i] = Mx->NN.Q_dJdW[l][t0][j][i];
			}
		}
	}
	/*
	//-- Hessian matrices
	for (l = 0; l<(NNParms->LevelsCount - 1); l++){
	for (n = 0; n < NNParms->NodesCount[l + 1]; n++){
	for (j = 0; j < NNParms->NodesCount[l]; j++){
	for (i = 0; i < NNParms->NodesCount[l]; i++){
	//-- (t-2)
	Mx->H[l][t2][n][j][i] = Mx->H[l][t1][n][j][i];
	//-- (t-1)
	Mx->H[l][t1][n][j][i] = Mx->H[l][t0][n][j][i];
	}
	}
	}
	}
	*/
}

double Derivate(int ActivationFunction, double INval) {
	double ret;
	switch (ActivationFunction) {
	case NN_ACTIVATION_TANH:
		ret = (1 - tanh(INval)*tanh(INval));
		break;
	case NN_ACTIVATION_EXP4:
		ret = 4 * exp(4 * INval) / (pow(exp(4 * INval) + 1, 2));
		break;
	default:
		ret = (1 - tanh(INval)*tanh(INval));
		break;
	}
	return ret;
}
double Derivate2(int ActivationFunction, double INval) {
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
void Activate(int ActivationFunction, int NeuronCount, double* gain, double* INval, double* OUTval, double* dOUTval) {
	for (int n = 0; n < NeuronCount; n++) {
		switch (ActivationFunction) {
		case NN_ACTIVATION_TANH:
			OUTval[n] = tanh(INval[n]);
			break;
		case NN_ACTIVATION_EXP4:
			OUTval[n] = 1 / (1 + exp(-4 * INval[n]));
			break;
		default:
			OUTval[n] = tanh(INval[n]);
			break;
		}
		dOUTval[n] = Derivate(ActivationFunction, INval[n]);
	}
}

void FeedBack(NN_Parms* NNParms, NN_Mem* NN, bool Zero) {

	//-- Sets values for Context Neurons. Called by FF (Zero=false) and Run_NN (Zero=true)

	int i, l, cc;

	cc = 0;
	for (l = NNParms->LevelsCount-1; l>0; l--) {
		cc = NNParms->NodesCount[l]-cc+((l==NNParms->LevelsCount-1) ? 0 : 1);
		for (i = 0; i<cc; i++) {
			NN->F[l-1][t0][NNParms->NodesCount[l-1]-cc+i] = (Zero) ? 0 : NN->F[l][t0][i+((l==NNParms->LevelsCount-1) ? 0 : 1)];
		}
	}
}
void FF(NN_Parms* pNNParms, NN_Mem* NN, int set) {

	//-- 1. Feed-Forward operation
	for (int l = 0; l<(pNNParms->LevelsCount-1); l++) {
		//-- 1.1. build neuron input as sum of lower-level neurons' output
		for (int tn = 0; tn<pNNParms->NodesCount[l+1]; tn++) {
			NN->a[l+1][t0][tn] = 0;
			for (int fn = 0; fn<pNNParms->NodesCount[l]; fn++) {
				NN->a[l+1][t0][tn] += NN->F[l][t0][fn]*NN->W[l][t0][tn][fn];
			}
		}
		//-- 1.2. calc neuron output by activation
		Activate(pNNParms->ActivationFunction, pNNParms->NodesCount[l+1], NN->c[l+1][t0], NN->a[l+1][t0], NN->F[l+1][t0], NN->dF[l+1][t0]);
		//-- 1.3. reset bias neurons. they should always be 1
		NN->F[l][t0][0] = 1;
	}

	//-- 2. Hidden->Context feedback
	if (pNNParms->UseContext==1) FeedBack(pNNParms, NN, false);

	//-- 3. calc Network Error (J)
	int n = pNNParms->OutputCount;
	double se = 0;
	for (int o = 0; o<n; o++) {
		NN->e[set][t0][o] = NN->F[pNNParms->LevelsCount-1][t0][o]-NN->u[set][t0][o];
		se += pow(NN->e[set][t0][o], 2);
	}
	NN->norm_e[set][t0] = se/n;

}

double CalcNetworkError(NN_Parms* pNNParms, NN_MxData* Mx, int set, double* pSample, double* pTarget) {

	//-- 1. Load sample data into Input Neurons OUT values , and target data into u[]
	Mx->NN.F[0][t0][0] = 1;	//-- F[0] is the bias neuron for L0
	for (int i = 0; i<pNNParms->InputCount; i++) Mx->NN.F[0][t0][i+1] = pSample[i];
	for (int i = 0; i<pNNParms->OutputCount; i++) Mx->NN.u[set][t0][i] = pTarget[i];
	//-- 2. Feed Forward
	FF(pNNParms, &Mx->NN, set);

	return Mx->NN.norm_e[set][t0]*pNNParms->OutputCount;
}

void Calc_H(NN_Parms* NN, NN_MxData* Mx) {
	// Hessian matrices for the whole network. There is one matrix for each neuron (n)
	int l, n, j, i;

	for (l = 0; l<(NN->LevelsCount - 1); l++) {
		for (n = 0; n < NN->NodesCount[l + 1]; n++) {
			for (j = 0; j < NN->NodesCount[l]; j++) {
				for (i = 0; i < NN->NodesCount[l]; i++) {
					Mx->NN.H[l][t0][n][j][i] = Mx->NN.F[l][t0][j] * Mx->NN.F[l][t0][i] * Derivate2(NN->ActivationFunction, Mx->NN.a[l + 1][t0][n]);
				}
			}
		}
	}

}

void dJdWcalc(NN_Parms* NNParms, NN_Mem* NN) {

	for (int l = NNParms->LevelsCount - 1; l > 0; l--) {

		if (l==(NNParms->LevelsCount-1)) {
			//-- top level only
			VbyV2V(NNParms->NodesCount[l], NN->e[TRAINING][t0], NN->dF[l][t0], NN->edF[l][t0]);										// edF(l) = e * F'(l)
		} else {
			//-- lower levels
			MbyV(NNParms->NodesCount[l+1], NNParms->NodesCount[l], NN->W[l][t0], true, NN->edF[l+1][t0], NN->edF[l][t0]);	// edF(l) = edF(l+1) * WT(l+1)
			VbyV2V(NNParms->NodesCount[l], NN->edF[l][t0], NN->dF[l][t0], NN->edF[l][t0]);									// edF(l) = edF(l)   * F'(l)
		}
		//-- common
		VbyV2M(NNParms->NodesCount[l], NN->edF[l][t0], NNParms->NodesCount[l-1], NN->F[l-1][t0], false, NN->dJdW[l-1][t0]);	// dJdW(l) = edF(l) * F(l-1)
	}

}

void BackupW(NN_Parms* NNParms, double**** w) {
	//-- Backup current W (into t5)
	for (int l = 0; l<(NNParms->LevelsCount-1); l++) {
		for (int fn = 0; fn<NNParms->NodesCount[l+1]; fn++) {
			for (int tn = 0; tn<NNParms->NodesCount[l]; tn++) {
				w[l][t5][fn][tn] = w[l][t0][fn][tn];
			}
		}
	}
}
void RestoreW(NN_Parms* NNParms, double**** w) {
	//-- Restore W
	for (int l = 0; l<(NNParms->LevelsCount-1); l++) {
		for (int fn = 0; fn<NNParms->NodesCount[l+1]; fn++) {
			for (int tn = 0; tn<NNParms->NodesCount[l]; tn++) {
				w[l][t0][fn][tn] = w[l][t5][fn][tn];
			}
		}
	}
}

void Ecalc(NN_Parms* NNParms, NN_Mem* NN, double* iW, double* oE) {
	BackupNeurons(NNParms, NN);
	BackupWeights(NNParms, NN);

	//-- put iW into W
	VCopy(NNParms->WeightsCountTotal, iW, NN->scgd->LVV_W[t0]);

	//-- calc E, by running FeedForward
	FF(NNParms, NN, TRAINING);

	//-- put e[t0] into output
	VCopy(NNParms->NodesCount[NNParms->LevelsCount-1], NN->e[t0], oE);

	//RestoreNeurons(NNParms, NN);
	RestoreWeights(NNParms, NN);

}
void Ecalc(NN_Parms* NNParms, NN_Mem* NN, double** iW, double* oE) {

	BackupNeurons(NNParms, NN);
	BackupWeights(NNParms, NN);

	//-- put iW into W
	VCopy(NNParms->WeightsCountTotal, iW, NN->scgd->LVV_W[t0]);

	//-- calc E, by running FeedForward
	FF(NNParms, NN, TRAINING);

	//-- put e[t0] into output
	VCopy(NNParms->NodesCount[NNParms->LevelsCount-1], NN->e[t0], oE);

	//RestoreNeurons(NNParms, NN);
	RestoreWeights(NNParms, NN);

}
void dEcalc(NN_Parms* NNParms, NN_Mem* NN, double* iW, double* odE) {

	BackupNeurons(NNParms, NN);
	BackupWeights(NNParms, NN);

	//-- put iW into W
	VCopy(NNParms->WeightsCountTotal, iW, NN->scgd->LVV_W[t0]);

	//-- calc E, by running FeedForward
	FF(NNParms, NN, TRAINING);

	//-- calc dJdW
	dJdWcalc(NNParms, NN);

	//-- put dJdW into output
	VCopy(NNParms->WeightsCountTotal, NN->scgd->LVV_W[t0], odE);

	RestoreNeurons(NNParms, NN);
	RestoreWeights(NNParms, NN);

}
void dEcalc(NN_Parms* NNParms, NN_Mem* NN, double** iW, double* odE) {

	BackupNeurons(NNParms, NN);
	BackupWeights(NNParms, NN);

	//-- put iW into W
	VCopy(NNParms->WeightsCountTotal, iW, NN->scgd->LVV_W[t0]);

	//-- calc E, by running FeedForward
	FF(NNParms, NN, TRAINING);

	//-- calc dJdW
	dJdWcalc(NNParms, NN);

	//-- put dJdW into output
	VCopy(NNParms->WeightsCountTotal, NN->scgd->LVV_W[t0], odE);

	RestoreNeurons(NNParms, NN);
	RestoreWeights(NNParms, NN);

}
int OLD_BP_scgd(int pid, int tid, int pEpoch, tDebugInfo* DebugParms, NN_Parms* NNParms, tCoreLog* NNLogs, NN_MxData* Mx) {
	
	double epsilon = NNParms->TargetMSE / NNParms->OutputCount;

	//-- some abbreviations
	int wl = NNParms->WeightsCountTotal;
	int el = NNParms->NodesCount[NNParms->LevelsCount-1];
	int nl = NNParms->NodesCountTotal;
	//--
	double** W = Mx->NN.scgd->LVV_W[t0];
	double** dW = Mx->NN.scgd->LVV_dW[t0];
	double** dE = Mx->NN.scgd->LVV_dJdW[t0];
	double* newW = Mx->NN.scgd->newW;
	//--
	double* p = Mx->NN.scgd->p;
	double* r = Mx->NN.scgd->r;
	double* s = Mx->NN.scgd->s;
	double sigma;
	double* E0 = Mx->NN.scgd->E0;
	double* E1 = Mx->NN.scgd->E1;
	double* E01 = Mx->NN.scgd->E;
	double* dE0 = Mx->NN.scgd->dE0;
	double* dE1 = Mx->NN.scgd->dE1;
	double* dE10 = Mx->NN.scgd->dE;
	double* SdW = Mx->NN.scgd->dW;
	double* sigmap = Mx->NN.scgd->sigmap;
	double delta;
	double lambda, lambdau;
	double* lambdap = Mx->NN.scgd->lp;
	double pnorm, pnorm2, rnorm, rnorm2, dWnorm;
	double mu, alpha;
	double comp;
	double* alphap = Mx->NN.scgd->alphap;
	double* prev_r = Mx->NN.scgd->prev_r;
	double beta = 0;
	double* bp = Mx->NN.scgd->bp;

	sigma = 1e-4;
	lambda = 1e-6; lambdau = 0;
	bool success = true;

	BackupW(NNParms, Mx->NN.W);

	//-- 0. Calc dJdW
	dJdWcalc(NNParms, &Mx->NN);

	//-- 1. Choose initial vector w ; p=r=-E'(w)
	VCopy(wl, dE, p); VbyS(wl, p, -1, p);
	VCopy(wl, p, r);

	//-- zero SdW
	VInit(wl, SdW, 0);

	int k = 0;
	do {
		pnorm = Vnorm(wl, p); pnorm2 = pnorm*pnorm;

		//-- 2.
		if (success) {
			sigma = sigma/pnorm;
			VbyS(wl, p, sigma, sigmap);
			VplusV(wl, sigmap, W, newW);
			dEcalc(NNParms, &Mx->NN, W, dE0);
			dEcalc(NNParms, &Mx->NN, newW, dE1);
			VminusV(wl, dE1, dE0, dE10);
			VdivS(wl, dE10, sigma, s);
			delta = VdotV(wl, p, s);
		}

		//-- 3.
		VbyS(wl, p, (lambda-lambdau), lambdap);
		VplusV(wl, s, lambdap, s);
		delta += (lambda-lambdau)*pnorm2;

		//-- 4.
		if (delta<=0) {
			VbyS(wl, p, lambda-2*delta/pnorm2, lambdap);
			VplusV(wl, s, lambdap, s);
			lambdau = 2*(lambda-delta/pnorm2);
			delta = -delta+lambda*pnorm2;
			lambda = lambdau;
		}

		//-- 5.
		mu = VdotV(wl, p, r);
		alpha = mu/delta;

		//-- 6.
		VbyS(wl, p, alpha, alphap);
		VplusV(wl, W, alphap, newW);
		Ecalc(NNParms, &Mx->NN, W, E0);
		Ecalc(NNParms, &Mx->NN, newW, E1);
		//-- calculating norm of the difference, instead of dthe difference of the two norms
		VminusV(el, E0, E1, E01);
		comp = 2*delta*Vnorm(el, E01)/(mu*mu);

		//-- 7.
		if (comp>=0) {
			//==============================
			VplusV(wl, W, alphap, W); 
			VplusV(wl, SdW, alphap, SdW);
			//==============================
			VCopy(wl, r, prev_r);
			FF(NNParms, &Mx->NN, TRAINING);
			dEcalc(NNParms, &Mx->NN, W, r); VbyS(wl, r, -1, r);
			lambdau = 0;
			success = true;
			//-- 7.a.
			if (((k+1) % nl) == 0) {
				VCopy(wl, r, p);
			} else {
				beta = (pow(Vnorm(wl, r), 2)-VdotV(wl, r, prev_r))/mu;
				VbyS(wl, p, beta, bp);
				VplusV(wl, r, bp, p);
			}
			//-- 7.b.
			if (comp>=0.75) lambda /= 2;
		} else {
			lambdau = lambda;
			success = false;
		}
		
		rnorm = Vnorm(wl, r); rnorm2 = rnorm*rnorm;
		dWnorm = Vnorm(wl, SdW);

		//-- 8.
		if (comp<0.25) lambda *= 4;

		//-- save logs
		if (isnan(delta) || pnorm==0) {
			int kaz = 0;
		}
		if (DebugParms->SaveInternals>0) SaveCoreData_SCGD(NNLogs, pid, tid, pEpoch, Mx->sampleid, Mx->BPCount, k, Mx->SCGD_progK, delta, mu, alpha, beta, lambda, lambdau, pnorm, rnorm, Mx->NN.norm_e[TRAINING][t0], dWnorm, comp);

		k++; Mx->SCGD_progK++;
	} while ((rnorm > epsilon) && (k<NNParms->SCGDmaxK));

	VCopy(wl, SdW, dW);

	RestoreW(NNParms, Mx->NN.W);

	return(1);	//-- so we don't update BdW and W in NNTrain()
}


//===================================================================================================================================================================
void Backup_Neurons(NN_Parms* NN, NN_MxData* Mx, int timebin) {

	for (int l = 0; l<NN->LevelsCount; l++) {
		VCopy(NN->NodesCount[l], Mx->NN.a[l][t0], Mx->NN.a[l][timebin]);
		VCopy(NN->NodesCount[l], Mx->NN.F[l][t0], Mx->NN.F[l][timebin]);
		VCopy(NN->NodesCount[l], Mx->NN.dF[l][t0], Mx->NN.dF[l][timebin]);
		VCopy(NN->NodesCount[l], Mx->NN.edF[l][t0], Mx->NN.edF[l][timebin]);
		VCopy(NN->NodesCount[l], Mx->NN.c[l][t0], Mx->NN.c[l][timebin]);
	}

	for (int i = 0; i<2; i++) {
		VCopy(NN->NodesCount[NN->LevelsCount-1], Mx->NN.e[i][t0], Mx->NN.e[i][timebin]);
		VCopy(NN->NodesCount[NN->LevelsCount-1], Mx->NN.u[i][t0], Mx->NN.u[i][timebin]);
		Mx->NN.norm_e[i][timebin] = Mx->NN.norm_e[i][t0];
	}
}
void Restore_Neurons(NN_Parms* NN, NN_MxData* Mx, int timebin) {

	for (int l = 0; l<NN->LevelsCount; l++) {
		VCopy(NN->NodesCount[l], Mx->NN.a[l][timebin], Mx->NN.a[l][t0]);
		VCopy(NN->NodesCount[l], Mx->NN.F[l][timebin], Mx->NN.F[l][t0]);
		VCopy(NN->NodesCount[l], Mx->NN.dF[l][timebin], Mx->NN.dF[l][t0]);
		VCopy(NN->NodesCount[l], Mx->NN.edF[l][timebin], Mx->NN.edF[l][t0]);
		VCopy(NN->NodesCount[l], Mx->NN.c[l][timebin], Mx->NN.c[l][t0]);
	}

	for (int i = 0; i<2; i++) {
		VCopy(NN->NodesCount[NN->LevelsCount-1], Mx->NN.e[i][timebin], Mx->NN.e[i][t0]);
		VCopy(NN->NodesCount[NN->LevelsCount-1], Mx->NN.u[i][timebin], Mx->NN.u[i][t0]);
		Mx->NN.norm_e[i][t0] = Mx->NN.norm_e[i][timebin];
	}
}
void Backup_Weights(NN_Parms* NN, NN_MxData* Mx, int timebin) {
	for (int l = 0; l < (NN->LevelsCount - 1); l++) {
		MCopy(NN->NodesCount[l+1], NN->NodesCount[l], Mx->NN.W[l][t0], Mx->NN.W[l][timebin]);
		MCopy(NN->NodesCount[l+1], NN->NodesCount[l], Mx->NN.dW[l][t0], Mx->NN.dW[l][timebin]);
		MCopy(NN->NodesCount[l+1], NN->NodesCount[l], Mx->NN.dJdW[l][t0], Mx->NN.dJdW[l][timebin]);
	}
}
void Restore_Weights(NN_Parms* NN, NN_MxData* Mx, int timebin, bool doW = true, bool dodW = true, bool dodJdW = true) {
	for (int l = 0; l < (NN->LevelsCount - 1); l++) {
		if (doW)    MCopy(NN->NodesCount[l+1], NN->NodesCount[l], Mx->NN.W[l][timebin], Mx->NN.W[l][t0]);
		if (dodW)   MCopy(NN->NodesCount[l+1], NN->NodesCount[l], Mx->NN.dW[l][timebin], Mx->NN.dW[l][t0]);
		if (dodJdW) MCopy(NN->NodesCount[l+1], NN->NodesCount[l], Mx->NN.dJdW[l][timebin], Mx->NN.dJdW[l][t0]);
	}
}
void Calc_dJdW(NN_Parms* NN, NN_MxData* Mx, bool doFF, bool doCalcH) {
	int l;

	if (doFF) FF(NN, &Mx->NN, TRAINING);

	for (l = NN->LevelsCount - 1; l > 0; l--) {

		if (l==(NN->LevelsCount-1)) {
			//-- top level only
			VbyV2V(NN->NodesCount[l], Mx->NN.e[TRAINING][t0], Mx->NN.dF[l][t0], Mx->NN.edF[l][t0]);									// edF(l) = e * F'(l)
		} else {
			//-- lower levels
			MbyV(NN->NodesCount[l+1], NN->NodesCount[l], Mx->NN.W[l][t0], true, Mx->NN.edF[l+1][t0], Mx->NN.edF[l][t0]);	// edF(l) = edF(l+1) * WT(l+1)
			VbyV2V(NN->NodesCount[l], Mx->NN.edF[l][t0], Mx->NN.dF[l][t0], Mx->NN.edF[l][t0]);								// edF(l) = edF(l)   * F'(l)
		}
		//-- common
		VbyV2M(NN->NodesCount[l], Mx->NN.edF[l][t0], NN->NodesCount[l-1], Mx->NN.F[l-1][t0], false, Mx->NN.dJdW[l-1][t0]);	// dJdW(l) = edF(l) * F(l-1)
	}

	if (doCalcH) Calc_H(NN, Mx);
}
void dEdW_at_w_LVV(NN_Parms* NN, NN_MxData* Mx, double** LVV_W, double* w_new, double* odEdW_at_w) {

	Backup_Weights(NN, Mx, t5);
	Backup_Neurons(NN, Mx, t5);

	//-- 1. put w_new into M
	VCopy(NN->WeightsCountTotal, w_new, LVV_W);
	//-- 2. calc dE/dW whole matrix (doFF before)
	Calc_dJdW(NN, Mx, true, false);
	//-- 3. return vector is one row of dE/dW corresponding to w_idx
	VCopy(NN->WeightsCountTotal, Mx->NN.scgd->LVV_dJdW[t0], odEdW_at_w);

	Restore_Neurons(NN, Mx, t5);
	Restore_Weights(NN, Mx, t5);

}
double E_at_w_LVV(NN_Parms* NN, NN_MxData* Mx, double** LVV_W, double* w_new) {
	double ret;

	Backup_Neurons(NN, Mx, t4);
	Backup_Weights(NN, Mx, t4);

	//-- 2. put w_new into LVV_W
	VCopy(NN->WeightsCountTotal, w_new, LVV_W);
	//-- 3. recalc Error
	FF(NN, &Mx->NN, TRAINING);
	//-- 5. return value is Mx->norm_e after FF
	ret = Mx->NN.norm_e[TRAINING][t0];

	Restore_Neurons(NN, Mx, t4);
	Restore_Weights(NN, Mx, t4);

	return ret;
}
int BP_scgd(int pid, int tid, int pEpoch, tDebugInfo* DebugParms, NN_Parms* NN, tCoreLog* NNLogs, NN_MxData* Mx) {

	int k;

	double sigma, delta, mu, alpha, beta = 0, b1, b2;
	double lambda, lambdau;
	double pnorm, pnorm2;
	double e_old, e_new, comp;
	bool success;
	double epsilon = NN->TargetMSE / NN->OutputCount;

	Calc_dJdW(NN, Mx, false, false);

	//Backup_Neurons(NN, Mx, t3);
	Backup_Weights(NN, Mx, t3);

	//-- 1. Choose initial vector w ; p=r=-E'(w)
	VCopy(NN->WeightsCountTotal, Mx->NN.scgd->LVV_dJdW[t0], Mx->NN.scgd->p); VbyS(NN->WeightsCountTotal, Mx->NN.scgd->p, -1, Mx->NN.scgd->p);
	VCopy(NN->WeightsCountTotal, Mx->NN.scgd->p, Mx->NN.scgd->r);
	//-- 1.1 Zero TotdW
	VInit(NN->WeightsCountTotal, Mx->NN.scgd->TotdW, 0);

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
			VCopy(NN->WeightsCountTotal, Mx->NN.scgd->LVV_dJdW[t0], Mx->NN.scgd->dE0);
			//-- get dE1 (dJdW at W+sigma*p)
			VbyS(NN->WeightsCountTotal, Mx->NN.scgd->p, sigma, Mx->NN.scgd->sigmap);
			VplusV(NN->WeightsCountTotal, Mx->NN.scgd->LVV_W[t0], Mx->NN.scgd->sigmap, Mx->NN.scgd->newW);
			//=================================
			dEdW_at_w_LVV(NN, Mx, Mx->NN.scgd->LVV_W[t0], Mx->NN.scgd->newW, Mx->NN.scgd->dE1);
			//=================================
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
		//--- 6.2 E(w) is current norm_e
		e_old = Mx->NN.norm_e[TRAINING][t0];
		//--- 6.3 E(w+dw) ir calculated by E_at_w()
		//=================================
		e_new = E_at_w_LVV(NN, Mx, Mx->NN.scgd->LVV_W[t0], Mx->NN.scgd->newW);
		//=================================
		//--- 6.4 comp=2*delta*(e_old-e_new)/mu^2
		comp = 2 * delta*(e_old - e_new) / pow(mu, 2);

		if (comp >= 0) {
			//-- 7. Update weight vector

			//-- dW = alpha * p
			//VbyS(NN->WeightsCountTotal, Mx->NN.scgd->p, alpha, Mx->NN.scgd->dW);
			//-- W = W + dW
			VplusV(NN->WeightsCountTotal, Mx->NN.scgd->LVV_W[t0], Mx->NN.scgd->dW, Mx->NN.scgd->LVV_W[t0]);
			//===========================================================================================================
			//-- TotdW = TotdW + dW
			VplusV(NN->WeightsCountTotal, Mx->NN.scgd->TotdW, Mx->NN.scgd->dW, Mx->NN.scgd->TotdW);
			//-- 7.1 recalc  dJdW
			//===========================================================================================================
			Calc_dJdW(NN, Mx, true, false);
			//===========================================================================================================
			//-- save r, and calc new r
			VCopy(NN->WeightsCountTotal, Mx->NN.scgd->r, Mx->NN.scgd->prev_r);
			VCopy(NN->WeightsCountTotal, Mx->NN.scgd->LVV_dJdW[t0], Mx->NN.scgd->r); VbyS(NN->WeightsCountTotal, Mx->NN.scgd->r, -1, Mx->NN.scgd->r);

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
		if (DebugParms->SaveInternals>0) SaveCoreData_SCGD(NNLogs, pid, tid, pEpoch, Mx->sampleid, Mx->BPCount, k, Mx->SCGD_progK, delta, mu, alpha, beta, lambda, lambdau, pnorm, Mx->NN.scgd->rnorm, Mx->NN.norm_e[TRAINING][t0], Vnorm(NN->WeightsCountTotal, Mx->NN.scgd->dW), comp);

		k++; Mx->SCGD_progK++;
	} while ((Mx->NN.scgd->rnorm>epsilon) && (k<NN->SCGDmaxK));

	//-- save the total dW into Mx->dW[l][t0]
	VCopy(NN->WeightsCountTotal, Mx->NN.scgd->TotdW, Mx->NN.scgd->LVV_dW[t0]);

	//-- 0. Before exiting, Restore original neurons and weights
	Restore_Weights(NN, Mx, t3, true, false, false);
	//Restore_Neurons(NN, Mx, t3);

	return(0);
}
//===================================================================================================================================================================


int BP_QuickProp(int pid, int tid, int pEpoch, tDebugInfo* DebugParms, NN_Parms* pNNParms, NN_MxData* Mx) {
	//-- as per QuickProp2.pdf, 2.6.3	
	int l, j, i;

	//-- save dJdW[t0]->dJdW[t1]
	for (l = 0; l<(pNNParms->LevelsCount-1); l++) {
		for (j = 0; j < pNNParms->NodesCount[l+1]; j++) {
			for (i = 0; i < pNNParms->NodesCount[l]; i++) {
				Mx->NN.dJdW[l][t1][j][i] = Mx->NN.dJdW[l][t0][j][i];
			}
		}
	}

	dJdWcalc(pNNParms, &Mx->NN);

	for (l = 0; l<(pNNParms->LevelsCount-1); l++) {
		for (j = 0; j < pNNParms->NodesCount[l+1]; j++) {
			for (i = 0; i < pNNParms->NodesCount[l]; i++) {

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

	dJdWcalc(NN, &Mx->NN);

	//-- calc dW
	for (int l = 0; l<(NN->LevelsCount-1); l++) {
		for (int j = 0; j < NN->NodesCount[l+1]; j++) {
			for (int i = 0; i < NN->NodesCount[l]; i++) {
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

	dJdWcalc(pNNParms, &Mx->NN);

	for (int l = 0; l<(pNNParms->LevelsCount-1); l++) {
		for (int j = 0; j < pNNParms->NodesCount[l+1]; j++) {
			for (int i = 0; i < pNNParms->NodesCount[l]; i++) {

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

void NNInit(NN_Parms* NN, NN_MxData* Mx, bool loadW, tCoreLog* NNLogs) {
	int i, k, l, x, y;

	for (int t = 0; t<TimeSteps; t++) {
		//-- Neurons
		for (l = 0; l < NN->LevelsCount; l++) {
			for (i = 0; i < NN->NodesCount[l]; i++) {
				Mx->NN.F[l][t][i] = 0;
				Mx->NN.dF[l][t][i] = 0;
				Mx->NN.c[l][t][i] = 1;
			}
		}
		//-- overwrite bias neurons. these should always have F=1
		for (l = 0; l < (NN->LevelsCount-1); l++) {
			Mx->NN.F[l][t][0] = 1;
		}

		//-- Weights
		k = 0;
		//FILE* fw = fopen("c:/temp/W.init", "r");
		//float w, dw;
		for (l = 0; l < (NN->LevelsCount-1); l++) {
			for (i = 0; i < (NN->NodesCount[l+1] * NN->NodesCount[l]); i++) {
				y = (int)(i / NN->NodesCount[l]);
				x = i%NN->NodesCount[l];

				if (loadW) {
					//-- load weights as we do in Run_NN():
					Mx->NN.W[l][t][y][x] = NNLogs->NNFinalW[l][y][x].Weight;
					Mx->NN.dW[l][t][y][x] = NNLogs->NNFinalW[l][y][x].dW;
					Mx->NN.dJdW[l][t][y][x] = NNLogs->NNFinalW[l][y][x].dJdW;
				} else {
					Mx->NN.W[l][t][y][x] = MyRndDbl(-1 / sqrt((double)NN->NodesCount[l]), 1 / sqrt((double)NN->NodesCount[l]));
					Mx->NN.dW[l][t][y][x] = 0;
					Mx->NN.dJdW[l][t][y][x] = 0;
				}

				//fprintf(fw, "%2.10f %2.10f\n", Mx->NN.W[l][t][y][x], Mx->NN.dW[l][t][y][x]);
				//fscanf(fw, "%f %f\n", &w, &dw); Mx->NN.W[l][t][y][x] = w; Mx->NN.dW[l][t][y][x]=dw;

				Mx->NN.scgd->LVV_W[t][k] = &Mx->NN.W[l][t][y][x];
				Mx->NN.scgd->LVV_dW[t][k] = &Mx->NN.dW[l][t][y][x];
				Mx->NN.scgd->LVV_dJdW[t][k] = &Mx->NN.dJdW[l][t][y][x];
				k++;
			}
		}
	}
	//fclose(fw);
	Mx->BPCount = 0; Mx->SCGD_progK = 0;

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
		break;
	}
	Mx->BPCount++;

	return ret;
}

void Update_W(NN_Parms* NN, NN_MxData* Mx, double**** baseW, double**** addedW) {
	//-- baseW = baseW + addedW
	for (int l = 0; l < (NN->LevelsCount - 1); l++) {
		MplusM(NN->NodesCount[l+1], NN->NodesCount[l], baseW[l][t0], addedW[l][t0], baseW[l][t0]);
	}
}

void NNTrain_ORIG(tDebugInfo* pDebugParms, NN_Parms* NNParms, tCoreLog* NNLogs, NN_MxData* Mx, int pSampleCount, double** pSampleData, double** pTargetData, double** pSampleDataV, double** pTargetDataV) {
	int s, si;
	int epoch;

	double TSE_T, TSE_V;
	int pid = GetCurrentProcessId();
	int tid = GetCurrentThreadId();
	int CalcdWType;

	//-- set initial network MSEs
	Mx->NN.mse[t0][TRAINING] = 0;
	Mx->NN.mse[t0][VALIDATION] = 0;

	//-- Samples shuffle
	int* sl = (int*)malloc(pSampleCount*sizeof(int)); for (int i = 0; i<pSampleCount; i++) sl[i] = i;
	ShuffleArray(sl, pSampleCount);

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
			for (int l = 0; l < (NNParms->LevelsCount - 1); l++) MInit(NNParms->NodesCount[l + 1], NNParms->NodesCount[l], Mx->NN.BdW[l][t0], 0);

			for (int i = 0; i < BatchSize; i++) {
				Mx->sampleid = si;
				s = sl[si];

				//-- 1. present every sample in the batch, and sum up total error in tse				
				if (Mx->useValidation>0)	TSE_V += CalcNetworkError(NNParms, Mx, VALIDATION, pSampleDataV[s], pTargetDataV[s]);
				TSE_T += CalcNetworkError(NNParms, Mx, TRAINING, pSampleData[s], pTargetData[s]);

				//-- 1.2 Calc dW for every sample based on BP algorithm
				CalcdWType = Calc_dW(pid, tid, epoch, pDebugParms, NNParms, NNLogs, Mx);

				//-- 1.3 BdW = BdW + dW (only if BP_ALGO is not global, like SCGD)
				if (CalcdWType==0) Update_W(NNParms, Mx, Mx->NN.BdW, Mx->NN.dW);

				//-- next sample id
				si++;
			}

			//-- 2. Weight update after every batch: W = W + BdW			
			if (CalcdWType==0) Update_W(NNParms, Mx, Mx->NN.W, Mx->NN.BdW);

		}

		//-- 4. Calc MSE for epoch , and exit if less than TargetMSE
		Mx->NN.mse[t1][TRAINING] = Mx->NN.mse[t0][TRAINING];	// save previous MSE
		Mx->NN.mse[t0][TRAINING] = TSE_T / pSampleCount / NNParms->OutputCount;		// MSE = TSE / samplecount

		if (Mx->useValidation>0) {
			Mx->NN.mse[t0][VALIDATION] = TSE_V / pSampleCount / NNParms->OutputCount;	// MSE = TSE / samplecount
			if (NNParms->StopAtDivergence == 1 && Mx->NN.mse[t0][TRAINING] > Mx->NN.mse[t1][TRAINING]) break;
		}

		//-- display progress
		WaitForSingleObject(Mx->ScreenMutex, 10);
		gotoxy(0, Mx->ScreenPos); printf("\rProcess %6d, Thread %6d, Epoch %6d , Training MSE=%f , Validation MSE=%f", pid, tid, epoch, Mx->NN.mse[t0][TRAINING], Mx->NN.mse[t0][VALIDATION]);
		ReleaseMutex(Mx->ScreenMutex);

		SaveMSEData(NNLogs, pid, tid, epoch, Mx->NN.mse[t0][TRAINING], (Mx->useValidation>0) ? Mx->NN.mse[t0][VALIDATION] : 0);

		if (Mx->NN.mse[t0][TRAINING] < NNParms->TargetMSE) {
			epoch++;
			break;
		}
	}
	NNLogs->ActualEpochs = epoch;
	NNLogs->IntCnt = (NNParms->BP_Algo == BP_SCGD) ? Mx->SCGD_progK : epoch;

	LogWrite(pDebugParms, LOG_INFO, "NNTrain() CheckPoint 4 - Thread=%d ; Final MSE_T=%f ; Final MSE_V=%f\n", 2, tid, Mx->NN.mse[t0][TRAINING], Mx->NN.mse[t0][VALIDATION]);
}
void NNTrain(tDebugInfo* pDebugParms, NN_Parms* NNParms, tCoreLog* NNLogs, NN_MxData* Mx, int pSampleCount, double** pSampleData, double** pTargetData, double** pSampleDataV, double** pTargetDataV) {
	int s, si;
	int epoch;

	int pid = GetCurrentProcessId();
	int tid = GetCurrentThreadId();
	int CalcdWType;

	//-- set initial network MSEs
	Mx->NN.mse[t0][TRAINING] = 0;
	Mx->NN.mse[t0][VALIDATION] = 0;

	//-- Samples shuffle
	int* sl = (int*)malloc(pSampleCount*sizeof(int)); for (int i = 0; i<pSampleCount; i++) sl[i] = i;
	ShuffleArray(sl, pSampleCount);

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
		Mx->NN.gse[t0][TRAINING] = 0;
		Mx->NN.gse[t0][VALIDATION] = 0;

		for (int b = 0; b<BatchCount; b++) {

			//-- 0. for each batch, BdW=0
			for (int l = 0; l < (NNParms->LevelsCount - 1); l++) MInit(NNParms->NodesCount[l + 1], NNParms->NodesCount[l], Mx->NN.BdW[l][t0], 0);

			for (int i = 0; i < BatchSize; i++) {
				Mx->sampleid = si;
				s = sl[si];

				//-- 1. present every sample in the batch, and sum up total error in tse				
				if (Mx->useValidation>0)	Mx->NN.gse[t0][VALIDATION] += CalcNetworkError(NNParms, Mx, VALIDATION, pSampleDataV[s], pTargetDataV[s]);
											Mx->NN.gse[t0][TRAINING]   += CalcNetworkError(NNParms, Mx, TRAINING,   pSampleData[s],  pTargetData[s]);

				//-- 1.2 Calc dW for every sample based on BP algorithm
				CalcdWType = Calc_dW(pid, tid, epoch, pDebugParms, NNParms, NNLogs, Mx);

				//-- 1.3 BdW = BdW + dW (only if BP_ALGO is not global, like SCGD)
				if (CalcdWType==0) Update_W(NNParms, Mx, Mx->NN.BdW, Mx->NN.dW);

				//-- next sample id
				si++;
			}

			//-- 2. Weight update after every batch: W = W + BdW			
			if (CalcdWType==0) Update_W(NNParms, Mx, Mx->NN.W, Mx->NN.BdW);

		}

		//-- 4. Calc MSE for epoch , and exit if less than TargetMSE
		Mx->NN.mse[t1][TRAINING] = Mx->NN.mse[t0][TRAINING];	// save previous MSE
		Mx->NN.mse[t0][TRAINING] = Mx->NN.gse[t0][TRAINING] / pSampleCount / NNParms->OutputCount;		// MSE = TSE / samplecount

		if (Mx->useValidation>0) {
			Mx->NN.mse[t0][VALIDATION] = Mx->NN.gse[t0][VALIDATION] / pSampleCount / NNParms->OutputCount;	// MSE = TSE / samplecount
			if (NNParms->StopAtDivergence == 1 && Mx->NN.mse[t0][TRAINING] > Mx->NN.mse[t1][TRAINING]) break;
		}

		//-- display progress
		WaitForSingleObject(Mx->ScreenMutex, 10);
		gotoxy(0, Mx->ScreenPos); printf("\rProcess %6d, Thread %6d, Epoch %6d , Training MSE=%f , Validation MSE=%f", pid, tid, epoch, Mx->NN.mse[t0][TRAINING], Mx->NN.mse[t0][VALIDATION]);
		ReleaseMutex(Mx->ScreenMutex);

		SaveMSEData(NNLogs, pid, tid, epoch, Mx->NN.mse[t0][TRAINING], (Mx->useValidation>0) ? Mx->NN.mse[t0][VALIDATION] : 0);

		if (Mx->NN.mse[t0][TRAINING] < NNParms->TargetMSE) {
			epoch++;
			break;
		}
	}
	NNLogs->ActualEpochs = epoch;
	NNLogs->IntCnt = (NNParms->BP_Algo == BP_SCGD) ? Mx->SCGD_progK : epoch;

	LogWrite(pDebugParms, LOG_INFO, "NNTrain() CheckPoint 4 - Thread=%d ; Final MSE_T=%f ; Final MSE_V=%f\n", 2, tid, Mx->NN.mse[t0][TRAINING], Mx->NN.mse[t0][VALIDATION]);
}

NN_Mem Malloc_NNMem(NN_Parms* pNNParms) {
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
			ret.a[l][t] = (double*)malloc(pNNParms->NodesCount[l] * sizeof(double));
			ret.F[l][t] = (double*)malloc(pNNParms->NodesCount[l] * sizeof(double));
			ret.dF[l][t] = (double*)malloc(pNNParms->NodesCount[l] * sizeof(double));
			ret.edF[l][t] = (double*)malloc(pNNParms->NodesCount[l] * sizeof(double));
			ret.c[l][t] = (double*)malloc(pNNParms->NodesCount[l] * sizeof(double));
		}
	}
	//-- outer node only -> [TRAINING/VALIDATION][Time]
	ret.e = MallocArray<double>(2, TimeSteps, pNNParms->NodesCount[pNNParms->LevelsCount-1]);
	ret.u = MallocArray<double>(2, TimeSteps, pNNParms->NodesCount[pNNParms->LevelsCount-1]);
	ret.norm_e = MallocArray<double>(2, TimeSteps);
	ret.mse = MallocArray<double>(2, TimeSteps);
	ret.gse = MallocArray<double>(2, TimeSteps);

	//-- weight levels -> [Levels-1][Time]
	ret.W = (double****)malloc((pNNParms->LevelsCount - 1) * sizeof(double***));					// Core
	ret.dW = (double****)malloc((pNNParms->LevelsCount - 1) * sizeof(double***));				// Core
	ret.dJdW = (double****)malloc((pNNParms->LevelsCount - 1) * sizeof(double***));				// Core
	ret.BdW = (double****)malloc((pNNParms->LevelsCount - 1) * sizeof(double***));				// Core - Batch Training
	ret.Q_dJdW = (double****)malloc((pNNParms->LevelsCount - 1) * sizeof(double***));			// Qing
	for (l = 0; l < (pNNParms->LevelsCount - 1); l++) {
		ret.W[l] = (double***)malloc(TimeSteps * sizeof(double**));
		ret.dW[l] = (double***)malloc(TimeSteps * sizeof(double**));
		ret.dJdW[l] = (double***)malloc(TimeSteps * sizeof(double**));
		ret.BdW[l] = (double***)malloc(TimeSteps * sizeof(double**));
		ret.Q_dJdW[l] = (double***)malloc(TimeSteps * sizeof(double**));
		for (t = 0; t < TimeSteps; t++) {
			ret.W[l][t] = (double**)malloc(pNNParms->NodesCount[l + 1] * sizeof(double*));
			ret.dW[l][t] = (double**)malloc(pNNParms->NodesCount[l + 1] * sizeof(double*));
			ret.dJdW[l][t] = (double**)malloc(pNNParms->NodesCount[l + 1] * sizeof(double*));
			ret.BdW[l][t] = (double**)malloc(pNNParms->NodesCount[l + 1] * sizeof(double*));
			ret.Q_dJdW[l][t] = (double**)malloc(pNNParms->NodesCount[l + 1] * sizeof(double*));
			for (i = 0; i < pNNParms->NodesCount[l + 1]; i++) {
				ret.W[l][t][i] = (double*)malloc(pNNParms->NodesCount[l] * sizeof(double));
				ret.dW[l][t][i] = (double*)malloc(pNNParms->NodesCount[l] * sizeof(double));
				ret.dJdW[l][t][i] = (double*)malloc(pNNParms->NodesCount[l] * sizeof(double));
				ret.BdW[l][t][i] = (double*)malloc(pNNParms->NodesCount[l] * sizeof(double));
				ret.Q_dJdW[l][t][i] = (double*)malloc(pNNParms->NodesCount[l] * sizeof(double));
			}
		}
	}
	//-- temp matrices
	ret.tmpM0 = (double***)malloc(pNNParms->LevelsCount * sizeof(double**));
	ret.tmpM1 = (double***)malloc(pNNParms->LevelsCount * sizeof(double**));
	ret.tmpM2 = (double***)malloc(pNNParms->LevelsCount * sizeof(double**));
	ret.tmpM3 = (double***)malloc(pNNParms->LevelsCount * sizeof(double**));
	for (l = 0; l < pNNParms->LevelsCount; l++) {
		ret.tmpM0[l] = (double**)malloc(pNNParms->NodesCount[l] * sizeof(double*));
		ret.tmpM1[l] = (double**)malloc(pNNParms->NodesCount[l] * sizeof(double*));
		ret.tmpM2[l] = (double**)malloc(pNNParms->NodesCount[l] * sizeof(double*));
		for (int y = 0; y<pNNParms->NodesCount[l]; y++) {
			ret.tmpM0[l][y] = (double*)malloc(1 * sizeof(double));
			ret.tmpM1[l][y] = (double*)malloc(pNNParms->NodesCount[l] * sizeof(double));
			ret.tmpM2[l][y] = (double*)malloc(1 * sizeof(double));
		}
		ret.tmpM3[l] = (double**)malloc(1 * sizeof(double*)); ret.tmpM3[l][0] = (double*)malloc(pNNParms->NodesCount[l] * sizeof(double));
	}
	//-- Qing stuff
	ret.adzev = (double**)malloc((pNNParms->LevelsCount - 1) * sizeof(double*));		//-- [Level][Node]
	for (l = 0; l < (pNNParms->LevelsCount - 1); l++) ret.adzev[l] = (double*)malloc(pNNParms->NodesCount[l] * sizeof(double));

	ret.uW = (double**)malloc(1 * sizeof(double*));
	ret.uW[0] = (double*)malloc(pNNParms->NodesCount[1] * pNNParms->NodesCount[0] * sizeof(double));
	ret.Q_V1 = (double*)malloc(pNNParms->NodesCount[0] * sizeof(double));
	ret.ux = (double**)malloc(pNNParms->NodesCount[0] * sizeof(double*));
	ret.ux_inv = (double**)malloc(pNNParms->NodesCount[0] * sizeof(double*));
	for (i = 0; i<pNNParms->NodesCount[0]; i++) ret.ux[i] = (double*)malloc(pNNParms->NodesCount[0] * sizeof(double));
	for (i = 0; i<pNNParms->NodesCount[0]; i++) ret.ux_inv[i] = (double*)malloc(pNNParms->NodesCount[0] * sizeof(double));
	ret.dxdW10 = (double**)malloc(pNNParms->NodesCount[1] * pNNParms->NodesCount[0] * sizeof(double*));
	for (i = 0; i<(pNNParms->NodesCount[1] * pNNParms->NodesCount[0]); i++) ret.dxdW10[i] = (double*)malloc(pNNParms->NodesCount[0] * sizeof(double));
	ret.Q_ExtG = (double**)malloc(pNNParms->NodesCount[1] * sizeof(double*));
	for (i = 0; i<pNNParms->NodesCount[1]; i++) ret.Q_ExtG[i] = (double*)malloc(pNNParms->NodesCount[0] * sizeof(double));

	ret.Q_M1 = (double***)malloc(pNNParms->LevelsCount * sizeof(double**));
	ret.Q_M2 = (double***)malloc(pNNParms->LevelsCount * sizeof(double**));
	ret.Q_M3 = (double***)malloc(pNNParms->LevelsCount * sizeof(double**));
	ret.Q_M4 = (double***)malloc(pNNParms->LevelsCount * sizeof(double**));
	ret.Q_M5 = (double***)malloc(pNNParms->LevelsCount * sizeof(double**));
	ret.Q_M6 = (double***)malloc(pNNParms->LevelsCount * sizeof(double**));
	for (l = 0; l<pNNParms->LevelsCount; l++) {
		ret.Q_M1[l] = (double**)malloc(pNNParms->NodesCount[l] * sizeof(double*));
		ret.Q_M2[l] = (double**)malloc(pNNParms->NodesCount[l] * sizeof(double*));
		ret.Q_M3[l] = (double**)malloc(pNNParms->NodesCount[l] * sizeof(double*));
		ret.Q_M4[l] = (double**)malloc(pNNParms->NodesCount[l] * sizeof(double*));
		ret.Q_M5[l] = (double**)malloc(pNNParms->NodesCount[l] * sizeof(double*));
		ret.Q_M6[l] = (double**)malloc(pNNParms->NodesCount[l] * sizeof(double*));
		for (i = 0; i < pNNParms->NodesCount[l]; i++) {
			ret.Q_M1[l][i] = (double*)malloc(pNNParms->NodesCount[l] * sizeof(double));
			ret.Q_M2[l][i] = (double*)malloc(pNNParms->NodesCount[l] * sizeof(double));
			ret.Q_M3[l][i] = (double*)malloc(pNNParms->NodesCount[l] * sizeof(double));
			ret.Q_M4[l][i] = (double*)malloc(pNNParms->NodesCount[l] * sizeof(double));
			ret.Q_M5[l][i] = (double*)malloc(pNNParms->NodesCount[l] * sizeof(double));
			ret.Q_M6[l][i] = (double*)malloc(pNNParms->NodesCount[l] * sizeof(double));
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

	return ret;
}
void   Free_NNMem(NN_Parms* pNNParms, NN_Mem NN) {
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
	FreeArray(2, TimeSteps, pNNParms->OutputCount, NN.e);
	FreeArray(2, TimeSteps, pNNParms->OutputCount, NN.u);
	FreeArray(2, TimeSteps, NN.mse);
	FreeArray(2, TimeSteps, NN.gse);

	//-- weight levels -> [Levels-1][Time]
	for (l = 0; l < (pNNParms->LevelsCount - 1); l++) {
		for (t = 0; t < TimeSteps; t++) {
			for (i = 0; i < pNNParms->NodesCount[l + 1]; i++) {
				free(NN.W[l][t][i]);
				free(NN.dW[l][t][i]);
				free(NN.dJdW[l][t][i]);
				free(NN.BdW[l][t][i]);
				free(NN.Q_dJdW[l][t][i]);
			}
			free(NN.W[l][t]);
			free(NN.dW[l][t]);
			free(NN.dJdW[l][t]);
			free(NN.BdW[l][t]);
			free(NN.Q_dJdW[l][t]);
		}
		free(NN.W[l]);
		free(NN.dW[l]);
		free(NN.dJdW[l]);
		free(NN.BdW[l]);
		free(NN.Q_dJdW[l]);
	}
	free(NN.W);
	free(NN.dW);
	free(NN.dJdW);
	free(NN.BdW);
	free(NN.Q_dJdW);

	//-- temp matrices
	for (l = 0; l < (pNNParms->LevelsCount); l++) {
		for (i = 0; i < pNNParms->NodesCount[l]; i++) {
			free(NN.tmpM0[l][i]);
			free(NN.tmpM1[l][i]);
			free(NN.tmpM2[l][i]);
		}
		free(NN.tmpM3[l][0]);
		free(NN.tmpM0[l]);
		free(NN.tmpM1[l]);
		free(NN.tmpM2[l]);
		free(NN.tmpM3[l]);
	}
	free(NN.tmpM0);
	free(NN.tmpM1);
	free(NN.tmpM2);
	free(NN.tmpM3);

	//-- Qing stuff
	for (l = 0; l < (pNNParms->LevelsCount - 1); l++)	free(NN.adzev[l]);
	free(NN.adzev);
	free(NN.uW[0]); free(NN.uW);
	free(NN.Q_V1);
	for (i = 0; i<pNNParms->NodesCount[0]; i++) {
		free(NN.ux[i]);
		free(NN.ux_inv[i]);
	}
	free(NN.ux);
	free(NN.ux_inv);

	for (i = 0; i<(pNNParms->NodesCount[1] * pNNParms->NodesCount[0]); i++) free(NN.dxdW10[i]);
	free(NN.dxdW10);
	for (i = 0; i<pNNParms->NodesCount[1]; i++) free(NN.Q_ExtG[i]);
	free(NN.Q_ExtG);

	for (l = 0; l<pNNParms->LevelsCount; l++) {
		for (int n = 0; n<pNNParms->NodesCount[l]; n++) {
			free(NN.Q_M1[l][n]);
			free(NN.Q_M2[l][n]);
			free(NN.Q_M3[l][n]);
			free(NN.Q_M4[l][n]);
			free(NN.Q_M5[l][n]);
			free(NN.Q_M6[l][n]);
		}
		free(NN.Q_M1[l]);
		free(NN.Q_M2[l]);
		free(NN.Q_M3[l]);
		free(NN.Q_M4[l]);
		free(NN.Q_M5[l]);
		free(NN.Q_M6[l]);
	}
	free(NN.Q_M1);
	free(NN.Q_M2);
	free(NN.Q_M3);
	free(NN.Q_M4);
	free(NN.Q_M5);
	free(NN.Q_M6);

	//-- SCGD stuff
	for (t = 0; t < TimeSteps; t++) {
		free(NN.scgd->LVV_W[t]);
		free(NN.scgd->LVV_dW[t]);
		free(NN.scgd->LVV_dJdW[t]);
	}
	free(NN.scgd->LVV_W);
	free(NN.scgd->LVV_dW);
	free(NN.scgd->LVV_dJdW);
	//--
	free(NN.scgd->p);
	free(NN.scgd->r);
	free(NN.scgd->s);
	free(NN.scgd->dW);
	free(NN.scgd->TotdW);
	free(NN.scgd->newW);
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
}

__declspec(dllexport) void Run_NN(tDebugInfo* pDebugParms, NN_Parms* NNParms, tCoreLog* NNLogs, tDataShape* pInputData, int pid, int tid, int pSampleCount, double** pSample, double** pTarget) {
	int i, s, l, j;
	int vTSCount = 1, d = 0;
	double vActual;
	double* vPrediction = nullptr;

	//-- 0. mallocs
	NN_MxData MxData;
	MxData.NN = Malloc_NNMem(NNParms);
	double* tmpSample = (double*)malloc(NNParms->InputCount * sizeof(double));

	//-- 1. Load W*** from NNParms->NNFinalW[Level][FromN][ToN] 
	for (l = 0; l<NNParms->LevelsCount; l++) {
		for (j = 0; j<NNParms->NodesCount[l+1]; j++) {
			for (i = 0; i<NNParms->NodesCount[l]; i++) {
				MxData.NN.W[l][t0][j][i] = NNLogs->NNFinalW[l][j][i].Weight;
				MxData.NN.dW[l][t0][j][i] = NNLogs->NNFinalW[l][j][i].dW;
				MxData.NN.dJdW[l][t0][j][i] = NNLogs->NNFinalW[l][j][i].dJdW;
			}
		}
	}

	//-- 2. Reset Context Neurons
	if (NNParms->UseContext==1)	FeedBack(NNParms, &MxData.NN, true);
	//-- 2.1. Reset Bias Neurons
	for (l = 0; l<NNParms->LevelsCount; l++) {
		for (i = 0; i<NNParms->NodesCount[l]; i++) {
			MxData.NN.F[l][t0][0] = 1;
		}
	}

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
		FF(NNParms, &MxData.NN, TRAINING);							//-- Feed-Forward the network;
		vPrediction = MxData.NN.F[NNParms->LevelsCount-1][t0];	//-- Predicted  Data. All steps
		vActual = pTarget[s][0];
		//-- Write RunLog structure
		SaveRunData(NNLogs, pid, tid, NNParms->InputCount + s, vActual, vPrediction);
	}

	//-- 4.2 Out-of-Sample . This always uses predicted value from previous step as actual value. if we do have actual future data, this is updated in CalcForecastFromEngineOutput()
	for (s = 0; s < pInputData->PredictionLen; s++) {
		ShiftArray(SHIFT_BACKWARD, NNParms->InputCount, tmpSample, vActual);
		//--
		for (i = 0; i < NNParms->InputCount; i++) MxData.NN.F[0][t0][i] = tmpSample[i];	//-- Present each sample to input neurons
		FF(NNParms, &MxData.NN, TRAINING);												//-- Feed-Forward the network;
		vPrediction = MxData.NN.F[NNParms->LevelsCount-1][t0];							//-- Predicted  Data. All steps

		SaveRunData(NNLogs, pid, tid, (s + pSampleCount+NNParms->InputCount), NULL, vPrediction);
		vActual = vPrediction[0];
	}

	//-- 5. frees()
	free(tmpSample);
	Free_NNMem(NNParms, MxData.NN);

}

__declspec(dllexport) int Train_NN(int pCorePos, int pTotCores, HANDLE pScreenMutex, tDebugInfo* pDebugParms, NN_Parms* pNNParms, tCoreLog* pNNLogs, bool loadW, int pSampleCount, double** pSampleData, double** pTargetData, int useValidation, double** pSampleDataV, double** pTargetDataV) {
	int pid = GetCurrentProcessId();
	int tid = GetCurrentThreadId();

	// srand()
	srand((unsigned int)time(NULL));

	// mallocs
	NN_MxData MxData;
	MxData.NN = Malloc_NNMem(pNNParms);
	MxData.ScreenPos = pCorePos+1;
	MxData.ScreenMutex = pScreenMutex;
	MxData.useValidation = useValidation;

	//-- Init Weights and Neurons
	NNInit(pNNParms, &MxData, loadW, pNNLogs);
	//-- Save Initial Weights
	SaveInitW(pNNParms, &MxData.NN, pNNLogs, pid, tid);
	//-- Train 
	NNTrain(pDebugParms, pNNParms, pNNLogs, &MxData, pSampleCount, pSampleData, pTargetData, pSampleDataV, pTargetDataV);
	//-- Save Final Weights
	SaveFinalW(pNNParms, &MxData.NN, pNNLogs, pid, tid);

	//-- free()s
	Free_NNMem(pNNParms, MxData.NN);


	return 0;
}

//#include <vld.h>

#include <MyNN.h>

__declspec(dllexport) void __stdcall setNNTopology(NN_Parms* NN) {
	int i;
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
	for (int nl = 0; nl<(NN->LevelsCount - 2); nl++) {
		NN->NodesCount[nl + 1] = (int)floor(NN->NodesCount[nl] * NN->LevelRatio[nl]);
		NN->NodesCountTotal += NN->NodesCount[nl + 1];
	}
	//-- calc totalweightscount
	NN->WeightsCountTotal = 0;
	for (int nl = 0; nl<(NN->LevelsCount - 1); nl++) {
		for (int nn1 = 0; nn1<NN->NodesCount[nl + 1]; nn1++) {
			for (int nn0 = 0; nn0<NN->NodesCount[nl]; nn0++) {
				NN->WeightsCountTotal++;
			}
		}
	}

	FreeArray(MAX_LEVELS,100, DescList);
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
	if(mallocIntP) coreLog->IntP = MallocArray<tLogInt>(tscnt);
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
	if(freeIntP) free(coreLog->IntP);
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
				if (l==0) NNLog->NNFinalW[l][j][i].CtxValue = (i >= NNParms->InputCount) ? NN->F[0][t0][i] : 0;
			}
		}
	}
}
void SaveInitW(NN_Parms* NNParms, tCoreLog* NNLog, DWORD pid, DWORD tid, double**** W, double** F0) {
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
				NNLog->NNInitW[l][j][i].Weight = W[l][t0][j][i];
				//-- Context neurons
				if (l==0) NNLog->NNInitW[l][j][i].CtxValue = (i >= NNParms->InputCount) ? F0[t0][i] : 0;
			}
		}
	}
}

void SaveCoreData_SCGD(tCoreLog* NNLog, int pid, int tid, int epoch, int BPid, int k, int timeStep, double delta, double mu, double alpha, double beta, double lambda, double lambdau, double rnorm, double enorm, double comp){
	NNLog->IntP[timeStep].ProcessId = pid;
	NNLog->IntP[timeStep].ThreadId = tid;
	NNLog->IntP[timeStep].Epoch = epoch;
	NNLog->IntP[timeStep].BPid = BPid;
	NNLog->IntP[timeStep].K=k;
	NNLog->IntP[timeStep].delta=delta;
	NNLog->IntP[timeStep].mu=mu;
	NNLog->IntP[timeStep].alpha=alpha;
	NNLog->IntP[timeStep].beta=beta;
	NNLog->IntP[timeStep].lambda=lambda;
	NNLog->IntP[timeStep].lambdau=lambdau;
	NNLog->IntP[timeStep].rnorm=rnorm;
	NNLog->IntP[timeStep].enorm=enorm;
	NNLog->IntP[timeStep].comp= comp;
}

// saving of internal parameters
/*
void SaveIntWFa(NN_Parms* NN, int pid, int tid, int DatasetId, int NetId, int Step, double*** a, double*** F, double**** W){
	int i, j, l;

	//-- First, Neurons
	for (l = 0; l < NN->LevelsCount; l++){
		for (i = 0; i < NN->NodesCount[l]; i++){
			NN->Inta[DatasetId][l][Step][i] = a[l][t0][i];
			NN->IntF[DatasetId][l][Step][i] = F[l][t0][i];
		}
	}

	//-- Then, Weights
	for (l = 0; l < (NN->LevelsCount - 1); l++){
		for (j = 0; j < NN->NodesCount[l + 1]; j++){
			for (i = 0; i < NN->NodesCount[l]; i++){
				NN->IntW[DatasetId][l][Step][j][i] = W[l][t0][j][i];
			}
		}
	}
}

void SaveIntParms(NN_Parms* NN, int pid, int tid, int DatasetId, int NetId, int Step, int sigma10, double ro10, double D10W, double adzev10, int hcp10, int sigma21, double ro21, double adzev21N, double norm_e){
	//-- For now, all params are assigned Layer 0
	NN->IntP[DatasetId][0][Step].ProcessId = pid;
	NN->IntP[DatasetId][0][Step].ThreadId = tid;
	NN->IntP[DatasetId][0][Step].Step=Step;
	NN->IntP[DatasetId][0][Step].sigma10 = sigma10;
	NN->IntP[DatasetId][0][Step].ro10 = ro10;
	NN->IntP[DatasetId][0][Step].D10W = D10W;
	NN->IntP[DatasetId][0][Step].adzev10 = adzev10;
	NN->IntP[DatasetId][0][Step].hcp10 = hcp10;
	NN->IntP[DatasetId][0][Step].sigma21 = sigma21;
	NN->IntP[DatasetId][0][Step].ro21 = ro21;
	NN->IntP[DatasetId][0][Step].adzev21N = adzev21N;
	NN->IntP[DatasetId][0][Step].norm_e = norm_e;
}
*/

void SavePrevNeurons(NN_Parms* NNParms, NN_MxData* Mx) {
	int i, l;

	for (l = 0; l<NNParms->LevelsCount; l++) {
		for (i = 0; i < NNParms->NodesCount[l]; i++) {
			//-- first, copy t1 into t2
			Mx->NN.a[l][t2][i] = Mx->NN.a[l][t1][i];
			Mx->NN.F[l][t2][i] = Mx->NN.F[l][t1][i];
			Mx->NN.dF[l][t2][i] = Mx->NN.dF[l][t1][i];
			Mx->NN.edF[l][t2][i] = Mx->NN.edF[l][t1][i];
			Mx->NN.c[l][t2][i] = Mx->NN.c[l][t1][i];
			//-- then, copy t0 inti t1
			Mx->NN.a[l][t1][i] = Mx->NN.a[l][t0][i];
			Mx->NN.F[l][t1][i] = Mx->NN.F[l][t0][i];
			Mx->NN.dF[l][t1][i] = Mx->NN.dF[l][t0][i];
			Mx->NN.edF[l][t1][i] = Mx->NN.edF[l][t0][i];
			Mx->NN.c[l][t1][i] = Mx->NN.c[l][t0][i];

			if (l==NNParms->LevelsCount-1) {
				//-- first, copy t1 into t2
				Mx->NN.e[t2][i] = Mx->NN.e[t1][i];
				Mx->NN.u[t2][i] = Mx->NN.u[t1][i];
				Mx->NN.Ve[t2][i] = Mx->NN.Ve[t1][i];
				Mx->NN.Vu[t2][i] = Mx->NN.Vu[t1][i];
				//-- then, copy t0 into t1
				Mx->NN.e[t1][i] = Mx->NN.e[t0][i];
				Mx->NN.u[t1][i] = Mx->NN.u[t0][i];
				Mx->NN.Ve[t1][i] = Mx->NN.Ve[t0][i];
				Mx->NN.Vu[t1][i] = Mx->NN.Vu[t0][i];
			}

		}
	}
	Mx->NN.norm_e[t2] = Mx->NN.norm_e[t1];
	Mx->NN.norm_e[t1] = Mx->NN.norm_e[t0];
}
void RestorePrevNeurons(NN_Parms* NNParms, NN_MxData* Mx) {
	int i, l;

	for (l = 0; l<NNParms->LevelsCount; l++) {
		for (i = 0; i < NNParms->NodesCount[l]; i++) {
			//-- first, copy t1 into t2
			Mx->NN.a[l][t0][i] = Mx->NN.a[l][t1][i];
			Mx->NN.F[l][t0][i] = Mx->NN.F[l][t1][i];
			Mx->NN.dF[l][t0][i] = Mx->NN.dF[l][t1][i];
			Mx->NN.edF[l][t0][i] = Mx->NN.edF[l][t1][i];
			Mx->NN.c[l][t0][i] = Mx->NN.c[l][t1][i];
			//-- then, copy t0 inti t1
			Mx->NN.a[l][t1][i] = Mx->NN.a[l][t2][i];
			Mx->NN.F[l][t1][i] = Mx->NN.F[l][t2][i];
			Mx->NN.dF[l][t1][i] = Mx->NN.dF[l][t2][i];
			Mx->NN.edF[l][t1][i] = Mx->NN.edF[l][t2][i];
			Mx->NN.c[l][t1][i] = Mx->NN.c[l][t2][i];

			if (l==NNParms->LevelsCount-1) {
				//-- first, copy t1 into t2
				Mx->NN.e[t0][i] = Mx->NN.e[t1][i];
				Mx->NN.u[t0][i] = Mx->NN.u[t1][i];
				Mx->NN.Ve[t0][i] = Mx->NN.Ve[t1][i];
				Mx->NN.Vu[t0][i] = Mx->NN.Vu[t1][i];
				//-- then, copy t0 into t1
				Mx->NN.e[t1][i] = Mx->NN.e[t2][i];
				Mx->NN.u[t1][i] = Mx->NN.u[t2][i];
				Mx->NN.Ve[t1][i] = Mx->NN.Ve[t2][i];
				Mx->NN.Vu[t1][i] = Mx->NN.Vu[t2][i];
			}

		}
	}
	Mx->NN.norm_e[t0] = Mx->NN.norm_e[t1];
	Mx->NN.norm_e[t1] = Mx->NN.norm_e[t2];
}

void SavePrevWeights(NN_Parms* NNParms, NN_MxData* Mx){
	int l, j, i;

	for (l = 0; l<(NNParms->LevelsCount-1); l++){
		for (j = 0; j < NNParms->NodesCount[l+1]; j++){
			for (i = 0; i < NNParms->NodesCount[l]; i++){
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
void RestorePrevWeights(NN_Parms* NNParms, NN_MxData* Mx) {
	int l, j, i;

	for (l = 0; l<(NNParms->LevelsCount-1); l++) {
		for (j = 0; j < NNParms->NodesCount[l+1]; j++) {
			for (i = 0; i < NNParms->NodesCount[l]; i++) {
				//-- (t-2)
				Mx->NN.W[l][t0][j][i] = Mx->NN.W[l][t1][j][i];
				//Mx->NN.dW[l][t0][j][i] = Mx->NN.dW[l][t1][j][i];
				//Mx->NN.dJdW[l][t0][j][i] = Mx->NN.dJdW[l][t1][j][i];
				Mx->NN.Q_dJdW[l][t0][j][i] = Mx->NN.Q_dJdW[l][t1][j][i];
				//-- (t-1)
				Mx->NN.W[l][t1][j][i] = Mx->NN.W[l][t2][j][i];
				//Mx->NN.dW[l][t1][j][i] = Mx->NN.dW[l][t2][j][i];
				//Mx->NN.dJdW[l][t1][j][i] = Mx->NN.dJdW[l][t2][j][i];
				Mx->NN.Q_dJdW[l][t1][j][i] = Mx->NN.Q_dJdW[l][t2][j][i];
			}
		}
	}
}

double Derivate(int ActivationFunction, double INval){
	double ret;
	switch (ActivationFunction){
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

double Derivate2(int ActivationFunction, double INval){
	double ret;
	switch (ActivationFunction){
	case NN_ACTIVATION_TANH:
		ret = -(8*(exp(2*INval)-1)*exp(2*INval))/pow((exp(2*INval)+1),3);
		break;
	case NN_ACTIVATION_EXP4:
		ret = -16*((exp(4*INval)-1)*exp(4*INval))/pow((exp(4*INval)+1),3);
		break;
	default:
		ret = (1 - tanh(INval)*tanh(INval));
		break;
	}
	return ret;
}

void Activate(int ActivationFunction, int NeuronCount, double* gain, double* INval, double* OUTval, double* dOUTval){
	for (int n = 0; n < NeuronCount; n++) {
		switch (ActivationFunction){
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

void FeedBack(NN_Parms* NN, NN_MxData* Mx, bool Zero){
	
	//-- Sets values for Context Neurons. Called by FF (Zero=false) and Run_NN (Zero=true)
	
	int i, l, cc;

	cc = 0;// NN->OutputCount;
	for (l = NN->LevelsCount-2; l>0; l--){
		cc = NN->NodesCount[l]-cc;
		for (i = 0; i<cc; i++){
			Mx->NN.F[l-1][t0][NN->NodesCount[l-1]-cc+i] = (Zero)?0:Mx->NN.F[l][t0][i];
		}
	}
}

void FF_Std(NN_Parms* pNNParms, NN_MxData* Mx){
/*	//== Classic
	int i, h, o;
	//-- L0 -> L1
	for (h = 0; h<pNNParms->HiddenCount; h++){
		Mx->a[L1][h] = 0;
		for (i = 0; i < (pNNParms->InputCount + pNNParms->ContextCount); i++) Mx->a[L1][h] += Mx->F[L0][i] * Mx->W[L10][h][i];
	}
	Activate(pNNParms->ActivationFunction, pNNParms->HiddenCount, Mx->c[L1], Mx->a[L1], Mx->F[L1], Mx->dF[L1]);
	//-- L1 -> L2
	for (o = 0; o < pNNParms->L2cnt; o++){
		Mx->a[L2][o] = 0;
		for (h = 0; h < pNNParms->HiddenCount; h++) Mx->a[L2][o] += Mx->F[L1][h] * Mx->W[L21][o][h];
	}
	Activate(pNNParms->ActivationFunction, pNNParms->L2cnt, Mx->c[L2], Mx->a[L2], Mx->F[L2], Mx->dF[L2]);
	//-- Hidden->Context
	if (pNNParms->UseContext == 1){
		for (h = 0; h < pNNParms->L1cnt; h++) Mx->F[L0][pNNParms->InputCount + h] = Mx->F[L1][h];
	}

	//== Matrix

	//-- L0 -> L1
	MbyV(pNNParms->L1cnt, pNNParms->L0cnt, Mx->W[L10][t0], Mx->F[L0][t0], Mx->a[L1][t0]);	// Qing (6)
	Activate(pNNParms->ActivationFunction, pNNParms->L1cnt, Mx->c[L1][t0], Mx->a[L1][t0], Mx->F[L1][t0], Mx->dF[L1][t0]);
	//-- L1 -> L2
	MbyV(pNNParms->L2cnt, pNNParms->L1cnt, Mx->W[L21][t0], Mx->F[L1][t0], Mx->a[L2][t0]);	// Qing (2)
	Activate(pNNParms->ActivationFunction, pNNParms->L2cnt, Mx->c[L2][t0], Mx->a[L2][t0], Mx->F[L2][t0], Mx->dF[L2][t0]);
	//-- Hidden->Context
	for (int c = 0; c < pNNParms->ContextCount; c++) Mx->F[L0][t0][pNNParms->InputCount + c] = Mx->F[L1][t0][c];
*/

	for (int l = 0; l<(pNNParms->LevelsCount-1); l++){
		MbyV(pNNParms->NodesCount[l+1], pNNParms->NodesCount[l], Mx->NN.W[l][t0], false, Mx->NN.F[l][t0], Mx->NN.a[l+1][t0]);	
		Activate(pNNParms->ActivationFunction, pNNParms->NodesCount[l+1], Mx->NN.c[l+1][t0], Mx->NN.a[l+1][t0], Mx->NN.F[l+1][t0], Mx->NN.dF[l+1][t0]);
	}
	//-- Hidden->Context 
	if (pNNParms->UseContext==1) FeedBack(pNNParms, Mx, false);

}

void FF(NN_Parms* NNParms, NN_MxData* Mx){

	FF_Std(NNParms, Mx);

	//-- Regardless of the method, here we update the network error, and calc eT (1xL2)matrix of e , and ||e|| (norm of e)
	VminusV(NNParms->NodesCount[NNParms->LevelsCount-1], Mx->NN.u[t0], Mx->NN.F[NNParms->LevelsCount-1][t0], Mx->NN.e[t0]);
	//V2HorM(NNParms->NodesCount[NNParms->LevelsCount-1], Mx->NN.e[t0], Mx->NN.eT);
	Mx->NN.norm_e[t0] = Vnorm(NNParms->NodesCount[NNParms->LevelsCount-1], Mx->NN.e[t0]);
	//-- the same goes for Validation error
	VminusV(NNParms->NodesCount[NNParms->LevelsCount-1], Mx->NN.Vu[t0], Mx->NN.F[NNParms->LevelsCount-1][t0], Mx->NN.Ve[t0]);
}

void Qing_CalcExtG(NN_Parms* NN, NN_MxData* Mx){
	MbyM(NN->NodesCount[1], 1, 1, NN->NodesCount[1]*NN->NodesCount[0], Mx->NN.Q_M6[1], Mx->NN.uW, Mx->NN.Q_M3[0]);
	MbyM(NN->NodesCount[1], NN->NodesCount[1]*NN->NodesCount[0], NN->NodesCount[1]*NN->NodesCount[0], NN->NodesCount[0], Mx->NN.Q_M3[0], Mx->NN.dxdW10, Mx->NN.Q_ExtG);
	MbyS(NN->NodesCount[1], NN->NodesCount[0], Mx->NN.Q_ExtG, -1, Mx->NN.Q_ExtG);
}

double Qing_Calcro10(NN_Parms* NN, NN_MxData* Mx){
	int i;
	double ro10a;
	double ro10b = 0;

	ro10a = pow(Mnorm(NN->NodesCount[1], NN->NodesCount[2], Mx->NN.Q_M5[1]),2);
	
	for (i = 0; i < NN->NodesCount[0];				i++) ro10b += pow(Mx->NN.F[0][t0][i], 2);
	for (i = 0; i < (NN->NodesCount[1]*NN->NodesCount[0]);	i++) ro10b += pow(Mx->NN.uW[0][i], 2);

	return(1 / (2 * Vmin_NoZero(NN->NodesCount[1], Mx->NN.dF[1][t0])*Vmin_NoZero(NN->NodesCount[2], Mx->NN.dF[2][t0]))*(1 + ro10a*ro10b));
}

void Qing_CalcdxdW10(NN_Parms* pNNParms, NN_MxData* Mx){
	//int i, h, m;
	int w;
	double a, b, c, x, z;
	int ic = pNNParms->InputCount;
	int hc = pNNParms->NodesCount[1];
	int iy, ix, hy, hx;
	//-- every W has its own Jacobian
	for (w = 0; w < hc; w++){

		//-- top (InputCount-long) of jacobian for @x/@Wm is zero-valued
		for (iy = 0; iy < ic; iy++){
			for (ix = 0; ix < pNNParms->NodesCount[0]; ix++){
				Mx->NN.dxdW10[w*(ic + hc) + iy][ix] = 0;
			}
		}
		//-- bottom (HiddenCount-long) of jacobian for @x/@Wm
		for (hy = 0; hy < hc; hy++){
			for (hx = 0; hx < pNNParms->NodesCount[0]; hx++){
				a = (hy == w)?Mx->NN.F[0][t1][hx]:0;
				b = Mx->NN.W[10][t1][hy][ic + w];
				c = Mx->NN.F[0][t2][hx];
				x = Mx->NN.W[10][t1][w][hx];
				z = Mx->NN.dW[10][t1][w][hx];
				Mx->NN.dxdW10[w*(ic+hc)+ic+hy][hx] = Mx->NN.F[1][t1][hy] * (a + b*c*Derivate(pNNParms->ActivationFunction, c*(x - z)));
			}
		}
	}
}

double Qing_CalcD10W(NN_Parms* NN, NN_MxData* Mx){
	double ret;

	//-- build ux
	VbyV2M(NN->NodesCount[0], Mx->NN.F[0][t0], NN->NodesCount[0], Mx->NN.F[0][t0], false, Mx->NN.ux);
	
	//-- Invert ux (???)
	//MInv(NN->NodesCount[0], Mx->NN.ux, Mx->NN.ux_inv);
	
	//-- M1[0] = uW* @x(t)/@W(t) => [1x0]
	MbyM(1, NN->NodesCount[1]*NN->NodesCount[0], NN->NodesCount[1]*NN->NodesCount[0], NN->NodesCount[0], Mx->NN.uW, Mx->NN.dxdW10, Mx->NN.Q_M1[0]);
	//-- Q_V1 = ux * x
	MbyV(NN->NodesCount[0], NN->NodesCount[0], Mx->NN.ux, false, Mx->NN.F[0][t0], Mx->NN.Q_V1);

	//-- D10W = M2[0][0] * Q_V1
	ret = VbyV(NN->NodesCount[0], Mx->NN.Q_M1[0][0], Mx->NN.Q_V1);

	return ret;
}

void Calc_H(NN_Parms* NN, NN_MxData* Mx){
	// Hessian matrices for the whole network. There is one matrix for each neuron (n)
	int l, n, j, i;

	for (l = 0; l<(NN->LevelsCount - 1); l++){
		for (n = 0; n < NN->NodesCount[l + 1]; n++){
			for (j = 0; j < NN->NodesCount[l]; j++){
				for (i = 0; i < NN->NodesCount[l]; i++){
					Mx->NN.H[l][t0][n][j][i] = Mx->NN.F[l][t0][j] * Mx->NN.F[l][t0][i] * Derivate2(NN->ActivationFunction, Mx->NN.a[l + 1][t0][n]);
				}
			}
		}
	}

}

void Calc_dJdW(NN_Parms* NN, NN_MxData* Mx, bool doFF, bool doCalcH){
	int l;
	
	if (doFF) FF(NN, Mx);

	for (l = NN->LevelsCount - 1; l > 0; l--){

		if (l==(NN->LevelsCount-1)){
			//-- top level only
			VbyV2V(NN->NodesCount[l], Mx->NN.e[t0], Mx->NN.dF[l][t0], Mx->NN.edF[l][t0]);									// edF(l) = e * F'(l)
		} else{
			//-- lower levels
			MbyV(NN->NodesCount[l+1], NN->NodesCount[l], Mx->NN.W[l][t0], true, Mx->NN.edF[l+1][t0], Mx->NN.edF[l][t0]);	// edF(l) = edF(l+1) * WT(l+1)
			VbyV2V(NN->NodesCount[l], Mx->NN.edF[l][t0], Mx->NN.dF[l][t0], Mx->NN.edF[l][t0]);								// edF(l) = edF(l)   * F'(l)
		}
		//-- common
		VbyV2M(NN->NodesCount[l], Mx->NN.edF[l][t0], NN->NodesCount[l-1], Mx->NN.F[l-1][t0], false, Mx->NN.dJdW[l-1][t0]);	// dJdW(l) = edF(l) * F(l-1)
	}

	if (doCalcH) Calc_H(NN, Mx);
}

/*void dEdW_at_w(NN_Parms* NN, NN_MxData* Mx, int level, double** W, int w_idx, double* w_new, double* odEdW_at_w){
	int mx = NN->NodesCount[level];
	double* tmpW = (double*)malloc(mx*sizeof(double));

	//-- 1. save w vector at pos w_idx into tmpW
	VCopy(mx, W[w_idx], tmpW);
	//-- 2. put w_new into M
	VCopy(mx, w_new, W[w_idx]);
	//-- 3. FF to recalc E
	FF(NN, Mx);
	//-- 4. calc dE/dW whole matrix
	Calc_dJdW(NN, Mx, false, false);
	//-- 5. return vector is one row of dE/dW corresponding to w_idx
	VCopy(mx, Mx->NN.dJdW[level][t0][w_idx], odEdW_at_w);
	//-- 6. put original w back into place, and re-run FF
	VCopy(mx, tmpW, W[w_idx]);
	FF(NN, Mx);

	free(tmpW);
}
*/

/*double E_at_w(NN_Parms* NN, NN_MxData* Mx, int my, int mx, double** M, int w_idx, double* w_new){
	double ret;
	double* tmpW = (double*)malloc(mx*sizeof(double));

	//-- 1. save w vector at pos w_idx into w_old
	VCopy(mx, M[w_idx], tmpW);
	//-- 2. put w_new into M
	VCopy(mx, w_new, M[w_idx]);
	//-- 3. FF to recalc E
	FF(NN, Mx);
	//-- 5. return value is Mx->norm_e after FF
	ret = Mx->NN.norm_e[t0];
	//-- 6. put original w back into place, and re-run FF
	VCopy(mx, tmpW, M[w_idx]);
	FF(NN, Mx);
	free(tmpW);

	return ret;
}
*/

//-- Backup/Restore utilities use t3/t4, as those are never used as actual timesteps
void Backup_Neurons(NN_Parms* NN, NN_MxData* Mx, int timebin) {

	for (int l = 0; l<NN->LevelsCount; l++) {
		VCopy(NN->NodesCount[l], Mx->NN.a[l][t0], Mx->NN.a[l][timebin]);
		VCopy(NN->NodesCount[l], Mx->NN.F[l][t0], Mx->NN.F[l][timebin]);
		VCopy(NN->NodesCount[l], Mx->NN.dF[l][t0], Mx->NN.dF[l][timebin]);
		VCopy(NN->NodesCount[l], Mx->NN.edF[l][t0], Mx->NN.edF[l][timebin]);
		VCopy(NN->NodesCount[l], Mx->NN.c[l][t0], Mx->NN.c[l][timebin]);
	}
	
	VCopy(NN->NodesCount[NN->LevelsCount-1], Mx->NN.e[t0], Mx->NN.e[timebin]);
	VCopy(NN->NodesCount[NN->LevelsCount-1], Mx->NN.u[t0], Mx->NN.u[timebin]);
	VCopy(NN->NodesCount[NN->LevelsCount-1], Mx->NN.Ve[t0], Mx->NN.Ve[timebin]);
	VCopy(NN->NodesCount[NN->LevelsCount-1], Mx->NN.Vu[t0], Mx->NN.Vu[timebin]);

	Mx->NN.norm_e[timebin] = Mx->NN.norm_e[t0];
}
void Restore_Neurons(NN_Parms* NN, NN_MxData* Mx, int timebin) {

	for (int l = 0; l<NN->LevelsCount; l++) {
		VCopy(NN->NodesCount[l], Mx->NN.a[l][timebin], Mx->NN.a[l][t0]);
		VCopy(NN->NodesCount[l], Mx->NN.F[l][timebin], Mx->NN.F[l][t0]);
		VCopy(NN->NodesCount[l], Mx->NN.dF[l][timebin], Mx->NN.dF[l][t0]);
		VCopy(NN->NodesCount[l], Mx->NN.edF[l][timebin], Mx->NN.edF[l][t0]);
		VCopy(NN->NodesCount[l], Mx->NN.c[l][timebin], Mx->NN.c[l][t0]);
	}

	VCopy(NN->NodesCount[NN->LevelsCount-1], Mx->NN.e[timebin], Mx->NN.e[t0]);
	VCopy(NN->NodesCount[NN->LevelsCount-1], Mx->NN.u[timebin], Mx->NN.u[t0]);
	VCopy(NN->NodesCount[NN->LevelsCount-1], Mx->NN.Ve[timebin], Mx->NN.Ve[t0]);
	VCopy(NN->NodesCount[NN->LevelsCount-1], Mx->NN.Vu[timebin], Mx->NN.Vu[t0]);

	Mx->NN.norm_e[t0] = Mx->NN.norm_e[timebin];
}
void Backup_Weights(NN_Parms* NN, NN_MxData* Mx, int timebin) {
	for (int l = 0; l < (NN->LevelsCount - 1); l++) {
		MCopy(NN->NodesCount[l+1], NN->NodesCount[l], Mx->NN.W[l][t0], Mx->NN.W[l][timebin]);
		MCopy(NN->NodesCount[l+1], NN->NodesCount[l], Mx->NN.dW[l][t0], Mx->NN.dW[l][timebin]);
		MCopy(NN->NodesCount[l+1], NN->NodesCount[l], Mx->NN.dJdW[l][t0], Mx->NN.dJdW[l][timebin]);
	}
}
void Restore_Weights(NN_Parms* NN, NN_MxData* Mx, int timebin, bool doW=true, bool dodW=true, bool dodJdW=true) {
	for (int l = 0; l < (NN->LevelsCount - 1); l++) {
		if(doW)    MCopy(NN->NodesCount[l+1], NN->NodesCount[l], Mx->NN.W[l][timebin], Mx->NN.W[l][t0]);
		if(dodW)   MCopy(NN->NodesCount[l+1], NN->NodesCount[l], Mx->NN.dW[l][timebin], Mx->NN.dW[l][t0]);
		if(dodJdW) MCopy(NN->NodesCount[l+1], NN->NodesCount[l], Mx->NN.dJdW[l][timebin], Mx->NN.dJdW[l][t0]);
	}
}

void dEdW_at_w_LVV(NN_Parms* NN, NN_MxData* Mx, double** LVV_W, double* w_new, double* odEdW_at_w){

	Backup_Neurons(NN, Mx, t4);
	Backup_Weights(NN, Mx, t4);

	//-- 1. put w_new into M
	VCopy(NN->WeightsCountTotal, w_new, LVV_W);
	//-- 2. calc dE/dW whole matrix (doFF before)
	Calc_dJdW(NN, Mx, true, false);
	//-- 3. return vector is one row of dE/dW corresponding to w_idx
	VCopy(NN->WeightsCountTotal, Mx->NN.scgd->LVV_dJdW[t0], odEdW_at_w);

	Restore_Neurons(NN, Mx, t4);
	Restore_Weights(NN, Mx, t4);

}

double E_at_w_LVV(NN_Parms* NN, NN_MxData* Mx, double** LVV_W, double* w_new){
	double ret;

	Backup_Neurons(NN, Mx, t4);
	Backup_Weights(NN, Mx, t4);

	//-- 2. put w_new into LVV_W
	VCopy(NN->WeightsCountTotal, w_new, LVV_W);
	//-- 3. FF to recalc E
	FF(NN, Mx);
	//-- 5. return value is Mx->norm_e after FF
	ret = Mx->NN.norm_e[t0];

	Restore_Neurons(NN, Mx, t4);
	Restore_Weights(NN, Mx, t4);

	return ret;
}

bool BP_Qing(int pid, int tid, tDebugInfo* DebugParms, int pEpoch, NN_Parms* NN, int pNetId, int TestId, NN_MxData* Mx){
	int i;

	//== L21

	//-- calc basic dJdW
		//-- Setup data structures
		V2DiagM(NN->NodesCount[2], Mx->NN.dF[2][t0], Mx->NN.Q_M1[2]);	// Q_M1[2] stores F'(2,1)	[2x2]
		V2VertM(NN->NodesCount[2], Mx->NN.e[t0], Mx->NN.Q_M2[2]);		// Q_M2[2] stores eT			[2x1]
		V2HorM(NN->NodesCount[1], Mx->NN.F[1][t0], Mx->NN.Q_M3[2]);	// Q_M3[2] stores F(1,0)		[1x1]
		//-- Standard BP, Qing(11)
		MbyM(NN->NodesCount[2], NN->NodesCount[2], NN->NodesCount[2], 1, Mx->NN.Q_M1[2], Mx->NN.Q_M2[2], Mx->NN.Q_M4[2]);	// Q_M4[2]    stores F'(2,1) X eT			[2x1]
		MbyM(NN->NodesCount[2], 1, 1, NN->NodesCount[1], Mx->NN.Q_M4[2], Mx->NN.Q_M3[2], Mx->NN.dJdW[21][t0]);			// dJdW[21] stores F'(2,1) X eT X F(1,0)T	[2x1]
	//-- calc ro			- Qing(18)
	Mx->NN.Q_ro[21] = (1 + pow(Vnorm(NN->NodesCount[1], Mx->NN.F[1][t0]), 2)*pow(Vnorm(NN->NodesCount[2], Mx->NN.dF[2][t0]), 2)) / Vmin_NoZero(NN->NodesCount[2], Mx->NN.dF[2][t0]);
	//-- calc sigma			- Qing(17)
	Mx->NN.Q_adzev21norm = Vnorm(NN->NodesCount[2], Mx->NN.adzev[21]);
	Mx->NN.Q_sigma[21] = (Mx->NN.norm_e[t0] < Mx->NN.Q_adzev21norm)?0:1;
	//-- calc actual Q_dJdW	- Qing(15)
	MbyS(NN->NodesCount[2], NN->NodesCount[1], Mx->NN.dJdW[21][t0], Mx->NN.Q_sigma[21] / Mx->NN.Q_ro[21], Mx->NN.Q_dJdW[21][t0]);
	//-- add actual Q_djdW to W
	MplusM(NN->NodesCount[2], NN->NodesCount[1], Mx->NN.W[21][t0], Mx->NN.Q_dJdW[21][t0], Mx->NN.W[21][t0]);
	//-- calc adzev			- Qing(16)
	for (i = 0; i < NN->NodesCount[2]; i++) Mx->NN.adzev[21][i] += Mx->NN.Q_sigma[21] / Mx->NN.Q_ro[21] * fabs(Mx->NN.e[t0][i]);

	//== 10

	//-- calc basic dJdW
		//-- Setup data structures
		V2DiagM(NN->NodesCount[1], Mx->NN.dF[1][t0], Mx->NN.Q_M1[1]);						// Q_M1[1] stores F'(1,0)	[1x1]
		Transpose(NN->NodesCount[2], NN->NodesCount[1], Mx->NN.W[21][t0], Mx->NN.Q_M2[1]);	// Q_M2[1] stores W(2,1)T	[1x2]
		V2HorM(NN->NodesCount[0], Mx->NN.F[0][t0], Mx->NN.Q_M3[1]);						// Q_M3[1] stores xT			[1x0]
		//-- Qing(12)
		MbyM(NN->NodesCount[1], NN->NodesCount[1], NN->NodesCount[1], NN->NodesCount[2], Mx->NN.Q_M1[1], Mx->NN.Q_M2[1], Mx->NN.Q_M4[1]);	// Q_M4[1]	 stores F'(1,0) X W(2,1)T						[1x2]
		MbyM(NN->NodesCount[1], NN->NodesCount[2], NN->NodesCount[2], NN->NodesCount[2], Mx->NN.Q_M4[1], Mx->NN.Q_M1[2], Mx->NN.Q_M5[1]);	// Q_M5[1]	 stores F'(1,0) X W(2,1)T X F'(2,1)				[1x2]
		MbyM(NN->NodesCount[1], NN->NodesCount[2], NN->NodesCount[2], 1, Mx->NN.Q_M5[1], Mx->NN.Q_M2[2], Mx->NN.Q_M6[1]);				// Q_M6[1]	 stores F'(1,0) X W(2,1)T X F'(2,1) X eT		[1x1]
		MbyM(NN->NodesCount[1], 1, 1, NN->NodesCount[0], Mx->NN.Q_M6[1], Mx->NN.Q_M3[1], Mx->NN.dJdW[10][t0]);						// dJdW[10] stores F'(1,0) X W(2,1)T X F'(2,1) X eT X xT	[1x0]
	//-- calc uW
	M2LVV(NN->NodesCount[1], NN->NodesCount[0], Mx->NN.W[10][t0], Mx->NN.uW[0]);
	//-- calc ro				- Qing(28)
	Mx->NN.Q_ro[10] = Qing_Calcro10(NN, Mx);
	//-- calc sigma				- Qing(21)
	Mx->NN.Q_sigma[10] = (Mx->NN.norm_e[t0] < Mx->NN.adzev[10][0])?0:1;
	//-- calc dxdW10			- Qing(27)
	Qing_CalcdxdW10(NN, Mx);
	//-- calc D10W				- Qing(23)
	Mx->NN.Q_D10W = Qing_CalcD10W(NN, Mx);
	//-- calc gamma				- Qing(22)
	Mx->NN.Q_gamma = ((Mx->NN.Q_D10W>NN->HCPbeta) || (Mx->NN.Q_D10W<0))?0:1;
	//-- calc extended gradient - Qing(24)
	Qing_CalcExtG(NN, Mx);
	//-- if gamma=1, add extended gradient to basic gradient, and save it into M4[0]; otherwise, copy basic gradient into M4[0]
	if (Mx->NN.Q_gamma == 1) {
		MplusM(NN->NodesCount[1], NN->NodesCount[0], Mx->NN.dJdW[10][t0], Mx->NN.Q_ExtG, Mx->NN.Q_M4[0]);
	}
	else{
		MCopy(NN->NodesCount[1], NN->NodesCount[0], Mx->NN.dJdW[10][t0], Mx->NN.Q_M4[0]);
	}
	//-- calc actual Q_dJdW		- Qing(19)
	MbyS(NN->NodesCount[1], NN->NodesCount[0], Mx->NN.Q_M4[0], -Mx->NN.Q_sigma[10] / Mx->NN.Q_ro[10], Mx->NN.Q_dJdW[10][t0]);
	//-- add actual Q_djdW to W
	MplusM(NN->NodesCount[1], NN->NodesCount[0], Mx->NN.W[10][t0], Mx->NN.Q_dJdW[10][t0], Mx->NN.W[10][t0]);
	//-- calc adzev				- Qing(20)
	Mx->NN.adzev[10][0] += Mx->NN.Q_sigma[10] / Mx->NN.Q_ro[10] * Mx->NN.norm_e[t0];

	return true;
}

bool BP_QuickProp(int pid, int tid, int pEpoch, tDebugInfo* DebugParms, NN_Parms* pNNParms, NN_MxData* Mx){
	//-- as per QuickProp2.pdf, 2.6.3	
	int l, j, i;
	
	Calc_dJdW(pNNParms, Mx, false, false);
	
	for (l = 0; l<(pNNParms->LevelsCount-1); l++){
		for (j = 0; j < pNNParms->NodesCount[l+1]; j++){
			for (i = 0; i < pNNParms->NodesCount[l]; i++){

				Mx->NN.dW[l][t0][j][i] = pNNParms->LearningRate*Mx->NN.dJdW[l][t0][j][i];
				if (Mx->NN.dW[l][t0][j][i]>0){
					if (Mx->NN.dJdW[l][t0][j][i]>(pNNParms->mu / (1 + pNNParms->mu)*Mx->NN.dJdW[l][t1][j][i])){
						Mx->NN.dW[l][t0][j][i] = pNNParms->mu*Mx->NN.dW[l][t0][j][i];
					}
					else{
						Mx->NN.dW[l][t0][j][i] = Mx->NN.dJdW[l][t0][j][i] / (Mx->NN.dJdW[l][t1][j][i] - Mx->NN.dJdW[l][t0][j][i])*Mx->NN.dW[l][t0][j][i];
					}
					if (Mx->NN.dJdW[l][t0][j][i]>0) Mx->NN.dW[l][t0][j][i] += pNNParms->LearningRate*Mx->NN.dJdW[l][t0][j][i];
				}
				else if (Mx->NN.dW[l][t0][j][i]<0){
					if (Mx->NN.dJdW[l][t0][j][i]<(pNNParms->mu / (1 + pNNParms->mu)*Mx->NN.dJdW[l][t1][j][i])){
						Mx->NN.dW[l][t0][j][i] = pNNParms->mu*Mx->NN.dW[l][t0][j][i];
					}
					else{
						Mx->NN.dW[l][t0][j][i] = Mx->NN.dJdW[l][t0][j][i] / (Mx->NN.dJdW[l][t1][j][i] - Mx->NN.dJdW[l][t0][j][i])*Mx->NN.dW[l][t0][j][i];
					}
					if (Mx->NN.dJdW[l][t0][j][i]<0) Mx->NN.dW[l][t0][j][i] += pNNParms->LearningRate*Mx->NN.dJdW[l][t0][j][i];
				}
				else if (Mx->NN.dW[l][t0][j][i] == 0){
					Mx->NN.dW[l][t0][j][i] += pNNParms->LearningRate*Mx->NN.dJdW[l][t0][j][i];
				}
			}
		}
	}
	return true;
}

bool BP_scgd(int pid, int tid, int pEpoch, tDebugInfo* DebugParms, NN_Parms* NN, tCoreLog* NNLogs, NN_MxData* Mx){

	int k;

	double sigma, delta, mu, alpha, beta = 0, b1, b2;
	double lambda, lambdau;
	double pnorm, pnorm2;
	double e_old, e_new, comp;
	bool success;
	double epsilon = NN->TargetMSE / NN->OutputCount;

	//Backup_Neurons(NN, Mx, t3);
	Backup_Weights(NN, Mx, t3);

	Calc_dJdW(NN, Mx, false, false);

	//-- 1. Choose initial vector w ; p=r=-E'(w)
	VCopy(NN->WeightsCountTotal, Mx->NN.scgd->LVV_dJdW[t0], Mx->NN.scgd->p); //VbyS(NN->WeightsCountTotal, Mx->NN.scgd->p, -1, Mx->NN.scgd->p);
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
		if (success){

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
			VminusV(NN->WeightsCountTotal, Mx->NN.scgd->dE0, Mx->NN.scgd->dE1, Mx->NN.scgd->dE);
			VdivS(NN->WeightsCountTotal, Mx->NN.scgd->dE, sigma, Mx->NN.scgd->s);

			//-- calc delta
			delta = VdotV(NN->WeightsCountTotal, Mx->NN.scgd->p, Mx->NN.scgd->s);
		}

		//-- 3. scale s and delta

		//--- 3.1 s=s+(lambda-lambdau)*p
		VbyS(NN->WeightsCountTotal, Mx->NN.scgd->p, (lambda - lambdau), Mx->NN.scgd->lp);
		VplusV(NN->WeightsCountTotal, Mx->NN.scgd->s, Mx->NN.scgd->lp, Mx->NN.scgd->s);
		//--- 3.2 delta=delta+(lambda-lambdau)*|p|^2
		delta += (lambda - lambdau)*pnorm2;

		//-- 4. if delta<=0 (i.e. Hessian is not positive definite) , then make it positive
		if (delta <= 0){
			//-- adjust s
			VbyS(NN->WeightsCountTotal, Mx->NN.scgd->p, (lambda - 2 * delta / pnorm2), Mx->NN.scgd->lp);
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
		e_old = Mx->NN.norm_e[t0];
		//--- 6.3 E(w+dw) ir calculated by E_at_w()
		//=================================
		e_new = E_at_w_LVV(NN, Mx, Mx->NN.scgd->LVV_W[t0], Mx->NN.scgd->newW);
		//=================================
		//--- 6.4 comp=2*delta*(e_old-e_new)/mu^2
		comp = 2 * delta*(e_old - e_new) / pow(mu, 2);

		if (comp >= 0){
			//-- 7. Update weight vector

			//-- W = W + dW
			VbyS(NN->WeightsCountTotal, Mx->NN.scgd->p, alpha, Mx->NN.scgd->dW);
			//===========================================================================================================
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
			VCopy(NN->WeightsCountTotal, Mx->NN.scgd->LVV_dJdW[t0], Mx->NN.scgd->r); //VbyS(NN->WeightsCountTotal, Mx->NN.scgd->r, -1, Mx->NN.scgd->r);

			//-- reset lambdau
			lambdau = 0; success = true;

			//-- 7a. if k mod N = 0 then restart algorithm, else create new conjugate direction
			if (((k + 1) % NN->NodesCountTotal) == 0){
				VCopy(NN->WeightsCountTotal, Mx->NN.scgd->r, Mx->NN.scgd->p);
			}
			else{
				b1 = pow(Vnorm(NN->WeightsCountTotal, Mx->NN.scgd->r), 2);
				b2 = VdotV(NN->WeightsCountTotal, Mx->NN.scgd->r, Mx->NN.scgd->prev_r);
				beta = (b1 - b2) / mu;
				//-- p = r + beta*p
				VbyS(NN->WeightsCountTotal, Mx->NN.scgd->p, beta, Mx->NN.scgd->bp);
				VminusV(NN->WeightsCountTotal, Mx->NN.scgd->bp, Mx->NN.scgd->r, Mx->NN.scgd->p);// VplusV(NN->WeightsCountTotal, r, bp, p);
			}
			//-- 7b. if comp>=0.75 reduce scale parameter
			if (comp >= 0.75) lambda = lambda / 2;

		}
		else{
			//-- a reduction in error is not possible.
			lambdau = lambda;
			success = false;
		}

		//-- 8. if comp<0.25 then increase scale parameter
		if (comp<0.25) lambda = lambda * 4;

		//-- 9. if the steepest descent direction r>epsilon and success=true, then set k=k+1 and go to 2, else terminate and return w as the desired minimum
		Mx->NN.scgd->rnorm = Vnorm(NN->WeightsCountTotal, Mx->NN.scgd->r);
		if(DebugParms->SaveInternals>0) SaveCoreData_SCGD(NNLogs, pid, tid, pEpoch, Mx->BPCount, k, Mx->SCGD_progK, delta, mu, alpha, beta, lambda, lambdau, Mx->NN.scgd->rnorm, Mx->NN.norm_e[t0], comp);

		k++; Mx->SCGD_progK++;
	} while ((Mx->NN.scgd->rnorm>epsilon) && (k<NN->SCGDmaxK));

	//-- save the total dW into Mx->dW[l][t0]
	VCopy(NN->WeightsCountTotal, Mx->NN.scgd->TotdW, Mx->NN.scgd->LVV_dW[t0]);

	//-- 0. Before exiting, Restore original neurons and weights
	//Restore_Neurons(NN, Mx, t3);
	Restore_Weights(NN, Mx, t3, true, false, false);

	return(k<NN->SCGDmaxK);
}

bool BP_Std(int pid, int tid, int pEpoch, tDebugInfo* DebugParms, NN_Parms* NN, NN_MxData* Mx){
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

	Calc_dJdW(NN, Mx, false, false);

	//-- calc dW 
	for (int l = 0; l<(NN->LevelsCount-1); l++){
		MbyS(NN->NodesCount[l+1], NN->NodesCount[l], Mx->NN.dJdW[l][t0], NN->LearningRate, Mx->NN.dW[l][t0]);
		MbyS(NN->NodesCount[l+1], NN->NodesCount[l], Mx->NN.dW[l][t1], NN->LearningMomentum, Mx->NN.dW[l][t1]);		//-- prevdW = prevdW * lm
		MbyS(NN->NodesCount[l+1], NN->NodesCount[l], Mx->NN.dW[l][t0], (1-NN->LearningMomentum), Mx->NN.dW[l][t0]);	//-- dW = dW * (1-lm)
		MplusM(NN->NodesCount[l+1], NN->NodesCount[l], Mx->NN.dW[l][t0], Mx->NN.dW[l][t1], Mx->NN.dW[l][t0]);		//-- dW = dW + prevdW
	}
	return true;
}

void NNInit(NN_Parms* NN, NN_MxData* Mx, bool loadW, tCoreLog* NNLogs){
	int i, k, l, x, y;

	//-- Neurons
	for (l = 0; l < NN->LevelsCount; l++){
		for (i = 0; i < NN->NodesCount[l]; i++){
			Mx->NN.F[l][t0][i] = 0;
			Mx->NN.dF[l][t0][i] = 0;
			Mx->NN.c[l][t0][i] = 1;
		}
	}

	//-- Weights
	k = 0;
	//FILE* fw = fopen("c:/temp/W.init", "r");
	//float w, dw;
	for (l = 0; l < (NN->LevelsCount-1); l++){
		for (i = 0; i < (NN->NodesCount[l+1] * NN->NodesCount[l]); i++){
			y = (int)(i / NN->NodesCount[l]);
			x = i%NN->NodesCount[l];

			if (loadW) {
				//-- load weights as we do in Run_NN():
				Mx->NN.W[l][t0][y][x] = NNLogs->NNFinalW[l][y][x].Weight;
				Mx->NN.dW[l][t0][y][x] = NNLogs->NNFinalW[l][y][x].dW;
				Mx->NN.dJdW[l][t0][y][x] = NNLogs->NNFinalW[l][y][x].dJdW;
			} else {
				Mx->NN.W[l][t0][y][x] = MyRndDbl(-1 / sqrt((double)NN->NodesCount[l + 1]), 1 / sqrt((double)NN->NodesCount[l]));
				Mx->NN.dW[l][t0][y][x] = MyRndDbl(-1 / sqrt((double)NN->NodesCount[l + 1]), 1 / sqrt((double)NN->NodesCount[l]));
				Mx->NN.dJdW[l][t0][y][x] = 0;
			}

			//fprintf(fw, "%2.10f %2.10f\n", Mx->NN.W[l][t0][y][x], Mx->NN.dW[l][t0][y][x]);
			//fscanf(fw, "%f %f\n", &w, &dw); Mx->NN.W[l][t0][y][x] = w; Mx->NN.dW[l][t0][y][x]=dw;

			Mx->NN.scgd->LVV_W[t0][k] = &Mx->NN.W[l][t0][y][x];
			Mx->NN.scgd->LVV_dW[t0][k] = &Mx->NN.dW[l][t0][y][x];
			Mx->NN.scgd->LVV_dJdW[t0][k] = &Mx->NN.dJdW[l][t0][y][x];
			Mx->NN.scgd->LVV_W[t1][k] = &Mx->NN.W[l][t0][y][x];
			Mx->NN.scgd->LVV_dW[t1][k] = &Mx->NN.dW[l][t0][y][x];
			Mx->NN.scgd->LVV_dJdW[t1][k] = &Mx->NN.dJdW[l][t0][y][x];
			k++;
		}
	}
	//fclose(fw);
	Mx->BPCount = 0; Mx->SCGD_progK = 0;

	//-- Qing stuff
	Mx->NN.adzev[0][0] = 0;
	for(i=0;i<NN->NodesCount[2]; i++) Mx->NN.adzev[1][i] = 0;
	Mx->NN.Q_ro[0] = 0; Mx->NN.Q_ro[1] = 0;
	Mx->NN.Q_sigma[0] = 0; Mx->NN.Q_sigma[1] = 0;

}

bool Calc_dW(int pid, int tid, int pEpoch, tDebugInfo* pDebugParms, NN_Parms* NN, tCoreLog* NNLogs, NN_MxData* Mx){
	//-- All the BP routines should only set Mx->dW , and NOT change Mx->W

	bool ret;	//-- if the specific BP routine returns false, than we do not apply the calculated dW

	//-- common to all BP variants
	SavePrevWeights(NN, Mx);

	switch (NN->BP_Algo){
	case BP_STD:
		ret=BP_Std(pid, tid, pEpoch, pDebugParms, NN, Mx);
		break;
	case BP_QUICKPROP:
		ret = BP_QuickProp(pid, tid, pEpoch, pDebugParms, NN, Mx);
		break;
	case BP_SCGD:
		ret = BP_scgd(pid, tid, pEpoch, pDebugParms, NN, NNLogs, Mx);
		break;
	}
	Mx->BPCount++;

	return ret;
}

void Update_W(NN_Parms* NN, NN_MxData* Mx, double**** baseW, double**** addedW){
	//-- Saves W[t0] in W[t1] , then baseW = baseW + addedW
	for (int l = 0; l < (NN->LevelsCount - 1); l++) {
		MplusM(NN->NodesCount[l + 1], NN->NodesCount[l], baseW[l][t0], addedW[l][t0], baseW[l][t0]);	// W = W + dW
	}
}

void InitBdW(NN_Parms* NN, NN_MxData* Mx){
	//-- this zeroes BdW for all levels
	for (int l = 0; l < (NN->LevelsCount - 1); l++){
		MInit(NN->NodesCount[l + 1], NN->NodesCount[l], Mx->NN.BdW[l][t0], 0);
	}
}

double CalcNetworkTSE(NN_Parms* NN, NN_MxData* Mx, double* pSample, double* pTarget){
	double ret = 0;
	//-- 1. Load SampleData into Input Neurons OUT values, and TargetData into u[]
	VCopy(NN->InputCount, pSample, Mx->NN.F[0][t0]);
	VCopy(NN->OutputCount, pTarget, Mx->NN.u[t0]);
	//-- 2. Feed Forward, and calc squared error on output layer
	FF(NN, Mx);
	for (int o = 0; o < NN->OutputCount; o++) ret += pow(Mx->NN.e[t0][o], 2);

	return ret;
}

void NNTrain_Batch(tDebugInfo* pDebugParms, NN_Parms* NNParms, tCoreLog* NNLogs, NN_MxData* Mx, int pSampleCount, double** pSampleData, double** pTargetData, double** pSampleDataV, double** pTargetDataV){

	int s;
	int epoch;
	double MSE_T=1, TSE_T;
	double MSE_V=1, TSE_V=0;
	double prevMSE_T;
	int pid = GetCurrentProcessId();
	int tid = GetCurrentThreadId();

	for (epoch = 0; epoch < NNParms->MaxEpochs; epoch++){

		//-- 0. reset BdW=0, TSE=0
		InitBdW(NNParms, Mx);

		//-- 1. present samples, and sum up dW into BdW
		TSE_T = 0; TSE_V = 0;
		for (s = 0; s < pSampleCount; s++) {
			//-- 1.1 Present Sample, and Sum up Squared Error for every Sample
			if (Mx->useValidation>0) TSE_V += CalcNetworkTSE(NNParms, Mx, pSampleDataV[s], pTargetDataV[s]);
			TSE_T += CalcNetworkTSE(NNParms, Mx, pSampleData[s], pTargetData[s]);
			//-- 1.2 Calc dW for every sample based on BP algorithm
			if (Calc_dW(pid, tid, epoch, pDebugParms, NNParms, NNLogs, Mx)) {
				//-- 1.3 BdW = BdW + dW (only if BP is successful)
				Update_W(NNParms, Mx, Mx->NN.BdW, Mx->NN.dW);
			}
		}

		//-- 2. Weight update : W = W + BdW
		Update_W(NNParms, Mx, Mx->NN.W, Mx->NN.BdW);

/*		//-- 3. Re-Evaluate error after weight adjustments
		TSE_T = 0; TSE_V = 0;
		for (s = 0; s < pSampleCount; s++){
			//-- 1. Present Sample, and Sum up Squared Error for every Sample
			if (Mx->useValidation>0) TSE_V += CalcNetworkTSE(NNParms, Mx, pSampleDataV[s], pTargetDataV[s]);
			TSE_T += CalcNetworkTSE(NNParms, Mx, pSampleData[s], pTargetData[s]);
		}
*/		
		//-- 4. Calc MSE for epoch , and exit if less than TargetMSE
		prevMSE_T = MSE_T;	// save previous MSE
		MSE_T = TSE_T / pSampleCount / NNParms->OutputCount;
		if (Mx->useValidation>0) {
			MSE_V = TSE_V / pSampleCount / NNParms->OutputCount;
			if (NNParms->StopAtDivergence == 1 && MSE_T > prevMSE_T) break;
		} 
		WaitForSingleObject(Mx->ScreenMutex, 10);
		gotoxy(0, Mx->ScreenPos); printf("\rProcess %6d, Thread %6d, Epoch %6d , Training MSE=%f , Validation MSE=%f", pid, tid, epoch, MSE_T, MSE_V);
		ReleaseMutex(Mx->ScreenMutex);
		SaveMSEData(NNLogs, pid, tid, epoch, MSE_T, (Mx->useValidation>0) ? MSE_V : 0);
		if (MSE_T < NNParms->TargetMSE) break;
	}
	NNLogs->ActualEpochs = epoch;
	NNLogs->IntCnt = (NNParms->BP_Algo == BP_SCGD) ? Mx->SCGD_progK : epoch;

	LogWrite(pDebugParms, LOG_INFO, "NNTrain_Batch() CheckPoint 4 - Thread=%d ; Final MSE_T=%f ; Final MSE_V=%f\n", 2, tid, MSE_T, MSE_V);

}

void NNTrain_Stochastic(tDebugInfo* pDebugParms, NN_Parms* NNParms, tCoreLog* NNLogs, NN_MxData* Mx, int pSampleCount, double** pSampleData, double** pTargetData, double** pSampleDataV, double** pTargetDataV){
	int s;
	int epoch;
	double MSE_T = 1000, MSE_V = 1000;
	double TSE_T, TSE_V;
	double prevMSE_T;
	int pid = GetCurrentProcessId();
	int tid = GetCurrentThreadId();

	int* sl = (int*)malloc(pSampleCount*sizeof(int)); for (int i = 0; i<pSampleCount; i++) sl[i] = i;
	ShuffleArray(sl, pSampleCount);

	for (epoch = 0; epoch < NNParms->MaxEpochs; epoch++) {
		TSE_T = 0; TSE_V = 0;
		for (int si = 0; si < pSampleCount; si++) {
			s = sl[si];

			//-- 1. Sum up Squared Error for every Sample
			if (Mx->useValidation>0) TSE_V += CalcNetworkTSE(NNParms, Mx, pSampleDataV[s], pTargetDataV[s]);
			TSE_T += CalcNetworkTSE(NNParms, Mx, pSampleData[s], pTargetData[s]);

			//-- 2. BackPropagation calculates dW 
			Calc_dW(pid, tid, epoch, pDebugParms, NNParms, NNLogs, Mx);

			//-- 3. Update Weights
			Update_W(NNParms, Mx, Mx->NN.W, Mx->NN.dW);
		}

		//-- 4. Calc MSE for epoch , and exit if less than TargetMSE
		prevMSE_T = MSE_T;	// save previous MSE
		MSE_T = TSE_T / pSampleCount / NNParms->OutputCount;
		if (Mx->useValidation>0) {
			MSE_V = TSE_V / pSampleCount / NNParms->OutputCount;
			if (NNParms->StopAtDivergence == 1 && MSE_T > prevMSE_T) break;
		}
		WaitForSingleObject(Mx->ScreenMutex, 10);
		gotoxy(0, Mx->ScreenPos); printf("\rProcess %6d, Thread %6d, Epoch %6d , Training MSE=%f , Validation MSE=%f", pid, tid, epoch, MSE_T, MSE_V);
		ReleaseMutex(Mx->ScreenMutex);
		//LogWrite(pDebugParms, LOG_INFO, "NNTrain() - Thread=%d ; Epoch=%d ; MSE=%f\n", 3, tid, epoch, MSE);
		SaveMSEData(NNLogs, pid, tid, epoch, MSE_T, (Mx->useValidation>0)?MSE_V:0);
		if (MSE_T < NNParms->TargetMSE) break;
	}
	NNLogs->ActualEpochs = epoch;
	NNLogs->IntCnt = (NNParms->BP_Algo == BP_SCGD) ? Mx->SCGD_progK : epoch;

	LogWrite(pDebugParms, LOG_INFO, "NNTrain() CheckPoint 4 - Thread=%d ; Final MSE_T=%f ; Final MSE_V=%f\n", 2, tid, MSE_T, MSE_V);

}

void NNTrain(tDebugInfo* pDebugParms, NN_Parms* NNParms, tCoreLog* NNLogs, NN_MxData* Mx, int pSampleCount, double** pSampleData, double** pTargetData, double** pSampleDataV, double** pTargetDataV){
	switch (NNParms->TrainingProtocol){
	case TP_STOCHASTIC:
		NNTrain_Stochastic(pDebugParms, NNParms, NNLogs, Mx, pSampleCount, pSampleData, pTargetData, pSampleDataV, pTargetDataV);
		break;
	case TP_BATCH:
		NNTrain_Batch(pDebugParms, NNParms, NNLogs, Mx, pSampleCount, pSampleData, pTargetData, pSampleDataV, pTargetDataV);
		break;
	}
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
	//-- outer node only -> [Time]
	ret.e = (double**)malloc(TimeSteps * sizeof(double*));
	ret.u = (double**)malloc(TimeSteps * sizeof(double*));
	ret.Ve = (double**)malloc(TimeSteps * sizeof(double*));
	ret.Vu = (double**)malloc(TimeSteps * sizeof(double*));
	for (t = 0; t < TimeSteps; t++) {
		ret.e[t] = (double*)malloc(pNNParms->NodesCount[pNNParms->LevelsCount - 1] * sizeof(double));
		ret.u[t] = (double*)malloc(pNNParms->NodesCount[pNNParms->LevelsCount - 1] * sizeof(double));
		ret.Ve[t] = (double*)malloc(pNNParms->NodesCount[pNNParms->LevelsCount - 1] * sizeof(double));
		ret.Vu[t] = (double*)malloc(pNNParms->NodesCount[pNNParms->LevelsCount - 1] * sizeof(double));
	}
	ret.norm_e = (double*)malloc(TimeSteps * sizeof(double));

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
	ret.scgd->bp = (double*)malloc(pNNParms->WeightsCountTotal*sizeof(double));
	ret.scgd->lp = (double*)malloc(pNNParms->WeightsCountTotal*sizeof(double));
	ret.scgd->dE0 = (double*)malloc(pNNParms->WeightsCountTotal*sizeof(double));
	ret.scgd->dE1 = (double*)malloc(pNNParms->WeightsCountTotal*sizeof(double));
	ret.scgd->dE = (double*)malloc(pNNParms->WeightsCountTotal*sizeof(double));
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
	for (t = 0; t < TimeSteps; t++) {
		free(NN.e[t]);
		free(NN.u[t]);
		free(NN.Ve[t]);
		free(NN.Vu[t]);
	}
	free(NN.e);
	free(NN.u);
	free(NN.Ve);
	free(NN.Vu);
	free(NN.norm_e);

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
	free(NN.scgd->bp);
	free(NN.scgd->lp);
	free(NN.scgd->dE0);
	free(NN.scgd->dE1);
	free(NN.scgd->dE);
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
	double* tmpSample = (double*)malloc(NNParms->NodesCount[0] * sizeof(double));

	//-- 1. Load W*** from NNParms->NNFinalW[Level][FromN][ToN] 
	for (l = 0; l<NNParms->LevelsCount; l++){
		for (j = 0; j<NNParms->NodesCount[l+1]; j++){
			for (i = 0; i<NNParms->NodesCount[l]; i++){
				MxData.NN.W[l][t0][j][i] = NNLogs->NNFinalW[l][j][i].Weight;
				MxData.NN.dW[l][t0][j][i] = NNLogs->NNFinalW[l][j][i].dW;
				MxData.NN.dJdW[l][t0][j][i] = NNLogs->NNFinalW[l][j][i].dJdW;
			}
		}
	}

	//-- 2. Reset Context Neurons
	if (NNParms->UseContext==1)	FeedBack(NNParms, &MxData, true);
	
	//-- 3. Write First window of data, with no prediction (that is, write the first sample)
	for (i = 0; i<NNParms->NodesCount[0]; i++) SaveRunData(NNLogs, pid, tid, i, pSample[0][i], NULL);

	//-- 4. Write Training Set data, with next-step prediction

	//-- 4.1 In-Sample
	for (s = 0; s<pSampleCount; s++){
		for (i = 0; i < NNParms->NodesCount[0]; i++){
			tmpSample[i] = pSample[s][i];	//-- Only used for the last sample ( pSample[pSampleCount-1] )
			MxData.NN.F[0][t0][i] = tmpSample[i];		//-- Present each sample to input neurons
		}
		FF(NNParms, &MxData);							//-- Feed-Forward the network;
		vPrediction = MxData.NN.F[NNParms->LevelsCount-1][t0];	//-- Predicted  Data. All steps
		vActual = pTarget[s][0];
		//-- Write RunLog structure
		SaveRunData(NNLogs, pid, tid, NNParms->NodesCount[0] + s, vActual, vPrediction);
	}

	//-- 4.2 Out-of-Sample
	for (s = 0; s < pInputData->PredictionLen; s++){

		// Target[s] only exist while s<SampleCount. Beyond that, Actual is prediction from previous step
		vActual = vPrediction[0];

		//-- Sample beyond SampleCount must be build, regardless of pOOS
		ShiftArray(SHIFT_BACKWARD, NNParms->NodesCount[0], tmpSample, vActual);

		for (i = 0; i < NNParms->NodesCount[0]; i++) MxData.NN.F[0][t0][i] = tmpSample[i];	//-- Present each sample to input neurons
		FF(NNParms, &MxData);																//-- Feed-Forward the network;
		vPrediction = MxData.NN.F[NNParms->LevelsCount-1][t0];								//-- Predicted  Data. All steps

		SaveRunData(NNLogs, pid, tid, (s + pSampleCount+NNParms->NodesCount[0]), vActual, vPrediction);
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
	SaveInitW(pNNParms, pNNLogs, pid, tid, MxData.NN.W, MxData.NN.F[0]);
	//-- Train 
	NNTrain(pDebugParms, pNNParms, pNNLogs, &MxData, pSampleCount, pSampleData, pTargetData, pSampleDataV, pTargetDataV);
	//-- Save Final Weights
	SaveFinalW(pNNParms, &MxData.NN, pNNLogs, pid, tid);

	//-- free()s
	Free_NNMem(pNNParms, MxData.NN);


	return 0;
}

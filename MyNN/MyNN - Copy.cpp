
#include <Windows.h>
#include <math.h>

#include <MyUtils.h>
#include <MyLogDefs.h>
#include <MyMatrix.h>
#include <DataShape.h>
#include <MyEngines.h>
#include <MyLogger.h>

#include <MyNN.h>

typedef struct {
	//-- common stuff
	double**	a;
	double**	F;
	double**	dF;
	double*		e;
	double*		u;
	double*		Ve;
	double*		Vu;
	double***	W;
	double***	dW;
	double***   dJdW;
	double***   BPdW;
	double*		dk;
	double**	prevF;
	double**	prevdF;
	double***	prevW;
	double***	prevdW;
	double***	prevdJdW;
	double***	prevBPdW;
	int			BPCount;
	//-- CFR/AG stuff
	double**	c;
	double***	d;
	double***	g;
	double***	B;
	double**	prevc;
	double***	prevd;
	double***	prevg;
	double***	prevB;
	//-- Qing stuff
	double** adzev;
	double*  ro;
	int*  sigma;
	double* uW;
	double* tmpV1;
	double* ux;
	double** dxdW10;
	//-- CGD stuff
	double*  cgd_sigma;
	double*  cgd_lambda;
	double*  cgd_lambdau;
	double*  cgd_delta;
	double** cgd_s;
	double** cgd_p;
	double** cgd_r;
	double** cgd_sigmap;
	double** cgd_newW;
	double** cgd_tmpV1;
	double** cgd_tmpV2;
	double** cgd_tmpV3;
	double** cgd_tmpV4;
	double* beta;
	//-- temp matrices, sized using the largest possible dimensions.
	double*** tmpM1;
	double*** tmpM2;
	double*** tmpM3;
	double*** tmpM4;
	double*** tmpM5;
	double*** tmpM6;
	double*** tmpM7;
	double*** tmpM8;
	double*** tmpM9;
	double*** tmpM10;
	double*** tmpM11;
	double*** tmpM12;
	double*** tmpM13;
	double*** tmpM14;
	double*** tmpM15;
	double*** tmpM16;
	double**  G;
} tMxData;

typedef struct {
	tDebugInfo* DebugParms;  NN_Parms* NNParms;
	int SampleCount; double** Sample; double** Target; double** SampleV; double** TargetV;
	int TestId; int DataSetId; int NetId;
	tMxData* MxData;
	tEngineHandle TrainInfo;
	tDataShape* InputData;
} tTrainParams;

void SaveMSEData(NN_Parms* NNParms, int pNetId, DWORD pid, DWORD tid, int pDataSet, int pTestId, int pEpoch, double pMSE_T, double pMSE_V){
	NNParms->MSEOutput[pDataSet][pNetId][pEpoch].ProcessId = pid;
	NNParms->MSEOutput[pDataSet][pNetId][pEpoch].ThreadId = tid;
	NNParms->MSEOutput[pDataSet][pNetId][pEpoch].TestId = pTestId;
	NNParms->MSEOutput[pDataSet][pNetId][pEpoch].Epoch = pEpoch;
	NNParms->MSEOutput[pDataSet][pNetId][pEpoch].MSE_T = pMSE_T;
	NNParms->MSEOutput[pDataSet][pNetId][pEpoch].MSE_V = pMSE_V;
}

void SaveRunData(NN_Parms* NNParms, int pNetId, DWORD pid, DWORD tid, int pDataSet, int pTestId, int pPos, int pOOSPos, double pActual, double pPredicted){
	NNParms->RunOutput[pDataSet][pNetId][pPos].ProcessId = pid;
	NNParms->RunOutput[pDataSet][pNetId][pPos].ThreadId = tid;
	NNParms->RunOutput[pDataSet][pNetId][pPos].TestId = pTestId;
	NNParms->RunOutput[pDataSet][pNetId][pPos].Pos = pPos;
	NNParms->RunOutput[pDataSet][pNetId][pPos].OOSPos = pOOSPos;
	NNParms->RunOutput[pDataSet][pNetId][pPos].Actual = pActual;
	NNParms->RunOutput[pDataSet][pNetId][pPos].Predicted = pPredicted;
}

void NNSave(NN_Parms* NNParms, int pNetId, DWORD pid, DWORD tid, int pDataSet, int pTestId, double*** W, double* F0){
	//-- This should be called only once at the end of training
	//-- a1 is passed to take care of Context neurons 
	int i, j, k;
	//-- L10 Weights
	for (j = 0; j < NNParms->L1cnt; j++){
		for (i = 0; i < NNParms->L0cnt; i++){
			NNParms->FinalW[pDataSet][pNetId][L10][j][i].ProcessId = pid;
			NNParms->FinalW[pDataSet][pNetId][L10][j][i].ThreadId = tid;
			NNParms->FinalW[pDataSet][pNetId][L10][j][i].TestId = pTestId;
			NNParms->FinalW[pDataSet][pNetId][L10][j][i].Level = L10;
			NNParms->FinalW[pDataSet][pNetId][L10][j][i].FromNeuron = j;
			NNParms->FinalW[pDataSet][pNetId][L10][j][i].ToNeuron = i;
			NNParms->FinalW[pDataSet][pNetId][L10][j][i].Weight = W[L10][j][i];
			//-- Context neurons
			NNParms->FinalW[pDataSet][pNetId][L10][j][i].CtxValue = (i >= NNParms->InputCount) ? F0[i] : 0;
		}
	}
	//-- L21 Weights
	for (k = 0; k < NNParms->L2cnt; k++){
		for (j = 0; j < NNParms->L1cnt; j++){
			NNParms->FinalW[pDataSet][pNetId][L21][k][j].ProcessId = pid;
			NNParms->FinalW[pDataSet][pNetId][L21][k][j].ThreadId = tid;
			NNParms->FinalW[pDataSet][pNetId][L21][k][j].TestId = pTestId;
			NNParms->FinalW[pDataSet][pNetId][L21][k][j].Level = L21;
			NNParms->FinalW[pDataSet][pNetId][L21][k][j].FromNeuron = k;
			NNParms->FinalW[pDataSet][pNetId][L21][k][j].ToNeuron = j;
			NNParms->FinalW[pDataSet][pNetId][L21][k][j].Weight = W[L21][k][j];
		}
	}
}

void SaveInternalsData(NN_Parms* NNParms, int pNetId, DWORD pid, DWORD tid, int pDataSet, int pTestId, int pEpoch, int pSampleId, int sigma10, double ro10, double D10W, double adzev10, int hcp10, int sigma21, double ro21, double adzev21N, double norm_e, double* F10, double* F21){
	NNParms->IntOutput[pDataSet][pNetId][pEpoch][pSampleId].ProcessId = pid;
	NNParms->IntOutput[pDataSet][pNetId][pEpoch][pSampleId].ThreadId = tid;
	NNParms->IntOutput[pDataSet][pNetId][pEpoch][pSampleId].TestId = pTestId;
	NNParms->IntOutput[pDataSet][pNetId][pEpoch][pSampleId].Epoch = pEpoch;
	NNParms->IntOutput[pDataSet][pNetId][pEpoch][pSampleId].SampleId = pSampleId;
	NNParms->IntOutput[pDataSet][pNetId][pEpoch][pSampleId].sigma10 = sigma10;
	NNParms->IntOutput[pDataSet][pNetId][pEpoch][pSampleId].ro10 = ro10;
	NNParms->IntOutput[pDataSet][pNetId][pEpoch][pSampleId].D10W = D10W;
	NNParms->IntOutput[pDataSet][pNetId][pEpoch][pSampleId].adzev10 = adzev10;
	NNParms->IntOutput[pDataSet][pNetId][pEpoch][pSampleId].hcp10 = hcp10;
	NNParms->IntOutput[pDataSet][pNetId][pEpoch][pSampleId].sigma21 = sigma21;
	NNParms->IntOutput[pDataSet][pNetId][pEpoch][pSampleId].ro21 = ro21;
	NNParms->IntOutput[pDataSet][pNetId][pEpoch][pSampleId].adzev21N = adzev21N;
	NNParms->IntOutput[pDataSet][pNetId][pEpoch][pSampleId].norm_e = norm_e;
	//NNParms->IntOutput[pDataSet][pNetId][pEpoch][pSampleId].F10 = F10;
	//NNParms->IntOutput[pDataSet][pNetId][pEpoch][pSampleId].F21 = F21;
}

void SavePrevNeurons(NN_Parms* NNParms, tMxData* Mx){
	int i, h, o;

	// L2 neurons
	for (o = 0; o < NNParms->L2cnt; o++){
		Mx->prevF[L2][o] = Mx->F[L2][o];
		Mx->prevdF[L2][o] = Mx->dF[L2][o];
		Mx->prevc[L2][o] = Mx->c[L2][o];
	}
	// L1 neurons
	for (h = 0; h < NNParms->L1cnt; h++){
		Mx->prevF[L1][h] = Mx->F[L1][h];
		Mx->prevdF[L1][h] = Mx->dF[L1][h];
		Mx->prevc[L1][h] = Mx->c[L1][h];
	}
	// L0 neurons
	for (i = 0; i < NNParms->L0cnt; i++){
		Mx->prevF[L0][i] = Mx->F[L0][i];
		Mx->prevdF[L0][i] = Mx->dF[L0][i];
		Mx->prevc[L0][1] = Mx->c[L0][i];
	}
}

void SavePrevWeights(NN_Parms* NNParms, tMxData* Mx){
	int i, h, o;

	// L21 connections
	for (o = 0; o < NNParms->L2cnt; o++){
		for (h = 0; h < NNParms->L1cnt; h++){
			Mx->prevW[L21][o][h] = Mx->W[L21][o][h];
			Mx->prevdW[L21][o][h] = Mx->dW[L21][o][h];
			Mx->prevdJdW[L21][o][h] = Mx->dJdW[L21][o][h];
			Mx->prevBPdW[L21][o][h] = Mx->BPdW[L21][o][h];
		}
	}
	// L10 connections
	for (h = 0; h < NNParms->L1cnt; h++){
		for (i = 0; i < NNParms->L0cnt; i++){
			Mx->prevW[L10][h][i] = Mx->W[L10][h][i];
			Mx->prevdW[L10][h][i] = Mx->dW[L10][h][i];
			Mx->prevdJdW[L10][h][i] = Mx->dJdW[L10][h][i];
			Mx->prevBPdW[L10][h][i] = Mx->BPdW[L10][h][i];
		}
	}
}

void Activate(int ActivationFunction, int NeuronCount, double* gain, double* INval, double* OUTval, double* dOUTval){
	double c = 4;	// Additional parameter used by activation functions
	for (int n = 0; n < NeuronCount; n++) {
		switch (ActivationFunction){
		case NN_ACTIVATION_STD:
			OUTval[n] = tanh(INval[n]);
			dOUTval[n] = 1 - tanh(INval[n])*tanh(INval[n]);
			break;
		case NN_ACTIVATION_RBF:
			OUTval[n] = 1 / sqrt(pow(INval[n], 2) + pow(c, 2));
			dOUTval[n] = -INval[n] / pow((pow(INval[n], 2) + pow(c, 2)), (3 / 2));
			break;
		case NN_ACTIVATION_GAIN:
			OUTval[n] = gain[n] * tanh(INval[n]);
			dOUTval[n] = gain[n] * (1 - tanh(gain[n] * INval[n])*tanh(gain[n] * INval[n]));
			break;
		}
	}
}

void FF_Std(NN_Parms* pNNParms, tMxData* Mx){
	//== Classic
/*	int i, h, o;
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
*/
	//== Matrix

	//-- Save previous Neurons
	SavePrevNeurons(pNNParms, Mx);
	//-- L0 -> L1
	MbyV(pNNParms->L1cnt, pNNParms->L0cnt, Mx->W[L10], false, Mx->F[L0], Mx->a[L1]);	// Qing (6)
	Activate(pNNParms->ActivationFunction, pNNParms->L1cnt, Mx->c[L1], Mx->a[L1], Mx->F[L1], Mx->dF[L1]);
	//-- L1 -> L2
	MbyV(pNNParms->L2cnt, pNNParms->L1cnt, Mx->W[L21], false, Mx->F[L1], Mx->a[L2]);	// Qing (2)
	Activate(pNNParms->ActivationFunction, pNNParms->L2cnt, Mx->c[L2], Mx->a[L2], Mx->F[L2], Mx->dF[L2]);
	//-- Hidden->Context
	for (int c = 0; c < pNNParms->ContextCount; c++) Mx->F[L0][pNNParms->InputCount + c] = Mx->F[L1][c];
}

void FF_RBF(NN_Parms* pNNParms, tMxData* Mx){
	int i, h, o;
	for (h = 0; h<pNNParms->HiddenCount; h++){
		Mx->a[L1][h] = 0;
		// Standard 
		for (i = 0; i < (pNNParms->InputCount + pNNParms->ContextCount); i++) Mx->a[L1][h] += Mx->F[L0][i] * Mx->W[L10][h][i];
		//--RBF
		Mx->a[L1][h] = VDistance((pNNParms->InputCount + pNNParms->ContextCount), Mx->W[L10][h], Mx->F[L0]);	// 230.pdf, 1.2
	}

	Activate(pNNParms->ActivationFunction, pNNParms->HiddenCount, Mx->c[L1], Mx->a[L1], Mx->F[L1], Mx->dF[L1]);
	for (o = 0; o < pNNParms->L2cnt; o++){
		Mx->a[L2][o] = 0;
		for (h = 0; h < pNNParms->HiddenCount; h++) Mx->a[L2][o] += Mx->F[L1][h] * Mx->W[L21][o][h];
	}
	Activate(pNNParms->ActivationFunction, pNNParms->L2cnt, Mx->c[L2], Mx->a[L2], Mx->F[L2], Mx->dF[L2]);
	//-- Hidden->Context
	for (int c = 0; c < pNNParms->ContextCount; c++) Mx->F[L0][pNNParms->InputCount + c] = Mx->F[L1][c];
}

void FF_Qing(NN_Parms* pNNParms, tMxData* Mx){
	//-- L0 -> L1
	MbyV(pNNParms->L1cnt, pNNParms->L0cnt, Mx->W[L10], false, Mx->F[L0], Mx->a[L1]);	// Qing (6)
	Activate(pNNParms->ActivationFunction, pNNParms->L1cnt, Mx->c[L1], Mx->a[L1], Mx->F[L1], Mx->dF[L1]);
	//-- L1 -> L2
	MbyV(pNNParms->L2cnt, pNNParms->L1cnt, Mx->W[L21], false, Mx->F[L1], Mx->a[L2]);	// Qing (2)
	Activate(pNNParms->ActivationFunction, pNNParms->L2cnt, Mx->c[L2], Mx->a[L2], Mx->F[L2], Mx->dF[L2]);
	//-- Hidden->Context
	for (int c = 0; c < pNNParms->ContextCount; c++) Mx->F[L0][pNNParms->InputCount + c] = Mx->F[L1][c];
}

void FF(NN_Parms* NNParms, tMxData* Mx){
	switch (NNParms->ActivationFunction){
	case NN_ACTIVATION_RBF:
		FF_RBF(NNParms, Mx);
		break;
	default:
		FF_Std(NNParms, Mx);
		break;
	}
	//-- Regardless of the method, here we update the network error
	VminusV(NNParms->L2cnt, Mx->u, Mx->F[L2], Mx->e);
}

void Qing_CalcG_OLD(NN_Parms* pNNParms, tMxData* Mx){
	// G should be <mn x n>
	int i, j, m;
	for (j = 0; j < pNNParms->L1cnt; j++){
		for (i = 0; i < pNNParms->L0cnt; i++){
			for (m = 0; m < pNNParms->L2cnt; m++){
				Mx->G[j*pNNParms->L0cnt + i][m] = 0;																// Qing (27) , <n> leftmost elements
			}
			for (m = 0; m < pNNParms->L1cnt; m++){
				Mx->G[j*pNNParms->L0cnt + i][pNNParms->L2cnt + m] = (Mx->F[L1][m] - Mx->prevF[L1][m]) / (Mx->W[L10][j][i] - Mx->prevW[L10][j][i]);	// Qing (27) , <m> rightmost elements
				//G[j*pNNParms->L0cnt + i][pNNParms->L2cnt + m] = Mx->prevF[L1][m] * Mx->prevF[L0][i];
			}
		}
	}
}

void Qing_CalcdxdW10(NN_Parms* pNNParms, tMxData* Mx){
	int i, h, n;
	//-- every W has its own Jacobian
	for (n = 0; n < pNNParms->L0cnt; n++){
		//-- single Jacobian for @x/@W1
		for (h = 0; h < pNNParms->L1cnt; h++){
			for (i = 0; i < pNNParms->ContextCount; i++){
				//Jacob[h][i] = Mx->prevdF[L10][h] * Mx->F[L0][pNNParms->InputCount + i];
				Mx->dxdW10[n*pNNParms->L1cnt+h][i] = Mx->prevdF[L10][h] * Mx->F[L0][pNNParms->InputCount + i];
			}
		}
	}
}

double Qing_CalcD10W(NN_Parms* pNNParms, tMxData* Mx){
	int j, i, l;
	double ret=0;

	//-- calc ux
	VbyV2M(pNNParms->L0cnt, Mx->F[L0], pNNParms->L0cnt, Mx->F[L0], Mx->tmpM11[L1]);
	//MInv(pNNParms->L0cnt, Mx->tmpM15[L1], Mx->tmpM15[L0]);	//-- use M15[L0] to hold inverted M15[L1]
	MbyV(pNNParms->L0cnt, pNNParms->L0cnt, Mx->tmpM11[L1], false, Mx->F[L0], Mx->ux);

	for (j = 0; j < pNNParms->L1cnt; j++){
		for (i = 0; i < pNNParms->L0cnt; i++){
			for (l = 0; l < pNNParms->L1cnt; l++){
				ret += Mx->prevF[L1][j] / Mx->prevW[L10][l][i] * Mx->W[L10][l][i] * Mx->ux[pNNParms->L2cnt + j] * Mx->prevF[L1][j];
			}
		}
	}
	return ret;
}

void Calc_dJdW21(NN_Parms* pNNParms, tMxData* Mx){
	//-- Setup data structures
	V2DiagM(pNNParms->L2cnt, Mx->dF[L2], Mx->tmpM1[L2]);														// tmpM1 stores F'(2,1)					[L2xL2]
	V2VertM(pNNParms->L2cnt, Mx->e, Mx->tmpM2[L2]);																// tmpM2 stores eT						[L2x1]
	V2HorM(pNNParms->L1cnt, Mx->F[L1], Mx->tmpM3[L2]);															// tmpM3 stores F(1,0)					[1xL1]
	//-- Save previous weights
	SavePrevWeights(pNNParms, Mx);
	//-- Standard BP, Qing(11)
	MbyM(pNNParms->L2cnt, pNNParms->L2cnt, pNNParms->L2cnt, 1, Mx->tmpM1[L2], Mx->tmpM2[L2], Mx->tmpM4[L2]);	// tmpM4 stores F'(2,1) X eT			[L2x1]
	MbyM(pNNParms->L2cnt, 1, 1, pNNParms->L1cnt, Mx->tmpM4[L2], Mx->tmpM3[L2], Mx->dJdW[L21]);					// dJdW stores F'(2,1) X eT X F(1,0)T	[L2xL1]
}

void Calc_dJdW10(NN_Parms* pNNParms, tMxData* Mx){
	//-- Setup data structures
	V2DiagM(pNNParms->L1cnt, Mx->dF[L1], Mx->tmpM7[L1]);																		// tmpM7 stores F'(1,0)									[L1xL1]
	Transpose(pNNParms->L2cnt, pNNParms->L1cnt, Mx->W[L21], Mx->tmpM8[L1]);														// tmpM8 stores W(2,1)T									[L1xL2]
	V2HorM(pNNParms->L0cnt, Mx->F[L0], Mx->tmpM9[L1]);																			// tmpM9 stores xT										[1xL0]
	//-- Save previous weights
	SavePrevWeights(pNNParms, Mx);
	//-- Qing(12)
	MbyM(pNNParms->L1cnt, pNNParms->L1cnt, pNNParms->L1cnt, pNNParms->L2cnt, Mx->tmpM7[L1], Mx->tmpM8[L1], Mx->tmpM10[L1]);		// tmpM10 stores F'(1,0) X W(2,1)T						[L1xL2]
	MbyM(pNNParms->L1cnt, pNNParms->L2cnt, pNNParms->L2cnt, 1, Mx->tmpM10[L1], Mx->tmpM4[L2], Mx->tmpM11[L1]);					// tmpM11 stores F'(1,0) X W(2,1)T X F'(2,1) X eT		[L1x1]
	MbyM(pNNParms->L1cnt, 1, 1, pNNParms->L0cnt, Mx->tmpM11[L1], Mx->tmpM9[L1], Mx->dJdW[L10]);								// tmpM12 stores F'(1,0) X W(2,1)T X F'(2,1) X eT X xT	[L1xL0]
}
/*
void BP_cgd(int pid, int tid, tDebugInfo* DebugParms, NN_Parms* pNNParms, int pNetId, int pDataSetId, int TestId, int Epoch, int SampleId, tMxData* Mx){
	double pnorm;
	double sigma, mu, alpha, beta;
	double comp;
	bool success;
	int o, h;

	//-- L21
	for (o = 0; o < pNNParms->L2cnt; o++){
		//-- 0. Init
		Mx->cgd_sigma[L21] = 0.0001;
		Mx->cgd_lambda[L21] = 0.000001;
		Mx->cgd_lambdau[L21] = 0.000001;

		//=== 1.
		//-- Calc dE/dW at current W (stored in Mx->dJdW):
		Calc_dJdW21(pNNParms, Mx);
		//-- Choose weight vector w1, and save its original value in cgd_tmpV1)
		VCopy(pNNParms->L1cnt, Mx->W[L21][o], Mx->cgd_tmpV1[L21]);
		//-- set p=-dJdW at current w1:
		VCopy(pNNParms->L1cnt, Mx->cgd_tmpV1[L21], Mx->cgd_p[L21]); VbyS(pNNParms->L1cnt, Mx->cgd_p[L21], -1,  Mx->cgd_p[L21]);
		//-- r=p
		VCopy(pNNParms->L1cnt, Mx->cgd_p[L21], Mx->cgd_r[L21]);
		//-- save E(w) in tmpV4
		VCopy(pNNParms->L2cnt, Mx->e, Mx->cgd_tmpV4[L21]);
		success = true;

		//=== 2.
		pnorm = Vnorm(pNNParms->L2cnt, Mx->cgd_p[L21]);
		Mx->cgd_sigma[L21] = Mx->cgd_sigma[L21] / pnorm;

		//-- calc new W into Mx->W
			//-- pick one W (e.g. W[L21][o] )
		//-- calc new W = W + sigma* p
		VbyS(pNNParms->L1cnt, Mx->cgd_p[L21], Mx->cgd_sigma[L21], Mx->cgd_tmpV2[L21]);
		VplusV(pNNParms->L1cnt, Mx->W[L21][o], Mx->cgd_tmpV2[L21], Mx->cgd_newW[L21]);
		//-- copy newW back into W
		VCopy(pNNParms->L1cnt, Mx->cgd_newW[L21], Mx->W[L21][o]);
		//-- Calc dE/dW at new W (NEED TO FeedForward, first):
		FF(pNNParms, Mx);
		Calc_dJdW21(pNNParms, Mx);
		//-- FF to refresh e
		FF(pNNParms, Mx);
		//-- save E(w)

		//-- Calc difference in dE/dW between before and after change , and store it in cgd_tmpV3:
		VminusV(pNNParms->L2cnt, Mx->dJdW[L21][o], Mx->prevdJdW[L21][o], Mx->cgd_tmpV3[L21]);
		//-- divide by sigma (Element-by-element)
		VdivS(pNNParms->L2cnt, Mx->cgd_tmpV3[L21], Mx->cgd_sigma[L21], Mx->cgd_s[L21]);
		//-- delta = p * s
		Mx->cgd_delta[L21] = VdotV(pNNParms->L2cnt, Mx->cgd_p[L21], Mx->cgd_s[L21]);

		//=== 3.
		Mx->cgd_delta[L21] += (Mx->cgd_lambda[L21]-Mx->cgd_lambdau[L21])*pow(pnorm, 2);

		//=== 4.
		if (Mx->cgd_delta[L21] <= 0){
			Mx->cgd_lambdau[L21] = 2 * (Mx->cgd_lambda[L21]-Mx->cgd_delta[L21]/pow(pnorm,2));
			Mx->cgd_delta[L21] = -Mx->cgd_delta[L21]+Mx->cgd_lambda[L21]*pow(pnorm,2);
			Mx->cgd_lambda[L21] = Mx->cgd_lambdau[L21];
		}

		//=== 5.
		mu = VdotV(pNNParms->L2cnt, Mx->cgd_p[L21], Mx->cgd_r[L21]);
		alpha = mu / Mx->cgd_delta[L21];

		//=== 6.
		//-- calc alpha*p into tmpV2
		VbyS(pNNParms->L1cnt, Mx->cgd_p[L21], alpha, Mx->cgd_tmpV2[L21]);
		//-- set newW=W+alpha*p
		VplusV(pNNParms->L1cnt, Mx->W[L21][o], Mx->cgd_tmpV2[L21], Mx->cgd_newW[L21]);
		//-- copy newW back into W
		VCopy(pNNParms->L1cnt, Mx->cgd_newW[L21], Mx->W[L21][o]);
		//-- Calc dE/dW at new W (NEED TO FeedForward, first):
		FF_Std(pNNParms, Mx);
		Calc_dJdW21(pNNParms, Mx);
		//-- FF to refresh e
		FF(pNNParms, Mx);
		//-- calc E(w) - E(w+alpha*p)
		comp = 2 * Mx->cgd_delta[L21] * (Vnorm(pNNParms->L2cnt, Mx->cgd_tmpV4[L21]) - Vnorm(pNNParms->L2cnt, Mx->e) ) / mu;

		//=== 7.
		if (comp>=0){
			//-- Wk+1 = Wk+Alphak*pk
			VplusV(pNNParms->L1cnt, Mx->W[L21][o], Mx->cgd_tmpV2[L21], Mx->W[L21][o]);
			//-- save r(k) in cgd_tmpV3
			VCopy(pNNParms->L1cnt, Mx->cgd_r[L21], Mx->cgd_tmpV3[L21]);
			//-- r(k+1) = -E(Wk+1)
			FF(pNNParms, Mx); VCopy(pNNParms->L2cnt, Mx->e, Mx->cgd_r[L21]); VbyS(pNNParms->L2cnt, Mx->cgd_r[L21], -1, Mx->cgd_r[L21]);
			//--
			Mx->cgd_lambdau[L21] = 0;
			success = true;
			//=== 7.a
			if (Epoch>0 && (Epoch % (pNNParms->L2cnt*pNNParms->L1cnt) == 0)){
				//-- Restart algorithm
				VCopy(pNNParms->L2cnt, Mx->cgd_r[L21], Mx->cgd_p[L21]);
				Mx->cgd_lambda[L21] = 0.5;
			}
			else{
				//-- Create new conjugate direction
				beta = (pow(Vnorm(pNNParms->L1cnt, Mx->cgd_r[L21]), 2) -VdotV(pNNParms->L1cnt, Mx->cgd_tmpV3[L21], Mx->cgd_r[L21]) )/ mu;
				VbyS(pNNParms->L1cnt, Mx->cgd_p[L21], beta, Mx->cgd_tmpV3[L21]);
				VplusV(pNNParms->L1cnt, Mx->cgd_r[L21], Mx->cgd_tmpV3[L21], Mx->cgd_p[L21]);
			}
			//=== 7.b
			if (comp >= 0.75) Mx->cgd_lambda[L21] = Mx->cgd_lambda[L21] / 4;

			//=== 8.
			if (comp < 0.75) Mx->cgd_lambda[L21] += Mx->cgd_delta[L21] * (1 - comp) / pow(pnorm, 2);
		}
	}

	//-- L10
	for (h = 0; h < pNNParms->L1cnt; h++){
		//-- 0. Init
		Mx->cgd_sigma[L10] = 0.0001;
		Mx->cgd_lambda[L10] = 0.000001;
		Mx->cgd_lambdau[L10] = 0.000001;

		//=== 1.
		//-- Calc dE/dW at current W (stored in Mx->dJdW):
		Calc_dJdW21(pNNParms, Mx);
		//-- Choose weight vector w1, and save its original value in cgd_tmpV1)
		VCopy(pNNParms->L0cnt, Mx->W[L10][h], Mx->cgd_tmpV1[L10]);
		//-- set p=-dJdW at current w1:
		VCopy(pNNParms->L0cnt, Mx->cgd_tmpV1[L10], Mx->cgd_p[L10]); VbyS(pNNParms->L0cnt, Mx->cgd_p[L10], -1, Mx->cgd_p[L10]);
		//-- r=p
		VCopy(pNNParms->L0cnt, Mx->cgd_p[L10], Mx->cgd_r[L10]);
		//-- save E(w) in tmpV4
		VCopy(pNNParms->L1cnt, Mx->e, Mx->cgd_tmpV4[L10]);
		success = true;

		//=== 2.
		pnorm = Vnorm(pNNParms->L1cnt, Mx->cgd_p[L10]);
		Mx->cgd_sigma[L10] = Mx->cgd_sigma[L10] / pnorm;

		//-- calc new W into Mx->W
		//-- pick one W (e.g. W[L10][h] )
		//-- calc new W = W + sigma* p
		VbyS(pNNParms->L0cnt, Mx->cgd_p[L10], Mx->cgd_sigma[L10], Mx->cgd_tmpV2[L10]);
		VplusV(pNNParms->L0cnt, Mx->W[L10][h], Mx->cgd_tmpV2[L10], Mx->cgd_newW[L10]);
		//-- copy newW back into W
		VCopy(pNNParms->L0cnt, Mx->cgd_newW[L10], Mx->W[L10][h]);
		//-- Calc dE/dW at new W (NEED TO FeedForward, first):
		FF(pNNParms, Mx);
		Calc_dJdW21(pNNParms, Mx);
		//-- FF to refresh e
		FF(pNNParms, Mx);
		//-- save E(w)

		//-- Calc difference in dE/dW between before and after change , and store it in cgd_tmpV3:
		VminusV(pNNParms->L1cnt, Mx->dJdW[L10][h], Mx->prevdJdW[L10][h], Mx->cgd_tmpV3[L10]);
		//-- divide by sigma (Element-by-element)
		VdivS(pNNParms->L1cnt, Mx->cgd_tmpV3[L10], Mx->cgd_sigma[L10], Mx->cgd_s[L10]);
		//-- delta = p * s
		Mx->cgd_delta[L10] = VdotV(pNNParms->L1cnt, Mx->cgd_p[L10], Mx->cgd_s[L10]);

		//=== 3.
		Mx->cgd_delta[L10] += (Mx->cgd_lambda[L10] - Mx->cgd_lambdau[L10])*pow(pnorm, 2);

		//=== 4.
		if (Mx->cgd_delta[L10] <= 0){
			Mx->cgd_lambdau[L10] = 2 * (Mx->cgd_lambda[L10] - Mx->cgd_delta[L10] / pow(pnorm, 2));
			Mx->cgd_delta[L10] = -Mx->cgd_delta[L10] + Mx->cgd_lambda[L10] * pow(pnorm, 2);
			Mx->cgd_lambda[L10] = Mx->cgd_lambdau[L10];
		}

		//=== 5.
		mu = VdotV(pNNParms->L1cnt, Mx->cgd_p[L10], Mx->cgd_r[L10]);
		alpha = mu / Mx->cgd_delta[L10];

		//=== 6.
		//-- calc alpha*p into tmpV2
		VbyS(pNNParms->L0cnt, Mx->cgd_p[L10], alpha, Mx->cgd_tmpV2[L10]);
		//-- set newW=W+alpha*p
		VplusV(pNNParms->L0cnt, Mx->W[L10][h], Mx->cgd_tmpV2[L10], Mx->cgd_newW[L10]);
		//-- copy newW back into W
		VCopy(pNNParms->L0cnt, Mx->cgd_newW[L10], Mx->W[L10][h]);
		//-- Calc dE/dW at new W (NEED TO FeedForward, first):
		FF_Std(pNNParms, Mx);
		Calc_dJdW21(pNNParms, Mx);
		//-- FF to refresh e
		FF(pNNParms, Mx);
		//-- calc E(w) - E(w+alpha*p)
		comp = 2 * Mx->cgd_delta[L10] * (Vnorm(pNNParms->L1cnt, Mx->cgd_tmpV4[L10]) - Vnorm(pNNParms->L1cnt, Mx->e)) / mu;

		//=== 7.
		if (comp >= 0){
			//-- Wk+1 = Wk+Alphak*pk
			VplusV(pNNParms->L0cnt, Mx->W[L10][h], Mx->cgd_tmpV2[L10], Mx->W[L10][h]);
			//-- save r(k) in cgd_tmpV3
			VCopy(pNNParms->L0cnt, Mx->cgd_r[L10], Mx->cgd_tmpV3[L10]);
			//-- r(k+1) = -E(Wk+1)
			FF(pNNParms, Mx); VCopy(pNNParms->L1cnt, Mx->e, Mx->cgd_r[L10]); VbyS(pNNParms->L1cnt, Mx->cgd_r[L10], -1, Mx->cgd_r[L10]);
			//--
			Mx->cgd_lambdau[L10] = 0;
			success = true;
			//=== 7.a
			if (Epoch>0 && (Epoch % (pNNParms->L1cnt*pNNParms->L0cnt) == 0)){
				//-- Restart algorithm
				VCopy(pNNParms->L1cnt, Mx->cgd_r[L10], Mx->cgd_p[L10]);
				Mx->cgd_lambda[L10] = 0.5;
			}
			else{
				//-- Create new conjugate direction
				beta = (pow(Vnorm(pNNParms->L0cnt, Mx->cgd_r[L10]), 2) - VdotV(pNNParms->L0cnt, Mx->cgd_tmpV3[L10], Mx->cgd_r[L10])) / mu;
				VbyS(pNNParms->L0cnt, Mx->cgd_p[L10], beta, Mx->cgd_tmpV3[L10]);
				VplusV(pNNParms->L0cnt, Mx->cgd_r[L10], Mx->cgd_tmpV3[L10], Mx->cgd_p[L10]);
			}
			//=== 7.b
			if (comp >= 0.75) Mx->cgd_lambda[L10] = Mx->cgd_lambda[L10] / 4;

			//=== 8.
			if (comp < 0.75) Mx->cgd_lambda[L10] += Mx->cgd_delta[L10] * (1 - comp) / pow(pnorm, 2);
		}
	}
}
*/
void BP_QuickProp(int pid, int tid, tDebugInfo* DebugParms, NN_Parms* pNNParms, int pNetId, int pDataSetId, int TestId, int Epoch, int SampleId, tMxData* Mx){
	//-- as per QuickProp2.pdf, 2.6.3	
	int i, h, o;
	double sk;

	//-- L2 -> L1
	for (o = 0; o < pNNParms->L2cnt; o++){
		for (h = 0; h < pNNParms->L1cnt; h++){
			Mx->dk[o] = (Mx->u[o] - Mx->F[L2][o])*Mx->dF[L2][o];
			Mx->dJdW[L21][o][h] = Mx->dk[o] * Mx->F[L1][h];

			Mx->dW[L21][o][h] = pNNParms->LearningRate*Mx->dJdW[L21][o][h];
			if (Mx->dW[L21][o][h]>0){
				if (Mx->dJdW[L21][o][h]>(pNNParms->mu / (1 + pNNParms->mu)*Mx->prevdJdW[L21][o][h])){
					Mx->dW[L21][o][h] = pNNParms->mu*Mx->dW[L21][o][h];
				}
				else{
					Mx->dW[L21][o][h] = Mx->dJdW[L21][o][h] / (Mx->prevdJdW[L21][o][h] - Mx->dJdW[L21][o][h])*Mx->dW[L21][o][h];
				}
				if (Mx->dJdW[L21][o][h]>0) Mx->dW[L21][o][h] += pNNParms->LearningRate*Mx->dJdW[L21][o][h];
			}
			else if (Mx->dW[L21][o][h]<0){
				if (Mx->dJdW[L21][o][h]<(pNNParms->mu / (1 + pNNParms->mu)*Mx->prevdJdW[L21][o][h])){
					Mx->dW[L21][o][h] = pNNParms->mu*Mx->dW[L21][o][h];
				}
				else{
					Mx->dW[L21][o][h] = Mx->dJdW[L21][o][h] / (Mx->prevdJdW[L21][o][h] - Mx->dJdW[L21][o][h])*Mx->dW[L21][o][h];
				}
				if (Mx->dJdW[L21][o][h]<0) Mx->dW[L21][o][h] += pNNParms->LearningRate*Mx->dJdW[L21][o][h];
			}
			else if (Mx->dW[L21][o][h] == 0){
				Mx->dW[L21][o][h] += pNNParms->LearningRate*Mx->dJdW[L21][o][h];
			}

			Mx->W[L21][o][h] += Mx->dW[L21][o][h];
		}
	}
	//-- L1 -> L0
	for (h = 0; h < pNNParms->L1cnt; h++){
		for (i = 0; i < pNNParms->L0cnt; i++){
			sk = 0;
			for (o = 0; o < pNNParms->L2cnt; o++) sk += Mx->W[L21][o][h] * Mx->dk[o];
			Mx->dJdW[L10][h][i] = sk*Mx->dF[L1][h] * Mx->F[L0][i];

			Mx->dW[L10][h][i] = pNNParms->LearningRate*Mx->dJdW[L10][h][i];
			if (Mx->dW[L10][h][i]>0){
				if (Mx->dJdW[L10][h][i]>(pNNParms->mu / (1 + pNNParms->mu)*Mx->prevdJdW[L10][h][i])){
					Mx->dW[L10][h][i] = pNNParms->mu*Mx->dW[L10][h][i];
				}
				else{
					Mx->dW[L10][h][i] = Mx->dJdW[L10][h][i] / (Mx->prevdJdW[L10][h][i] - Mx->dJdW[L10][h][i])*Mx->dW[L10][h][i];
				}
				if (Mx->dJdW[L10][h][i]>0) Mx->dW[L10][h][i] += pNNParms->LearningRate*Mx->dJdW[L10][h][i];
			}
			else if (Mx->dW[L10][h][i]<0){
				if (Mx->dJdW[L10][h][i]<(pNNParms->mu / (1 + pNNParms->mu)*Mx->prevdJdW[L10][h][i])){
					Mx->dW[L10][h][i] = pNNParms->mu*Mx->dW[L10][h][i];
				}
				else{
					Mx->dW[L10][h][i] = Mx->dJdW[L10][h][i] / (Mx->prevdJdW[L10][h][i] - Mx->dJdW[L10][h][i])*Mx->dW[L10][h][i];
				}
				if (Mx->dJdW[L10][h][i]<0) Mx->dW[L10][h][i] += pNNParms->LearningRate*Mx->dJdW[L10][h][i];
			}
			else if (Mx->dW[L10][h][i] == 0){
				Mx->dW[L10][h][i] += pNNParms->LearningRate*Mx->dJdW[L10][h][i];
			}

			Mx->W[L10][h][i] += Mx->dW[L10][h][i];
		}
	}
}

void BP_Qing(int pid, int tid, tDebugInfo* DebugParms, NN_Parms* pNNParms, int pNetId, int pDataSetId, int TestId, int Epoch, int SampleId, tMxData* Mx){
	int o;
	double adzev21norm, etnorm;
	int hcp;
	double D10W;

	//-- L2->L1
	V2DiagM(pNNParms->L2cnt, Mx->dF[L2], Mx->tmpM1[L2]);														// tmpM1[L2] stores F'(2,1)					[L2xL2]
	V2VertM(pNNParms->L2cnt, Mx->e, Mx->tmpM2[L2]);																// tmpM2[L2] stores eT						[L2x1]
	V2HorM(pNNParms->L1cnt, Mx->F[L1], Mx->tmpM3[L2]);															// tmpM3[L2] stores F(1,0)					[1xL1]
	//-- Standard BP, Qing(11)
	MbyM(pNNParms->L2cnt, pNNParms->L2cnt, pNNParms->L2cnt, 1, Mx->tmpM1[L2], Mx->tmpM2[L2], Mx->tmpM4[L2]);	// tmpM4[L2] stores F'(2,1) X eT			[L2x1]
	MbyM(pNNParms->L2cnt, 1, 1, pNNParms->L1cnt, Mx->tmpM4[L2], Mx->tmpM3[L2], Mx->tmpM5[L2]);					// tmpM5[L2] stores F'(2,1) X eT X F(1,0)T	[L2xL1]
	MbyS(pNNParms->L2cnt, pNNParms->L1cnt, Mx->tmpM5[L2], pNNParms->LearningRate, Mx->tmpM6[L2]);				// tmpM6[L2] stores dW21 from simple BP		[L2xL1]
	//--

	//-- calc ro[L21]
	//Mx->ro[L21] = (1 + pow(Vnorm(pNNParms->L1cnt, Mx->F[L1]), 2)*pow(Vnorm(pNNParms->L2cnt, Mx->dF[L2]), 2) / (Vmin_NoZero(pNNParms->L2cnt, Mx->dF[L2])));	// Qing(18)
	Mx->ro[L21] = (1 + pow(Vnorm(pNNParms->L1cnt, Mx->dF[L1]), 2)*pow(Vnorm(pNNParms->L2cnt, Mx->dF[L2]), 2) / (Vmin_NoZero(pNNParms->L2cnt, Mx->dF[L2])));	// Qing(18)
	//-- calc sigma[L21]
	Mx->sigma[L21] = (Vnorm(pNNParms->L2cnt, Mx->e) < Vnorm(pNNParms->L2cnt, Mx->adzev[L21]))?0:1;															// Qing(17)
	//-- calc adzev[L21]
	for (o = 0; o < pNNParms->L2cnt; o++) Mx->adzev[L21][o] += Mx->sigma[L21] / Mx->ro[L21] * abs(Mx->e[o]);												// Qing(16)
	//--temporary
	adzev21norm = Vnorm(pNNParms->L2cnt, Mx->adzev[L21]);
	etnorm = Vnorm(pNNParms->L2cnt, Mx->e);
	//--
	MbyS(pNNParms->L2cnt, pNNParms->L1cnt, Mx->tmpM5[L2], Mx->sigma[L21] / Mx->ro[L21], Mx->tmpM6[L2]);			// tmpM6 stores dW21 from Qing 		[L2xL1]

	//-- add
	//MplusM(pNNParms->L2cnt, pNNParms->L1cnt, Mx->W[L21], Mx->tmpM6[L0], Mx->W[L21]);	// simple BP
	MplusM(pNNParms->L2cnt, pNNParms->L1cnt, Mx->W[L21], Mx->tmpM6[L2], Mx->W[L21]);	// Qing BP

	//---------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

	//-- L1->L0
	V2DiagM(pNNParms->L1cnt, Mx->dF[L1], Mx->tmpM1[L1]);																		// tmpM1[L1] stores F'(1,0)								[L1xL1]
	Transpose(pNNParms->L2cnt, pNNParms->L1cnt, Mx->W[L21], Mx->tmpM2[L1]);														// tmpM2[L1] stores W(2,1)T								[L1xL2]
	V2HorM(pNNParms->L0cnt, Mx->F[L0], Mx->tmpM3[L1]);																			// tmpM3[L1] stores xT									[1xL0]
	//-- Qing(12)
	MbyM(pNNParms->L1cnt, pNNParms->L1cnt, pNNParms->L1cnt, pNNParms->L2cnt, Mx->tmpM1[L1], Mx->tmpM2[L1], Mx->tmpM4[L1]);		// tmpM4[L1] stores F'(1,0) X W(2,1)T					[L1xL2]
	MbyM(pNNParms->L1cnt, pNNParms->L2cnt, pNNParms->L2cnt, 1, Mx->tmpM4[L1], Mx->tmpM4[L2], Mx->tmpM5[L1]);					// tmpM5[L1] stores F'(1,0) X W(2,1)T X F'(2,1) X eT	[L1x1]
	MbyM(pNNParms->L1cnt, 1, 1, pNNParms->L0cnt, Mx->tmpM5[L1], Mx->tmpM3[L1], Mx->tmpM6[L1]);									// tmpM6[L1] stores F'(1,0) X W(2,1)T X F'(2,1) X eT X xT	[L1xL0]
	//MbyS(pNNParms->L1cnt, pNNParms->L0cnt, Mx->tmpM12[L1], pNNParms->LearningRate, Mx->tmpM13[L1]);							// tmpM13 stores dW10 from simple BP					[L1xL0]
	//--

	//-- populate uW
	M2LVV(pNNParms->L1cnt, pNNParms->L0cnt, Mx->W[L10], Mx->uW);																// uW is [1xL1L0]
	//-- calc ro[L10]
	MbyM(pNNParms->L1cnt, pNNParms->L2cnt, pNNParms->L2cnt, pNNParms->L2cnt, Mx->tmpM4[L1], Mx->tmpM1[L2], Mx->tmpM7[L1]);		// tmpM7[L1] stores F'(1,0) X W(2,1)T X F'(2,1)			[L1xL2]
	VExtend(pNNParms->L0cnt, Mx->F[L0], (pNNParms->L1cnt*pNNParms->L0cnt), Mx->uW, Mx->tmpV1);									// Mx->tmpV1 stores Qing (28), third element
	Mx->ro[L10] = (pow(Mnorm(pNNParms->L1cnt, pNNParms->L2cnt, Mx->tmpM2[L1]), 2) * pow(Vnorm(pNNParms->L1cnt*pNNParms->L0cnt, Mx->tmpV1), 2)) / (2 * Vmin_NoZero(pNNParms->L1cnt, Mx->dF[L1])*Vmin_NoZero(pNNParms->L2cnt, Mx->dF[L2]));
	//-- calc sigma[L10]
	Mx->sigma[L10] = (Vnorm(pNNParms->L2cnt, Mx->e) < Mx->adzev[L10][0])?0:1;													// Qing(21)
	//-- calc adzev[L10]
	for (o = 0; o < pNNParms->L2cnt; o++) Mx->adzev[L10][0] += Mx->sigma[L10] / Mx->ro[L10] * abs(Mx->e[o]);					// Qing(20)
	//-- calc D10W
	D10W = Qing_CalcD10W(pNNParms, Mx);	
	//-- calc hcp
	hcp = ((D10W>pNNParms->HCPbeta) || (D10W < 0))?0:1;																			// Qing(22)
	//-- calc extended gradient
	Qing_CalcdxdW10(pNNParms, Mx);
	//-- Qing(24)
	V2HorM((pNNParms->L1cnt*pNNParms->L0cnt), Mx->uW, Mx->tmpM8[L1]);																							// tmpM8[L1] stores uW vector into 1-row matrix				[1xL1L0]
	MbyM(pNNParms->L1cnt, 1, 1, pNNParms->L0cnt, Mx->tmpM5[L1], Mx->tmpM8[L1], Mx->tmpM9[L1]);																	// tmpM9[L1] stores F'(1,0) X W(2,1)T X F'(2,1) X eT X uW	[L1xL1L0]
	MbyM(pNNParms->L1cnt, (pNNParms->L1cnt*pNNParms->L0cnt), (pNNParms->L1cnt*pNNParms->L0cnt), pNNParms->L0cnt, Mx->tmpM9[L1], Mx->dxdW10, Mx->tmpM10[L1]);	// tmpM10[L1] stores Qing(24)								[L1xL0]

	MbyS(pNNParms->L1cnt, pNNParms->L0cnt, Mx->tmpM15[L1], Mx->sigma[L10] / Mx->ro[L10], Mx->tmpM10[L1]);														// Qing(19) complete with extended gradient tmpM10[L1] [L1xL0]

	MplusM(pNNParms->L1cnt, pNNParms->L0cnt, Mx->tmpM16[L1], Mx->W[L10], Mx->W[L10]);								// add dW10 to W10

	SaveInternalsData(pNNParms, 0, pid, tid, pDataSetId, TestId, Epoch, SampleId, Mx->sigma[L10], Mx->ro[L10], D10W, Mx->adzev[L10][0], hcp, Mx->sigma[L21], Mx->ro[L21], adzev21norm, etnorm, 0, 0);
}

void BP_cgd(int pid, int tid, tDebugInfo* DebugParms, NN_Parms* pNNParms, int pNetId, int pDataSetId, int TestId, int Epoch, int SampleId, tMxData* Mx){
	int i, h, o;
	double sk;

	//-- L2 -> L1
	for (o = 0; o < pNNParms->L2cnt; o++){
		for (h = 0; h < pNNParms->HiddenCount; h++){
			Mx->dk[o] = Mx->e[o] * Mx->dF[L2][o];
			Mx->dJdW[L21][o][h] = Mx->dk[o] * Mx->F[L1][h];

			Mx->beta[L21] = (Mx->BPCount==0)?0:pow(Mx->dJdW[L21][o][h], 2) / pow(Mx->prevdJdW[L21][o][h], 2);
			Mx->dW[L21][o][h]=pNNParms->LearningRate*(Mx->dJdW[L21][o][h] + Mx->beta[L21] * Mx->prevdW[L21][o][h]);

			Mx->W[L21][o][h] += Mx->dW[L21][o][h];
		}
	}
	//-- L1 -> L0
	for (h = 0; h < pNNParms->HiddenCount; h++){
		sk = 0;
		for (o = 0; o < pNNParms->L2cnt; o++) sk += Mx->W[L21][o][h] * Mx->dk[o];
		for (i = 0; i < (pNNParms->InputCount + pNNParms->ContextCount); i++){
			Mx->dJdW[L10][h][i] = sk*Mx->dF[L1][h] * Mx->F[L0][i];

			Mx->W[L10][h][i] += Mx->BPdW[L10][h][i];

			Mx->beta[L10] = (Mx->BPCount == 0)?0:pow(Mx->dJdW[L10][h][i], 2) / pow(Mx->prevdJdW[L10][h][i], 2);
			Mx->dW[L10][h][i] = pNNParms->LearningRate*(Mx->dJdW[L10][h][i] + Mx->beta[L10] * Mx->prevdW[L10][h][i]);

			Mx->W[L10][h][i] += Mx->dW[L10][h][i];
		}
	}
}

void BP_Std(int pid, int tid, tDebugInfo* DebugParms, NN_Parms* pNNParms, int pNetId, int pDataSetId, int TestId, int Epoch, int SampleId, tMxData* Mx){
	int i, h, o;
	double sk;
	double BPdW;
	//-- L2 -> L1
	for (h = 0; h < pNNParms->HiddenCount; h++){
		for (o = 0; o < pNNParms->L2cnt; o++){
			Mx->dk[o] = Mx->e[o] * Mx->dF[L2][o];
			BPdW = pNNParms->LearningRate*Mx->dk[o] * Mx->F[L1][h];
			Mx->dW[L21][o][h] = (1 - pNNParms->LearningMomentum)*BPdW + pNNParms->LearningMomentum*Mx->prevdW[L21][o][h];
			Mx->W[L21][o][h] += Mx->dW[L21][o][h];
		}
	}
	//-- L1 -> L0
	for (i = 0; i < (pNNParms->InputCount + pNNParms->ContextCount); i++){
		for (h = 0; h < pNNParms->HiddenCount; h++){
			sk = 0;
			for (o = 0; o < pNNParms->L2cnt; o++) sk += Mx->W[L21][o][h] * Mx->dk[o];
			BPdW = pNNParms->LearningRate*sk*Mx->dF[L1][h] * Mx->F[L0][i];
			Mx->dW[L10][h][i] = (1 - pNNParms->LearningMomentum)*BPdW + pNNParms->LearningMomentum*Mx->prevdW[L10][h][i];
			Mx->W[L10][h][i] += Mx->dW[L10][h][i];
		}
	}
}

void BP(int pid, int tid, tDebugInfo* DebugParms, NN_Parms* NNParms, int pNetId, int DataSetId, int TestId, int Epoch, int SampleId, tMxData* Mx){
	//-- Save previous weights
	SavePrevWeights(NNParms, Mx);

	if (NNParms->BP_Algo == BP_STD)			BP_Std(pid, tid, DebugParms, NNParms, pNetId, DataSetId, TestId, Epoch, SampleId, Mx);
	if (NNParms->BP_Algo == BP_CGD)			BP_cgd(pid, tid, DebugParms, NNParms, pNetId, DataSetId, TestId, Epoch, SampleId, Mx);
	if (NNParms->BP_Algo == BP_QING)		BP_Qing(pid, tid, DebugParms, NNParms, pNetId, DataSetId, TestId, Epoch, SampleId, Mx);
	if (NNParms->BP_Algo == BP_QUICKPROP)	BP_QuickProp(pid, tid, DebugParms, NNParms, pNetId, DataSetId, TestId, Epoch, SampleId, Mx);
	Mx->BPCount++;
}

void NNInit(NN_Parms* pNNParms, tMxData* Mx){
	int i, j, k;

	// L2 neurons
	for (i = 0; i < pNNParms->L2cnt; i++){
		Mx->F[L2][i] = 0;
		Mx->dF[L2][i] = 0;
		Mx->c[L2][i] = 1;
	}
	// L1 neurons
	for (i = 0; i < pNNParms->L1cnt; i++){
		Mx->F[L1][i] = 0;
		Mx->dF[L1][i] = 0;
		Mx->c[L1][i] = 1;
	}
	// L0 neurons
	for (i = 0; i < pNNParms->L0cnt; i++){
		Mx->F[L0][i] = 0;
		Mx->dF[L0][i] = 0;
		Mx->c[L0][i] = 1;
	}
	// L21 connections
	for (k = 0; k<pNNParms->L2cnt; k++){
		for (j = 0; j < pNNParms->L1cnt; j++){
			Mx->W[L21][k][j] = MyRndDbl(-1 / sqrt((double)pNNParms->L1cnt), 1 / sqrt((double)pNNParms->L1cnt));
			Mx->dW[L21][k][j] = MyRndDbl(-1 / sqrt((double)pNNParms->L1cnt), 1 / sqrt((double)pNNParms->L1cnt));
			Mx->dJdW[L21][k][j] = 0;
		}
	}
	// L10 connections
	for (j = 0; j < pNNParms->L1cnt; j++){
		for (i = 0; i < pNNParms->L0cnt; i++){
			Mx->W[L10][j][i] = MyRndDbl(-1 / sqrt((double)pNNParms->L0cnt), 1 / sqrt((double)pNNParms->L0cnt));
			Mx->dW[L10][j][i] = MyRndDbl(-1 / sqrt((double)pNNParms->L0cnt), 1 / sqrt((double)pNNParms->L0cnt));
			Mx->dJdW[L10][j][i] = 0;
		}
	}

	//-- Qing stuff
	Mx->ro[L10] = 0;
	Mx->ro[L21] = 0;
	Mx->sigma[L10] = 0;
	Mx->sigma[L21] = 0;
	Mx->adzev[L10][0] = 0;
	for(i=0;i<pNNParms->L2cnt; i++) Mx->adzev[L21][i] = 0;

	//-- CGD stuff
	Mx->beta[L10] = 0; Mx->beta[L21] = 0;
	Mx->BPCount = 0;
}

void NNTrain_Batch(NN_Parms* pNNParms, tTrainParams* tp){
	int s, i, o;
	int epoch;
	double MSE_T, TSE_T;
	double MSE_V, TSE_V;
	int pid = GetCurrentProcessId();
	int tid = GetCurrentThreadId();

	for (epoch = 0; epoch < pNNParms->MaxEpochs; epoch++){
		TSE_T = 0; TSE_V = 0;

		for (s = 0; s < tp->SampleCount; s++){

			//-- 2. Validation Data

			//-- 2.1. Load SampleData into Input Neurons OUT values
			for (i = 0; i < pNNParms->InputCount; i++) tp->MxData->F[L0][i] = tp->SampleV[s][i];
			//-- 2.2. Feed Forward
			FF(pNNParms, tp->MxData);
			//-- 2.2. Sum up the toral error for the epoch
			for (o = 0; o < pNNParms->L2cnt; o++){
				tp->MxData->Vu[o] = tp->TargetV[s][o];
				tp->MxData->Ve[o] = tp->MxData->Vu[o] - tp->MxData->F[L2][o];
				TSE_V += pow(tp->MxData->Ve[o], 2) / 2;
			}

			//-- 3. Training Data

			//-- 3.1. Load SampleData into Input Neurons OUT values
			for (i = 0; i < pNNParms->InputCount; i++) tp->MxData->F[L0][i] = tp->Sample[s][i];
			//-- 3.2 Load Target Data into u
			for (o = 0; o < pNNParms->L2cnt; o++) tp->MxData->u[o] = tp->Target[s][o];
			//-- 3.3. Feed Forward (also recalculates error)
			FF(pNNParms, tp->MxData);
			//-- 3.3. Sum up the toral error for the epoch
			for (o = 0; o < pNNParms->L2cnt; o++) TSE_T += pow(tp->MxData->e[o], 2) / 2;

		}
		//-- 4. BackPropagation (Neurons are loaded with Training Data)
		BP(pid, tid, tp->DebugParms, pNNParms, tp->NetId, tp->DataSetId, tp->TestId, epoch, s, tp->MxData);

		//-- 5. Calc MSE for epoch , and exit if less than TargetMSE
		MSE_T = TSE_T / tp->SampleCount / pNNParms->L2cnt;
		MSE_V = TSE_V / tp->SampleCount / pNNParms->L2cnt;
		//LogWrite(DebugParms, "NNTrain() CheckPoint 3 - epoch=%d ; MSE=%f\n", 2, epoch, MSE);
		gotoxy(0, 1 + tp->DataSetId);  printf("\rProcess %5d, Thread %5d, Dataset %d , TestId %d , Epoch %6d , Training MSE=%f , Validation MSE=%f", pid, tid, tp->DataSetId, tp->TestId, epoch, MSE_T, MSE_V);
		//LogWrite(tp->DebugParms, LOG_INFO, "NNTrain() - Thread=%d ; Epoch=%d ; MSE=%f\n", 3, tid, epoch, MSE);
		SaveMSEData(pNNParms, tp->NetId, pid, tid, tp->DataSetId, tp->TestId, epoch, MSE_T, MSE_V);
		if (MSE_T < pNNParms->TargetMSE) break;
	}
	pNNParms->ActualEpochs = epoch;
	LogWrite(tp->DebugParms, LOG_INFO, "NNTrain() CheckPoint 4 - Thread=%d ; Final MSE_T=%f ; Final MSE_V=%f\n", 2, tid, MSE_T, MSE_V);
}

void NNTrain_Online(NN_Parms* pNNParms, tTrainParams* tp){
	int s, i, o;
	double MSE_T, TSE_T;
	double MSE_V, TSE_V;
	int pid = GetCurrentProcessId();
	int tid = GetCurrentThreadId();

	TSE_T = 0; TSE_V = 0;
	for (s = 0; s < tp->SampleCount; s++){

		//-- 2. Validation Data

		//-- 2.1. Load SampleData into Input Neurons OUT values
		for (i = 0; i < pNNParms->InputCount; i++) tp->MxData->F[L0][i] = tp->SampleV[s][i];
		//-- 2.2. Feed Forward
		FF(pNNParms, tp->MxData);
		//-- 2.2. Sum up the toral error for the epoch
		for (o = 0; o < pNNParms->L2cnt; o++){
			tp->MxData->Vu[o] = tp->TargetV[s][o];
			tp->MxData->Ve[o] = tp->MxData->Vu[o] - tp->MxData->F[L2][o];
			TSE_V += pow(tp->MxData->Ve[o], 2) / 2;
		}

		//-- 3. Training Data

		//-- 3.1. Load SampleData into Input Neurons OUT values
		for (i = 0; i < pNNParms->InputCount; i++) tp->MxData->F[L0][i] = tp->Sample[s][i];
		//-- 3.2 Load Target Data into u
		for (o = 0; o < pNNParms->L2cnt; o++) tp->MxData->u[o] = tp->Target[s][o];
		//-- 3.3. Feed Forward (also recalculates error)
		FF(pNNParms, tp->MxData);
		//-- 3.3. Sum up the toral error for the epoch
		for (o = 0; o < pNNParms->L2cnt; o++) TSE_T += pow(tp->MxData->e[o], 2) / 2;

		//-- 4. BackPropagation (Neurons are loaded with Training Data)
		BP(pid, tid, tp->DebugParms, pNNParms, tp->NetId, tp->DataSetId, tp->TestId, 0, s, tp->MxData);

		//-- 5. Calc MSE for epoch , and exit if less than TargetMSE
		MSE_T = TSE_T / tp->SampleCount / pNNParms->L2cnt;
		MSE_V = TSE_V / tp->SampleCount / pNNParms->L2cnt;
		//LogWrite(DebugParms, "NNTrain() CheckPoint 3 - epoch=%d ; MSE=%f\n", 2, epoch, MSE);
		gotoxy(0, 1 + tp->DataSetId);  printf("\rProcess %5d, Thread %5d, Dataset %d , TestId %d , Sample %d , Training MSE=%f , Validation MSE=%f", pid, tid, tp->DataSetId, tp->TestId, s, MSE_T, MSE_V);
		//LogWrite(tp->DebugParms, LOG_INFO, "NNTrain() - Thread=%d ; Epoch=%d ; MSE=%f\n", 3, tid, epoch, MSE);
		SaveMSEData(pNNParms, tp->NetId, pid, tid, tp->DataSetId, tp->TestId, s, MSE_T, MSE_V);
		if (MSE_T < pNNParms->TargetMSE) break;
	}
	LogWrite(tp->DebugParms, LOG_INFO, "NNTrain() CheckPoint 4 - Thread=%d ; Final MSE_T=%f ; Final MSE_V=%f\n", 2, tid, MSE_T, MSE_V);
}

void NNTrain_Stochastic(NN_Parms* pNNParms, tTrainParams* tp){
	int s, i, o;
	int epoch;
	double MSE_T = 1000, MSE_V = 1000;
	double TSE_T, TSE_V;
	double prevMSE_T;
	double adzev10 = 0, prevadzev10 = 0;
	int pid = GetCurrentProcessId();
	int tid = GetCurrentThreadId();
	
	for (epoch = 0; epoch < pNNParms->MaxEpochs; epoch++){
		TSE_T = 0; TSE_V = 0;
		for (s = 0; s < tp->SampleCount; s++){

			//-- 2. Validation Data

			//-- 2.1. Load SampleData into Input Neurons OUT values
			for (i = 0; i < pNNParms->InputCount; i++) tp->MxData->F[L0][i] = tp->SampleV[s][i];
			//-- 2.2. Feed Forward
			FF(pNNParms, tp->MxData);
			//-- 2.2. Sum up the toral error for the epoch
			for (o = 0; o < pNNParms->L2cnt; o++){
				tp->MxData->Vu[o] = tp->TargetV[s][o];
				tp->MxData->Ve[o] = tp->MxData->Vu[o] - tp->MxData->F[L2][o];
				TSE_V += pow(tp->MxData->Ve[o], 2) / 2;
			}

			//-- 3. Training Data

			//-- 3.1. Load SampleData into Input Neurons OUT values
			for (i = 0; i < pNNParms->InputCount; i++) tp->MxData->F[L0][i] = tp->Sample[s][i];
			//-- 3.2 Load Target Data into u
			for (o = 0; o < pNNParms->L2cnt; o++) tp->MxData->u[o] = tp->Target[s][o];
			//-- 3.3. Feed Forward (also recalculates error)
			FF(pNNParms, tp->MxData);
			//-- 3.3. Sum up the toral error for the epoch
			for (o = 0; o < pNNParms->L2cnt; o++) TSE_T += pow(tp->MxData->e[o], 2) / 2;

			//-- 4. BackPropagation (Neurons are loaded with Training Data)
			BP(pid, tid, tp->DebugParms, pNNParms, tp->NetId, tp->DataSetId, tp->TestId, epoch, s, tp->MxData);
		}

		//-- 5. Calc MSE for epoch , and exit if less than TargetMSE
		prevMSE_T = MSE_T;	// save previous MSE
		MSE_T = TSE_T / tp->SampleCount / pNNParms->L2cnt;
		MSE_V = TSE_V / tp->SampleCount / pNNParms->L2cnt;
		if (pNNParms->StopAtDivergence==1 && MSE_T > prevMSE_T) break;
		//LogWrite(DebugParms, "NNTrain() CheckPoint 3 - epoch=%d ; MSE=%f\n", 2, epoch, MSE);
		gotoxy(0, 1 + tp->DataSetId);  printf("\rProcess %5d, Thread %5d, Dataset %d , TestId %d , Epoch %6d , Training MSE=%f , Validation MSE=%f", pid, tid, tp->DataSetId, tp->TestId, epoch, MSE_T, MSE_V);
		//LogWrite(tp->DebugParms, LOG_INFO, "NNTrain() - Thread=%d ; Epoch=%d ; MSE=%f\n", 3, tid, epoch, MSE);
		SaveMSEData(pNNParms, tp->NetId, pid, tid, tp->DataSetId, tp->TestId, epoch, MSE_T, MSE_V);
		if (MSE_T < pNNParms->TargetMSE) break;
	}
	pNNParms->ActualEpochs = epoch;
	LogWrite(tp->DebugParms, LOG_INFO, "NNTrain() CheckPoint 4 - Thread=%d ; Final MSE_T=%f ; Final MSE_V=%f\n", 2, tid, MSE_T, MSE_V);
}

void NNTrain(NN_Parms* pNNParms, tTrainParams* tp){
	switch (pNNParms->TrainingProtocol){
	case TP_STOCHASTIC:
		NNTrain_Stochastic(pNNParms, tp);
		break;
	case TP_BATCH:
		NNTrain_Batch(pNNParms, tp);
		break;
	case TP_ONLINE:
		NNTrain_Online(pNNParms, tp);
		break;
	}
}

void TrainSave_NN(tTrainParams* TrainParms){
	int pid = GetCurrentProcessId();
	int tid = GetCurrentThreadId();
	//-- Init Weights and Neurons
	NNInit(TrainParms->NNParms, TrainParms->MxData);
	//-- Train 
	NNTrain(TrainParms->NNParms, TrainParms);
	//-- Save
	NNSave(TrainParms->NNParms, TrainParms->NetId, pid, tid, TrainParms->DataSetId, TrainParms->TestId, TrainParms->MxData->W, TrainParms->MxData->F[L0]);
	//-- Run
	//Run_NN(parms->DebugParms, parms->NNParms, parms->NetId, parms->InputData, parms->OOS, pid, tid, parms->DataSetId, parms->TestId, parms->SampleCount, parms->Sample, parms->Target, parms->Forecast);
}

__declspec(dllexport) void Run_NN(tDebugInfo* pDebugParms, NN_Parms* pNNParms, tDataShape* pInputData, int pOOS, int pid, int pDatasetId, int pNetId, int pTestId, int pSampleCount, double** pSample, double** pTarget, double* pFD_TRS){
	int i, s, j, k;
	double vActual, vPrediction;
	LogWrite(pDebugParms, LOG_INFO, "Run_NN() called. ProcessId=%d ; pDataParms:\n", 1, pid);
	LogWrite(pDebugParms, LOG_INFO, "\t\t\tDatasetsCount=%d\n", 1, pInputData->DatasetsCount);
	LogWrite(pDebugParms, LOG_INFO, "\t\t\tHistoryLen=%d\n", 1, pInputData->HistoryLen);
	LogWrite(pDebugParms, LOG_INFO, "\t\t\tSampleLen=%d\n", 1, pInputData->SampleLen);
	LogWrite(pDebugParms, LOG_INFO, "\t\t\tPredictionLen=%d\n", 1, pInputData->PredictionLen);
	LogWrite(pDebugParms, LOG_INFO, "\t\t\tL0cnt=%d\n", 1, pNNParms->L0cnt);
	LogWrite(pDebugParms, LOG_INFO, "\t\t\tL1cnt=%d\n", 1, pNNParms->L1cnt);
	LogWrite(pDebugParms, LOG_INFO, "\t\t\tL2cnt=%d\n", 1, pNNParms->L2cnt);
	LogWrite(pDebugParms, LOG_INFO, "\t\t\tDataTransformation=%d\n", 1, pInputData->DataTransformation);
	LogWrite(pDebugParms, LOG_INFO, "\t\t\tScaleMin=%f\n", 1, pInputData->ScaleMin);
	LogWrite(pDebugParms, LOG_INFO, "\t\t\tScaleMax=%f\n", 1, pInputData->ScaleMax);
	LogWrite(pDebugParms, LOG_INFO, "\t\t\tWiggleRoom=%f\n", 1, pInputData->wiggleRoom);
	LogWrite(pDebugParms, LOG_INFO, "\t\t\tTSF Count=%d\n", 1, pInputData->TSFcnt);

	tMxData MxData;
	//-- 0. mallocs
	double* tmpSample = (double*)malloc(pInputData->SampleLen*sizeof(double));
	double**  a   = (double**)malloc(LAYERS*sizeof(double*));
	double**  F   = (double**)malloc(LAYERS*sizeof(double*));
	double**  dF = (double**)malloc(LAYERS*sizeof(double*));
	double**  prevF = (double**)malloc(LAYERS*sizeof(double*));
	double**  prevdF = (double**)malloc(LAYERS*sizeof(double*));
	double**  c = (double**)malloc(LAYERS*sizeof(double*));
	double**  prevc = (double**)malloc(LAYERS*sizeof(double*));
	double*   e = (double*)malloc(pNNParms->L2cnt*sizeof(double));
	double*   u = (double*)malloc(pNNParms->L2cnt*sizeof(double));
	double*** W = (double***)malloc(2 * sizeof(double***));
	a[L0] = (double*)malloc(pNNParms->L0cnt*sizeof(double)); a[L1] = (double*)malloc(pNNParms->L1cnt*sizeof(double)); a[L2] = (double*)malloc(pNNParms->L2cnt*sizeof(double));
	F[L0] = (double*)malloc(pNNParms->L0cnt*sizeof(double)); F[L1] = (double*)malloc(pNNParms->L1cnt*sizeof(double)); F[L2] = (double*)malloc(pNNParms->L2cnt*sizeof(double));
	dF[L0] = (double*)malloc(pNNParms->L0cnt*sizeof(double)); dF[L1] = (double*)malloc(pNNParms->L1cnt*sizeof(double)); dF[L2] = (double*)malloc(pNNParms->L2cnt*sizeof(double));
	prevF[L0] = (double*)malloc(pNNParms->L0cnt*sizeof(double)); prevF[L1] = (double*)malloc(pNNParms->L1cnt*sizeof(double)); prevF[L2] = (double*)malloc(pNNParms->L2cnt*sizeof(double));
	prevdF[L0] = (double*)malloc(pNNParms->L0cnt*sizeof(double)); prevdF[L1] = (double*)malloc(pNNParms->L1cnt*sizeof(double)); prevdF[L2] = (double*)malloc(pNNParms->L2cnt*sizeof(double));
	c[L0] = (double*)malloc(pNNParms->L0cnt*sizeof(double)); c[L1] = (double*)malloc(pNNParms->L1cnt*sizeof(double)); c[L2] = (double*)malloc(pNNParms->L2cnt*sizeof(double));
	prevc[L0] = (double*)malloc(pNNParms->L0cnt*sizeof(double)); prevc[L1] = (double*)malloc(pNNParms->L1cnt*sizeof(double)); prevc[L2] = (double*)malloc(pNNParms->L2cnt*sizeof(double));
	W[L10] = (double**)malloc(pNNParms->L1cnt*sizeof(double*)); for (i = 0; i < pNNParms->L1cnt; i++) W[L10][i] = (double*)malloc(pNNParms->L0cnt*sizeof(double));
	W[L21] = (double**)malloc(pNNParms->L2cnt*sizeof(double*)); for (i = 0; i < pNNParms->L2cnt; i++) W[L21][i] = (double*)malloc(pNNParms->L1cnt*sizeof(double));

	MxData.a = a;
	MxData.F = F;
	MxData.dF = dF;
	MxData.prevF = prevF;
	MxData.prevdF = prevdF;
	MxData.c = c;
	MxData.e = e;
	MxData.u = u;
	MxData.prevc = prevc;
	MxData.W = W;
	LogWrite(pDebugParms, LOG_INFO, "Run_NN() CheckPoint 1\n", 0);

	//-- Load W*** from pNNParms->FinalW[DataSet][Level][FromN][ToN] 
	//-- L21
	for (k = 0; k < pNNParms->L2cnt; k++){
		for (j = 0; j < pNNParms->L1cnt; j++){
			W[L21][k][j] = pNNParms->FinalW[pDatasetId][pNetId][L21][k][j].Weight;
			//LogWrite(pDebugParms, LOG_INFO, "Run_NN() CheckPoint 1.1 - W[L21][%d][%d]=%f\n", 3, k, j, W[L21][k][j]);
		}
	}
	//-- L10
	for (j = 0; j < pNNParms->L1cnt; j++){
		for (i = 0; i < pNNParms->L0cnt; i++){
			W[L10][j][i] = pNNParms->FinalW[pDatasetId][pNetId][L10][j][i].Weight;
			//LogWrite(pDebugParms, LOG_INFO, "Run_NN() CheckPoint 1.2 - W[L10][%d][%d]=%f\n", 3, j, i, W[L10][j][i]);
		}
	}

	//-- 1. Reset Context Neurons
	for (int cx = 0; cx < pNNParms->ContextCount; cx++) F[L0][pInputData->SampleLen + cx] = 0;
	LogWrite(pDebugParms, LOG_INFO, "Run_NN() CheckPoint 2\n", 0);

	//-- 3 Write First window of data, with no prediction (that is, write the first sample)
	for (i = 0; i<pInputData->SampleLen; i++){
	//for (i = 1; i<pInputData->SampleLen; i++){
		SaveRunData(pNNParms, pNetId, pid, pNNParms->TrainingTid[pDatasetId][pNetId], pDatasetId, pTestId, i, (pInputData->HistoryLen - i), pSample[0][i], NULL);
	}
	LogWrite(pDebugParms, LOG_INFO, "Run_NN() CheckPoint 3\n", 0);

	//-- 4 Write Training Set data, with next-step prediction
	
	//-- 4.1 In-Sample
	for (s = 0; s<pSampleCount; s++){
		for (i = 0; i < pInputData->SampleLen; i++){
			tmpSample[i] = pSample[s][i];	//-- Only used for the last sample ( pSample[pSampleCount-1] )
			F[L0][i] = tmpSample[i];	//-- Present each sample to input neurons
			//LogWrite(pDebugParms, LOG_INFO, "Run_NN() CheckPoint 3.1 ; SampleId=%d ; F[L0][%d]=%f ; ", 3, s, i, F[L0][i]);
		}
		//LogWrite(pDebugParms, LOG_INFO, "\n", 0);
		FF(pNNParms, &MxData);								//-- Feed-Forward the network;
		vPrediction = F[L2][0];										//-- Predicted  Data. Only step 0 prediction is considered.
		vActual = pTarget[s][0];
		//-- Write RunLog structure
		SaveRunData(pNNParms, pNetId, pid, pNNParms->TrainingTid[pDatasetId][pNetId], pDatasetId, pTestId, pInputData->SampleLen + s, (s - pInputData->HistoryLen + pInputData->SampleLen + 1), vActual, vPrediction);
		//LogWrite(pDebugParms, LOG_INFO, "Run_NN() CheckPoint 3.2 ; vActual=%f ; vPrediction=%f\n", 2, vActual, vPrediction);
		//return;
	}
	LogWrite(pDebugParms, LOG_INFO, "Run_NN() CheckPoint 4\n", 0);

	//-- 4.2 Out-of-Sample
	//LogWrite(pDebugParms, "Run_NN() CheckPoint 4.2\n", 0);
	for (s = 0; s < pInputData->PredictionLen; s++){
		// Target[s] only exist while s<SampleCount. Beyond that, and if no target is provided (pOOS=0) , Actual is prediction from previous step
		if (pOOS == 1){
			//LogWrite(pDebugParms, LOG_INFO, "Run_NN() CheckPoint 4.1.a\n", 0);
			vActual = pFD_TRS[s];
		}
		else{
			//LogWrite(pDebugParms, LOG_INFO, "Run_NN() CheckPoint 4.1.b ; vActual=%f ; vPrediction=%f\n", 2, vActual, vPrediction);
			vActual = vPrediction;
		}
		//-- Sample beyond SampleCount must be build, regardless of pOOS
		ShiftArray(SHIFT_BACKWARD, pInputData->SampleLen, tmpSample, vActual);

		for (i = 0; i < pInputData->SampleLen; i++) F[L0][i] = tmpSample[i];	//-- Present each sample to input neurons
		//LogWrite(pDebugParms, LOG_INFO, "Run_NN() CheckPoint 4.4\n", 0);
		FF(pNNParms, &MxData);								//-- Feed-Forward the network;
		//LogWrite(pDebugParms, LOG_INFO, "Run_NN() CheckPoint 4.5\n", 0);
		vPrediction = F[L2][0];										//-- Predicted  Data. Only step 0 prediction is considered.

		SaveRunData(pNNParms, pNetId, pid, pNNParms->TrainingTid[pDatasetId][pNetId], pDatasetId, pTestId, (s + pInputData->HistoryLen), (s + 1), vActual, vPrediction);
	}
	LogWrite(pDebugParms, LOG_INFO, "Run_NN() CheckPoint 5\n", 0);

	//-- frees()
	for (i = 0; i < pNNParms->L1cnt; i++) free(W[L10][i]);
	LogWrite(pDebugParms, LOG_INFO, "Run_NN() CheckPoint 5.1\n", 0);
	for (i = 0; i < pNNParms->L2cnt; i++) free(W[L21][i]);
	LogWrite(pDebugParms, LOG_INFO, "Run_NN() CheckPoint 5.2\n", 0);
	free(W[L10]);
	LogWrite(pDebugParms, LOG_INFO, "Run_NN() CheckPoint 5.3\n", 0);
	free(W[L21]);
	LogWrite(pDebugParms, LOG_INFO, "Run_NN() CheckPoint 5.4\n", 0);
	free(W);
	LogWrite(pDebugParms, LOG_INFO, "Run_NN() CheckPoint 5.5\n", 0);
	free(dF[L0]); free(dF[L1]);
	LogWrite(pDebugParms, LOG_INFO, "Run_NN() CheckPoint 5.6\n", 0);
	free(dF[L2]); free(dF);
	LogWrite(pDebugParms, LOG_INFO, "Run_NN() CheckPoint 5.7\n", 0);
	free(F[L0]); free(F[L1]); free(F[L2]); free(F);
	LogWrite(pDebugParms, LOG_INFO, "Run_NN() CheckPoint 5.8\n", 0);
	free(a[L0]); free(a[L1]); free(a[L2]); free(a);
	free(tmpSample);

	LogWrite(pDebugParms, LOG_INFO, "Run_NN() CheckPoint 6\n", 0);
}

__declspec(dllexport) int Train_NN(tDebugInfo* pDebugParms, NN_Parms* pNNParams, tDataShape* pInputData, int pTestId, int pSampleCount, double**** pSampleData, double**** pTargetData, double**** pSampleDataV, double**** pTargetDataV){
	int i, d;

	LogWrite(pDebugParms, LOG_INFO, "Train_NN() called. ProcessId=%d ; pDataParms:\n", 1, GetCurrentProcessId());
	LogWrite(pDebugParms, LOG_INFO, "\t\t\tL0cnt=%d\n", 1, pNNParams->L0cnt);
	LogWrite(pDebugParms, LOG_INFO, "\t\t\tL1cnt=%d\n", 1, pNNParams->L1cnt);
	LogWrite(pDebugParms, LOG_INFO, "\t\t\tL2cnt=%d\n", 1, pNNParams->L2cnt);
	LogWrite(pDebugParms, LOG_INFO, "\t\t\tHiddenCount=%d\n", 1, pNNParams->HiddenCount);
	LogWrite(pDebugParms, LOG_INFO, "\t\t\tContextCount=%d\n", 1, pNNParams->ContextCount);
	LogWrite(pDebugParms, LOG_INFO, "\t\t\tUseContext=%d\n", 1, pNNParams->UseContext);
	LogWrite(pDebugParms, LOG_INFO, "\t\t\tBP_Algo=%d\n", 1, pNNParams->BP_Algo);
	LogWrite(pDebugParms, LOG_INFO, "\t\t\tLearningRate=%f\n", 1, pNNParams->LearningRate);
	LogWrite(pDebugParms, LOG_INFO, "\t\t\tLearningMomentum=%f\n", 1, pNNParams->LearningMomentum);
	LogWrite(pDebugParms, LOG_INFO, "\t\t\tActivationFunction=%d\n", 1, pNNParams->ActivationFunction);

	// srand() and mallocs
	srand((unsigned int)time(NULL));

	//-- Multithreading stuff
	HANDLE* HTrain = (HANDLE*)malloc(pInputData->DatasetsCount*sizeof(HANDLE));
	tTrainParams* tp = (tTrainParams*)malloc(pInputData->DatasetsCount*sizeof(tTrainParams));
	DWORD* kaz = (DWORD*)malloc(pInputData->DatasetsCount*sizeof(DWORD));
	LPDWORD* tid = (LPDWORD*)malloc(pInputData->DatasetsCount*sizeof(LPDWORD)); for (i = 0; i < pInputData->DatasetsCount; i++) tid[i] = &kaz[i];

	//-- Core Network stuff
	tMxData* MxData = (tMxData*)malloc(pInputData->DatasetsCount*sizeof(tMxData));
	double*** a = (double***)malloc(pInputData->DatasetsCount*sizeof(double**));
	double*** F = (double***)malloc(pInputData->DatasetsCount*sizeof(double**));
	double*** dF = (double***)malloc(pInputData->DatasetsCount*sizeof(double**));
	double** e = (double**)malloc(pInputData->DatasetsCount*sizeof(double*));
	double** u = (double**)malloc(pInputData->DatasetsCount*sizeof(double*));
	double** Ve = (double**)malloc(pInputData->DatasetsCount*sizeof(double*));
	double** Vu = (double**)malloc(pInputData->DatasetsCount*sizeof(double*));
	double** dk = (double**)malloc(pInputData->DatasetsCount*sizeof(double*));
	double**** W = (double****)malloc(pInputData->DatasetsCount * sizeof(double***));
	double**** dW = (double****)malloc(pInputData->DatasetsCount * sizeof(double***));
	double**** dJdW = (double****)malloc(pInputData->DatasetsCount * sizeof(double***));
	double**** BPdW = (double****)malloc(pInputData->DatasetsCount * sizeof(double***));
	double*** prevF = (double***)malloc(pInputData->DatasetsCount*sizeof(double**));
	double*** prevdF = (double***)malloc(pInputData->DatasetsCount*sizeof(double**));
	double**** prevW = (double****)malloc(pInputData->DatasetsCount * sizeof(double***));
	double**** prevdW = (double****)malloc(pInputData->DatasetsCount * sizeof(double***));
	double**** prevdJdW = (double****)malloc(pInputData->DatasetsCount * sizeof(double***));
	double**** prevBPdW = (double****)malloc(pInputData->DatasetsCount * sizeof(double***));
	//-- CFR/AG stuff
	double***	c = (double***)malloc(pInputData->DatasetsCount*sizeof(double**));
	double****	d_tmp = (double****)malloc(pInputData->DatasetsCount*sizeof(double***));
	double****	g = (double****)malloc(pInputData->DatasetsCount*sizeof(double***));
	double****	B = (double****)malloc(pInputData->DatasetsCount*sizeof(double***));
	double***	prevc = (double***)malloc(pInputData->DatasetsCount*sizeof(double**));
	double****	prevd = (double****)malloc(pInputData->DatasetsCount*sizeof(double***));
	double****	prevg = (double****)malloc(pInputData->DatasetsCount*sizeof(double***));
	double****	prevB = (double****)malloc(pInputData->DatasetsCount*sizeof(double***));
	//-- Qing stuff
	double*** adzev = (double***)malloc(pInputData->DatasetsCount*sizeof(double**));
	double**  ro = (double**)malloc(pInputData->DatasetsCount*sizeof(double*));
	int**  sigma = (int**)malloc(pInputData->DatasetsCount*sizeof(int*));
	double** uW = (double**)malloc(pInputData->DatasetsCount*sizeof(double*));
	double** tmpV1 = (double**)malloc(pInputData->DatasetsCount*sizeof(double*));
	double** ux = (double**)malloc(pInputData->DatasetsCount*sizeof(double*));
	double*** dxdW10 = (double***)malloc(pInputData->DatasetsCount*sizeof(double**));
	//-- CGD stuff
	double** cgd_sigma = (double**)malloc(pInputData->DatasetsCount*sizeof(double*));
	double** cgd_lambda = (double**)malloc(pInputData->DatasetsCount*sizeof(double*));
	double** cgd_lambdau = (double**)malloc(pInputData->DatasetsCount*sizeof(double*));
	double** cgd_delta = (double**)malloc(pInputData->DatasetsCount*sizeof(double*));
	double*** cgd_p = (double***)malloc(pInputData->DatasetsCount*sizeof(double**));
	double*** cgd_r = (double***)malloc(pInputData->DatasetsCount*sizeof(double**));
	double*** cgd_s = (double***)malloc(pInputData->DatasetsCount*sizeof(double**));
	double*** cgd_sigmap = (double***)malloc(pInputData->DatasetsCount*sizeof(double**));
	double*** cgd_tmpV1 = (double***)malloc(pInputData->DatasetsCount*sizeof(double**));
	double*** cgd_tmpV2 = (double***)malloc(pInputData->DatasetsCount*sizeof(double**));
	double*** cgd_tmpV3 = (double***)malloc(pInputData->DatasetsCount*sizeof(double**));
	double*** cgd_tmpV4 = (double***)malloc(pInputData->DatasetsCount*sizeof(double**));
	double*** cgd_newW = (double***)malloc(pInputData->DatasetsCount * sizeof(double**));
	double** beta = (double**)malloc(pInputData->DatasetsCount * sizeof(double**));

	//-- temp matrices, sized using the largest possible dimensions. there are 2 of them, as most matrix operations take at most 2 matrices
	double**** tmpM1 = (double****)malloc(pInputData->DatasetsCount*sizeof(double***));
	double**** tmpM2 = (double****)malloc(pInputData->DatasetsCount*sizeof(double***));
	double**** tmpM3 = (double****)malloc(pInputData->DatasetsCount*sizeof(double***));
	double**** tmpM4 = (double****)malloc(pInputData->DatasetsCount*sizeof(double***));
	double**** tmpM5 = (double****)malloc(pInputData->DatasetsCount*sizeof(double***));
	double**** tmpM6 = (double****)malloc(pInputData->DatasetsCount*sizeof(double***));
	double**** tmpM7 = (double****)malloc(pInputData->DatasetsCount*sizeof(double***));
	double**** tmpM8 = (double****)malloc(pInputData->DatasetsCount*sizeof(double***));
	double**** tmpM9 = (double****)malloc(pInputData->DatasetsCount*sizeof(double***));
	double**** tmpM10 = (double****)malloc(pInputData->DatasetsCount*sizeof(double***));
	double**** tmpM11 = (double****)malloc(pInputData->DatasetsCount*sizeof(double***));
	double**** tmpM12 = (double****)malloc(pInputData->DatasetsCount*sizeof(double***));
	double**** tmpM13 = (double****)malloc(pInputData->DatasetsCount*sizeof(double***));
	double**** tmpM14 = (double****)malloc(pInputData->DatasetsCount*sizeof(double***));
	double**** tmpM15 = (double****)malloc(pInputData->DatasetsCount*sizeof(double***));
	double**** tmpM16 = (double****)malloc(pInputData->DatasetsCount*sizeof(double***));
	double***  G =      (double***)malloc(pInputData->DatasetsCount*sizeof(double**));
	for (d = 0; d < pInputData->DatasetsCount; d++){

		//-- Core network stuff
		a[d] = (double**)malloc(LAYERS*sizeof(double*));
		a[d][L0] = (double*)malloc(pNNParams->L0cnt*sizeof(double)); a[d][L1] = (double*)malloc(pNNParams->L1cnt*sizeof(double)); a[d][L2] = (double*)malloc(pNNParams->L2cnt*sizeof(double));
		F[d] = (double**)malloc(LAYERS*sizeof(double*));
		F[d][L0] = (double*)malloc(pNNParams->L0cnt*sizeof(double)); F[d][L1] = (double*)malloc(pNNParams->L1cnt*sizeof(double)); F[d][L2] = (double*)malloc(pNNParams->L2cnt*sizeof(double));
		dF[d] = (double**)malloc(LAYERS*sizeof(double*));
		dF[d][L0] = (double*)malloc(pNNParams->L0cnt*sizeof(double)); dF[d][L1] = (double*)malloc(pNNParams->L1cnt*sizeof(double)); dF[d][L2] = (double*)malloc(pNNParams->L2cnt*sizeof(double));
		e[d] = (double*)malloc(pNNParams->L2cnt*sizeof(double));
		u[d] = (double*)malloc(pNNParams->L2cnt*sizeof(double));
		Ve[d] = (double*)malloc(pNNParams->L2cnt*sizeof(double));
		Vu[d] = (double*)malloc(pNNParams->L2cnt*sizeof(double));
		dk[d] = (double*)malloc(pNNParams->L2cnt*sizeof(double));
		W[d] = (double***)malloc((LAYERS - 1)*sizeof(double**));
		W[d][L10] = (double**)malloc(pNNParams->L1cnt*sizeof(double*));		for (i = 0; i < pNNParams->L1cnt; i++) W[d][L10][i] = (double*)malloc(pNNParams->L0cnt*sizeof(double));
		W[d][L21] = (double**)malloc(pNNParams->L2cnt*sizeof(double*));		for (i = 0; i < pNNParams->L2cnt; i++) W[d][L21][i] = (double*)malloc(pNNParams->L1cnt*sizeof(double));
		dW[d] = (double***)malloc((LAYERS - 1)*sizeof(double**));
		dW[d][L10] = (double**)malloc(pNNParams->L1cnt*sizeof(double*));		for (i = 0; i < pNNParams->L1cnt; i++) dW[d][L10][i] = (double*)malloc(pNNParams->L0cnt*sizeof(double));
		dW[d][L21] = (double**)malloc(pNNParams->L2cnt*sizeof(double*));		for (i = 0; i < pNNParams->L2cnt; i++) dW[d][L21][i] = (double*)malloc(pNNParams->L1cnt*sizeof(double));
		dJdW[d] = (double***)malloc((LAYERS - 1)*sizeof(double**));
		dJdW[d][L10] = (double**)malloc(pNNParams->L1cnt*sizeof(double*));		for (i = 0; i < pNNParams->L1cnt; i++) dJdW[d][L10][i] = (double*)malloc(pNNParams->L0cnt*sizeof(double));
		dJdW[d][L21] = (double**)malloc(pNNParams->L2cnt*sizeof(double*));		for (i = 0; i < pNNParams->L2cnt; i++) dJdW[d][L21][i] = (double*)malloc(pNNParams->L1cnt*sizeof(double));
		BPdW[d] = (double***)malloc((LAYERS - 1)*sizeof(double**));
		BPdW[d][L10] = (double**)malloc(pNNParams->L1cnt*sizeof(double*));		for (i = 0; i < pNNParams->L1cnt; i++) BPdW[d][L10][i] = (double*)malloc(pNNParams->L0cnt*sizeof(double));
		BPdW[d][L21] = (double**)malloc(pNNParams->L2cnt*sizeof(double*));		for (i = 0; i < pNNParams->L2cnt; i++) BPdW[d][L21][i] = (double*)malloc(pNNParams->L1cnt*sizeof(double));
		prevF[d] = (double**)malloc(LAYERS*sizeof(double*));
		prevF[d][L0] = (double*)malloc(pNNParams->L0cnt*sizeof(double)); prevF[d][L1] = (double*)malloc(pNNParams->L1cnt*sizeof(double)); prevF[d][L2] = (double*)malloc(pNNParams->L2cnt*sizeof(double));
		prevdF[d] = (double**)malloc(LAYERS*sizeof(double*));
		prevdF[d][L0] = (double*)malloc(pNNParams->L0cnt*sizeof(double)); prevdF[d][L1] = (double*)malloc(pNNParams->L1cnt*sizeof(double)); prevdF[d][L2] = (double*)malloc(pNNParams->L2cnt*sizeof(double));
		prevW[d] = (double***)malloc((LAYERS - 1)*sizeof(double**));
		prevW[d][L10] = (double**)malloc(pNNParams->L1cnt*sizeof(double*));		for (i = 0; i < pNNParams->L1cnt; i++) prevW[d][L10][i] = (double*)malloc(pNNParams->L0cnt*sizeof(double));
		prevW[d][L21] = (double**)malloc(pNNParams->L2cnt*sizeof(double*));		for (i = 0; i < pNNParams->L2cnt; i++) prevW[d][L21][i] = (double*)malloc(pNNParams->L1cnt*sizeof(double));
		prevdW[d] = (double***)malloc((LAYERS - 1)*sizeof(double**));
		prevdW[d][L10] = (double**)malloc(pNNParams->L1cnt*sizeof(double*));		for (i = 0; i < pNNParams->L1cnt; i++) prevdW[d][L10][i] = (double*)malloc(pNNParams->L0cnt*sizeof(double));
		prevdW[d][L21] = (double**)malloc(pNNParams->L2cnt*sizeof(double*));		for (i = 0; i < pNNParams->L2cnt; i++) prevdW[d][L21][i] = (double*)malloc(pNNParams->L1cnt*sizeof(double));
		prevdJdW[d] = (double***)malloc((LAYERS - 1)*sizeof(double**));
		prevdJdW[d][L10] = (double**)malloc(pNNParams->L1cnt*sizeof(double*));		for (i = 0; i < pNNParams->L1cnt; i++) prevdJdW[d][L10][i] = (double*)malloc(pNNParams->L0cnt*sizeof(double));
		prevdJdW[d][L21] = (double**)malloc(pNNParams->L2cnt*sizeof(double*));		for (i = 0; i < pNNParams->L2cnt; i++) prevdJdW[d][L21][i] = (double*)malloc(pNNParams->L1cnt*sizeof(double));
		prevBPdW[d] = (double***)malloc((LAYERS - 1)*sizeof(double**));
		prevBPdW[d][L10] = (double**)malloc(pNNParams->L1cnt*sizeof(double*));		for (i = 0; i < pNNParams->L1cnt; i++) prevBPdW[d][L10][i] = (double*)malloc(pNNParams->L0cnt*sizeof(double));
		prevBPdW[d][L21] = (double**)malloc(pNNParams->L2cnt*sizeof(double*));		for (i = 0; i < pNNParams->L2cnt; i++) prevBPdW[d][L21][i] = (double*)malloc(pNNParams->L1cnt*sizeof(double));

		//-- CFR/AG stuff
		c[d] = (double**)malloc(LAYERS*sizeof(double*));
		c[d][L0] = (double*)malloc(pNNParams->L0cnt*sizeof(double)); c[d][L1] = (double*)malloc(pNNParams->L1cnt*sizeof(double)); c[d][L2] = (double*)malloc(pNNParams->L2cnt*sizeof(double));
		d_tmp[d] = (double***)malloc((LAYERS - 1)*sizeof(double**));
		d_tmp[d][L10] = (double**)malloc(pNNParams->L0cnt*pNNParams->L1cnt*sizeof(double*));		for (i = 0; i < pNNParams->L1cnt; i++) d_tmp[d][L10][i] = (double*)malloc(pNNParams->L0cnt*sizeof(double));
		d_tmp[d][L21] = (double**)malloc(pNNParams->L2cnt*pNNParams->L1cnt*sizeof(double*));		for (i = 0; i < pNNParams->L2cnt; i++) d_tmp[d][L21][i] = (double*)malloc(pNNParams->L1cnt*sizeof(double));
		g[d] = (double***)malloc((LAYERS - 1)*sizeof(double**));
		g[d][L10] = (double**)malloc(pNNParams->L0cnt*pNNParams->L1cnt*sizeof(double*));		for (i = 0; i < pNNParams->L1cnt; i++) g[d][L10][i] = (double*)malloc(pNNParams->L0cnt*sizeof(double));
		g[d][L21] = (double**)malloc(pNNParams->L2cnt*pNNParams->L1cnt*sizeof(double*));		for (i = 0; i < pNNParams->L2cnt; i++) g[d][L21][i] = (double*)malloc(pNNParams->L1cnt*sizeof(double));
		B[d] = (double***)malloc((LAYERS - 1)*sizeof(double**));
		B[d][L10] = (double**)malloc(pNNParams->L1cnt*sizeof(double*));		for (i = 0; i < pNNParams->L1cnt; i++) B[d][L10][i] = (double*)malloc(pNNParams->L0cnt*sizeof(double));
		B[d][L21] = (double**)malloc(pNNParams->L2cnt*sizeof(double*));		for (i = 0; i < pNNParams->L2cnt; i++) B[d][L21][i] = (double*)malloc(pNNParams->L1cnt*sizeof(double));
		prevc[d] = (double**)malloc(LAYERS*sizeof(double*));
		prevc[d][L0] = (double*)malloc(pNNParams->L0cnt*sizeof(double)); prevc[d][L1] = (double*)malloc(pNNParams->L1cnt*sizeof(double)); prevc[d][L2] = (double*)malloc(pNNParams->L2cnt*sizeof(double));
		prevd[d] = (double***)malloc((LAYERS - 1)*sizeof(double**));
		prevd[d][L10] = (double**)malloc(pNNParams->L0cnt*pNNParams->L1cnt*sizeof(double*));		for (i = 0; i < pNNParams->L1cnt; i++) prevd[d][L10][i] = (double*)malloc(pNNParams->L0cnt*sizeof(double));
		prevd[d][L21] = (double**)malloc(pNNParams->L2cnt*pNNParams->L1cnt*sizeof(double*));		for (i = 0; i < pNNParams->L2cnt; i++) prevd[d][L21][i] = (double*)malloc(pNNParams->L1cnt*sizeof(double));
		prevg[d] = (double***)malloc((LAYERS - 1)*sizeof(double**));
		prevg[d][L10] = (double**)malloc(pNNParams->L0cnt*pNNParams->L1cnt*sizeof(double*));		for (i = 0; i < pNNParams->L1cnt; i++) prevg[d][L10][i] = (double*)malloc(pNNParams->L0cnt*sizeof(double));
		prevg[d][L21] = (double**)malloc(pNNParams->L2cnt*pNNParams->L1cnt*sizeof(double*));		for (i = 0; i < pNNParams->L2cnt; i++) prevg[d][L21][i] = (double*)malloc(pNNParams->L1cnt*sizeof(double));
		prevB[d] = (double***)malloc((LAYERS - 1)*sizeof(double**));
		prevB[d][L10] = (double**)malloc(pNNParams->L1cnt*sizeof(double*));		for (i = 0; i < pNNParams->L1cnt; i++) prevB[d][L10][i] = (double*)malloc(pNNParams->L0cnt*sizeof(double));
		prevB[d][L21] = (double**)malloc(pNNParams->L2cnt*sizeof(double*));		for (i = 0; i < pNNParams->L2cnt; i++) prevB[d][L21][i] = (double*)malloc(pNNParams->L1cnt*sizeof(double));

		//-- Qing stuff
		adzev[d] = (double**)malloc((LAYERS - 1)*sizeof(double*));
		adzev[d][L10] = (double*)malloc(1 * sizeof(double));
		adzev[d][L21] = (double*)malloc(pNNParams->L2cnt * sizeof(double));
		ro[d] = (double*)malloc((LAYERS - 1)*sizeof(double));
		sigma[d] = (int*)malloc((LAYERS - 1)*sizeof(int));
		uW[d] = (double*)malloc(pNNParams->L1cnt*pNNParams->L0cnt * sizeof(double));
		tmpV1[d] = (double*)malloc((pNNParams->L1cnt + (pNNParams->L1cnt*pNNParams->L0cnt))* sizeof(double));
		ux[d] = (double*)malloc(pNNParams->L0cnt* sizeof(double));
		dxdW10[d] = (double**)malloc(pNNParams->L1cnt*pNNParams->L0cnt*sizeof(double*));
		for (i = 0; i<(pNNParams->L1cnt*pNNParams->L0cnt); i++) dxdW10[d][i] = (double*)malloc(pNNParams->L0cnt*sizeof(double));
		//-- CGD stuff
		cgd_sigma[d] = (double*)malloc(LAYERS*sizeof(double));
		cgd_lambda[d] = (double*)malloc(LAYERS*sizeof(double));
		cgd_lambdau[d] = (double*)malloc(LAYERS*sizeof(double));
		cgd_delta[d] = (double*)malloc(LAYERS*sizeof(double));
		cgd_p[d] = (double**)malloc((LAYERS - 1)*sizeof(double*));
		cgd_p[d][L0] = (double*)malloc(pNNParams->L0cnt*sizeof(double));
		cgd_p[d][L1] = (double*)malloc(pNNParams->L1cnt*sizeof(double));
		cgd_p[d][L2] = (double*)malloc(pNNParams->L2cnt*sizeof(double));
		cgd_r[d] = (double**)malloc((LAYERS - 1)*sizeof(double*));
		cgd_r[d][L0] = (double*)malloc(pNNParams->L0cnt*sizeof(double));
		cgd_r[d][L1] = (double*)malloc(pNNParams->L1cnt*sizeof(double));
		cgd_r[d][L2] = (double*)malloc(pNNParams->L2cnt*sizeof(double));
		cgd_s[d] = (double**)malloc((LAYERS - 1)*sizeof(double*));
		cgd_s[d][L0] = (double*)malloc(pNNParams->L0cnt*sizeof(double));
		cgd_s[d][L1] = (double*)malloc(pNNParams->L1cnt*sizeof(double));
		cgd_s[d][L2] = (double*)malloc(pNNParams->L2cnt*sizeof(double));
		cgd_sigmap[d] = (double**)malloc((LAYERS - 1)*sizeof(double*));
		cgd_sigmap[d][L10] = (double*)malloc(pNNParams->L0cnt*sizeof(double));
		cgd_sigmap[d][L21] = (double*)malloc(pNNParams->L1cnt*sizeof(double));
		cgd_tmpV1[d] = (double**)malloc((LAYERS - 1)*sizeof(double*));
		cgd_tmpV1[d][L10] = (double*)malloc(pNNParams->L0cnt*sizeof(double));
		cgd_tmpV1[d][L21] = (double*)malloc(pNNParams->L1cnt*sizeof(double));
		cgd_tmpV2[d] = (double**)malloc((LAYERS - 1)*sizeof(double*));
		cgd_tmpV2[d][L10] = (double*)malloc(pNNParams->L0cnt*sizeof(double));
		cgd_tmpV2[d][L21] = (double*)malloc(pNNParams->L1cnt*sizeof(double));
		cgd_tmpV3[d] = (double**)malloc((LAYERS - 1)*sizeof(double*));
		cgd_tmpV3[d][L10] = (double*)malloc(pNNParams->L0cnt*sizeof(double));
		cgd_tmpV3[d][L21] = (double*)malloc(pNNParams->L1cnt*sizeof(double));
		cgd_tmpV4[d] = (double**)malloc((LAYERS - 1)*sizeof(double*));
		cgd_tmpV4[d][L10] = (double*)malloc(pNNParams->L0cnt*sizeof(double));
		cgd_tmpV4[d][L21] = (double*)malloc(pNNParams->L1cnt*sizeof(double));
		cgd_newW[d] = (double**)malloc((LAYERS - 1)*sizeof(double*));
		cgd_newW[d][L10] = (double*)malloc(pNNParams->L0cnt*sizeof(double));
		cgd_newW[d][L21] = (double*)malloc(pNNParams->L1cnt*sizeof(double));
		beta[d] = (double*)malloc((LAYERS - 1)*sizeof(double));

		//-- temp matrices
		tmpM1[d] = (double***)malloc((LAYERS)*sizeof(double**));
		tmpM1[d][L0] = (double**)malloc(pNNParams->LNC*pNNParams->LNC*sizeof(double*)); for (i = 0; i < pNNParams->LNC; i++) tmpM1[d][L0][i] = (double*)malloc(pNNParams->LNC*sizeof(double));
		tmpM1[d][L1] = (double**)malloc(pNNParams->LNC*pNNParams->LNC*sizeof(double*)); for (i = 0; i < pNNParams->LNC; i++) tmpM1[d][L1][i] = (double*)malloc(pNNParams->LNC*sizeof(double));
		tmpM1[d][L2] = (double**)malloc(pNNParams->LNC*pNNParams->LNC*sizeof(double*)); for (i = 0; i < pNNParams->LNC; i++) tmpM1[d][L2][i] = (double*)malloc(pNNParams->LNC*sizeof(double));
		tmpM2[d] = (double***)malloc((LAYERS - 1)*sizeof(double**));
		tmpM2[d][L0] = (double**)malloc(pNNParams->LNC*pNNParams->LNC*sizeof(double*)); for (i = 0; i < pNNParams->LNC; i++) tmpM2[d][L0][i] = (double*)malloc(pNNParams->LNC*sizeof(double));
		tmpM2[d][L1] = (double**)malloc(pNNParams->LNC*pNNParams->LNC*sizeof(double*)); for (i = 0; i < pNNParams->LNC; i++) tmpM2[d][L1][i] = (double*)malloc(pNNParams->LNC*sizeof(double));
		tmpM2[d][L2] = (double**)malloc(pNNParams->LNC*pNNParams->LNC*sizeof(double*)); for (i = 0; i < pNNParams->LNC; i++) tmpM2[d][L2][i] = (double*)malloc(pNNParams->LNC*sizeof(double));
		tmpM3[d] = (double***)malloc((LAYERS - 1)*sizeof(double**));
		tmpM3[d][L0] = (double**)malloc(pNNParams->LNC*pNNParams->LNC*sizeof(double*)); for (i = 0; i < pNNParams->LNC; i++) tmpM3[d][L0][i] = (double*)malloc(pNNParams->LNC*sizeof(double));
		tmpM3[d][L1] = (double**)malloc(pNNParams->LNC*pNNParams->LNC*sizeof(double*)); for (i = 0; i < pNNParams->LNC; i++) tmpM3[d][L1][i] = (double*)malloc(pNNParams->LNC*sizeof(double));
		tmpM3[d][L2] = (double**)malloc(pNNParams->LNC*pNNParams->LNC*sizeof(double*)); for (i = 0; i < pNNParams->LNC; i++) tmpM3[d][L2][i] = (double*)malloc(pNNParams->LNC*sizeof(double));
		tmpM4[d] = (double***)malloc((LAYERS - 1)*sizeof(double**));
		tmpM4[d][L0] = (double**)malloc(pNNParams->LNC*pNNParams->LNC*sizeof(double*)); for (i = 0; i < pNNParams->LNC; i++) tmpM4[d][L0][i] = (double*)malloc(pNNParams->LNC*sizeof(double));
		tmpM4[d][L1] = (double**)malloc(pNNParams->LNC*pNNParams->LNC*sizeof(double*)); for (i = 0; i < pNNParams->LNC; i++) tmpM4[d][L1][i] = (double*)malloc(pNNParams->LNC*sizeof(double));
		tmpM4[d][L2] = (double**)malloc(pNNParams->LNC*pNNParams->LNC*sizeof(double*)); for (i = 0; i < pNNParams->LNC; i++) tmpM4[d][L2][i] = (double*)malloc(pNNParams->LNC*sizeof(double));
		tmpM5[d] = (double***)malloc((LAYERS - 1)*sizeof(double**));
		tmpM5[d][L0] = (double**)malloc(pNNParams->LNC*pNNParams->LNC*sizeof(double*)); for (i = 0; i < pNNParams->LNC; i++) tmpM5[d][L0][i] = (double*)malloc(pNNParams->LNC*sizeof(double));
		tmpM5[d][L1] = (double**)malloc(pNNParams->LNC*pNNParams->LNC*sizeof(double*)); for (i = 0; i < pNNParams->LNC; i++) tmpM5[d][L1][i] = (double*)malloc(pNNParams->LNC*sizeof(double));
		tmpM5[d][L2] = (double**)malloc(pNNParams->LNC*pNNParams->LNC*sizeof(double*)); for (i = 0; i < pNNParams->LNC; i++) tmpM5[d][L2][i] = (double*)malloc(pNNParams->LNC*sizeof(double));
		tmpM6[d] = (double***)malloc((LAYERS - 1)*sizeof(double**));
		tmpM6[d][L0] = (double**)malloc(pNNParams->LNC*pNNParams->LNC*sizeof(double*)); for (i = 0; i < pNNParams->LNC; i++) tmpM6[d][L0][i] = (double*)malloc(pNNParams->LNC*sizeof(double));
		tmpM6[d][L1] = (double**)malloc(pNNParams->LNC*pNNParams->LNC*sizeof(double*)); for (i = 0; i < pNNParams->LNC; i++) tmpM6[d][L1][i] = (double*)malloc(pNNParams->LNC*sizeof(double));
		tmpM6[d][L2] = (double**)malloc(pNNParams->LNC*pNNParams->LNC*sizeof(double*)); for (i = 0; i < pNNParams->LNC; i++) tmpM6[d][L2][i] = (double*)malloc(pNNParams->LNC*sizeof(double));
		tmpM7[d] = (double***)malloc((LAYERS - 1)*sizeof(double**));
		tmpM7[d][L0] = (double**)malloc(pNNParams->LNC*pNNParams->LNC*sizeof(double*)); for (i = 0; i < pNNParams->LNC; i++) tmpM7[d][L0][i] = (double*)malloc(pNNParams->LNC*sizeof(double));
		tmpM7[d][L1] = (double**)malloc(pNNParams->LNC*pNNParams->LNC*sizeof(double*)); for (i = 0; i < pNNParams->LNC; i++) tmpM7[d][L1][i] = (double*)malloc(pNNParams->LNC*sizeof(double));
		tmpM7[d][L2] = (double**)malloc(pNNParams->LNC*pNNParams->LNC*sizeof(double*)); for (i = 0; i < pNNParams->LNC; i++) tmpM7[d][L2][i] = (double*)malloc(pNNParams->LNC*sizeof(double));
		tmpM8[d] = (double***)malloc((LAYERS - 1)*sizeof(double**));
		tmpM8[d][L0] = (double**)malloc(pNNParams->LNC*pNNParams->LNC*sizeof(double*)); for (i = 0; i < pNNParams->LNC; i++) tmpM8[d][L0][i] = (double*)malloc(pNNParams->LNC*sizeof(double));
		tmpM8[d][L1] = (double**)malloc(pNNParams->LNC*pNNParams->LNC*sizeof(double*)); for (i = 0; i < pNNParams->LNC; i++) tmpM8[d][L1][i] = (double*)malloc(pNNParams->LNC*sizeof(double));
		tmpM8[d][L2] = (double**)malloc(pNNParams->LNC*pNNParams->LNC*sizeof(double*)); for (i = 0; i < pNNParams->LNC; i++) tmpM8[d][L2][i] = (double*)malloc(pNNParams->LNC*sizeof(double));
		tmpM9[d] = (double***)malloc((LAYERS - 1)*sizeof(double**));
		tmpM9[d][L0] = (double**)malloc(pNNParams->LNC*pNNParams->LNC*sizeof(double*)); for (i = 0; i < pNNParams->LNC; i++) tmpM9[d][L0][i] = (double*)malloc(pNNParams->LNC*sizeof(double));
		tmpM9[d][L1] = (double**)malloc(pNNParams->LNC*pNNParams->LNC*sizeof(double*)); for (i = 0; i < pNNParams->LNC; i++) tmpM9[d][L1][i] = (double*)malloc(pNNParams->LNC*sizeof(double));
		tmpM9[d][L2] = (double**)malloc(pNNParams->LNC*pNNParams->LNC*sizeof(double*)); for (i = 0; i < pNNParams->LNC; i++) tmpM9[d][L2][i] = (double*)malloc(pNNParams->LNC*sizeof(double));
		tmpM10[d] = (double***)malloc((LAYERS - 1)*sizeof(double**));
		tmpM10[d][L0] = (double**)malloc(pNNParams->LNC*pNNParams->LNC*sizeof(double*)); for (i = 0; i < pNNParams->LNC; i++) tmpM10[d][L0][i] = (double*)malloc(pNNParams->LNC*sizeof(double));
		tmpM10[d][L1] = (double**)malloc(pNNParams->LNC*pNNParams->LNC*sizeof(double*)); for (i = 0; i < pNNParams->LNC; i++) tmpM10[d][L1][i] = (double*)malloc(pNNParams->LNC*sizeof(double));
		tmpM10[d][L2] = (double**)malloc(pNNParams->LNC*pNNParams->LNC*sizeof(double*)); for (i = 0; i < pNNParams->LNC; i++) tmpM10[d][L2][i] = (double*)malloc(pNNParams->LNC*sizeof(double));
		tmpM11[d] = (double***)malloc((LAYERS - 1)*sizeof(double**));
		tmpM11[d][L0] = (double**)malloc(pNNParams->LNC*pNNParams->LNC*sizeof(double*)); for (i = 0; i < pNNParams->LNC; i++) tmpM11[d][L0][i] = (double*)malloc(pNNParams->LNC*sizeof(double));
		tmpM11[d][L1] = (double**)malloc(pNNParams->LNC*pNNParams->LNC*sizeof(double*)); for (i = 0; i < pNNParams->LNC; i++) tmpM11[d][L1][i] = (double*)malloc(pNNParams->LNC*sizeof(double));
		tmpM11[d][L2] = (double**)malloc(pNNParams->LNC*pNNParams->LNC*sizeof(double*)); for (i = 0; i < pNNParams->LNC; i++) tmpM11[d][L2][i] = (double*)malloc(pNNParams->LNC*sizeof(double));
		tmpM12[d] = (double***)malloc((LAYERS - 1)*sizeof(double**));
		tmpM12[d][L0] = (double**)malloc(pNNParams->LNC*pNNParams->LNC*sizeof(double*)); for (i = 0; i < pNNParams->LNC; i++) tmpM12[d][L0][i] = (double*)malloc(pNNParams->LNC*sizeof(double));
		tmpM12[d][L1] = (double**)malloc(pNNParams->LNC*pNNParams->LNC*sizeof(double*)); for (i = 0; i < pNNParams->LNC; i++) tmpM12[d][L1][i] = (double*)malloc(pNNParams->LNC*sizeof(double));
		tmpM12[d][L2] = (double**)malloc(pNNParams->LNC*pNNParams->LNC*sizeof(double*)); for (i = 0; i < pNNParams->LNC; i++) tmpM12[d][L2][i] = (double*)malloc(pNNParams->LNC*sizeof(double));
		tmpM13[d] = (double***)malloc((LAYERS - 1)*sizeof(double**));
		tmpM13[d][L0] = (double**)malloc(pNNParams->LNC*pNNParams->LNC*sizeof(double*)); for (i = 0; i < pNNParams->LNC; i++) tmpM13[d][L0][i] = (double*)malloc(pNNParams->LNC*sizeof(double));
		tmpM13[d][L1] = (double**)malloc(pNNParams->LNC*pNNParams->LNC*sizeof(double*)); for (i = 0; i < pNNParams->LNC; i++) tmpM13[d][L1][i] = (double*)malloc(pNNParams->LNC*sizeof(double));
		tmpM13[d][L2] = (double**)malloc(pNNParams->LNC*pNNParams->LNC*sizeof(double*)); for (i = 0; i < pNNParams->LNC; i++) tmpM13[d][L2][i] = (double*)malloc(pNNParams->LNC*sizeof(double));
		tmpM14[d] = (double***)malloc((LAYERS - 1)*sizeof(double**));
		tmpM14[d][L0] = (double**)malloc(pNNParams->LNC*pNNParams->LNC*sizeof(double*)); for (i = 0; i < pNNParams->LNC; i++) tmpM14[d][L0][i] = (double*)malloc(pNNParams->LNC*sizeof(double));
		tmpM14[d][L1] = (double**)malloc(pNNParams->LNC*pNNParams->LNC*sizeof(double*)); for (i = 0; i < pNNParams->LNC; i++) tmpM14[d][L1][i] = (double*)malloc(pNNParams->LNC*sizeof(double));
		tmpM14[d][L2] = (double**)malloc(pNNParams->LNC*pNNParams->LNC*sizeof(double*)); for (i = 0; i < pNNParams->LNC; i++) tmpM14[d][L2][i] = (double*)malloc(pNNParams->LNC*sizeof(double));
		tmpM15[d] = (double***)malloc((LAYERS - 1)*sizeof(double**));
		tmpM15[d][L0] = (double**)malloc(pNNParams->LNC*pNNParams->LNC*sizeof(double*)); for (i = 0; i < pNNParams->LNC; i++) tmpM15[d][L0][i] = (double*)malloc(pNNParams->LNC*sizeof(double));
		tmpM15[d][L1] = (double**)malloc(pNNParams->LNC*pNNParams->LNC*sizeof(double*)); for (i = 0; i < pNNParams->LNC; i++) tmpM15[d][L1][i] = (double*)malloc(pNNParams->LNC*sizeof(double));
		tmpM15[d][L2] = (double**)malloc(pNNParams->LNC*pNNParams->LNC*sizeof(double*)); for (i = 0; i < pNNParams->LNC; i++) tmpM15[d][L2][i] = (double*)malloc(pNNParams->LNC*sizeof(double));
		tmpM16[d] = (double***)malloc((LAYERS - 1)*sizeof(double**));
		tmpM16[d][L0] = (double**)malloc(pNNParams->LNC*pNNParams->LNC*sizeof(double*)); for (i = 0; i < pNNParams->LNC; i++) tmpM16[d][L0][i] = (double*)malloc(pNNParams->LNC*sizeof(double));
		tmpM16[d][L1] = (double**)malloc(pNNParams->LNC*pNNParams->LNC*sizeof(double*)); for (i = 0; i < pNNParams->LNC; i++) tmpM16[d][L1][i] = (double*)malloc(pNNParams->LNC*sizeof(double));
		tmpM16[d][L2] = (double**)malloc(pNNParams->LNC*pNNParams->LNC*sizeof(double*)); for (i = 0; i < pNNParams->LNC; i++) tmpM16[d][L2][i] = (double*)malloc(pNNParams->LNC*sizeof(double));
		G[d] = (double**)malloc(pNNParams->L1cnt*pNNParams->L0cnt*sizeof(double*)); for (i = 0; i < (pNNParams->L1cnt*pNNParams->L0cnt); i++) G[d][i] = (double*)malloc(pNNParams->L0cnt*sizeof(double));

		//-- Bundle parameters into MxData
		MxData[d].a = a[d];
		MxData[d].F = F[d];
		MxData[d].dF = dF[d];
		MxData[d].e = e[d];
		MxData[d].u = u[d];
		MxData[d].Ve = Ve[d];
		MxData[d].Vu = Vu[d];
		MxData[d].dk = dk[d];
		MxData[d].W = W[d];
		MxData[d].dW = dW[d];
		MxData[d].dJdW = dJdW[d];
		MxData[d].BPdW = BPdW[d];
		MxData[d].prevF = prevF[d];
		MxData[d].prevdF = prevdF[d];
		MxData[d].prevW = prevW[d];
		MxData[d].prevdW = prevdW[d];
		MxData[d].prevdJdW = prevdJdW[d];
		MxData[d].prevBPdW = prevBPdW[d];
		//--
		MxData[d].c = c[d];
		MxData[d].d = d_tmp[d];
		MxData[d].g = g[d];
		MxData[d].B = B[d];
		MxData[d].prevc = prevc[d];
		MxData[d].prevd = prevd[d];
		MxData[d].prevg = prevg[d];
		MxData[d].prevB = prevB[d];
		//--
		MxData[d].adzev = adzev[d];
		MxData[d].sigma = sigma[d];
		MxData[d].ro = ro[d];
		MxData[d].uW = uW[d];
		MxData[d].tmpV1 = tmpV1[d];
		MxData[d].ux = ux[d];
		MxData[d].dxdW10 = dxdW10[d];
		//--
		MxData[d].cgd_sigma = cgd_sigma[d];
		MxData[d].cgd_lambda = cgd_lambda[d];
		MxData[d].cgd_lambdau = cgd_lambdau[d];
		MxData[d].cgd_delta = cgd_delta[d];
		MxData[d].cgd_s = cgd_s[d];
		MxData[d].cgd_p = cgd_p[d];
		MxData[d].cgd_r = cgd_r[d];
		MxData[d].cgd_tmpV1 = cgd_tmpV1[d];
		MxData[d].cgd_tmpV2 = cgd_tmpV2[d];
		MxData[d].cgd_tmpV3 = cgd_tmpV3[d];
		MxData[d].cgd_tmpV4 = cgd_tmpV4[d];
		MxData[d].cgd_newW = cgd_newW[d];
		MxData[d].beta = beta[d];
		//--
		MxData[d].tmpM1 = tmpM1[d];
		MxData[d].tmpM2 = tmpM2[d];
		MxData[d].tmpM3 = tmpM3[d];
		MxData[d].tmpM4 = tmpM4[d];
		MxData[d].tmpM5 = tmpM5[d];
		MxData[d].tmpM6 = tmpM6[d];
		MxData[d].tmpM7 = tmpM7[d];
		MxData[d].tmpM8 = tmpM8[d];
		MxData[d].tmpM9 = tmpM9[d];
		MxData[d].tmpM10 = tmpM10[d];
		MxData[d].tmpM11 = tmpM11[d];
		MxData[d].tmpM12 = tmpM12[d];
		MxData[d].tmpM13 = tmpM13[d];
		MxData[d].tmpM14 = tmpM14[d];
		MxData[d].tmpM15 = tmpM15[d];
		MxData[d].tmpM16 = tmpM16[d];
		MxData[d].G = G[d];
	}

	//-- Do the following for each dataset; each Dataset is handled by one separate thread
	for (d = 0; d < pInputData->DatasetsCount; d++){

		//-- prepare Training parameters
		tp[d].DebugParms = pDebugParms;
		tp[d].NNParms = pNNParams;
		tp[d].TestId = pTestId;
		tp[d].DataSetId = d;
		tp[d].NetId = 0;
		tp[d].SampleCount = pSampleCount; tp[d].Sample = pSampleData[d][0]; tp[d].Target = pTargetData[d][0]; tp[d].SampleV = pSampleDataV[d][0]; tp[d].TargetV = pTargetDataV[d][0];
		tp[d].InputData = pInputData;
		tp[d].MxData = &MxData[d];

		//-- CreateThread()
		HTrain[d] = CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE)TrainSave_NN, &tp[d], 0, tid[d]);

		//-- Store Engine Handler
		tp[d].TrainInfo.DatasetId = d;
		tp[d].TrainInfo.ProcessId = GetCurrentProcessId();
		tp[d].TrainInfo.ThreadId = (*tid[d]);
		tp[d].TrainInfo.TestId = pTestId;
		//-- Store Thread Ids to be passed to Run()
		pNNParams->TrainingTid[d][0] = (*tid[d]);
	}
	WaitForMultipleObjects(pInputData->DatasetsCount, HTrain, TRUE, INFINITE);

	LogWrite(pDebugParms, LOG_INFO, "TrainAndRun_NN() CheckPoint 2\n", 0);

	//-- free()s
	for (d = 0; d < pInputData->DatasetsCount; d++){
		//-- Core network stuff
		free(a[d][L0]); 
		free(a[d][L1]); 
		free(a[d][L2]); 
		free(a[d]);
		free(F[d][L0]);
		free(F[d][L1]);
		free(F[d][L2]);
		free(F[d]);
		free(dF[d][L0]); free(dF[d][L1]); free(dF[d][L2]); free(dF[d]);
		free(prevF[d][L0]); free(prevF[d][L1]); free(prevF[d][L2]); free(prevF[d]);
		free(prevdF[d][L0]); free(prevdF[d][L1]); free(prevdF[d][L2]); free(prevdF[d]);
		free(e[d]); free(u[d]); free(Ve[d]); free(Vu[d]); free(dk[d]);
		for (i = 0; i < pNNParams->L1cnt; i++) free(W[d][L10][i]);
		for (i = 0; i < pNNParams->L2cnt; i++) free(W[d][L21][i]);
		free(W[d][L10]); free(W[d][L21]); free(W[d]);
		for (i = 0; i < pNNParams->L1cnt; i++) free(dW[d][L10][i]);
		for (i = 0; i < pNNParams->L2cnt; i++) free(dW[d][L21][i]);
		free(dW[d][L10]); free(dW[d][L21]); free(dW[d]);
		for (i = 0; i < pNNParams->L1cnt; i++) free(prevW[d][L10][i]);
		for (i = 0; i < pNNParams->L2cnt; i++) free(prevW[d][L21][i]);
		free(prevW[d][L10]); free(prevW[d][L21]); free(prevW[d]);
		for (i = 0; i < pNNParams->L1cnt; i++) free(prevdW[d][L10][i]);
		for (i = 0; i < pNNParams->L2cnt; i++) free(prevdW[d][L21][i]);
		free(prevdW[d][L10]); free(prevdW[d][L21]); free(prevdW[d]);

		//-- CFR/AG stuff
		free(c[d][L0]); free(c[d][L1]); free(c[d][L2]); free(c[d]);
		free(prevc[d][L0]); free(prevc[d][L1]); free(prevc[d][L2]); free(prevc[d]);
		for (i = 0; i < pNNParams->L1cnt; i++) free(d_tmp[d][L10][i]);
		for (i = 0; i < pNNParams->L2cnt; i++) free(d_tmp[d][L21][i]);
		free(d_tmp[d][L10]); free(d_tmp[d][L21]); free(d_tmp[d]);
		for (i = 0; i < pNNParams->L1cnt; i++) free(g[d][L10][i]);
		for (i = 0; i < pNNParams->L2cnt; i++) free(g[d][L21][i]);
		free(g[d][L10]); free(g[d][L21]); free(g[d]);
		for (i = 0; i < pNNParams->L1cnt; i++) free(prevg[d][L10][i]);
		for (i = 0; i < pNNParams->L2cnt; i++) free(prevg[d][L21][i]);
		free(prevg[d][L10]); free(prevg[d][L21]); free(prevg[d]);
		free(prevB[d]);

		//-- Qing stuff
		free(adzev[d][L10]); 
		free(adzev[d][L21]); 
		free(adzev[d]);
		free(ro[d]); 
		free(sigma[d]); 
		free(uW[d]); 
		//free(tmpV1[d]); 
		//free(ux[d]);
/*
		//-- temp matrices
		for (int l = L0; l <= L2; l++){
			for (i = 0; i < pNNParams->LNC; i++){
				free(tmpM1[d][l][i]); free(tmpM2[d][l][i]); free(tmpM3[d][l][i]); free(tmpM4[d][l][i]); free(tmpM5[d][l][i]); free(tmpM6[d][l][i]); free(tmpM7[d][l][i]); free(tmpM8[d][l][i]); free(tmpM9[d][l][i]);
				free(tmpM10[d][l][i]); free(tmpM11[d][l][i]); free(tmpM12[d][l][i]); free(tmpM13[d][l][i]); free(tmpM14[d][l][i]); free(tmpM15[d][l][i]); free(tmpM16[d][l][i]);
			}
			free(tmpM1[d][l]); free(tmpM2[d][l]); free(tmpM3[d][l]); free(tmpM4[d][l]); free(tmpM5[d][l]); free(tmpM6[d][l]); free(tmpM7[d][l]); free(tmpM8[d][l]); free(tmpM9[d][l]);
			free(tmpM10[d][l]); free(tmpM11[d][l]); free(tmpM12[d][l]); free(tmpM13[d][l]); free(tmpM14[d][l]); free(tmpM15[d][l]); free(tmpM16[d][l]);
		}
		free(tmpM1[d]); free(tmpM2[d]); free(tmpM3[d]); free(tmpM4[d]); free(tmpM5[d]); free(tmpM6[d]); free(tmpM7[d]); free(tmpM8[d]); free(tmpM9[d]);
		free(tmpM10[d]); free(tmpM11[d]); free(tmpM12[d]); free(tmpM13[d]); free(tmpM14[d]); free(tmpM15[d]); free(tmpM16[d]);
		*/
	}
	free(a); free(F); free(dF); free(prevF); free(prevdF);
	free(W); free(dW); free(prevW); free(prevdW);
	free(tmpM1); free(tmpM2); free(tmpM3); free(tmpM4); free(tmpM5); free(tmpM6); free(tmpM7); free(tmpM8); free(tmpM9);
	free(tmpM10); free(tmpM11); free(tmpM12); free(tmpM13); free(tmpM14); free(tmpM15); free(tmpM16);


	return 0;
}

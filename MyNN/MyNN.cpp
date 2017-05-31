#include <vld.h>
#include <MyNN.h>

	void cNN::setTopology() {
		char** DescList = MallocArray<char>(NN_MAXLEVELS, 256);

		//-- 1. Put the comma-separated string values into an array of strings. Max desc length=10
		int Levcnt = cslToArray(levelRatioS, ',', DescList);

		//-- 2. For Network Topology, convert string to float
		for (int i = 0; i <= Levcnt; i++) {
			levelRatio[i] = atof(DescList[i]);
		}
		// set LevelsCount
		levelsCnt = (Levcnt + 2);

		// set NodesCount, NodesCountTotal
		nodesCnt[0] = SampleLen;
		nodesCnt[levelsCnt - 1] = TargetLen;
		nodesCntTotal = SampleLen + TargetLen;
		//-- calc nodescount[], totalnodescount
		for (int nl = 0; nl<(levelsCnt - 2); nl++) {
			nodesCnt[nl + 1] = (int)floor(nodesCnt[nl] * levelRatio[nl]);
			nodesCntTotal += nodesCnt[nl+1];
		}
		//-- add context neurons
		if (useContext > 0) {
			for (int l = levelsCnt-2; l >0; l--) {
				nodesCnt[l-1] += nodesCnt[l];
				nodesCntTotal += nodesCnt[l];
			}
		}

		//-- calc totalweightscount
		weightsCntTotal = 0;
		for (int nl = 0; nl<(levelsCnt - 1); nl++) {
			for (int nn1 = 0; nn1<nodesCnt[nl + 1]; nn1++) {
				for (int nn0 = 0; nn0<nodesCnt[nl]; nn0++) {
					weightsCntTotal++;
				}
			}
		}

		FreeArray(NN_MAXLEVELS, 100, DescList);
	}
/*	void cNN::mallocNNLog(int tscnt) {
		//-- mallocs specific portions of coreLog (FinalW, IntP)

		//-- FinalW
		coreLog->NNFinalW = (tNNWeight***)malloc((levelsCnt - 1) * sizeof(tNNWeight**));
		for (int l = 0; l < (levelsCnt - 1); l++) {
			coreLog->NNFinalW[l] = (tNNWeight**)malloc(nodesCnt[l] * sizeof(tNNWeight*));
			for (int fn = 0; fn < nodesCnt[l]; fn++) {
				coreLog->NNFinalW[l][fn] = (tNNWeight*)malloc(nodesCnt[l+1] * sizeof(tNNWeight));
			}
		}
		//-- IntP
		coreLog->IntP = MallocArray<tLogInt>(tscnt);
	}
	void cNN::freeNNLog() {
		//-- FinalW
		for (int l = 0; l < (levelsCnt - 1); l++) {
			for (int fn = 0; fn < nodesCnt[l]; fn++) {
				free(coreLog->NNFinalW[l][fn]);
			}
			free(coreLog->NNFinalW[l]);
		}
		free(coreLog->NNFinalW);
		//-- IntP
		free(coreLog->IntP);
	}
*/
	//--
	void cNN::init() {
		int i, l, k;

		//-- 1. malloc(s)
		mallocNNMem();

		//-- 2. Init neurons
		for (l = 0; l < levelsCnt; l++) {
			for (i = 0; i < nodesCnt[l]; i++) {
				a[l][i] = 0;
				F[l][i] = 0;
				dF[l][i] = 0;
			}
		}

		//-- 3. Init weights
		k = 0;
		for (l = 0; l < (levelsCnt - 1); l++) {
			for (int fn = 0; fn < nodesCnt[l]; fn++) {
				for (int tn = 0; tn < nodesCnt[l+1]; tn++) {
					W[l][fn][tn] = MyRndDbl(-1 / sqrt((double)nodesCnt[l + 1]), 1 / sqrt((double)nodesCnt[l]));
					dW[l][fn][tn] = MyRndDbl(-1 / sqrt((double)nodesCnt[l + 1]), 1 / sqrt((double)nodesCnt[l]));
					dJdW[l][fn][tn] = 0;

					//-- SCGD stuff
					if (BPAlgo==BP_SCGD) {
						LVV_W[k] = &W[l][fn][tn];
						LVV_dW[k] = &dW[l][fn][tn];
						LVV_dJdW[k] = &dJdW[l][fn][tn];
						prevLVV_W[k] = &W[l][fn][tn];
						prevLVV_dW[k] = &dW[l][fn][tn];
						prevLVV_dJdW[k] = &dJdW[l][fn][tn];
						k++;
					}
				}
			}
		}

		//-- 4. SCGD stuff
		BPCount = 0; SCGD_progK = 0;
		/*
		k = 0;
		for (l = 0; l < (levelsCnt-1); l++) {
		for (i = 0; i < (nodesCnt[l+1] * nodesCnt[l]); i++) {
		x = (int)(i / nodesCnt[l]);
		y = i%nodesCnt[l];
		LVV_W[k] = &W[l][x][y];
		LVV_dW[k] = &dW[l][x][y];
		LVV_dJdW[k] = &dJdW[l][x][y];
		prevLVV_W[k] = &W[l][x][y];
		prevLVV_dW[k] = &dW[l][x][y];
		prevLVV_dJdW[k] = &dJdW[l][x][y];
		k++;
		}
		}
		*/
	}
	int cNN::train(tDebugInfo* pDebugParms, int DatasetId, int sampleCnt, int sampleLen, int targetLen, double** SampleT, double** TargetT, int useValidation, double** SampleV, double** TargetV) {
		dsid = DatasetId;

		//-- first, we need to set net topology, and init F,W
		setTopology();
		init();

		//-- then, run the proper training protocol
		switch (TrainingProtocol) {
		case TP_STOCHASTIC:
			train_Stochastic(sampleCnt, sampleLen, targetLen, SampleT, TargetT, useValidation, SampleV, TargetV);
			break;
		case TP_BATCH:
			train_Batch(sampleCnt, sampleLen, targetLen, SampleT, TargetT, useValidation, SampleV, TargetV);
			break;
		case TP_ONLINE:
			//train_Online(sampleCnt, sampleLen, targetLen, SampleT, TargetT, useValidation, SampleV, TargetV);
			break;
		}

		//-- finally, save weights
		SaveFinalW();

		return 0;
	}
	int cNN::run(tDebugInfo* pDebugParms, int sampleCnt, int sampleLen, int targetLen, double** S, double** T, void* img) {
		//dsid = DatasetId;

		int i, s, l, j;
		double vActual;
		double* vPrediction = nullptr;

		//-- 0. malloc(s)
		double* tmpSample = (double*)malloc(sampleLen * sizeof(double));

		//-- 1. Load W*** from NNParms->NNFinalW[Level][FromN][ToN] 
		double*** savedW = (double***)img;
		for (l = 0; l<(levelsCnt-1); l++) {
			for (j = 0; j < nodesCnt[l]; j++) {
				for (i = 0; i < nodesCnt[l+1]; i++) {
					W[l][j][i] = savedW[l][j][i];
				}
			}
		}

		//-- 2. Reset Context Neurons
		if (useContext>0) FB();

		//-- 3. Write First window of data, with no prediction (that is, write the first sample)
		for (i = 0; i<sampleLen; i++) SaveRunData(i, S[0][i], NULL);

		//-- 4. Write Training Set data, with next-step prediction

		//-- 4.1 In-Sample
		for (s = 0; s<sampleCnt; s++) {
			for (i = 0; i < sampleLen; i++) {
				tmpSample[i] = S[s][i];		//-- Only used for the last sample ( pSample[pSampleCount-1] )
				F[0][i] = tmpSample[i];		//-- Present each sample to input neurons
			}
			FF();							//-- Feed-Forward the network;
			vPrediction = F[levelsCnt-1];	//-- Predicted  Data. All steps
			vActual = T[s][0];
			//-- Write RunLog structure
			SaveRunData(sampleLen+s, vActual, vPrediction);
		}

		//-- 4.2 Out-of-Sample
		for (s = 0; s < targetLen; s++) {

			// Target[s] only exist while s<SampleCount. Beyond that, Actual is prediction from previous step
			vActual = vPrediction[0];

			//-- Sample beyond SampleCount must be build, regardless of pOOS
			ShiftArray(SHIFT_BACKWARD, sampleLen, tmpSample, vActual);

			for (i = 0; i < sampleLen; i++) F[0][i] = tmpSample[i];	//-- Present each sample to input neurons
			FF();														//-- Feed-Forward the network;
			vPrediction = F[levelsCnt-1];								//-- Predicted  Data. All steps

			SaveRunData((s + sampleCnt+sampleLen), vActual, vPrediction);
		}

		//-- 5. frees()
		free(tmpSample);

		return 0;
	}
/*	int  cNN::setParms(tDebugInfo* DebugParms, tDBConnection* DBConn, int pid, int tid, bool load, int iSampleCnt) {
		//-- (pre)
		if (load) {
			if (LoadCoreParms_NN(DebugParms, DBConn, pid, tid, &SampleLen, &TargetLen, &useContext, &MaxEpochs, &BPAlgo, &ActivationFunction, &levelRatioS, &LearningRate, &LearningMomentum, &HCPbeta, &TargetMSE) <0) return -1;
		}
		//-- (post)
		TimeStepsCount = MaxEpochs*((BPAlgo == BP_SCGD) ? iSampleCnt : 1);
		MSECount = MaxEpochs;
		return 0;
	}
*/	int  cNN::LoadImage(tDebugInfo* DebugParms, tDBConnection* DBConn, int pid, int tid) {
		if (LoadCoreImage_NN(DebugParms, DBConn, pid, tid, NNLog[dsid]->FinalW) <0) return -1;
		return 0;
	}
	void cNN::mallocLogs(int dscnt) {
		//-- NN-specific logs only
		for (int d = 0; d<dscnt; d++) NNLog[d] = new cNNLog(levelsCnt, nodesCnt, TimeStepsCount, weightsCntTotal);
	}
	void cNN::getScaleRange(double* oScaleMin, double* oScaleMax) {
		switch (ActivationFunction) {
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
	}
	//--
	void cNN::mallocNNMem() {
		int i, l;

		//-- node levels -> [Levels]

		a = (double**)malloc(levelsCnt * sizeof(double*));					// Core
		F = (double**)malloc(levelsCnt * sizeof(double*));					// Core
		dF = (double**)malloc(levelsCnt * sizeof(double*));				// Core
		edF = (double**)malloc(levelsCnt * sizeof(double*));				// Core
		c = (double**)malloc(levelsCnt * sizeof(double*));					// CFR/AG
		for (l = 0; l < levelsCnt; l++) {
			a[l] = (double*)malloc(nodesCnt[l] * sizeof(double));
			F[l] = (double*)malloc(nodesCnt[l] * sizeof(double));
			dF[l] = (double*)malloc(nodesCnt[l] * sizeof(double));
			edF[l] = (double*)malloc(nodesCnt[l] * sizeof(double));
			c[l] = (double*)malloc(nodesCnt[l] * sizeof(double));
		}
		//-- outer node only
		e = (double*)malloc(nodesCnt[levelsCnt-1] * sizeof(double));
		u = (double*)malloc(nodesCnt[levelsCnt-1] * sizeof(double));
		dk = (double*)malloc(nodesCnt[levelsCnt-1] * sizeof(double));

		//-- weight levels -> [Levels-1][Time]
		W = (double***)malloc((levelsCnt - 1) * sizeof(double**));					// Core
		dW = (double***)malloc((levelsCnt - 1) * sizeof(double**));					// Core
		dJdW = (double***)malloc((levelsCnt - 1) * sizeof(double**));					// Core
		prevW = (double***)malloc((levelsCnt - 1) * sizeof(double**));					// Core
		prevdW = (double***)malloc((levelsCnt - 1) * sizeof(double**));					// Core
		prevdJdW = (double***)malloc((levelsCnt - 1) * sizeof(double**));					// Core
		BdW = (double***)malloc((levelsCnt - 1) * sizeof(double**));					// Core
		for (l = 0; l < (levelsCnt-1); l++) {
			W[l] = (double**)malloc(nodesCnt[l] * sizeof(double*));
			dW[l] = (double**)malloc(nodesCnt[l] * sizeof(double*));
			dJdW[l] = (double**)malloc(nodesCnt[l] * sizeof(double*));
			prevW[l] = (double**)malloc(nodesCnt[l] * sizeof(double*));
			prevdW[l] = (double**)malloc(nodesCnt[l] * sizeof(double*));
			prevdJdW[l] = (double**)malloc(nodesCnt[l] * sizeof(double*));
			BdW[l] = (double**)malloc(nodesCnt[l] * sizeof(double*));
			for (i = 0; i < nodesCnt[l]; i++) {
				W[l][i] = (double*)malloc(nodesCnt[l + 1] * sizeof(double));
				dW[l][i] = (double*)malloc(nodesCnt[l + 1] * sizeof(double));
				dJdW[l][i] = (double*)malloc(nodesCnt[l + 1] * sizeof(double));
				prevW[l][i] = (double*)malloc(nodesCnt[l + 1] * sizeof(double));
				prevdW[l][i] = (double*)malloc(nodesCnt[l + 1] * sizeof(double));
				prevdJdW[l][i] = (double*)malloc(nodesCnt[l + 1] * sizeof(double));
				BdW[l][i] = (double*)malloc(nodesCnt[l + 1] * sizeof(double));
			}
		}
		//-- SCGD stuff
		LVV_W = (double**)malloc(weightsCntTotal * sizeof(double*));
		LVV_dW = (double**)malloc(weightsCntTotal * sizeof(double*));
		LVV_dJdW = (double**)malloc(weightsCntTotal * sizeof(double*));
		prevLVV_W = (double**)malloc(weightsCntTotal * sizeof(double*));
		prevLVV_dW = (double**)malloc(weightsCntTotal * sizeof(double*));
		prevLVV_dJdW = (double**)malloc(weightsCntTotal * sizeof(double*));
	}
	void cNN::freeNNMem() {
		int l, i;
		//-- node levels -> [Levels][Time]
		for (l = 0; l < levelsCnt; l++) {
			free(a[l]);
			free(F[l]);
			free(dF[l]);
			free(edF[l]);
			free(c[l]);
		}
		free(a);
		free(F);
		free(dF);
		free(edF);
		free(c);
		//-- outer node only -> [Time]
		free(e);
		free(u);
		free(dk);

		//-- weight levels -> [Levels-1][Time]
		for (l = 0; l < (levelsCnt - 1); l++) {
			for (i = 0; i < nodesCnt[l]; i++) {
				free(W[l][i]);
				free(dW[l][i]);
				free(prevW[l][i]);
				free(prevdW[l][i]);
				free(prevdJdW[l][i]);
				free(dJdW[l][i]);
				free(BdW[l][i]);
			}
			free(W[l]);
			free(dW[l]);
			free(prevW[l]);
			free(prevdW[l]);
			free(prevdJdW[l]);
			free(dJdW[l]);
			free(BdW[l]);
		}
		free(W);
		free(dW);
		free(prevW);
		free(prevdW);
		free(prevdJdW);
		free(dJdW);
		free(BdW);

		//-- SCGD stuff
		free(LVV_W);
		free(LVV_dW);
		free(LVV_dJdW);
		free(prevLVV_W);
		free(prevLVV_dW);
		free(prevLVV_dJdW);
	}
	
	void cNN::initdW() {
		//-- used only for Batch Training
		for (int l = 0; l < (levelsCnt - 1); l++) {
			for (int fn = 0; fn < nodesCnt[l]; fn++) {
				for (int tn = 0; tn < nodesCnt[l+1]; tn++) {
					dW[l][fn][tn] = 0;	// MyRndDbl(-1 / sqrt((double)nodesCnt[l + 1]), 1 / sqrt((double)nodesCnt[l]));
					dJdW[l][fn][tn] = 0;
					BdW[l][fn][tn] = 0;
				}
			}
		}
	}
	void cNN::train_Batch(int sampleCnt, int sampleLen, int targetLen, double** S, double** T, int useV, double** Sv, double** Tv){
		int i, o;
		double MSE_T = 1, TSE_T;
		double MSE_V = 0, TSE_V = 0;
		double prevMSE_T;
		int epoch;
		for (epoch = 0; epoch < ((BPAlgo==BP_SCGD)?1:MaxEpochs); epoch++) {
			initdW();
			TSE_T = 0;
			for (int s = 0; s < sampleCnt; s++) {
				//-- 1. present sample to L0 neurons, and target to u[]
				for (i = 0; i < sampleLen; i++)	F[0][i] = S[s][i];
				for (i = 0; i < targetLen; i++) u[i] = T[s][i];
				//-- 2. FeedForward (also calcs e[] )
				FF();
				//-- 3. calc TSE
				for (o = 0; o < nodesCnt[levelsCnt-1]; o++) TSE_T += pow(e[o], 2);
				//-- 4. BackPropagation calculates dW
				BP();
				//-- 5. BdW (Batch dW) is the cumulative sum of dW for all samples
				for (int l = 0; l<(levelsCnt-1); l++) MplusM(nodesCnt[l], nodesCnt[l+1], BdW[l], dW[l], BdW[l]);
			}
			//-- Update Weights (W = W + BdW)
			for (int l = 0; l<(levelsCnt-1); l++) MplusM(nodesCnt[l], nodesCnt[l+1], W[l], BdW[l], W[l]);

			prevMSE_T = MSE_T;	// save previous MSE
			MSE_T = TSE_T / nodesCnt[levelsCnt-1] /sampleCnt;
			if (useValidation>0) MSE_V = TSE_V / nodesCnt[levelsCnt-1] /sampleCnt;
			if (useValidation>0 && StopAtDivergence == 1 && MSE_T > prevMSE_T) break;
			WaitForSingleObject(ScreenMutex, 10);
			gotoxy(0, ScreenPos); printf("\rProcess %6d, Thread %6d, Epoch %6d , Training MSE=%f , Validation MSE=%f", pid, tid, epoch, MSE_T, MSE_V);
			ReleaseMutex(ScreenMutex);
			if (BPAlgo != BP_SCGD) SaveMSEData(epoch, MSE_T, MSE_V);
			if (MSE_T < TargetMSE) break;
		}
		coreLog[dsid]->ActualEpochs = epoch;
	}
	void cNN::train_Stochastic(int sampleCnt, int sampleLen, int targetLen, double** S, double** T, int useV, double** Sv, double** Tv) {
		int i, o;
		double MSE_T = 1, TSE_T;
		double MSE_V=0, TSE_V = 0;
		double prevMSE_T;
		int epoch;
		for (epoch = 0; epoch < MaxEpochs; epoch++) {
			TSE_T = 0;
			for (int s = 0; s < sampleCnt; s++) {
				//-- 1. present sample to L0 neurons, and target to u[]
				for (i = 0; i < sampleLen; i++)	F[0][i] = S[s][i];
				for (i = 0; i < targetLen; i++) u[i] = T[s][i];
				//-- 2. FeedForward (also calcs e[] )
				FF();
				//-- 3. calc TSE
				for (o = 0; o < nodesCnt[levelsCnt-1]; o++) TSE_T += pow(e[o], 2);				
				//-- 4. BackPropagation calculates dW
				BP();
				//-- 5. Update Weights (W = W + dW)
				for (int l = 0; l<(levelsCnt-1); l++) MplusM(nodesCnt[l], nodesCnt[l+1], W[l], dW[l], W[l]);
			}
			prevMSE_T = MSE_T;	// save previous MSE
			MSE_T = TSE_T / nodesCnt[levelsCnt-1] /sampleCnt;
			if (useValidation>0) MSE_V = TSE_V / nodesCnt[levelsCnt-1] /sampleCnt;
			if (useValidation>0 && StopAtDivergence == 1 && MSE_T > prevMSE_T) break;
			WaitForSingleObject(ScreenMutex, 10);
			gotoxy(0, ScreenPos); printf("\rProcess %6d, Thread %6d, Epoch %6d , Training MSE=%f , Validation MSE=%f", pid, tid, epoch, MSE_T, MSE_V);
			ReleaseMutex(ScreenMutex);
			if (BPAlgo != BP_SCGD) SaveMSEData(epoch, MSE_T, MSE_V);
			if (MSE_T < TargetMSE) break;
		}
		coreLog[dsid]->ActualEpochs = epoch;
	}

	void cNN::SaveMSEData(int pEpoch, double pMSE_T, double pMSE_V) {
		coreLog[dsid]->MSEOutput[pEpoch].ProcessId = pid;
		coreLog[dsid]->MSEOutput[pEpoch].ThreadId = tid;
		coreLog[dsid]->MSEOutput[pEpoch].Epoch = pEpoch;
		coreLog[dsid]->MSEOutput[pEpoch].MSE_T = pMSE_T;
		coreLog[dsid]->MSEOutput[pEpoch].MSE_V = pMSE_V;
	}
	void cNN::SaveRunData(int pPos, double pActual, double* pPredicted) {
		coreLog[dsid]->RunOutput[pPos].ProcessId = pid;
		coreLog[dsid]->RunOutput[pPos].ThreadId = tid;
		coreLog[dsid]->RunOutput[pPos].Pos = pPos;
		coreLog[dsid]->RunOutput[pPos].Actual_TRS = pActual;
		coreLog[dsid]->RunOutput[pPos].Predicted_TRS = (pPredicted == NULL) ? 0 : pPredicted[0];
	}
	void cNN::SaveFinalW() {
		//-- This should be called only once at the end of training
		int i, j, l;
		for (l = 0; l<(levelsCnt-1); l++) {
			for (j = 0; j < nodesCnt[l]; j++) {
				for (i = 0; i < nodesCnt[l+1]; i++) {
					NNLog[dsid]->FinalW[l][j][i] = W[l][j][i];
				}
			}
		}
	}
	void cNN::SaveCoreData_SCGD(int epoch, int BPid, int k, int timeStep, double delta, double mu, double alpha, double beta, double lambda, double lambdau, double rnorm, double enorm, double comp) {
		NNLog[dsid]->IntP[timeStep].ProcessId = pid;
		NNLog[dsid]->IntP[timeStep].ThreadId = tid;
		NNLog[dsid]->IntP[timeStep].Epoch = epoch;
		NNLog[dsid]->IntP[timeStep].BPid = BPid;
		NNLog[dsid]->IntP[timeStep].K = k;
		NNLog[dsid]->IntP[timeStep].delta = delta;
		NNLog[dsid]->IntP[timeStep].mu = mu;
		NNLog[dsid]->IntP[timeStep].alpha = alpha;
		NNLog[dsid]->IntP[timeStep].beta = beta;
		NNLog[dsid]->IntP[timeStep].lambda = lambda;
		NNLog[dsid]->IntP[timeStep].lambdau = lambdau;
		NNLog[dsid]->IntP[timeStep].rnorm = rnorm;
		NNLog[dsid]->IntP[timeStep].enorm = enorm;
		NNLog[dsid]->IntP[timeStep].comp = comp;
	}

	void cNN::SavePrevWeights() {
		for (int l = 0; l < (levelsCnt - 1); l++) {
			for (int j = 0; j < nodesCnt[l]; j++) {
				for (int i = 0; i < nodesCnt[l + 1]; i++) {
					//-- (t-1)
					prevW[l][j][i] = W[l][j][i];
					prevdW[l][j][i] = dW[l][j][i];
				}
			}
		}
	}

	void cNN::Calc_dJdW(bool doFF, bool doCalcH) {

		//-- prevdJdW is only needed by BP_QUICKPROP
		if (BPAlgo==BP_QUICKPROP) {
			for(int l=0; l<levelsCnt; l++) MCopy(nodesCnt[l], nodesCnt[l+1], dJdW[l], prevdJdW[l]);
		}

		if (doFF) FF();

		for (int l = levelsCnt-1; l>0; l--) {

			if (l==(levelsCnt-1)) {
				//-- top level only
				VbyV2V(nodesCnt[l], e, dF[l], edF[l]);								// edF(l) = e * F'(l)
			} else {
				//-- lower levels
				MbyV(nodesCnt[l], nodesCnt[l+1], W[l], false, edF[l+1], edF[l]);		// edF(l) = edF(l+1) * WT(l+1)
				VbyV2V(nodesCnt[l], edF[l], dF[l], edF[l]);							// edF(l) = edF(l)   * F'(l)
			}
			//-- common
			VbyV2M(nodesCnt[l], edF[l], nodesCnt[l-1], F[l-1], true, dJdW[l-1]);	// dJdW(l) = edF(l) * F(l-1)
		}

		//-- calc Hessian Matrix
		if (doCalcH) Calc_H();
	}
	void cNN::dEdW_at_w_LVV(double** LVV_W, double* w_new, double* odEdW_at_w) {

		double* tmpW = (double*)malloc(weightsCntTotal*sizeof(double));

		//-- 1. save w vector into tmpW
		VCopy(weightsCntTotal, LVV_W, tmpW);
		//-- 2. put w_new into M
		VCopy(weightsCntTotal, w_new, LVV_W);
		//-- 3. FF to recalc E
		FF();
		//-- 4. calc dE/dW whole matrix
		Calc_dJdW(false, false);
		//-- 5. return vector is one row of dE/dW corresponding to w_idx
		VCopy(weightsCntTotal, LVV_dJdW, odEdW_at_w);
		//-- 6. put original w back into place, and re-run FF
		VCopy(weightsCntTotal, tmpW, LVV_W);
		FF();

		free(tmpW);
	}
	double cNN::E_at_w_LVV(double** LVV_W, double* w_new) {
		double ret;
		double* tmpW = (double*)malloc(weightsCntTotal*sizeof(double));

		//-- 1. save w vector into tmpW
		VCopy(weightsCntTotal, LVV_W, tmpW);
		//-- 2. put w_new into LVV_W
		VCopy(weightsCntTotal, w_new, LVV_W);
		//-- 3. FF to recalc E
		FF();
		//-- 5. return value is Mx->norm_e after FF
		ret = norm_e;
		//-- 6. put original w back into place, and re-run FF
		VCopy(weightsCntTotal, tmpW, LVV_W);
		FF();
		free(tmpW);

		return ret;
	}
	void cNN::Calc_H() {
		// Hessian matrices for the whole network. There is one matrix for each neuron (n)
		for (int l = 0; l<(levelsCnt-1); l++) {
			for (int n = 0; n < nodesCnt[l + 1]; n++) {
				for (int j = 0; j < nodesCnt[l]; j++) {
					for (int i = 0; i < nodesCnt[l]; i++) {
						H[l][n][j][i] = F[l][j] * F[l][i] * Derivate2(a[l+1][n]);
					}
				}
			}
		}

	}
	void cNN::Activate(double a, double* oF, double* odF) {
		switch (ActivationFunction) {
		case NN_ACTIVATION_TANH:
			(*oF) = tanh(a);
			break;
		case NN_ACTIVATION_EXP4:
			(*oF) = 1 / (1 + exp(-4 * a));
			break;
		default:
			(*oF) = tanh(a);
			break;
		}
		(*odF) = Derivate(a);
	}
	double cNN::Derivate(double INval) {
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
	double cNN::Derivate2(double INval) {
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

	void cNN::FF() {
		//-- classic Feed-Forward
		for (int l = 1; l < levelsCnt; l++) {
			for (int i = 0; i < nodesCnt[l]; i++) {
				a[l][i] = 0;
				for (int j = 0; j < nodesCnt[l - 1]; j++) {
					a[l][i] += F[l-1][j] * W[l-1][j][i];
				}
				Activate(a[l][i], &F[l][i], &dF[l][i]);
			}
		}
		//-- calc e, ||e||
		VminusV(nodesCnt[levelsCnt-1], u, F[levelsCnt-1], e);
		norm_e = Vnorm(nodesCnt[levelsCnt-1], F[levelsCnt-1]);

		//-- feed back to context neurons
		if (useContext>0) FB();
	}
	void cNN::FB() {
		for (int l = levelsCnt-2; l >0; l--) {
			for (int i = 0; i<nodesCnt[l]; i++) {
				F[l-1][nodesCnt[l-1]-i-1] = F[l][nodesCnt[l]-i-1];
			}
		}
	}
	void cNN::BP_Std() {

		//Calc_dW();	// dW = lr*@J/@W
/*
		int i, h, o;
		double sk;
		//double BPdW;
		//-- 2 -> 1
		for (h = 0; h < nodesCnt[1]; h++) {
			for (o = 0; o < nodesCnt[2]; o++) {
				dk[o] = e[o] * dF[2][o];
				dJdW[1][h][o] = dk[o] * F[1][h];
				//dJdW[1][h][o] = LearningRate*dk[o] * F[1][h];
				//dW[1][h][o] = (1-LearningMomentum)*dJdW[1][h][o] + LearningMomentum*prevdW[1][h][o];
				//BPdW = LearningRate*dk[o] * F[1][h];
				//dW[1][h][o] = (1-LearningMomentum)*BPdW + LearningMomentum*prevdW[1][h][o];
				//W[1][h][o] += dW[1][h][o];
			}
		}

		//-- 1 -> 0
		for (i = 0; i < (nodesCnt[0]); i++) {
			for (h = 0; h < nodesCnt[1]; h++) {
				sk = 0;
				for (o = 0; o < nodesCnt[2]; o++) sk += W[1][h][o] * dk[o];
				dJdW[0][i][h] = sk*dF[1][h] * F[0][i];
				//dJdW[0][i][h] = LearningRate*sk*dF[1][h] * F[0][i];
				//dW[0][i][h] = (1-LearningMomentum)*dJdW[0][i][h] + LearningMomentum*prevdW[0][i][h];
				//BPdW = LearningRate*sk*dF[1][h] * F[0][i];
				//dW[0][i][h] = (1-LearningMomentum)*BPdW + LearningMomentum*prevdW[0][i][h];
				//W[0][i][h] += dW[0][i][h];
			}
		}
*/
		Calc_dJdW(false, false);
		for (int l = 0; l<(levelsCnt - 1); l++) {
			MbyS(nodesCnt[l], nodesCnt[l+1], dJdW[l], LearningRate, dJdW[l]);			//-- dJdW = dJdW * lr
			MbyS(nodesCnt[l], nodesCnt[l+1], dJdW[l], (1-LearningMomentum), dW[l]);		//-- dW = dJdW * (1-lm)
			MbyS(nodesCnt[l], nodesCnt[l+1], prevdW[l], LearningMomentum, prevdW[l]);	//-- prevdW = prevdW * lm
			MplusM(nodesCnt[l], nodesCnt[l+1], dW[l], prevdW[l], dW[l]);				//-- dW = dW + prevdW
		}

	}
	void cNN::BP_scgd() {
		int k;
		int maxk = MaxEpochs;

		double sigma, delta, mu, alpha, beta = 0, b1, b2;
		double lambda, lambdau;
		double rnorm, pnorm, pnorm2;
		double e_old, e_new, comp;
		//double kcomp;
		bool success;
		double epsilon = TargetMSE / nodesCnt[levelsCnt-1];

		double* p = (double*)malloc(weightsCntTotal * sizeof(double));
		double* r = (double*)malloc(weightsCntTotal * sizeof(double));
		double* s = (double*)malloc(weightsCntTotal * sizeof(double));
		double* dW = (double*)malloc(weightsCntTotal * sizeof(double));
		double* TotdW = (double*)malloc(weightsCntTotal * sizeof(double));
		double* newW = (double*)malloc(weightsCntTotal * sizeof(double));
		double* prev_r = (double*)malloc(weightsCntTotal * sizeof(double));
		double* bp = (double*)malloc(weightsCntTotal * sizeof(double));
		double* lp = (double*)malloc(weightsCntTotal * sizeof(double));
		double* dE0 = (double*)malloc(weightsCntTotal * sizeof(double));
		double* dE1 = (double*)malloc(weightsCntTotal * sizeof(double));
		double* dE = (double*)malloc(weightsCntTotal * sizeof(double));
		double* sigmap = (double*)malloc(weightsCntTotal * sizeof(double));

		//-- 0. Save original Mx->W into Mx->W[t1] (for all levels)
		for (int l = 0; l < (levelsCnt-1); l++) MCopy(nodesCnt[l], nodesCnt[l+1], W[l], prevW[l]);

		Calc_dJdW(true, false);

		//-- 1. Choose initial vector w ; p=r=-E'(w)
		VCopy(weightsCntTotal, LVV_dJdW, p); //VbyS(weightsCntTotal, p, -1, p);
		VCopy(weightsCntTotal, p, r);
		//-- 1.1 Zero TotdW
		VInit(weightsCntTotal, TotdW, 0);

		success = true;
		sigma = 1e-4;
		lambda = 1e-6; lambdau = 0;

		k = 0;
		do {
			rnorm = Vnorm(weightsCntTotal, r);
			pnorm = Vnorm(weightsCntTotal, p);
			pnorm2 = pow(pnorm, 2);

			//-- 2. if success=true Calculate second-order  information (s and delta)
			if (success) {

				//-- non-Hessian approximation
				sigma = sigma / pnorm;
				//-- get dE0 (dJdW at current W)
				VCopy(weightsCntTotal, LVV_dJdW, dE0);
				//-- get dE1 (dJdW at W+sigma*p)
				VbyS(weightsCntTotal, p, sigma, sigmap);
				VplusV(weightsCntTotal, LVV_W, sigmap, newW);
				dEdW_at_w_LVV(LVV_W, newW, dE1);
				//-- calc s
				VminusV(weightsCntTotal, dE0, dE1, dE);
				VdivS(weightsCntTotal, dE, sigma, s);

				//-- calc delta
				delta = VdotV(weightsCntTotal, p, s);
			}

			//-- 3. scale s and delta

			//--- 3.1 s=s+(lambda-lambdau)*p
			VbyS(weightsCntTotal, p, (lambda - lambdau), lp);
			VplusV(weightsCntTotal, s, lp, s);
			//--- 3.2 delta=delta+(lambda-lambdau)*|p|^2
			delta += (lambda - lambdau)*pnorm2;

			//-- 4. if delta<=0 (i.e. Hessian is not positive definite) , then make it positive
			if (delta <= 0) {
				//-- adjust s
				VbyS(weightsCntTotal, p, (lambda - 2 * delta / pnorm2), lp);
				VplusV(weightsCntTotal, s, lp, s);
				//-- adjust lambdau
				lambdau = 2 * (lambda - delta / pnorm2);
				//-- adjust delta
				delta = -delta + lambda*pnorm2;
				//-- adjust lambda
				lambda = lambdau;
			}

			//-- 5. Calculate step size
			mu = VdotV(weightsCntTotal, p, r);
			alpha = mu / delta;

			//-- 6. Comparison parameter

			//--- 6.1 calc newW=w+alpha*p , which will also be used in (7)
			VbyS(weightsCntTotal, p, alpha, dW);
			VplusV(weightsCntTotal, LVV_W, dW, newW);
			//--- 6.2 E(w) is current norm_e
			e_old = norm_e;
			//--- 6.3 E(w+dw) ir calculated by E_at_w()
			e_new = E_at_w_LVV(LVV_W, newW);
			//--- 6.4 comp=2*delta*(e_old-e_new)/mu^2
			comp = 2 * delta*(e_old - e_new) / pow(mu, 2);

			if (comp >= 0) {
				//-- 7. Update weight vector

				//-- W = W + dW
				VbyS(weightsCntTotal, p, alpha, dW);
				VplusV(weightsCntTotal, LVV_W, dW, LVV_W);
				//-- TotdW = TotdW + dW
				VplusV(weightsCntTotal, TotdW, dW, TotdW);
				//-- 7.1 recalc  dJdW
				Calc_dJdW(true, false);
				//-- save r, and calc new r
				VCopy(weightsCntTotal, r, prev_r);
				VCopy(weightsCntTotal, LVV_dJdW, r); //VbyS(weightsCntTotal, r, -1, r);

																	  //-- reset lambdau
				lambdau = 0; success = true;

				//-- 7a. if k mod N = 0 then restart algorithm, else create new conjugate direction
				if (((k + 1) % nodesCntTotal) == 0) {
					VCopy(weightsCntTotal, r, p);
				}
				else {
					b1 = pow(Vnorm(weightsCntTotal, r), 2);
					b2 = VdotV(weightsCntTotal, r, prev_r);
					beta = (b1 - b2) / mu;
					//-- p = r + beta*p
					VbyS(weightsCntTotal, p, beta, bp);
					VminusV(weightsCntTotal, bp, r, p);// VplusV(weightsCntTotal, r, bp, p);
				}
				//-- 7b. if comp>=0.75 reduce scale parameter
				if (comp >= 0.75) lambda = lambda / 2;

			}
			else {
				//-- a reduction in error is not possible.
				lambdau = lambda;
				success = false;
			}

			//-- 8. if comp<0.25 then increase scale parameter
			if (comp<0.25) lambda = lambda * 4;

			//-- 9. if the steepest descent direction r>epsilon and success=true, then set k=k+1 and go to 2, else terminate and return w as the desired minimum
			rnorm = Vnorm(weightsCntTotal, r);
			SaveCoreData_SCGD(0, BPCount, k, SCGD_progK, delta, mu, alpha, beta, lambda, lambdau, rnorm, norm_e, comp);
			SaveMSEData(SCGD_progK, sqrt(norm_e), 0);	// === TODO : sqrt(norm_e) is NOT the same as MSE! Also, MSE_V is missing!

			k++; SCGD_progK++;
		} while ((rnorm>epsilon) && (k<maxk));

		//-- save the total dW for this neuron into Mx->dW[l][n]
		VCopy(weightsCntTotal, TotdW, LVV_dW);

		//fprintf(Mx->fIntLog, "%d, %d, %d, %d, %d, %d, %d, , , , , , , , , \n", pid, tid, pEpoch, Mx->BPCount, 0, 0, k);

		free(p); free(r); free(s); free(dW); free(TotdW); free(prev_r); free(bp); free(newW); free(dE0); free(dE1); free(dE); free(lp); free(sigmap);

		//-- 0. Before exiting, Restore original Mx->W from Mx->W[t1] (for all levels)
		for (int l = 0; l < (levelsCnt-1); l++) MCopy(nodesCnt[l], nodesCnt[l+1], prevW[l], W[l]);
	}
	void cNN::BP_QuickProp() {
		//-- as per QuickProp2.pdf, 2.6.3	
		int l, j, i;

		Calc_dJdW(false, false);

		for (l = 0; l<(levelsCnt-1); l++) {
			for (j = 0; j < nodesCnt[l]; j++) {
				for (i = 0; i < nodesCnt[l+1]; i++) {

					dW[l][j][i] =LearningRate*dJdW[l][j][i];
					if (dW[l][j][i]>0) {
						if (dJdW[l][j][i]>(mu / (1 + mu)*prevdJdW[l][j][i])) {
							dW[l][j][i] = mu*dW[l][j][i];
						} else {
							dW[l][j][i] = dJdW[l][j][i] / (prevdJdW[l][j][i] - dJdW[l][j][i])*dW[l][j][i];
						}
						if (dJdW[l][j][i]>0) dW[l][j][i] += LearningRate*dJdW[l][j][i];
					} else if (dW[l][j][i]<0) {
						if (dJdW[l][j][i]<(mu / (1+mu)*prevdJdW[l][j][i])) {
							dW[l][j][i] = mu*dW[l][j][i];
						} else {
							dW[l][j][i] = dJdW[l][j][i] / (prevdJdW[l][j][i] - dJdW[l][j][i])*dW[l][j][i];
						}
						if (dJdW[l][j][i]<0) dW[l][j][i] += LearningRate*dJdW[l][j][i];
					}	else if (dW[l][j][i] == 0) {
						dW[l][j][i] += LearningRate*dJdW[l][j][i];
					}
				}
			}
		}
	}

	void cNN::BP() {
		SavePrevWeights();

		//-- All the BP routines should only set dW , and NOT change W
		switch (BPAlgo) {
		case BP_STD:
			BP_Std();
			break;
		case BP_QUICKPROP:
			BP_QuickProp();
			break;
		case BP_SCGD:
			BP_scgd();
			break;
		}

		BPCount++;
	}

	cNN::cNN(int ppid, int ptid) {
		levelRatioS = new char[256];
		pid = ppid;
		tid = ptid;
	}
	EXPORT cNN::cNN() {
		levelRatioS = new char[256];
	}
	cNN::~cNN(){
		freeNNMem();
	}

/*
void loadTS(double* ts, double* baseVal) {
	(*baseVal) = 1.54230;
	ts[0] = 1.54257;
	ts[1] = 1.54047;
	ts[2] = 1.54082;
	ts[3] = 1.54093;
	ts[4] = 1.5394;
	ts[5] = 1.53962;
	ts[6] = 1.5401;
	ts[7] = 1.54107;
	ts[8] = 1.5399;
	ts[9] = 1.53945;
	ts[10] = 1.53972;
	ts[11] = 1.54171;
	ts[12] = 1.54138;
	ts[13] = 1.54033;
	ts[14] = 1.5383;
	ts[15] = 1.53876;
	ts[16] = 1.53872;
	ts[17] = 1.53607;
	ts[18] = 1.53705;
	ts[19] = 1.53587;
	ts[20] = 1.5368;
	ts[21] = 1.53607;
	ts[22] = 1.53646;
	ts[23] = 1.53642;
	ts[24] = 1.53573;
	ts[25] = 1.5358;
	ts[26] = 1.53654;
	ts[27] = 1.53712;
	ts[28] = 1.5374;
	ts[29] = 1.53704;
	ts[30] = 1.53809;
	ts[31] = 1.53866;
	ts[32] = 1.53808;
	ts[33] = 1.53815;
	ts[34] = 1.53651;
	ts[35] = 1.53683;
	ts[36] = 1.53715;
	ts[37] = 1.53665;
	ts[38] = 1.53503;
	ts[39] = 1.53503;
	ts[40] = 1.53908;
	ts[41] = 1.53719;
	ts[42] = 1.539;
	ts[43] = 1.53817;
	ts[44] = 1.53765;
	ts[45] = 1.5365;
	ts[46] = 1.53671;
	ts[47] = 1.53575;
	ts[48] = 1.53603;
	ts[49] = 1.53665;
	ts[50] = 1.5368;
	ts[51] = 1.53628;
	ts[52] = 1.53571;
	ts[53] = 1.5356;
	ts[54] = 1.53493;
	ts[55] = 1.53517;
	ts[56] = 1.53437;
	ts[57] = 1.53643;
	ts[58] = 1.53625;
	ts[59] = 1.53344;
	ts[60] = 1.53339;
	ts[61] = 1.53412;
	ts[62] = 1.53352;
	ts[63] = 1.53253;
	ts[64] = 1.52976;
	ts[65] = 1.52688;
	ts[66] = 1.52645;
	ts[67] = 1.52627;
	ts[68] = 1.52526;
	ts[69] = 1.52604;
	ts[70] = 1.52625;
	ts[71] = 1.52637;
	ts[72] = 1.52635;
	ts[73] = 1.52621;
	ts[74] = 1.52604;
	ts[75] = 1.52545;
	ts[76] = 1.52542;
	ts[77] = 1.52533;
	ts[78] = 1.52483;
	ts[79] = 1.52462;
	ts[80] = 1.52271;
	ts[81] = 1.52462;
	ts[82] = 1.52466;
	ts[83] = 1.52414;
	ts[84] = 1.52536;
	ts[85] = 1.52427;
	ts[86] = 1.52471;
	ts[87] = 1.52281;
	ts[88] = 1.52395;
	ts[89] = 1.52362;
	ts[90] = 1.52275;
	ts[91] = 1.5228;
	ts[92] = 1.52296;
	ts[93] = 1.52382;
	ts[94] = 1.52312;
	ts[95] = 1.52378;
	ts[96] = 1.52506;
	ts[97] = 1.52465;
	ts[98] = 1.52369;
	ts[99] = 1.52429;
	ts[100] = 1.52426;
	ts[101] = 1.52476;
	ts[102] = 1.52484;
	ts[103] = 1.52438;
	ts[104] = 1.524;
	ts[105] = 1.52353;
	ts[106] = 1.52137;
	ts[107] = 1.5199;
	ts[108] = 1.51772;
	ts[109] = 1.51753;
	ts[110] = 1.51861;
	ts[111] = 1.51315;
	ts[112] = 1.50651;
	ts[113] = 1.5061;
	ts[114] = 1.50614;
	ts[115] = 1.50587;
	ts[116] = 1.50576;
	ts[117] = 1.50467;
	ts[118] = 1.50523;
	ts[119] = 1.50327;
	ts[120] = 1.50356;
	ts[121] = 1.50593;
	ts[122] = 1.50572;
	ts[123] = 1.50588;
	ts[124] = 1.50536;
	ts[125] = 1.50597;
	ts[126] = 1.5059;
	ts[127] = 1.50681;
	ts[128] = 1.50648;
	ts[129] = 1.50751;
	ts[130] = 1.50659;
	ts[131] = 1.51033;
	ts[132] = 1.51101;
	ts[133] = 1.51107;
	ts[134] = 1.51027;
	ts[135] = 1.51046;
	ts[136] = 1.51028;
	ts[137] = 1.50959;
	ts[138] = 1.50961;
	ts[139] = 1.51091;
	ts[140] = 1.51196;
	ts[141] = 1.51287;
	ts[142] = 1.51301;
	ts[143] = 1.51275;
	ts[144] = 1.51282;
	ts[145] = 1.51195;
	ts[146] = 1.51068;
	ts[147] = 1.51013;
	ts[148] = 1.50968;
	ts[149] = 1.50909;
	ts[150] = 1.5084;
	ts[151] = 1.50807;
	ts[152] = 1.50856;
	ts[153] = 1.50877;
	ts[154] = 1.50854;
	ts[155] = 1.50437;
	ts[156] = 1.50523;
	ts[157] = 1.50773;
	ts[158] = 1.50421;
	ts[159] = 1.50607;
	ts[160] = 1.50904;
	ts[161] = 1.50812;
	ts[162] = 1.50851;
	ts[163] = 1.50943;
	ts[164] = 1.50966;
	ts[165] = 1.50722;
	ts[166] = 1.50649;
	ts[167] = 1.50659;
	ts[168] = 1.50535;
	ts[169] = 1.50671;
	ts[170] = 1.5077;
	ts[171] = 1.50754;
	ts[172] = 1.50838;
	ts[173] = 1.50732;
	ts[174] = 1.50807;
	ts[175] = 1.5074;
	ts[176] = 1.50748;
	ts[177] = 1.50792;
	ts[178] = 1.50846;
	ts[179] = 1.50632;
	ts[180] = 1.50605;
	ts[181] = 1.50558;
	ts[182] = 1.50529;
	ts[183] = 1.50468;
	ts[184] = 1.50151;
	ts[185] = 1.49582;
	ts[186] = 1.49439;
	ts[187] = 1.49452;
	ts[188] = 1.49127;
	ts[189] = 1.4935;
	ts[190] = 1.4933;
	ts[191] = 1.49273;
	ts[192] = 1.49283;
	ts[193] = 1.49386;
	ts[194] = 1.49336;
	ts[195] = 1.49328;
	ts[196] = 1.49291;
	ts[197] = 1.49178;
	ts[198] = 1.49196;
	ts[199] = 1.49325;
	ts[200] = 1.49407;
	ts[201] = 1.49632;
	ts[202] = 1.50048;
	ts[203] = 1.49724;
	ts[204] = 1.49888;
	ts[205] = 1.50043;
	ts[206] = 1.49855;
	ts[207] = 1.49708;
	ts[208] = 1.49403;
	ts[209] = 1.49428;
	ts[210] = 1.49057;
	ts[211] = 1.48861;
	ts[212] = 1.48587;
	ts[213] = 1.48508;
	ts[214] = 1.48814;
	ts[215] = 1.48816;
	ts[216] = 1.48861;
	ts[217] = 1.48877;
	ts[218] = 1.48906;
	ts[219] = 1.4875;
	ts[220] = 1.48745;
	ts[221] = 1.48724;
	ts[222] = 1.48699;
	ts[223] = 1.48624;
	ts[224] = 1.48642;
	ts[225] = 1.48569;
	ts[226] = 1.48762;
	ts[227] = 1.48795;
	ts[228] = 1.4853;
	ts[229] = 1.48316;
	ts[230] = 1.48015;
	ts[231] = 1.4795;
	ts[232] = 1.47218;
	ts[233] = 1.4734;
	ts[234] = 1.4754;
	ts[235] = 1.47345;
	ts[236] = 1.47268;
	ts[237] = 1.47237;
	ts[238] = 1.47415;
	ts[239] = 1.47402;
	ts[240] = 1.47364;
	ts[241] = 1.47524;
	ts[242] = 1.4754;
	ts[243] = 1.47548;
	ts[244] = 1.47638;
	ts[245] = 1.4757;
	ts[246] = 1.47586;
	ts[247] = 1.47518;
	ts[248] = 1.47685;
	ts[249] = 1.47769;
	ts[250] = 1.47736;
	ts[251] = 1.47943;
	ts[252] = 1.4787;
	ts[253] = 1.47821;
	ts[254] = 1.47849;
	ts[255] = 1.4796;
	ts[256] = 1.48167;
	ts[257] = 1.47709;
	ts[258] = 1.47989;
	ts[259] = 1.48435;
	ts[260] = 1.48373;
	ts[261] = 1.48336;
	ts[262] = 1.483;
	ts[263] = 1.48266;
	ts[264] = 1.48256;
	ts[265] = 1.48244;
	ts[266] = 1.48239;
	ts[267] = 1.48205;
	ts[268] = 1.48202;
	ts[269] = 1.48278;
	ts[270] = 1.48217;
	ts[271] = 1.48277;
	ts[272] = 1.48214;
	ts[273] = 1.48357;
	ts[274] = 1.48258;
	ts[275] = 1.47869;
	ts[276] = 1.47922;
	ts[277] = 1.47706;
	ts[278] = 1.47503;
	ts[279] = 1.47616;
	ts[280] = 1.47638;
	ts[281] = 1.47537;
	ts[282] = 1.4742;
	ts[283] = 1.47408;
	ts[284] = 1.4754;
	ts[285] = 1.4754;
	ts[286] = 1.47425;
	ts[287] = 1.47483;
	ts[288] = 1.47431;
	ts[289] = 1.47458;
	ts[290] = 1.47497;
	ts[291] = 1.47623;
	ts[292] = 1.47626;
	ts[293] = 1.47598;
	ts[294] = 1.47608;
	ts[295] = 1.4762;
	ts[296] = 1.47542;
	ts[297] = 1.47555;
	ts[298] = 1.47551;
	ts[299] = 1.47558;
	ts[300] = 1.46729;
	ts[301] = 1.46774;
	ts[302] = 1.46371;
	ts[303] = 1.46383;
	ts[304] = 1.46723;
	ts[305] = 1.46618;
	ts[306] = 1.46849;
	ts[307] = 1.47064;
	ts[308] = 1.47278;
	ts[309] = 1.48591;
	ts[310] = 1.49475;
	ts[311] = 1.49764;
	ts[312] = 1.49574;
	ts[313] = 1.4941;
	ts[314] = 1.49601;
	ts[315] = 1.49824;
	ts[316] = 1.49452;
	ts[317] = 1.49077;
	ts[318] = 1.48884;
	ts[319] = 1.48827;
	ts[320] = 1.48983;
	ts[321] = 1.49011;
	ts[322] = 1.484;
	ts[323] = 1.48361;
	ts[324] = 1.48967;
	ts[325] = 1.48994;
	ts[326] = 1.48946;
	ts[327] = 1.48525;
	ts[328] = 1.47809;
	ts[329] = 1.47585;
	ts[330] = 1.47258;
	ts[331] = 1.47373;
	ts[332] = 1.47211;
	ts[333] = 1.472;
	ts[334] = 1.47262;
	ts[335] = 1.47508;
	ts[336] = 1.47551;
	ts[337] = 1.47569;
	ts[338] = 1.47593;
	ts[339] = 1.47597;
	ts[340] = 1.47739;
	ts[341] = 1.47696;
	ts[342] = 1.47689;
	ts[343] = 1.47611;
}

int main() {
	system("cls");

	srand((unsigned int)time((time_t)NULL));

//===================== TO BE TAKEN CARE OF BY MyForecast() =======================================
	int hlen = 344;
	double* ts = MallocArray<double>(hlen);
	double* ts_tr = MallocArray<double>(hlen);
	double* ts_trs = MallocArray<double>(hlen);
	double bv;
	double TSmin, scaleM, scaleP;
	loadTS(ts, &bv);

	int sampleLen = 8;
	int targetLen = 3;
	int sampleCnt = hlen - sampleLen;
	int runCnt    = hlen + targetLen;
	double** Sample = MallocArray<double>(sampleCnt, sampleLen);
	double** Target = MallocArray<double>(sampleCnt, targetLen);

	dataTransform(DT_DELTALOG, hlen, ts, bv, &TSmin, ts_tr);
	DataScale(hlen, ts_tr, -1, 1, ts_trs, &scaleM, &scaleP);
	SlideArray(hlen, ts_trs, sampleCnt, sampleLen, Sample, targetLen, Target, 2);

	cNN* myNN = new cNN(GetCurrentProcessId(), GetCurrentThreadId());
	strcpy(myNN->levelRatioS, "0.5");
	myNN->TrainingProtocol = TP_STOCHASTIC;
	myNN->BPAlgo = BP_STD;
	myNN->ActivationFunction = NN_ACTIVATION_TANH;
	myNN->useContext = 0;
	myNN->MaxEpochs = 3000;
	myNN->LearningRate = 0.01;
	myNN->LearningMomentum = 0.8;
	myNN->TargetMSE = 0.0001;
	myNN->useValidation = 0;
	myNN->StopAtDivergence = 0;
	myNN->mu = 1.75;
	myNN->setTopology(sampleLen, targetLen);
	//--
	myNN->ScreenMutex = CreateMutex(NULL, FALSE, NULL);
	myNN->ScreenPos = 3;
	//--
	int TimeStepsCount = myNN->MaxEpochs * ((myNN->BPAlgo == BP_SCGD) ? sampleCnt : 1);
	myNN->coreLog = new tCoreLog();
	myNN->mallocNNLog(TimeStepsCount);
	myNN->coreLog->MSEOutput = MallocArray<tLogMSE>(myNN->MaxEpochs);
	myNN->coreLog->RunOutput = MallocArray<tLogRUN>(runCnt);
	//--
//===================================================================================================

	//== timer init
	LARGE_INTEGER frequency;			// ticks per second
	LARGE_INTEGER time_start, time_end; // ticks
	double elapsedTime = 0; char elapsedTimeS[30];
	// get ticks per second
	QueryPerformanceFrequency(&frequency);
	// start timer
	QueryPerformanceCounter(&time_start);
	//==

	myNN->init();
	myNN->train(sampleCnt, sampleLen, targetLen, Sample, Target);
	myNN->run(myNN->coreLog->NNFinalW, sampleCnt, sampleLen, targetLen, Sample, Target);

	//-- stop timer, compute the elapsed time
	QueryPerformanceCounter(&time_end);
	elapsedTime = (time_end.QuadPart - time_start.QuadPart) * 1000.0 / frequency.QuadPart;
	ms2ts(elapsedTime, elapsedTimeS);
	printf("\n Elapsed Time: %s\n", elapsedTimeS);

	FreeArray(hlen, ts);
	FreeArray(hlen, ts_tr);
	FreeArray(hlen, ts_trs);
	FreeArray(sampleCnt, sampleLen, Sample);
	FreeArray(sampleCnt, targetLen, Target);
	FreeArray(myNN->MaxEpochs, myNN->coreLog->MSEOutput);
	FreeArray(runCnt, myNN->coreLog->RunOutput);
	delete myNN;

	printf("\n");
	{printf("Press any key to continue...\n"); getchar();};
	return 0;
}
*/

cNNLog::cNNLog(int pLevelsCnt, int* pNodesCnt, int pTimeSteps, int pWeightsCntTotal){
	levelsCnt = pLevelsCnt;
	nodesCnt = pNodesCnt;
	weightsCntTotal = pWeightsCntTotal;
	//-- FinalW
	FinalW = (double***)malloc((pLevelsCnt - 1) * sizeof(double**));
	for (int l = 0; l < (pLevelsCnt - 1); l++) {
		FinalW[l] = (double**)malloc(pNodesCnt[l] * sizeof(double*));
		for (int fn = 0; fn < pNodesCnt[l]; fn++) {
			FinalW[l][fn] = (double*)malloc(pNodesCnt[l+1] * sizeof(double));
		}
	}
	//-- IntP
	IntP = MallocArray<tLogInt>(pTimeSteps);
}
cNNLog::~cNNLog() {
	//-- FinalW
	for (int l = 0; l < (levelsCnt - 1); l++) {
		for (int fn = 0; fn < nodesCnt[l]; fn++) {
			free(FinalW[l][fn]);
		}
		free(FinalW[l]);
	}
	free(FinalW);
	//-- IntP
	free(IntP);
}
int cNNLog::SaveImage(tDebugInfo* pDebugParms, tDBConnection* pDBConn) {
	return( InsertCoreImage_NN(pDebugParms, pDBConn, ProcessId, ThreadId, levelsCnt, nodesCnt, weightsCntTotal, FinalW) );
}

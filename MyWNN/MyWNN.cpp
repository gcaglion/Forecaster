//#include <vld.h>
#include <MyWNN.h>

void P2V(int Len, double* P, std::vector<double> &V) {
	for (int i = 0; i < Len; i++) V.push_back(P[i]);
}
void V2P(int Len, double* P, std::vector<double> &V) {
	for (int i = 0; i < Len; i++) P[i] = V[i];
}

void WaweletDecomp(int pTSlen, double* pTS, int pDecompLevel, char* pWaweletType, double* oLFA, double** oHFD) {
	int i, n;
	std::vector<double> SWTin; std::vector<double> SWTout;

	//-- 1.1. First, convert pointer to vector
	SWTin.clear(); SWTout.clear();
	P2V(pTSlen, pTS, SWTin);
	//-- 1.2. Then, call swt on TS_TRS[d]
	swt(SWTin, pDecompLevel, pWaweletType, SWTout, pTSlen);

	//-- 1.3. Then, parse output vectors into LFA and HFD[DecompLevel]
	//--- 1.3.1 First, A[] into LFA[]
	for (i = 0; i < pTSlen; i++) oLFA[i] = SWTout[i];
	//--- 1.3.2 Then,  D[j] into HFD[j]
	for (n = 0; n < pDecompLevel; n++) {
		for (i = 0; i < pTSlen; i++) oHFD[n][i] = SWTout[pTSlen*(n + 1) + i];
	}
}

__declspec(dllexport) void BuildLayer0Input_WNN(int dataSet, int decompLevel, char* wtype, int tslen, double* its, double ibv, double** ots, double* obv) {
	int i, h;
	// ots[CoreId][wlen]

	//-- Build Layer 0 : get ots[][] by creating wavelets from its
	double*  fts = MallocArray<double>(tslen + 1);
	double*  LFA = MallocArray<double>(tslen + 1);
	double** HFD = MallocArray<double>(decompLevel, tslen + 1);

	// build temp timeserie by adding baseval at the beginning of its
	fts[0] = ibv;
	for (i = 0; i<tslen; i++) fts[i + 1] = its[i];

	//-- now, fill LFA and HFD[] by calling WaveletDecomp()
	WaweletDecomp(tslen + 1, fts, decompLevel, wtype, LFA, HFD);

	//-- extract baseval from LFA,HFD
	obv[0] = LFA[0];
	for (h = 0; h<decompLevel; h++) obv[h + 1] = HFD[h][0];

	//-- copy LFA,HFD into ots[], skipping initial element (baseVal)
	for (i = 0; i < tslen; i++) {
		ots[0][i] = LFA[i + 1];
		for (h = 0; h < decompLevel; h++) ots[h + 1][i] = HFD[h][i + 1];
	}

	FreeArray(tslen + 1, fts);
	FreeArray(tslen + 1, LFA);
	FreeArray(decompLevel, tslen + 1, HFD);
}

__declspec(dllexport) void BuildLayer1Input_WNN(int dataSet, int sampleCnt, int l0sampleLen, int l1sampleLen, int tsfcnt, double* tsf, int l0cores, int l0predlen, int l1predlen, cCore** l0log, double** l1target, double** oSample, double** oTarget) {
	int i, n0, s;
	int slen = tsfcnt + l0cores*l0predlen;

	// l0log [Core][DataSet][pointer-to <XXX_Logs]

	double*  R = MallocArray<double>(l0predlen);	// we only need the last (prediction) from runlog

	for (s = 0; s < sampleCnt; s++) {

		for (n0 = 0; n0 < l0cores; n0++) {
			// 0. "extract" Predicted items from RunLog
			for (i = 0; i < l0predlen; i++) R[i] = l0log[n0]->coreLog[dataSet]->RunOutput[l0sampleLen + s + i].Predicted_TRS;	// we only need the last (prediction) from runlog

																																	// 1. build sample S by aligning TSFs|OutputFromCore0|OutputFromCore1|OutputFromCore2|OutputFromCore3|OutputFromCore4
			for (i = 0; i < tsfcnt; i++)    oSample[s][i] = tsf[i];
			for (i = 0; i < l0predlen; i++) oSample[s][tsfcnt + n0*l0predlen + i] = R[i];

		}


		//-- 2. TargetData for Layer 1 is target data from SlideArray() on the original hd
		for (i = 0; i < l0predlen; i++) oTarget[s][i] = l1target[s][i];

	}
	/*
	//-- 2. build temp ts by un-sliding Samples array
	int tslen = sampleCnt + l1sampleLen;
	double* tempts = MallocArray<double>(tslen);
	double** tempS = MallocArray<double>(sampleCnt, l1sampleLen);
	TSfromSamples(sampleCnt, l1sampleLen, oSample, tempts);
	SlideArrayNew(tslen, tempts, l1sampleLen, l1predlen, S, oTarget, 2);
	*/
	FreeArray(l0predlen, R);

}

__declspec(dllexport) void BuildLayerInput_WNN(int layer, cEngine* pEngineParms, int dataTrx, int dataSet, int sampleCnt, int l0tslen, double* l0its, double l0ibv, double** l0ots, double* l0obv, double* tsf, cCore** l0log, double** l1target, double** oSample, double** oTarget) {
	if (layer == 0) {
		BuildLayer0Input_WNN(dataSet, pEngineParms->WNN_DecompLevel, pEngineParms->WNN_WaveletType, l0tslen, l0its, l0ibv, l0ots, l0obv);
	}
	else {
		BuildLayer1Input_WNN(dataSet, sampleCnt, pEngineParms->Core[0][0]->SampleLen, pEngineParms->Core[1][0]->SampleLen, pEngineParms->TSFcnt, tsf, pEngineParms->CoresCount[0], pEngineParms->Core[0][0]->TargetLen, pEngineParms->Core[1][0]->TargetLen, l0log, l1target, oSample, oTarget);
	}
}
//#include <vld.h>

#include <MyTimeSeries.h>
/*
//-- Statistical Features
int cmp_dbl(const void *x, const void *y) {
	double xx = *(double*)x, yy = *(double*)y;
	if (xx < yy) return -1;
	if (xx > yy) return  1;
	return 0;
}
double cTimeSerie::Mean(){
	double VSum = 0;
	for (int i=0; i<TSlen; i++) VSum += Data[i];
	return(VSum / TSlen);
}
double cTimeSerie::MeanAbsoluteDeviation(){
	double VAvg = TSMean(TSlen, Data);
	double VSum = 0;
	for (int i = 0; i < TSlen; i++) VSum += fabs(Data[i] - VAvg);
	return(VSum / TSlen);
}
double cTimeSerie::Variance(){
	double VAvg = TSMean(TSlen, Data);
	double VSum = 0;
	for (int i = 0; i < TSlen; i++) VSum += pow(Data[i] - VAvg, 2);
	return(VSum / (TSlen - 1));
}
double cTimeSerie::Skewness(){
	double VAvg = TSMean(TSlen, Data);
	double VSigma = sqrt(TSVariance(TSlen, Data));
	double VSum = 0;
	for (int i = 0; i < TSlen; i++) VSum += pow((Data[i] - VAvg) / VSigma, 3);
	return(VSum / TSlen);
}
double cTimeSerie::Kurtosis(){
	double VAvg = TSMean(TSlen, Data);
	double VSigma = sqrt(TSVariance(TSlen, Data));
	double VSum = 0;
	for (int i = 0; i < TSlen; i++) VSum += pow((Data[i] - VAvg) / VSigma, 4);
	return(VSum / TSlen - 3);
}
double cTimeSerie::TurningPoints(){
	int tp = 0;
	for (int i = 1; i < TSlen; i++) {
		if ((Data[i + 1] - Data[i])*(Data[i] - Data[i - 1]) <0) tp++;
	}
	return(tp);
}
double cTimeSerie::ShannonEntropy(){
	int i;
	double* uval = (double*)malloc(TSlen * sizeof(double));	// unique values
	double* uval_p = (double*)malloc(TSlen * sizeof(double));	// unique values probabilities
	double h = 0;

	//-- Before anything else, make a local copy of Input Array
	double* tmpV = (double*)malloc(TSlen * sizeof(double));
	memcpy(tmpV, Data, TSlen * sizeof(double));

	//-- First, sort input Array
	qsort(tmpV, TSlen, sizeof(double), cmp_dbl);

	//-- Then, find unique values
	int unique = 1; //In case we have only one element; it is unique!
	for (i = 0; i < TSlen; i++) {
		if (tmpV[i] == tmpV[i + 1]) {
			uval_p[unique - 1]++;
			continue;
		}
		else {
			unique++;
			uval[unique - 1] = tmpV[i];
			uval_p[unique - 1] = 1;
		}
	}

	//-- Normalize probabilities. Sum must be 1
	for (i = 0; i < (unique - 1); i++) uval_p[i] = uval_p[i + 1] / unique;

	//-- Then, calc entropy from p
	for (i = 0; i < unique; i++) h += uval_p[i] * log2(uval_p[i]);

	free(uval); free(uval_p); free(tmpV);
	return(h);
}
double cTimeSerie::HistoricalVolatility(){
	int i;
	double s, u;
	double* w = (double*)malloc(TSlen * sizeof(double));

	s = 0;
	for (i = 1; i<TSlen; i++) {
		u = log(Data[i] / Data[i - 1]);
		if (i>1) {
			w[i] = w[i - 1] * 0.94;
		}
		else {
			w[i] = 1 - 0.94;
		}
		s += pow(u, 2)*w[i];
	}

	free(w);
	return sqrt(s);
}
*/
//-- Transformation and Scaling
void cTimeSerie::TransformScale(int dt, double sMin, double sMax) {
	int i;
	
	ScaleMin = sMin; ScaleMax = sMax;
	FindMinMax(TSlen, Data, &MinVal, &MaxVal);
	ScaleM = (ScaleMax - ScaleMin) / (MaxVal - MinVal);
	ScaleP = ScaleMin - MinVal*ScaleM;

	//-- 1. Transform
	switch (dt) {
	case DT_DELTA:
		for (i=0; i<TSlen; i++) Data_TR[i] = Data[i]-( (i>0) ? Data[i-1] : BaseVal );
		break;
	case DT_LOG:
		for (i=0; i<TSlen; i++) Data_TR[i] = log(Data[i] - MinVal + 1);
		break;
	case DT_DELTALOG:
		for (i = 0; i<TSlen; i++) {
			Data_TR[i] = Data[i]-((i>0) ? Data[i-1] : BaseVal);
			Data_TR[i] = log(Data_TR[i] - MinVal + 1);
		}
		break;
	default:
		break;
	}

	//-- 2. Scale
	DataScale(TSlen, Data_TR, ScaleMin, ScaleMax, Data_TRS, &ScaleM, &ScaleP);

}
/*void cTimeSerie::UnTransformScale(int dt){
	int i;
	double prev;

	//-- 1. UnScale
	DataUnScale(TSlen, 0, TSlen, Data_TRS, ScaleM, ScaleP, Data_TR);

	//-- 2. UnTransform
	dataUnTransform(dt, 0, TSlen, Data_TR, BaseVal, MinVal, Data, )

}
*/
//-- constructors / destructor
cTimeSerie::cTimeSerie(int len, double* data, double* bw, double bv) {
	TSlen = len;
	BaseVal = bv;
	Data = MallocArray<double>(len);
	Data_TR = MallocArray<double>(len);
	Data_TRS = MallocArray<double>(len);
	BarWidth = MallocArray<double>(len);

	for (int i = 0; i<TSlen; i++) {
		Data[i] = data[i];
		BarWidth[i] = bw[i];
	}
	MinVal = ArrayMin<double>(len, data);
}
EXPORT cTimeSerie::cTimeSerie(int len) {
	TSlen = len;
	Data = MallocArray<double>(len);
	Data_TR = MallocArray<double>(len);
	Data_TRS = MallocArray<double>(len);
	BarWidth = MallocArray<double>(len);
}
cTimeSerie::cTimeSerie(cTimeSerie* ts1, cTimeSerie* ts2) {
	//-- creates a timeserie by concatenating ts1 and ts2
	TSlen = ts1->TSlen+ts2->TSlen;
	BaseVal = ts1->BaseVal;
	Data = MallocArray<double>(TSlen);
	Data_TR = MallocArray<double>(TSlen);
	Data_TRS = MallocArray<double>(TSlen);
	BarWidth = MallocArray<double>(TSlen);

	for (int i = 0; i<ts1->TSlen; i++) {
		Data[i] = ts1->Data[i];
		Data_TR[i] = ts1->Data_TR[i];
		Data_TRS[i] = ts1->Data_TRS[i];
		BarWidth[i] = ts1->BarWidth[i];
	}
	for (int i = 0; i<ts2->TSlen; i++) {
		Data[ts1->TSlen+i] = ts2->Data[i];
		Data_TR[ts1->TSlen+i] = ts2->Data_TR[i];
		Data_TRS[ts1->TSlen+i] = ts2->Data_TRS[i];
		BarWidth[ts1->TSlen+i] = ts2->BarWidth[i];
	}
	MinVal = ArrayMin<double>(TSlen, Data);
}
cTimeSerie::~cTimeSerie(){
	free(Data);
	free(Data_TR);
	free(Data_TRS);
	free(BarWidth);
}



EXPORT void dataTransform(int dt, int dlen, double* idata, double baseVal, double* oMinVal, double* odata) {
	double maxval;

	FindMinMax(dlen, idata, oMinVal, &maxval);

	switch (dt) {

	case DT_DELTA:
		for (int i = 0; i < dlen; i++) odata[i] = idata[i] - ((i>0) ? idata[i - 1] : baseVal);
		break;

	case DT_LOG:
		for (int i = 0; i < dlen; i++) odata[i] = log(idata[i] - (*oMinVal) + 1);
		break;

	case DT_DELTALOG:
		dataTransform(DT_DELTA, dlen, idata, baseVal, oMinVal, odata);
		dataTransform(DT_LOG, dlen, odata, baseVal, oMinVal, odata);
		break;

	default:
		for (int i = 0; i < dlen; i++) odata[i] = idata[i];
		break;
	}

}
EXPORT void dataUnTransform(int dt, int from_i, int to_i, double* idata, double baseVal, double iMinVal, double* iActual, double* odata) {
	double prev;
	int i;

	switch (dt) {

	case DT_DELTA:
		for (i = from_i; i < to_i; i++) {
			if (i > from_i) {
				prev = iActual[i - 1];
			}
			else {
				if (from_i > 0) {
					prev = iActual[i - 1];
				}
				else {
					prev = baseVal;
				}
			}
			odata[i] = idata[i] + prev;
		}
		break;

	case DT_LOG:
		for (i = from_i; i < to_i; i++) odata[i] = exp(idata[i]) + iMinVal - 1;
		break;

	case DT_DELTALOG:

		for (i = from_i; i < to_i; i++) {

			//-- 1. unLOG
			odata[i] = exp(idata[i]) + iMinVal - 1;

			//-- 2. unDELTA
			if (i > from_i) {
				prev = iActual[i - 1];
			}
			else {
				if (from_i > 0) {
					prev = iActual[i - 1];
				}
				else {
					prev = baseVal;
				}
			}
			odata[i] = odata[i] + prev;
		}

		break;

	default:
		for (i = from_i; i < to_i; i++) odata[i] = idata[i];
		break;
	}

}

//-- Timeseries Statistical Features
EXPORT double TSMean(int VLen, double* V) {
	double VSum = 0;
	for (int i = 0; i < VLen; i++) VSum += V[i];
	return(VSum / VLen);
}
EXPORT double TSMeanAbsoluteDeviation(int VLen, double* V) {
	double VAvg = TSMean(VLen, V);
	double VSum = 0;
	for (int i = 0; i < VLen; i++) VSum += fabs(V[i] - VAvg);
	return(VSum / VLen);
}
EXPORT double TSVariance(int VLen, double* V) {
	double VAvg = TSMean(VLen, V);
	double VSum = 0;
	for (int i = 0; i < VLen; i++) VSum += pow(V[i] - VAvg, 2);
	return(VSum / (VLen - 1));
}
EXPORT double TSSkewness(int VLen, double* V) {
	double VAvg = TSMean(VLen, V);
	double VSigma = sqrt(TSVariance(VLen, V));
	double VSum = 0;
	for (int i = 0; i < VLen; i++) VSum += pow((V[i] - VAvg) / VSigma, 3);
	return(VSum / VLen);
}
EXPORT double TSKurtosis(int VLen, double* V) {
	double VAvg = TSMean(VLen, V);
	double VSigma = sqrt(TSVariance(VLen, V));
	double VSum = 0;
	for (int i = 0; i < VLen; i++) VSum += pow((V[i] - VAvg) / VSigma, 4);
	return(VSum / VLen - 3);
}
EXPORT double TSTurningPoints(int VLen, double* V) {
	int tp = 0;
	for (int i = 1; i < VLen; i++) {
		if ((V[i + 1] - V[i])*(V[i] - V[i - 1]) <0) tp++;
	}
	return(tp);
}
int cmp_dbl(const void *x, const void *y) {
	double xx = *(double*)x, yy = *(double*)y;
	if (xx < yy) return -1;
	if (xx > yy) return  1;
	return 0;
}
EXPORT double TSShannonEntropy(int VLen, double* V) {
	int i;
	double* uval = (double*)malloc(VLen * sizeof(double));	// unique values
	double* uval_p = (double*)malloc(VLen * sizeof(double));	// unique values probabilities
	double h = 0;

	//-- Before anything else, make a local copy of Input Array
	double* tmpV = (double*)malloc(VLen * sizeof(double));
	memcpy(tmpV, V, VLen * sizeof(double));

	//-- First, sort input Array
	qsort(tmpV, VLen, sizeof(double), cmp_dbl);

	//-- Then, find unique values
	int unique = 1; //In case we have only one element; it is unique!
	for (i = 0; i < VLen; i++) {
		if (tmpV[i] == tmpV[i + 1]) {
			uval_p[unique - 1]++;
			continue;
		}
		else {
			unique++;
			uval[unique - 1] = tmpV[i];
			uval_p[unique - 1] = 1;
		}
	}

	//-- Normalize probabilities. Sum must be 1
	for (i = 0; i < (unique - 1); i++) uval_p[i] = uval_p[i + 1] / unique;

	//-- Then, calc entropy from p
	for (i = 0; i < unique; i++) h += uval_p[i] * log2(uval_p[i]);

	free(uval); free(uval_p); free(tmpV);
	return(h);
}
EXPORT double TSHistoricalVolatility(int VLen, double* V) {
	int i;
	double s, u;
	double* w = (double*)malloc(VLen * sizeof(double));

	s = 0;
	for (i = 1; i<VLen; i++) {
		u = log(V[i] / V[i - 1]);
		if (i>1) {
			w[i] = w[i - 1] * 0.94;
		}
		else {
			w[i] = 1 - 0.94;
		}
		s += pow(u, 2)*w[i];
	}

	free(w);
	return sqrt(s);
}
EXPORT void CalcTSF(int TSFcnt, int* TSFid, tDataShape* pDataParms, int pTSLen, double* pTS, double* pTSF) {
	double scaleM, scaleP;	// unused!

	for (int t = 0; t < TSFcnt; t++) {
		switch (TSFid[t]) {
		case TSF_MEAN:
			pTSF[TSFid[t]] = TSMean(pTSLen, pTS);
			break;
		case TSF_MAD:
			pTSF[TSFid[t]] = TSMeanAbsoluteDeviation(pTSLen, pTS);
			break;
		case TSF_VARIANCE:
			pTSF[TSFid[t]] = TSVariance(pTSLen, pTS);
			break;
		case TSF_SKEWNESS:
			pTSF[TSFid[t]] = TSSkewness(pTSLen, pTS);
			break;
		case TSF_KURTOSIS:
			pTSF[TSFid[t]] = TSKurtosis(pTSLen, pTS);
			break;
		case TSF_TURNINGPOINTS:
			pTSF[TSFid[t]] = TSTurningPoints(pTSLen, pTS);
			break;
		case TSF_SHE:
			pTSF[TSFid[t]] = TSShannonEntropy(pTSLen, pTS);
			break;
		case TSF_HISTVOL:
			pTSF[TSFid[t]] = TSHistoricalVolatility(pTSLen, pTS);
			break;
		}
	}

	//-- TSF Scaling - Scaling across different TSFs ; REVIEW!!
	if (TSFcnt>0) {
		DataScale(TSFcnt, pTSF, -1, 1, pTSF, &scaleM, &scaleP);
	}

}
//--

EXPORT int FXDataCompact(char* INfilename, int INtimeframe, char* OUTfilename, int OUTtimeframe) {
	//-- IN File must be tab-delimited, have no header, and the first column must be YYYYMMDDHH24MI formatted
	//-- timeframes are expected as the number of minutes (1 for M1, 60 for H1, and so on)
	FILE* INfile = fopen(INfilename, "r"); if (INfile == NULL) return -1;
	FILE* OUTfile = fopen(OUTfilename, "w"); if (OUTfile == NULL) return -1;
	char vLine[256];
	int tabpos, nlpos;
	char vDateTime[12 + 1];
	char vOpen[10];
	char vHigh[10];
	char vLow[10];
	char vClose[10];
	char vVol[10];

	while (strlen(fgets(&vLine[0], 256, INfile))>0) {
		tabpos = (int)(strchr(vLine, '\t') - vLine); nlpos = (int)(strchr(vLine, '\n') - vLine);
		if (nlpos<tabpos) tabpos = nlpos;
		memcpy(&vDateTime[0], &vLine[0], tabpos); vDateTime[tabpos] = '\0';
		memcpy(&vLine[0], &vLine[tabpos + 1], strlen(vLine) - tabpos);
		tabpos = (int)(strchr(vLine, '\t') - vLine); nlpos = (int)(strchr(vLine, '\n') - vLine);
		if (nlpos<tabpos) tabpos = nlpos;
		memcpy(&vOpen[0], &vLine[0], tabpos); vOpen[tabpos] = '\0';
		memcpy(&vLine[0], &vLine[tabpos + 1], strlen(vLine) - tabpos);
		tabpos = (int)(strchr(vLine, '\t') - vLine); nlpos = (int)(strchr(vLine, '\n') - vLine);
		if (nlpos<tabpos) tabpos = nlpos;
		memcpy(&vHigh[0], &vLine[0], tabpos); vHigh[tabpos] = '\0';
		memcpy(&vLine[0], &vLine[tabpos + 1], strlen(vLine) - tabpos);
		tabpos = (int)(strchr(vLine, '\t') - vLine); nlpos = (int)(strchr(vLine, '\n') - vLine);
		if (nlpos<tabpos) tabpos = nlpos;
		memcpy(&vLow[0], &vLine[0], tabpos); vLow[tabpos] = '\0';
		memcpy(&vLine[0], &vLine[tabpos + 1], strlen(vLine) - tabpos);
		tabpos = (int)(strchr(vLine, '\t') - vLine); nlpos = (int)(strchr(vLine, '\n') - vLine);
		if (nlpos<tabpos) tabpos = nlpos;
		memcpy(&vClose[0], &vLine[0], tabpos); vClose[tabpos] = '\0';
		memcpy(&vLine[0], &vLine[tabpos + 1], strlen(vLine) - tabpos);
		tabpos = (int)(strchr(vLine, '\t') - vLine); nlpos = (int)(strchr(vLine, '\n') - vLine);
		if (nlpos<tabpos) tabpos = nlpos;
		memcpy(&vVol[0], &vLine[0], tabpos); vVol[tabpos] = '\0';
		memcpy(&vLine[0], &vLine[tabpos + 1], strlen(vLine) - tabpos);
	}

	return 0;
}

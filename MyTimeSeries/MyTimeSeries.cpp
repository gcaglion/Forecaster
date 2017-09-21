////#include <vld.h>

//#define _NO_ORCL

#include <stdio.h>
#include <Windows.h>
#include <math.h>
#include <MyUtils.h>
#include <FXData.h>
#include <MyLogger.h>
#include <MyOraUtils.h>
#include <MyTimeSeries.h>
#include <MyMatrix.h>

#undef EXPORT
#define EXPORT __declspec(dllexport)

EXPORT int __stdcall LoadData_FXDB(tDebugInfo* DebugParms, tFXData* DBParms, int pHistoryLen, int pFutureLen, char* pDate0, int pValidationShift, int pDatasetCount, double** oHistoryData, double** oHistoryBarW, double** oValidationData, double** oFutureData, double** oFutureBarW, double** oWholeData, double** oWholeBarW, double* oPrevValH, double* oPrevValV, double* oPrevBarW) {
	int i, d;
	tBar* PastBar = (tBar*)malloc((1 + pHistoryLen) * sizeof(tBar));
	tBar* FutureBar = (tBar*)malloc(pFutureLen * sizeof(tBar));

	char stmt[1000];

#ifndef _NO_ORCL
	if (DBParms->FXDB->DBCtx == NULL) {
		if (OraConnect(DebugParms, DBParms->FXDB) != 0) return -1;
	}
#endif

	//=== 1. Get History Data ===

	strcpy(stmt, "select to_char(NewDateTime, 'YYYYMMDDHH24MI'), Open, High, Low, Close, nvl(Volume,0) from History.");
	strcat(stmt, DBParms->Symbol);
	strcat(stmt, "_");
	strcat(stmt, DBParms->TimeFrame);
	strcat(stmt, (DBParms->IsFilled == 1) ? "_FILLED " : " ");
	strcat(stmt, "where NewDateTime <= to_date('");
	strcat(stmt, pDate0);
	strcat(stmt, "','YYYYMMDDHH24MI') order by 1 desc");

#ifndef _NO_ORCL
	if (GetBarsFromQuery(DebugParms, DBParms->FXDB->DBCtx, stmt, pHistoryLen + 1, 1, PastBar) != 0) return -1;	//-- HistoryData
#endif
																												//-- Repeat for each Dataset
	for (d = 0; d < pDatasetCount; d++) {

		//-- HistoryData
		for (i = 0; i<pHistoryLen; i++) {
			switch (DBParms->BarDataType[d]) {
			case OPEN:
				oHistoryData[d][i] = PastBar[pHistoryLen - 1 - i].Open;
				break;
			case HIGH:
				oHistoryData[d][i] = PastBar[pHistoryLen - 1 - i].High;
				break;
			case LOW:
				oHistoryData[d][i] = PastBar[pHistoryLen - 1 - i].Low;
				break;
			case CLOSE:
				oHistoryData[d][i] = PastBar[pHistoryLen - 1 - i].Close;
				break;
			case VOLUME:
				oHistoryData[d][i] = PastBar[pHistoryLen - 1 - i].Volume;
				break;
			}
			oHistoryBarW[d][i] = PastBar[pHistoryLen - 1 - i].High - PastBar[pHistoryLen - 1 - i].Low;
			oWholeData[d][i] = oHistoryData[d][i];
			oWholeBarW[d][i] = oHistoryBarW[d][i];
		}
		switch (DBParms->BarDataType[d]) {
		case OPEN:
			oPrevValH[d] = PastBar[pHistoryLen].Open;
			break;
		case HIGH:
			oPrevValH[d] = PastBar[pHistoryLen].High;
			break;
		case LOW:
			oPrevValH[d] = PastBar[pHistoryLen].Low;
			break;
		case CLOSE:
			oPrevValH[d] = PastBar[pHistoryLen].Close;
			break;
		case VOLUME:
			oPrevValH[d] = PastBar[pHistoryLen].Volume;
			break;
		}
	}

	//=== 2. Get Future Data ===
	strcpy(stmt, "select to_char(NewDateTime, 'YYYYMMDDHH24MI'), Open, High, Low, Close, nvl(Volume,0), Open-nvl(lag(Open) over(order by NewDateTime), 0), High-nvl(lag(High) over(order by NewDateTime), 0), Low-nvl(lag(Low) over(order by NewDateTime), 0), Close-nvl(lag(Close) over(order by NewDateTime), 0), nvl(Volume,0)-nvl(lag(Volume) over(order by NewDateTime), 0) from History.");
	strcat(stmt, DBParms->Symbol);
	strcat(stmt, "_");
	strcat(stmt, DBParms->TimeFrame);
	strcat(stmt, (DBParms->IsFilled == 1) ? "_FILLED " : " ");
	strcat(stmt, "where NewDateTime >= to_date('");
	strcat(stmt, pDate0);
	strcat(stmt, "','YYYYMMDDHH24MI') order by 1");

#ifndef _NO_ORCL
	if (GetBarsFromQuery(DebugParms, DBParms->FXDB->DBCtx, stmt, pFutureLen, 0, FutureBar) != 0) return -1;
#endif
	//-- Repeat for each Dataset
	for (d = 0; d < pDatasetCount; d++) {
		for (i = 0; i<pFutureLen; i++) {
			switch (DBParms->BarDataType[d]) {
			case OPEN:
				oFutureData[d][i] = FutureBar[i].Open;
				break;
			case HIGH:
				oFutureData[d][i] = FutureBar[i].High;
				break;
			case LOW:
				oFutureData[d][i] = FutureBar[i].Low;
				break;
			case CLOSE:
				oFutureData[d][i] = FutureBar[i].Close;
				break;
			case VOLUME:
				oFutureData[d][i] = FutureBar[i].Volume;
				break;
			}
			oFutureBarW[d][i] = FutureBar[i].High - FutureBar[i].Low;
			oWholeData[d][pHistoryLen + i] = oFutureData[d][i];
			oWholeBarW[d][pHistoryLen + i] = oFutureBarW[d][i];
		}
	}

	//=== 3. Get Validation Data ===
	if (pValidationShift != 0) {
		//-- first, find the new Date0
		char newDate0[12 + 1];
		sprintf(&stmt[0], "select to_char(min(newdatetime),'YYYYMMDDHH24MI') from( select * from (	select newdatetime from History.%s_%s%s where newdatetime %s to_date(%s,'YYYYMMDDHH24MI') order by 1 desc ) where rownum<%d)", \
			DBParms->Symbol, DBParms->TimeFrame, ((DBParms->IsFilled > 0) ? "FILLED" : ""), ((pValidationShift > 0) ? ">" : "<"), pDate0, abs(pValidationShift));
if (GetCharPFromQuery(DebugParms, DBParms->FXDB->DBCtx, stmt, &newDate0[0])) return -1;

//-- then, same as for HistoryData
sprintf(&stmt[0], "select to_char(NewDateTime, 'YYYYMMDDHH24MI'), Open, High, Low, Close, nvl(Volume,0) from History.%s_%s%s where newdatetime <= to_date(%s,'YYYYMMDDHH24MI') order by 1", DBParms->Symbol, DBParms->TimeFrame, ((DBParms->IsFilled > 0) ? "FILLED" : ""), newDate0);


#ifndef _NO_ORCL
if (GetBarsFromQuery(DebugParms, DBParms->FXDB->DBCtx, stmt, pHistoryLen + 1, 1, PastBar) != 0) return -1;	//-- ValidationData
#endif
																															//-- Repeat for each Dataset
for (d = 0; d < pDatasetCount; d++) {

	//-- HistoryData
	for (i = 0; i < pHistoryLen; i++) {
		switch (DBParms->BarDataType[d]) {
		case OPEN:
			oValidationData[d][i] = PastBar[pHistoryLen - 1 - i].Open;
			break;
		case HIGH:
			oValidationData[d][i] = PastBar[pHistoryLen - 1 - i].High;
			break;
		case LOW:
			oValidationData[d][i] = PastBar[pHistoryLen - 1 - i].Low;
			break;
		case CLOSE:
			oValidationData[d][i] = PastBar[pHistoryLen - 1 - i].Close;
			break;
		case VOLUME:
			oValidationData[d][i] = PastBar[pHistoryLen - 1 - i].Volume;
			break;
		}
	}
	switch (DBParms->BarDataType[d]) {
	case OPEN:
		oPrevValV[d] = PastBar[pHistoryLen].Open;
		break;
	case HIGH:
		oPrevValV[d] = PastBar[pHistoryLen].High;
		break;
	case LOW:
		oPrevValV[d] = PastBar[pHistoryLen].Low;
		break;
	case CLOSE:
		oPrevValV[d] = PastBar[pHistoryLen].Close;
		break;
	case VOLUME:
		oPrevValV[d] = PastBar[pHistoryLen].Volume;
		break;
	}
}
	}
	free(PastBar); free(FutureBar);

	return 0;

}

int GetDataSetFromCol(int col, tFileData* pDataFile) {

	for (int d = 0; d < pDataFile->FileDataSetsCount; d++) {
		if (pDataFile->FileDataSet[d] == (col)) return d;
	}
	return -1;
}

#define MaxLineSize 200
void LineParser(tFileData* pDataFile, int l, char* pLine, char* pTimeStamp, int pHistoryLen, double** oHistoryData, double** oFutureData, double** oWholeData, double* oBaseVal) {
	int i, ii;
	int c, col, d, valcnt;
	char vals[32];
	double val;
	char delimiter = pDataFile->FieldSep;

	//-- Read first column (datetime)
	for (i = 0; i < 12; i++) pTimeStamp[i] = pLine[i];
	pTimeStamp[12] = '\0';
	//-- Remove first column from pLine, by sliding chars starting at pos.(12+1) backwards
	for (i = 0; i < (MaxLineSize); i++) {
		pLine[i] = pLine[i + 12 + 1];
	}
	//-- Now read each column into each dataset
	c = 0;
	col = 0;
	d = 0;
	valcnt = 0;
	while (pLine[c] != '\0') {
		vals[c] = pLine[c];
		if (vals[c] == delimiter || vals[c] == '\n') {
			val = atof(vals);
			d = GetDataSetFromCol(col, pDataFile);
			if (d != -1) {
				if (l>=0) oWholeData[d][l] = (double)val;
				//-- BaseVal vs. History vs. Future
				if (l < 0) {
					oBaseVal[d] = (double)val;
				} else if (l<pHistoryLen) {
					oHistoryData[d][l] = (double)val;
				} else {
					oFutureData[d][l - pHistoryLen] = (double)val;
				}
			}
			col++;
			//-- Remove retrieved column from pLine, by sliding chars starting at pos. (i+1) backwards
			for (ii = 0; ii < (MaxLineSize); ii++) {
				pLine[ii] = pLine[ii + c + 1];
			}
			c = -1;
		}
		c++;
	}

}
EXPORT int __stdcall LoadData_CSV(tDebugInfo* DebugParms, tFileData* pDataFile, int pHistoryLen, int pFutureLen, char* pDate0, int pValidationShift, int pDatasetCount, double** oHistoryData, double** oHistoryBarW, double** oValidationData, double** oFutureData, double** oFutureBarW, double** oWholeData, double** oWholeBarW, double* oPrevValH, double* oPrevValV, double* oPrevBarW) {
	//-- Data File must have no headers, and be sorted by datetime, ascending. First column should be a date in YYYYMMDDHH24MI format, then one column for each dataset

	char vLine[MaxLineSize]; strcpy(vLine, "0");
	char prevLine[MaxLineSize]; strcpy(prevLine, "0");
	char vLineBkp[MaxLineSize]; strcpy(vLineBkp, "0");
	char vTimeStamp[12 + 1];
	int i;
	int l = 0;
	int l0=0;
	bool isBaseValSet = false;

	//-- Open Data File
	FILE* fData = fopen(pDataFile->FileName, "r");
	if (fData == NULL) {
		LogWrite(DebugParms, LOG_ERROR, "Could not open Source Data File. Exiting...\n", 0);
		return -1;
	}

	//-- Find line number corresponding to pDate0, and out it into l0
	while (!feof(fData)) {
		if (fgets(vLine, MaxLineSize, fData) == NULL) {
			LogWrite(DebugParms, LOG_ERROR, "Unexpected end of History Data in Source File at %d. Exiting...\n", 1, l);
			return -1;
		}

		for (i = 0; i < 12; i++) vTimeStamp[i] = vLine[i];
		vTimeStamp[12] = '\0';
		if (atof(vTimeStamp) >= atof(pDate0)) break;

		l0++;
	}
	//-- Rewind, then advance l0 lines
	rewind(fData);
	if (l0<pHistoryLen) {
		LogWrite(DebugParms, LOG_ERROR, "Not enough History Data in Source File (Date0 found at line %d ; HistoryLen=%d). Exiting...\n", 2, l0+1, pHistoryLen);
		return -1;
	}
	for (i = 0; i<(l0-pHistoryLen+1); i++) {
		if (fgets(vLine, MaxLineSize, fData) == NULL) {
			LogWrite(DebugParms, LOG_ERROR, "Unexpected end of History Data in Source File at %d. Exiting...\n", 1, l);
			return -1;
		}
	}
	//-- we are now on prevLine, so we set oPrevVal by sending l=-1
	LineParser(pDataFile, -1, vLine, vTimeStamp, pHistoryLen, oHistoryData, oFutureData, oWholeData, oPrevValH);

	//-- Read Whole Data
	while(!feof(fData) && l<(pHistoryLen+pFutureLen)){

		strcpy(prevLine, vLineBkp);

		if (fgets(vLine, MaxLineSize, fData) == NULL) {
			LogWrite(DebugParms, LOG_ERROR, "Unexpected end of History Data in Source File at %d. Exiting...\n", 1, l);
			return -1;
		}
		strcpy(vLineBkp, vLine);

		//-- Read first column (datetime)
		for (i = 0; i < 12; i++) vTimeStamp[i] = vLine[i];
		vTimeStamp[12] = '\0';

		LineParser(pDataFile, l, vLine, vTimeStamp, pHistoryLen, oHistoryData, oFutureData, oWholeData, oPrevValH);

		l++;
	}

	//-- calc Barwidth
	int d, bwidxH, bwidxL;
	if (pDataFile->CalcFileDataBW>0) {
		for (d = 0; d<pDatasetCount; d++) {
			if (pDataFile->FileDataSet[d]==pDataFile->FileBWDataSet[0]) bwidxH = d;
			if (pDataFile->FileDataSet[d]==pDataFile->FileBWDataSet[1]) bwidxL = d;
		}
		for (d = 0; d<pDatasetCount; d++) {
			for (i = 0; i < (pHistoryLen); i++) {
				oHistoryBarW[d][i] = oHistoryData[bwidxH][i]-oHistoryData[bwidxL][i];
				oWholeBarW[d][i] = oHistoryBarW[d][i];
			}
			for (i = 0; i < (pFutureLen); i++) {
				oFutureBarW[d][i] = oFutureData[bwidxH][i]-oFutureData[bwidxL][i];
				oWholeBarW[d][pHistoryLen + i] = oFutureBarW[d][i];
			}
		}
	}

	fclose(fData);
	return 0;
}

EXPORT int __stdcall GetDates_FXDB(tDebugInfo* DebugParms, tFXData* SourceParms, char* StartDate, int DatesCount, char** oDate) {
	// Retrieves plain ordered list of NewDateTime starting from StartDate onwards for <DatesCount> records
	char stmt[1000];

#ifndef _NO_ORCL
	if (SourceParms->FXDB->DBCtx == NULL) {
		if (OraConnect(DebugParms, SourceParms->FXDB) != 0) return -1;
	}
#endif
	//strcpy(stmt, "select to_char(NewDateTime, 'YYYYMMDDHH24MI'), 0,0,0,0,0,0,0,0,0,0 from History.");
	strcpy(stmt, "select to_char(NewDateTime, 'YYYYMMDDHH24MI') from History.");
	strcat(stmt, SourceParms->Symbol);
	strcat(stmt, "_");
	strcat(stmt, SourceParms->TimeFrame);
	strcat(stmt, (SourceParms->IsFilled == 1) ? "_FILLED " : " ");
	strcat(stmt, "where NewDateTime>=to_date('");
	strcat(stmt, StartDate);
	strcat(stmt, "','YYYYMMDDHH24MI') order by 1");

#ifndef _NO_ORCL
	if (GetStringArrayFromQuery(DebugParms, SourceParms->FXDB->DBCtx, stmt, DatesCount, oDate) != 0) return -1;
#endif
	return 0;
}

EXPORT int __stdcall GetDates_CSV_OLD(tDebugInfo* DebugParms, tFileData* pDataFile, char* StartDate, int pDatesCount, char** oDate) {
	// Retrieves plain ordered list of DateTime starting from StartDate onwards for <DatesCount> records

	int vLinesCount = 0;
	char vLine[1024];
	char vDateTime[12 + 1];
	int i;
	int retcnt = 0;

	FILE* fData = fopen(pDataFile->FileName, "r");
	if (fData == NULL) {
		LogWrite(DebugParms, LOG_ERROR, "Could not open Source Data File. Exiting...\n", 0);
		return -1;
	}

	//-- 1. Just Count number of lines in file
	while (fgets(vLine, sizeof(vLine), fData)) vLinesCount++;

	//-- 2. malloc() temporary container for un-sorted dates
	char** tmpDate = (char**)malloc(vLinesCount*(12 + 1)); for (i = 0; i < vLinesCount; i++) tmpDate[i] = (char*)malloc(12 + 1);

	//-- 3. Load un-sorted dates in temporary container
	rewind(fData); i = 0;
	while (fgets(vLine, sizeof(vLine), fData)) {
		memcpy(vDateTime, vLine, 12);
		vDateTime[12] = '\0';
		strcpy(tmpDate[i], vDateTime);
		i++;
	}

	//-- 4. Sort temporary container
	StringSort(vLinesCount, tmpDate);
	//-- 4.1 Copy first elements of temporary container into oDate, if greater than StartDate
	for (i = 0; i < vLinesCount; i++) {
		if (strcmp(tmpDate[i], StartDate) >= 0) {
			memcpy(oDate[retcnt], tmpDate[i], 12);
			oDate[retcnt][12] = '\0';
			retcnt++;
			if (retcnt >= pDatesCount) break;
		}
	}
	//-- 5. free(s)
	for (i = 0; i < vLinesCount; i++) free(tmpDate[i]);
	free(tmpDate);

	fclose(fData);
	return 0;
}

EXPORT int __stdcall GetDates_CSV(tDebugInfo* DebugParms, tFileData* pDataFile, char* StartDate, int pDatesCount, char** oDate) {
	// Retrieves plain ordered list of DateTime starting from StartDate onwards for <DatesCount> records. CSV file MUST BE SORTED in ascending order!

	char vLine[1024];
	char vDateTime[12 + 1];
	int i;
	int retcnt = 0;

	FILE* fData = fopen(pDataFile->FileName, "r");
	if (fData == NULL) {
		LogWrite(DebugParms, LOG_ERROR, "Could not open Source Data File. Exiting...\n", 0);
		return -1;
	}

	i = 0;
	while (fgets(vLine, sizeof(vLine), fData)) {
		memcpy(vDateTime, vLine, 12);
		if (strcmp(vDateTime, StartDate) >=0) {
			memcpy(oDate[retcnt], vDateTime, 12);
			oDate[retcnt][12] = '\0';
			retcnt++;
			if (retcnt >= pDatesCount) break;
		}
		i++;
	}

	fclose(fData);
	return 0;
}

EXPORT int __stdcall LoadHistoryData(int pHistoryLen, char* pDate0, int pBarDataType, double* oHistoryData, tFXData* DBParms, tDebugInfo* DebugParms) {
	int i;
	tBar* PastBar = (tBar*)malloc(pHistoryLen * sizeof(tBar));
	char stmt[1000];

#ifndef _NO_ORCL
	if (DBParms->FXDB->DBCtx == NULL) {
		if (OraConnect(DebugParms, DBParms->FXDB) != 0) return -1;
	}
#endif
	//=== 1. Get History Data ===
	strcpy(stmt, "select to_char(NewDateTime, 'YYYYMMDDHH24MI'), Open, High, Low, Close, nvl(Volume,0), Open-nvl(lag(Open) over(order by NewDateTime), 0), High-nvl(lag(High) over(order by NewDateTime), 0), Low-nvl(lag(Low) over(order by NewDateTime), 0), Close-nvl(lag(Close) over(order by NewDateTime), 0), nvl(Volume,0)-nvl(lag(Volume) over(order by NewDateTime), 0) from History.");
	strcat(stmt, DBParms->Symbol);
	strcat(stmt, "_");
	strcat(stmt, DBParms->TimeFrame);
	strcat(stmt, (DBParms->IsFilled == 1) ? "_FILLED " : " ");
	strcat(stmt, "where NewDateTime <= to_date('");
	strcat(stmt, pDate0);
	strcat(stmt, "','YYYYMMDDHH24MI') order by 1 desc");

#ifndef _NO_ORCL
	if (GetBarsFromQuery(DebugParms, DBParms->FXDB->DBCtx, stmt, pHistoryLen, 0, PastBar) != 0) return -1;
#endif

	for (i = 0; i<pHistoryLen; i++) {
		switch (pBarDataType) {
		case OPEN:
			oHistoryData[i] = PastBar[i].Open;
			break;
		case HIGH:
			oHistoryData[i] = PastBar[i].High;
			break;
		case LOW:
			oHistoryData[i] = PastBar[i].Low;
			break;
		case CLOSE:
			oHistoryData[i] = PastBar[i].Close;
			break;
		case VOLUME:
			oHistoryData[i] = PastBar[i].Volume;
			break;
		}
	}

	//-- Disconnect upon exit
	//OraDisconnect(vCtx);
	free(PastBar);

	return 0;

}

#define LOGMINVAL -10000
EXPORT void dataTransform(int dt, int dlen, double* idata, double baseVal, double* odata) {

	switch (dt) {

	case DT_DELTA:
		for (int i = 0; i < dlen; i++) odata[i] = idata[i] - ((i>0) ? idata[i - 1] : baseVal);
		break;

	case DT_LOG:
		for (int i = 0; i < dlen; i++) odata[i] = log(idata[i] - LOGMINVAL + 1);
		break;

	case DT_DELTALOG:
		dataTransform(DT_DELTA, dlen, idata, baseVal, odata);
		dataTransform(DT_LOG,   dlen, odata, baseVal, odata);
		break;

	default:
		for (int i = 0; i < dlen; i++) odata[i] = idata[i];
		break;
	}

}

EXPORT void dataUnTransform(int dt, int dlen, int from_i, int to_i, double* idata, double baseVal, double* iActual, double* odata) {
	double prev;
	int i;

	switch (dt) {

	case DT_DELTA:
		for (i = from_i; i < to_i; i++) {
			if (i > from_i) {
				prev = (iActual[i-1]!=EMPTY_VALUE)?iActual[i-1]:odata[i-1];
			}
			else {
				if (from_i > 0) {
					prev = iActual[i-1];
				}
				else {
					prev = baseVal;
				}
			}
			odata[i] = idata[i] + prev;
		}
		break;

	case DT_LOG:
		for (i = from_i; i < to_i; i++) odata[i] = exp(idata[i]) + LOGMINVAL - 1;
		break;

	case DT_DELTALOG:

		for (i = from_i; i < to_i; i++){

			//-- 1. unLOG
			odata[i] = exp(idata[i]) + LOGMINVAL - 1;

			//-- 2. unDELTA
			if (i > from_i) {
				prev = iActual[i-1];
			} else {
				if (from_i > 0) {
					prev = iActual[i-1];
				} else {
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

	for (i = 0; i < from_i; i++) odata[i] = EMPTY_VALUE;
	for (i = to_i; i < dlen; i++) odata[i] = EMPTY_VALUE;

}

EXPORT void __stdcall TSfromSamples(int sampleCnt, int sampleLen, double** iSample, double* oTS) {

	for (int i = 0; i < sampleLen; i++)	oTS[i] = iSample[0][i];

	for (int s = 1; s < sampleCnt; s++)	oTS[sampleLen - 1 + s] = iSample[s][sampleLen - 1];

}

//-- Timeseries Statistical Features

EXPORT double __stdcall TSMean(int VLen, double* V) {
	double VSum = 0;
	for (int i = 0; i < VLen; i++) VSum += V[i];
	return(VSum / VLen);
}

EXPORT double __stdcall TSMeanAbsoluteDeviation(int VLen, double* V) {
	double VAvg = TSMean(VLen, V);
	double VSum = 0;
	for (int i = 0; i < VLen; i++) VSum += fabs(V[i] - VAvg);
	return(VSum / VLen);
}

EXPORT double __stdcall TSVariance(int VLen, double* V) {
	double VAvg = TSMean(VLen, V);
	double VSum = 0;
	for (int i = 0; i < VLen; i++) VSum += pow(V[i] - VAvg, 2);
	return(VSum / (VLen - 1));
}

EXPORT double __stdcall TSSkewness(int VLen, double* V) {
	double VAvg = TSMean(VLen, V);
	double VSigma = sqrt(TSVariance(VLen, V));
	double VSum = 0;
	for (int i = 0; i < VLen; i++) VSum += pow((V[i] - VAvg) / VSigma, 3);
	return(VSum / VLen);
}

EXPORT double __stdcall TSKurtosis(int VLen, double* V) {
	double VAvg = TSMean(VLen, V);
	double VSigma = sqrt(TSVariance(VLen, V));
	double VSum = 0;
	for (int i = 0; i < VLen; i++) VSum += pow((V[i] - VAvg) / VSigma, 4);
	return(VSum / VLen - 3);
}

EXPORT double __stdcall TSTurningPoints(int VLen, double* V) {
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

EXPORT double __stdcall TSShannonEntropy(int VLen, double* V) {
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

EXPORT double __stdcall TSHistoricalVolatility(int VLen, double* V) {
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

EXPORT void __stdcall CalcTSF(int TSFcnt, int* TSFid, tDataShape* pDataParms, int pTSLen, double* pTS, double* pTSF) {
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

EXPORT int __stdcall FXDataCompact(char* INfilename, int INtimeframe, char* OUTfilename, int OUTtimeframe) {
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
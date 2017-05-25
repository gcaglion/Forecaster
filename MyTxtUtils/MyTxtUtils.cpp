#include <MyTxtUtils.h>

int GetDataSetFromCol(int col, tFileData* pDataFile) {

	for (int d = 0; d < pDataFile->FileDataSetsCount; d++) {
		if (pDataFile->FileDataSet[d] == (col + 1)) return d;
	}
	return -1;
}

EXPORT int Txt_GetDates(tDebugInfo* DebugParms, tFileData* pDataFile, char* StartDate, int pDatesCount, char** oDate) {
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
EXPORT int Txt_LoadData(tDebugInfo* DebugParms, tFileData* pDataFile, int pHistoryLen, int pFutureLen, char* pDate0, int pValidationShift, int pDatasetCount, double** oHistoryData, double** oHistoryBarW, double** oValidationData, double** oFutureData, double** oFutureBarW, double** oWholeData, double** oWholeBarW) {
	//-- Data File must have no headers. First column should be a date in YYYYMMDDHH24MI format, then one column for each dataset

	const int MaxLineSize = 200;
	char vLine[MaxLineSize];
	char vTimeStamp[12 + 1];
	char vals[32];
	double val;
	int valcnt;
	int d, i, c, l, ii;
	int col;
	char delimiter = '\t';

	//-- Open Data File
	FILE* fData = fopen(pDataFile->FileName, "r");
	if (fData == NULL) {
		LogWrite(DebugParms, LOG_ERROR, "Could not open Source Data File. Exiting...\n", 0);
		printf("Press any key to continue...\n"); getchar();;
		return -1;
	}

	//-- Barwidth is always 0 for File-based data
	for (d = 0; d < pDatasetCount; d++) {
		for (i = 0; i < (pHistoryLen); i++) {
			oHistoryBarW[d][i] = 0;
			oWholeBarW[d][i] = 0;
		}
		for (i = 0; i < (pFutureLen); i++) {
			oFutureBarW[d][i] = 0;
			oWholeBarW[d][pHistoryLen + i] = 0;
		}
	}

	//-- Read Whole Data
	for (l = 0; l < (pHistoryLen + pFutureLen); l++) {
		if (fgets(vLine, MaxLineSize, fData) == NULL) {
			LogWrite(DebugParms, LOG_ERROR, "Unexpected end of History Data in Source File at %d. Exiting...\n", 1, l);
			printf("Press any key to continue...\n"); getchar();;
			return -1;
		}
		//-- Read first column (datetime)
		for (i = 0; i < 12; i++) vTimeStamp[i] = vLine[i];
		vTimeStamp[12] = '\0';
		//-- Remove first column from vLine, by sliding chars starting at pos.(12+1) backwards
		for (i = 0; i < (MaxLineSize); i++) {
			//if (vLine[i] == '\0') break;	// end of line
			vLine[i] = vLine[i + 12 + 1];
		}
		//-- Now read each column into each dataset
		c = 0;
		col = 0;
		d = 0;
		valcnt = 0;
		while (vLine[c] != '\0') {
			vals[c] = vLine[c];
			if (vals[c] == delimiter || vals[c] == '\n') {
				val = atof(vals);
				d = GetDataSetFromCol(col, pDataFile);
				if (d != -1) oWholeData[d][l] = (double)val;
				//-- History vs. Future
				if (l<pHistoryLen) {
					if (d != -1) oHistoryData[d][l] = (double)val;
				}
				else {
					if (d != -1) oFutureData[d][l - pHistoryLen] = (double)val;
				}
				col++;
				//-- Remove retrieved column from vLine, by sliding chars starting at pos. (i+1) backwards
				for (ii = 0; ii < (MaxLineSize); ii++) {
					//if (vLine[ii] == 0) break;	// end of line
					vLine[ii] = vLine[ii + c + 1];
				}
				c = -1;
			}
			c++;
		}
	}

	fclose(fData);
	return 0;
}

EXPORT int Txt_LoadDataParms(tDebugInfo* DebugParms, int pid, int* oHistoryLen, int* oSampleLen, int* oSampleCount, int* oPRedictionLen, int* oDataTransformation, double* oWiggleRoom){ return -1; }
EXPORT int Txt_LoadEngineParms(tDebugInfo* DebugParms, int pid, int* oEngineType, int* oLayersCount, int* oDecompLevel, char** oWaveletType){ return -1; }

//-- Load CoreParms(s)
EXPORT int Txt_GetCoreThreadId(tDebugInfo* DebugParms, int pid, int testid, int DatasetId, int LayerId, int CoreId){ return -1; }
EXPORT int Txt_LoadCoreParms_NN(tDebugInfo* DebugParms, int pid, int tid,
	int* oInputCount, int* oOutputCount, int* oUseContext, int* oMaxEpochs, int* oBP_Algo, int* oActivationFunction,
	char* oLevelRatioS[256],
	double* oLearningRate, double* oLearningMomentum, double* oHCPBeta, double* oTargetMSE){ return -1; }
EXPORT int Txt_LoadCoreParms_SOM(tDebugInfo* DebugParms, int pid, int tid,
	int* oInputCount, int* oOutputCount, int* oMaxEpochs, int* oTDFunction, int* oLRFunction,
	double* oBaseTD, double* oBaseLR){ return -1; }
EXPORT int Txt_LoadCoreParms_SVM(tDebugInfo* DebugParms, int pid, int tid,
	int* oInputCount, int* oMaxEpochs, int* osvmIterToShrink, int* oKernelType, int* oPolyDegree, int* oKernelCacheSize,
	double* oC, double* oEpsilon, double* oRBFGamma, double* oCoefLin, double* oCoefConst){ return -1; }

//-- Load Core Image
EXPORT int Txt_LoadCoreImage_NN(tDebugInfo* DebugParms, int pid, int tid, double*** oFinalW){ return -1; }
EXPORT int Txt_LoadCoreImage_SOM(tDebugInfo* DebugParms, int pid, int tid, double** oSOMWeight){ return -1; }
EXPORT int Txt_LoadCoreImage_SVM(tDebugInfo* DebugParms, int pid, int tid, double** oSVMWeight){ return -1; }

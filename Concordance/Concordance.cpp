#include <stdlib.h>
#include "stdio.h"
#include "windows.h"
#include "winbase.h"
#include "time.h"
#include <math.h>

#include <MyUtils.h>
#include <MyLog.h>
#include <FXData.h>
#include <MyOraUtils.h>
#include <Concordance.h>

#define FH 0
#define FL 1

// ====== ConcordanceCalc - related ========

int SRank(int pOutputType, tBar* CBar, tBar* HBar, int arrsize, int arr2RankFrom, double* oCRank, double* oHRank, double* od2Rank){
	int i, j;
	int Num, Den;
	//-- Build main table
	struct RankRecord{
		double CVal;
		double HVal;
		double CRank;
		double HRank;
		double d2Rank;
	};
	RankRecord* rec = (RankRecord*)malloc(arrsize*sizeof(struct RankRecord));

	//-- Load arr1 into RankRecord.CVal, arr2 into RankRecord.HVal
	for (i = 0; i < arrsize; i++){
		rec[i].CVal = (pOutputType == FH) ? CBar[i].High : CBar[i].Low;
		rec[i].HVal = (pOutputType == FH) ? HBar[arr2RankFrom + i].High : HBar[arr2RankFrom + i].Low;
	}
	//-- Sort main table by HVal
	for (i = 0; i < arrsize; i++){
		for (j = 0; j < i; j++){
			if (rec[i].HVal < rec[j].HVal){
				swapD(&rec[i].CVal, &rec[j].CVal);
				swapD(&rec[i].HVal, &rec[j].HVal);
			}
		}
	}
	//-- Set HRank
	for (i = 1; i <= arrsize; i++){
		Num = i; Den = 1;
		while (rec[i - 1].HVal == rec[i].HVal){
			Num = Num + i + 1;
			Den++;
			i++;
		}
		for (j = 0; j < Den; j++){
			rec[i - j - 1].HRank = (double)Num / Den;
		}
	}
	//-- Sort main table by CVal
	for (i = 0; i < arrsize; i++){
		for (j = 0; j < i; j++){
			if (rec[i].CVal < rec[j].CVal){
				swapD(&rec[i].CVal, &rec[j].CVal);
				swapD(&rec[i].HVal, &rec[j].HVal);
				swapD(&rec[i].HRank, &rec[j].HRank);
			}
		}
	}
	//-- Set CRank, d2Rank
	for (i = 1; i <= arrsize; i++){
		Num = i; Den = 1;
		while (rec[i - 1].CVal == rec[i].CVal){
			Num = Num + i + 1;
			Den++;
			i++;
		}
		for (j = 0; j < Den; j++){
			rec[i - j - 1].CRank = (double)Num / Den;
			rec[i - j - 1].d2Rank = pow((rec[i - j - 1].CRank - rec[i - j - 1].HRank), 2);
		}
	}
	//-- Populate return arrays oCRank, oHRank, od2Rank
	for (i = 0; i < arrsize; i++){
		oCRank[i] = rec[i].CRank;
		oHRank[i] = rec[i].HRank;
		(*od2Rank) += rec[i].d2Rank;
	}
	free(rec);
	return 0;
}

EXPORT int __stdcall ConcordanceCalc(tConcCalcParms* parms){
#define BULK_SIZE 9000
#define TOP_PREDICTORS_COUNT 10
	//--
	int ret;
	int h, i, j, l, t, u;
	int CRecCount;
	int HRecCount;
	char vCFromDate[12 + 1];
	double Sumd2Rank;
	double vSRho;
	double Knumer;
	double vKTau;
	double vWeakC;
	double vGini;
	int InsertCount = 0;
	int InsertTotalCount = 0;
	int InsertActualCount = 0;
	tConcordanceRec ConcordanceRec[BULK_SIZE];
	tConcordanceRec BestSRHORec[TOP_PREDICTORS_COUNT];
	tConcordanceRec BestKTAURec[TOP_PREDICTORS_COUNT];

	MyLogWrite(parms->DebugParms, "%s Process %d , Thread %d : Calling ConcordanceCalc for %s...\n", 4, timestamp(), GetCurrentProcessId(), GetCurrentThreadId(), (parms->OutputType == FH) ? "High" : "Low");

	//-- Load CRec
	CRecCount = parms->PastDepth;
	tBar* CRec = (tBar*)malloc(CRecCount * sizeof(tBar));
	if (LoadCurrentRecord(parms->DebugParms, parms->FXDBInfo,  pCToDate, pPastDepth,  CRecCount, CRec) != 0) return -1;
	strcpy(vCFromDate, CRec[0].NewDateTime);
	double* CRank = (double*)malloc(CRecCount*sizeof(double));

	//-- Load HRec
	if (GetHRecCount(parms->DebugParms, pContext, pHSymbol, pTimeFrame, vCFromDate, pDelta, pIsFilled, &HRecCount) != 0) return -1;
	tBar* HRec = (tBar*)malloc(HRecCount * sizeof(tBar));
	if (LoadHistoryRecord(pDebugLevel, pLogFile, pContext, pHSymbol, pTimeFrame, vCFromDate, pDelta, pIsFilled, HRecCount, HRec) != 0) return -1;
	double* HRank = (double*)malloc(CRecCount*sizeof(double));

	//-- Initialize Best Predictors
	for (i = 0; i < TOP_PREDICTORS_COUNT; i++){
		BestSRHORec[i].SRho = 0;
		BestKTAURec[i].KTau = 0;
	}
	//-- Main loop (h,l)
	for (h = 0; h <= (HRecCount - CRecCount); h++){
		for (l = CRecCount; l <= CRecCount; l++){
			//-- Calc Spearman Rho
			Sumd2Rank = 0;
			ret = SRank(pOutputType, CRec, HRec, l, h, CRank, HRank, &Sumd2Rank);
			vSRho = 1 - (6 * Sumd2Rank) / (l*(pow((double)l, 2) - 1));
			//-- Calc Kendall Tau
			Knumer = 0;
			for (i = 1; i < l; i++){
				for (j = 0; j<(i - 1); j++){
					if (pOutputType == FH){
						Knumer = Knumer + sign(CRec[i].High - CRec[j].High) * sign(HRec[i + h].High - HRec[j + h].High);
					}
					else{
						Knumer = Knumer + sign(CRec[i].Low - CRec[j].Low) * sign(HRec[i + h].Low - HRec[j + h].Low);
					}
				}
			}
			vKTau = Knumer / (0.5 * l*(l - 1));
			//-- Calc WeakC
			vWeakC = 0;
			//-- Calc Gini
			vGini = 0;
			//-- Prepare array for insert
			strcpy(ConcordanceRec[InsertCount].CurrentData, pCSymbol);
			strcpy(ConcordanceRec[InsertCount].CurrentStart, CRec[0].NewDateTime);
			strcpy(ConcordanceRec[InsertCount].TimeFrame, pTimeFrame);
			strcpy(ConcordanceRec[InsertCount].OutputType, (pOutputType == FH) ? "High" : "Low");
			strcpy(ConcordanceRec[InsertCount].PredictorData, pHSymbol);
			Trim(HRec[h].NewDateTime); strcpy(ConcordanceRec[InsertCount].PredictorStart, HRec[h].NewDateTime);
			ConcordanceRec[InsertCount].PatternLength = l;
			ConcordanceRec[InsertCount].PatternShift = h;
			ConcordanceRec[InsertCount].KTau = vKTau;
			ConcordanceRec[InsertCount].SRho = vSRho;
			ConcordanceRec[InsertCount].Gini = vGini;
			ConcordanceRec[InsertCount].WeakC = vWeakC;
			//-- Does this make the Top-10?
				//-- First, SRho
			if (ConcordanceRec[InsertCount].SRho > BestSRHORec[0].SRho){
				for (u = TOP_PREDICTORS_COUNT - 1; u>0; u--) memcpy(&BestSRHORec[u], &BestSRHORec[u - 1], sizeof(tConcordanceRec));
				memcpy(&BestSRHORec[0], &ConcordanceRec[InsertCount], sizeof(tConcordanceRec));
			}
			//-- Then, KTau
			if (ConcordanceRec[InsertCount].KTau > BestKTAURec[0].KTau){
				for (u = TOP_PREDICTORS_COUNT - 1; u>0; u--) memcpy(&BestKTAURec[u], &BestKTAURec[u - 1], sizeof(tConcordanceRec));
				memcpy(&BestKTAURec[0], &ConcordanceRec[InsertCount], sizeof(tConcordanceRec));
			}
			InsertCount++;
			//-- Bulk Insert BULK_SIZE records
			if (InsertCount == BULK_SIZE){
				//if (BulkConcordanceInsert(pDebugLevel, pLogFile, pContext, &InsertCount, ConcordanceRec) <-1) return -1;	// 0: insert completed ; 1: data already in concordance table
				InsertTotalCount += InsertCount;
				InsertCount = 0;
			}
		}
	}
	//-- Bulk Insert the remaining records
	int TPC = TOP_PREDICTORS_COUNT;
	if (BulkConcordanceInsert(pDebugLevel, pLogFile, pContext, &TPC, BestSRHORec) <-1) return -1;
	if (BulkConcordanceInsert(pDebugLevel, pLogFile, pContext, &TPC, BestKTAURec) <-1) return -1;
	//if (BulkConcordanceInsert(pDebugLevel, pLogFile, pContext, &InsertCount, ConcordanceRec) <-1) return -1;
	InsertTotalCount += InsertCount;
	//MyLogWrite(pDebugLevel, pLogFile, "%s Bulk Insert Completed. %d records inserted.\n", 2, timestamp(), InsertTotalCount);

	free(CRec); free(CRank); free(HRec); free(HRank);

	MyLogWrite(pDebugLevel, pLogFile, "%s Thread %d : Completed ConcordanceCalc for %s. %d records inserted in TConcordance\n", 4, timestamp(), GetCurrentThreadId(), (pOutputType == FH) ? "High" : "Low", InsertTotalCount);
	return 0;
}
//=========================================

int main(int argc, char* argv[]){
	tCalcConc** param = (tCalcConc**)malloc(2 * sizeof(tCalcConc*)); param[FH] = (tCalcConc*)malloc(sizeof(tCalcConc)); param[FL] = (tCalcConc*)malloc(sizeof(tCalcConc));
	param[FH]->OutputType = FH;
	param[FH]->DebugLevel = 1;
	param[FH]->UserName = "GAUser"; param[FH]->Password = "GAPwd"; param[FH]->DBString = "Algo";
	param[FH]->CSymbol = "EURUSD";
	param[FH]->HSymbol = "EURUSD";
	param[FH]->TimeFrame = "H1";
	param[FH]->CToDate = "201502270000";
	param[FH]->PastDepth = 24;
	param[FH]->Delta = 0;
	param[FH]->IsFilled = 0;
	FILE* vLogFile = fopen("c:\\temp\\Concordance.log", "w");
	param[FH]->LogFile = vLogFile;
	void* vCtx;

	if (OraConnect(param[FH]->UserName, param[FH]->Password, param[FH]->DBString, param[FH]->DebugLevel, vLogFile, &vCtx) != 0) return -1;
	param[FH]->Context = vCtx;

	printf("ConcordanceCalc(High) returned %d\n", ConcordanceCalc(param[FH]));

	OraDisconnect(vCtx);

	fclose(vLogFile);
	system("pause");
	return 0;
}

#include <stdio.h>
#include <iostream>
#include <cstring>
#include <stdlib.h>
#include <math.h>
#include <algorithm>
// Multi-Threading
#include <conio.h>
#include <process.h>
#include <windows.h>

#include <MyGA.h>
#include <MyLogger.h>
#include <MyUtils.h>

//--- Data Structures ---//
#define ADF_VALUE_DATA   1
#define ADF_VALUE_SCALAR 2
#define PARENT 0
#define CHILD  1
const int OperationsCount = 8;	// { <terminal> , + , - , * , / , cos, sin, sqr , max}
const int FixedValuesCount = 19;
int FixedValue[FixedValuesCount] = { -9, -8, -7, -6, -5, -4, -3, -2, -1, 0, 1, 2, 3, 4, 5, 6, 7, 8, 9 };

#undef EXPORT
#define EXPORT __declspec (dllexport)

typedef struct sADF {
	int level;
	int opid;			// For Functional ADFs
	int valueType;		// For Terminal ADFs, to discriminate between PastData and Scalars
	int valueid;		// Terminal ADFs, ID only
	double value;		// Terminal	ADFs, actual value to use for evaluation
	int ChromosomeId;	// 
	int parent;
	int child1;
	int child2;
} tADF;

typedef struct sChromosome{
	int		RootADFid;
	double	Cval;
	double	Fitness;
}tChromosome;

typedef struct{
	tDebugInfo* DebugParms; 
	GA_Parms* GAParams; 
	GA_Logs* GALogs;
	int DatasetId;
	int NetId;
	int TestId;
	int SampleCount; 
	int SampleLen; 
	double** SampleData; 
	double** SampleTarget; 
	tChromosome* Chromosome; 
	tADF* ADF;
	tChromosome* tempChr;
	tADF* tempADF;
	tEngineHandle* TrainInfo;
} tTrainParams;

void SaveMSEData(GA_Logs* GALogs, int pNetId, DWORD pid, DWORD tid, int pDataSet, int pTestId, int pEpoch, double pMSE_T, double pMSE_V){
	GALogs->MSEOutput[pEpoch].ProcessId = pid;
	GALogs->MSEOutput[pEpoch].ThreadId = tid;
	GALogs->MSEOutput[pEpoch].TestId = pTestId;
	GALogs->MSEOutput[pEpoch].Epoch = pEpoch;
	GALogs->MSEOutput[pEpoch].MSE_T = pMSE_T;
	GALogs->MSEOutput[pEpoch].MSE_V = pMSE_V;
}

void SaveRunData(GA_Logs* GALogs, int pNetId, DWORD pid, DWORD tid, int pDataSet, int pTestId, int pPos, int pOOSPos, double pActual, double pPredicted, double pError/*, double pBarWidth, double pErrorP*/){
	GALogs->RunOutput[pPos].ProcessId = pid;
	GALogs->RunOutput[pPos].ThreadId = tid;
	GALogs->RunOutput[pPos].TestId = pTestId;
	GALogs->RunOutput[pPos].Pos = pPos;
	GALogs->RunOutput[pPos].Actual = pActual;
	GALogs->RunOutput[pPos].Predicted = pPredicted;
	GALogs->RunOutput[pPos].Actual = pActual;
	GALogs->RunOutput[pPos].Error = pError;
	//GALogs->RunOutput[pPos].BarWidth = pBarWidth;
	//GALogs->RunOutput[pPos].ErrorP = pErrorP;
}

EXPORT int 		__stdcall  DelChrFiles(GA_Parms* GAParms, DWORD pid){
	int ret = 0;
	WIN32_FIND_DATA FindFileData;
	HANDLE hFind;

	LPCWSTR fname = (LPCWSTR)malloc(260);
	char* fPattern = (char*)malloc(500);
	strcpy(fPattern, GAParms->BestChrPath);
	strcat(fPattern, "\\Chr_p*");

	printf("Deleting chromosome files: %s\n", fPattern);
	hFind = FindFirstFile(convertCharArrayToLPCWSTR(fPattern), &FindFileData);
	if (hFind == INVALID_HANDLE_VALUE)	{
		printf("FindFirstFile failed (%d)\n", GetLastError());
		ret = -1;
	}
	else {
		if (DeleteFile(FullFileName(GAParms->BestChrPath, FindFileData.cFileName)) == 0) ret = -1;
	}

	while (FindNextFile(hFind, &FindFileData) != 0){
		if (DeleteFile(FullFileName(GAParms->BestChrPath, FindFileData.cFileName)) == 0) ret = -1;
	}

	FindClose(hFind);
	free(fPattern); //free(fname);
	return ret;
}

int PickADFValue(GA_Parms* GAParms, int pListLen){
	// Makes sure every one of the PastData values are present in each chromosome
	static __declspec(thread) int* vList;
	static __declspec(thread) int vListCount = -1;
	int i; int l;
	int ret = -2;
	//time_t starttime = time(NULL);
	while (ret<-1){
		if (GAParms->ADF_ForcePresence == 1){
			if (vListCount == -1) vList = (int*)malloc(pListLen*sizeof(int));
			if (vListCount <= 0) {
				vListCount = pListLen;
				for (i = 0; i<pListLen; i++) vList[i] = i;
			}
			i = (vListCount>1) ? MyRndInt(0, vListCount - 1) : 0;
			ret = vList[i];
			for (l = i; l<vListCount - 1; l++) vList[l] = vList[l + 1];
			vListCount--;
		}
		else {
			ret = MyRndInt(0, pListLen - 1);
		}
	}
	//	LogWrite(gDebugLevel, gLogFile, "PickADFValue\t%f\n", 1, difftime(time(NULL),starttime));
	return ret;
}

double EvalADF(tADF* ADF, int ADFid){
	double ret;
	//printf("\n[EvalADF]: ADF[%d].level=%d ; ADF[%d].opid=%d ; ADF[%d].valueType=%d, ADF[%d].valueid=%d ; ADF[%d].value=%10.5f ; ADF[%d].ChromosomeId=%d ; ADF[%d].parent=%d ; ADF[%d].child1=%d ; ADF[%d].child2=%d ", ADFid, ADF[ADFid].level, ADFid, ADF[ADFid].opid, ADFid, ADF[ADFid].valueType, ADFid, ADF[ADFid].valueid, ADFid, ADF[ADFid].value, ADFid, ADF[ADFid].ChromosomeId, ADFid, ADF[ADFid].parent, ADFid, ADF[ADFid].child1, ADFid, ADF[ADFid].child2);
	switch (ADF[ADFid].opid){
	case 0: ret = ADF[ADFid].value; break;
	case 1:	ret = EvalADF(ADF,  ADF[ADFid].child1) + EvalADF(ADF,  ADF[ADFid].child2); break;
	case 2:	ret = EvalADF(ADF,  ADF[ADFid].child1) - EvalADF(ADF,  ADF[ADFid].child2); break;
	case 3:	ret = EvalADF(ADF,  ADF[ADFid].child1) * EvalADF(ADF,  ADF[ADFid].child2); break;
	case 4:	ret = EvalADF(ADF,  ADF[ADFid].child1) / (EvalADF(ADF,  ADF[ADFid].child2) == 0 ? 1 : EvalADF(ADF,  ADF[ADFid].child2)); break;
	case 5: ret = cos(EvalADF(ADF,  ADF[ADFid].child1) * EvalADF(ADF,  ADF[ADFid].child2)); break;		// cos() returns cos(Arg1*Arg2)
	case 6: ret = sin(EvalADF(ADF,  ADF[ADFid].child1) * EvalADF(ADF,  ADF[ADFid].child2)); break;		// sin() returns sin(Arg1*Arg2)
	case 7: ret = sqrt(abs(EvalADF(ADF,  ADF[ADFid].child1)) * abs(EvalADF(ADF,  ADF[ADFid].child2))); break;		// sqr() returns sqr(abs(Arg1)*abs(Arg2))
	case 8: ret = max(EvalADF(ADF,  ADF[ADFid].child1), EvalADF(ADF,  ADF[ADFid].child2)); break;
	}
	return ret;
}

int FindADFParent(GA_Parms* GAParms, int ADFIdx){  // Fast, but Works only if ADFs are never mutaded or crossed over . :-(
	//time_t starttime = time(NULL);
	int ret = 0;
	int id = ADFIdx % ((int)pow((double)2, GAParms->Levels) - 1);	// First, find the correspoinding ADFId from ADF 0

	if (floor(id / 2) != id / 2) id = id + 1;	// always pick the even (rightmost) child
	ret = (int)id / 2 - ((id == 0)?0:1);
	// Before returning, traslate to original ADF
	ret = (int)floor((double)ADFIdx / ((int)pow((double)2, GAParms->Levels) - 1))*((int)pow((double)2, GAParms->Levels) - 1) + ret;
	if (ret<0) printf("==== FindADFParent(%d) is returning %d !!! ===\n", id, ret);
	//LogWrite(gDebugLevel, gLogFile, "FindADFParent\t%f\n", 1, difftime(time(NULL), starttime));
	return ret;
}

int InitADFs(tDebugInfo* pDebugParms, GA_Parms* GAParms, tADF* ADF, int StartId, int pSampleLen) {
	tADF NewADF;
	int id = StartId;

	time_t starttime = time(NULL);

	int NotChosenPVCount = pSampleLen;
	int* NotChosenPV = (int*)malloc(pSampleLen*sizeof(int));	// Not yet chosen PastValues
	for (int i = 0; i<pSampleLen; i++)	NotChosenPV[i] = i;		// Initialized linearly with values from 0 to SampleLen-1

	for (int l = 0; l<GAParms->Levels; l++){
		for (int h = 0; h<pow((double)2, l); h++){
			NewADF.level = l;
			if (l == (GAParms->Levels - 1)) {
				// Lowest level ADFs must be values. 
				NewADF.opid = 0;
				NewADF.child1 = -1;
				NewADF.child2 = -1;
				if (id*GAParms->ADF_Leaf_FixedValues_Ratio == floor(id*GAParms->ADF_Leaf_FixedValues_Ratio)) {
					// Fixed value
					NewADF.valueType = ADF_VALUE_SCALAR;
					NewADF.valueid = (int)MyRndInt(0, FixedValuesCount);
					NewADF.value = FixedValue[NewADF.valueid];	// Because Fixed Values are not loaded with Past or Test Data...
				}
				else {
					// DataPoint
					NewADF.valueType = ADF_VALUE_DATA;
					NewADF.valueid = PickADFValue(GAParms, pSampleLen);
				}
			}
			else if (l == 0) {
				// Root ADF must be a Function. 
				NewADF.opid = (int)MyRndInt(1, OperationsCount);
				NewADF.valueid = -1;
				NewADF.valueType = 0;
				NewADF.value = 0;
				NewADF.child1 = StartId + 0 + (int)pow((double)2, l);
				NewADF.child2 = StartId + 1 + (int)pow((double)2, l);
			}
			else {
				// The rest are governed by ADF_FIXEDVALUES_RATIO and ADF_DATAPOINTS_RATIO
				if (id*GAParms->ADF_Tree_FixedValues_Ratio == floor(id*GAParms->ADF_Tree_FixedValues_Ratio)) {
					// Fixed value
					NewADF.opid = 0;
					NewADF.valueType = ADF_VALUE_SCALAR;
					NewADF.valueid = MyRndInt(1, FixedValuesCount);
					NewADF.value = FixedValue[NewADF.valueid];
					NewADF.child1 = -1;
					NewADF.child2 = -1;
				}
				else if (id*GAParms->ADF_Tree_DataPoints_Ratio == floor(id*GAParms->ADF_Tree_DataPoints_Ratio)) {
					// Data Point value
					NewADF.opid = 0;
					NewADF.valueid = PickADFValue(GAParms, pSampleLen);
					NewADF.valueType = ADF_VALUE_DATA;
					NewADF.value = 0;
					NewADF.child1 = -1;
					NewADF.child2 = -1;
				}
				else {
					// Function value
					NewADF.opid = MyRndInt(1, OperationsCount);
					NewADF.valueid = -1;
					NewADF.value = 0;
					NewADF.valueType = 0;
					NewADF.child1 = id + (int)pow((double)2, l) + h;
					NewADF.child2 = id + (int)pow((double)2, l) + h + 1;
				}
			}
			//printf("ADF[%d] .level=%d .opid=%d .parent=%d .child1=%d .child2=%d .valueid=%d\n", id, l, NewADF.opid, NewADF.parent, NewADF.child1, NewADF.child2, NewADF.valueid);
			NewADF.parent = FindADFParent(GAParms, id);
			ADF[id] = NewADF;		//Struct version
			id++;
		}
	}
	free(NotChosenPV);
	//LogWrite(pDebugParms, "InitADF\t%f\n", 1, difftime(time(NULL), starttime));
	return 0;
}

void PrintADF(tChromosome* Chromosome, tADF* ADF, int ADFIdx, FILE* cFile){
	// Recursive ADF print. File must be already open
	if (ADFIdx<0) return;
	//fprintf(cFile, "%d, \t\t%d, \t\t%d, \t\t%d, \t\t%d, \t\t%f, \t\t%d, \t\t%d, \t\t%d, \t\t%d\n",ADFIdx, ADF[ADFIdx].level, ADF[ADFIdx].opid, ADF[ADFIdx].valueType, ADF[ADFIdx].valueid, ADF[ADFIdx].value, ADF[ADFIdx].ChromosomeId, ADF[ADFIdx].parent, ADF[ADFIdx].child1, ADF[ADFIdx].child2);
	fprintf(cFile, "%d, %d, %d, %d, %d, %f, %d, %d, %d, %d\n", ADFIdx, ADF[ADFIdx].level, ADF[ADFIdx].opid, ADF[ADFIdx].valueType, ADF[ADFIdx].valueid, ADF[ADFIdx].value, ADF[ADFIdx].ChromosomeId, ADF[ADFIdx].parent, ADF[ADFIdx].child1, ADF[ADFIdx].child2);
	PrintADF(Chromosome, ADF, ADF[ADFIdx].child1, cFile);
	PrintADF(Chromosome, ADF, ADF[ADFIdx].child2, cFile);
	return;
}

void SaveChromosome(tDebugInfo* pDebugParms, GA_Parms* GAParms, tChromosome* Chromosome, tADF* ADF, int gen, int cid){
	//time_t starttime = time(NULL);
	char* ChrFileNameOnly = (char*)malloc(200);
	char* ChrFileName = (char*)malloc(300);
	sprintf(ChrFileNameOnly, "/Chr_p%d_t%d_g%d_c%d.csv", GetCurrentProcessId(), GetCurrentThreadId(), gen, cid);
	ChrFileName = strcpy(ChrFileName, GAParms->BestChrPath); ChrFileName = strcat(ChrFileName, ChrFileNameOnly);

	FILE* chrFile;
	errno_t err = -1;

	err = fopen_s(&chrFile, ChrFileName, "w");
	if (err == 0){
		fprintf(chrFile, "Fitness: %f\n", Chromosome[cid].Fitness);
		fprintf(chrFile, "ADFId, Level, OpId, ValueType, ValueId, Value, ChromosomeId, Parent, Child1, Child2\n");
		PrintADF(Chromosome, ADF, Chromosome[cid].RootADFid, chrFile);
		//LogWrite(pDebugLevel, pLogFile, "%s SaveChromosome: Thread %d Closing Chromosome file %s\n", 3, timestamp(), GetCurrentThreadId(), ChrFileName);
		fclose(chrFile);
	}
	else{
		LogWrite(pDebugParms, LOG_ERROR, "%s SaveChromosome: Thread %d raised an ERROR while trying to write Chromosome file %s. err=%d\n", 3, timestamp(), GetCurrentThreadId(), ChrFileName, err);
	}

	free(ChrFileName); free(ChrFileNameOnly);

}

int FPS(GA_Parms* GAParms, tChromosome* Chromosome) {	// Fitness Proportionate Selection (Roulette Selection)
	//time_t starttime = time(NULL);
	int i;
	double r;
	double FitSum = 0;	// Sum of the fitness of all the individuals
	double FitMin = 100000000000000; double FitMax = 0;
	double* rdist = (double*)malloc(GAParms->PopulationSize*sizeof(double));
	double rdistMin = 100000000000;
	int retc;
	//-- 1. Find FitMin, FitMax, FitSum
	for (i = 0; i<GAParms->PopulationSize; i++){
		//-- Check if Fitness>0 to avoid non-initialized fitness in chromosomes
		if (Chromosome[i].Fitness>0)								{ FitSum = Chromosome[i].Fitness + FitSum; }
		if (Chromosome[i].Fitness>0 && Chromosome[i].Fitness<FitMin){ FitMin = Chromosome[i].Fitness; }
		if (Chromosome[i].Fitness>FitMax)							{ FitMax = Chromosome[i].Fitness; }
	}
	//-- 2. Pick a random position between FitMin and FitMax
	r = FitMin + MyRandom01() * (FitMax - FitMin);

	//-- 3. Select the Chromosome sitting in that position
	for (i = 0; i<GAParms->PopulationSize; i++){
		//-- 3.1 Calculate distance between each chromosome fitness and r
		rdist[i] = (Chromosome[i].Fitness>0) ? abs(r - Chromosome[i].Fitness) : 100000000000000;
		//-- 3.2 Find min(rdist)
		if (rdist[i]<rdistMin){
			rdistMin = rdist[i];
			retc = i;
		}
	}

	free(rdist);
	//LogWrite(gDebugLevel, gLogFile, "FPS\t%f\n", 1, difftime(time(NULL), starttime));
	return retc;
}

void LoadDataToADF(tADF* ADF, int ADFId, int pSampleLen, double* pSampleData){
	//time_t starttime = time(NULL);
	if (ADFId == -1) return;

	if (ADF[ADFId].valueType == ADF_VALUE_DATA)   ADF[ADFId].value = pSampleData[ADF[ADFId].valueid];
	if (ADF[ADFId].valueType == ADF_VALUE_SCALAR)	ADF[ADFId].value = FixedValue[ADF[ADFId].valueid];
	LoadDataToADF(ADF, ADF[ADFId].child1, pSampleLen, pSampleData);
	LoadDataToADF(ADF, ADF[ADFId].child2, pSampleLen, pSampleData);
}

void CalcChrFitness(GA_Parms* GAParms, tADF* ADF, tChromosome* Chromosome, int cid, int pSampleCount, int pSampleLen, double** pSampleData, double** pSampleTarget){
	double CFit;
	double vCVal;
	double SqErr_Tot = 0;
	int sample;
	//HANDLE ADFMutex=CreateMutex(NULL, FALSE, NULL);
	//time_t starttime = time(NULL);

	for (sample = 0; sample<pSampleCount; sample++){
		// For each sample, Load Data to ADF, then Eval it.
		//WaitForSingleObject(ADFMutex, INFINITE);
		LoadDataToADF(ADF, Chromosome[cid].RootADFid, pSampleLen, pSampleData[sample]);
		//ReleaseMutex(ADFMutex);
		// After ALL ADFs have ben set values, Eval Root ADF for chromosome
		vCVal = EvalADF(ADF, Chromosome[cid].RootADFid);
		if (!isnormal(vCVal)) vCVal = 0;
		// Calc Squared Error, and sum it up to allow for averaging out of the loop
		switch (GAParms->FitnessSkewingFactor){
		case 0:
			SqErr_Tot = SqErr_Tot + pow((vCVal - pSampleTarget[sample][0]), 2);			// Original, every sample "weighs" the same on fitness calculation
			break;
		case 1:
			SqErr_Tot = SqErr_Tot + sample*pow((vCVal - pSampleTarget[sample][0]), 2);	// Updated,  error is (linearly) amplified towards the end of the Sample
			break;
		case 2:
			SqErr_Tot = SqErr_Tot + pow((sample*(vCVal - pSampleTarget[sample][0])), 2);	// Updated,  error is (squarely) amplified towards the end of the Sample
			break;
		default:
			SqErr_Tot = SqErr_Tot + pow((vCVal - pSampleTarget[sample][0]), 2);			// defaults to Original, every sample "weighs" the same on fitness calculation
			break;
		}
	}

	//printf("\n");
	// Calc Fitness from Total Absolute Error (1/MSE)
	if (SqErr_Tot == 0){
		CFit = GAParms->TargetFitness;		// To Avoid dividing by zero
	}
	else {
		CFit = pSampleCount / SqErr_Tot;	// 1/MSE
	}
	Chromosome[cid].Cval = vCVal;
	Chromosome[cid].Fitness = CFit;
	//printf("[CalcChrFitness] Chromosome[%d].Fitness=%f\n", cid, Chromosome[cid].Fitness);
	//LogWrite(gDebugLevel, gLogFile, "CalcChrFitness\t%f\n", 1, difftime(time(NULL), starttime));

}

int COWalkDown(GA_Parms* GAParms, tADF* ADF, int RootADFId){	// CrossOver Walk-Down
	//time_t starttime = time(NULL);
	int ADFId = RootADFId;
	int r = MyRndInt(1, GAParms->Levels - 1);
	for (int i = 0; i<r; i++){
		// At each step, choose randomly between child1 and child2
		if (rand()<0.5){
			//printf("[COWalkDown]: rand()<0.5 ; ADFId=%d ; ADF[ADFId].child1=%d\n", ADFId, ADF[ADFId].child1);
			if (ADF[ADFId].child1 == -1) return ADFId; // returns the last ADF encountered before -1
			ADFId = ADF[ADFId].child1;
		}
		else {
			//printf("[COWalkDown]: rand()>0.5 ; ADFId=%d ; ADF[ADFId].child2=%d\n", ADFId, ADF[ADFId].child2);
			if (ADF[ADFId].child2 == -1) return ADFId;	// returns the last ADF encountered before -1
			ADFId = ADF[ADFId].child2;
		}
	}
	//LogWrite(gDebugLevel, gLogFile, "COWalkDown\t%f\n", 1, difftime(time(NULL), starttime));
	return ADFId;
}

void ResetADFCid(tADF* ADF, int ADFId) {
	// Recursive Copy ChromosomeID from ADFId to child1, child2
	if (ADF[ADFId].child1 == -1 || ADF[ADFId].child2 == -1) return;
	ADF[ADF[ADFId].child1].ChromosomeId = ADF[ADFId].ChromosomeId;
	ADF[ADF[ADFId].child2].ChromosomeId = ADF[ADFId].ChromosomeId;
	ResetADFCid(ADF, ADF[ADFId].child1);
	ResetADFCid(ADF, ADF[ADFId].child2);
	return;
}

void CrossOver(GA_Parms* GAParms, tADF* ADF, tChromosome* Chromosome, int cid1, int cid2) {
	//time_t starttime = time(NULL);
	int r1 = 0; int r2 = 0;
	int ADF1Id;		int ADF2Id;
	int ADF1opid;	int ADF2opid;
	int kaz = 0;

	// V3
	// Can crossover Functional and Terminal ADFs, but need to prune
	// ...

	// V2.0
	// Start from Root ADF, then go down the tree <r> steps (min 1)
	ADF1Id = COWalkDown(GAParms, ADF, Chromosome[cid1].RootADFid);
	// Where did I land? (Function/Terminal)?
	ADF1opid = ADF[ADF1Id].opid;
	// Repeat for cid2, and make sure to pick an ADF of the same type
	do {
		ADF2Id = COWalkDown(GAParms, ADF, Chromosome[cid2].RootADFid);
		ADF2opid = ADF[ADF2Id].opid;
	} while ((ADF1opid>0 && ADF2opid == 0) || (ADF1opid == 0 && ADF2opid>0));

	// Now swap ADF1Id and ADF2Id
	if (ADF[ADF1Id].child1 == -1 || ADF[ADF2Id].child1 == -1 || ADF[ADF1Id].child2 == -1 || ADF[ADF2Id].child2 == -1){
		kaz = -1;
	}
	if (ADF1Id == ADF[ADF[ADF1Id].parent].child1 && ADF2Id == ADF[ADF[ADF2Id].parent].child1) {
		// Swap child1 on cid1 with child1 on cid2
		std::swap(ADF[ADF1Id].child1, ADF[ADF2Id].child1); //if(gDebug==1) printf ("[CrossOver] Swap child1 on cid1 with child1 on cid2\n");
		// If both of the children just swapped are -1 (that is, both ADF1 and ADF2 are terminals), then DO NOTHING
		if (ADF[ADF1Id].child1 == -1 && ADF[ADF2Id].child1 == -1) kaz = 1;
		// If one of the two children just swapped is -1 (that is, if ADF1 or ADF2 are terminals),  then only set parentid for the other one
		else if (ADF[ADF1Id].child1 == -1 && ADF[ADF2Id].child1 != -1) ADF[ADF[ADF2Id].child1].parent = ADF2Id;
		else if (ADF[ADF2Id].child1 == -1 && ADF[ADF1Id].child1 != -1) ADF[ADF[ADF1Id].child1].parent = ADF1Id;
		// Else, Swap Parents between child1 on cid1 and child1 on cid2
		else	std::swap(ADF[ADF[ADF1Id].child1].parent, ADF[ADF[ADF2Id].child1].parent);
		kaz = 1;
	}
	if (ADF1Id == ADF[ADF[ADF1Id].parent].child1 && ADF2Id == ADF[ADF[ADF2Id].parent].child2) {
		// Swap child1 on cid1 with child2 on cid2
		std::swap(ADF[ADF1Id].child1, ADF[ADF2Id].child2); //if(gDebug==1) printf ("[CrossOver] Swap child1 on cid1 with child2 on cid2\n");
		// If both of the children just swapped are -1 (that is, both ADF1 and ADF2 are terminals), then DO NOTHING
		if (ADF[ADF1Id].child1 == -1 && ADF[ADF2Id].child2 == -1) kaz = 1;
		// If any of the two children just swapped is -1 (that is, if ADF1 or ADF2 are terminals) then only set parentid for the other one
		else if (ADF[ADF1Id].child1 == -1 && ADF[ADF2Id].child2 != -1) ADF[ADF[ADF2Id].child2].parent = ADF2Id;
		else if (ADF[ADF2Id].child2 == -1 && ADF[ADF1Id].child1 != -1) ADF[ADF[ADF1Id].child1].parent = ADF1Id;
		// Else, Swap Parents between child1 on cid1 and child2 on cid2
		else    std::swap(ADF[ADF[ADF1Id].child1].parent, ADF[ADF[ADF2Id].child2].parent);
		kaz = 1;
	}
	if (ADF1Id == ADF[ADF[ADF1Id].parent].child2 && ADF2Id == ADF[ADF[ADF2Id].parent].child1) {
		// Swap child2 on cid1 with child1 on cid2
		std::swap(ADF[ADF1Id].child2, ADF[ADF2Id].child1); //if(gDebug==1) printf ("[CrossOver] Swap child2 on cid1 with child1 on cid2\n");
		// If both of the children just swapped are -1 (that is, both ADF1 and ADF2 are terminals), then DO NOTHING
		if (ADF[ADF1Id].child2 == -1 && ADF[ADF2Id].child1 == -1) kaz = 1;
		// If any of the two children just swapped is -1 (that is, if ADF1 or ADF2 are terminals) then only set parentid for the other one
		else if (ADF[ADF1Id].child2 == -1 && ADF[ADF2Id].child1 != -1) ADF[ADF[ADF2Id].child1].parent = ADF2Id;
		else if (ADF[ADF2Id].child1 == -1 && ADF[ADF1Id].child2 != -1) ADF[ADF[ADF1Id].child2].parent = ADF1Id;
		// Else, Swap Parents between child2 on cid1 and child1 on cid2
		else     std::swap(ADF[ADF[ADF1Id].child2].parent, ADF[ADF[ADF2Id].child1].parent);
		kaz = 1;
	}
	if (ADF1Id == ADF[ADF[ADF1Id].parent].child2 && ADF2Id == ADF[ADF[ADF2Id].parent].child2) {
		// Swap child2 on cid1 with child2 on cid2
		std::swap(ADF[ADF1Id].child2, ADF[ADF2Id].child2); //if(gDebug==1) printf ("[CrossOver] Swap child2 on cid1 with child2 on cid2\n");
		// If both of the children just swapped are -1 (that is, both ADF1 and ADF2 are terminals), then DO NOTHING
		if (ADF[ADF1Id].child2 == -1 && ADF[ADF2Id].child2 == -1) kaz = 1;
		// If any of the two children just swapped is -1 (that is, if ADF1 or ADF2 are terminals) then only set parentid for the other one
		else if (ADF[ADF1Id].child2 == -1 && ADF[ADF2Id].child2 != -1) ADF[ADF[ADF2Id].child2].parent = ADF2Id;
		else if (ADF[ADF2Id].child2 == -1 && ADF[ADF1Id].child2 != -1) ADF[ADF[ADF1Id].child2].parent = ADF1Id;
		// Else, Swap Parents between child2 on cid1 and child2 on cid2
		else     std::swap(ADF[ADF[ADF1Id].child2].parent, ADF[ADF[ADF2Id].child2].parent);
		kaz = 1;
	}
	// If one of the ADFs ends up with (at least one) child <> -1 , then it can not have opid=0
	//if ( (ADF[ADF1Id].child1==-1 || ADF[ADF1Id].child1==-1) && ADF[ADF1Id].opid==0) ADF[ADF1Id].opid=MyRandomInt(1,

	// When finished, make sure ChromosomeId is reset for all the ADFs 
	ResetADFCid(ADF, Chromosome[cid2].RootADFid);	// on cid1
	ResetADFCid(ADF, Chromosome[cid1].RootADFid);	// and on cid2
}

void Mutate(GA_Parms* GAParms, tADF* ADF, int cid, int pSampleLen) {
	//time_t starttime = time(NULL);
	int prevval;
	// Randomly pick one ADF (BELONGING TO cid !!)
	//	int ADFIdx1=cid*(int)pow(2,Levels);
	//	int ADFIdx2=(cid+1)*(int)pow(2,Levels)-1;
	//	for (int ADFIdx=ADFIdx1; ADFIdx<=ADFIdx2; ADFIdx++){
	for (int ADFIdx = 0; ADFIdx<(GAParms->PopulationSize*(pow((double)2, GAParms->Levels) - 1)); ADFIdx++){
		if (GAParms->MutationProbability > MyRandom01() && ADF[ADFIdx].ChromosomeId == cid){
			if (ADF[ADFIdx].opid>0){
				// This is a Function node (i.e. operator)
				prevval = ADF[ADFIdx].opid;
				ADF[ADFIdx].opid = (int)MyRndInt(1, OperationsCount);
				ADF[ADFIdx].value = 0;
			}
			else {
				// This is a Terminal node (i.e. value)
				prevval = ADF[ADFIdx].valueid;
				ADF[ADFIdx].opid = 0;
				ADF[ADFIdx].valueid = (int)MyRndInt(0, pSampleLen - 1);
			}
		}
	}
	//LogWrite(gDebugLevel, gLogFile, "Mutate\t%f\n", 1, difftime(time(NULL), starttime));
}

int InitChromosomes(tDebugInfo* pDebugParms, GA_Parms* GAParms, tADF* ADF, tChromosome* Chromosome, int GenType, int pSampleLen){
	// Init Chromosomes (ADF trees)
	//time_t starttime = time(NULL);
	for (int c = 0; c<GAParms->PopulationSize; c++){
		// Set RootADFid for last built chromosome
		Chromosome[c].RootADFid = c*((int)pow((double)2, GAParms->Levels) - 1);
		// Build new tree;
		if (InitADFs(pDebugParms, GAParms, ADF, c*(((int)pow((double)2, GAParms->Levels) - 1)), pSampleLen) <0) return -1;
		// Associate ADF from last built tree to current chromosome
		int ADF1 = c*((int)pow((double)2, GAParms->Levels) - 1);
		int ADF2 = ADF1 + (int)pow((double)2, GAParms->Levels) - 2;
		for (int ADFid = ADF1; ADFid <= ADF2; ADFid++)  ADF[ADFid].ChromosomeId = c;
	}
	return 0;
	//LogWrite(gDebugLevel, gLogFile, "InitChromosomes\t%f\n", 1, difftime(time(NULL), starttime));
}

void CopyADF(tADF* FromADF, int ADFid, tADF* ToADF){
	if (FromADF[ADFid].child1 != -1) CopyADF(FromADF, FromADF[ADFid].child1, ToADF);
	if (FromADF[ADFid].child2 != -1) CopyADF(FromADF, FromADF[ADFid].child2, ToADF);
	ToADF[ADFid] = FromADF[ADFid];
}

void CopyChromosomeAndADFs(tADF* FromADF, tChromosome* FromChromosome, int cid, tADF* ToADF, tChromosome* ToChromosome){
	//-- 1 First, copy ADF recursively, setting cid to ChildCid
	CopyADF(FromADF, FromChromosome[cid].RootADFid, ToADF);
	//-- 2. Then, copy Chromosome
	ToChromosome[cid] = FromChromosome[cid];
}

int LoadChromosome(GA_Parms* GAParms, tADF* ADF, tChromosome* Chromosome, int gen, int cid){
	int GenType = CHILD;
	//time_t starttime = time(NULL);
	char* ChrFileNameOnly = (char*)malloc(200);
	char* ChrFileName = (char*)malloc(300);
	sprintf(ChrFileNameOnly, "/Chr_p%d_t%d_g%d_c%d.csv", GetCurrentProcessId(), GetCurrentThreadId(), gen, cid);
	ChrFileName = strcpy(ChrFileName, GAParms->BestChrPath); ChrFileName = strcat(ChrFileName, ChrFileNameOnly);

	FILE* chrFile;
	char* vLine = (char*)malloc(100);
	float vFitness;
	bool FirstADF = true;
	int vADFId; int vLevel; int vOpId; int vValueType; int vValueId; double vValue; int vChromosomeId; int vParent; int vChild1; int vChild2;

	chrFile = fopen(ChrFileName, "r");	if (chrFile == NULL) return -1;

	fscanf(chrFile, "Fitness: %f\n", &vFitness);
	fgets(vLine, 100, chrFile);	// Reads Header Line
	//while ( fscanf(chrFile, "%d, \t\t%d, \t\t%d, \t\t%d, \t\t%d, \t\t%f, \t\t%d, \t\t%d, \t\t%d, \t\t%d", &vADFId, &vLevel, &vOpId, &vValueType, &vValueId, &vValue, &vChromosomeId, &vParent, &vChild1, &vChild2) != EOF){
	while (fscanf(chrFile, "%d, %d, %d, %d, %d, %lf, %d, %d, %d, %d", &vADFId, &vLevel, &vOpId, &vValueType, &vValueId, &vValue, &vChromosomeId, &vParent, &vChild1, &vChild2) != EOF){
		// The first ADF in this loop must be assigned as RootADFId to Chromosome[0]
		if (FirstADF){
			Chromosome[0].RootADFid = vADFId;
			FirstADF = false;
		}
		// Reset all properties for each ADFId to the value each had when it was saved
		ADF[vADFId].level = vLevel;
		ADF[vADFId].opid = vOpId;
		ADF[vADFId].valueType = vValueType;
		ADF[vADFId].valueid = vValueId;
		//ADF[vADFId].value=vValue;	// Don't need this; it will be assigned in LoadDataToADF()
		//ADF[vADFId].ChromosomeId=vChromosomeId;
		ADF[vADFId].ChromosomeId = 0;	// So we avoid loading ADFs that belonged to cid in generations after the best )
		ADF[vADFId].parent = vParent;
		ADF[vADFId].child1 = vChild1;
		ADF[vADFId].child2 = vChild2;
	}

	fclose(chrFile);
	free(vLine);
	free(ChrFileName); free(ChrFileNameOnly);
	//LogWrite(gDebugLevel, gLogFile, "LoadChromosome\t%f\n", 1, difftime(time(NULL), starttime));
	return 0;
}

int GATrain(tDebugInfo* pDebugParms, GA_Parms* pGAParams, GA_Logs* pGALogs, int pNetId, int pTestId, int pDatasetId, int pSampleCount, int pSampleLen, double** pSampleData, double** pSampleTarget, tChromosome* Chromosome, tADF* ADF, tChromosome* tempChr, tADF* tempADF){
	int g, c;
	pGAParams->BestFitness=0;
	int ParentCid1; int ParentCid2;
	double SumFitness = 0;
	DWORD pid = GetCurrentProcessId();
	DWORD tid = GetCurrentThreadId();

	//-- 3. Generations Loop: Calc Fitness for each Chromosomes, and exit training if any one has reached Target Fitness
	for (g = 0; g<pGAParams->MaxGenerations; g++)	{
		SumFitness = 0;
		if (pDebugParms->DebugLevel>0) SaveMSEData(pGALogs, pNetId, pid, tid, pDatasetId, pTestId, g, (pGAParams->BestFitness == 0)?0:(1/pGAParams->BestFitness), 0);
		for (c = 0; c<pGAParams->PopulationSize; c++){
			CalcChrFitness(pGAParams, ADF, Chromosome, c, pSampleCount, pSampleLen, pSampleData, pSampleTarget);
			SumFitness = SumFitness + Chromosome[c].Fitness;
			if (Chromosome[c].Fitness > pGAParams->BestFitness){
				pGAParams->BestGen = g; pGAParams->BestCid = c; pGAParams->BestFitness = Chromosome[c].Fitness;
				SaveChromosome(pDebugParms, pGAParams, Chromosome, ADF, g, c);
			}
			if (pGAParams->BestFitness > pGAParams->TargetFitness) break;
		}
		if (pGAParams->BestFitness>pGAParams->TargetFitness) break;
		gotoxy(0, 1 + pDatasetId); printf("\rProcess %d; Thread %d ; Generation %d/%d ; Best Fitness: %12.6f (Chromosome %d from Generation %d) ; Average Fitness=%f", pid, tid, g, pGAParams->MaxGenerations, pGAParams->BestFitness, pGAParams->BestCid, pGAParams->BestGen, SumFitness / pGAParams->PopulationSize);
		//== TODO: fprintf(FitnessFile, "%d, %d, %d, %f, %d, %d, %f\n", PopulationSize, run, g, pGAParams->BestFitness[run], pGAParams->BestCid, pGAParams->BestGen, SumFitness / PopulationSize);
		// === 3.1. Evolve to next generation
		//-- Here, Children Population (Q) is empty.
		// Repeat the following until the next generation is filled
		for (c = 0; c < (pGAParams->PopulationSize / 2); c++) {

			// === 3.1.1 === First, select two parents from the current generation
			ParentCid1 = 0; ParentCid2 = 0; int Rcount = 0;
			//while (ParentCid1 == ParentCid2 && !HasBeenChosen(c, ParentCid1) && !HasBeenChosen(c, ParentCid2) && Rcount <= RouletteMaxTries){  // To avoid picking the same chromosome twice
			while (ParentCid1 == ParentCid2 && Rcount <= pGAParams->RouletteMaxTries){
				//while (ParentCid1 == ParentCid2){
				ParentCid1 = FPS(pGAParams, Chromosome);
				ParentCid2 = FPS(pGAParams, Chromosome);
				Rcount++;
			}
			if (ParentCid1 == ParentCid2){
				LogWrite(pDebugParms, LOG_ERROR, "\n === ERROR === FPS could not select two different Chromosomes. Quitting...\n", 0);
				return -1;
			}
			// === 3.1.2 === Make a copy of the selected Parents into temps
			CopyChromosomeAndADFs(ADF, Chromosome, ParentCid1, tempADF, tempChr);
			CopyChromosomeAndADFs(ADF, Chromosome, ParentCid2, tempADF, tempChr);

			// === 3.1.3 === Then, cross the two temps over
			CrossOver(pGAParams, tempADF, tempChr, ParentCid1, ParentCid2 );

			// === 3.1.4 === Then, mutate the two children
			Mutate(pGAParams, tempADF, ParentCid1, pSampleLen);
			Mutate(pGAParams, tempADF, ParentCid2, pSampleLen);

			// === 3.1.5 === Then, copy temp Chromosomes into Parents pool
			CopyChromosomeAndADFs(tempADF, tempChr, ParentCid1, ADF, Chromosome);
			CopyChromosomeAndADFs(tempADF, tempChr, ParentCid2, ADF, Chromosome);
		}
		if (pGAParams->BestFitness > pGAParams->TargetFitness) break;
	}
	pGAParams->BestGen = pGAParams->BestGen;
	pGAParams->BestCid = pGAParams->BestCid;
	LogWrite(pDebugParms, LOG_INFO, "\n%s DoGATraining completed. pBestGen=%d , pBestCid=%d, pBestFitness=%f\n", 3, timestamp(), pGAParams->BestGen, pGAParams->BestCid, pGAParams->BestFitness);

	return 0;
}

int GARun(tDebugInfo* pDebugParms, GA_Parms* pGAParams, tADF* ADF, tChromosome* Chromosome, int pBestGen, int pBestCid, int pRunLen, double* pRunData, int pPredictionLen, double* pForecast, double pScaleM, double pScaleP) {
	//-- Eval Chromosome to get Next Value Prediction; need to unscale it before returning it
	// 1. Load Best Chromosome from Chromosome File
	if (LoadChromosome(pGAParams, ADF, Chromosome, pBestGen, pBestCid) <0) {
		LogWrite(pDebugParms, LOG_ERROR, "%s GAEngine: DoGARun: LoadChromosome failed. Exiting...\n", 1, timestamp());
		return -1;
	}
	for (int i = 0; i <pPredictionLen; i++){
		LoadDataToADF(ADF, Chromosome[pBestCid].RootADFid, pRunLen, pRunData);
		pForecast[i] = EvalADF(ADF, Chromosome[0].RootADFid);
		//pForecast[i] = DataUnscale(pForecast[i], pScaleM, pScaleP);
	}
	return 0;
}

int SaveGA(GA_Parms* pGAParms, int pNetId, int pid, int tid, int pDatasetId, int pTestId, tChromosome* pChromosome, tADF* pADF){
	return 0;
}

void TrainAndSave_GA(tTrainParams* parms){
	int pid = GetCurrentProcessId();
	int tid = GetCurrentThreadId();
	//-- Init Chromosomes and ADFs
	InitChromosomes(parms->DebugParms, parms->GAParams, parms->ADF, parms->Chromosome, PARENT, parms->SampleLen);
	//-- Training
	GATrain(parms->DebugParms, parms->GAParams, parms->GALogs, parms->NetId, parms->TestId, parms->DatasetId, parms->SampleCount, parms->SampleLen, parms->SampleData, parms->SampleTarget, parms->Chromosome, parms->ADF, parms->tempChr, parms->tempADF);
	//-- Save
	SaveGA(parms->GAParams, parms->NetId, pid, tid, parms->DatasetId, parms->TestId, parms->Chromosome, parms->ADF);

/*	//-- Run from Best Gen/Cid

	//-- Get the last sample presented to the GA
	//...
	//-- Load Best Chromosome
	LoadChromosome(parms->GAParams, parms->ADF, parms->Chromosome, parms->GAParams->BestGen, parms->GAParams->BestCid);
	//-- Load the sample to the chromosomes
	LoadDataToADF(parms->ADF, parms->Chromosome[parms->GAParams->BestCid].RootADFid, parms->GAParams->InputCount, parms->SampleData[parms->SampleCount - 1]);
	//-- Forecast from EvalADF
	parms->Forecast[0] = EvalADF(parms->ADF, parms->Chromosome[parms->GAParams->BestCid].RootADFid);
	//GARun(parms->DebugParms, parms->GAParams, parms->ADF, parms->Chromosome, (*parms->GAParams->BestGen), (*parms->GAParams->BestCid), vRunLen, vRunData, parms->PredictionLen, parms->Forecast, parms->ScaleM, parms->ScaleP);
*/
}

__declspec(dllexport) int Train_GA(tDebugInfo* pDebugParms, GA_Parms* pGAParams, tDataShape* pInputData, int pTestId, int pSampleCount, double*** pSampleData, double*** pTargetData, double*** pSampleDataV, double*** pTargetDataV){
	int d, i;
	int pid = GetCurrentProcessId();

	// Read GAEngine.ini parameters
	//if (ReadGAParameters()<0) return -1;

	// srand() and mallocs
	srand((unsigned int)time(NULL));
	HANDLE* HTrain = (HANDLE*)malloc(pInputData->DatasetsCount*sizeof(HANDLE));
	tTrainParams* tp = (tTrainParams*)malloc(pInputData->DatasetsCount*sizeof(tTrainParams));
	DWORD* kaz = (DWORD*)malloc(pInputData->DatasetsCount*sizeof(DWORD));
	LPDWORD* tid = (LPDWORD*)malloc(pInputData->DatasetsCount*sizeof(LPDWORD)); for (i = 0; i < pInputData->DatasetsCount; i++) tid[i] = &kaz[i];

	tChromosome** Chromosome = (tChromosome**)malloc(pInputData->DatasetsCount*sizeof(tChromosome*));
	tADF** ADF = (tADF**)malloc(pInputData->DatasetsCount*sizeof(tADF*));
	tChromosome** tempChr = (tChromosome**)malloc(pInputData->DatasetsCount*sizeof(tChromosome*));
	tADF** tempADF = (tADF**)malloc(pInputData->DatasetsCount*sizeof(tADF*));

	//--

	//-- 0.1 Run File to hold the Run Results
/*	char RunFileNameOnly[MAX_PATH];
	char RunFileName[MAX_PATH];
	sprintf(RunFileNameOnly, "/Run_p%d_t%d.csv", GetCurrentProcessId(), GetCurrentThreadId());
	strcpy(RunFileName, BestChrPath); strcat(RunFileName, RunFileNameOnly);
	FILE* RunFile;
	errno_t err = -1;
	err = fopen_s(&RunFile, RunFileName, "w");
	strcpy(oRunFileName, RunFileName);
	FILE* FitnessFile = fopen("C:/temp/Fitness.csv", "w");
	fprintf(FitnessFile, "PopSize, Run, Generation, BestFitness, BestChr, BestGen, AvgFitness\n");
*/
	//-- When should training/Run stop?
	double vBestFitness = 0;
	double wiggleRoom = 0;
	//--

	for (d = 0; d < pInputData->DatasetsCount; d++){
		Chromosome[d] = (tChromosome*)malloc(pGAParams->PopulationSize*sizeof(tChromosome));
		ADF[d] = (tADF*)malloc(pGAParams->PopulationSize*(int)pow((double)2, pGAParams->Levels)*sizeof(tADF));
		tempChr[d] = (tChromosome*)malloc(pGAParams->PopulationSize*sizeof(tChromosome));
		tempADF[d] = (tADF*)malloc(pGAParams->PopulationSize*(int)pow((double)2, pGAParams->Levels)*sizeof(tADF));
	}
	//-- Do the following for each dataset
	for (d = 0; d < pInputData->DatasetsCount; d++){
		//-- prepare Training parameters
		tp[d].NetId = 0;
		tp[d].GAParams = pGAParams; tp[d].DebugParms = pDebugParms; tp[d].TestId = pTestId; tp[d].DatasetId = d;
		tp[d].SampleCount = pSampleCount; tp[d].SampleLen = pInputData->SampleLen; tp[d].SampleData = pSampleData[d]; tp[d].SampleTarget = pTargetData[d]; 
		tp[d].ADF = ADF[d]; tp[d].Chromosome = Chromosome[d]; tp[d].tempADF = tempADF[d]; tp[d].tempChr = tempChr[d];
		//-- Train and Save GA
		HTrain[d] = CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE)TrainAndSave_GA, &tp[d], 0, tid[d]);
		//-- Store Engine Handler
		tp[d].TrainInfo[d].DatasetId = d; 
		tp[d].TrainInfo[d].ProcessId = pid;
		tp[d].TrainInfo[d].ThreadId = (*tid[d]); 
		tp[d].TrainInfo[d].TestId = pTestId;
	}
	WaitForMultipleObjects(pInputData->DatasetsCount, HTrain, TRUE, INFINITE);
	//-- 0.2 Main ReRun Loop
	//for (run = 0; run < vReRuns; run++){
/*		run = 0;
		srand((int)time(NULL));

		//=== TRAIN

		//=== RUN 

		// 1. Load Best Chromosome from Chromosome File
		if (LoadChromosome(pGAParams, PARENT, vBestGen, vBestCid)<0) {
			LogWrite(pDebugParms, "%s GAEngine: DoGARun: LoadChromosome failed. Exiting...\n", 1, timestamp()); 
			return -1;
		}

		// 2. Prepare Array to hold Run Data (that is, only the <RunDataCount> rightmost elements of PastData
		// 2.1 Set the first half of RunTable to 0
		for (i = 0; i < RunDataCount; i++){
			for (j = 0; j < vReRuns; j++) RunTable[j][i] = 0;
		}
		for (i = 0; i<RunDataCount; i++){
			for (j = 0; j<RunDataCount; j++) RunData[j] = pHistoryData[d][i + j];
			// 3.1. Load Run Sample Data to ADF
			LoadDataToADF(PARENT, Chromosome[0].RootADFid, RunDataCount, RunData);
			// 3.2. Eval Chromosome to get Next Value Prediction
			ret = EvalADF(PARENT, Chromosome[0].RootADFid);
			RunTable[run][RunDataCount + i] = ret;
		}
		// 3. Actual Run OUT-OF-SAMPLE
		// Prepare Array to hold Run Data (that is, only the <RunDataCount> rightmost elements of PastData
		for (i = 0; i<RunDataCount; i++) RunData[i] = pHistoryData[d][pHistoryLen - RunDataCount + i];
		// To obtain each of the next prediction, shift RunData backwards, add ret as the latest value
		for (p = 0; p<pPredictionLen; p++){
			// 3.1. Load Run Sample Data to ADF
			LoadDataToADF(PARENT, Chromosome[0].RootADFid, RunDataCount, RunData);
			// 3.2. Eval Chromosome to get Next Value Prediction
			ret = EvalADF(PARENT, Chromosome[0].RootADFid);
			RunTable[run][pHistoryLen + p] = ret;
			// 3.4 Shift RunData back, adding ret as the rightmost element
			ShiftArray(SHIFT_BACKWARD, RunDataCount, RunData, ret);
		}
	}

	//=== Calc Averages , and print results
	//-- 0. Column Headers
	fprintf(RunFile, "Actual, ");
	for (i = 0; i < vReRuns; i++) fprintf(RunFile, "F=%f,", vBestFitness[i]);
	fprintf(RunFile, "Run Avg\n");
	//-- 2. Rest of the file
	for (j = 0; j < (pHistoryLen + pPredictionLen); j++){
		retsum[j] = 0;
		if (j == (pHistoryLen)) fprintf(RunFile, "\n");	// empty line between past and prediction
		if (j >= pHistoryLen){
			fprintf(RunFile, "%f,", pForecastData[d][j - pHistoryLen]);
		}
		else{
			fprintf(RunFile, "%f,", pHistoryData[d][j]);
		}
		for (i = 0; i < vReRuns; i++){
			retsum[j] += oRunTable[i][j];
			if (j>RunDataCount){
				fprintf(RunFile, "%f,", oRunTable[i][j]);
			}
			else {
				fprintf(RunFile, ",");
			}
		}
		RunTable[vReRuns][j] = retsum[j] / vReRuns;	//The last column holds the average of the previous ones
		if (j>RunDataCount)	fprintf(RunFile, "%f", oRunTable[vReRuns][j]);
		fprintf(RunFile, "\n");

		if (vBestFitness[run]>vFitnessThreshold) break;
	}
	//-- 1. Fitness values
	fprintf(RunFile, "\n");
	for (i = 0; i<vReRuns; i++) fprintf(RunFile, ",%f", vBestFitness[i]);
	fprintf(RunFile, "\n");

	fclose(RunFile); fclose(FitnessFile);

	//free(ADF);
	//free(Chromosome);
	free(retsum);
	free(vBestFitness);
	Free2DDoubleArray(vSampleData, vSampleCount, vSampleLen);
	free(vSampleTarget);
	free(RunData);
*/
	return 0;
}

//#include <vld.h>

#define _CRT_RAND_S
#include <stdlib.h>
#include <Windows.h>
#include <time.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <direct.h>

#include <MyUtils.h>

#ifndef DATE_FORMAT
#define DATE_FORMAT 
#endif

#undef EXPORT
#define EXPORT __declspec(dllexport)

//------------ Resources Usage utilities -------------------
static float CalculateCPULoad(unsigned long long idleTicks, unsigned long long totalTicks)
{
	static unsigned long long _previousTotalTicks = 0;
	static unsigned long long _previousIdleTicks = 0;

	unsigned long long totalTicksSinceLastTime = totalTicks-_previousTotalTicks;
	unsigned long long idleTicksSinceLastTime = idleTicks-_previousIdleTicks;

	float ret = 1.0f-((totalTicksSinceLastTime > 0) ? ((float)idleTicksSinceLastTime)/totalTicksSinceLastTime : 0);

	_previousTotalTicks = totalTicks;
	_previousIdleTicks = idleTicks;
	return ret;
}
static unsigned long long FileTimeToInt64(const FILETIME & ft) { return (((unsigned long long)(ft.dwHighDateTime))<<32)|((unsigned long long)ft.dwLowDateTime); }

// Returns 1.0f for "CPU fully pinned", 0.0f for "CPU idle", or somewhere in between
// You'll need to call this at regular intervals, since it measures the load between
// the previous call and the current one.  Returns -1.0 on error.
EXPORT float GetCPULoad() {
	FILETIME idleTime, kernelTime, userTime;
	return GetSystemTimes(&idleTime, &kernelTime, &userTime) ? CalculateCPULoad(FileTimeToInt64(idleTime), FileTimeToInt64(kernelTime)+FileTimeToInt64(userTime)) : -1.0f;
}
EXPORT DWORD GetMemLoad() {
	MEMORYSTATUSEX statex;
	statex.dwLength = sizeof(statex);
	GlobalMemoryStatusEx(&statex);
	return statex.dwMemoryLoad;
}
//------	Random Utilities	- Start		--------------
EXPORT int __stdcall	MyRndInt(int rmin, int rmax){
	int ret = -1;
	while (ret<0) ret= (rmin + (rand() % rmax));
	return ret;
}
EXPORT double __stdcall MyRndDbl(double min, double max){
	unsigned int number;
	int err;
	double ret;

	err = rand_s(&number);
	ret = min + (double)number / ((double)UINT_MAX + 1) * (max - min);
	return ret;
}

EXPORT double __stdcall		MyRandom01(){
	//srand ((unsigned int)time(NULL));
	return( (double) rand()/RAND_MAX );
}
//------	Random Utilities	- End		--------------

//------	Time Utilities	- Start		--------------
EXPORT int __stdcall		TimeFrameToMins(char* tf){
	if (tf=="M1"){return 1;} else if (tf=="M5"){return 5;} else if (tf=="M15"){return 15;} else if (tf=="M30"){return 30;} else if (tf=="H1"){return 60;} else if (tf=="H4"){return 240;} else if (tf=="D1"){return 1440;} else{return -1;}
}

EXPORT char* __stdcall		timestamp(){
	char* ftime;
    time_t ltime; // calendar time 
	HANDLE TimeMutex;

	TimeMutex=CreateMutex(NULL, TRUE, NULL);
	WaitForSingleObject(TimeMutex, INFINITE);
    ltime=time(NULL); // get current cal time 
    ftime=asctime(localtime(&ltime));
	ftime[strlen(ftime)-1]='\0';
	ReleaseMutex(TimeMutex);

	return (ftime);
}

EXPORT int __stdcall		TimeFrameToSecs(char* tf){
	if		(strcmp(tf,"M1")==0) return 1    *60;
	else if (strcmp(tf,"M5")==0) return 5    *60;
	else if (strcmp(tf,"M15")==0) return 15  *60;
	else if (strcmp(tf,"M30")==0) return 30  *60;
	else if (strcmp(tf,"H1")==0) return 60   *60;
	else if (strcmp(tf,"H4")==0) return 240  *60;
	else if (strcmp(tf,"D1")==0) return 1440 *60;
	else return 0;
}

EXPORT time_t __stdcall		TimeStringToTime(char* TimeString){
	struct tm tm;
	time_t t;
	int yy; int mm; int dd; int hh; int mi;
	const char* sDateFormat="%4d%02d%02d%02d%02d";
	sscanf_s(TimeString, sDateFormat, &yy, &mm, &dd, &hh, &mi);
	tm.tm_year=yy-1900; tm.tm_mon=mm-1; tm.tm_mday=dd; tm.tm_hour=hh; tm.tm_min=mi; tm.tm_sec=0; tm.tm_isdst=-1;
	t=mktime(&tm);
	return t;
}

EXPORT void __stdcall		TimeToTimeString(time_t pTime, char* pcTime){
	struct tm * timeinfo;
	timeinfo = localtime (&pTime);
	char* buffer = (char*)malloc(80);
	strftime(buffer, strlen(buffer), "%Y%m%d%H%M", timeinfo);
	strcpy(pcTime, buffer);
	free(buffer);
}

EXPORT void _stdcall ms2ts(double ims, char* ots) {
	//-- milliseconds to timestring (HH:MI:SS.ms)
	int ms = (int)ims % 1000;
	int ss = (int)(floor(ims / 1000)) % 60;
	int mi = (int)(floor(ims / 1000 / 60)) % 60;
	int hh = (int)(floor(ims / 1000 / 60 / 60)) % 60;

	sprintf(ots, "%02d:%02d:%02d.%d", hh, mi, ss, ms);
	int kaz = 0;
}


//------	Time Utilities	- End		--------------

//------	String Utilities	- Start		--------------
EXPORT void __stdcall StringSort(int strcnt, char** str){
	int i, j;
	char temp[256];
	for (i = 0; i < strcnt; i++) {
		for (j = 0; j < strcnt - 1; j++) {
			if (strcmp(str[j], str[j + 1]) > 0) {
				strcpy(temp, str[j]);
				strcpy(str[j], str[j + 1]);
				strcpy(str[j + 1], temp);
			}
		}
	}
}

EXPORT void __stdcall Trim(char* str){
	int l = 0;
	int i;
	int r = (int)strlen(str);
	char ret[MAX_PATH];
	while (isspace(str[l])>0) l++;
	while (isspace(str[r - 1])>0) r--;
	for (i = 0; i<(r - l); i++) ret[i] = str[l + i];
	ret[r - l] = '\0';
	strcpy(str, ret);
}

EXPORT char* __stdcall substr(char* str, int start, int len) {
	char ret[1000];
	memcpy(ret, &str[start], len);
	ret[len] = '\0';
	return &ret[0];
}

EXPORT char* __stdcall right(char* str, int len) {
	return(substr(str, (int)strlen(str) - len, len));
}
EXPORT char* __stdcall left(char* str, int len) {
	return(substr(str, 0, len));
}


EXPORT void __stdcall UpperCase(char* str){
	int pos=0;
	while (str[pos] != '\0')	{
		str[pos]=toupper(str[pos]);
		pos++;
	}
}

EXPORT wchar_t *convertCharArrayToLPCWSTR(const char* charArray)
{
	wchar_t wString[4096];
	MultiByteToWideChar(CP_ACP, 0, charArray, -1, wString, 4096);
	return &wString[0];
}

EXPORT char* convertLPCWSTRToCharArray(LPCWSTR wideStr){
	char buffer[500];
	wcstombs(buffer, wideStr, 500);
	return &buffer[0];
}

EXPORT wchar_t* FullFileName(char* pPath, LPCWSTR pFilename){
	char pFullName[500];
	strcpy(pFullName, pPath);
	strcat(pFullName, "\\");
	strcat(pFullName, convertLPCWSTRToCharArray(pFilename) );
	return (convertCharArrayToLPCWSTR(pFullName));
}

EXPORT char* MyGetCurrentDirectory(){
	TCHAR Buffer[MAX_PATH];
	char  RetBuf[MAX_PATH];
	DWORD dwRet;

	dwRet = GetCurrentDirectory(MAX_PATH, Buffer);
	if (dwRet == 0)	{
		printf("GetCurrentDirectory failed (%d)\n", GetLastError());
	}
	wcstombs(RetBuf, Buffer, MAX_PATH);
	return &RetBuf[0];
}

//------	String Utilities	- End		--------------

//------	Arrays Utilities	- Start		--------------
#define SHIFT_FORWARD 1
#define SHIFT_BACKWARD 2

EXPORT void		__stdcall ShuffleArray(int *array, size_t n) {
	srand((unsigned int)time(NULL));
	if (n > 1) {
		size_t i;
		for (i = 0; i < n - 1; i++)	{
			size_t j = i + rand() / (RAND_MAX / (n - i) + 1);
			int t = array[j];
			array[j] = array[i];
			array[i] = t;
		}
	}
}

EXPORT void			__stdcall ShiftArray(int direction, int ArrLen, double* Arr, double NewVal){
	int j;
	if(direction==SHIFT_FORWARD){
		for (j=ArrLen-1; j>0; j--) Arr[j]=Arr[j-1];
		Arr[0]=NewVal;
	} else {   // SHIFT_BACKWARD
		for (j=0; j<ArrLen; j++) Arr[j]=Arr[j+1];
		Arr[ArrLen-1]=NewVal;
	}
	return;
}

EXPORT void			__stdcall InvertArray(int ArrLen, double* Arr){
	int i;
	double* tmpArr = (double*)malloc(ArrLen*sizeof(double));
	memcpy(tmpArr, Arr, ArrLen*sizeof(double));						// original array copied in temp
	for (i = 0; i < ArrLen; i++) Arr[i] = tmpArr[ArrLen - i - 1];	// original array repopulated from temp
	free(tmpArr);
}

EXPORT int			__stdcall DumpArrayD(int ArrLen, double* Arr, char* fname){
	FILE* fDump = fopen(fname, "w");
	if (fDump == NULL){
		printf("Could not open Source Data File. Exiting...\n");
		printf("Press any key..."); getchar();;
		return -1;
	}
	for (int i = 0; i < ArrLen; i++){
		fprintf(fDump, "%f\n", Arr[i]);
	}
	fclose(fDump);
	return 0;
}

//------	Arrays Utilities	- End	--------------

//------	Miscellaneous Utilities	- Start	----------
 EXPORT int __stdcall	FindMinMax(int pDataCount, double* pData, double* oMin, double* oMax){
	int i;
	double vMin=10000000000; double vMax=-10000000000;
	//FILE* fk = fopen("C:/temp/FindMinMax.log", "w");
	for (i=0; i<pDataCount; i++){
		if (pData[i]<vMin && pData[i] != EMPTY_VALUE) vMin = pData[i];
		if (pData[i]>vMax && pData[i] != EMPTY_VALUE) vMax = pData[i];
		//fprintf(fk, "data=%f ; vMin=%f vMax=%f\n", pData[i], vMin, vMax);
	}
	memcpy(oMin, &vMin, sizeof(double));
	memcpy(oMax, &vMax, sizeof(double));
	//fclose(fk);

	return 0;
}

 void RemoveCommentFromLine(char* pLine){
	 const char cmt[3] = "//";
	 for (unsigned int i = 0; i < strlen(pLine); i++){
		 if (pLine[i] == cmt[0] && pLine[i+1] == cmt[1]){
			 pLine[i] = '\0';
			 return;
		 }
	 }
 }

 EXPORT void __stdcall swapD(double* a, double* b) {
	 double c = *a; *a = *b; *b = c;
 }
 EXPORT void __stdcall swapI(int* a, int* b) {
	 int c = *a; *a = *b; *b = c;
 }

 EXPORT void __stdcall gotoxy(int x, int y){
	 COORD coord;
	 coord.X = x;
	 coord.Y = y;
	 SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
 }

 EXPORT int isIndeterminate(const double pV)
 {
	 return (pV != pV);
 }

 EXPORT int cslToArray(char* csl, char Separator, char** StrList){
	 //-- 1. Put a <separator>-separated list of string values into an array of strings, and returns list length
	 int i = 0;
	 int prevSep = 0;
	 int ListLen = 0;
	 int kaz;

	 while (csl[i] != '\0'){
		 kaz = (prevSep == 0)?0:1;
		 if (csl[i] == Separator){
			 // separator
			 memcpy(StrList[ListLen], &csl[prevSep + kaz], i - prevSep - kaz);
			 StrList[ListLen][i - prevSep - kaz] = '\0';	// add null terminator
			 Trim(StrList[ListLen]);
			 ListLen++;
			 prevSep = i;
		 }
		 i++;
	 }
	 //-- portion of pDesc after the last comma
	 memcpy(StrList[ListLen], &csl[prevSep + kaz], i - prevSep - kaz);
	 StrList[ListLen][i - prevSep - kaz] = '\0';	// add null terminator
	 Trim(StrList[ListLen]);

	 return (ListLen+1);
 }

 //------	Miscellaneous Utilities	- End	----------

//------	Data Scaling Utilities	- Start ---------
EXPORT void __stdcall SlideArray(int iWholeSetLen, double* iWholeSet, int iSampleCount, int iSampleLen, double** oSample, int iTargetLen, double** oTarget, int pWriteLog){
	int s, i;
	char LogFileName[MAX_PATH];
	FILE* LogFile=NULL;

	if (pWriteLog>1){
		//strcpy(LogFileName, MyGetCurrentDirectory()); strcat(LogFileName, "\\SlideArray.log");
		strcpy(LogFileName, "C:/temp/SlideArray.log");
		LogFile = fopen(LogFileName, "w");
	}

	for (s = 0; s<iSampleCount; s++){
		for (i = 0; i<iSampleLen; i++){
			oSample[s][i] = iWholeSet[s + i];
			if (pWriteLog>1) fprintf(LogFile, "%f ", oSample[s][i]);
		}
		for (i = 0; i<iTargetLen; i++){
			if ((s + iSampleLen + i) >= iWholeSetLen){
				oTarget[s][i] = oTarget[s][i - 1];
			}
			else {
				oTarget[s][i] = iWholeSet[s + iSampleLen + i];
			}
			if (pWriteLog>1) fprintf(LogFile, "%f ", oTarget[s][i]);
		}
		if (pWriteLog>1) fprintf(LogFile, "\n");
	}

	if (pWriteLog>1) fclose(LogFile);
}

 EXPORT void __stdcall SlideArrayNew(int dlen, double* idata, int iSampleLen, int iTargetLen, double** oSample, double** oTarget, int pWriteLog) {
	 int s, i;
	 char LogFileName[MAX_PATH];
	 FILE* LogFile = NULL;

	 if (pWriteLog > 1) {
		 //strcpy(LogFileName, MyGetCurrentDirectory()); strcat(LogFileName, "\\SlideArray.log");
		 strcpy(LogFileName, "C:/temp/SlideArray.log");
		 LogFile = fopen(LogFileName, "w");
	 }

	 int SampleCount = dlen - iSampleLen;
	 for (s = 0; s < SampleCount; s++) {
		 for (i = 0; i < iSampleLen; i++) {
			 oSample[s][i] = idata[s + i];
			 if (pWriteLog > 1) fprintf(LogFile, "%f ", oSample[s][i]);
		 }
		 for (i = 0; i < iTargetLen; i++) {
			 if ((s + iSampleLen + i) >= dlen) {
				 oTarget[s][i] = oTarget[s][i - 1];
			 }
			 else {
				 oTarget[s][i] = idata[s + iSampleLen + i];
			 }
			 if (pWriteLog > 1) fprintf(LogFile, "%f ", oTarget[s][i]);
		 }
		 if (pWriteLog > 1) fprintf(LogFile, "\n");
	 }

	 if (pWriteLog > 1) fclose(LogFile);
 }

 EXPORT void __stdcall UnSlideArray(int pRowsCnt, int pSampleLen, int pTargetLen, double** pSample, double** pTarget, double* oArr) {
	 int ArrLen = pRowsCnt + pSampleLen;
	 int i;
	 for (i = 0; i<pRowsCnt; i++) {
		 oArr[i] = pSample[i][0];
	 }
	 for (i = 0; i<pSampleLen; i++) {
		 oArr[pRowsCnt + i] = pSample[pRowsCnt - 1][i + 1];
	 }
	 oArr[pRowsCnt + pSampleLen - 1] = pTarget[pRowsCnt - 1][0];
 }
 
 EXPORT void __stdcall  DataScale(int iDataLen, double* iOrigData, double iScaleMin, double iScaleMax, double* oScaledData, double* oScaleM, double* oScaleP){
	int i;
	double OrigMin, OrigMax;

	//FILE* fk = fopen("C:/temp/DataScale.log", "w");

	FindMinMax(iDataLen, iOrigData, &OrigMin, &OrigMax);
	(*oScaleM) = (iScaleMax - iScaleMin) / (OrigMax - OrigMin);
	(*oScaleP) = iScaleMin - OrigMin * (*oScaleM);

	for (i = 0; i < iDataLen; i++){
		if (iOrigData[i] == EMPTY_VALUE){
			oScaledData[i] = iOrigData[i];
		} else{
			oScaledData[i] = iOrigData[i] * (*oScaleM) + (*oScaleP);
		}
		//fprintf(fk, "iOrigData[%d]=%f ; oScaledData[%d]=%f\n", i, iOrigData[i], i, oScaledData[i]);
	}
	//fclose(fk);
}

/*EXPORT void __stdcall  DataUnScale(int iDataLen, double* InOutData, double iScaleM, double iScaleP){
	for (int i = 0; i < iDataLen; i++) InOutData[i] = (InOutData[i] - iScaleP) / iScaleM;
}
EXPORT void __stdcall  DataUnScale(int iDataLen, double* iScaledData, double iScaleM, double iScaleP, double* oUnScaledData){
	for (int i = 0; i < iDataLen; i++) oUnScaledData[i] = (iScaledData[i] - iScaleP) / iScaleM;
}
*/
EXPORT void __stdcall  DataUnScale(int iDataLen, int iFromItem, int iToItem, double* iScaledData, double iScaleM, double iScaleP, double* oUnScaledData){
	int i;
	for (i = iFromItem; i < iToItem; i++) oUnScaledData[i] = (iScaledData[i] - iScaleP) / iScaleM;
	for (i = 0; i < iFromItem; i++) oUnScaledData[i] = EMPTY_VALUE;
	for (i = iToItem; i < iDataLen; i++) oUnScaledData[i] = EMPTY_VALUE;
}

//------	Data Scaling Utilities	- End ---------

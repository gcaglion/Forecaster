#pragma once

#define _CRT_RAND_S

#include <stdlib.h>
#include <time.h>
#include <Windows.h>
#include <math.h>
#include <stdio.h>
#include <direct.h>
#include <MyUtils2.h>

#include <MyUtilsT.cpp>


//------	Random Utilities	- Start		--------------
#define _CRT_RAND_S
EXPORT int 	MyRndInt(int rmin, int rmax);
EXPORT double MyRndDbl(double min, double max);
EXPORT double		MyRandom01();

//------	Time Utilities	- Start		--------------
EXPORT int		TimeFrameToMins(char* tf);
EXPORT char* timestamp();
EXPORT int		TimeFrameToSecs(char* tf);
EXPORT time_t	TimeStringToTime(char* TimeString);
EXPORT void		TimeToTimeString(time_t pTime, char* pcTime);
EXPORT void		ms2ts(double ims, char* ots);

//------	String Utilities	- Start		--------------
#define BUFSIZE MAX_PATH

EXPORT void StringSort(int strcnt, char** str);
EXPORT char* substr(char* str, int start, int len);
EXPORT char* right(char* str, int len);
EXPORT char* left(char* str, int len);
EXPORT void UpperCase(char* str);
EXPORT wchar_t *convertCharArrayToLPCWSTR(const char* charArray);
EXPORT char*    convertLPCWSTRToCharArray(LPCWSTR wideStr);
EXPORT wchar_t* FullFileName(char* pPath, LPCWSTR pFilename);
EXPORT char* MyGetCurrentDirectory();

//------	Arrays Utilities	- Start		--------------
#define SHIFT_FORWARD 1
#define SHIFT_BACKWARD 2
EXPORT void	ShuffleArray(int *array, size_t n);
EXPORT void	ShiftArray(int direction, int ArrLen, double* Arr, double NewVal);
EXPORT void	InvertArray(int ArrLen, double* Arr);
EXPORT int	DumpArrayD(int ArrLen, double* Arr, char* fname);

//------	Miscellaneous Utilities	- Start	----------
#define greater(a,b) ((a>b)?a:b)
EXPORT int			FindMinMax(int pDataCount, double* pData, double* oMin, double* oMax);
EXPORT int cslToArray(char* csl, char Separator, char** StrList);
EXPORT void			swapD(double* a, double* b);
EXPORT void			swapI(int* a, int* b);
EXPORT void gotoxy(int x, int y);
EXPORT int isIndeterminate(const double pV);
//------	Miscellaneous Utilities	- End	----------

//------	Data Scaling Utilities			---------
#define EMPTY_VALUE -9999	// This is needed for partial Unscaling and UnTransformation of Dataseries

EXPORT void SlideArray(int iWholeSetLen, double* iWholeSet, int iSampleCount, int iSampleLen, double** oSample, int iTargetLen, double** oTarget, int pWriteLog);
EXPORT void SlideArrayNew(int dlen, double* idata, int iSampleLen, int iTargetLen, double** oSample, double** oTarget, int pWriteLog);
EXPORT void UnSlideArray(int pRowsCnt, int pSampleLen, int pTargetLen, double** pSample, double** pTarget, double* oArr);
EXPORT void  DataScale(int iDataLen, double* iOrigData, double iScaleMin, double iScaleMax, double* oScaledData, double* oScaleM, double* oScaleP);
EXPORT void  DataUnScale(int iDataLen, int iFromItem, int iToItem, double* iScaledData, double iScaleM, double iScaleP, double* oUnScaledData);
//------	Data Scaling Utilities - End	---------

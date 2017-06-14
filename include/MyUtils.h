#define _CRT_RAND_S
#include <stdlib.h>

#include <time.h>
#include <Windows.h>
#include <stdio.h>

#include <MyUtilsT.cpp>


#undef EXPORT
#define EXPORT __declspec(dllexport)

//------------ CPU Usage utilities -------------------
EXPORT float GetCPULoad();
EXPORT DWORD GetMemLoad();

//------	Random Utilities	- Start		--------------
//#define MyRnd(rmin, rmax) (rmin + (rand() % rmax))

EXPORT int __stdcall	MyRndInt(int rmin, int rmax);
EXPORT double __stdcall MyRndDbl(double min, double max);
EXPORT double		__stdcall MyRandom01();
//------	Random Utilities	- End		--------------

//------	Time Utilities	- Start		--------------
EXPORT int		__stdcall TimeFrameToMins(char* tf);
EXPORT char*	__stdcall timestamp();
EXPORT int		__stdcall TimeFrameToSecs(char* tf);
EXPORT time_t	__stdcall TimeStringToTime(char* TimeString);
EXPORT void		__stdcall TimeToTimeString(time_t pTime, char* pcTime);
EXPORT void		__stdcall ms2ts(double ims, char* ots);
//------	Time Utilities	- End		--------------

//------	String Utilities	- Start		--------------
#define BUFSIZE MAX_PATH

EXPORT void __stdcall StringSort(int strcnt, char** str);
EXPORT char* __stdcall substr(char* str, int start, int len);
EXPORT char* __stdcall right(char* str, int len);
EXPORT char* __stdcall left(char* str, int len);
EXPORT void __stdcall Trim(char* str);
EXPORT void __stdcall UpperCase(char* str);
EXPORT wchar_t *convertCharArrayToLPCWSTR(const char* charArray);
EXPORT char*    convertLPCWSTRToCharArray(LPCWSTR wideStr);
EXPORT wchar_t* FullFileName(char* pPath, LPCWSTR pFilename);
EXPORT char* MyGetCurrentDirectory();

//------	String Utilities	- End		--------------

//------	Arrays Utilities	- Start		--------------
#define SHIFT_FORWARD 1
#define SHIFT_BACKWARD 2

EXPORT void	__stdcall ShuffleArray(int *array, size_t n);
EXPORT void	__stdcall ShiftArray(int direction, int ArrLen, double* Arr, double NewVal);
EXPORT void	__stdcall InvertArray(int ArrLen, double* Arr);
EXPORT int	__stdcall DumpArrayD(int ArrLen, double* Arr, char* fname);

//------	Arrays Utilities	- End	--------------

//------	Miscellaneous Utilities	- Start	----------
//#define sign(a) ( ( (a) < 0 )  ?  -1   : ( (a) > 0 ) )
#define greater(a,b) ((a>b)?a:b)
EXPORT int			__stdcall FindMinMax(int pDataCount, double* pData, double* oMin, double* oMax);

EXPORT int cslToArray(char* csl, char Separator, char** StrList);

EXPORT int __stdcall	ReadMultiParamFromFileI(char* pFileName, char* pParamName, int** oParamValue);
//----------------------------------------------


EXPORT void			__stdcall swapD(double* a, double* b);
EXPORT void			__stdcall swapI(int* a, int* b);
EXPORT void __stdcall gotoxy(int x, int y);
EXPORT int isIndeterminate(const double pV);
//------	Miscellaneous Utilities	- End	----------

//------	Data Scaling Utilities			---------
#define EMPTY_VALUE -9999	// This is needed for partial Unscaling and UnTransformation of Dataseries

EXPORT void __stdcall SlideArray(int iWholeSetLen, double* iWholeSet, int iSampleCount, int iSampleLen, double** oSample, int iTargetLen, double** oTarget, int pWriteLog);
EXPORT void __stdcall SlideArrayNew(int dlen, double* idata, int iSampleLen, int iTargetLen, double** oSample, double** oTarget, int pWriteLog);
EXPORT void __stdcall UnSlideArray(int pRowsCnt, int pSampleLen, int pTargetLen, double** pSample, double** pTarget, double* oArr);
EXPORT void __stdcall  DataScale(int iDataLen, double* iOrigData, double iScaleMin, double iScaleMax, double* oScaledData, double* oScaleM, double* oScaleP);
EXPORT void __stdcall  DataUnScale(int iDataLen, int iFromItem, int iToItem, double* iScaledData, double iScaleM, double iScaleP, double* oUnScaledData);
//------	Data Scaling Utilities - End	---------

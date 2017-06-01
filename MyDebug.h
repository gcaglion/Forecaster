#pragma once
#include <stdio.h>
#include <Windows.h>
#include <DBConnection.h>
#include <MyUtils.h>

#undef EXPORT
#ifdef __cplusplus
#define EXPORT extern "C" __declspec(dllexport)
#else
#define EXPORT __declspec(dllexport)
#endif

#define LOG_INFO 0
#define LOG_ERROR 1

// Logs Destinations
#define LOG_TO_TEXT   1
#define LOG_TO_ORCL	  2

typedef struct sDebugInfo {
	int DebugLevel;		//-- 0:Nothing ; 1:Screen-Only ; 2:File-Only ; 3:File+Screen
//	int DebugDest;		//-- ORCL | TEXT
//	tDBConnection* DebugDB;
	char fPath[MAX_PATH];
	char fName[MAX_PATH];
	char FullfName[MAX_PATH];
	FILE* fHandle;
	int  fIsOpen;
	//void* DBCtx;
	int ThreadSafeLogging;
	int SaveMSE;
	int SaveRun;
	int SaveInternals;
	HANDLE Mtx;		// Mutex handle used by LogWrite()
	
	//-- used by cores output to screen
	int CorePos;
	int TotCores;
/*
#ifdef __cplusplus
	sDebugInfo() {
		DebugDB = new tDBConnection();
		Mtx = CreateMutex(NULL, false, NULL);
	}
	~sDebugInfo() {
		delete(DebugDB);
	}
#endif
*/
} tDebugInfo;

EXPORT void LogWrite(tDebugInfo* DebugParms, int LogType, char* msg, int argcount, ...);
EXPORT void LogClose(tDebugInfo* DebugParms);

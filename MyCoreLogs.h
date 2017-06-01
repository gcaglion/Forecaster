//-- cCoreLog defines common section of core logs. Each core type extends this class with its own specific logs (cNNLog, cSVMLog, ...)

#pragma once
#include <MyUtils.h>
#include <CoreCommonLogs.h>
#include <MyDebug.h>
#include <DBConnection.h>
#include <ExportDef.h>

//#include <MyDataAbstraction.h>

class cCoreLog {
public:
	int			ProcessId;
	int			ThreadId;	// thread id of saved thread used for saving/loading
	int			ActualEpochs;		// If training was stopped before reaching MaxEpochs (because TargetMSE was reached, or because of Training Divergence), this saves the actual Epochs run
	tLogMSE*	MSEOutput;		// [Epoch]
	int			RunCount;
	tLogRUN*	RunOutput;		// [pos]

	EXPORT int SaveMSE(tDebugInfo* DebugParms, tDBConnection* DBConn);
	EXPORT int SaveRun(tDebugInfo* DebugParms, tDBConnection* DBConn, int hlen);
	EXPORT virtual int SaveImage(tDebugInfo* DebugParms) =0;

	EXPORT cCoreLog();
	//cCoreLog(int MSEcnt, int RunCnt);
	EXPORT ~cCoreLog();
};
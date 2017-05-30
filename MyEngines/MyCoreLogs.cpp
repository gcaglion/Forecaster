#include <MyCoreLogs.h>

EXPORT int cCoreLog::SaveMSE(tDebugInfo* DebugParms, tDBConnection* DBConn) {
	return(InsertMSELog(DebugParms, DBConn, &ActualEpochs, MSEOutput));
}
EXPORT int cCoreLog::SaveRun(tDebugInfo* DebugParms, tDBConnection* DBConn, int hlen) {
	return(InsertRunLog(DebugParms, DBConn, &ActualEpochs, hlen, RunOutput));
}
EXPORT int cCoreLog::SaveImage(tDebugInfo* DebugParms) { return 0; }

//-- constructors / destructor
EXPORT cCoreLog::cCoreLog(){}
cCoreLog::cCoreLog(int MSEcnt, int Runcnt){
	MSEOutput = MallocArray<tLogMSE>(MSEcnt);
	RunCount = Runcnt;
	RunOutput = MallocArray<tLogRUN>(Runcnt);
}
EXPORT cCoreLog::~cCoreLog(){
	free(MSEOutput);
	free(RunOutput);
}

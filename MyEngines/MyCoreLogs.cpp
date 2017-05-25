#include <MyCoreLogs.h>

EXPORT int cCoreLog::SaveMSE(tDebugInfo* DebugParms) {
	return(InsertMSELog(DebugParms, &ActualEpochs, MSEOutput));
}
EXPORT int cCoreLog::SaveRun(tDebugInfo* DebugParms, int hlen) {
	return(InsertRunLog(DebugParms, &ActualEpochs, hlen, RunOutput));
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

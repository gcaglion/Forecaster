#include <MyCores.h>

EXPORT cCore::cCore(int cType, int dscnt, int inputCnt, int outputCnt){
	CoreType = cType;
	coreLog = MallocArray<cCoreLog*>(1);
	InputCount = inputCnt; OutputCount = outputCnt;
}
EXPORT cCore::cCore() {
	coreLog = MallocArray<cCoreLog*>(1);
}
EXPORT cCore::~cCore() {
	FreeArray(1, coreLog);
}

void cCore::init(){}
EXPORT int  cCore::train(tDebugInfo* pDebugParms, int DatasetId, int sampleCnt, int sampleLen, int targetLen, double** SampleT, double** TargetT, int useValidation, double** SampleV, double** TargetV) { return 0; }
EXPORT int  cCore::run(tDebugInfo* pDebugParms, int sampleCnt, int sampleLen, int targetLen, double** S, double** T) { return 0; }
EXPORT int  cCore::setParms(tDebugInfo* DebugParms, int pid, int tid) { return 0; }
int  cCore::LoadImage(tDebugInfo* DebugParms, tDBConnection* DBConn, int pid, int tid) { return 0; }
void cCore::mallocLogs(int dscnt) {
	for (int d = 0; d<dscnt; d++) coreLog[d] = new cCoreLog(MSECount, RunCount);
}
EXPORT void cCore::getScaleRange(double* oScaleMin, double* oScaleMax) { 
	//-- default behavior
	(*oScaleMin) = -1;
	(*oScaleMax) =  1;
	return; 
}
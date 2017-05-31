#include <MyCores.h>

EXPORT cCore::cCore(int cType, int dscnt, int inputCnt, int outputCnt){
	CoreType = cType;
	coreLog = MallocArray<cCoreLog*>(1);
	SampleLen = inputCnt; TargetLen = outputCnt;
}
EXPORT cCore::cCore() {
	coreLog = MallocArray<cCoreLog*>(1);
}
EXPORT cCore::~cCore() {
	FreeArray(1, coreLog);
}

void cCore::mallocLogs(int dscnt) {
	for (int d = 0; d<dscnt; d++) coreLog[d] = new cCoreLog(MSECount, RunCount);
}
EXPORT void cCore::getScaleRange(double* oScaleMin, double* oScaleMax) { 
	//-- default behavior
	(*oScaleMin) = -1;
	(*oScaleMax) =  1;
	return; 
}
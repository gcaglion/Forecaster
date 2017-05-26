#include <MySVM.h>

int cSVM::calcSVcnt(MODEL* model) {
	long sv_num = 1;
	for (long i = 1; i<model->sv_num; i++) {
		for (SVECTOR* v = model->supvec[i]->fvec; v; v = v->next)
			sv_num++;
	}
	return sv_num;
}


EXPORT void cSVM::init() {}
void cSVM::train(int DatasetId, int sampleCnt, int sampleLen, int targetLen, double** S_t, double** T_t, int useValidation, double** S_v, double** T_v) {}
void cSVM::run(int DatasetId, double*** savedW, int sampleCnt, int sampleLen, int targetLen, double** S, double** T) {}
int  cSVM::setParms(tDebugInfo* DebugParms, int pid, int tid, bool load, int iSampleCnt) {
	return 0;
}
EXPORT int  cSVM::LoadImage(tDebugInfo* DebugParms, int pid, int tid) {
	return 0;
}
EXPORT void cSVM::mallocLogs(int dscnt) {}

EXPORT cSVM::cSVM(){}
cSVM::~cSVM(){}

//-- cSVMLog stuff
cSVMLog::cSVMLog(int pSVcnt, int pVarcnt) {
	SVcnt = pSVcnt; Varcnt = pVarcnt;
	//-- SVs
	FinalW = MallocArray<double>(pSVcnt, pVarcnt);
}
cSVMLog::~cSVMLog() {
	//-- SVs
	FreeArray(SVcnt, Varcnt, FinalW);
}

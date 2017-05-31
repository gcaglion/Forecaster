#include <MySVM.h>

int cSVM::calcSVcnt(MODEL* model) {
	long sv_num = 1;
	for (long i = 1; i<model->sv_num; i++) {
		for (SVECTOR* v = model->supvec[i]->fvec; v; v = v->next)
			sv_num++;
	}
	return sv_num;
}


void cSVM::init() {}
int cSVM::train(tDebugInfo* pDebugParms, int DatasetId, int sampleCnt, int sampleLen, int targetLen, double** S_t, double** T_t, int useValidation, double** S_v, double** T_v) {
	return 0;
}
int  cSVM::run(tDebugInfo* pDebugParms, int sampleCnt, int sampleLen, int targetLen, double** S, double** T, void* img) {
	return 0;
}
int  cSVM::LoadImage(tDebugInfo* DebugParms, tDBConnection* DBConnection, int pid, int tid) {
	return 0;
}
void cSVM::mallocLogs(int dscnt) {}
void cSVM::getScaleRange(double* oScaleMin, double* oScaleMax) {
	(*oScaleMin) = -1;
	(*oScaleMax) = 1;
}

cSVM::cSVM(){}
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

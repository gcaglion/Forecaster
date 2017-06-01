#include <MyNN.h>

void cNN::init(){}
int  cNN::train(tDebugInfo* pDebugParms, int DatasetId, int sampleCnt, int sampleLen, int targetLen, double** S_t, double** T_t, int useValidation, double** S_v, double** T_v){
	return 0;
}
int  cNN::run(tDebugInfo* pDebugParms, int sampleCnt, int sampleLen, int targetLen, double** S, double** T, void* img){
	return 0;
}
int  cNN::loadImage(tDebugInfo* DebugParms, tDBConnection* DBConn, int pid, int tid){
	return 0;
}
//void mallocLogs(int dscnt){}
void cNN::getScaleRange(double* oScaleMin, double* oScaleMax){}
void cNN::setTopology(){}

cNN::cNN(){}
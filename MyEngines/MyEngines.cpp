#include <vld.h>

#include <MyEngines.h>
#include <MyNN.h>
#include <MyGA.h>
#include <MySOM.h>
#include <MySVM.h>

EXPORT void cEngine::setLayout(int DatasetsCount, int DataSampleLen, int DataTargetLen) {
	int l, c;
	
	InputCount = DataSampleLen;
	OutputCount = DataTargetLen;

	if (EngineType==ENGINE_WNN) {
		//-- LayersCount, CoresCount[]
		LayersCount = 2;
		CoresCount = MallocArray<int>(LayersCount);
		CoresCount[0] = WNN_DecompLevel+1;
		CoresCount[1] = 1;

		//-- CoreType[][]
		CoreType = MallocArray<int>(LayersCount, ArrayMax(LayersCount, CoresCount));
		for (c = 0; c<CoresCount[0]; c++) CoreType[0][c] = CORE_NN;
		CoreType[1][0] = CORE_NN;
	}
	else if (EngineType = ENGINE_XIE) {
		//-- LayersCount, CoresCount[]
		LayersCount = 2;
		CoresCount = MallocArray<int>(LayersCount);
		CoresCount[0] = 2;
		CoresCount[1] = 1;

		//-- CoreType[][]
		CoreType = MallocArray<int>(LayersCount, ArrayMax(LayersCount, CoresCount));
		CoreType[0][0] = CORE_SVM;
		CoreType[0][1] = CORE_NN;
		CoreType[1][0] = CORE_NN;
	}
	else {
		//-- LayersCount, CoresCount[]
		LayersCount = 1;
		CoresCount = MallocArray<int>(LayersCount);
		CoresCount[0] = 1;

		//-- CoreType[][]
		CoreType = MallocArray<int>(LayersCount, ArrayMax(LayersCount, CoresCount));
		CoreType[0][0] = EngineType;
	}

	for (l = 0; l<LayersCount; l++) {
		for (c = 0; c<CoresCount[l]; c++) {
			switch (CoreType[l][c]) {
			case CORE_NN:
				Core[l][c] = new cNN();
				break;
			case CORE_GA:
				Core[l][c] = new cGA();
				break;
			case CORE_SOM:
				Core[l][c] = new cSOM();
				break;
			case CORE_SVM:
				Core[l][c] = new cSVM();
				break;
			}
		}
	}

}

EXPORT cEngine::cEngine(){
	TSFid = MallocArray<int>(MAX_TSFCOUNT);
}
EXPORT cEngine::cEngine(int DataSampleLen, int DataTargetLen) {
	InputCount = DataSampleLen;
	OutputCount = DataTargetLen;
	TSFid = MallocArray<int>(MAX_TSFCOUNT);
	WNN_WaveletType = MallocArray<char>(WTypeDescLen);
}
cEngine::~cEngine() {
	free(TSFid);
	for (int l = 0; l<LayersCount; l++) free(Core[l]);
	free(Core);

	for (int l = 0; l<LayersCount; l++) {
		for (int c = 0; c<CoresCount[l]; c++) {
			free(Core[l][c]);
		}
		free(Core[l]);
	}
	free(Core);
}

EXPORT int cEngine::LoadCoresParms(tDebugInfo* pDebugParms, tDBConnection* pDBConn, int pid) {

	for (int l = 0; l <LayersCount; l++) {
		for (int n = 0; n<CoresCount[l]; n++) {
			//-- first, get ThreadId for this core. Use Dataset=0 and TestId=0, as core parameters are the same for every dataset/Test
			Core[l][n]
			Core[l][n]->coreLog[0]->ThreadId = GetCoreThreadId(pDebugParms, pDBConn, pid, 0, 0, l, n); if (Core[l][n]->coreLog[l][n].ThreadId<0) return -1;
			//-- then,  load core parameters
			if (Core[l][n]->setParms(pDebugParms, pid, Core[l][n]->coreLog[l][n].ThreadId) <0) return -1;
		}
	}
	return 0;
}
EXPORT int cEngine::LoadCoresImage(tDebugInfo* pDebugParms, tDBConnection* pDBConn, int pid) {

	for (int l = 0; l < LayersCount; l++) {
		for (int n = 0; n < CoresCount[l]; n++) {
			if (Core[l][n]->setParms(pDebugParms, pid, Core[l][n]->coreLog[l][n].ThreadId) <0) return -1;
		}
	}

	return 0;
}
EXPORT int cEngine::Save(tDebugInfo* DebugParms, tDBConnection* pDBConn, int pid, int testid, int dscnt) {

	//-- first, EngineParms
	if (InsertEngineParms(DebugParms, pDBConn, pid, EngineType, LayersCount, WNN_DecompLevel, WNN_WaveletType) <0) return -1;

	//-- then, EngineThreads
	for (int l = 0; l<LayersCount; l++) {
		for (int c = 0; c<CoresCount[l]; c++) {
			for (int d = 0; d<dscnt; d++) {
				if (InsertEngineThreads(DebugParms, pDBConn, pid, testid, l, c, Core[l][c]->CoreType, d, Core[l][c]->coreLog[d]->ThreadId) <0) return -1;
			}
		}
	}
	return 0;
}
EXPORT int cEngine::SaveMSELogs(tDebugInfo* DebugParms, tDBConnection* pDBConn, int pid, int dscnt){
	for (int l = 0; l<LayersCount; l++) {
		for (int c = 0; c<CoresCount[l]; c++) {
			for (int d = 0; d<dscnt; d++) {
				return( Core[l][c]->coreLog[d]->SaveMSE(DebugParms, pDBConn) );
			}
		}
	}
	return 0;
}
EXPORT int cEngine::SaveRunLogs(tDebugInfo* DebugParms, tDBConnection* pDBConn, int pid, int dscnt, int pHistoryLen){
	for (int l = 0; l<LayersCount; l++) {
		for (int c = 0; c<CoresCount[l]; c++) {
			for (int d = 0; d<dscnt; d++) {
				return( Core[l][c]->coreLog[d]->SaveRun(DebugParms, pDBConn, pHistoryLen) );
			}
		}
	}
	return 0;
}
EXPORT int cEngine::SaveImage(tDebugInfo* DebugParms, int pid, int dscnt, int testid){
	for (int l = 0; l<LayersCount; l++) {
		for (int c = 0; c<CoresCount[l]; c++) {
			for (int d = 0; d<dscnt; d++) {
				return( Core[l][c]->coreLog[d]->SaveImage(DebugParms) );
			}
		}
	}
	return 0;
}

EXPORT void cEngine::mallocCoresLogs(int dscnt) {
	for (int l = 0; l<LayersCount; l++) {
		for (int c = 0; c<CoresCount[l]; c++) {
			Core[l][c]->mallocLogs(dscnt);
		}
	}
}


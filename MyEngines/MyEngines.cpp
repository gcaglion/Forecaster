#include <vld.h>

#include <MyEngines.h>

EXPORT void cEngine::setLayout() {

	//-- 1. set LayersCount, CoresCount, Core[]
	switch (EngineType) {
	case ENGINE_WNN:
		LayersCount = 2;
		CoresCount = MallocArray<int>(LayersCount);
		CoresCount[0] = WNN_DecompLevel+1;
		CoresCount[1] = 1;

		Core = MallocArray<cCore**>(LayersCount);
		for (int l = 0; l<LayersCount; l++) {
			Core[l] = MallocArray<cCore*>(CoresCount[l]);
			for (int c = 0; c<CoresCount[l]; c++) {
				Core[l][c] = new cCore(CORE_NN, (l>0)?(CoresCount[0]*OutputCount+TSFcnt):InputCount, OutputCount);	
			}
		}
		break;
	case ENGINE_XIE:
		LayersCount = 2;
		CoresCount = MallocArray<int>(LayersCount);
		CoresCount[0] = 2;
		CoresCount[1] = 1;

		Core = MallocArray<cCore**>(LayersCount);
		Core[0] = MallocArray<cCore*>(CoresCount[0]);
		Core[0] = MallocArray<cCore*>(CoresCount[1]);

		Core[0][0] = new cCore(CORE_SVM, InputCount, OutputCount);
		Core[0][1] = new cCore(CORE_NN, InputCount, OutputCount);
		Core[1][0] = new cCore(CORE_NN, (2*OutputCount+TSFcnt), OutputCount);

		break;
	default:
		LayersCount = 1;
		CoresCount = MallocArray<int>(LayersCount);
		CoresCount[0] = 1;
		Core = MallocArray<cCore**>(LayersCount);

		Core[0][0] = new cCore(EngineType, InputCount, OutputCount);
		break;
	}

	//-- 2. set TotalCoresCount, and RunCount for every core
	TotalCoresCount = 0;
	for (int l = 0; l < LayersCount; l++) {
		for (int c = 0; c < CoresCount[l]; c++) {
			Core[l][c]->RunCount = InputCount+OutputCount;
			TotalCoresCount++;
		}
	}
/*
	//-- 3. set InputCount/OutputCount for each core. This depends on ENGINE_TYPE, not CORE_TYPE (see ENGINE_WNN)
	switch (EngineType) {
	case ENGINE_WNN:
		break;
	case ENGINE_XIE:
		Core[0][0]->InputCount = InputCount;
		Core[0][0]->OutputCount = OutputCount;
		Core[0][1]->InputCount = InputCount;
		Core[0][1]->OutputCount = OutputCount;
		Core[1][0]->InputCount = Core[0][0]->OutputCount+Core[0][1]->OutputCount+TSFcnt;
		break;
	default:
		Core[0][0]->InputCount  = InputCount;
		Core[0][0]->OutputCount = OutputCount;
		break;
	}
	*/
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

EXPORT int cEngine::LoadCoresParms(tDebugInfo* pDebugParms, int pid) {

	for (int l = 0; l <LayersCount; l++) {
		for (int n = 0; n<CoresCount[l]; n++) {
			//-- first, get ThreadId for this core. Use Dataset=0 and TestId=0, as core parameters are the same for every dataset/Test
			Core[l][n]->coreLog[l][n].ThreadId = GetCoreThreadId(pDebugParms, pid, 0, 0, l, n); if (Core[l][n]->coreLog[l][n].ThreadId<0) return -1;
			//-- then,  load core parameters
			if (Core[l][n]->setParms(pDebugParms, pid, Core[l][n]->coreLog[l][n].ThreadId) <0) return -1;
		}
	}
	return 0;
}
EXPORT int cEngine::LoadCoresImage(tDebugInfo* pDebugParms, int pid) {

	for (int l = 0; l < LayersCount; l++) {
		for (int n = 0; n < CoresCount[l]; n++) {
			if (Core[l][n]->setParms(pDebugParms, pid, Core[l][n]->coreLog[l][n].ThreadId) <0) return -1;
		}
	}

	return 0;
}
EXPORT int cEngine::Save(tDebugInfo* DebugParms, int pid, int testid, int dscnt) {

	//-- first, EngineParms
	if (InsertEngineParms(DebugParms, pid, EngineType, LayersCount, WNN_DecompLevel, WNN_WaveletType) <0) return -1;

	//-- then, EngineThreads
	for (int l = 0; l<LayersCount; l++) {
		for (int c = 0; c<CoresCount[l]; c++) {
			for (int d = 0; d<dscnt; d++) {
				if (InsertEngineThreads(DebugParms, pid, testid, l, c, Core[l][c]->CoreType, d, Core[l][c]->coreLog[d]->ThreadId) <0) return -1;
			}
		}
	}
	return 0;
}
EXPORT int cEngine::SaveMSELogs(tDebugInfo* DebugParms, int pid, int dscnt){
	for (int l = 0; l<LayersCount; l++) {
		for (int c = 0; c<CoresCount[l]; c++) {
			for (int d = 0; d<dscnt; d++) {
				return( Core[l][c]->coreLog[d]->SaveMSE(DebugParms) );
			}
		}
	}
	return 0;
}
EXPORT int cEngine::SaveRunLogs(tDebugInfo* DebugParms, int pid, int dscnt, int pHistoryLen){
	for (int l = 0; l<LayersCount; l++) {
		for (int c = 0; c<CoresCount[l]; c++) {
			for (int d = 0; d<dscnt; d++) {
				return( Core[l][c]->coreLog[d]->SaveRun(DebugParms, pHistoryLen) );
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


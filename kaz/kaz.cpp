//#include <MyOraUtils.h>
//#include <DBConnection.h>
//#include <MyLogDefs.h>



/*int main() {

	tDebugInfo Debugpnames;
	Debugpnames.DebugLevel = 1;
	Debugpnames.DebugDest = LOG_TO_TEXT;
	strcpy(Debugpnames.fPath, "C:/temp");
	strcpy(Debugpnames.fName, "kaz.log");

	tDBConnection DBconn;
	strcpy(DBconn.DBUser, "History");
	strcpy(DBconn.DBPassword, "HistoryPwd");
	strcpy(DBconn.DBConnString, "Algo");
	DBconn.DBCtx = nullptr;

	char* vOH = getenv("ORACLE_HOME");
	char* vPath = getenv("PATH");
	printf("ORACLE_HOME=%s\nPATH=%s\n", vOH,vPath);

	if (OraConnect(&Debugpnames, &DBconn) <0) return -1;

	getchar();
    return 0;
}
*/

#include <MyUtils.h>

/*static float CalculateCPULoad(unsigned long long idleTicks, unsigned long long totalTicks)
{
	static unsigned long long _previousTotalTicks = 0;
	static unsigned long long _previousIdleTicks = 0;

	unsigned long long totalTicksSinceLastTime = totalTicks-_previousTotalTicks;
	unsigned long long idleTicksSinceLastTime = idleTicks-_previousIdleTicks;

	float ret = 1.0f-((totalTicksSinceLastTime > 0) ? ((float)idleTicksSinceLastTime)/totalTicksSinceLastTime : 0);

	_previousTotalTicks = totalTicks;
	_previousIdleTicks = idleTicks;
	return ret;
}

static unsigned long long FileTimeToInt64(const FILETIME & ft) { return (((unsigned long long)(ft.dwHighDateTime))<<32)|((unsigned long long)ft.dwLowDateTime); }

// Returns 1.0f for "CPU fully pinned", 0.0f for "CPU idle", or somewhere in between
// You'll need to call this at regular intervals, since it measures the load between
// the previous call and the current one.  Returns -1.0 on error.
float GetCPULoad()
{
	FILETIME idleTime, kernelTime, userTime;
	return GetSystemTimes(&idleTime, &kernelTime, &userTime) ? CalculateCPULoad(FileTimeToInt64(idleTime), FileTimeToInt64(kernelTime)+FileTimeToInt64(userTime)) : -1.0f;
}
*/

typedef struct sHogParms {
	int id;
} tHogParms;

void cpuHog(tHogParms* parms) {
	for (int i = 0; i<30000000; i++) {
		gotoxy(0, parms->id);
		printf("\r%d: %d", parms->id, i);
	}
}

#include <thread>
using namespace std;

/*int main() {
	HANDLE th;
	LPDWORD tid=0;
	const int MaxThreads = 10;
	const float MaxCPU = 0.6f;
	int i = 0;
	tHogParms* parms= new tHogParms;

	float cpuusage=0;
	printf("\n");
	while (cpuusage<MaxCPU && i<MaxThreads) {
		cpuusage = GetCPULoad();
		printf("\rCPU Usage: %f", cpuusage);
		Sleep(1000);
		parms->id = i;
		th = CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE)cpuHog, &parms, 0, tid);

		i++;
	}

}
*/

/*int main() {
	char* low = "giacomo";
	char* upp = strdup(low);
	printf("low=%s ; upp=%s\n", low, upp);
	getchar();
}
*/

#include <vector>
#include <string>
#include <iostream>

using namespace std;

typedef struct sParm {
	string			name;
	vector<string>	sval;
	vector<int>		ival;
	vector<double>	dval;
} tParm;


int getVarCnt(vector<tParm> parm, int parmid) {
	if (parm[parmid].sval.size()>0) return (int)parm[parmid].sval.size();
	if (parm[parmid].ival.size()>0) return (int)parm[parmid].ival.size();
	if (parm[parmid].dval.size()>0) return (int)parm[parmid].dval.size();
	return -1;
}

string getVarVal(vector<tParm> parm, int parmid, int varid) {
	if (parm[parmid].sval.size()>0) return parm[parmid].sval[varid];
	if (parm[parmid].ival.size()>0) return to_string(parm[parmid].ival[varid]);
	if (parm[parmid].dval.size()>0) return to_string(parm[parmid].dval[varid]);
	return "";
}

string buildCmd(vector<tParm> parm, int* varIdx) {
	string s;

	for (int p = 0; p<parm.size(); p++) {
		s = s+" --"+parm[p].name+"="+getVarVal(parm, p, varIdx[p]);
	}

	return s;
}

void getCmd(vector<tParm> parm, int* varCnt, int* varIdx, int parmid, vector<string> &cmd) {

	if (varIdx[parmid]>=varCnt[parmid]-1) {
		parmid--; if (parmid<0) return;
		varIdx[parmid]++;
		if (varIdx[parmid]==varCnt[parmid]) getCmd(parm, varCnt, varIdx, parmid, cmd);
		for (int p = parmid+1; p<parm.size(); p++) varIdx[p] = 0;	// reset down
		parmid = (int)parm.size()-1;
	} else {
		varIdx[parmid]++;
	}

	if (varIdx[0]<varCnt[0]) {
		cmd.push_back(buildCmd(parm, varIdx));
		getCmd(parm, varCnt, varIdx, parmid, cmd);
	}
}

void main() {

	vector<string> cmd;
	vector<tParm> parm;

	tParm p;
	//p = { "Forecaster.Engine",{ "ENGINE_SVM" },{},{} };	parm.push_back(p);
	p = { "DataParms.HistoryLen",{},{ 200, 500, 1000 },{} }; parm.push_back(p);
	p = { "DataParms.SampleLen",{},{ 24,100 },{} }; parm.push_back(p);
	p = { "DataParms.PredictionLen",{},{ 3 },{} }; parm.push_back(p);
	p = { "DataParms.DataTransformation",{ "DT_DELTA","DT_DELTALOG" },{},{} }; parm.push_back(p);
	p = { "SVMInfo.C",{},{ 5, 10, 15 },{} }; parm.push_back(p);
	p = { "SVMInfo.epsilon",{},{},{ 0.01, 0.001 } }; parm.push_back(p);
	p = { "SVMInfo.KernelType",{ "KERNEL_TYPE_RBF", "KERNEL_TYPE_LINEAR" },{},{} }; parm.push_back(p);
	p = { "SVMInfo.RBFGamma",{},{},{ 0.1, 0.01 } }; parm.push_back(p);
	//p = { "NNInfo.LevelRatios",{ "0.5", "1", "1,0.5", "0.5,1", "1,1" },{},{} }; parm.push_back(p);
	//p = { "NNInfo.UseContext",{},{ 0, 1 },{} }; parm.push_back(p);
	//p = { "NNInfo.MaxEpochs",{},{ 1000, 3000 },{} }; parm.push_back(p);
	//p = { "NNInfo.LearningRate",{},{},{ 0.1, 0.05, 0.01 } }; parm.push_back(p);
	//p = { "NNInfo.LearningMomentum",{},{},{ 1, 0.5, 0.8 } }; parm.push_back(p);

	int* varCnt = (int*)malloc(parm.size()*sizeof(int));
	int* varIdx = (int*)malloc(parm.size()*sizeof(int));

	for (int p = 0; p<parm.size(); p++) {
		varCnt[p] = getVarCnt(parm, p);
		varIdx[p] = 0;
	}

	cmd.push_back(buildCmd(parm, varIdx));
	getCmd(parm, varCnt, varIdx, (int)parm.size()-1, cmd);
	
	cout<<"Completed. "<<cmd.size()<<" commands created.";
	getchar();
}


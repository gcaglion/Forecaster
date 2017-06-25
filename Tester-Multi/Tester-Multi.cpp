#include <vector>
#include <string>
#include <iostream>
#include <Windows.h>
#include <MyUtils.h>

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
	}
	else {
		varIdx[parmid]++;
	}

	if (varIdx[0]<varCnt[0]) {
		cmd.push_back(buildCmd(parm, varIdx));
		getCmd(parm, varCnt, varIdx, parmid, cmd);
	}
}

vector<string> getCmdList() {
	const int MAX_LINELEN = 4096;
	const int MAX_PARAMNAMELEN = 256;
	const int MAX_PARAMTYPELEN = 8;
	const int MAX_PARAMVALLEN = 64;
	const int MAX_VARIANTS = 12;
	const int MAX_PARAMVALTOTLEN = MAX_PARAMVALLEN*MAX_VARIANTS;
	const char SEPARATOR = 124;
	int vCnt;
	FILE* fComb; FILE* ftmp;

	vector<string> cmd;
	vector<tParm> parm;
	tParm* p;
	int parmid = 0;

	fComb = fopen("TesterCombinations.ini", "r");
	if (fComb==NULL) return{ "","" };
	char vline[MAX_LINELEN];
	char pname[MAX_PARAMNAMELEN];
	char ptype[MAX_PARAMTYPELEN];
	char pval[MAX_PARAMVALTOTLEN];
	char** subP = (char**)malloc(MAX_VARIANTS * sizeof(char*)); for (int i = 0; i<MAX_VARIANTS; i++) subP[i] = (char*)malloc(MAX_PARAMVALLEN);

	//-- create a comments.free version of the file
	ftmp = fopen("TesterCombinations.tmp", "w");
	while (fgets(vline, MAX_LINELEN, fComb)!=NULL) {
		if ((vline[0]=='/' && vline[1]=='/') || (vline[0]=='\n') ) continue;
		fprintf(ftmp, vline);
	}
	fclose(fComb); fclose(ftmp);
	ftmp = fopen("TesterCombinations.tmp", "r");

	while (fscanf(ftmp, "%s %s %[^\n] ", &pname[0], &ptype[0], &pval[0]) >0) {
		Trim(pname); UpperCase(pname);
		Trim(ptype); UpperCase(ptype);
		Trim(pval); UpperCase(pval);
		vCnt = cslToArray(pval, SEPARATOR, subP);

		p = new tParm();
		p->name = pname;
		for (int v = 0; v<vCnt; v++) {
			if (strcmp(ptype, "INT")==0) {
				p->ival.push_back( atoi(subP[v]) );
			}
			else if (strcmp(ptype, "DOUBLE")==0) {
				p->dval.push_back( atof(subP[v]) );
			}
			else if (strcmp(ptype, "STRING")==0) {
				p->sval.push_back( subP[v] );
			}
		}
		parm.push_back((*p));
	}
	fclose(ftmp);

	/*//p = { "Forecaster.Engine",{ "ENGINE_SVM" },{},{} };	parm.push_back(p);
	p = { "DataParms.HistoryLen",{},{ 200, 500, 1000 },{} }; parm.push_back(p);
	p = { "DataParms.SampleLen",{},{ 24,100 },{} }; parm.push_back(p);
	p = { "DataParms.PredictionLen",{},{ 3 },{} }; parm.push_back(p);
	p = { "DataParms.DataTransformation",{ "DT_DELTA","DT_DELTALOG" },{},{} }; parm.push_back(p);
	//p = { "SVMInfo.C",{},{ 5, 10, 15 },{} }; parm.push_back(p);
	//p = { "SVMInfo.epsilon",{},{},{ 0.01, 0.001 } }; parm.push_back(p);
	//p = { "SVMInfo.KernelType",{ "KERNEL_TYPE_RBF", "KERNEL_TYPE_LINEAR" },{},{} }; parm.push_back(p);
	//p = { "SVMInfo.RBFGamma",{},{},{ 0.1, 0.01 } }; parm.push_back(p);
	p = { "NNInfo.LevelRatios",{ "0.5", "1", "1,0.5", "0.5,1", "1,1" },{},{} }; parm.push_back(p);
	p = { "NNInfo.UseContext",{},{ 0, 1 },{} }; parm.push_back(p);
	p = { "NNInfo.MaxEpochs",{},{ 1000, 3000 },{} }; parm.push_back(p);
	p = { "NNInfo.LearningRate",{},{},{ 0.1, 0.05, 0.01 } }; parm.push_back(p);
	p = { "NNInfo.LearningMomentum",{},{},{ 1, 0.5, 0.8 } }; parm.push_back(p);
*/
	int* varCnt = (int*)malloc(parm.size()*sizeof(int));
	int* varIdx = (int*)malloc(parm.size()*sizeof(int));

	for (int p = 0; p<parm.size(); p++) {
		varCnt[p] = getVarCnt(parm, p);
		varIdx[p] = 0;
	}

	cmd.push_back(buildCmd(parm, varIdx));
	getCmd(parm, varCnt, varIdx, (int)parm.size()-1, cmd);

	//cout<<"Completed. "<<cmd.size()<<" commands created.";
	//getchar();

	free(varCnt); free(varIdx);
	return cmd;
}


bool createProcess(int id, string cmd, PROCESS_INFORMATION* pi) {

	STARTUPINFO si;
	ZeroMemory(&si, sizeof(si));
	ZeroMemory(pi, sizeof((*pi)));

	DWORD CreationFlags = CREATE_NEW_CONSOLE;
	DWORD WindowFlags = STARTF_USESIZE || STARTF_USEPOSITION || STARTF_USESHOWWINDOW;
	si.cb = sizeof(si);
	si.dwFlags = WindowFlags;
	si.lpTitle = new wchar_t[20]; wsprintf(si.lpTitle, L"%d", id);
	si.dwX = 200; si.dwY = 50*id;
	si.dwXSize = 80; si.dwYSize = 30;
	si.wShowWindow = SW_SHOW;

	if (
		CreateProcess(NULL,   // No module name (use command line)
			convertCharArrayToLPCWSTR(cmd.c_str()), // Command line
			NULL,           // Process handle not inheritable
			NULL,           // Thread handle not inheritable
			FALSE,          // Set handle inheritance to FALSE
			CreationFlags,
			NULL,           // Use parent's environment block
			NULL,           // Use parent's starting directory 
			&si,            // Pointer to STARTUPINFO structure
			pi)           // Pointer to PROCESS_INFORMATION structure
		) {
		return true;
	}
	else {
		return false;
	}
}

bool isRunning(PROCESS_INFORMATION pi, LPDWORD lasterror) {
	DWORD ret;
	if (!GetExitCodeProcess(pi.hProcess, &ret)) {
		printf("Could not get Process status...\n");
		getchar();
	}
	lasterror = &ret;
	return(ret==STILL_ACTIVE);
}

void main(int argc, char* argv[]) {
	int MaxProcs = 3; if (argc>1) MaxProcs = atoi(argv[1]);

	//string cmdBase = "C:\\Users\\gcaglion\\Documents\\dev\\Forecaster\\x64\\Debug\\cpuhog.exe ";
	//vector<string> cmdParms = { "1 50000", "2 50000", "3 50000", "4 50000", "5 50000", "6 50000" , "7 50000" , "8 50000" };
	string cmdBase = "tester.exe --Forecaster.PauseOnError=0 ";
	vector<string> cmdParms = getCmdList();

	vector<string> cmd;
	int cmdCnt = (int)cmdParms.size();

	int consoleId = 0;
	int consoleCnt = 0;
	vector<string> consoleCmd(MaxProcs);

	PROCESS_INFORMATION* pi = (PROCESS_INFORMATION*)malloc(cmdCnt*sizeof(PROCESS_INFORMATION));
	HANDLE* h = (HANDLE*)malloc(MaxProcs*sizeof(HANDLE)); for (int i = 0; i<MaxProcs; i++) h[i] = NULL;
	int retW;
	DWORD exitCode;
	int i, c;

	FILE* procLog=fopen("Tester-multi.log","w");

	for (c = 0; c<cmdCnt; c++) {
		cmd.push_back(cmdBase+cmdParms[c]);

		
		for (i = 0; i<MaxProcs; i++) {
			if (h[i]==NULL) break;
		}
		consoleId = i;

		//printf("consoleId=%d ; starting new console\n", consoleId);
		consoleCmd[consoleId] = cmd[c];
		if (!createProcess(c, cmd[c], &pi[c])) continue;
		h[consoleId] = pi[c].hProcess; //fprintf(procLog, "h[%d]=%p\n", consoleId, h[consoleId]);
		consoleCnt++;

		if (consoleCnt==(MaxProcs)) {
			retW = (int)WaitForMultipleObjects(MaxProcs, h, false, INFINITE)+WAIT_OBJECT_0;
			GetExitCodeProcess(h[retW], &exitCode);
			printf("CombinationId=%d ; exitCode=%d ; parameters=%s\n", c, exitCode, consoleCmd[retW].c_str());
			fprintf(procLog, "CombinationId=%d ; exitCode=%d ; parameters=%s\n", c, exitCode, consoleCmd[retW].c_str());
			h[retW] = NULL;
			consoleCnt--;
		}
	}

	fprintf(procLog, "\n");
	//- last remaining processes
	while (consoleCnt>0) {
		retW = (int)WaitForMultipleObjects(consoleCnt, h, false, INFINITE)+WAIT_OBJECT_0;
		if (retW!=-1) {
			GetExitCodeProcess(h[retW], &exitCode);
			printf("CombinationId=%d ; exitCode=%d ; parameters=%s\n", c, exitCode, consoleCmd[retW].c_str());
			fprintf(procLog, "CombinationId=%d ; exitCode=%d ; parameters=%s\n", c, exitCode, consoleCmd[retW].c_str());
		}
		consoleCnt--;
		c++;
	}

	//system("pause");
	fclose(procLog);
}

//						

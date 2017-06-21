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
	}
	else {
		varIdx[parmid]++;
	}

	if (varIdx[0]<varCnt[0]) {
		cmd.push_back(buildCmd(parm, varIdx));
		getCmd(parm, varCnt, varIdx, parmid, cmd);
	}
}

void RPmain() {

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


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

#include <Windows.h>
#include <vector>
#include <string>
using namespace std;
#include <stdio.h>


/*int main() {
	HANDLE th;
	LPDWORD tid=0;
	const float MaxCPU = 0.6f;
	int i = 0;
	tHogParms* parms= new tHogParms;

	float CPUload = GetCPULoad();

	vector<string> cmd = { "start cpuhog.exe","start cpuhog.exe","start cpuhog.exe","start cpuhog.exe","start cpuhog.exe","start cpuhog.exe","start cpuhog.exe","start cpuhog.exe","start cpuhog.exe","start cpuhog.exe","start cpuhog.exe","start cpuhog.exe","start cpuhog.exe","start cpuhog.exe","start cpuhog.exe","start cpuhog.exe" };

	while (CPUload<MaxCPU && i<cmd.size() ) {
		system(cmd[i].c_str());
		Sleep(500);
		CPUload = GetCPULoad(); printf("CPU Load=%f\n", CPUload);
	}
}
*/

/*int main() {
	tHogParms* hp=new tHogParms; hp->id = 0;
	cpuHog(hp);
}
*/

vector<string> RPmain();
bool createProcess(string cmd, PROCESS_INFORMATION* pi) {

	STARTUPINFO si;
	ZeroMemory(&si, sizeof(si));
	si.cb = sizeof(si);
	ZeroMemory(pi, sizeof((*pi)));

	DWORD winprops = STARTF_USEPOSITION || STARTF_USESHOWWINDOW;
	si.dwFlags = winprops;
	si.lpTitle = L"Window Title?";
	si.dwX = 100; si.dwY = 100;
	si.dwXSize = 200; si.dwYSize = 30;
	si.wShowWindow = SW_SHOW;

	return(
		CreateProcess(NULL,   // No module name (use command line)
		convertCharArrayToLPCWSTR(cmd.c_str()), // Command line
		NULL,           // Process handle not inheritable
		NULL,           // Thread handle not inheritable
		FALSE,          // Set handle inheritance to FALSE
		0,              // No creation flags
		NULL,           // Use parent's environment block
		NULL,           // Use parent's starting directory 
		&si,            // Pointer to STARTUPINFO structure
		pi)           // Pointer to PROCESS_INFORMATION structure
		);

}

bool isRunning(PROCESS_INFORMATION pi){
	DWORD ret;
	if (!GetExitCodeProcess(pi.hProcess, &ret)) {
		printf("Could not get Process status...\n");
		getchar();
	}
	return(ret==STILL_ACTIVE);
}

void main(int argc, char* argv[] ) {

	int MaxProcs = 2; if (argc>1) MaxProcs = atoi(argv[1]);
	vector<PROCESS_INFORMATION> runningPid;

	vector<string> cmd = RPmain();
	PROCESS_INFORMATION pi;

	while (cmd.size()>0) {
		if (runningPid.size()<MaxProcs) {
			if(createProcess("tester.exe --IniFile=C:\\Users\\gcaglion\\Documents\\dev\\Forecaster\\Tester\\Tester.ini "+cmd[cmd.size()-1], &pi)){
				runningPid.push_back(pi);
				cmd.pop_back();
			} else {
				printf("CreateProcess failed (%d).\n", GetLastError());
				break;
			}
		}
		for (int i = 0; i<runningPid.size(); i++) {
			if (!isRunning(runningPid[i])) {
				runningPid.erase(runningPid.begin()+i);
			}
		}
	}

}

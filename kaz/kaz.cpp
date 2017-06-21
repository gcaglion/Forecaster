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

int main() {
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


/*int main() {
	tHogParms* hp=new tHogParms; hp->id = 0;
	cpuHog(hp);
}
*/


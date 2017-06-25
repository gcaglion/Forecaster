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
	int duration;
} tHogParms;

int cpuHog(tHogParms* parms) {
	//--
	LARGE_INTEGER frequency;			// ticks per second
	LARGE_INTEGER time_start, time_end; // ticks
	double elapsedTime = 0; char elapsedTimeS[30];
	// get ticks per second
	QueryPerformanceFrequency(&frequency);
	// start timer
	QueryPerformanceCounter(&time_start);
	//--

	for (int i = 0; i<parms->duration; i++) {
		gotoxy(0, parms->id);
		printf("\r%d: %d", parms->id, i);
	}

	//-- introduce failure for odd ids
	if (parms->id%2==1) return -1;

	//-- stop timer, compute the elapsed time
	QueryPerformanceCounter(&time_end);
	elapsedTime = (time_end.QuadPart - time_start.QuadPart) * 1000.0 / frequency.QuadPart;
	ms2ts(elapsedTime, elapsedTimeS);
	printf("\nCompleted in %s ", elapsedTimeS);
	//Sleep(5000);
	return 1;
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

int main(int argc, char* argv[]) {
	tHogParms* hp=new tHogParms;
	hp->id = (argc>1) ? atoi(argv[1]) : 1;
	hp->duration = (argc>2) ? atoi(argv[2]) : 1000000;
	return (cpuHog(hp) );
}


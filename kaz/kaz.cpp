//#include <MyOraUtils.h>
//#include <DBConnection.h>
//#include <MyLogDefs.h>



/*int main() {

	tDebugInfo DebugParms;
	DebugParms.DebugLevel = 1;
	DebugParms.DebugDest = LOG_TO_TEXT;
	strcpy(DebugParms.fPath, "C:/temp");
	strcpy(DebugParms.fName, "kaz.log");

	tDBConnection DBconn;
	strcpy(DBconn.DBUser, "History");
	strcpy(DBconn.DBPassword, "HistoryPwd");
	strcpy(DBconn.DBConnString, "Algo");
	DBconn.DBCtx = nullptr;

	char* vOH = getenv("ORACLE_HOME");
	char* vPath = getenv("PATH");
	printf("ORACLE_HOME=%s\nPATH=%s\n", vOH,vPath);

	if (OraConnect(&DebugParms, &DBconn) <0) return -1;

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
int main() {
	printf("\n");
	while (true) {
		printf("\rCPU Usage: %f", GetCPULoad());
		Sleep(1000);
	}
}


/*int main() {
	char* low = "giacomo";
	char* upp = strdup(low);
	printf("low=%s ; upp=%s\n", low, upp);
	getchar();
}
*/
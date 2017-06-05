#include <MyOraUtils.h>
#include <DBConnection.h>
#include <MyLogDefs.h>

int main() {

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


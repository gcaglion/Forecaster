// Database Connection - generic (can be used for both data retrieval and logging)
#pragma once
typedef struct sDBConnection {
	char DBUser[30];
	char DBPassword[30];
	char DBConnString[30];
	void* DBCtx;

#ifdef __cplusplus
	//-- constructor accepting with connection parms
	sDBConnection(char* user, char* pwd, char* connstring) {
		strcpy(DBUser, user);
		strcpy(DBPassword, pwd);
		strcpy(DBConnString, connstring);
	}

	//-- default constructor
	sDBConnection() {

	}
#endif

} tDBConnection;

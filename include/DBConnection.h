// Database Connection - generic (can be used for both data retrieval and logging)
#pragma once
typedef struct sDBConnection{
	char DBUser[30];
	char DBPassword[30];
	char DBConnString[30];
	void* DBCtx;
} tDBConnection;

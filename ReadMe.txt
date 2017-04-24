Train_<XXX>() always saves multiple engines (unique processid, different threadid(s))

When Calling GetForecast() from either MT4 or Tester:
	Allocate Engine[<DatasetsCount>]
	if ENGINE_LOAD,  then set Engine[0] with the Identification params for the desired Engine to load
	if ENGINE_TRAIN, then leave Engine[] empty; it will be filled by Train_XXX()



	============================================================= HEADER FILES =============================================================
	DBConnection.h	: Database Connection - generic (can be used for both data retrieval and logging)	|	defines tDBConnection
	FileData.h		: File Retrieval Properties for File-based DataSources								|	defines tFileData
	FXData.h		: Properties for FX Bars data														|	defines tFXData, tBar
	MyEngines.h		: Defines Engines and Engine Handle													|	defines tEnginHandle
	DataShape.h		: Dataset properties																|	defines tDataShape
	MyLogDefs.h		: Debug and Logging structures, and Debug destinations definitions					|	defines tDebugInfo, tLogMSE, tLogRUN
	========================================================================================================================================

	Call to WriteTestLog() moved from Tester.cpp to MyForecast.cpp

	Tester.exe looks for Tester.ini in current directory

	MT4 Setup:
	create terminal.cmd in the same ProgramFiles(x86) dir as terminal.exe, with the following:
		set ORACLE_HOME=D:\app\oracle\product\11.2.0\dbhome_2
		set PATH=%ORACLE_HOME%\bin
		start /b .\terminal

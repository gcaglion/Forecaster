#include <Engine.h>


EXPORT int getForecast() {
	int engType = ENGINE_WNN; int decompLevel = 4;
	int SampleLen = 24;
	int TargetLen = 5;

	//-- 1. read DataParms and DebugParms from parameters
	//-- 2. read DoTraining
	//-- 3.a if DoTraining, then build engine
	//-- 3.b else, LoadEngineParms

	cEngine* engine = new cEngine(engType, decompLevel, SampleLen, TargetLen);

	//--
	// ... load / get parms
	//
	// ... If InputCount/OutputCount of loaded Engine are different from those in Tester.ini, WE CANNOT CONTINUE
	//--



	return 0;
}
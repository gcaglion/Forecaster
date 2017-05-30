#pragma once

#define SOURCE_DATA_FROM_FXDB 0
#define SOURCE_DATA_FROM_FILE 1
#define SOURCE_DATA_FROM_MT   2

typedef struct sClientParms {
	int SimulationLength;
	char SimulationStart[12+1];
	int DoTraining;
	int HaveFutureData;
} tClientParms;
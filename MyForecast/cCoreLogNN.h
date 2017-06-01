#pragma once
#include <MyCoreLogs.h>

typedef struct sNNIntP {
	int pid;
	int tid;
	//...
	//...
	//...

} tNNIntP;

class cCoreLogNN : public cCoreLog {
public:

	double*** finalW;	// [Level][FromNeuron][ToNeuron]
	tNNIntP*  intP;

	EXPORT int SaveImage(tDebugInfo* DebugParms);

	cCoreLogNN();
	~cCoreLogNN();
};


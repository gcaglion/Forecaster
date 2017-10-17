//#include <vld.h>

#include <MyEnums.h>

//=============== ENUMS ============================
EXPORT int getEnumVal(char* edesc, char* eVal, int* oVal) {
	int ret=-1;

	UpperCase(edesc);

	if(strcmp(edesc, "FORECASTER.ACTION")==0){
		if (strcmp(eVal, "TRAIN_SAVE_RUN")==0) { (*oVal)=TRAIN_SAVE_RUN; ret=0;}
		if (strcmp(eVal, "ADD_SAMPLES")==0) { (*oVal)=ADD_SAMPLES; ret=0;}
		if (strcmp(eVal, "JUST_RUN")==0) { (*oVal)=JUST_RUN; ret=0;}
	}
	else if (strcmp(edesc, "FORECASTER.ENGINE") == 0) {
		if (strcmp(eVal, "ENGINE_NN") == 0) { (*oVal)=ENGINE_NN; ret=0;}
		if (strcmp(eVal, "ENGINE_GA") == 0) { (*oVal)=ENGINE_GA; ret=0;}
		if (strcmp(eVal, "ENGINE_SVM") == 0) { (*oVal)=ENGINE_SVM; ret=0;}
		if (strcmp(eVal, "ENGINE_SOM") == 0) { (*oVal)=ENGINE_SOM; ret=0;}
		if (strcmp(eVal, "ENGINE_WNN") == 0) { (*oVal)=ENGINE_WNN; ret=0;}
		if (strcmp(eVal, "ENGINE_XIE") == 0) { (*oVal)=ENGINE_XIE; ret=0;}
	}
	else if (strcmp(edesc, "RESULTS.DESTINATION") == 0) {
		if (strcmp(eVal, "LOG_TO_TEXT") == 0) { (*oVal)=LOG_TO_TEXT; ret=0;}
		if (strcmp(eVal, "LOG_TO_ORCL") == 0) { (*oVal)=LOG_TO_ORCL; ret=0;}
	}
	else if (strcmp(edesc, "DATASOURCE.SOURCETYPE") == 0) {
		if (strcmp(eVal, "SOURCE_DATA_FROM_FXDB") == 0) { (*oVal)=SOURCE_DATA_FROM_FXDB; ret=0;}
		if (strcmp(eVal, "SOURCE_DATA_FROM_FILE") == 0) { (*oVal)=SOURCE_DATA_FROM_FILE; ret=0;}
		if (strcmp(eVal, "SOURCE_DATA_FROM_MT") == 0) { (*oVal)=SOURCE_DATA_FROM_MT; ret=0;}
	}
	else if (strcmp(edesc, "DATASOURCE.SOURCETYPE") == 0) {
	}
	else if (strcmp(edesc, "DATASOURCE.TEXTFIELDSEPARATOR") == 0) {
		if (strcmp(eVal, "COMMA") == 0) { (*oVal)=(int)COMMA; ret=0;}
		if (strcmp(eVal, "TAB") == 0) { (*oVal)=(int)TAB; ret=0;}
		if (strcmp(eVal, "SPACE") == 0) { (*oVal)=(int)SPACE; ret=0;}
	}
	else if (strcmp(edesc, "DATAPARMS.DATATRANSFORMATION") == 0) {
		if (strcmp(eVal, "DT_NONE") == 0) { (*oVal)=DT_NONE; ret=0;}
		if (strcmp(eVal, "DT_DELTA") == 0) { (*oVal)=DT_DELTA; ret=0;}
		if (strcmp(eVal, "DT_LOG") == 0) { (*oVal)=DT_LOG; ret=0;}
		if (strcmp(eVal, "DT_DELTALOG") == 0) { (*oVal)=DT_DELTALOG; ret=0;}
	}
	else if (strcmp(edesc, "DATASOURCE.BARDATATYPES") == 0) {
		if (strcmp(eVal, "OPEN") == 0) { (*oVal)=OPEN; ret=0;}
		if (strcmp(eVal, "HIGH") == 0) { (*oVal)=HIGH; ret=0;}
		if (strcmp(eVal, "LOW") == 0) { (*oVal)=LOW; ret=0;}
		if (strcmp(eVal, "CLOSE") == 0) { (*oVal)=CLOSE; ret=0;}
		if (strcmp(eVal, "VOLUME") == 0) { (*oVal)=VOLUME; ret=0;}
		if (strcmp(eVal, "OTHER") == 0) { (*oVal)=OTHER; ret=0;}
	}
	else if (strcmp(edesc, "DATAPARMS.TSFEATURES") == 0) {
		if (strcmp(eVal, "TSF_MEAN") == 0) { (*oVal)=TSF_MEAN; ret=0;}
		if (strcmp(eVal, "TSF_MAD") == 0) { (*oVal)=TSF_MAD; ret=0;}
		if (strcmp(eVal, "TSF_VARIANCE") == 0) { (*oVal)=TSF_VARIANCE; ret=0;}
		if (strcmp(eVal, "TSF_SKEWNESS") == 0) { (*oVal)=TSF_SKEWNESS; ret=0;}
		if (strcmp(eVal, "TSF_KURTOSIS") == 0) { (*oVal)=TSF_KURTOSIS; ret=0;}
		if (strcmp(eVal, "TSF_TURNINGPOINTS") == 0) { (*oVal)=TSF_TURNINGPOINTS; ret=0;}
		if (strcmp(eVal, "TSF_SHE") == 0) { (*oVal)=TSF_SHE; ret=0;}
		if (strcmp(eVal, "TSF_HISTVOL") == 0) { (*oVal)=TSF_HISTVOL; ret=0;}
	}
	else if (strcmp(right(edesc, 7), "BP_ALGO") == 0) {
		if (strcmp(eVal, "BP_STD") == 0) { (*oVal)=BP_STD; ret=0;}
		if (strcmp(eVal, "BP_QING") == 0) { (*oVal)=BP_QING; ret=0;}
		if (strcmp(eVal, "BP_SCGD") == 0) { (*oVal) = BP_SCGD; ret = 0; }
		if (strcmp(eVal, "BP_LM") == 0) { (*oVal) = BP_LM; ret = 0; }
		if (strcmp(eVal, "BP_QUICKPROP") == 0) { (*oVal) = BP_QUICKPROP; ret = 0; }
		if (strcmp(eVal, "BP_RPROP") == 0) { (*oVal) = BP_RPROP; ret = 0; }
	}
	else if (strcmp(right(edesc, 18), "ACTIVATIONFUNCTION") == 0) {
		if (strcmp(eVal, "NN_ACTIVATION_TANH") == 0) { (*oVal)=NN_ACTIVATION_TANH; ret=0;}
		if (strcmp(eVal, "NN_ACTIVATION_EXP4") == 0) { (*oVal)=NN_ACTIVATION_EXP4; ret=0;}
	}
	else if (strcmp(edesc, "SOMINFO.TDFUNCTION") == 0) {
		if (strcmp(eVal, "TD_DECAY_CONSTANT") == 0) { (*oVal)=TD_DECAY_CONSTANT; ret=0;}
		if (strcmp(eVal, "TD_DECAY_LINEAR") == 0) { (*oVal)=TD_DECAY_LINEAR; ret=0;}
		if (strcmp(eVal, "TD_DECAY_STEPPED") == 0) { (*oVal)=TD_DECAY_STEPPED; ret=0;}
		if (strcmp(eVal, "TD_DECAY_EXP") == 0) { (*oVal)=TD_DECAY_EXP; ret=0;}
	}
	else if (strcmp(edesc, "SOMINFO.LRFUNCTION") == 0) {
		if (strcmp(eVal, "LR_DECAY_CONSTANT") == 0) { (*oVal)=LR_DECAY_CONSTANT; ret=0;}
		if (strcmp(eVal, "LR_DECAY_LINEAR") == 0) { (*oVal)=LR_DECAY_LINEAR; ret=0;}
		if (strcmp(eVal, "LR_DECAY_STEPPED") == 0) { (*oVal)=LR_DECAY_STEPPED; ret=0;}
		if (strcmp(eVal, "LR_DECAY_EXP") == 0) { (*oVal)=LR_DECAY_EXP; ret=0;}
	}
	else if (strcmp(right(edesc, 10), "KERNELTYPE") == 0) {
		if (strcmp(eVal, "KERNEL_TYPE_LINEAR") == 0) { (*oVal)=KERNEL_TYPE_LINEAR; ret=0;}
		if (strcmp(eVal, "KERNEL_TYPE_POLY") == 0) { (*oVal)=KERNEL_TYPE_POLY; ret=0;}
		if (strcmp(eVal, "KERNEL_TYPE_RBF") == 0) { (*oVal)=KERNEL_TYPE_RBF; ret=0;}
		if (strcmp(eVal, "KERNEL_TYPE_TANH") == 0) { (*oVal)=KERNEL_TYPE_TANH; ret=0;}
		if (strcmp(eVal, "KERNEL_TYPE_CUSTOM") == 0) { (*oVal)=KERNEL_TYPE_CUSTOM; ret=0;}
	}
	else if (strcmp(right(edesc, 9), "SLACKNORM") == 0) {
		if (strcmp(eVal, "SLACK_NORM_L1") == 0) { (*oVal)=SLACK_NORM_L1; ret=0;}
		if (strcmp(eVal, "SLACK_NORM_SQUARED") == 0) { (*oVal)=SLACK_NORM_SQUARED; ret=0;}
	}
	else if (strcmp(right(edesc, 15), "RESCALINGMETHOD") == 0) {
		if (strcmp(eVal, "RESCALING_METHOD_SLACK") == 0) { (*oVal)=RESCALING_METHOD_SLACK; ret=0;}
		if (strcmp(eVal, "RESCALING_METHOD_MARGIN") == 0) { (*oVal)=RESCALING_METHOD_MARGIN; ret=0;}
	}
	else if (strcmp(right(edesc, 12), "LOSSFUNCTION") == 0) {
		if (strcmp(eVal, "LOSS_FUNCTION_ZEROONE") == 0) { (*oVal)=LOSS_FUNCTION_ZEROONE; ret=0;}
	}
	else if (strcmp(right(edesc, 12), "LEARNINGALGO") == 0) {
		if (strcmp(eVal, "LEARNING_ALGO_NSLACK") == 0) { (*oVal)=LEARNING_ALGO_NSLACK; ret=0;}
		if (strcmp(eVal, "LEARNING_ALGO_NSLACK_SHRINK") == 0) { (*oVal)=LEARNING_ALGO_NSLACK_SHRINK; ret=0;}
		if (strcmp(eVal, "LEARNING_ALGO_1SLACK_PRIMAL") == 0) { (*oVal)=LEARNING_ALGO_1SLACK_PRIMAL; ret=0;}
		if (strcmp(eVal, "LEARNING_ALGO_1SLACK_DUAL") == 0) { (*oVal)=LEARNING_ALGO_1SLACK_DUAL; ret=0;}
		if (strcmp(eVal, "LEARNING_ALGO_1SLACK_DUAL_CONSTR") == 0) { (*oVal)=LEARNING_ALGO_1SLACK_DUAL_CONSTR; ret=0;}
		if (strcmp(eVal, "LEARNING_ALGO_CUSTOM") == 0) { (*oVal)=LEARNING_ALGO_CUSTOM; ret=0;}
	}

	return ret;
}
//==================================================

//============ WNN VERSIONS - OBSOLETE ===============
/*
__declspec(dllexport) int __stdcall	ReadParamArrayFromFile(char* pFileName, char* pParamName, int* oParamValue) {
	char vParamValue[1000];
	int i;
	int ArrayLen;
	char** subP = (char**)malloc(MAX_LAYERS * sizeof(char*)); for (i = 0; i<MAX_LAYERS; i++) subP[i] = (char*)malloc(256);

	if (ReadParamFromFile(pFileName, pParamName, &vParamValue[0]) != 0) return -1;
	//-- now, vParamValue has the '|'-separated list of values
	ArrayLen = cslToArray(vParamValue, 124, subP);
	for (i = 0; i<ArrayLen; i++) oParamValue[i] = atoi(subP[i]);

	for (i = 0; i<MAX_LAYERS; i++) free(subP[i]);
	free(subP);
	return 0;
}
__declspec(dllexport) int __stdcall	ReadParamArrayFromFile(char* pFileName, char* pParamName, double* oParamValue) {
	char vParamValue[1000];
	int i;
	int ArrayLen;
	char** subP = (char**)malloc(MAX_LAYERS * sizeof(char*)); for (i = 0; i<MAX_LAYERS; i++) subP[i] = (char*)malloc(256);

	if (ReadParamFromFile(pFileName, pParamName, &vParamValue[0]) != 0) return -1;
	//-- now, vParamValue has the '|'-separated list of values
	ArrayLen = cslToArray(vParamValue, 124, subP);
	for (i = 0; i<ArrayLen; i++) oParamValue[i] = atof(subP[i]);

	for (i = 0; i<MAX_LAYERS; i++) free(subP[i]);
	free(subP);
	return 0;
}
__declspec(dllexport) int __stdcall	ReadParamArrayFromFile(char* pFileName, char* pParamName, char** oParamValue) {
	char vParamValue[1000];
	int i;
	int ArrayLen;
	char** subP = (char**)malloc(MAX_LAYERS * sizeof(char*)); for (i = 0; i<MAX_LAYERS; i++) subP[i] = (char*)malloc(256);

	if (ReadParamFromFile(pFileName, pParamName, &vParamValue[0]) != 0) return -1;
	//-- now, vParamValue has the '|'-separated list of values
	ArrayLen = cslToArray(vParamValue, 124, subP);
	for (i = 0; i<ArrayLen; i++) strcpy(oParamValue[i], subP[i]);

	for (i = 0; i<MAX_LAYERS; i++) free(subP[i]);
	free(subP);
	return 0;
}
*/
//==================================================

/*static int CLparamCount;
static char CLparamName[1000][100];	// 1000 parameters max. Parameter name must bel less than 100 characters long
static char CLparamVal[1000][100];		// 1000 parameters max. Parameter name must bel less than 100 characters long
*/




////#include <vld.h>

#include <MyUtils.h>
#include <MyLogDefs.h>
#include <MyLogger.h>
#include "svm_common.h"
#include "svm_learn.h"
#include <MySVM.h>


int calcSVcnt(MODEL* model) {
	long sv_num = 1;
	for (long i = 1; i<model->sv_num; i++) {
		for (SVECTOR* v = model->supvec[i]->fvec; v; v = v->next)
			sv_num++;
	}
	return sv_num;
}

__declspec(dllexport) void mallocSVMLog(tCoreLog* coreLog, int SVcnt, int slen) {
	//-- mallocs specific portions of coreLog (alphaY, SV). This is not called by MyForecast(), as we can only know the number of SVs after training
	coreLog->SVMFinalW = MallocArray<tSVMWeight>(SVcnt, slen + 1);	// +1 because we save alpha along with vars
	//coreLog->alphaY = MallocArray<double>(SVcnt);
	//coreLog->SV = MallocArray<double>(SVcnt, slen);
}
__declspec(dllexport) void freeSVMLog(tCoreLog* coreLog, int slen) {
	if (coreLog->SVMResult.SVcount > 0) {
		FreeArray(coreLog->SVMResult.SVcount, slen, coreLog->SVMFinalW);
	}
}

void 	SaveFinalV(SVM_Parms* SVMParms, tCoreLog* SVMLog, DWORD pid, DWORD tid, MODEL* model, int pIterationsCount) {
	//-- replaces svm_common::write_model()
	int sv, j;
	SVECTOR* v;

	SVMLog->SVMResult.ProcessId = pid;
	SVMLog->SVMResult.ThreadId = tid;
	SVMLog->SVMResult.Iterations = pIterationsCount;
	SVMLog->SVMResult.SVcount = model->sv_num;
	SVMLog->SVMResult.ThresholdB = model->b;
	SVMLog->SVMResult.maxdiff = model->maxdiff;
	SVMLog->SVMResult.L1loss = model->L1loss;
	SVMLog->SVMResult.WVnorm = (_isnan(model->WVnorm))?-1:model->WVnorm;
	SVMLog->SVMResult.LEVnorm = model->LEVnorm;
	SVMLog->SVMResult.KEvCount = model->KEvCount;

	for (sv = 1; sv<model->sv_num; sv++) {
		for (v = model->supvec[sv]->fvec; v; v = v->next) {
			//-- SV 
			for (j = 0; (v->words[j]).wnum; j++) {
				SVMLog->SVMFinalW[sv][j].ProcessId = pid;
				SVMLog->SVMFinalW[sv][j].ThreadId = tid;
				SVMLog->SVMFinalW[sv][j].SVId = sv;
				SVMLog->SVMFinalW[sv][j].VarId=j;
				SVMLog->SVMFinalW[sv][j].Weight = (double)(v->words[j]).weight;
			}
			//-- alpha is saved at (samplelen+1) position
			SVMLog->SVMFinalW[sv][j].ProcessId = pid;
			SVMLog->SVMFinalW[sv][j].ThreadId = tid;
			SVMLog->SVMFinalW[sv][j].SVId = sv;
			SVMLog->SVMFinalW[sv][j].VarId = j;
			SVMLog->SVMFinalW[sv][j].Weight = model->alpha[sv] * v->factor;
		}
	}

}

int read_documents(int sampleCnt, int sampleLen, double** Sample, double** Target, DOC ***docs, double **label, long int *totwords, long int *totdoc) {
	//-- this overrides original read_documents() in svm_common.c

	char *line, *comment;
	char item[30];
	svmWORD *words;
	long dnum = 0, wpos, dpos = 0, dneg = 0, dunlab = 0, queryid, slackid, max_docs;
	long max_words_doc, ll;
	double doc_label, costfactor;
	//FILE *docfl;

	max_docs = sampleCnt;
	ll = 50*sampleLen;	//-- totally arbitrary ??
	max_words_doc = 3 * sampleLen*sampleCnt;	//-- totally arbitrary ??

	//nol_ll(docfile, &max_docs, &max_words_doc, &ll); /* scan size of input file */
	max_words_doc += 2;
	ll += 2;
	max_docs += 2;

	(*docs) = (DOC **)malloc(sizeof(DOC *)*max_docs);    /* feature vectors */
	(*label) = (double *)malloc(sizeof(double)*max_docs); /* target values */
	line = (char *)malloc(sizeof(char)*ll);
	words = (svmWORD *)malloc(sizeof(svmWORD)*(max_words_doc + 10));

	dnum = 0;
	(*totwords) = 0;
	//--
	for(int s=0; s<sampleCnt; s++){
		sprintf(item, "%f", Target[s][0]);
		strcpy(line, item);
		for (int i = 0; i < sampleLen; i++) {
			sprintf(item, " %d:%f", i+1, Sample[s][i]);
			strcat(line, item);
		}
		strcat(line, "\n");

	//while ((!feof(docfl)) && fgets(line, (int)ll, docfl)) {
		//if (line[0] == '#') continue;  /* line contains comments */
		if (!parse_document(line, words, &doc_label, &queryid, &slackid, &costfactor, &wpos, max_words_doc, &comment)) {
			printf("\nParsing error in line %ld!\n%s", dnum, line);
			return -1;
		}
		(*label)[dnum] = doc_label;
		/* printf("docnum=%ld: Class=%f ",dnum,doc_label); */
		if (doc_label > 0) dpos++;
		if (doc_label < 0) dneg++;
		if (doc_label == 0) dunlab++;
		if ((wpos>1) && ((words[wpos - 2]).wnum>(*totwords))) (*totwords) = (words[wpos - 2]).wnum;
		if ((*totwords) > MAXFEATNUM) {
			printf("\nMaximum feature number exceeds limit defined in MAXFEATNUM!\n");
			printf("LINE: %s\n", line);
			return -1;
		}
		(*docs)[dnum] = create_example(dnum, queryid, slackid, costfactor, create_svector(words, comment, 1.0));
		/* printf("\nNorm=%f\n",((*docs)[dnum]->fvec)->twonorm_sq);  */
		dnum++;
	}

	free(line);
	free(words);
	(*totdoc) = dnum;
	return 0;
}

void CastSVMParms(SVM_Parms* in, LEARN_PARM* lout, KERNEL_PARM* kout) {

	if (lout != NULL) {

		lout->eps = in->epsilon;
		lout->svm_c = in->C;
		lout->sharedslack = 0;
		lout->svm_iter_to_shrink = in->svmIterToShrink;
		lout->maxiter = in->MaxEpochs;

		strcpy(lout->alphafile, "");
		lout->biased_hyperplane = 1;
		lout->compute_loo = 0;
		lout->epsilon_a = 1E-10;
		//lout->epsilon_const=
		lout->epsilon_crit = 0.001;
		//lout->epsilon_shrink=
		lout->kernel_cache_size = 40;
		//lout->opt_precision = ;
		strcpy(lout->predfile, "trans_predictions");
		lout->remove_inconsistent = 0;
		lout->rho = 1.0;
		//lout->sharedslack = ;
		lout->skip_final_opt_check = 0;
		//lout->svm_cost = ;
		lout->svm_costratio = 1.0;
		lout->svm_costratio_unlab = 1.0;
		//lout->svm_c_factor = ;
		//lout->svm_c_steps = ;
		//lout->svm_iter_to_shrink = 100;
		lout->svm_maxqpsize = 10;
		lout->svm_newvarsinqp = 0;
		lout->svm_unlabbound = 1E-5;
		lout->transduction_posratio = -1.0;
		lout->xa_depth = 0;
	}

	if (kout != NULL) {
		kout->kernel_type = in->KernelType;
		kout->coef_const = in->CoefConst;
		kout->coef_lin = in->CoefLin;
		strcpy(kout->custom, in->CustomKernel);
		//kout->gram_matrix=in->
		kout->kernel_type = in->KernelType;
		kout->poly_degree = in->PolyDegree;
		kout->rbf_gamma = in->RBFGamma;
	}

}

void buildSVMsample(int sLen, double* S, double* T, char* oLine) {
	char s[20];
	//strcpy(oLine, "0");	// target value
	sprintf(oLine, "%f", T[0]);	// target value
	for (int i = 0; i < sLen; i++) {
		sprintf(s, " %d:%f", i + 1, S[i]);
		strcat(oLine, s);
	}
	strcat(oLine, "\n");
}

double SVMPredict(char* sample, int ktype, long max_words_doc, MODEL* model, svmWORD* words) {
	DOC* doc;
	double doc_label, costfactor;
	long queryid, slackid, wnum;
	char* comment;
	//--
	double pred;

	if (parse_document(sample, words, &doc_label, &queryid, &slackid, &costfactor, &wnum, max_words_doc, &comment) < 0) {
		printf("Press any key..."); getchar();;
		return -1;
	}
	doc = create_example(-1, 0, 0, 0.0, create_svector(words, comment, 1.0));
	if (ktype == KERNEL_TYPE_LINEAR) {
		pred = classify_example_linear(model, doc);
	}
	else {
		pred = classify_example(model, doc);
	}
	free_example(doc, 1);

	return pred;
}

__declspec(dllexport) int Train_SVM(int pCorePos, int pTotCores, HANDLE pScreenMutex, tDebugInfo* pDebugParms, SVM_Parms* pSVMParms, tCoreLog* pSVMLogs, int pSampleCount, double** pSampleData, double** pTargetData, int useValidation, double** pSampleDataV, double** pTargetDataV) {

	int i;
	//--
	DOC **docs;  /* training examples */
	long totwords, totdoc;
	double *target;
	double *alpha_in = NULL;
	KERNEL_CACHE *kernel_cache;
	LEARN_PARM learn_parm;
	KERNEL_PARM kernel_parm;
	MODEL *model = (MODEL *)malloc(sizeof(MODEL));
	//--
	int pid = GetCurrentProcessId();
	int tid = GetCurrentThreadId();
	//--

	int vSampleLen = pSVMParms->InputCount;	//=== ARE WE SURE ??? ===

	//-- epoch/MSE -> Iteration/maxdiff
	int vIterationsCount;
	double* vMSE = MallocArray<double>(pSVMParms->MaxEpochs);
	//--

	//-- read input parameters
	CastSVMParms(pSVMParms, &learn_parm, &kernel_parm);
	learn_parm.type = REGRESSION;
	set_verbosity(pSVMParms->DebugLevel);

	//-- read the training examples
	read_documents(pSampleCount, pSVMParms->InputCount, pSampleData, pTargetData, &docs, &target, &totwords, &totdoc);

	//-- START MAIN ALGORITHM
	if (kernel_parm.kernel_type == LINEAR) { /* don't need the cache */
		kernel_cache = NULL;
	} else {
		kernel_cache = kernel_cache_init(totdoc, learn_parm.kernel_cache_size);
	}

	svm_learn_regression(docs, target, totdoc, totwords, &learn_parm, &kernel_parm, &kernel_cache, model, 1, &vIterationsCount, pSVMParms->MaxEpochs, vMSE);

	if (kernel_cache) kernel_cache_cleanup(kernel_cache);

	//-- save Support Vectors in coreLog
	mallocSVMLog(pSVMLogs, calcSVcnt(model), pSVMParms->InputCount);
	SaveFinalV(pSVMParms, pSVMLogs, pid, tid, model, vIterationsCount);

	//-- Save MSE Data: Iteration/MaxDiff -> epoch/MSE
	pSVMLogs->ActualEpochs = vIterationsCount;
	for (i = 0; i < vIterationsCount; i++) SaveMSEData(pSVMLogs, pid, tid, i, vMSE[i], NULL);
	//--

	free(vMSE);
	free_model(model, 0);
	free(alpha_in);
	for (i = 0; i<totdoc; i++) free_example(docs[i], 1);
	free(docs);
	free(target);

	return 0;
}

__declspec(dllexport) int Run_SVM(tDebugInfo* pDebugParms, SVM_Parms* SVMParms, tCoreLog* SVMLogs, tDataShape* pInputData, int pid, int tid, int pSampleCount, double** pSample, double** pTarget) {
	MODEL *Mymodel = (MODEL *)malloc(sizeof(MODEL));
	//--
	double vActual, MyPrediction;
	int s, i;
	int vSampleLen = SVMParms->InputCount;	//=== ARE WE SURE ??? ===
	double* tmpSample = MallocArray<double>(vSampleLen);
	char* SVMsample = (char*)malloc(20 * pSampleCount);
	//-- read model
	svmWORD* words = MallocArray<svmWORD>(vSampleLen+10);

	Mymodel->kernel_parm.kernel_type = SVMParms->KernelType;
	Mymodel->kernel_parm.poly_degree = SVMParms->PolyDegree;
	Mymodel->kernel_parm.rbf_gamma = SVMParms->RBFGamma;
	Mymodel->kernel_parm.coef_lin = SVMParms->CoefLin;
	Mymodel->kernel_parm.coef_const = SVMParms->CoefConst;
	//strcpy(Mymodel->kernel_parm.custom, SVMParms->CustomKernel);
	strcpy(Mymodel->kernel_parm.custom, "");
	//--
	Mymodel->totwords = vSampleLen;
	Mymodel->totdoc = 2*pSampleCount;
	Mymodel->sv_num = SVMLogs->SVMResult.SVcount;
	Mymodel->b = SVMLogs->SVMResult.ThresholdB;
	//--
	Mymodel->supvec= (DOC **)malloc(sizeof(DOC *)*Mymodel->sv_num+2);
	Mymodel->alpha = (double *)malloc(sizeof(double)*Mymodel->sv_num+2);
	Mymodel->index = NULL;
	Mymodel->lin_weights = NULL;
	//--

	for (int sv = 1; sv < SVMLogs->SVMResult.SVcount; sv++) {
		for (int i = 0; i < vSampleLen; i++) {
			words[i].wnum = i+1;
			words[i].weight = (float)SVMLogs->SVMFinalW[sv][i].Weight;
		}
		words[vSampleLen].wnum = 0;
		Mymodel->supvec[sv] = create_example(-1, 0, 0, 0.0, create_svector(words, "blah", 1.0));
		Mymodel->alpha[sv] = SVMLogs->SVMFinalW[sv][vSampleLen].Weight;
	}
	//--

	//-- 0.1 if linear kernel, compute weight vector
	if (Mymodel->kernel_parm.kernel_type == 0) add_weight_vector_to_linear_model(Mymodel);

	//-- 1. Write First window of data, with no prediction (that is, write the first sample)
	for (i = 0; i<SVMParms->InputCount; i++) SaveRunData(SVMLogs, pid, tid, i, pSample[0][i], NULL);

	//-- 2. Write Training Set data, with next-step prediction

	//-- 2.1 in-sample
	for (s = 0; s < pSampleCount; s++) {
		vActual = pTarget[s][0];

		for (i = 0; i<SVMParms->InputCount; i++) tmpSample[i] = pSample[s][i];	//-- Only used for the last sample ( pSample[pSampleCount-1] )

		buildSVMsample(vSampleLen, pSample[s], pTarget[s], SVMsample);
		MyPrediction = SVMPredict(SVMsample, SVMParms->KernelType, vSampleLen, Mymodel, words);

		SaveRunData(SVMLogs, pid, tid, SVMParms->InputCount + s, vActual, &MyPrediction);
	}

	//-- 2.2 out-of-sample
	for (s = 0; s < pInputData->PredictionLen; s++) {

		// Target[s] only exist while s<SampleCount. Beyond that, Actual is prediction from previous step
		vActual = MyPrediction;

		//-- Sample beyond SampleCount must be build, regardless of pOOS
		ShiftArray(SHIFT_BACKWARD, SVMParms->InputCount, tmpSample, vActual);

		buildSVMsample(vSampleLen, tmpSample, pTarget[s], SVMsample);
		MyPrediction = SVMPredict(SVMsample, SVMParms->KernelType, vSampleLen, Mymodel, words);

		SaveRunData(SVMLogs, pid, tid, (s + pSampleCount + SVMParms->InputCount), vActual, &MyPrediction);
	}

	if (Mymodel->kernel_parm.kernel_type == 0) free(Mymodel->lin_weights);
	for (int sv = 1; sv < SVMLogs->SVMResult.SVcount; sv++) {
		free(Mymodel->supvec[sv]->fvec->words);
		free(Mymodel->supvec[sv]->fvec->userdefined);
		free(Mymodel->supvec[sv]->fvec);
		free(Mymodel->supvec[sv]);
	}
	free(Mymodel->supvec);
	free(Mymodel->alpha);
	free(Mymodel);
	free(SVMsample);
	free(tmpSample);
	free(words);

	return 0;
}

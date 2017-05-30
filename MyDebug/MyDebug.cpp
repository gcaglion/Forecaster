#include <MyDebug.h>

EXPORT void LogWrite(tDebugInfo* DebugParms, int LogType, char* msg, int argcount, ...) {
	// pLogLevel=	0 (No screen, No file) | 1 (Screen, No file) | 2 (Screen AND File)
	int n;
	char*			arg_s;
	int				arg_d;
	double			arg_f;
	va_list			arguments;
	char submsg[MAX_PATH];
	unsigned int	im = 0;
	int				prev_im = 0;

	if (DebugParms->DebugLevel == 0 && LogType == LOG_INFO) return;

	if (DebugParms->ThreadSafeLogging>0) WaitForSingleObject(DebugParms->Mtx, INFINITE);

	//-- Opens Log file only once
	if (DebugParms->fIsOpen != 1) {
		strcpy(DebugParms->FullfName, DebugParms->fPath); strcat(DebugParms->FullfName, "/"); strcat(DebugParms->FullfName, DebugParms->fName);
		DebugParms->fHandle = fopen(DebugParms->FullfName, "w");
		DebugParms->fIsOpen = 1;
	}

	va_start(arguments, argcount);
	n = 0;

	do {
		if (msg[im] == 37) {                // "%"
			memcpy(submsg, &msg[prev_im], (im - prev_im + 2)); submsg[im - prev_im + 2] = '\0';
			n++;
			prev_im = im + 2;
			if (msg[im + 1] == 115) {   // "s"
				arg_s = va_arg(arguments, char*);
				if (DebugParms->DebugLevel == 1 || DebugParms->DebugLevel == 3 || LogType == LOG_ERROR) printf(submsg, arg_s);
				if (DebugParms->DebugLevel == 2 || DebugParms->DebugLevel == 3 || LogType == LOG_ERROR)	fprintf(DebugParms->fHandle, submsg, arg_s);
			}
			else if (msg[im + 1] == 100) {   // "d"
				arg_d = va_arg(arguments, int);
				if (DebugParms->DebugLevel == 1 || DebugParms->DebugLevel == 3 || LogType == LOG_ERROR) printf(submsg, arg_d);
				if (DebugParms->DebugLevel == 2 || DebugParms->DebugLevel == 3 || LogType == LOG_ERROR)	fprintf(DebugParms->fHandle, submsg, arg_d);
			}
			else if (msg[im + 1] == 112) {   // "p"
				arg_d = va_arg(arguments, long);
				if (DebugParms->DebugLevel == 1 || DebugParms->DebugLevel == 3 || LogType == LOG_ERROR) printf(submsg, arg_d);
				if (DebugParms->DebugLevel == 2 || DebugParms->DebugLevel == 3 || LogType == LOG_ERROR)	fprintf(DebugParms->fHandle, submsg, arg_d);
			}
			else {   // this could be 67 ("f") or any mask before "f" -> in any case, it's a double
				arg_f = va_arg(arguments, double);
				if (DebugParms->DebugLevel == 1 || DebugParms->DebugLevel == 3 || LogType == LOG_ERROR) printf(submsg, arg_f);
				if (DebugParms->DebugLevel == 2 || DebugParms->DebugLevel == 3 || LogType == LOG_ERROR)	fprintf(DebugParms->fHandle, submsg, arg_f);
			}
		}
		im++;
	} while (im<strlen(msg));

	memcpy(submsg, &msg[prev_im], (im - prev_im + 2)); submsg[im - prev_im + 2] = '\0';
	if (DebugParms->DebugLevel == 1 || DebugParms->DebugLevel == 3 || LogType == LOG_ERROR) printf(submsg);
	if (DebugParms->DebugLevel == 2 || DebugParms->DebugLevel == 3 || LogType == LOG_ERROR) fprintf(DebugParms->fHandle, submsg);
	if (LogType == LOG_ERROR) {printf("Press any key to continue...\n"); getchar();};

	va_end(arguments);

	if (DebugParms->ThreadSafeLogging>0) ReleaseMutex(DebugParms->Mtx);
}
EXPORT void LogClose(tDebugInfo* DebugParms) {
	if (DebugParms->fIsOpen == 1) {
		fclose(DebugParms->fHandle);
		DebugParms->fIsOpen = 0;
	}
}

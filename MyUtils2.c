#include <MyUtils2.h>

EXPORT char* timestamp() {
	char* ftime;
	time_t ltime; // calendar time 
	HANDLE TimeMutex;

	TimeMutex = CreateMutex(NULL, TRUE, NULL);
	WaitForSingleObject(TimeMutex, INFINITE);
	ltime = time(NULL); // get current cal time 
	ftime = asctime(localtime(&ltime));
	ftime[strlen(ftime)-1] = '\0';
	ReleaseMutex(TimeMutex);

	return (ftime);
}

EXPORT void Trim(char* str) {
	int l = 0;
	int i;
	int r = (int)strlen(str);
	char ret[MAX_PATH];
	while (isspace(str[l])>0) l++;
	while (isspace(str[r - 1])>0) r--;
	for (i = 0; i<(r - l); i++) ret[i] = str[l + i];
	ret[r - l] = '\0';
	strcpy(str, ret);
}

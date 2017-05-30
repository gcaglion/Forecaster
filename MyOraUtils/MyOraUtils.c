
/* Result Sets Interface */
#ifndef SQL_CRSR
#  define SQL_CRSR
  struct sql_cursor
  {
    unsigned int curocn;
    void *ptr1;
    void *ptr2;
    unsigned int magic;
  };
  typedef struct sql_cursor sql_cursor;
  typedef struct sql_cursor SQL_CURSOR;
#endif /* SQL_CRSR */

/* Thread Safety */
typedef void * sql_context;
typedef void * SQL_CONTEXT;

/* Object support */
struct sqltvn
{
  unsigned char *tvnvsn; 
  unsigned short tvnvsnl; 
  unsigned char *tvnnm;
  unsigned short tvnnml; 
  unsigned char *tvnsnm;
  unsigned short tvnsnml;
};
typedef struct sqltvn sqltvn;

struct sqladts
{
  unsigned int adtvsn; 
  unsigned short adtmode; 
  unsigned short adtnum;  
  sqltvn adttvn[1];       
};
typedef struct sqladts sqladts;

static struct sqladts sqladt = {
  1,1,0,
};

/* Binding to PL/SQL Records */
struct sqltdss
{
  unsigned int tdsvsn; 
  unsigned short tdsnum; 
  unsigned char *tdsval[1]; 
};
typedef struct sqltdss sqltdss;
static struct sqltdss sqltds =
{
  1,
  0,
};

/* File name & Package Name */
struct sqlcxp
{
  unsigned short fillen;
           char  filnam[14];
};
static const struct sqlcxp sqlfpn =
{
    13,
    "MyOraUtils.pc"
};


static unsigned int sqlctx = 658067;


static struct sqlexd {
   unsigned int   sqlvsn;
   unsigned int   arrsiz;
   unsigned int   iters;
   unsigned int   offset;
   unsigned short selerr;
   unsigned short sqlety;
   unsigned int   occurs;
      const short *cud;
   unsigned char  *sqlest;
      const char  *stmt;
   sqladts *sqladtp;
   sqltdss *sqltdsp;
            void  **sqphsv;
   unsigned int   *sqphsl;
            int   *sqphss;
            void  **sqpind;
            int   *sqpins;
   unsigned int   *sqparm;
   unsigned int   **sqparc;
   unsigned short  *sqpadto;
   unsigned short  *sqptdso;
   unsigned int   sqlcmax;
   unsigned int   sqlcmin;
   unsigned int   sqlcincr;
   unsigned int   sqlctimeout;
   unsigned int   sqlcnowait;
              int   sqfoff;
   unsigned int   sqcmod;
   unsigned int   sqfmod;
   unsigned int   sqlpfmem;
            void  *sqhstv[11];
   unsigned int   sqhstl[11];
            int   sqhsts[11];
            void  *sqindv[11];
            int   sqinds[11];
   unsigned int   sqharm[11];
   unsigned int   *sqharc[11];
   unsigned short  sqadto[11];
   unsigned short  sqtdso[11];
} sqlstm = {13,11};

/* SQLLIB Prototypes */
extern void sqlcxt (void **, unsigned int *,
                    struct sqlexd *, const struct sqlcxp *);
extern void sqlcx2t(void **, unsigned int *,
                    struct sqlexd *, const struct sqlcxp *);
extern void sqlbuft(void **, char *);
extern void sqlgs2t(void **, char *);
extern void sqlorat(void **, unsigned int *, void *);

/* Forms Interface */
static const int IAPSUCC = 0;
static const int IAPFAIL = 1403;
static const int IAPFTL  = 535;
extern void sqliem(unsigned char *, signed int *);

typedef struct { unsigned short len; unsigned char arr[1]; } VARCHAR;
typedef struct { unsigned short len; unsigned char arr[1]; } varchar;

/* cud (compilation unit data) array */
static const short sqlcud0[] =
{13,4138,178,8,0,
5,0,0,0,0,0,58,22,0,0,1,1,0,1,0,3,109,0,0,
24,0,0,0,0,0,27,26,0,0,4,4,0,1,0,1,97,0,0,1,97,0,0,1,97,0,0,1,10,0,0,
55,0,0,2,0,0,30,44,0,0,0,0,0,1,0,
70,0,0,3,0,0,29,52,0,0,0,0,0,1,0,
85,0,0,0,0,0,90,108,0,64,0,0,5,105,110,77,83,69,1,0,
105,0,0,0,0,0,93,109,0,64,0,0,5,105,110,77,83,69,1,0,
125,0,0,0,0,0,93,110,0,64,1,1,5,105,110,77,83,69,1,0,3329,3,0,0,
149,0,0,0,0,0,93,111,0,64,1,1,5,105,110,77,83,69,1,0,3329,3,0,0,
173,0,0,0,0,0,93,112,0,64,1,1,5,105,110,77,83,69,1,0,3329,3,0,0,
197,0,0,0,0,0,93,113,0,64,1,1,5,105,110,77,83,69,1,0,3329,4,0,0,
221,0,0,0,0,0,93,114,0,64,1,1,5,105,110,77,83,69,1,0,3329,4,0,0,
245,0,0,4,0,0,17,115,0,0,1,1,0,1,0,1,97,0,0,
264,0,0,4,0,0,23,116,0,64,0,0,5,105,110,77,83,69,1,0,
284,0,0,0,0,0,91,126,0,64,0,0,5,105,110,77,83,69,1,0,
304,0,0,0,0,0,90,210,0,64,0,0,5,105,110,82,117,110,1,0,
324,0,0,0,0,0,93,211,0,64,1,1,5,105,110,82,117,110,1,0,513,3,0,0,
348,0,0,0,0,0,93,212,0,64,1,1,5,105,110,82,117,110,1,0,513,3,0,0,
372,0,0,0,0,0,93,213,0,64,1,1,5,105,110,82,117,110,1,0,513,3,0,0,
396,0,0,0,0,0,93,214,0,64,1,1,5,105,110,82,117,110,1,0,513,3,0,0,
420,0,0,0,0,0,93,215,0,64,1,1,5,105,110,82,117,110,1,0,513,3,0,0,
444,0,0,0,0,0,93,216,0,64,1,1,5,105,110,82,117,110,1,0,513,3,0,0,
468,0,0,0,0,0,93,217,0,64,1,1,5,105,110,82,117,110,1,0,513,3,0,0,
492,0,0,0,0,0,93,218,0,64,1,1,5,105,110,82,117,110,1,0,513,3,0,0,
516,0,0,0,0,0,93,219,0,64,1,1,5,105,110,82,117,110,1,0,513,3,0,0,
540,0,0,0,0,0,93,220,0,64,1,1,5,105,110,82,117,110,1,0,513,3,0,0,
564,0,0,0,0,0,93,221,0,64,1,1,5,105,110,82,117,110,1,0,513,3,0,0,
588,0,0,0,0,0,93,222,0,64,1,1,5,105,110,82,117,110,1,0,513,3,0,0,
612,0,0,0,0,0,93,223,0,64,1,1,5,105,110,82,117,110,1,0,513,3,0,0,
636,0,0,0,0,0,93,225,0,64,0,0,5,105,110,82,117,110,1,0,
656,0,0,0,0,0,93,226,0,64,1,1,5,105,110,82,117,110,1,0,3329,3,0,0,
680,0,0,0,0,0,93,227,0,64,1,1,5,105,110,82,117,110,1,0,3329,3,0,0,
704,0,0,0,0,0,93,228,0,64,1,1,5,105,110,82,117,110,1,0,3329,3,0,0,
728,0,0,0,0,0,93,229,0,64,1,1,5,105,110,82,117,110,1,0,3329,3,0,0,
752,0,0,0,0,0,93,230,0,64,1,1,5,105,110,82,117,110,1,0,3329,3,0,0,
776,0,0,0,0,0,93,231,0,64,1,1,5,105,110,82,117,110,1,0,3329,4,0,0,
800,0,0,0,0,0,93,232,0,64,1,1,5,105,110,82,117,110,1,0,3329,4,0,0,
824,0,0,0,0,0,93,233,0,64,1,1,5,105,110,82,117,110,1,0,3329,4,0,0,
848,0,0,0,0,0,93,234,0,64,1,1,5,105,110,82,117,110,1,0,3329,4,0,0,
872,0,0,0,0,0,93,235,0,64,1,1,5,105,110,82,117,110,1,0,3329,4,0,0,
896,0,0,0,0,0,93,236,0,64,1,1,5,105,110,82,117,110,1,0,3329,4,0,0,
920,0,0,0,0,0,93,237,0,64,1,1,5,105,110,82,117,110,1,0,3329,4,0,0,
944,0,0,0,0,0,93,238,0,64,1,1,5,105,110,82,117,110,1,0,3329,4,0,0,
968,0,0,4,0,0,17,240,0,0,1,1,0,1,0,1,97,0,0,
987,0,0,4,0,0,23,241,0,64,0,0,5,105,110,82,117,110,1,0,
1007,0,0,5,0,0,24,258,0,0,1,1,0,1,0,1,97,0,0,
1026,0,0,0,0,0,91,265,0,64,0,0,5,105,110,82,117,110,1,0,
1046,0,0,6,0,0,24,269,0,0,1,1,0,1,0,1,97,0,0,
1065,0,0,7,0,0,24,278,0,0,1,1,0,1,0,1,97,0,0,
1084,0,0,8,0,0,24,512,0,0,1,1,0,1,0,1,97,0,0,
1103,0,0,9,0,0,24,537,0,0,1,1,0,1,0,1,97,0,0,
1122,0,0,10,0,0,17,569,0,0,1,1,0,1,0,1,97,0,0,
1141,0,0,10,0,0,45,571,0,0,0,0,0,1,0,
1156,0,0,10,0,0,13,572,0,0,5,0,0,1,0,2,3,0,0,2,3,0,0,2,3,0,0,2,3,0,0,2,4,0,0,
1191,0,0,10,0,0,15,578,0,0,0,0,0,1,0,
1206,0,0,11,0,0,17,612,0,0,1,1,0,1,0,1,97,0,0,
1225,0,0,11,0,0,45,614,0,0,0,0,0,1,0,
1240,0,0,11,0,0,13,615,0,0,4,0,0,1,0,2,3,0,0,2,3,0,0,2,3,0,0,2,97,0,0,
1271,0,0,11,0,0,15,621,0,0,0,0,0,1,0,
1286,0,0,12,0,0,24,650,0,0,1,1,0,1,0,1,97,0,0,
1305,0,0,13,0,0,24,672,0,0,1,1,0,1,0,1,97,0,0,
1324,0,0,14,0,0,24,693,0,0,1,1,0,1,0,1,97,0,0,
1343,0,0,15,0,0,17,720,0,0,1,1,0,1,0,1,97,0,0,
1362,0,0,15,0,0,45,722,0,0,0,0,0,1,0,
1377,0,0,15,0,0,13,723,0,0,1,0,0,1,0,2,3,0,0,
1396,0,0,15,0,0,15,728,0,0,0,0,0,1,0,
1411,0,0,16,0,0,17,754,0,0,1,1,0,1,0,1,97,0,0,
1430,0,0,16,0,0,45,756,0,0,0,0,0,1,0,
1445,0,0,16,0,0,13,761,0,0,11,0,0,1,0,2,3,0,0,2,3,0,0,2,97,0,0,2,3,0,0,2,3,0,0,
2,3,0,0,2,4,0,0,2,4,0,0,2,3,0,0,2,4,0,0,2,4,0,0,
1504,0,0,16,0,0,15,774,0,0,0,0,0,1,0,
1519,0,0,17,0,0,17,798,0,0,1,1,0,1,0,1,97,0,0,
1538,0,0,17,0,0,45,800,0,0,0,0,0,1,0,
1553,0,0,17,0,0,13,805,0,0,7,0,0,1,0,2,3,0,0,2,3,0,0,2,3,0,0,2,3,0,0,2,4,0,0,2,
3,0,0,2,4,0,0,
1596,0,0,17,0,0,15,817,0,0,0,0,0,1,0,
1611,0,0,18,0,0,17,841,0,0,1,1,0,1,0,1,97,0,0,
1630,0,0,18,0,0,45,843,0,0,0,0,0,1,0,
1645,0,0,18,0,0,13,848,0,0,11,0,0,1,0,2,3,0,0,2,3,0,0,2,4,0,0,2,4,0,0,2,3,0,0,
2,3,0,0,2,3,0,0,2,4,0,0,2,4,0,0,2,4,0,0,2,3,0,0,
1704,0,0,18,0,0,15,860,0,0,0,0,0,1,0,
1719,0,0,19,0,0,17,885,0,0,1,1,0,1,0,1,97,0,0,
1738,0,0,19,0,0,45,887,0,0,0,0,0,1,0,
1753,0,0,19,0,0,13,889,0,0,4,0,0,1,0,2,3,0,0,2,3,0,0,2,3,0,0,2,4,0,0,
1784,0,0,19,0,0,15,900,0,0,0,0,0,1,0,
1799,0,0,20,0,0,17,923,0,0,1,1,0,1,0,1,97,0,0,
1818,0,0,20,0,0,45,925,0,0,0,0,0,1,0,
1833,0,0,20,0,0,13,927,0,0,3,0,0,1,0,2,3,0,0,2,3,0,0,2,4,0,0,
1860,0,0,20,0,0,15,938,0,0,0,0,0,1,0,
1875,0,0,21,0,0,17,961,0,0,1,1,0,1,0,1,97,0,0,
1894,0,0,21,0,0,45,963,0,0,0,0,0,1,0,
1909,0,0,21,0,0,13,965,0,0,3,0,0,1,0,2,3,0,0,2,3,0,0,2,4,0,0,
1936,0,0,21,0,0,15,976,0,0,0,0,0,1,0,
1951,0,0,0,0,0,90,1031,0,64,0,0,3,87,78,78,1,0,
1969,0,0,0,0,0,93,1032,0,64,0,0,3,87,78,78,1,0,
1987,0,0,0,0,0,93,1033,0,64,1,1,3,87,78,78,1,0,513,3,0,0,
2009,0,0,0,0,0,93,1034,0,64,1,1,3,87,78,78,1,0,513,3,0,0,
2031,0,0,0,0,0,93,1035,0,64,1,1,3,87,78,78,1,0,513,3,0,0,
2053,0,0,0,0,0,93,1036,0,64,1,1,3,87,78,78,1,0,513,3,0,0,
2075,0,0,0,0,0,93,1037,0,64,1,1,3,87,78,78,1,0,513,3,0,0,
2097,0,0,0,0,0,93,1038,0,64,1,1,3,87,78,78,1,0,513,3,0,0,
2119,0,0,0,0,0,93,1040,0,64,1,1,3,87,78,78,1,0,3329,3,0,0,
2141,0,0,0,0,0,93,1041,0,64,1,1,3,87,78,78,1,0,3329,3,0,0,
2163,0,0,0,0,0,93,1042,0,64,1,1,3,87,78,78,1,0,3329,3,0,0,
2185,0,0,0,0,0,93,1043,0,64,1,1,3,87,78,78,1,0,3329,3,0,0,
2207,0,0,0,0,0,93,1044,0,64,1,1,3,87,78,78,1,0,3329,3,0,0,
2229,0,0,0,0,0,93,1045,0,64,1,1,3,87,78,78,1,0,3329,4,0,0,
2251,0,0,22,0,0,17,1047,0,0,1,1,0,1,0,1,97,0,0,
2270,0,0,22,0,0,23,1048,0,64,0,0,3,87,78,78,1,0,
2288,0,0,0,0,0,91,1054,0,64,0,0,3,87,78,78,1,0,
2306,0,0,23,0,0,17,1088,0,0,1,1,0,1,0,1,97,0,0,
2325,0,0,23,0,0,45,1090,0,0,0,0,0,1,0,
2340,0,0,23,0,0,13,1091,0,0,1,0,0,1,0,2,97,0,0,
2359,0,0,23,0,0,15,1096,0,0,0,0,0,1,0,
2374,0,0,24,0,0,17,1107,0,0,1,1,0,1,0,1,97,0,0,
2393,0,0,24,0,0,45,1109,0,0,0,0,0,1,0,
2408,0,0,24,0,0,13,1110,0,0,1,0,0,1,0,2,3,0,0,
2427,0,0,24,0,0,15,1115,0,0,0,0,0,1,0,
2442,0,0,25,0,0,17,1160,0,0,1,1,0,1,0,1,97,0,0,
2461,0,0,25,0,0,45,1162,0,0,0,0,0,1,0,
2476,0,0,25,0,0,13,1169,0,0,3,0,0,1,0,2,97,0,0,2,3,0,0,2,97,0,0,
2503,0,0,25,0,0,15,1179,0,0,0,0,0,1,0,
2518,0,0,26,0,0,17,1192,0,0,1,1,0,1,0,1,97,0,0,
2537,0,0,26,0,0,45,1194,0,0,0,0,0,1,0,
2552,0,0,26,0,0,13,1199,0,0,1,0,0,1,0,2,97,0,0,
2571,0,0,26,0,0,15,1205,0,0,0,0,0,1,0,
2586,0,0,27,0,0,17,1217,0,0,1,1,0,1,0,1,97,0,0,
2605,0,0,27,0,0,45,1219,0,0,0,0,0,1,0,
2620,0,0,27,0,0,13,1225,0,0,1,0,0,1,0,2,97,0,0,
2639,0,0,27,0,0,15,1232,0,0,0,0,0,1,0,
2654,0,0,28,0,0,17,1244,0,0,1,1,0,1,0,1,97,0,0,
2673,0,0,28,0,0,45,1246,0,0,0,0,0,1,0,
2688,0,0,28,0,0,13,1247,0,0,1,0,0,1,0,2,3,0,0,
2707,0,0,28,0,0,15,1255,0,0,0,0,0,1,0,
2722,0,0,29,0,0,17,1283,0,0,1,1,0,1,0,1,97,0,0,
2741,0,0,29,0,0,45,1285,0,0,0,0,0,1,0,
2756,0,0,29,0,0,13,1287,0,0,6,0,0,1,0,2,97,0,0,2,4,0,0,2,4,0,0,2,4,0,0,2,4,0,0,
2,4,0,0,
2795,0,0,29,0,0,15,1300,0,0,0,0,0,1,0,
2810,0,0,30,0,0,17,1325,0,0,1,1,0,1,0,1,97,0,0,
2829,0,0,30,0,0,45,1327,0,0,0,0,0,1,0,
2844,0,0,30,0,0,13,1329,0,0,9,0,0,1,0,2,97,0,0,2,4,0,0,2,4,0,0,2,4,0,0,2,4,0,0,
2,4,0,0,2,4,0,0,2,4,0,0,2,4,0,0,
2895,0,0,30,0,0,15,1348,0,0,0,0,0,1,0,
};


//#include <vld.h>

#include <sqlca.h>
#include <MyOraUtils.h>

//-- DB common functions
EXPORT int  OraConnect(tDebugInfo* DebugInfo, tDBConnection* DBConnInfo){

	/* EXEC SQL BEGIN DECLARE SECTION; */ 

	char* username = DBConnInfo->DBUser;
	char* password = DBConnInfo->DBPassword;
	char* dbstring = DBConnInfo->DBConnString;
	sql_context vCtx = NULL;
	int kaz;
	/* EXEC SQL END DECLARE SECTION; */ 


	//LogWrite(DebugParms, "%s About to execute connect with %s , %s , %s\n", 4, timestamp(), pUserName, pPassword, pDBString);

	char* vPath = getenv("PATH");
	char* vOH = getenv("ORACLE_HOME");

	/* EXEC SQL CONTEXT ALLOCATE :vCtx; */ 

{
 struct sqlexd sqlstm;
 sqlstm.sqlvsn = 13;
 sqlstm.arrsiz = 1;
 sqlstm.sqladtp = &sqladt;
 sqlstm.sqltdsp = &sqltds;
 sqlstm.stmt = "";
 sqlstm.iters = (unsigned int  )1;
 sqlstm.offset = (unsigned int  )5;
 sqlstm.cud = sqlcud0;
 sqlstm.sqlest = (unsigned char  *)&sqlca;
 sqlstm.sqlety = (unsigned short)4352;
 sqlstm.occurs = (unsigned int  )0;
 sqlstm.sqhstv[0] = (         void  *)&vCtx;
 sqlstm.sqhstl[0] = (unsigned int  )sizeof(void *);
 sqlstm.sqhsts[0] = (         int  )0;
 sqlstm.sqindv[0] = (         void  *)0;
 sqlstm.sqinds[0] = (         int  )0;
 sqlstm.sqharm[0] = (unsigned int  )0;
 sqlstm.sqadto[0] = (unsigned short )0;
 sqlstm.sqtdso[0] = (unsigned short )0;
 sqlstm.sqphsv = sqlstm.sqhstv;
 sqlstm.sqphsl = sqlstm.sqhstl;
 sqlstm.sqphss = sqlstm.sqhsts;
 sqlstm.sqpind = sqlstm.sqindv;
 sqlstm.sqpins = sqlstm.sqinds;
 sqlstm.sqparm = sqlstm.sqharm;
 sqlstm.sqparc = sqlstm.sqharc;
 sqlstm.sqpadto = sqlstm.sqadto;
 sqlstm.sqptdso = sqlstm.sqtdso;
 sqlcxt((void **)0, &sqlctx, &sqlstm, &sqlfpn);
}


//	kaz = sqlca.sqlcode;
//	printf("vPath=%s\nvOH=%s\nkaz=%d\n", vPath, vOH, kaz);
	/* EXEC SQL CONTEXT USE :vCtx; */ 

	/* EXEC SQL CONNECT :username IDENTIFIED BY :password USING :dbstring; */ 

{
 struct sqlexd sqlstm;
 sqlstm.sqlvsn = 13;
 sqlstm.arrsiz = 4;
 sqlstm.sqladtp = &sqladt;
 sqlstm.sqltdsp = &sqltds;
 sqlstm.iters = (unsigned int  )10;
 sqlstm.offset = (unsigned int  )24;
 sqlstm.cud = sqlcud0;
 sqlstm.sqlest = (unsigned char  *)&sqlca;
 sqlstm.sqlety = (unsigned short)4352;
 sqlstm.occurs = (unsigned int  )0;
 sqlstm.sqhstv[0] = (         void  *)username;
 sqlstm.sqhstl[0] = (unsigned int  )0;
 sqlstm.sqhsts[0] = (         int  )0;
 sqlstm.sqindv[0] = (         void  *)0;
 sqlstm.sqinds[0] = (         int  )0;
 sqlstm.sqharm[0] = (unsigned int  )0;
 sqlstm.sqadto[0] = (unsigned short )0;
 sqlstm.sqtdso[0] = (unsigned short )0;
 sqlstm.sqhstv[1] = (         void  *)password;
 sqlstm.sqhstl[1] = (unsigned int  )0;
 sqlstm.sqhsts[1] = (         int  )0;
 sqlstm.sqindv[1] = (         void  *)0;
 sqlstm.sqinds[1] = (         int  )0;
 sqlstm.sqharm[1] = (unsigned int  )0;
 sqlstm.sqadto[1] = (unsigned short )0;
 sqlstm.sqtdso[1] = (unsigned short )0;
 sqlstm.sqhstv[2] = (         void  *)dbstring;
 sqlstm.sqhstl[2] = (unsigned int  )0;
 sqlstm.sqhsts[2] = (         int  )0;
 sqlstm.sqindv[2] = (         void  *)0;
 sqlstm.sqinds[2] = (         int  )0;
 sqlstm.sqharm[2] = (unsigned int  )0;
 sqlstm.sqadto[2] = (unsigned short )0;
 sqlstm.sqtdso[2] = (unsigned short )0;
 sqlstm.sqphsv = sqlstm.sqhstv;
 sqlstm.sqphsl = sqlstm.sqhstl;
 sqlstm.sqphss = sqlstm.sqhsts;
 sqlstm.sqpind = sqlstm.sqindv;
 sqlstm.sqpins = sqlstm.sqinds;
 sqlstm.sqparm = sqlstm.sqharm;
 sqlstm.sqparc = sqlstm.sqharc;
 sqlstm.sqpadto = sqlstm.sqadto;
 sqlstm.sqptdso = sqlstm.sqtdso;
 sqlstm.sqlcmax = (unsigned int )100;
 sqlstm.sqlcmin = (unsigned int )2;
 sqlstm.sqlcincr = (unsigned int )1;
 sqlstm.sqlctimeout = (unsigned int )0;
 sqlstm.sqlcnowait = (unsigned int )0;
 sqlcxt(&vCtx, &sqlctx, &sqlstm, &sqlfpn);
}



	if (sqlca.sqlcode == 0){
		DBConnInfo->DBCtx = vCtx;
		LogWrite(DebugInfo, LOG_INFO, "OraConnect() - Connected to ORACLE as user: %s ; DBConnInfo->DBCtx=%p\n", 2, username, DBConnInfo->DBCtx);
	}
	else {
		LogWrite(DebugInfo, LOG_ERROR, "%s Error %d connecting to ORACLE as user: %s\n", 3, timestamp(), sqlca.sqlcode, DBConnInfo->DBUser);
		LogWrite(DebugInfo, LOG_ERROR, "PATH=%s\nORACLE_HOME=%s\n", 2, vPath, vOH);
	}
	return(sqlca.sqlcode);
}
EXPORT void OraDisconnect(sql_context pCtx) {
	/* EXEC SQL BEGIN DECLARE SECTION; */ 

	sql_context vCtx = pCtx;
	/* EXEC SQL END   DECLARE SECTION; */ 


	/* EXEC SQL CONTEXT USE : vCtx; */ 

	/* EXEC SQL COMMIT WORK RELEASE; */ 

{
 struct sqlexd sqlstm;
 sqlstm.sqlvsn = 13;
 sqlstm.arrsiz = 4;
 sqlstm.sqladtp = &sqladt;
 sqlstm.sqltdsp = &sqltds;
 sqlstm.iters = (unsigned int  )1;
 sqlstm.offset = (unsigned int  )55;
 sqlstm.cud = sqlcud0;
 sqlstm.sqlest = (unsigned char  *)&sqlca;
 sqlstm.sqlety = (unsigned short)4352;
 sqlstm.occurs = (unsigned int  )0;
 sqlcxt(&vCtx, &sqlctx, &sqlstm, &sqlfpn);
}


}
EXPORT void OraCommit(void* pCtx) {
	/* EXEC SQL BEGIN DECLARE SECTION; */ 

	sql_context vCtx = pCtx;
	/* EXEC SQL END   DECLARE SECTION; */ 


	/* EXEC SQL CONTEXT USE : vCtx; */ 

	/* EXEC SQL COMMIT; */ 

{
 struct sqlexd sqlstm;
 sqlstm.sqlvsn = 13;
 sqlstm.arrsiz = 4;
 sqlstm.sqladtp = &sqladt;
 sqlstm.sqltdsp = &sqltds;
 sqlstm.iters = (unsigned int  )1;
 sqlstm.offset = (unsigned int  )70;
 sqlstm.cud = sqlcud0;
 sqlstm.sqlest = (unsigned char  *)&sqlca;
 sqlstm.sqlety = (unsigned short)4352;
 sqlstm.occurs = (unsigned int  )0;
 sqlcxt(&vCtx, &sqlctx, &sqlstm, &sqlfpn);
}


}

//-- MSE / Run logs
EXPORT int Ora_InsertMSELog(tDebugInfo* DebugParms, tDBConnection* DBConnInfo, int* pInsertCount, tLogMSE* MSEData) {
	/* EXEC SQL BEGIN DECLARE SECTION; */ 

	int i;
	int vInsertCount;
	sql_context vCtx = DBConnInfo->DBCtx;
	char stmt[1000];
	//--
	int* vProcessId;
	int* vThreadId;
	int* vEpoch;
	double* vMSE_T;
	double* vMSE_V;
	//--
	int dbl_type = 22;	// Oracle SQLT_BDOUBLE
	int int_type = 3;	// 
	unsigned int dbl_len = sizeof(double);
	unsigned int vchar_type = 96;
	unsigned int vchar_len = 12 + 1;

	/* EXEC SQL END   DECLARE SECTION; */ 


	//-- Connects to DB only once
	LogWrite(DebugParms, LOG_INFO, "Ora_InsertMSELog() CheckPoint 1 - LogDB->DBCtx=%p\n", 1, DBConnInfo->DBCtx);

	if (vCtx == NULL) {
		if (OraConnect(DebugParms, DBConnInfo) != 0) LogWrite(DebugParms, LOG_ERROR, "Ora_InsertMSELog could not connect to Log Database...\n", 0);
		vCtx = DBConnInfo->DBCtx;
	}
	LogWrite(DebugParms, LOG_INFO, "Ora_InsertMSELog() CheckPoint 2 - LogDB->DBCtx=%p , vCtx=%p\n", 2, DBConnInfo->DBCtx, vCtx);

	vInsertCount = (*pInsertCount);
	vProcessId = (int*)malloc(vInsertCount*sizeof(int));
	vThreadId = (int*)malloc(vInsertCount*sizeof(int));
	vEpoch = (int*)malloc(vInsertCount*sizeof(int));
	vMSE_T = (double*)malloc(vInsertCount*sizeof(double));
	vMSE_V = (double*)malloc(vInsertCount*sizeof(double));

	for (i = 0; i < vInsertCount; i++) {
		vProcessId[i] = MSEData[i].ProcessId;
		vThreadId[i] = MSEData[i].ThreadId;
		vEpoch[i] = MSEData[i].Epoch;
		vMSE_T[i] = MSEData[i].MSE_T;
		vMSE_V[i] = MSEData[i].MSE_V;
	}

	//-- Then, Build the Insert statement
	sprintf(&stmt[0], "insert into MyLog_MSE (ProcessId, ThreadId, Epoch, MSE_T, MSE_V) values(:P01, :P02, :P03, :P04, :P05)");
	LogWrite(DebugParms, LOG_INFO, "Ora_InsertMSELog() CheckPoint 4 - stmt='%s'\n", 1, stmt);

	/* EXEC SQL CONTEXT USE : vCtx; */ 

	//EXEC SQL ALTER SESSION SET EVENTS '10046 trace name context forever, level 4';
	//EXEC SQL ALTER SESSION SET SQL_TRACE = TRUE;
	/* EXEC SQL FOR : vInsertCount ALLOCATE DESCRIPTOR 'inMSE'; */ 

{
 struct sqlexd sqlstm;
 sqlstm.sqlvsn = 13;
 sqlstm.arrsiz = 4;
 sqlstm.sqladtp = &sqladt;
 sqlstm.sqltdsp = &sqltds;
 sqlstm.stmt = "";
 sqlstm.iters = (unsigned int  )vInsertCount;
 sqlstm.offset = (unsigned int  )85;
 sqlstm.cud = sqlcud0;
 sqlstm.sqlest = (unsigned char  *)&sqlca;
 sqlstm.sqlety = (unsigned short)4352;
 sqlstm.occurs = (unsigned int  )100;
 sqlcxt(&vCtx, &sqlctx, &sqlstm, &sqlfpn);
}


	/* EXEC SQL SET DESCRIPTOR 'inMSE' COUNT = 5; */ 

{
 struct sqlexd sqlstm;
 sqlstm.sqlvsn = 13;
 sqlstm.arrsiz = 4;
 sqlstm.sqladtp = &sqladt;
 sqlstm.sqltdsp = &sqltds;
 sqlstm.stmt = "";
 sqlstm.iters = (unsigned int  )1;
 sqlstm.offset = (unsigned int  )105;
 sqlstm.cud = sqlcud0;
 sqlstm.sqlest = (unsigned char  *)&sqlca;
 sqlstm.sqlety = (unsigned short)4352;
 sqlstm.occurs = (unsigned int  )5;
 sqlcxt(&vCtx, &sqlctx, &sqlstm, &sqlfpn);
}


	/* EXEC SQL FOR : vInsertCount SET DESCRIPTOR 'inMSE' VALUE 1 DATA = : vProcessId; */ 

{
 struct sqlexd sqlstm;
 sqlstm.sqlvsn = 13;
 sqlstm.arrsiz = 4;
 sqlstm.sqladtp = &sqladt;
 sqlstm.sqltdsp = &sqltds;
 sqlstm.stmt = "";
 sqlstm.iters = (unsigned int  )vInsertCount;
 sqlstm.offset = (unsigned int  )125;
 sqlstm.cud = sqlcud0;
 sqlstm.sqlest = (unsigned char  *)&sqlca;
 sqlstm.sqlety = (unsigned short)4352;
 sqlstm.occurs = (unsigned int  )1;
 sqlstm.sqhstv[0] = (         void  *)vProcessId;
 sqlstm.sqhstl[0] = (unsigned int  )sizeof(int);
 sqlstm.sqhsts[0] = (         int  )sizeof(int);
 sqlstm.sqindv[0] = (         void  *)0;
 sqlstm.sqinds[0] = (         int  )0;
 sqlstm.sqharm[0] = (unsigned int  )0;
 sqlstm.sqadto[0] = (unsigned short )0;
 sqlstm.sqtdso[0] = (unsigned short )0;
 sqlstm.sqphsv = sqlstm.sqhstv;
 sqlstm.sqphsl = sqlstm.sqhstl;
 sqlstm.sqphss = sqlstm.sqhsts;
 sqlstm.sqpind = sqlstm.sqindv;
 sqlstm.sqpins = sqlstm.sqinds;
 sqlstm.sqparm = sqlstm.sqharm;
 sqlstm.sqparc = sqlstm.sqharc;
 sqlstm.sqpadto = sqlstm.sqadto;
 sqlstm.sqptdso = sqlstm.sqtdso;
 sqlcxt(&vCtx, &sqlctx, &sqlstm, &sqlfpn);
}


	/* EXEC SQL FOR : vInsertCount SET DESCRIPTOR 'inMSE' VALUE 2 DATA = : vThreadId; */ 

{
 struct sqlexd sqlstm;
 sqlstm.sqlvsn = 13;
 sqlstm.arrsiz = 4;
 sqlstm.sqladtp = &sqladt;
 sqlstm.sqltdsp = &sqltds;
 sqlstm.stmt = "";
 sqlstm.iters = (unsigned int  )vInsertCount;
 sqlstm.offset = (unsigned int  )149;
 sqlstm.cud = sqlcud0;
 sqlstm.sqlest = (unsigned char  *)&sqlca;
 sqlstm.sqlety = (unsigned short)4352;
 sqlstm.occurs = (unsigned int  )2;
 sqlstm.sqhstv[0] = (         void  *)vThreadId;
 sqlstm.sqhstl[0] = (unsigned int  )sizeof(int);
 sqlstm.sqhsts[0] = (         int  )sizeof(int);
 sqlstm.sqindv[0] = (         void  *)0;
 sqlstm.sqinds[0] = (         int  )0;
 sqlstm.sqharm[0] = (unsigned int  )0;
 sqlstm.sqadto[0] = (unsigned short )0;
 sqlstm.sqtdso[0] = (unsigned short )0;
 sqlstm.sqphsv = sqlstm.sqhstv;
 sqlstm.sqphsl = sqlstm.sqhstl;
 sqlstm.sqphss = sqlstm.sqhsts;
 sqlstm.sqpind = sqlstm.sqindv;
 sqlstm.sqpins = sqlstm.sqinds;
 sqlstm.sqparm = sqlstm.sqharm;
 sqlstm.sqparc = sqlstm.sqharc;
 sqlstm.sqpadto = sqlstm.sqadto;
 sqlstm.sqptdso = sqlstm.sqtdso;
 sqlcxt(&vCtx, &sqlctx, &sqlstm, &sqlfpn);
}


	/* EXEC SQL FOR : vInsertCount SET DESCRIPTOR 'inMSE' VALUE 3 DATA = : vEpoch; */ 

{
 struct sqlexd sqlstm;
 sqlstm.sqlvsn = 13;
 sqlstm.arrsiz = 4;
 sqlstm.sqladtp = &sqladt;
 sqlstm.sqltdsp = &sqltds;
 sqlstm.stmt = "";
 sqlstm.iters = (unsigned int  )vInsertCount;
 sqlstm.offset = (unsigned int  )173;
 sqlstm.cud = sqlcud0;
 sqlstm.sqlest = (unsigned char  *)&sqlca;
 sqlstm.sqlety = (unsigned short)4352;
 sqlstm.occurs = (unsigned int  )3;
 sqlstm.sqhstv[0] = (         void  *)vEpoch;
 sqlstm.sqhstl[0] = (unsigned int  )sizeof(int);
 sqlstm.sqhsts[0] = (         int  )sizeof(int);
 sqlstm.sqindv[0] = (         void  *)0;
 sqlstm.sqinds[0] = (         int  )0;
 sqlstm.sqharm[0] = (unsigned int  )0;
 sqlstm.sqadto[0] = (unsigned short )0;
 sqlstm.sqtdso[0] = (unsigned short )0;
 sqlstm.sqphsv = sqlstm.sqhstv;
 sqlstm.sqphsl = sqlstm.sqhstl;
 sqlstm.sqphss = sqlstm.sqhsts;
 sqlstm.sqpind = sqlstm.sqindv;
 sqlstm.sqpins = sqlstm.sqinds;
 sqlstm.sqparm = sqlstm.sqharm;
 sqlstm.sqparc = sqlstm.sqharc;
 sqlstm.sqpadto = sqlstm.sqadto;
 sqlstm.sqptdso = sqlstm.sqtdso;
 sqlcxt(&vCtx, &sqlctx, &sqlstm, &sqlfpn);
}


	/* EXEC SQL FOR : vInsertCount SET DESCRIPTOR 'inMSE' VALUE 4 DATA = : vMSE_T; */ 

{
 struct sqlexd sqlstm;
 sqlstm.sqlvsn = 13;
 sqlstm.arrsiz = 4;
 sqlstm.sqladtp = &sqladt;
 sqlstm.sqltdsp = &sqltds;
 sqlstm.stmt = "";
 sqlstm.iters = (unsigned int  )vInsertCount;
 sqlstm.offset = (unsigned int  )197;
 sqlstm.cud = sqlcud0;
 sqlstm.sqlest = (unsigned char  *)&sqlca;
 sqlstm.sqlety = (unsigned short)4352;
 sqlstm.occurs = (unsigned int  )4;
 sqlstm.sqhstv[0] = (         void  *)vMSE_T;
 sqlstm.sqhstl[0] = (unsigned int  )sizeof(double);
 sqlstm.sqhsts[0] = (         int  )sizeof(double);
 sqlstm.sqindv[0] = (         void  *)0;
 sqlstm.sqinds[0] = (         int  )0;
 sqlstm.sqharm[0] = (unsigned int  )0;
 sqlstm.sqadto[0] = (unsigned short )0;
 sqlstm.sqtdso[0] = (unsigned short )0;
 sqlstm.sqphsv = sqlstm.sqhstv;
 sqlstm.sqphsl = sqlstm.sqhstl;
 sqlstm.sqphss = sqlstm.sqhsts;
 sqlstm.sqpind = sqlstm.sqindv;
 sqlstm.sqpins = sqlstm.sqinds;
 sqlstm.sqparm = sqlstm.sqharm;
 sqlstm.sqparc = sqlstm.sqharc;
 sqlstm.sqpadto = sqlstm.sqadto;
 sqlstm.sqptdso = sqlstm.sqtdso;
 sqlcxt(&vCtx, &sqlctx, &sqlstm, &sqlfpn);
}


	/* EXEC SQL FOR : vInsertCount SET DESCRIPTOR 'inMSE' VALUE 5 DATA = : vMSE_V; */ 

{
 struct sqlexd sqlstm;
 sqlstm.sqlvsn = 13;
 sqlstm.arrsiz = 4;
 sqlstm.sqladtp = &sqladt;
 sqlstm.sqltdsp = &sqltds;
 sqlstm.stmt = "";
 sqlstm.iters = (unsigned int  )vInsertCount;
 sqlstm.offset = (unsigned int  )221;
 sqlstm.cud = sqlcud0;
 sqlstm.sqlest = (unsigned char  *)&sqlca;
 sqlstm.sqlety = (unsigned short)4352;
 sqlstm.occurs = (unsigned int  )5;
 sqlstm.sqhstv[0] = (         void  *)vMSE_V;
 sqlstm.sqhstl[0] = (unsigned int  )sizeof(double);
 sqlstm.sqhsts[0] = (         int  )sizeof(double);
 sqlstm.sqindv[0] = (         void  *)0;
 sqlstm.sqinds[0] = (         int  )0;
 sqlstm.sqharm[0] = (unsigned int  )0;
 sqlstm.sqadto[0] = (unsigned short )0;
 sqlstm.sqtdso[0] = (unsigned short )0;
 sqlstm.sqphsv = sqlstm.sqhstv;
 sqlstm.sqphsl = sqlstm.sqhstl;
 sqlstm.sqphss = sqlstm.sqhsts;
 sqlstm.sqpind = sqlstm.sqindv;
 sqlstm.sqpins = sqlstm.sqinds;
 sqlstm.sqparm = sqlstm.sqharm;
 sqlstm.sqparc = sqlstm.sqharc;
 sqlstm.sqpadto = sqlstm.sqadto;
 sqlstm.sqptdso = sqlstm.sqtdso;
 sqlcxt(&vCtx, &sqlctx, &sqlstm, &sqlfpn);
}


	/* EXEC SQL PREPARE DynIns FROM : stmt; */ 

{
 struct sqlexd sqlstm;
 sqlstm.sqlvsn = 13;
 sqlstm.arrsiz = 4;
 sqlstm.sqladtp = &sqladt;
 sqlstm.sqltdsp = &sqltds;
 sqlstm.stmt = "";
 sqlstm.iters = (unsigned int  )1;
 sqlstm.offset = (unsigned int  )245;
 sqlstm.cud = sqlcud0;
 sqlstm.sqlest = (unsigned char  *)&sqlca;
 sqlstm.sqlety = (unsigned short)4352;
 sqlstm.occurs = (unsigned int  )0;
 sqlstm.sqhstv[0] = (         void  *)stmt;
 sqlstm.sqhstl[0] = (unsigned int  )1000;
 sqlstm.sqhsts[0] = (         int  )0;
 sqlstm.sqindv[0] = (         void  *)0;
 sqlstm.sqinds[0] = (         int  )0;
 sqlstm.sqharm[0] = (unsigned int  )0;
 sqlstm.sqadto[0] = (unsigned short )0;
 sqlstm.sqtdso[0] = (unsigned short )0;
 sqlstm.sqphsv = sqlstm.sqhstv;
 sqlstm.sqphsl = sqlstm.sqhstl;
 sqlstm.sqphss = sqlstm.sqhsts;
 sqlstm.sqpind = sqlstm.sqindv;
 sqlstm.sqpins = sqlstm.sqinds;
 sqlstm.sqparm = sqlstm.sqharm;
 sqlstm.sqparc = sqlstm.sqharc;
 sqlstm.sqpadto = sqlstm.sqadto;
 sqlstm.sqptdso = sqlstm.sqtdso;
 sqlcxt(&vCtx, &sqlctx, &sqlstm, &sqlfpn);
}


	/* EXEC SQL FOR : vInsertCount EXECUTE DynIns USING DESCRIPTOR 'inMSE'; */ 

{
 struct sqlexd sqlstm;
 sqlstm.sqlvsn = 13;
 sqlstm.arrsiz = 4;
 sqlstm.sqladtp = &sqladt;
 sqlstm.sqltdsp = &sqltds;
 sqlstm.stmt = "";
 sqlstm.iters = (unsigned int  )vInsertCount;
 sqlstm.offset = (unsigned int  )264;
 sqlstm.cud = sqlcud0;
 sqlstm.sqlest = (unsigned char  *)&sqlca;
 sqlstm.sqlety = (unsigned short)4352;
 sqlstm.occurs = (unsigned int  )0;
 sqlcxt(&vCtx, &sqlctx, &sqlstm, &sqlfpn);
}


	LogWrite(DebugParms, LOG_INFO, "Ora_InsertMSELog() CheckPoint 5\n", 0);
	//EXEC SQL ALTER SESSION SET SQL_TRACE = FALSE;

	//pInsertCount[vNetLevel] = sqlca.sqlerrd[2];
	LogWrite(DebugParms, LOG_INFO, "Ora_InsertMSELog() inserted %d rows.\n", 1, sqlca.sqlerrd[2]);
	if (sqlca.sqlcode != 0) {
		if (sqlca.sqlcode != 1) LogWrite(DebugParms, LOG_ERROR, "Ora_InsertMSELog failed. SQL Error %d\n", 1, sqlca.sqlcode);
		return sqlca.sqlcode;
	}
	/* EXEC SQL DEALLOCATE DESCRIPTOR 'inMSE'; */ 

{
 struct sqlexd sqlstm;
 sqlstm.sqlvsn = 13;
 sqlstm.arrsiz = 4;
 sqlstm.sqladtp = &sqladt;
 sqlstm.sqltdsp = &sqltds;
 sqlstm.stmt = "";
 sqlstm.iters = (unsigned int  )1;
 sqlstm.offset = (unsigned int  )284;
 sqlstm.cud = sqlcud0;
 sqlstm.sqlest = (unsigned char  *)&sqlca;
 sqlstm.sqlety = (unsigned short)4352;
 sqlstm.occurs = (unsigned int  )0;
 sqlcxt(&vCtx, &sqlctx, &sqlstm, &sqlfpn);
}



	//-- free()s
	free(vProcessId);
	free(vThreadId);
	free(vEpoch);
	free(vMSE_T);
	free(vMSE_V);

	return sqlca.sqlcode;
}
EXPORT int Ora_InsertRunLog(tDebugInfo* DebugParms, tDBConnection* DBConnInfo, int* pInsertCount, int pHistoryLen, tLogRUN* RunData) {
	//-- pHistoryLen only needed to know where to insert the "spacer"
	/* EXEC SQL BEGIN DECLARE SECTION; */ 

	int i;
	sql_context vCtx = DBConnInfo->DBCtx;
	int vInsertCount;
	char stmt[1000];
	//--
	int* vProcessId;
	int* vThreadId;
	int* vNetProcessId;
	int* vNetThreadId;
	//--
	int* vPos;
	double* vActual; double* vActual_TRS;
	double* vPredicted; double* vPredicted_TRS;
	double* vError; double* vError_TRS;
	double* vBarWidth;
	double* vErrorP;
	//--
	int dbl_type = 22;	// Oracle SQLT_BDOUBLE
	int int_type = 3;	// 
	unsigned int dbl_len = sizeof(double);
	unsigned int vchar_type = 96;
	unsigned int vchar_len = 12 + 1;

	/* EXEC SQL END   DECLARE SECTION; */ 


	//-- Connects to DB only once
	if (vCtx == NULL) {
		if (OraConnect(DebugParms, DBConnInfo) != 0) printf("Ora_BulkRunInsert() could not connect to Log Database...\n");
		vCtx = DBConnInfo->DBCtx;
	}

	vInsertCount = (*pInsertCount);

	vProcessId = (int*)malloc(vInsertCount*sizeof(int));
	vThreadId = (int*)malloc(vInsertCount*sizeof(int));
	vNetProcessId = (int*)malloc(vInsertCount*sizeof(int));
	vNetThreadId = (int*)malloc(vInsertCount*sizeof(int));
	vPos = (int*)malloc(vInsertCount*sizeof(int));
	vActual = (double*)malloc(vInsertCount*sizeof(double));
	vPredicted = (double*)malloc(vInsertCount*sizeof(double));
	vError = (double*)malloc(vInsertCount*sizeof(double));
	vActual_TRS = (double*)malloc(vInsertCount*sizeof(double));
	vPredicted_TRS = (double*)malloc(vInsertCount*sizeof(double));
	vError_TRS = (double*)malloc(vInsertCount*sizeof(double));
	vBarWidth = (double*)malloc(vInsertCount*sizeof(double));
	vErrorP = (double*)malloc(vInsertCount*sizeof(double));
	for (i = 0; i < vInsertCount; i++) {
		vProcessId[i] = RunData[i].ProcessId;
		vThreadId[i] = RunData[i].ThreadId;
		vNetProcessId[i] = RunData[i].NetProcessId;
		vNetThreadId[i] = RunData[i].NetThreadId;
		//--
		vPos[i] = RunData[i].Pos;
		vActual[i] = RunData[i].Actual;
		vPredicted[i] = RunData[i].Predicted;
		vError[i] = RunData[i].Error;
		vActual_TRS[i] = RunData[i].Actual_TRS;
		vPredicted_TRS[i] = RunData[i].Predicted_TRS;
		vError_TRS[i] = RunData[i].Error_TRS;
		vBarWidth[i] = RunData[i].BarWidth;
		vErrorP[i] = RunData[i].ErrorP;
		//LogWrite(DebugParms, LOG_INFO, "vProcessId[%d][%d][%d]=%d , vThreadId[%d][%d][%d]=%d , vTestId[%d][%d][%d]=%d , vNetId[%d][%d][%d]=%d, vPos[%d][%d][%d]=%d \n", 20, d, n, i, vProcessId[n][i], d, n, i, vThreadId[n][i], d, n, i, vTestId[n][i], d, n, i, vNetId[n][i], d, n, i, vPos[n][i]);
	}
	//-- Then, Build the Insert statement
	sprintf(&stmt[0], "insert into MyLog_Run (ProcessId, ThreadId, NetProcessId, NetThreadId, Pos, Actual, Predicted, Error, ActualC, PredictedC, ErrorC, BarWidth, ErrorP)");
	strcat(stmt, " values(:Run1, :Run2, :Run3, :Run4, :Run5, :Run6, :Run7, :Run8, :Run9, :Run10, :Run11, :Run12, :Run13)");

	/* EXEC SQL CONTEXT USE : vCtx; */ 

	//EXEC SQL ALTER SESSION SET EVENTS '10046 trace name context forever, level 4';
	//EXEC SQL ALTER SESSION SET SQL_TRACE = TRUE;
	/* EXEC SQL FOR : vInsertCount ALLOCATE DESCRIPTOR 'inRun'; */ 

{
 struct sqlexd sqlstm;
 sqlstm.sqlvsn = 13;
 sqlstm.arrsiz = 4;
 sqlstm.sqladtp = &sqladt;
 sqlstm.sqltdsp = &sqltds;
 sqlstm.stmt = "";
 sqlstm.iters = (unsigned int  )vInsertCount;
 sqlstm.offset = (unsigned int  )304;
 sqlstm.cud = sqlcud0;
 sqlstm.sqlest = (unsigned char  *)&sqlca;
 sqlstm.sqlety = (unsigned short)4352;
 sqlstm.occurs = (unsigned int  )100;
 sqlcxt(&vCtx, &sqlctx, &sqlstm, &sqlfpn);
}


	/* EXEC SQL SET DESCRIPTOR 'inRun' VALUE 1 TYPE = :int_type; */ 

{
 struct sqlexd sqlstm;
 sqlstm.sqlvsn = 13;
 sqlstm.arrsiz = 4;
 sqlstm.sqladtp = &sqladt;
 sqlstm.sqltdsp = &sqltds;
 sqlstm.stmt = "";
 sqlstm.iters = (unsigned int  )1;
 sqlstm.offset = (unsigned int  )324;
 sqlstm.cud = sqlcud0;
 sqlstm.sqlest = (unsigned char  *)&sqlca;
 sqlstm.sqlety = (unsigned short)4352;
 sqlstm.occurs = (unsigned int  )1;
 sqlstm.sqhstv[0] = (         void  *)&int_type;
 sqlstm.sqhstl[0] = (unsigned int  )sizeof(int);
 sqlstm.sqhsts[0] = (         int  )0;
 sqlstm.sqindv[0] = (         void  *)0;
 sqlstm.sqinds[0] = (         int  )0;
 sqlstm.sqharm[0] = (unsigned int  )0;
 sqlstm.sqadto[0] = (unsigned short )0;
 sqlstm.sqtdso[0] = (unsigned short )0;
 sqlstm.sqphsv = sqlstm.sqhstv;
 sqlstm.sqphsl = sqlstm.sqhstl;
 sqlstm.sqphss = sqlstm.sqhsts;
 sqlstm.sqpind = sqlstm.sqindv;
 sqlstm.sqpins = sqlstm.sqinds;
 sqlstm.sqparm = sqlstm.sqharm;
 sqlstm.sqparc = sqlstm.sqharc;
 sqlstm.sqpadto = sqlstm.sqadto;
 sqlstm.sqptdso = sqlstm.sqtdso;
 sqlcxt(&vCtx, &sqlctx, &sqlstm, &sqlfpn);
}


	/* EXEC SQL SET DESCRIPTOR 'inRun' VALUE 2 TYPE = :int_type; */ 

{
 struct sqlexd sqlstm;
 sqlstm.sqlvsn = 13;
 sqlstm.arrsiz = 4;
 sqlstm.sqladtp = &sqladt;
 sqlstm.sqltdsp = &sqltds;
 sqlstm.stmt = "";
 sqlstm.iters = (unsigned int  )1;
 sqlstm.offset = (unsigned int  )348;
 sqlstm.cud = sqlcud0;
 sqlstm.sqlest = (unsigned char  *)&sqlca;
 sqlstm.sqlety = (unsigned short)4352;
 sqlstm.occurs = (unsigned int  )2;
 sqlstm.sqhstv[0] = (         void  *)&int_type;
 sqlstm.sqhstl[0] = (unsigned int  )sizeof(int);
 sqlstm.sqhsts[0] = (         int  )0;
 sqlstm.sqindv[0] = (         void  *)0;
 sqlstm.sqinds[0] = (         int  )0;
 sqlstm.sqharm[0] = (unsigned int  )0;
 sqlstm.sqadto[0] = (unsigned short )0;
 sqlstm.sqtdso[0] = (unsigned short )0;
 sqlstm.sqphsv = sqlstm.sqhstv;
 sqlstm.sqphsl = sqlstm.sqhstl;
 sqlstm.sqphss = sqlstm.sqhsts;
 sqlstm.sqpind = sqlstm.sqindv;
 sqlstm.sqpins = sqlstm.sqinds;
 sqlstm.sqparm = sqlstm.sqharm;
 sqlstm.sqparc = sqlstm.sqharc;
 sqlstm.sqpadto = sqlstm.sqadto;
 sqlstm.sqptdso = sqlstm.sqtdso;
 sqlcxt(&vCtx, &sqlctx, &sqlstm, &sqlfpn);
}


	/* EXEC SQL SET DESCRIPTOR 'inRun' VALUE 3 TYPE = :int_type; */ 

{
 struct sqlexd sqlstm;
 sqlstm.sqlvsn = 13;
 sqlstm.arrsiz = 4;
 sqlstm.sqladtp = &sqladt;
 sqlstm.sqltdsp = &sqltds;
 sqlstm.stmt = "";
 sqlstm.iters = (unsigned int  )1;
 sqlstm.offset = (unsigned int  )372;
 sqlstm.cud = sqlcud0;
 sqlstm.sqlest = (unsigned char  *)&sqlca;
 sqlstm.sqlety = (unsigned short)4352;
 sqlstm.occurs = (unsigned int  )3;
 sqlstm.sqhstv[0] = (         void  *)&int_type;
 sqlstm.sqhstl[0] = (unsigned int  )sizeof(int);
 sqlstm.sqhsts[0] = (         int  )0;
 sqlstm.sqindv[0] = (         void  *)0;
 sqlstm.sqinds[0] = (         int  )0;
 sqlstm.sqharm[0] = (unsigned int  )0;
 sqlstm.sqadto[0] = (unsigned short )0;
 sqlstm.sqtdso[0] = (unsigned short )0;
 sqlstm.sqphsv = sqlstm.sqhstv;
 sqlstm.sqphsl = sqlstm.sqhstl;
 sqlstm.sqphss = sqlstm.sqhsts;
 sqlstm.sqpind = sqlstm.sqindv;
 sqlstm.sqpins = sqlstm.sqinds;
 sqlstm.sqparm = sqlstm.sqharm;
 sqlstm.sqparc = sqlstm.sqharc;
 sqlstm.sqpadto = sqlstm.sqadto;
 sqlstm.sqptdso = sqlstm.sqtdso;
 sqlcxt(&vCtx, &sqlctx, &sqlstm, &sqlfpn);
}


	/* EXEC SQL SET DESCRIPTOR 'inRun' VALUE 4 TYPE = :int_type; */ 

{
 struct sqlexd sqlstm;
 sqlstm.sqlvsn = 13;
 sqlstm.arrsiz = 4;
 sqlstm.sqladtp = &sqladt;
 sqlstm.sqltdsp = &sqltds;
 sqlstm.stmt = "";
 sqlstm.iters = (unsigned int  )1;
 sqlstm.offset = (unsigned int  )396;
 sqlstm.cud = sqlcud0;
 sqlstm.sqlest = (unsigned char  *)&sqlca;
 sqlstm.sqlety = (unsigned short)4352;
 sqlstm.occurs = (unsigned int  )4;
 sqlstm.sqhstv[0] = (         void  *)&int_type;
 sqlstm.sqhstl[0] = (unsigned int  )sizeof(int);
 sqlstm.sqhsts[0] = (         int  )0;
 sqlstm.sqindv[0] = (         void  *)0;
 sqlstm.sqinds[0] = (         int  )0;
 sqlstm.sqharm[0] = (unsigned int  )0;
 sqlstm.sqadto[0] = (unsigned short )0;
 sqlstm.sqtdso[0] = (unsigned short )0;
 sqlstm.sqphsv = sqlstm.sqhstv;
 sqlstm.sqphsl = sqlstm.sqhstl;
 sqlstm.sqphss = sqlstm.sqhsts;
 sqlstm.sqpind = sqlstm.sqindv;
 sqlstm.sqpins = sqlstm.sqinds;
 sqlstm.sqparm = sqlstm.sqharm;
 sqlstm.sqparc = sqlstm.sqharc;
 sqlstm.sqpadto = sqlstm.sqadto;
 sqlstm.sqptdso = sqlstm.sqtdso;
 sqlcxt(&vCtx, &sqlctx, &sqlstm, &sqlfpn);
}


	/* EXEC SQL SET DESCRIPTOR 'inRun' VALUE 5 TYPE = :int_type; */ 

{
 struct sqlexd sqlstm;
 sqlstm.sqlvsn = 13;
 sqlstm.arrsiz = 4;
 sqlstm.sqladtp = &sqladt;
 sqlstm.sqltdsp = &sqltds;
 sqlstm.stmt = "";
 sqlstm.iters = (unsigned int  )1;
 sqlstm.offset = (unsigned int  )420;
 sqlstm.cud = sqlcud0;
 sqlstm.sqlest = (unsigned char  *)&sqlca;
 sqlstm.sqlety = (unsigned short)4352;
 sqlstm.occurs = (unsigned int  )5;
 sqlstm.sqhstv[0] = (         void  *)&int_type;
 sqlstm.sqhstl[0] = (unsigned int  )sizeof(int);
 sqlstm.sqhsts[0] = (         int  )0;
 sqlstm.sqindv[0] = (         void  *)0;
 sqlstm.sqinds[0] = (         int  )0;
 sqlstm.sqharm[0] = (unsigned int  )0;
 sqlstm.sqadto[0] = (unsigned short )0;
 sqlstm.sqtdso[0] = (unsigned short )0;
 sqlstm.sqphsv = sqlstm.sqhstv;
 sqlstm.sqphsl = sqlstm.sqhstl;
 sqlstm.sqphss = sqlstm.sqhsts;
 sqlstm.sqpind = sqlstm.sqindv;
 sqlstm.sqpins = sqlstm.sqinds;
 sqlstm.sqparm = sqlstm.sqharm;
 sqlstm.sqparc = sqlstm.sqharc;
 sqlstm.sqpadto = sqlstm.sqadto;
 sqlstm.sqptdso = sqlstm.sqtdso;
 sqlcxt(&vCtx, &sqlctx, &sqlstm, &sqlfpn);
}


	/* EXEC SQL SET DESCRIPTOR 'inRun' VALUE 6 TYPE = :dbl_type; */ 

{
 struct sqlexd sqlstm;
 sqlstm.sqlvsn = 13;
 sqlstm.arrsiz = 4;
 sqlstm.sqladtp = &sqladt;
 sqlstm.sqltdsp = &sqltds;
 sqlstm.stmt = "";
 sqlstm.iters = (unsigned int  )1;
 sqlstm.offset = (unsigned int  )444;
 sqlstm.cud = sqlcud0;
 sqlstm.sqlest = (unsigned char  *)&sqlca;
 sqlstm.sqlety = (unsigned short)4352;
 sqlstm.occurs = (unsigned int  )6;
 sqlstm.sqhstv[0] = (         void  *)&dbl_type;
 sqlstm.sqhstl[0] = (unsigned int  )sizeof(int);
 sqlstm.sqhsts[0] = (         int  )0;
 sqlstm.sqindv[0] = (         void  *)0;
 sqlstm.sqinds[0] = (         int  )0;
 sqlstm.sqharm[0] = (unsigned int  )0;
 sqlstm.sqadto[0] = (unsigned short )0;
 sqlstm.sqtdso[0] = (unsigned short )0;
 sqlstm.sqphsv = sqlstm.sqhstv;
 sqlstm.sqphsl = sqlstm.sqhstl;
 sqlstm.sqphss = sqlstm.sqhsts;
 sqlstm.sqpind = sqlstm.sqindv;
 sqlstm.sqpins = sqlstm.sqinds;
 sqlstm.sqparm = sqlstm.sqharm;
 sqlstm.sqparc = sqlstm.sqharc;
 sqlstm.sqpadto = sqlstm.sqadto;
 sqlstm.sqptdso = sqlstm.sqtdso;
 sqlcxt(&vCtx, &sqlctx, &sqlstm, &sqlfpn);
}


	/* EXEC SQL SET DESCRIPTOR 'inRun' VALUE 7 TYPE = :dbl_type; */ 

{
 struct sqlexd sqlstm;
 sqlstm.sqlvsn = 13;
 sqlstm.arrsiz = 4;
 sqlstm.sqladtp = &sqladt;
 sqlstm.sqltdsp = &sqltds;
 sqlstm.stmt = "";
 sqlstm.iters = (unsigned int  )1;
 sqlstm.offset = (unsigned int  )468;
 sqlstm.cud = sqlcud0;
 sqlstm.sqlest = (unsigned char  *)&sqlca;
 sqlstm.sqlety = (unsigned short)4352;
 sqlstm.occurs = (unsigned int  )7;
 sqlstm.sqhstv[0] = (         void  *)&dbl_type;
 sqlstm.sqhstl[0] = (unsigned int  )sizeof(int);
 sqlstm.sqhsts[0] = (         int  )0;
 sqlstm.sqindv[0] = (         void  *)0;
 sqlstm.sqinds[0] = (         int  )0;
 sqlstm.sqharm[0] = (unsigned int  )0;
 sqlstm.sqadto[0] = (unsigned short )0;
 sqlstm.sqtdso[0] = (unsigned short )0;
 sqlstm.sqphsv = sqlstm.sqhstv;
 sqlstm.sqphsl = sqlstm.sqhstl;
 sqlstm.sqphss = sqlstm.sqhsts;
 sqlstm.sqpind = sqlstm.sqindv;
 sqlstm.sqpins = sqlstm.sqinds;
 sqlstm.sqparm = sqlstm.sqharm;
 sqlstm.sqparc = sqlstm.sqharc;
 sqlstm.sqpadto = sqlstm.sqadto;
 sqlstm.sqptdso = sqlstm.sqtdso;
 sqlcxt(&vCtx, &sqlctx, &sqlstm, &sqlfpn);
}


	/* EXEC SQL SET DESCRIPTOR 'inRun' VALUE 8 TYPE = :dbl_type; */ 

{
 struct sqlexd sqlstm;
 sqlstm.sqlvsn = 13;
 sqlstm.arrsiz = 4;
 sqlstm.sqladtp = &sqladt;
 sqlstm.sqltdsp = &sqltds;
 sqlstm.stmt = "";
 sqlstm.iters = (unsigned int  )1;
 sqlstm.offset = (unsigned int  )492;
 sqlstm.cud = sqlcud0;
 sqlstm.sqlest = (unsigned char  *)&sqlca;
 sqlstm.sqlety = (unsigned short)4352;
 sqlstm.occurs = (unsigned int  )8;
 sqlstm.sqhstv[0] = (         void  *)&dbl_type;
 sqlstm.sqhstl[0] = (unsigned int  )sizeof(int);
 sqlstm.sqhsts[0] = (         int  )0;
 sqlstm.sqindv[0] = (         void  *)0;
 sqlstm.sqinds[0] = (         int  )0;
 sqlstm.sqharm[0] = (unsigned int  )0;
 sqlstm.sqadto[0] = (unsigned short )0;
 sqlstm.sqtdso[0] = (unsigned short )0;
 sqlstm.sqphsv = sqlstm.sqhstv;
 sqlstm.sqphsl = sqlstm.sqhstl;
 sqlstm.sqphss = sqlstm.sqhsts;
 sqlstm.sqpind = sqlstm.sqindv;
 sqlstm.sqpins = sqlstm.sqinds;
 sqlstm.sqparm = sqlstm.sqharm;
 sqlstm.sqparc = sqlstm.sqharc;
 sqlstm.sqpadto = sqlstm.sqadto;
 sqlstm.sqptdso = sqlstm.sqtdso;
 sqlcxt(&vCtx, &sqlctx, &sqlstm, &sqlfpn);
}


	/* EXEC SQL SET DESCRIPTOR 'inRun' VALUE 9 TYPE = :dbl_type; */ 

{
 struct sqlexd sqlstm;
 sqlstm.sqlvsn = 13;
 sqlstm.arrsiz = 4;
 sqlstm.sqladtp = &sqladt;
 sqlstm.sqltdsp = &sqltds;
 sqlstm.stmt = "";
 sqlstm.iters = (unsigned int  )1;
 sqlstm.offset = (unsigned int  )516;
 sqlstm.cud = sqlcud0;
 sqlstm.sqlest = (unsigned char  *)&sqlca;
 sqlstm.sqlety = (unsigned short)4352;
 sqlstm.occurs = (unsigned int  )9;
 sqlstm.sqhstv[0] = (         void  *)&dbl_type;
 sqlstm.sqhstl[0] = (unsigned int  )sizeof(int);
 sqlstm.sqhsts[0] = (         int  )0;
 sqlstm.sqindv[0] = (         void  *)0;
 sqlstm.sqinds[0] = (         int  )0;
 sqlstm.sqharm[0] = (unsigned int  )0;
 sqlstm.sqadto[0] = (unsigned short )0;
 sqlstm.sqtdso[0] = (unsigned short )0;
 sqlstm.sqphsv = sqlstm.sqhstv;
 sqlstm.sqphsl = sqlstm.sqhstl;
 sqlstm.sqphss = sqlstm.sqhsts;
 sqlstm.sqpind = sqlstm.sqindv;
 sqlstm.sqpins = sqlstm.sqinds;
 sqlstm.sqparm = sqlstm.sqharm;
 sqlstm.sqparc = sqlstm.sqharc;
 sqlstm.sqpadto = sqlstm.sqadto;
 sqlstm.sqptdso = sqlstm.sqtdso;
 sqlcxt(&vCtx, &sqlctx, &sqlstm, &sqlfpn);
}


	/* EXEC SQL SET DESCRIPTOR 'inRun' VALUE 10 TYPE = :dbl_type; */ 

{
 struct sqlexd sqlstm;
 sqlstm.sqlvsn = 13;
 sqlstm.arrsiz = 4;
 sqlstm.sqladtp = &sqladt;
 sqlstm.sqltdsp = &sqltds;
 sqlstm.stmt = "";
 sqlstm.iters = (unsigned int  )1;
 sqlstm.offset = (unsigned int  )540;
 sqlstm.cud = sqlcud0;
 sqlstm.sqlest = (unsigned char  *)&sqlca;
 sqlstm.sqlety = (unsigned short)4352;
 sqlstm.occurs = (unsigned int  )10;
 sqlstm.sqhstv[0] = (         void  *)&dbl_type;
 sqlstm.sqhstl[0] = (unsigned int  )sizeof(int);
 sqlstm.sqhsts[0] = (         int  )0;
 sqlstm.sqindv[0] = (         void  *)0;
 sqlstm.sqinds[0] = (         int  )0;
 sqlstm.sqharm[0] = (unsigned int  )0;
 sqlstm.sqadto[0] = (unsigned short )0;
 sqlstm.sqtdso[0] = (unsigned short )0;
 sqlstm.sqphsv = sqlstm.sqhstv;
 sqlstm.sqphsl = sqlstm.sqhstl;
 sqlstm.sqphss = sqlstm.sqhsts;
 sqlstm.sqpind = sqlstm.sqindv;
 sqlstm.sqpins = sqlstm.sqinds;
 sqlstm.sqparm = sqlstm.sqharm;
 sqlstm.sqparc = sqlstm.sqharc;
 sqlstm.sqpadto = sqlstm.sqadto;
 sqlstm.sqptdso = sqlstm.sqtdso;
 sqlcxt(&vCtx, &sqlctx, &sqlstm, &sqlfpn);
}


	/* EXEC SQL SET DESCRIPTOR 'inRun' VALUE 11 TYPE = :dbl_type; */ 

{
 struct sqlexd sqlstm;
 sqlstm.sqlvsn = 13;
 sqlstm.arrsiz = 4;
 sqlstm.sqladtp = &sqladt;
 sqlstm.sqltdsp = &sqltds;
 sqlstm.stmt = "";
 sqlstm.iters = (unsigned int  )1;
 sqlstm.offset = (unsigned int  )564;
 sqlstm.cud = sqlcud0;
 sqlstm.sqlest = (unsigned char  *)&sqlca;
 sqlstm.sqlety = (unsigned short)4352;
 sqlstm.occurs = (unsigned int  )11;
 sqlstm.sqhstv[0] = (         void  *)&dbl_type;
 sqlstm.sqhstl[0] = (unsigned int  )sizeof(int);
 sqlstm.sqhsts[0] = (         int  )0;
 sqlstm.sqindv[0] = (         void  *)0;
 sqlstm.sqinds[0] = (         int  )0;
 sqlstm.sqharm[0] = (unsigned int  )0;
 sqlstm.sqadto[0] = (unsigned short )0;
 sqlstm.sqtdso[0] = (unsigned short )0;
 sqlstm.sqphsv = sqlstm.sqhstv;
 sqlstm.sqphsl = sqlstm.sqhstl;
 sqlstm.sqphss = sqlstm.sqhsts;
 sqlstm.sqpind = sqlstm.sqindv;
 sqlstm.sqpins = sqlstm.sqinds;
 sqlstm.sqparm = sqlstm.sqharm;
 sqlstm.sqparc = sqlstm.sqharc;
 sqlstm.sqpadto = sqlstm.sqadto;
 sqlstm.sqptdso = sqlstm.sqtdso;
 sqlcxt(&vCtx, &sqlctx, &sqlstm, &sqlfpn);
}


	/* EXEC SQL SET DESCRIPTOR 'inRun' VALUE 12 TYPE = :dbl_type; */ 

{
 struct sqlexd sqlstm;
 sqlstm.sqlvsn = 13;
 sqlstm.arrsiz = 4;
 sqlstm.sqladtp = &sqladt;
 sqlstm.sqltdsp = &sqltds;
 sqlstm.stmt = "";
 sqlstm.iters = (unsigned int  )1;
 sqlstm.offset = (unsigned int  )588;
 sqlstm.cud = sqlcud0;
 sqlstm.sqlest = (unsigned char  *)&sqlca;
 sqlstm.sqlety = (unsigned short)4352;
 sqlstm.occurs = (unsigned int  )12;
 sqlstm.sqhstv[0] = (         void  *)&dbl_type;
 sqlstm.sqhstl[0] = (unsigned int  )sizeof(int);
 sqlstm.sqhsts[0] = (         int  )0;
 sqlstm.sqindv[0] = (         void  *)0;
 sqlstm.sqinds[0] = (         int  )0;
 sqlstm.sqharm[0] = (unsigned int  )0;
 sqlstm.sqadto[0] = (unsigned short )0;
 sqlstm.sqtdso[0] = (unsigned short )0;
 sqlstm.sqphsv = sqlstm.sqhstv;
 sqlstm.sqphsl = sqlstm.sqhstl;
 sqlstm.sqphss = sqlstm.sqhsts;
 sqlstm.sqpind = sqlstm.sqindv;
 sqlstm.sqpins = sqlstm.sqinds;
 sqlstm.sqparm = sqlstm.sqharm;
 sqlstm.sqparc = sqlstm.sqharc;
 sqlstm.sqpadto = sqlstm.sqadto;
 sqlstm.sqptdso = sqlstm.sqtdso;
 sqlcxt(&vCtx, &sqlctx, &sqlstm, &sqlfpn);
}


	/* EXEC SQL SET DESCRIPTOR 'inRun' VALUE 13 TYPE = :dbl_type; */ 

{
 struct sqlexd sqlstm;
 sqlstm.sqlvsn = 13;
 sqlstm.arrsiz = 4;
 sqlstm.sqladtp = &sqladt;
 sqlstm.sqltdsp = &sqltds;
 sqlstm.stmt = "";
 sqlstm.iters = (unsigned int  )1;
 sqlstm.offset = (unsigned int  )612;
 sqlstm.cud = sqlcud0;
 sqlstm.sqlest = (unsigned char  *)&sqlca;
 sqlstm.sqlety = (unsigned short)4352;
 sqlstm.occurs = (unsigned int  )13;
 sqlstm.sqhstv[0] = (         void  *)&dbl_type;
 sqlstm.sqhstl[0] = (unsigned int  )sizeof(int);
 sqlstm.sqhsts[0] = (         int  )0;
 sqlstm.sqindv[0] = (         void  *)0;
 sqlstm.sqinds[0] = (         int  )0;
 sqlstm.sqharm[0] = (unsigned int  )0;
 sqlstm.sqadto[0] = (unsigned short )0;
 sqlstm.sqtdso[0] = (unsigned short )0;
 sqlstm.sqphsv = sqlstm.sqhstv;
 sqlstm.sqphsl = sqlstm.sqhstl;
 sqlstm.sqphss = sqlstm.sqhsts;
 sqlstm.sqpind = sqlstm.sqindv;
 sqlstm.sqpins = sqlstm.sqinds;
 sqlstm.sqparm = sqlstm.sqharm;
 sqlstm.sqparc = sqlstm.sqharc;
 sqlstm.sqpadto = sqlstm.sqadto;
 sqlstm.sqptdso = sqlstm.sqtdso;
 sqlcxt(&vCtx, &sqlctx, &sqlstm, &sqlfpn);
}



	/* EXEC SQL SET DESCRIPTOR 'inRun' COUNT = 13; */ 

{
 struct sqlexd sqlstm;
 sqlstm.sqlvsn = 13;
 sqlstm.arrsiz = 4;
 sqlstm.sqladtp = &sqladt;
 sqlstm.sqltdsp = &sqltds;
 sqlstm.stmt = "";
 sqlstm.iters = (unsigned int  )1;
 sqlstm.offset = (unsigned int  )636;
 sqlstm.cud = sqlcud0;
 sqlstm.sqlest = (unsigned char  *)&sqlca;
 sqlstm.sqlety = (unsigned short)4352;
 sqlstm.occurs = (unsigned int  )13;
 sqlcxt(&vCtx, &sqlctx, &sqlstm, &sqlfpn);
}


	/* EXEC SQL FOR : vInsertCount SET DESCRIPTOR 'inRun' VALUE 1 DATA = : vProcessId; */ 

{
 struct sqlexd sqlstm;
 sqlstm.sqlvsn = 13;
 sqlstm.arrsiz = 4;
 sqlstm.sqladtp = &sqladt;
 sqlstm.sqltdsp = &sqltds;
 sqlstm.stmt = "";
 sqlstm.iters = (unsigned int  )vInsertCount;
 sqlstm.offset = (unsigned int  )656;
 sqlstm.cud = sqlcud0;
 sqlstm.sqlest = (unsigned char  *)&sqlca;
 sqlstm.sqlety = (unsigned short)4352;
 sqlstm.occurs = (unsigned int  )1;
 sqlstm.sqhstv[0] = (         void  *)vProcessId;
 sqlstm.sqhstl[0] = (unsigned int  )sizeof(int);
 sqlstm.sqhsts[0] = (         int  )sizeof(int);
 sqlstm.sqindv[0] = (         void  *)0;
 sqlstm.sqinds[0] = (         int  )0;
 sqlstm.sqharm[0] = (unsigned int  )0;
 sqlstm.sqadto[0] = (unsigned short )0;
 sqlstm.sqtdso[0] = (unsigned short )0;
 sqlstm.sqphsv = sqlstm.sqhstv;
 sqlstm.sqphsl = sqlstm.sqhstl;
 sqlstm.sqphss = sqlstm.sqhsts;
 sqlstm.sqpind = sqlstm.sqindv;
 sqlstm.sqpins = sqlstm.sqinds;
 sqlstm.sqparm = sqlstm.sqharm;
 sqlstm.sqparc = sqlstm.sqharc;
 sqlstm.sqpadto = sqlstm.sqadto;
 sqlstm.sqptdso = sqlstm.sqtdso;
 sqlcxt(&vCtx, &sqlctx, &sqlstm, &sqlfpn);
}


	/* EXEC SQL FOR : vInsertCount SET DESCRIPTOR 'inRun' VALUE 2 DATA = : vThreadId; */ 

{
 struct sqlexd sqlstm;
 sqlstm.sqlvsn = 13;
 sqlstm.arrsiz = 4;
 sqlstm.sqladtp = &sqladt;
 sqlstm.sqltdsp = &sqltds;
 sqlstm.stmt = "";
 sqlstm.iters = (unsigned int  )vInsertCount;
 sqlstm.offset = (unsigned int  )680;
 sqlstm.cud = sqlcud0;
 sqlstm.sqlest = (unsigned char  *)&sqlca;
 sqlstm.sqlety = (unsigned short)4352;
 sqlstm.occurs = (unsigned int  )2;
 sqlstm.sqhstv[0] = (         void  *)vThreadId;
 sqlstm.sqhstl[0] = (unsigned int  )sizeof(int);
 sqlstm.sqhsts[0] = (         int  )sizeof(int);
 sqlstm.sqindv[0] = (         void  *)0;
 sqlstm.sqinds[0] = (         int  )0;
 sqlstm.sqharm[0] = (unsigned int  )0;
 sqlstm.sqadto[0] = (unsigned short )0;
 sqlstm.sqtdso[0] = (unsigned short )0;
 sqlstm.sqphsv = sqlstm.sqhstv;
 sqlstm.sqphsl = sqlstm.sqhstl;
 sqlstm.sqphss = sqlstm.sqhsts;
 sqlstm.sqpind = sqlstm.sqindv;
 sqlstm.sqpins = sqlstm.sqinds;
 sqlstm.sqparm = sqlstm.sqharm;
 sqlstm.sqparc = sqlstm.sqharc;
 sqlstm.sqpadto = sqlstm.sqadto;
 sqlstm.sqptdso = sqlstm.sqtdso;
 sqlcxt(&vCtx, &sqlctx, &sqlstm, &sqlfpn);
}


	/* EXEC SQL FOR : vInsertCount SET DESCRIPTOR 'inRun' VALUE 3 DATA = : vNetProcessId; */ 

{
 struct sqlexd sqlstm;
 sqlstm.sqlvsn = 13;
 sqlstm.arrsiz = 4;
 sqlstm.sqladtp = &sqladt;
 sqlstm.sqltdsp = &sqltds;
 sqlstm.stmt = "";
 sqlstm.iters = (unsigned int  )vInsertCount;
 sqlstm.offset = (unsigned int  )704;
 sqlstm.cud = sqlcud0;
 sqlstm.sqlest = (unsigned char  *)&sqlca;
 sqlstm.sqlety = (unsigned short)4352;
 sqlstm.occurs = (unsigned int  )3;
 sqlstm.sqhstv[0] = (         void  *)vNetProcessId;
 sqlstm.sqhstl[0] = (unsigned int  )sizeof(int);
 sqlstm.sqhsts[0] = (         int  )sizeof(int);
 sqlstm.sqindv[0] = (         void  *)0;
 sqlstm.sqinds[0] = (         int  )0;
 sqlstm.sqharm[0] = (unsigned int  )0;
 sqlstm.sqadto[0] = (unsigned short )0;
 sqlstm.sqtdso[0] = (unsigned short )0;
 sqlstm.sqphsv = sqlstm.sqhstv;
 sqlstm.sqphsl = sqlstm.sqhstl;
 sqlstm.sqphss = sqlstm.sqhsts;
 sqlstm.sqpind = sqlstm.sqindv;
 sqlstm.sqpins = sqlstm.sqinds;
 sqlstm.sqparm = sqlstm.sqharm;
 sqlstm.sqparc = sqlstm.sqharc;
 sqlstm.sqpadto = sqlstm.sqadto;
 sqlstm.sqptdso = sqlstm.sqtdso;
 sqlcxt(&vCtx, &sqlctx, &sqlstm, &sqlfpn);
}


	/* EXEC SQL FOR : vInsertCount SET DESCRIPTOR 'inRun' VALUE 4 DATA = : vNetThreadId; */ 

{
 struct sqlexd sqlstm;
 sqlstm.sqlvsn = 13;
 sqlstm.arrsiz = 4;
 sqlstm.sqladtp = &sqladt;
 sqlstm.sqltdsp = &sqltds;
 sqlstm.stmt = "";
 sqlstm.iters = (unsigned int  )vInsertCount;
 sqlstm.offset = (unsigned int  )728;
 sqlstm.cud = sqlcud0;
 sqlstm.sqlest = (unsigned char  *)&sqlca;
 sqlstm.sqlety = (unsigned short)4352;
 sqlstm.occurs = (unsigned int  )4;
 sqlstm.sqhstv[0] = (         void  *)vNetThreadId;
 sqlstm.sqhstl[0] = (unsigned int  )sizeof(int);
 sqlstm.sqhsts[0] = (         int  )sizeof(int);
 sqlstm.sqindv[0] = (         void  *)0;
 sqlstm.sqinds[0] = (         int  )0;
 sqlstm.sqharm[0] = (unsigned int  )0;
 sqlstm.sqadto[0] = (unsigned short )0;
 sqlstm.sqtdso[0] = (unsigned short )0;
 sqlstm.sqphsv = sqlstm.sqhstv;
 sqlstm.sqphsl = sqlstm.sqhstl;
 sqlstm.sqphss = sqlstm.sqhsts;
 sqlstm.sqpind = sqlstm.sqindv;
 sqlstm.sqpins = sqlstm.sqinds;
 sqlstm.sqparm = sqlstm.sqharm;
 sqlstm.sqparc = sqlstm.sqharc;
 sqlstm.sqpadto = sqlstm.sqadto;
 sqlstm.sqptdso = sqlstm.sqtdso;
 sqlcxt(&vCtx, &sqlctx, &sqlstm, &sqlfpn);
}


	/* EXEC SQL FOR : vInsertCount SET DESCRIPTOR 'inRun' VALUE 5 DATA = : vPos; */ 

{
 struct sqlexd sqlstm;
 sqlstm.sqlvsn = 13;
 sqlstm.arrsiz = 4;
 sqlstm.sqladtp = &sqladt;
 sqlstm.sqltdsp = &sqltds;
 sqlstm.stmt = "";
 sqlstm.iters = (unsigned int  )vInsertCount;
 sqlstm.offset = (unsigned int  )752;
 sqlstm.cud = sqlcud0;
 sqlstm.sqlest = (unsigned char  *)&sqlca;
 sqlstm.sqlety = (unsigned short)4352;
 sqlstm.occurs = (unsigned int  )5;
 sqlstm.sqhstv[0] = (         void  *)vPos;
 sqlstm.sqhstl[0] = (unsigned int  )sizeof(int);
 sqlstm.sqhsts[0] = (         int  )sizeof(int);
 sqlstm.sqindv[0] = (         void  *)0;
 sqlstm.sqinds[0] = (         int  )0;
 sqlstm.sqharm[0] = (unsigned int  )0;
 sqlstm.sqadto[0] = (unsigned short )0;
 sqlstm.sqtdso[0] = (unsigned short )0;
 sqlstm.sqphsv = sqlstm.sqhstv;
 sqlstm.sqphsl = sqlstm.sqhstl;
 sqlstm.sqphss = sqlstm.sqhsts;
 sqlstm.sqpind = sqlstm.sqindv;
 sqlstm.sqpins = sqlstm.sqinds;
 sqlstm.sqparm = sqlstm.sqharm;
 sqlstm.sqparc = sqlstm.sqharc;
 sqlstm.sqpadto = sqlstm.sqadto;
 sqlstm.sqptdso = sqlstm.sqtdso;
 sqlcxt(&vCtx, &sqlctx, &sqlstm, &sqlfpn);
}


	/* EXEC SQL FOR : vInsertCount SET DESCRIPTOR 'inRun' VALUE 6 DATA = : vActual; */ 

{
 struct sqlexd sqlstm;
 sqlstm.sqlvsn = 13;
 sqlstm.arrsiz = 4;
 sqlstm.sqladtp = &sqladt;
 sqlstm.sqltdsp = &sqltds;
 sqlstm.stmt = "";
 sqlstm.iters = (unsigned int  )vInsertCount;
 sqlstm.offset = (unsigned int  )776;
 sqlstm.cud = sqlcud0;
 sqlstm.sqlest = (unsigned char  *)&sqlca;
 sqlstm.sqlety = (unsigned short)4352;
 sqlstm.occurs = (unsigned int  )6;
 sqlstm.sqhstv[0] = (         void  *)vActual;
 sqlstm.sqhstl[0] = (unsigned int  )sizeof(double);
 sqlstm.sqhsts[0] = (         int  )sizeof(double);
 sqlstm.sqindv[0] = (         void  *)0;
 sqlstm.sqinds[0] = (         int  )0;
 sqlstm.sqharm[0] = (unsigned int  )0;
 sqlstm.sqadto[0] = (unsigned short )0;
 sqlstm.sqtdso[0] = (unsigned short )0;
 sqlstm.sqphsv = sqlstm.sqhstv;
 sqlstm.sqphsl = sqlstm.sqhstl;
 sqlstm.sqphss = sqlstm.sqhsts;
 sqlstm.sqpind = sqlstm.sqindv;
 sqlstm.sqpins = sqlstm.sqinds;
 sqlstm.sqparm = sqlstm.sqharm;
 sqlstm.sqparc = sqlstm.sqharc;
 sqlstm.sqpadto = sqlstm.sqadto;
 sqlstm.sqptdso = sqlstm.sqtdso;
 sqlcxt(&vCtx, &sqlctx, &sqlstm, &sqlfpn);
}


	/* EXEC SQL FOR : vInsertCount SET DESCRIPTOR 'inRun' VALUE 7 DATA = : vPredicted; */ 

{
 struct sqlexd sqlstm;
 sqlstm.sqlvsn = 13;
 sqlstm.arrsiz = 4;
 sqlstm.sqladtp = &sqladt;
 sqlstm.sqltdsp = &sqltds;
 sqlstm.stmt = "";
 sqlstm.iters = (unsigned int  )vInsertCount;
 sqlstm.offset = (unsigned int  )800;
 sqlstm.cud = sqlcud0;
 sqlstm.sqlest = (unsigned char  *)&sqlca;
 sqlstm.sqlety = (unsigned short)4352;
 sqlstm.occurs = (unsigned int  )7;
 sqlstm.sqhstv[0] = (         void  *)vPredicted;
 sqlstm.sqhstl[0] = (unsigned int  )sizeof(double);
 sqlstm.sqhsts[0] = (         int  )sizeof(double);
 sqlstm.sqindv[0] = (         void  *)0;
 sqlstm.sqinds[0] = (         int  )0;
 sqlstm.sqharm[0] = (unsigned int  )0;
 sqlstm.sqadto[0] = (unsigned short )0;
 sqlstm.sqtdso[0] = (unsigned short )0;
 sqlstm.sqphsv = sqlstm.sqhstv;
 sqlstm.sqphsl = sqlstm.sqhstl;
 sqlstm.sqphss = sqlstm.sqhsts;
 sqlstm.sqpind = sqlstm.sqindv;
 sqlstm.sqpins = sqlstm.sqinds;
 sqlstm.sqparm = sqlstm.sqharm;
 sqlstm.sqparc = sqlstm.sqharc;
 sqlstm.sqpadto = sqlstm.sqadto;
 sqlstm.sqptdso = sqlstm.sqtdso;
 sqlcxt(&vCtx, &sqlctx, &sqlstm, &sqlfpn);
}


	/* EXEC SQL FOR : vInsertCount SET DESCRIPTOR 'inRun' VALUE 8 DATA = : vError; */ 

{
 struct sqlexd sqlstm;
 sqlstm.sqlvsn = 13;
 sqlstm.arrsiz = 4;
 sqlstm.sqladtp = &sqladt;
 sqlstm.sqltdsp = &sqltds;
 sqlstm.stmt = "";
 sqlstm.iters = (unsigned int  )vInsertCount;
 sqlstm.offset = (unsigned int  )824;
 sqlstm.cud = sqlcud0;
 sqlstm.sqlest = (unsigned char  *)&sqlca;
 sqlstm.sqlety = (unsigned short)4352;
 sqlstm.occurs = (unsigned int  )8;
 sqlstm.sqhstv[0] = (         void  *)vError;
 sqlstm.sqhstl[0] = (unsigned int  )sizeof(double);
 sqlstm.sqhsts[0] = (         int  )sizeof(double);
 sqlstm.sqindv[0] = (         void  *)0;
 sqlstm.sqinds[0] = (         int  )0;
 sqlstm.sqharm[0] = (unsigned int  )0;
 sqlstm.sqadto[0] = (unsigned short )0;
 sqlstm.sqtdso[0] = (unsigned short )0;
 sqlstm.sqphsv = sqlstm.sqhstv;
 sqlstm.sqphsl = sqlstm.sqhstl;
 sqlstm.sqphss = sqlstm.sqhsts;
 sqlstm.sqpind = sqlstm.sqindv;
 sqlstm.sqpins = sqlstm.sqinds;
 sqlstm.sqparm = sqlstm.sqharm;
 sqlstm.sqparc = sqlstm.sqharc;
 sqlstm.sqpadto = sqlstm.sqadto;
 sqlstm.sqptdso = sqlstm.sqtdso;
 sqlcxt(&vCtx, &sqlctx, &sqlstm, &sqlfpn);
}


	/* EXEC SQL FOR : vInsertCount SET DESCRIPTOR 'inRun' VALUE 9 DATA = : vActual_TRS; */ 

{
 struct sqlexd sqlstm;
 sqlstm.sqlvsn = 13;
 sqlstm.arrsiz = 4;
 sqlstm.sqladtp = &sqladt;
 sqlstm.sqltdsp = &sqltds;
 sqlstm.stmt = "";
 sqlstm.iters = (unsigned int  )vInsertCount;
 sqlstm.offset = (unsigned int  )848;
 sqlstm.cud = sqlcud0;
 sqlstm.sqlest = (unsigned char  *)&sqlca;
 sqlstm.sqlety = (unsigned short)4352;
 sqlstm.occurs = (unsigned int  )9;
 sqlstm.sqhstv[0] = (         void  *)vActual_TRS;
 sqlstm.sqhstl[0] = (unsigned int  )sizeof(double);
 sqlstm.sqhsts[0] = (         int  )sizeof(double);
 sqlstm.sqindv[0] = (         void  *)0;
 sqlstm.sqinds[0] = (         int  )0;
 sqlstm.sqharm[0] = (unsigned int  )0;
 sqlstm.sqadto[0] = (unsigned short )0;
 sqlstm.sqtdso[0] = (unsigned short )0;
 sqlstm.sqphsv = sqlstm.sqhstv;
 sqlstm.sqphsl = sqlstm.sqhstl;
 sqlstm.sqphss = sqlstm.sqhsts;
 sqlstm.sqpind = sqlstm.sqindv;
 sqlstm.sqpins = sqlstm.sqinds;
 sqlstm.sqparm = sqlstm.sqharm;
 sqlstm.sqparc = sqlstm.sqharc;
 sqlstm.sqpadto = sqlstm.sqadto;
 sqlstm.sqptdso = sqlstm.sqtdso;
 sqlcxt(&vCtx, &sqlctx, &sqlstm, &sqlfpn);
}


	/* EXEC SQL FOR : vInsertCount SET DESCRIPTOR 'inRun' VALUE 10 DATA = : vPredicted_TRS; */ 

{
 struct sqlexd sqlstm;
 sqlstm.sqlvsn = 13;
 sqlstm.arrsiz = 4;
 sqlstm.sqladtp = &sqladt;
 sqlstm.sqltdsp = &sqltds;
 sqlstm.stmt = "";
 sqlstm.iters = (unsigned int  )vInsertCount;
 sqlstm.offset = (unsigned int  )872;
 sqlstm.cud = sqlcud0;
 sqlstm.sqlest = (unsigned char  *)&sqlca;
 sqlstm.sqlety = (unsigned short)4352;
 sqlstm.occurs = (unsigned int  )10;
 sqlstm.sqhstv[0] = (         void  *)vPredicted_TRS;
 sqlstm.sqhstl[0] = (unsigned int  )sizeof(double);
 sqlstm.sqhsts[0] = (         int  )sizeof(double);
 sqlstm.sqindv[0] = (         void  *)0;
 sqlstm.sqinds[0] = (         int  )0;
 sqlstm.sqharm[0] = (unsigned int  )0;
 sqlstm.sqadto[0] = (unsigned short )0;
 sqlstm.sqtdso[0] = (unsigned short )0;
 sqlstm.sqphsv = sqlstm.sqhstv;
 sqlstm.sqphsl = sqlstm.sqhstl;
 sqlstm.sqphss = sqlstm.sqhsts;
 sqlstm.sqpind = sqlstm.sqindv;
 sqlstm.sqpins = sqlstm.sqinds;
 sqlstm.sqparm = sqlstm.sqharm;
 sqlstm.sqparc = sqlstm.sqharc;
 sqlstm.sqpadto = sqlstm.sqadto;
 sqlstm.sqptdso = sqlstm.sqtdso;
 sqlcxt(&vCtx, &sqlctx, &sqlstm, &sqlfpn);
}


	/* EXEC SQL FOR : vInsertCount SET DESCRIPTOR 'inRun' VALUE 11 DATA = : vError_TRS; */ 

{
 struct sqlexd sqlstm;
 sqlstm.sqlvsn = 13;
 sqlstm.arrsiz = 4;
 sqlstm.sqladtp = &sqladt;
 sqlstm.sqltdsp = &sqltds;
 sqlstm.stmt = "";
 sqlstm.iters = (unsigned int  )vInsertCount;
 sqlstm.offset = (unsigned int  )896;
 sqlstm.cud = sqlcud0;
 sqlstm.sqlest = (unsigned char  *)&sqlca;
 sqlstm.sqlety = (unsigned short)4352;
 sqlstm.occurs = (unsigned int  )11;
 sqlstm.sqhstv[0] = (         void  *)vError_TRS;
 sqlstm.sqhstl[0] = (unsigned int  )sizeof(double);
 sqlstm.sqhsts[0] = (         int  )sizeof(double);
 sqlstm.sqindv[0] = (         void  *)0;
 sqlstm.sqinds[0] = (         int  )0;
 sqlstm.sqharm[0] = (unsigned int  )0;
 sqlstm.sqadto[0] = (unsigned short )0;
 sqlstm.sqtdso[0] = (unsigned short )0;
 sqlstm.sqphsv = sqlstm.sqhstv;
 sqlstm.sqphsl = sqlstm.sqhstl;
 sqlstm.sqphss = sqlstm.sqhsts;
 sqlstm.sqpind = sqlstm.sqindv;
 sqlstm.sqpins = sqlstm.sqinds;
 sqlstm.sqparm = sqlstm.sqharm;
 sqlstm.sqparc = sqlstm.sqharc;
 sqlstm.sqpadto = sqlstm.sqadto;
 sqlstm.sqptdso = sqlstm.sqtdso;
 sqlcxt(&vCtx, &sqlctx, &sqlstm, &sqlfpn);
}


	/* EXEC SQL FOR : vInsertCount SET DESCRIPTOR 'inRun' VALUE 12 DATA = : vBarWidth; */ 

{
 struct sqlexd sqlstm;
 sqlstm.sqlvsn = 13;
 sqlstm.arrsiz = 4;
 sqlstm.sqladtp = &sqladt;
 sqlstm.sqltdsp = &sqltds;
 sqlstm.stmt = "";
 sqlstm.iters = (unsigned int  )vInsertCount;
 sqlstm.offset = (unsigned int  )920;
 sqlstm.cud = sqlcud0;
 sqlstm.sqlest = (unsigned char  *)&sqlca;
 sqlstm.sqlety = (unsigned short)4352;
 sqlstm.occurs = (unsigned int  )12;
 sqlstm.sqhstv[0] = (         void  *)vBarWidth;
 sqlstm.sqhstl[0] = (unsigned int  )sizeof(double);
 sqlstm.sqhsts[0] = (         int  )sizeof(double);
 sqlstm.sqindv[0] = (         void  *)0;
 sqlstm.sqinds[0] = (         int  )0;
 sqlstm.sqharm[0] = (unsigned int  )0;
 sqlstm.sqadto[0] = (unsigned short )0;
 sqlstm.sqtdso[0] = (unsigned short )0;
 sqlstm.sqphsv = sqlstm.sqhstv;
 sqlstm.sqphsl = sqlstm.sqhstl;
 sqlstm.sqphss = sqlstm.sqhsts;
 sqlstm.sqpind = sqlstm.sqindv;
 sqlstm.sqpins = sqlstm.sqinds;
 sqlstm.sqparm = sqlstm.sqharm;
 sqlstm.sqparc = sqlstm.sqharc;
 sqlstm.sqpadto = sqlstm.sqadto;
 sqlstm.sqptdso = sqlstm.sqtdso;
 sqlcxt(&vCtx, &sqlctx, &sqlstm, &sqlfpn);
}


	/* EXEC SQL FOR : vInsertCount SET DESCRIPTOR 'inRun' VALUE 13 DATA = : vErrorP; */ 

{
 struct sqlexd sqlstm;
 sqlstm.sqlvsn = 13;
 sqlstm.arrsiz = 4;
 sqlstm.sqladtp = &sqladt;
 sqlstm.sqltdsp = &sqltds;
 sqlstm.stmt = "";
 sqlstm.iters = (unsigned int  )vInsertCount;
 sqlstm.offset = (unsigned int  )944;
 sqlstm.cud = sqlcud0;
 sqlstm.sqlest = (unsigned char  *)&sqlca;
 sqlstm.sqlety = (unsigned short)4352;
 sqlstm.occurs = (unsigned int  )13;
 sqlstm.sqhstv[0] = (         void  *)vErrorP;
 sqlstm.sqhstl[0] = (unsigned int  )sizeof(double);
 sqlstm.sqhsts[0] = (         int  )sizeof(double);
 sqlstm.sqindv[0] = (         void  *)0;
 sqlstm.sqinds[0] = (         int  )0;
 sqlstm.sqharm[0] = (unsigned int  )0;
 sqlstm.sqadto[0] = (unsigned short )0;
 sqlstm.sqtdso[0] = (unsigned short )0;
 sqlstm.sqphsv = sqlstm.sqhstv;
 sqlstm.sqphsl = sqlstm.sqhstl;
 sqlstm.sqphss = sqlstm.sqhsts;
 sqlstm.sqpind = sqlstm.sqindv;
 sqlstm.sqpins = sqlstm.sqinds;
 sqlstm.sqparm = sqlstm.sqharm;
 sqlstm.sqparc = sqlstm.sqharc;
 sqlstm.sqpadto = sqlstm.sqadto;
 sqlstm.sqptdso = sqlstm.sqtdso;
 sqlcxt(&vCtx, &sqlctx, &sqlstm, &sqlfpn);
}



	/* EXEC SQL PREPARE DynIns FROM : stmt; */ 

{
 struct sqlexd sqlstm;
 sqlstm.sqlvsn = 13;
 sqlstm.arrsiz = 4;
 sqlstm.sqladtp = &sqladt;
 sqlstm.sqltdsp = &sqltds;
 sqlstm.stmt = "";
 sqlstm.iters = (unsigned int  )1;
 sqlstm.offset = (unsigned int  )968;
 sqlstm.cud = sqlcud0;
 sqlstm.sqlest = (unsigned char  *)&sqlca;
 sqlstm.sqlety = (unsigned short)4352;
 sqlstm.occurs = (unsigned int  )0;
 sqlstm.sqhstv[0] = (         void  *)stmt;
 sqlstm.sqhstl[0] = (unsigned int  )1000;
 sqlstm.sqhsts[0] = (         int  )0;
 sqlstm.sqindv[0] = (         void  *)0;
 sqlstm.sqinds[0] = (         int  )0;
 sqlstm.sqharm[0] = (unsigned int  )0;
 sqlstm.sqadto[0] = (unsigned short )0;
 sqlstm.sqtdso[0] = (unsigned short )0;
 sqlstm.sqphsv = sqlstm.sqhstv;
 sqlstm.sqphsl = sqlstm.sqhstl;
 sqlstm.sqphss = sqlstm.sqhsts;
 sqlstm.sqpind = sqlstm.sqindv;
 sqlstm.sqpins = sqlstm.sqinds;
 sqlstm.sqparm = sqlstm.sqharm;
 sqlstm.sqparc = sqlstm.sqharc;
 sqlstm.sqpadto = sqlstm.sqadto;
 sqlstm.sqptdso = sqlstm.sqtdso;
 sqlcxt(&vCtx, &sqlctx, &sqlstm, &sqlfpn);
}


	/* EXEC SQL FOR : vInsertCount EXECUTE DynIns USING DESCRIPTOR 'inRun'; */ 

{
 struct sqlexd sqlstm;
 sqlstm.sqlvsn = 13;
 sqlstm.arrsiz = 4;
 sqlstm.sqladtp = &sqladt;
 sqlstm.sqltdsp = &sqltds;
 sqlstm.stmt = "";
 sqlstm.iters = (unsigned int  )vInsertCount;
 sqlstm.offset = (unsigned int  )987;
 sqlstm.cud = sqlcud0;
 sqlstm.sqlest = (unsigned char  *)&sqlca;
 sqlstm.sqlety = (unsigned short)4352;
 sqlstm.occurs = (unsigned int  )0;
 sqlcxt(&vCtx, &sqlctx, &sqlstm, &sqlfpn);
}


	//EXEC SQL ALTER SESSION SET SQL_TRACE = FALSE;

	(*pInsertCount) = sqlca.sqlerrd[2];
	LogWrite(DebugParms, LOG_INFO, "BulkRunInsert() CheckPoint 3 - InsertCount=%d\n", 1, (*pInsertCount));
	LogWrite(DebugParms, LOG_INFO, "BulkRunInsert() CheckPoint 4 - sqlca.sqlcode=%d\n", 1, sqlca.sqlcode);
	if (sqlca.sqlcode != 0) {
		if (sqlca.sqlcode != 1) {
			LogWrite(DebugParms, LOG_ERROR, "BulkRunInsert failed. SQL Error %d\n", 1, sqlca.sqlcode);
		}
		return sqlca.sqlcode;
	}

	//-- Need to insert the spacer that is no longer created in MyNN.cpp
	sprintf(&stmt[0], "insert into MyLog_Run (ProcessId, ThreadId, NetProcessId, NetThreadId, Pos, Actual, Predicted, Error, ActualC, PredictedC, ErrorC) \
						  						values(%d, %d, %d, %d, %f, NULL, NULL, NULL, NULL, NULL, NULL)", \
		vProcessId[0], vThreadId[0], vNetProcessId[0], vNetThreadId[0], (vPos[pHistoryLen - 1] + 0.5));
	/* EXEC SQL EXECUTE IMMEDIATE : stmt; */ 

{
 struct sqlexd sqlstm;
 sqlstm.sqlvsn = 13;
 sqlstm.arrsiz = 4;
 sqlstm.sqladtp = &sqladt;
 sqlstm.sqltdsp = &sqltds;
 sqlstm.stmt = "";
 sqlstm.iters = (unsigned int  )1;
 sqlstm.offset = (unsigned int  )1007;
 sqlstm.cud = sqlcud0;
 sqlstm.sqlest = (unsigned char  *)&sqlca;
 sqlstm.sqlety = (unsigned short)4352;
 sqlstm.occurs = (unsigned int  )0;
 sqlstm.sqhstv[0] = (         void  *)stmt;
 sqlstm.sqhstl[0] = (unsigned int  )1000;
 sqlstm.sqhsts[0] = (         int  )0;
 sqlstm.sqindv[0] = (         void  *)0;
 sqlstm.sqinds[0] = (         int  )0;
 sqlstm.sqharm[0] = (unsigned int  )0;
 sqlstm.sqadto[0] = (unsigned short )0;
 sqlstm.sqtdso[0] = (unsigned short )0;
 sqlstm.sqphsv = sqlstm.sqhstv;
 sqlstm.sqphsl = sqlstm.sqhstl;
 sqlstm.sqphss = sqlstm.sqhsts;
 sqlstm.sqpind = sqlstm.sqindv;
 sqlstm.sqpins = sqlstm.sqinds;
 sqlstm.sqparm = sqlstm.sqharm;
 sqlstm.sqparc = sqlstm.sqharc;
 sqlstm.sqpadto = sqlstm.sqadto;
 sqlstm.sqptdso = sqlstm.sqtdso;
 sqlcxt(&vCtx, &sqlctx, &sqlstm, &sqlfpn);
}


	if (sqlca.sqlcode != 0) {
		if (sqlca.sqlcode != 1403) {
			LogWrite(DebugParms, LOG_ERROR, "Inserting spacer in MyLog_Run failed. SQL Error %d\n", 1, sqlca.sqlcode);
			return sqlca.sqlcode;
		}
	}
	/* EXEC SQL DEALLOCATE DESCRIPTOR 'inRun'; */ 

{
 struct sqlexd sqlstm;
 sqlstm.sqlvsn = 13;
 sqlstm.arrsiz = 4;
 sqlstm.sqladtp = &sqladt;
 sqlstm.sqltdsp = &sqltds;
 sqlstm.stmt = "";
 sqlstm.iters = (unsigned int  )1;
 sqlstm.offset = (unsigned int  )1026;
 sqlstm.cud = sqlcud0;
 sqlstm.sqlest = (unsigned char  *)&sqlca;
 sqlstm.sqlety = (unsigned short)4352;
 sqlstm.occurs = (unsigned int  )0;
 sqlcxt(&vCtx, &sqlctx, &sqlstm, &sqlfpn);
}



	//-- Fixing the '0' values on actual that mess up excel charts
	strcpy(&stmt[0], "update MyLog_Run set Predicted=NULL, Error=NULL, PredictedC=NULL, ErrorC=NULL, BarWidth=NULL, ErrorP=NULL where Predicted=0");
	/* EXEC SQL EXECUTE IMMEDIATE : stmt; */ 

{
 struct sqlexd sqlstm;
 sqlstm.sqlvsn = 13;
 sqlstm.arrsiz = 4;
 sqlstm.sqladtp = &sqladt;
 sqlstm.sqltdsp = &sqltds;
 sqlstm.stmt = "";
 sqlstm.iters = (unsigned int  )1;
 sqlstm.offset = (unsigned int  )1046;
 sqlstm.cud = sqlcud0;
 sqlstm.sqlest = (unsigned char  *)&sqlca;
 sqlstm.sqlety = (unsigned short)4352;
 sqlstm.occurs = (unsigned int  )0;
 sqlstm.sqhstv[0] = (         void  *)stmt;
 sqlstm.sqhstl[0] = (unsigned int  )1000;
 sqlstm.sqhsts[0] = (         int  )0;
 sqlstm.sqindv[0] = (         void  *)0;
 sqlstm.sqinds[0] = (         int  )0;
 sqlstm.sqharm[0] = (unsigned int  )0;
 sqlstm.sqadto[0] = (unsigned short )0;
 sqlstm.sqtdso[0] = (unsigned short )0;
 sqlstm.sqphsv = sqlstm.sqhstv;
 sqlstm.sqphsl = sqlstm.sqhstl;
 sqlstm.sqphss = sqlstm.sqhsts;
 sqlstm.sqpind = sqlstm.sqindv;
 sqlstm.sqpins = sqlstm.sqinds;
 sqlstm.sqparm = sqlstm.sqharm;
 sqlstm.sqparc = sqlstm.sqharc;
 sqlstm.sqpadto = sqlstm.sqadto;
 sqlstm.sqptdso = sqlstm.sqtdso;
 sqlcxt(&vCtx, &sqlctx, &sqlstm, &sqlfpn);
}


	if (sqlca.sqlcode != 0) {
		if (sqlca.sqlcode != 1403) {
			LogWrite(DebugParms, LOG_ERROR, "Updating 0s in MyLog_Run failed. SQL Error %d\n", 1, sqlca.sqlcode);
			return sqlca.sqlcode;
		}
	}

	strcpy(&stmt[0], "update MyLog_Run set Actual=NULL, ActualC=NULL, Error=NULL, ErrorP=NULL where Actual=0");
	/* EXEC SQL EXECUTE IMMEDIATE : stmt; */ 

{
 struct sqlexd sqlstm;
 sqlstm.sqlvsn = 13;
 sqlstm.arrsiz = 4;
 sqlstm.sqladtp = &sqladt;
 sqlstm.sqltdsp = &sqltds;
 sqlstm.stmt = "";
 sqlstm.iters = (unsigned int  )1;
 sqlstm.offset = (unsigned int  )1065;
 sqlstm.cud = sqlcud0;
 sqlstm.sqlest = (unsigned char  *)&sqlca;
 sqlstm.sqlety = (unsigned short)4352;
 sqlstm.occurs = (unsigned int  )0;
 sqlstm.sqhstv[0] = (         void  *)stmt;
 sqlstm.sqhstl[0] = (unsigned int  )1000;
 sqlstm.sqhsts[0] = (         int  )0;
 sqlstm.sqindv[0] = (         void  *)0;
 sqlstm.sqinds[0] = (         int  )0;
 sqlstm.sqharm[0] = (unsigned int  )0;
 sqlstm.sqadto[0] = (unsigned short )0;
 sqlstm.sqtdso[0] = (unsigned short )0;
 sqlstm.sqphsv = sqlstm.sqhstv;
 sqlstm.sqphsl = sqlstm.sqhstl;
 sqlstm.sqphss = sqlstm.sqhsts;
 sqlstm.sqpind = sqlstm.sqindv;
 sqlstm.sqpins = sqlstm.sqinds;
 sqlstm.sqparm = sqlstm.sqharm;
 sqlstm.sqparc = sqlstm.sqharc;
 sqlstm.sqpadto = sqlstm.sqadto;
 sqlstm.sqptdso = sqlstm.sqtdso;
 sqlcxt(&vCtx, &sqlctx, &sqlstm, &sqlfpn);
}


	if (sqlca.sqlcode != 0) {
		if (sqlca.sqlcode != 1403) {
			LogWrite(DebugParms, LOG_ERROR, "Updating 0s in MyLog_Run failed. SQL Error %d\n", 1, sqlca.sqlcode);
			return sqlca.sqlcode;
		}
	}

	//-- free()s
	free(vProcessId);
	free(vThreadId);
	free(vNetProcessId);
	free(vNetThreadId);
	free(vPos);
	free(vActual);
	free(vPredicted);
	free(vError);
	free(vActual_TRS);
	free(vPredicted_TRS);
	free(vError_TRS);
	free(vBarWidth);
	free(vErrorP);

	return 0;
}


//-- Tester / client stuff
EXPORT int Ora_LoadData(tDebugInfo* DebugParms, tDBConnection* DBConnInfo, tFXData* DBParms, int pHistoryLen, int pFutureLen, char* pDate0, int pValidationShift, int pDatasetCount, double** oHistoryData, double** oHistoryBarW, double** oValidationData, double** oFutureData, double** oFutureBarW, double** oWholeData, double** oWholeBarW, double* oPrevValH, double* oPrevValV, double* oPrevBarW) {
	int i, d;
	tBar* PastBar = (tBar*)malloc((1 + pHistoryLen) * sizeof(tBar));
	tBar* FutureBar = (tBar*)malloc(pFutureLen * sizeof(tBar));

	char stmt[1000];

	if (DBConnInfo->DBCtx == NULL) {
		if (OraConnect(DebugParms, DBConnInfo) != 0) return -1;
	}

	//=== 1. Get History Data ===

	strcpy(stmt, "select to_char(NewDateTime, 'YYYYMMDDHH24MI'), Open, High, Low, Close, nvl(Volume,0) from History.");
	strcat(stmt, DBParms->Symbol);
	strcat(stmt, "_");
	strcat(stmt, DBParms->TimeFrame);
	strcat(stmt, (DBParms->IsFilled == 1) ? "_FILLED " : " ");
	strcat(stmt, "where NewDateTime <= to_date('");
	strcat(stmt, pDate0);
	strcat(stmt, "','YYYYMMDDHH24MI') order by 1 desc");

	if (GetBarsFromQuery(DebugParms, DBConnInfo->DBCtx, stmt, pHistoryLen + 1, 1, PastBar) != 0) return -1;	//-- HistoryData
																												//-- Repeat for each Dataset
	for (d = 0; d < pDatasetCount; d++) {

		//-- HistoryData
		for (i = 0; i<pHistoryLen; i++) {
			switch (DBParms->BarDataType[d]) {
			case OPEN:
				oHistoryData[d][i] = PastBar[pHistoryLen - 1 - i].Open;
				break;
			case HIGH:
				oHistoryData[d][i] = PastBar[pHistoryLen - 1 - i].High;
				break;
			case LOW:
				oHistoryData[d][i] = PastBar[pHistoryLen - 1 - i].Low;
				break;
			case CLOSE:
				oHistoryData[d][i] = PastBar[pHistoryLen - 1 - i].Close;
				break;
			case VOLUME:
				oHistoryData[d][i] = PastBar[pHistoryLen - 1 - i].Volume;
				break;
			}
			oHistoryBarW[d][i] = PastBar[pHistoryLen - 1 - i].High - PastBar[pHistoryLen - 1 - i].Low;
			oWholeData[d][i] = oHistoryData[d][i];
			oWholeBarW[d][i] = oHistoryBarW[d][i];
		}
		switch (DBParms->BarDataType[d]) {
		case OPEN:
			oPrevValH[d] = PastBar[pHistoryLen].Open;
			break;
		case HIGH:
			oPrevValH[d] = PastBar[pHistoryLen].High;
			break;
		case LOW:
			oPrevValH[d] = PastBar[pHistoryLen].Low;
			break;
		case CLOSE:
			oPrevValH[d] = PastBar[pHistoryLen].Close;
			break;
		case VOLUME:
			oPrevValH[d] = PastBar[pHistoryLen].Volume;
			break;
		}
	}

	//=== 2. Get Future Data ===
	strcpy(stmt, "select to_char(NewDateTime, 'YYYYMMDDHH24MI'), Open, High, Low, Close, nvl(Volume,0), Open-nvl(lag(Open) over(order by NewDateTime), 0), High-nvl(lag(High) over(order by NewDateTime), 0), Low-nvl(lag(Low) over(order by NewDateTime), 0), Close-nvl(lag(Close) over(order by NewDateTime), 0), nvl(Volume,0)-nvl(lag(Volume) over(order by NewDateTime), 0) from History.");
	strcat(stmt, DBParms->Symbol);
	strcat(stmt, "_");
	strcat(stmt, DBParms->TimeFrame);
	strcat(stmt, (DBParms->IsFilled == 1) ? "_FILLED " : " ");
	strcat(stmt, "where NewDateTime >= to_date('");
	strcat(stmt, pDate0);
	strcat(stmt, "','YYYYMMDDHH24MI') order by 1");

	if (GetBarsFromQuery(DebugParms, DBConnInfo->DBCtx, stmt, pFutureLen, 0, FutureBar) != 0) return -1;

	//-- Repeat for each Dataset
	for (d = 0; d < pDatasetCount; d++) {
		for (i = 0; i<pFutureLen; i++) {
			switch (DBParms->BarDataType[d]) {
			case OPEN:
				oFutureData[d][i] = FutureBar[i].Open;
				break;
			case HIGH:
				oFutureData[d][i] = FutureBar[i].High;
				break;
			case LOW:
				oFutureData[d][i] = FutureBar[i].Low;
				break;
			case CLOSE:
				oFutureData[d][i] = FutureBar[i].Close;
				break;
			case VOLUME:
				oFutureData[d][i] = FutureBar[i].Volume;
				break;
			}
			oFutureBarW[d][i] = FutureBar[i].High - FutureBar[i].Low;
			oWholeData[d][pHistoryLen + i] = oFutureData[d][i];
			oWholeBarW[d][pHistoryLen + i] = oFutureBarW[d][i];
		}
	}

	//=== 3. Get Validation Data ===
	if (pValidationShift != 0) {
		//-- first, find the new Date0
		char newDate0[12 + 1];
		sprintf(&stmt[0], "select to_char(min(newdatetime),'YYYYMMDDHH24MI') from( select * from (	select newdatetime from History.%s_%s%s where newdatetime %s to_date(%s,'YYYYMMDDHH24MI') order by 1 desc ) where rownum<%d)", \
			DBParms->Symbol, DBParms->TimeFrame, ((DBParms->IsFilled > 0) ? "FILLED" : ""), ((pValidationShift > 0) ? ">" : "<"), pDate0, abs(pValidationShift));
		if (GetCharPFromQuery(DebugParms, DBConnInfo, DBConnInfo->DBCtx, stmt, &newDate0[0])) return -1;

		//-- then, same as for HistoryData
		sprintf(&stmt[0], "select to_char(NewDateTime, 'YYYYMMDDHH24MI'), Open, High, Low, Close, nvl(Volume,0) from History.%s_%s%s where newdatetime <= to_date(%s,'YYYYMMDDHH24MI') order by 1", DBParms->Symbol, DBParms->TimeFrame, ((DBParms->IsFilled > 0) ? "FILLED" : ""), newDate0);


		if (GetBarsFromQuery(DebugParms, DBConnInfo->DBCtx, stmt, pHistoryLen + 1, 1, PastBar) != 0) return -1;	//-- ValidationData
																													//-- Repeat for each Dataset
		for (d = 0; d < pDatasetCount; d++) {

			//-- HistoryData
			for (i = 0; i < pHistoryLen; i++) {
				switch (DBParms->BarDataType[d]) {
				case OPEN:
					oValidationData[d][i] = PastBar[pHistoryLen - 1 - i].Open;
					break;
				case HIGH:
					oValidationData[d][i] = PastBar[pHistoryLen - 1 - i].High;
					break;
				case LOW:
					oValidationData[d][i] = PastBar[pHistoryLen - 1 - i].Low;
					break;
				case CLOSE:
					oValidationData[d][i] = PastBar[pHistoryLen - 1 - i].Close;
					break;
				case VOLUME:
					oValidationData[d][i] = PastBar[pHistoryLen - 1 - i].Volume;
					break;
				}
			}
			switch (DBParms->BarDataType[d]) {
			case OPEN:
				oPrevValV[d] = PastBar[pHistoryLen].Open;
				break;
			case HIGH:
				oPrevValV[d] = PastBar[pHistoryLen].High;
				break;
			case LOW:
				oPrevValV[d] = PastBar[pHistoryLen].Low;
				break;
			case CLOSE:
				oPrevValV[d] = PastBar[pHistoryLen].Close;
				break;
			case VOLUME:
				oPrevValV[d] = PastBar[pHistoryLen].Volume;
				break;
			}
		}
	}
	free(PastBar); free(FutureBar);
	return 0;

}
EXPORT int Ora_GetDates(tDebugInfo* DebugParms, tDBConnection* DBConnInfo, tFXData* SourceParms, char* StartDate, int DatesCount, char** oDate) {
	// Retrieves plain ordered list of NewDateTime starting from StartDate onwards for <DatesCount> records
	char stmt[1000];

	if (DBConnInfo->DBCtx == NULL) {
		if (OraConnect(DebugParms, DBConnInfo) != 0) return -1;
	}

	strcpy(stmt, "select to_char(NewDateTime, 'YYYYMMDDHH24MI') from History.");
	strcat(stmt, SourceParms->Symbol);
	strcat(stmt, "_");
	strcat(stmt, SourceParms->TimeFrame);
	strcat(stmt, (SourceParms->IsFilled == 1) ? "_FILLED " : " ");
	strcat(stmt, "where NewDateTime>=to_date('");
	strcat(stmt, StartDate);
	strcat(stmt, "','YYYYMMDDHH24MI') order by 1");

	if (GetStringArrayFromQuery(DebugParms, DBConnInfo, DBConnInfo->DBCtx, stmt, DatesCount, oDate) != 0) return -1;

	return 0;
}
EXPORT int Ora_InsertTesterParms(tDebugInfo* DebugParms, tDBConnection* DBConnInfo, int pid, int pSimulationLen, char* pSimulationStart, double pElapsedSecs, int pDoTraining, int pDoRun) {
	/* EXEC SQL BEGIN DECLARE SECTION; */ 

	sql_context vCtx = DBConnInfo->DBCtx;
	char stmt[1000];
	/* EXEC SQL END DECLARE SECTION; */ 


	//-- Connects to DB only once
	if (vCtx == NULL) {
		if (OraConnect(DebugParms, DBConnInfo) != 0) {
			printf("%s() could not connect to Log Database...\n", __func__);
			return -1;
		}
		vCtx = DBConnInfo->DBCtx;
	}
	//-- Builds Insert statement
	sprintf(&stmt[0], "insert into TesterParms(ProcessId, TesterStart,	SimulationLen,	Duration, 	  SimulationStart,					DoTraining, DoRun) \
						values(					%d,			sysdate,	%d,				%f,			  to_date('%s','YYYYMMDDHH24MI'),	%d,			%d)",
		pid, pSimulationLen, pElapsedSecs, pSimulationStart, pDoTraining, pDoRun);
	//-- Executes Insert statement
	/* EXEC SQL CONTEXT USE : vCtx; */ 

	/* EXEC SQL EXECUTE IMMEDIATE : stmt; */ 

{
 struct sqlexd sqlstm;
 sqlstm.sqlvsn = 13;
 sqlstm.arrsiz = 4;
 sqlstm.sqladtp = &sqladt;
 sqlstm.sqltdsp = &sqltds;
 sqlstm.stmt = "";
 sqlstm.iters = (unsigned int  )1;
 sqlstm.offset = (unsigned int  )1084;
 sqlstm.cud = sqlcud0;
 sqlstm.sqlest = (unsigned char  *)&sqlca;
 sqlstm.sqlety = (unsigned short)4352;
 sqlstm.occurs = (unsigned int  )0;
 sqlstm.sqhstv[0] = (         void  *)stmt;
 sqlstm.sqhstl[0] = (unsigned int  )1000;
 sqlstm.sqhsts[0] = (         int  )0;
 sqlstm.sqindv[0] = (         void  *)0;
 sqlstm.sqinds[0] = (         int  )0;
 sqlstm.sqharm[0] = (unsigned int  )0;
 sqlstm.sqadto[0] = (unsigned short )0;
 sqlstm.sqtdso[0] = (unsigned short )0;
 sqlstm.sqphsv = sqlstm.sqhstv;
 sqlstm.sqphsl = sqlstm.sqhstl;
 sqlstm.sqphss = sqlstm.sqhsts;
 sqlstm.sqpind = sqlstm.sqindv;
 sqlstm.sqpins = sqlstm.sqinds;
 sqlstm.sqparm = sqlstm.sqharm;
 sqlstm.sqparc = sqlstm.sqharc;
 sqlstm.sqpadto = sqlstm.sqadto;
 sqlstm.sqptdso = sqlstm.sqtdso;
 sqlcxt(&vCtx, &sqlctx, &sqlstm, &sqlfpn);
}


	if (sqlca.sqlcode != 0) {
		if (sqlca.sqlcode != 1) LogWrite(DebugParms, LOG_ERROR, "%s failed. SQL Error %d\n", 2, __func__, sqlca.sqlcode);
		return sqlca.sqlcode;
	}
	return 0;
}
EXPORT int Ora_UpdateTesterDuration(tDebugInfo* DebugParms, tDBConnection* DBConnInfo, int pid, double pElapsedSecs) {
	/* EXEC SQL BEGIN DECLARE SECTION; */ 

	sql_context vCtx = DBConnInfo->DBCtx;
	char stmt[1000];
	/* EXEC SQL END DECLARE SECTION; */ 


	//-- Connects to DB only once
	if (vCtx == NULL) {
		if (OraConnect(DebugParms,DBConnInfo) != 0) {
			printf("%s() could not connect to Log Database...\n", __func__);
			return -1;
		}
		vCtx =DBConnInfo->DBCtx;
	}
	//-- Builds Update statement
	sprintf(&stmt[0], "update TesterParms set Duration=%f where processid=%d", pElapsedSecs, pid);
	//-- Executes Update statement
	/* EXEC SQL CONTEXT USE : vCtx; */ 

	/* EXEC SQL EXECUTE IMMEDIATE : stmt; */ 

{
 struct sqlexd sqlstm;
 sqlstm.sqlvsn = 13;
 sqlstm.arrsiz = 4;
 sqlstm.sqladtp = &sqladt;
 sqlstm.sqltdsp = &sqltds;
 sqlstm.stmt = "";
 sqlstm.iters = (unsigned int  )1;
 sqlstm.offset = (unsigned int  )1103;
 sqlstm.cud = sqlcud0;
 sqlstm.sqlest = (unsigned char  *)&sqlca;
 sqlstm.sqlety = (unsigned short)4352;
 sqlstm.occurs = (unsigned int  )0;
 sqlstm.sqhstv[0] = (         void  *)stmt;
 sqlstm.sqhstl[0] = (unsigned int  )1000;
 sqlstm.sqhsts[0] = (         int  )0;
 sqlstm.sqindv[0] = (         void  *)0;
 sqlstm.sqinds[0] = (         int  )0;
 sqlstm.sqharm[0] = (unsigned int  )0;
 sqlstm.sqadto[0] = (unsigned short )0;
 sqlstm.sqtdso[0] = (unsigned short )0;
 sqlstm.sqphsv = sqlstm.sqhstv;
 sqlstm.sqphsl = sqlstm.sqhstl;
 sqlstm.sqphss = sqlstm.sqhsts;
 sqlstm.sqpind = sqlstm.sqindv;
 sqlstm.sqpins = sqlstm.sqinds;
 sqlstm.sqparm = sqlstm.sqharm;
 sqlstm.sqparc = sqlstm.sqharc;
 sqlstm.sqpadto = sqlstm.sqadto;
 sqlstm.sqptdso = sqlstm.sqtdso;
 sqlcxt(&vCtx, &sqlctx, &sqlstm, &sqlfpn);
}


	if (sqlca.sqlcode != 0) {
		LogWrite(DebugParms, LOG_ERROR, "%s failed. SQL Error %d\n", 2, __func__, sqlca.sqlcode);
		return sqlca.sqlcode;
	}
	return 0;
}



//-- Load DataParms, EngineParms
EXPORT int Ora_LoadDataParms(tDebugInfo* DebugParms, tDBConnection* DBConnInfo, int pid, int* oHistoryLen, int* oSampleLen, int* oSampleCount, int* oPredictionLen, int* oDataTransformation, double* oWiggleRoom) {
	/* EXEC SQL BEGIN DECLARE SECTION; */ 

	int ret;
	sql_context vCtx =DBConnInfo->DBCtx;
	char stmt[1000];
	int vHistoryLen, vSampleLen, vPredictionLen, vDataTransformation;
	double vWiggleRoom;
	/* EXEC SQL END   DECLARE SECTION; */ 


	//-- Connects to DB only once
	if (vCtx == NULL) {
		if (OraConnect(DebugParms,DBConnInfo) != 0) printf("%s() could not connect to Log Database...\n", __func__);
		vCtx =DBConnInfo->DBCtx;
	}

	sprintf(&stmt[0], "select HistoryLen, SampleLen, PredictionLen, DataTransformation, WiggleRoom from DataParms where ProcessId=%d", pid);
	LogWrite(DebugParms, LOG_INFO, "%s() CheckPoint 3 - stmt = %s\n", 2, __func__, stmt);

	//-- Executes SQL 
	vCtx =DBConnInfo->DBCtx;
	/* EXEC SQL CONTEXT USE : vCtx; */ 

	/* EXEC SQL PREPARE s15 FROM : stmt; */ 

{
 struct sqlexd sqlstm;
 sqlstm.sqlvsn = 13;
 sqlstm.arrsiz = 4;
 sqlstm.sqladtp = &sqladt;
 sqlstm.sqltdsp = &sqltds;
 sqlstm.stmt = "";
 sqlstm.iters = (unsigned int  )1;
 sqlstm.offset = (unsigned int  )1122;
 sqlstm.cud = sqlcud0;
 sqlstm.sqlest = (unsigned char  *)&sqlca;
 sqlstm.sqlety = (unsigned short)4352;
 sqlstm.occurs = (unsigned int  )0;
 sqlstm.sqhstv[0] = (         void  *)stmt;
 sqlstm.sqhstl[0] = (unsigned int  )1000;
 sqlstm.sqhsts[0] = (         int  )0;
 sqlstm.sqindv[0] = (         void  *)0;
 sqlstm.sqinds[0] = (         int  )0;
 sqlstm.sqharm[0] = (unsigned int  )0;
 sqlstm.sqadto[0] = (unsigned short )0;
 sqlstm.sqtdso[0] = (unsigned short )0;
 sqlstm.sqphsv = sqlstm.sqhstv;
 sqlstm.sqphsl = sqlstm.sqhstl;
 sqlstm.sqphss = sqlstm.sqhsts;
 sqlstm.sqpind = sqlstm.sqindv;
 sqlstm.sqpins = sqlstm.sqinds;
 sqlstm.sqparm = sqlstm.sqharm;
 sqlstm.sqparc = sqlstm.sqharc;
 sqlstm.sqpadto = sqlstm.sqadto;
 sqlstm.sqptdso = sqlstm.sqtdso;
 sqlcxt(&vCtx, &sqlctx, &sqlstm, &sqlfpn);
}


	/* EXEC SQL DECLARE c15 CURSOR FOR s15; */ 

	/* EXEC SQL OPEN c15; */ 

{
 struct sqlexd sqlstm;
 sqlstm.sqlvsn = 13;
 sqlstm.arrsiz = 4;
 sqlstm.sqladtp = &sqladt;
 sqlstm.sqltdsp = &sqltds;
 sqlstm.stmt = "";
 sqlstm.iters = (unsigned int  )1;
 sqlstm.offset = (unsigned int  )1141;
 sqlstm.selerr = (unsigned short)1;
 sqlstm.sqlpfmem = (unsigned int  )0;
 sqlstm.cud = sqlcud0;
 sqlstm.sqlest = (unsigned char  *)&sqlca;
 sqlstm.sqlety = (unsigned short)4352;
 sqlstm.occurs = (unsigned int  )0;
 sqlstm.sqcmod = (unsigned int )0;
 sqlcxt(&vCtx, &sqlctx, &sqlstm, &sqlfpn);
}


	/* EXEC SQL FETCH c15 INTO :vHistoryLen, :vSampleLen, :vPredictionLen, :vDataTransformation, :vWiggleRoom; */ 

{
 struct sqlexd sqlstm;
 sqlstm.sqlvsn = 13;
 sqlstm.arrsiz = 5;
 sqlstm.sqladtp = &sqladt;
 sqlstm.sqltdsp = &sqltds;
 sqlstm.iters = (unsigned int  )1;
 sqlstm.offset = (unsigned int  )1156;
 sqlstm.selerr = (unsigned short)1;
 sqlstm.sqlpfmem = (unsigned int  )0;
 sqlstm.cud = sqlcud0;
 sqlstm.sqlest = (unsigned char  *)&sqlca;
 sqlstm.sqlety = (unsigned short)4352;
 sqlstm.occurs = (unsigned int  )0;
 sqlstm.sqfoff = (           int )0;
 sqlstm.sqfmod = (unsigned int )2;
 sqlstm.sqhstv[0] = (         void  *)&vHistoryLen;
 sqlstm.sqhstl[0] = (unsigned int  )sizeof(int);
 sqlstm.sqhsts[0] = (         int  )0;
 sqlstm.sqindv[0] = (         void  *)0;
 sqlstm.sqinds[0] = (         int  )0;
 sqlstm.sqharm[0] = (unsigned int  )0;
 sqlstm.sqadto[0] = (unsigned short )0;
 sqlstm.sqtdso[0] = (unsigned short )0;
 sqlstm.sqhstv[1] = (         void  *)&vSampleLen;
 sqlstm.sqhstl[1] = (unsigned int  )sizeof(int);
 sqlstm.sqhsts[1] = (         int  )0;
 sqlstm.sqindv[1] = (         void  *)0;
 sqlstm.sqinds[1] = (         int  )0;
 sqlstm.sqharm[1] = (unsigned int  )0;
 sqlstm.sqadto[1] = (unsigned short )0;
 sqlstm.sqtdso[1] = (unsigned short )0;
 sqlstm.sqhstv[2] = (         void  *)&vPredictionLen;
 sqlstm.sqhstl[2] = (unsigned int  )sizeof(int);
 sqlstm.sqhsts[2] = (         int  )0;
 sqlstm.sqindv[2] = (         void  *)0;
 sqlstm.sqinds[2] = (         int  )0;
 sqlstm.sqharm[2] = (unsigned int  )0;
 sqlstm.sqadto[2] = (unsigned short )0;
 sqlstm.sqtdso[2] = (unsigned short )0;
 sqlstm.sqhstv[3] = (         void  *)&vDataTransformation;
 sqlstm.sqhstl[3] = (unsigned int  )sizeof(int);
 sqlstm.sqhsts[3] = (         int  )0;
 sqlstm.sqindv[3] = (         void  *)0;
 sqlstm.sqinds[3] = (         int  )0;
 sqlstm.sqharm[3] = (unsigned int  )0;
 sqlstm.sqadto[3] = (unsigned short )0;
 sqlstm.sqtdso[3] = (unsigned short )0;
 sqlstm.sqhstv[4] = (         void  *)&vWiggleRoom;
 sqlstm.sqhstl[4] = (unsigned int  )sizeof(double);
 sqlstm.sqhsts[4] = (         int  )0;
 sqlstm.sqindv[4] = (         void  *)0;
 sqlstm.sqinds[4] = (         int  )0;
 sqlstm.sqharm[4] = (unsigned int  )0;
 sqlstm.sqadto[4] = (unsigned short )0;
 sqlstm.sqtdso[4] = (unsigned short )0;
 sqlstm.sqphsv = sqlstm.sqhstv;
 sqlstm.sqphsl = sqlstm.sqhstl;
 sqlstm.sqphss = sqlstm.sqhsts;
 sqlstm.sqpind = sqlstm.sqindv;
 sqlstm.sqpins = sqlstm.sqinds;
 sqlstm.sqparm = sqlstm.sqharm;
 sqlstm.sqparc = sqlstm.sqharc;
 sqlstm.sqpadto = sqlstm.sqadto;
 sqlstm.sqptdso = sqlstm.sqtdso;
 sqlcxt(&vCtx, &sqlctx, &sqlstm, &sqlfpn);
}


	ret = sqlca.sqlcode;
	if (sqlca.sqlcode != 0) {
		LogWrite(DebugParms, LOG_ERROR, "%s(): SQL Error %d\n", 2, __func__, sqlca.sqlcode);
		return sqlca.sqlcode;
	}
	/* EXEC SQL CLOSE c15; */ 

{
 struct sqlexd sqlstm;
 sqlstm.sqlvsn = 13;
 sqlstm.arrsiz = 5;
 sqlstm.sqladtp = &sqladt;
 sqlstm.sqltdsp = &sqltds;
 sqlstm.iters = (unsigned int  )1;
 sqlstm.offset = (unsigned int  )1191;
 sqlstm.cud = sqlcud0;
 sqlstm.sqlest = (unsigned char  *)&sqlca;
 sqlstm.sqlety = (unsigned short)4352;
 sqlstm.occurs = (unsigned int  )0;
 sqlcxt(&vCtx, &sqlctx, &sqlstm, &sqlfpn);
}


	ret = sqlca.sqlcode;

	//-- Fill oDataParms, and returns
	(*oHistoryLen) = vHistoryLen;
	(*oSampleLen) = vSampleLen;
	(*oSampleCount) = vHistoryLen-vSampleLen;
	(*oPredictionLen) = vPredictionLen;
	(*oDataTransformation) = vDataTransformation;
	(*oWiggleRoom) = vWiggleRoom;
	LogWrite(DebugParms, LOG_INFO, "%s(): HistoryLen=%d ; SampleLen=%d ; PredictionLen=%d \n", 4, __func__, (*oHistoryLen), (*oSampleLen), (*oPredictionLen));
	return ret;
}
EXPORT int Ora_LoadEngineParms(tDebugInfo* DebugParms, tDBConnection* DBConnInfo, int pid, int* oEngineType, int* oLayersCount, int* oDecompLevel, char** oWaveletType) {
	/* EXEC SQL BEGIN DECLARE SECTION; */ 

	int ret;
	sql_context vCtx =DBConnInfo->DBCtx;
	char stmt[1000];
	int vEngineType, vLayersCount, vDecompLevel;
	char vWType[30];
	/* EXEC SQL END   DECLARE SECTION; */ 


	//-- Connects to DB only once
	if (vCtx == NULL) {
		if (OraConnect(DebugParms,DBConnInfo) != 0) printf("%s() could not connect to Log Database...\n", __func__);
		vCtx =DBConnInfo->DBCtx;
	}

	sprintf(&stmt[0], "select EngineType, LayersCount, WNN_DecompLevel, decode(WNN_WaveletType,NULL,'UNUSED',WNN_WaveletType) from EngineParms where ProcessId=%d", pid);
	LogWrite(DebugParms, LOG_INFO, "%s() CheckPoint 3 - stmt = %s\n", 2, __func__, stmt);

	//-- Executes SQL 
	vCtx =DBConnInfo->DBCtx;
	/* EXEC SQL CONTEXT USE : vCtx; */ 

	/* EXEC SQL PREPARE s16 FROM : stmt; */ 

{
 struct sqlexd sqlstm;
 sqlstm.sqlvsn = 13;
 sqlstm.arrsiz = 5;
 sqlstm.sqladtp = &sqladt;
 sqlstm.sqltdsp = &sqltds;
 sqlstm.stmt = "";
 sqlstm.iters = (unsigned int  )1;
 sqlstm.offset = (unsigned int  )1206;
 sqlstm.cud = sqlcud0;
 sqlstm.sqlest = (unsigned char  *)&sqlca;
 sqlstm.sqlety = (unsigned short)4352;
 sqlstm.occurs = (unsigned int  )0;
 sqlstm.sqhstv[0] = (         void  *)stmt;
 sqlstm.sqhstl[0] = (unsigned int  )1000;
 sqlstm.sqhsts[0] = (         int  )0;
 sqlstm.sqindv[0] = (         void  *)0;
 sqlstm.sqinds[0] = (         int  )0;
 sqlstm.sqharm[0] = (unsigned int  )0;
 sqlstm.sqadto[0] = (unsigned short )0;
 sqlstm.sqtdso[0] = (unsigned short )0;
 sqlstm.sqphsv = sqlstm.sqhstv;
 sqlstm.sqphsl = sqlstm.sqhstl;
 sqlstm.sqphss = sqlstm.sqhsts;
 sqlstm.sqpind = sqlstm.sqindv;
 sqlstm.sqpins = sqlstm.sqinds;
 sqlstm.sqparm = sqlstm.sqharm;
 sqlstm.sqparc = sqlstm.sqharc;
 sqlstm.sqpadto = sqlstm.sqadto;
 sqlstm.sqptdso = sqlstm.sqtdso;
 sqlcxt(&vCtx, &sqlctx, &sqlstm, &sqlfpn);
}


	/* EXEC SQL DECLARE c16 CURSOR FOR s16; */ 

	/* EXEC SQL OPEN c16; */ 

{
 struct sqlexd sqlstm;
 sqlstm.sqlvsn = 13;
 sqlstm.arrsiz = 5;
 sqlstm.sqladtp = &sqladt;
 sqlstm.sqltdsp = &sqltds;
 sqlstm.stmt = "";
 sqlstm.iters = (unsigned int  )1;
 sqlstm.offset = (unsigned int  )1225;
 sqlstm.selerr = (unsigned short)1;
 sqlstm.sqlpfmem = (unsigned int  )0;
 sqlstm.cud = sqlcud0;
 sqlstm.sqlest = (unsigned char  *)&sqlca;
 sqlstm.sqlety = (unsigned short)4352;
 sqlstm.occurs = (unsigned int  )0;
 sqlstm.sqcmod = (unsigned int )0;
 sqlcxt(&vCtx, &sqlctx, &sqlstm, &sqlfpn);
}


	/* EXEC SQL FETCH c16 INTO : vEngineType, : vLayersCount, : vDecompLevel, : vWType; */ 

{
 struct sqlexd sqlstm;
 sqlstm.sqlvsn = 13;
 sqlstm.arrsiz = 5;
 sqlstm.sqladtp = &sqladt;
 sqlstm.sqltdsp = &sqltds;
 sqlstm.iters = (unsigned int  )1;
 sqlstm.offset = (unsigned int  )1240;
 sqlstm.selerr = (unsigned short)1;
 sqlstm.sqlpfmem = (unsigned int  )0;
 sqlstm.cud = sqlcud0;
 sqlstm.sqlest = (unsigned char  *)&sqlca;
 sqlstm.sqlety = (unsigned short)4352;
 sqlstm.occurs = (unsigned int  )0;
 sqlstm.sqfoff = (           int )0;
 sqlstm.sqfmod = (unsigned int )2;
 sqlstm.sqhstv[0] = (         void  *)&vEngineType;
 sqlstm.sqhstl[0] = (unsigned int  )sizeof(int);
 sqlstm.sqhsts[0] = (         int  )0;
 sqlstm.sqindv[0] = (         void  *)0;
 sqlstm.sqinds[0] = (         int  )0;
 sqlstm.sqharm[0] = (unsigned int  )0;
 sqlstm.sqadto[0] = (unsigned short )0;
 sqlstm.sqtdso[0] = (unsigned short )0;
 sqlstm.sqhstv[1] = (         void  *)&vLayersCount;
 sqlstm.sqhstl[1] = (unsigned int  )sizeof(int);
 sqlstm.sqhsts[1] = (         int  )0;
 sqlstm.sqindv[1] = (         void  *)0;
 sqlstm.sqinds[1] = (         int  )0;
 sqlstm.sqharm[1] = (unsigned int  )0;
 sqlstm.sqadto[1] = (unsigned short )0;
 sqlstm.sqtdso[1] = (unsigned short )0;
 sqlstm.sqhstv[2] = (         void  *)&vDecompLevel;
 sqlstm.sqhstl[2] = (unsigned int  )sizeof(int);
 sqlstm.sqhsts[2] = (         int  )0;
 sqlstm.sqindv[2] = (         void  *)0;
 sqlstm.sqinds[2] = (         int  )0;
 sqlstm.sqharm[2] = (unsigned int  )0;
 sqlstm.sqadto[2] = (unsigned short )0;
 sqlstm.sqtdso[2] = (unsigned short )0;
 sqlstm.sqhstv[3] = (         void  *)vWType;
 sqlstm.sqhstl[3] = (unsigned int  )30;
 sqlstm.sqhsts[3] = (         int  )0;
 sqlstm.sqindv[3] = (         void  *)0;
 sqlstm.sqinds[3] = (         int  )0;
 sqlstm.sqharm[3] = (unsigned int  )0;
 sqlstm.sqadto[3] = (unsigned short )0;
 sqlstm.sqtdso[3] = (unsigned short )0;
 sqlstm.sqphsv = sqlstm.sqhstv;
 sqlstm.sqphsl = sqlstm.sqhstl;
 sqlstm.sqphss = sqlstm.sqhsts;
 sqlstm.sqpind = sqlstm.sqindv;
 sqlstm.sqpins = sqlstm.sqinds;
 sqlstm.sqparm = sqlstm.sqharm;
 sqlstm.sqparc = sqlstm.sqharc;
 sqlstm.sqpadto = sqlstm.sqadto;
 sqlstm.sqptdso = sqlstm.sqtdso;
 sqlcxt(&vCtx, &sqlctx, &sqlstm, &sqlfpn);
}


	ret = sqlca.sqlcode;
	if (sqlca.sqlcode != 0) {
		LogWrite(DebugParms, LOG_ERROR, "%s(): SQL Error %d\n", 2, __func__, sqlca.sqlcode);
		return sqlca.sqlcode;
	}
	/* EXEC SQL CLOSE c16; */ 

{
 struct sqlexd sqlstm;
 sqlstm.sqlvsn = 13;
 sqlstm.arrsiz = 5;
 sqlstm.sqladtp = &sqladt;
 sqlstm.sqltdsp = &sqltds;
 sqlstm.iters = (unsigned int  )1;
 sqlstm.offset = (unsigned int  )1271;
 sqlstm.cud = sqlcud0;
 sqlstm.sqlest = (unsigned char  *)&sqlca;
 sqlstm.sqlety = (unsigned short)4352;
 sqlstm.occurs = (unsigned int  )0;
 sqlcxt(&vCtx, &sqlctx, &sqlstm, &sqlfpn);
}


	ret = sqlca.sqlcode;

	//-- Fill oEngineParms, and returns
	(*oEngineType) = vEngineType;
	(*oLayersCount) = vLayersCount;
//	if (vEngineType == ENGINE_WNN) {
		(*oDecompLevel) = vDecompLevel;
		strcpy((*oWaveletType), vWType);
//	}
	LogWrite(DebugParms, LOG_INFO, "%s(): EngineType=%d ; LayersCount=%d\n", 3, __func__, (*oEngineType), (*oLayersCount));
	return ret;
}
//-- Save DataParms, EngineParms
EXPORT int Ora_InsertDataParms(tDebugInfo* pDebugParms, tDBConnection* DBConnInfo, int pid, int pDatasetId, int pDSType, char* pDSFileName, char* pSymbol, char* pTimeFrame, int pIsFilled, int pBarData, int pDataTransformation, double pwiggleRoom, int pHistoryLen, int pSampleLen, int pPredictionLen) {
	/* EXEC SQL BEGIN DECLARE SECTION; */ 

	sql_context vCtx = DBConnInfo->DBCtx;
	char stmt[1000];
	/* EXEC SQL END   DECLARE SECTION; */ 


	if (vCtx == NULL) {
		if (OraConnect(pDebugParms, DBConnInfo) != 0) LogWrite(pDebugParms, LOG_ERROR, "Ora_InsertDataParms() could not connect to Log Database...\n", 0);
		vCtx = DBConnInfo->DBCtx;
	}
	LogWrite(pDebugParms, LOG_INFO, "Ora_InsertDataParms() CheckPoint 2 - LogDB->DBCtx=%p , vCtx=%p\n", 2, DBConnInfo->DBCtx, vCtx);

	sprintf(&stmt[0], "insert into DataParms (ProcessId, DatasetId, DatasourceType, DatasourceFileName, Symbol, Timeframe, IsFilled, BarData, DataTransformation, WiggleRoom, HistoryLen, SampleLen, PredictionLen)\
					  values				(%d,			%d,		%d,				'%s',					'%s',		'%s',		%d,			%d,		%d,					%f,			%d,			%d,			%d)", \
		pid, pDatasetId, pDSType, pDSFileName, pSymbol, pTimeFrame, pIsFilled, pBarData, pDataTransformation, pwiggleRoom, pHistoryLen, pSampleLen, pPredictionLen);
	/* EXEC SQL EXECUTE IMMEDIATE : stmt; */ 

{
 struct sqlexd sqlstm;
 sqlstm.sqlvsn = 13;
 sqlstm.arrsiz = 5;
 sqlstm.sqladtp = &sqladt;
 sqlstm.sqltdsp = &sqltds;
 sqlstm.stmt = "";
 sqlstm.iters = (unsigned int  )1;
 sqlstm.offset = (unsigned int  )1286;
 sqlstm.cud = sqlcud0;
 sqlstm.sqlest = (unsigned char  *)&sqlca;
 sqlstm.sqlety = (unsigned short)4352;
 sqlstm.occurs = (unsigned int  )0;
 sqlstm.sqhstv[0] = (         void  *)stmt;
 sqlstm.sqhstl[0] = (unsigned int  )1000;
 sqlstm.sqhsts[0] = (         int  )0;
 sqlstm.sqindv[0] = (         void  *)0;
 sqlstm.sqinds[0] = (         int  )0;
 sqlstm.sqharm[0] = (unsigned int  )0;
 sqlstm.sqadto[0] = (unsigned short )0;
 sqlstm.sqtdso[0] = (unsigned short )0;
 sqlstm.sqphsv = sqlstm.sqhstv;
 sqlstm.sqphsl = sqlstm.sqhstl;
 sqlstm.sqphss = sqlstm.sqhsts;
 sqlstm.sqpind = sqlstm.sqindv;
 sqlstm.sqpins = sqlstm.sqinds;
 sqlstm.sqparm = sqlstm.sqharm;
 sqlstm.sqparc = sqlstm.sqharc;
 sqlstm.sqpadto = sqlstm.sqadto;
 sqlstm.sqptdso = sqlstm.sqtdso;
 sqlcxt(&vCtx, &sqlctx, &sqlstm, &sqlfpn);
}


	if (sqlca.sqlcode != 0) {
		LogWrite(pDebugParms, LOG_ERROR, "Ora_InsertDataParms() Insert into DataParms failed. SQL Error %d\n", 1, sqlca.sqlcode);
		return sqlca.sqlcode;
	}

	return 0;
}
EXPORT int Ora_InsertEngineParms(tDebugInfo* pDebugParms, tDBConnection* DBConnInfo, int pid, int pEngineType, int pLayersCount, int pWNNDecompLevel, char* pWNNWaveletType) {
	/* EXEC SQL BEGIN DECLARE SECTION; */ 

	sql_context vCtx = DBConnInfo->DBCtx;
	char stmt[1000];
	/* EXEC SQL END   DECLARE SECTION; */ 


	if (vCtx == NULL) {
		if (OraConnect(pDebugParms, DBConnInfo) != 0) LogWrite(pDebugParms, LOG_ERROR, "Ora_InsertEngineParms() could not connect to Log Database...\n", 0);
		vCtx = DBConnInfo->DBCtx;
	}
	LogWrite(pDebugParms, LOG_INFO, "Ora_InsertEngineParms() CheckPoint 2 - LogDB->DBCtx=%p , vCtx=%p\n", 2, DBConnInfo->DBCtx, vCtx);

	//-- 1. Insert into EngineParms
	sprintf(&stmt[0], "insert into EngineParms(ProcessId, EngineType, LayersCount, WNN_DecompLevel, WNN_WaveletType) values(%d, %d, %d, %d, '%s')", pid, pEngineType, pLayersCount, pWNNDecompLevel, pWNNWaveletType);
	/* EXEC SQL EXECUTE IMMEDIATE : stmt; */ 

{
 struct sqlexd sqlstm;
 sqlstm.sqlvsn = 13;
 sqlstm.arrsiz = 5;
 sqlstm.sqladtp = &sqladt;
 sqlstm.sqltdsp = &sqltds;
 sqlstm.stmt = "";
 sqlstm.iters = (unsigned int  )1;
 sqlstm.offset = (unsigned int  )1305;
 sqlstm.cud = sqlcud0;
 sqlstm.sqlest = (unsigned char  *)&sqlca;
 sqlstm.sqlety = (unsigned short)4352;
 sqlstm.occurs = (unsigned int  )0;
 sqlstm.sqhstv[0] = (         void  *)stmt;
 sqlstm.sqhstl[0] = (unsigned int  )1000;
 sqlstm.sqhsts[0] = (         int  )0;
 sqlstm.sqindv[0] = (         void  *)0;
 sqlstm.sqinds[0] = (         int  )0;
 sqlstm.sqharm[0] = (unsigned int  )0;
 sqlstm.sqadto[0] = (unsigned short )0;
 sqlstm.sqtdso[0] = (unsigned short )0;
 sqlstm.sqphsv = sqlstm.sqhstv;
 sqlstm.sqphsl = sqlstm.sqhstl;
 sqlstm.sqphss = sqlstm.sqhsts;
 sqlstm.sqpind = sqlstm.sqindv;
 sqlstm.sqpins = sqlstm.sqinds;
 sqlstm.sqparm = sqlstm.sqharm;
 sqlstm.sqparc = sqlstm.sqharc;
 sqlstm.sqpadto = sqlstm.sqadto;
 sqlstm.sqptdso = sqlstm.sqtdso;
 sqlcxt(&vCtx, &sqlctx, &sqlstm, &sqlfpn);
}


	if (sqlca.sqlcode != 0) {
		LogWrite(pDebugParms, LOG_ERROR, "Ora_InsertEngineParms() Insert into EngineParms failed. SQL Error %d ; stmt=%s\n", 2, sqlca.sqlcode, stmt);
		return sqlca.sqlcode;
	}

	return 0;
}
EXPORT int Ora_InsertEngineThreads(tDebugInfo* pDebugParms, tDBConnection* DBConnInfo, int pid, int testid, int layerid, int coreid, int coretype, int dsid, int tid) {
	/* EXEC SQL BEGIN DECLARE SECTION; */ 

	sql_context vCtx = DBConnInfo->DBCtx;
	char stmt[1000];
	/* EXEC SQL END   DECLARE SECTION; */ 


	if (vCtx == NULL) {
		if (OraConnect(pDebugParms, DBConnInfo) != 0) LogWrite(pDebugParms, LOG_ERROR, "%s() could not connect to Log Database...\n", 1, __func__);
		vCtx = DBConnInfo->DBCtx;
	}
	LogWrite(pDebugParms, LOG_INFO, "%s() CheckPoint 2 - LogDB->DBCtx=%p , vCtx=%p\n", 3, __func__, DBConnInfo->DBCtx, vCtx);

	sprintf(&stmt[0], "insert into EngineThreads(ProcessId, TestId, LayerId, CoreId, CoreType, DatasetId, ThreadId) values(%d, %d, %d, %d, %d, %d, %d)", pid, testid, layerid, coreid, coretype, dsid, tid);
	/* EXEC SQL EXECUTE IMMEDIATE : stmt; */ 

{
 struct sqlexd sqlstm;
 sqlstm.sqlvsn = 13;
 sqlstm.arrsiz = 5;
 sqlstm.sqladtp = &sqladt;
 sqlstm.sqltdsp = &sqltds;
 sqlstm.stmt = "";
 sqlstm.iters = (unsigned int  )1;
 sqlstm.offset = (unsigned int  )1324;
 sqlstm.cud = sqlcud0;
 sqlstm.sqlest = (unsigned char  *)&sqlca;
 sqlstm.sqlety = (unsigned short)4352;
 sqlstm.occurs = (unsigned int  )0;
 sqlstm.sqhstv[0] = (         void  *)stmt;
 sqlstm.sqhstl[0] = (unsigned int  )1000;
 sqlstm.sqhsts[0] = (         int  )0;
 sqlstm.sqindv[0] = (         void  *)0;
 sqlstm.sqinds[0] = (         int  )0;
 sqlstm.sqharm[0] = (unsigned int  )0;
 sqlstm.sqadto[0] = (unsigned short )0;
 sqlstm.sqtdso[0] = (unsigned short )0;
 sqlstm.sqphsv = sqlstm.sqhstv;
 sqlstm.sqphsl = sqlstm.sqhstl;
 sqlstm.sqphss = sqlstm.sqhsts;
 sqlstm.sqpind = sqlstm.sqindv;
 sqlstm.sqpins = sqlstm.sqinds;
 sqlstm.sqparm = sqlstm.sqharm;
 sqlstm.sqparc = sqlstm.sqharc;
 sqlstm.sqpadto = sqlstm.sqadto;
 sqlstm.sqptdso = sqlstm.sqtdso;
 sqlcxt(&vCtx, &sqlctx, &sqlstm, &sqlfpn);
}


	if (sqlca.sqlcode != 0) {
		LogWrite(pDebugParms, LOG_ERROR, "%s() Insert into EngineParms failed. SQL Error %d ; stmt=%s\n", 3, __func__, sqlca.sqlcode, stmt);
		return sqlca.sqlcode;
	}

	return 0;
}

//-- Load CoreParms(s)
EXPORT int Ora_GetCoreThreadId(tDebugInfo* DebugParms, tDBConnection* DBConnInfo, int pid, int testid, int DatasetId, int LayerId, int CoreId) {
	/* EXEC SQL BEGIN DECLARE SECTION; */ 

	sql_context vCtx =DBConnInfo->DBCtx;
	char stmt[1000];
	int Ctid;
	/* EXEC SQL END   DECLARE SECTION; */ 


	//-- Connects to DB only once
	if (vCtx == NULL) {
		if (OraConnect(DebugParms,DBConnInfo) != 0) printf("%s() could not connect to Log Database...\n", __func__);
		vCtx =DBConnInfo->DBCtx;
	}

	sprintf(&stmt[0], "select ThreadId from EngineThreads where ProcessId=%d and TestId=%d and DatasetId=%d and LayerId=%d and CoreId=%d", pid, testid, DatasetId, LayerId, CoreId);
	//-- Executes SQL 
	vCtx =DBConnInfo->DBCtx;
	/* EXEC SQL CONTEXT USE : vCtx; */ 

	/* EXEC SQL PREPARE sCtid FROM : stmt; */ 

{
 struct sqlexd sqlstm;
 sqlstm.sqlvsn = 13;
 sqlstm.arrsiz = 5;
 sqlstm.sqladtp = &sqladt;
 sqlstm.sqltdsp = &sqltds;
 sqlstm.stmt = "";
 sqlstm.iters = (unsigned int  )1;
 sqlstm.offset = (unsigned int  )1343;
 sqlstm.cud = sqlcud0;
 sqlstm.sqlest = (unsigned char  *)&sqlca;
 sqlstm.sqlety = (unsigned short)4352;
 sqlstm.occurs = (unsigned int  )0;
 sqlstm.sqhstv[0] = (         void  *)stmt;
 sqlstm.sqhstl[0] = (unsigned int  )1000;
 sqlstm.sqhsts[0] = (         int  )0;
 sqlstm.sqindv[0] = (         void  *)0;
 sqlstm.sqinds[0] = (         int  )0;
 sqlstm.sqharm[0] = (unsigned int  )0;
 sqlstm.sqadto[0] = (unsigned short )0;
 sqlstm.sqtdso[0] = (unsigned short )0;
 sqlstm.sqphsv = sqlstm.sqhstv;
 sqlstm.sqphsl = sqlstm.sqhstl;
 sqlstm.sqphss = sqlstm.sqhsts;
 sqlstm.sqpind = sqlstm.sqindv;
 sqlstm.sqpins = sqlstm.sqinds;
 sqlstm.sqparm = sqlstm.sqharm;
 sqlstm.sqparc = sqlstm.sqharc;
 sqlstm.sqpadto = sqlstm.sqadto;
 sqlstm.sqptdso = sqlstm.sqtdso;
 sqlcxt(&vCtx, &sqlctx, &sqlstm, &sqlfpn);
}


	/* EXEC SQL DECLARE cCtid CURSOR FOR sCtid; */ 

	/* EXEC SQL OPEN cCtid; */ 

{
 struct sqlexd sqlstm;
 sqlstm.sqlvsn = 13;
 sqlstm.arrsiz = 5;
 sqlstm.sqladtp = &sqladt;
 sqlstm.sqltdsp = &sqltds;
 sqlstm.stmt = "";
 sqlstm.iters = (unsigned int  )1;
 sqlstm.offset = (unsigned int  )1362;
 sqlstm.selerr = (unsigned short)1;
 sqlstm.sqlpfmem = (unsigned int  )0;
 sqlstm.cud = sqlcud0;
 sqlstm.sqlest = (unsigned char  *)&sqlca;
 sqlstm.sqlety = (unsigned short)4352;
 sqlstm.occurs = (unsigned int  )0;
 sqlstm.sqcmod = (unsigned int )0;
 sqlcxt(&vCtx, &sqlctx, &sqlstm, &sqlfpn);
}


	/* EXEC SQL FETCH cCtid INTO : Ctid; */ 

{
 struct sqlexd sqlstm;
 sqlstm.sqlvsn = 13;
 sqlstm.arrsiz = 5;
 sqlstm.sqladtp = &sqladt;
 sqlstm.sqltdsp = &sqltds;
 sqlstm.iters = (unsigned int  )1;
 sqlstm.offset = (unsigned int  )1377;
 sqlstm.selerr = (unsigned short)1;
 sqlstm.sqlpfmem = (unsigned int  )0;
 sqlstm.cud = sqlcud0;
 sqlstm.sqlest = (unsigned char  *)&sqlca;
 sqlstm.sqlety = (unsigned short)4352;
 sqlstm.occurs = (unsigned int  )0;
 sqlstm.sqfoff = (           int )0;
 sqlstm.sqfmod = (unsigned int )2;
 sqlstm.sqhstv[0] = (         void  *)&Ctid;
 sqlstm.sqhstl[0] = (unsigned int  )sizeof(int);
 sqlstm.sqhsts[0] = (         int  )0;
 sqlstm.sqindv[0] = (         void  *)0;
 sqlstm.sqinds[0] = (         int  )0;
 sqlstm.sqharm[0] = (unsigned int  )0;
 sqlstm.sqadto[0] = (unsigned short )0;
 sqlstm.sqtdso[0] = (unsigned short )0;
 sqlstm.sqphsv = sqlstm.sqhstv;
 sqlstm.sqphsl = sqlstm.sqhstl;
 sqlstm.sqphss = sqlstm.sqhsts;
 sqlstm.sqpind = sqlstm.sqindv;
 sqlstm.sqpins = sqlstm.sqinds;
 sqlstm.sqparm = sqlstm.sqharm;
 sqlstm.sqparc = sqlstm.sqharc;
 sqlstm.sqpadto = sqlstm.sqadto;
 sqlstm.sqptdso = sqlstm.sqtdso;
 sqlcxt(&vCtx, &sqlctx, &sqlstm, &sqlfpn);
}


	if (sqlca.sqlcode != 0) {
		LogWrite(DebugParms, LOG_ERROR, "%s(): SQL Error %d\n", 2, __func__, sqlca.sqlcode);
		return -1;
	}
	/* EXEC SQL CLOSE cCtid; */ 

{
 struct sqlexd sqlstm;
 sqlstm.sqlvsn = 13;
 sqlstm.arrsiz = 5;
 sqlstm.sqladtp = &sqladt;
 sqlstm.sqltdsp = &sqltds;
 sqlstm.iters = (unsigned int  )1;
 sqlstm.offset = (unsigned int  )1396;
 sqlstm.cud = sqlcud0;
 sqlstm.sqlest = (unsigned char  *)&sqlca;
 sqlstm.sqlety = (unsigned short)4352;
 sqlstm.occurs = (unsigned int  )0;
 sqlcxt(&vCtx, &sqlctx, &sqlstm, &sqlfpn);
}



	return Ctid;
}
EXPORT int Ora_LoadCoreParms_NN(tDebugInfo* DebugParms, tDBConnection* DBConnInfo, int pid, int tid,
	int* oInputCount, int* oOutputCount, int* oUseContext, int* oMaxEpochs, int* oBP_Algo, int* oActivationFunction,
	char* oLevelRatioS[256],
	double* oLearningRate, double* oLearningMomentum, double* oHCPbeta, double* oTargetMSE)
{
	/* EXEC SQL BEGIN DECLARE SECTION; */ 

	sql_context vCtx =DBConnInfo->DBCtx;
	char stmt[1000];
	//-- Network Properties variables
	int vInputCount, vOutputCount, vUseContext, vMaxEpochs, vBP_Algo, vActivationFunction;
	char vLevelRatios[256];
	double vLearningRate, vLearningMomentum, vHCPBeta, vTargetMSE;
	/* EXEC SQL END DECLARE SECTION; */ 


	//-- Connects to DB only once
	if (vCtx == NULL) {
		if (OraConnect(DebugParms,DBConnInfo) != 0) printf("%s() could not connect to Log Database...\n", __func__);
		vCtx =DBConnInfo->DBCtx;
	}

	sprintf(&stmt[0], "select InputCount, OutputCount, LevelRatioS, UseContext, MaxEpochs, BP_Algo, LearningRate, LearningMomentum, ActivationFunction, HCPBeta, TargetMSE from CoreParms_NN where ProcessId=%d and ThreadId=%d", pid, tid);
	/* EXEC SQL CONTEXT USE : vCtx; */ 

	/* EXEC SQL PREPARE sLEPNN FROM : stmt; */ 

{
 struct sqlexd sqlstm;
 sqlstm.sqlvsn = 13;
 sqlstm.arrsiz = 5;
 sqlstm.sqladtp = &sqladt;
 sqlstm.sqltdsp = &sqltds;
 sqlstm.stmt = "";
 sqlstm.iters = (unsigned int  )1;
 sqlstm.offset = (unsigned int  )1411;
 sqlstm.cud = sqlcud0;
 sqlstm.sqlest = (unsigned char  *)&sqlca;
 sqlstm.sqlety = (unsigned short)4352;
 sqlstm.occurs = (unsigned int  )0;
 sqlstm.sqhstv[0] = (         void  *)stmt;
 sqlstm.sqhstl[0] = (unsigned int  )1000;
 sqlstm.sqhsts[0] = (         int  )0;
 sqlstm.sqindv[0] = (         void  *)0;
 sqlstm.sqinds[0] = (         int  )0;
 sqlstm.sqharm[0] = (unsigned int  )0;
 sqlstm.sqadto[0] = (unsigned short )0;
 sqlstm.sqtdso[0] = (unsigned short )0;
 sqlstm.sqphsv = sqlstm.sqhstv;
 sqlstm.sqphsl = sqlstm.sqhstl;
 sqlstm.sqphss = sqlstm.sqhsts;
 sqlstm.sqpind = sqlstm.sqindv;
 sqlstm.sqpins = sqlstm.sqinds;
 sqlstm.sqparm = sqlstm.sqharm;
 sqlstm.sqparc = sqlstm.sqharc;
 sqlstm.sqpadto = sqlstm.sqadto;
 sqlstm.sqptdso = sqlstm.sqtdso;
 sqlcxt(&vCtx, &sqlctx, &sqlstm, &sqlfpn);
}


	/* EXEC SQL DECLARE cLEPNN CURSOR FOR sLEPNN; */ 

	/* EXEC SQL OPEN cLEPNN; */ 

{
 struct sqlexd sqlstm;
 sqlstm.sqlvsn = 13;
 sqlstm.arrsiz = 5;
 sqlstm.sqladtp = &sqladt;
 sqlstm.sqltdsp = &sqltds;
 sqlstm.stmt = "";
 sqlstm.iters = (unsigned int  )1;
 sqlstm.offset = (unsigned int  )1430;
 sqlstm.selerr = (unsigned short)1;
 sqlstm.sqlpfmem = (unsigned int  )0;
 sqlstm.cud = sqlcud0;
 sqlstm.sqlest = (unsigned char  *)&sqlca;
 sqlstm.sqlety = (unsigned short)4352;
 sqlstm.occurs = (unsigned int  )0;
 sqlstm.sqcmod = (unsigned int )0;
 sqlcxt(&vCtx, &sqlctx, &sqlstm, &sqlfpn);
}


	if (sqlca.sqlcode != 0) {
		LogWrite(DebugParms, LOG_ERROR, "%s: SQL Error %d ; stmt=%s\n", 3, __func__, sqlca.sqlcode, stmt);
		return sqlca.sqlcode;
	}
	/* EXEC SQL FETCH cLEPNN INTO vInputCount, vOutputCount, vLevelRatios, vUseContext, vMaxEpochs, vBP_Algo, vLearningRate, vLearningMomentum, vActivationFunction, vHCPBeta, vTargetMSE; */ 

{
 struct sqlexd sqlstm;
 sqlstm.sqlvsn = 13;
 sqlstm.arrsiz = 11;
 sqlstm.sqladtp = &sqladt;
 sqlstm.sqltdsp = &sqltds;
 sqlstm.iters = (unsigned int  )1;
 sqlstm.offset = (unsigned int  )1445;
 sqlstm.selerr = (unsigned short)1;
 sqlstm.sqlpfmem = (unsigned int  )0;
 sqlstm.cud = sqlcud0;
 sqlstm.sqlest = (unsigned char  *)&sqlca;
 sqlstm.sqlety = (unsigned short)4352;
 sqlstm.occurs = (unsigned int  )0;
 sqlstm.sqfoff = (           int )0;
 sqlstm.sqfmod = (unsigned int )2;
 sqlstm.sqhstv[0] = (         void  *)&vInputCount;
 sqlstm.sqhstl[0] = (unsigned int  )sizeof(int);
 sqlstm.sqhsts[0] = (         int  )0;
 sqlstm.sqindv[0] = (         void  *)0;
 sqlstm.sqinds[0] = (         int  )0;
 sqlstm.sqharm[0] = (unsigned int  )0;
 sqlstm.sqadto[0] = (unsigned short )0;
 sqlstm.sqtdso[0] = (unsigned short )0;
 sqlstm.sqhstv[1] = (         void  *)&vOutputCount;
 sqlstm.sqhstl[1] = (unsigned int  )sizeof(int);
 sqlstm.sqhsts[1] = (         int  )0;
 sqlstm.sqindv[1] = (         void  *)0;
 sqlstm.sqinds[1] = (         int  )0;
 sqlstm.sqharm[1] = (unsigned int  )0;
 sqlstm.sqadto[1] = (unsigned short )0;
 sqlstm.sqtdso[1] = (unsigned short )0;
 sqlstm.sqhstv[2] = (         void  *)vLevelRatios;
 sqlstm.sqhstl[2] = (unsigned int  )256;
 sqlstm.sqhsts[2] = (         int  )0;
 sqlstm.sqindv[2] = (         void  *)0;
 sqlstm.sqinds[2] = (         int  )0;
 sqlstm.sqharm[2] = (unsigned int  )0;
 sqlstm.sqadto[2] = (unsigned short )0;
 sqlstm.sqtdso[2] = (unsigned short )0;
 sqlstm.sqhstv[3] = (         void  *)&vUseContext;
 sqlstm.sqhstl[3] = (unsigned int  )sizeof(int);
 sqlstm.sqhsts[3] = (         int  )0;
 sqlstm.sqindv[3] = (         void  *)0;
 sqlstm.sqinds[3] = (         int  )0;
 sqlstm.sqharm[3] = (unsigned int  )0;
 sqlstm.sqadto[3] = (unsigned short )0;
 sqlstm.sqtdso[3] = (unsigned short )0;
 sqlstm.sqhstv[4] = (         void  *)&vMaxEpochs;
 sqlstm.sqhstl[4] = (unsigned int  )sizeof(int);
 sqlstm.sqhsts[4] = (         int  )0;
 sqlstm.sqindv[4] = (         void  *)0;
 sqlstm.sqinds[4] = (         int  )0;
 sqlstm.sqharm[4] = (unsigned int  )0;
 sqlstm.sqadto[4] = (unsigned short )0;
 sqlstm.sqtdso[4] = (unsigned short )0;
 sqlstm.sqhstv[5] = (         void  *)&vBP_Algo;
 sqlstm.sqhstl[5] = (unsigned int  )sizeof(int);
 sqlstm.sqhsts[5] = (         int  )0;
 sqlstm.sqindv[5] = (         void  *)0;
 sqlstm.sqinds[5] = (         int  )0;
 sqlstm.sqharm[5] = (unsigned int  )0;
 sqlstm.sqadto[5] = (unsigned short )0;
 sqlstm.sqtdso[5] = (unsigned short )0;
 sqlstm.sqhstv[6] = (         void  *)&vLearningRate;
 sqlstm.sqhstl[6] = (unsigned int  )sizeof(double);
 sqlstm.sqhsts[6] = (         int  )0;
 sqlstm.sqindv[6] = (         void  *)0;
 sqlstm.sqinds[6] = (         int  )0;
 sqlstm.sqharm[6] = (unsigned int  )0;
 sqlstm.sqadto[6] = (unsigned short )0;
 sqlstm.sqtdso[6] = (unsigned short )0;
 sqlstm.sqhstv[7] = (         void  *)&vLearningMomentum;
 sqlstm.sqhstl[7] = (unsigned int  )sizeof(double);
 sqlstm.sqhsts[7] = (         int  )0;
 sqlstm.sqindv[7] = (         void  *)0;
 sqlstm.sqinds[7] = (         int  )0;
 sqlstm.sqharm[7] = (unsigned int  )0;
 sqlstm.sqadto[7] = (unsigned short )0;
 sqlstm.sqtdso[7] = (unsigned short )0;
 sqlstm.sqhstv[8] = (         void  *)&vActivationFunction;
 sqlstm.sqhstl[8] = (unsigned int  )sizeof(int);
 sqlstm.sqhsts[8] = (         int  )0;
 sqlstm.sqindv[8] = (         void  *)0;
 sqlstm.sqinds[8] = (         int  )0;
 sqlstm.sqharm[8] = (unsigned int  )0;
 sqlstm.sqadto[8] = (unsigned short )0;
 sqlstm.sqtdso[8] = (unsigned short )0;
 sqlstm.sqhstv[9] = (         void  *)&vHCPBeta;
 sqlstm.sqhstl[9] = (unsigned int  )sizeof(double);
 sqlstm.sqhsts[9] = (         int  )0;
 sqlstm.sqindv[9] = (         void  *)0;
 sqlstm.sqinds[9] = (         int  )0;
 sqlstm.sqharm[9] = (unsigned int  )0;
 sqlstm.sqadto[9] = (unsigned short )0;
 sqlstm.sqtdso[9] = (unsigned short )0;
 sqlstm.sqhstv[10] = (         void  *)&vTargetMSE;
 sqlstm.sqhstl[10] = (unsigned int  )sizeof(double);
 sqlstm.sqhsts[10] = (         int  )0;
 sqlstm.sqindv[10] = (         void  *)0;
 sqlstm.sqinds[10] = (         int  )0;
 sqlstm.sqharm[10] = (unsigned int  )0;
 sqlstm.sqadto[10] = (unsigned short )0;
 sqlstm.sqtdso[10] = (unsigned short )0;
 sqlstm.sqphsv = sqlstm.sqhstv;
 sqlstm.sqphsl = sqlstm.sqhstl;
 sqlstm.sqphss = sqlstm.sqhsts;
 sqlstm.sqpind = sqlstm.sqindv;
 sqlstm.sqpins = sqlstm.sqinds;
 sqlstm.sqparm = sqlstm.sqharm;
 sqlstm.sqparc = sqlstm.sqharc;
 sqlstm.sqpadto = sqlstm.sqadto;
 sqlstm.sqptdso = sqlstm.sqtdso;
 sqlcxt(&vCtx, &sqlctx, &sqlstm, &sqlfpn);
}


	if (sqlca.sqlcode == 0) {
		(*oInputCount) = vInputCount; (*oOutputCount) = vOutputCount; (*oUseContext) = vUseContext; (*oMaxEpochs) = vMaxEpochs; (*oBP_Algo) = vBP_Algo; (*oLearningRate) = vLearningRate; (*oLearningMomentum) = vLearningMomentum; (*oActivationFunction) = vActivationFunction; (*oHCPbeta) = vHCPBeta; (*oTargetMSE) = vTargetMSE;
		strcpy((*oLevelRatioS), vLevelRatios);
	}
	else if (sqlca.sqlcode == 1403) {
		LogWrite(DebugParms, LOG_ERROR, "%s(): Core not found. ProcessId=%d ; ThreadId=%d\n", 3, __func__, pid, tid);
		return sqlca.sqlcode;
	}
	else {
		LogWrite(DebugParms, LOG_ERROR, "%s(): SQL Error %d in fetch\n", 2, __func__, sqlca.sqlcode);
		return sqlca.sqlcode;
	}
	/* EXEC SQL CLOSE cLEPNN; */ 

{
 struct sqlexd sqlstm;
 sqlstm.sqlvsn = 13;
 sqlstm.arrsiz = 11;
 sqlstm.sqladtp = &sqladt;
 sqlstm.sqltdsp = &sqltds;
 sqlstm.iters = (unsigned int  )1;
 sqlstm.offset = (unsigned int  )1504;
 sqlstm.cud = sqlcud0;
 sqlstm.sqlest = (unsigned char  *)&sqlca;
 sqlstm.sqlety = (unsigned short)4352;
 sqlstm.occurs = (unsigned int  )0;
 sqlcxt(&vCtx, &sqlctx, &sqlstm, &sqlfpn);
}



	return 0;
}
EXPORT int Ora_LoadCoreParms_SOM(tDebugInfo* DebugParms, tDBConnection* DBConnInfo, int pid, int tid,
	int* oInputCount, int* oOutputCount, int* oMaxEpochs, int* oTDFunction, int* oLRFunction,
	double* oBaseTD, double* oBaseLR)
{
	/* EXEC SQL BEGIN DECLARE SECTION; */ 

	sql_context vCtx =DBConnInfo->DBCtx;
	char stmt[1000];
	//-- SOM Properties variables
	int vInputCount, vOutputCount, vMaxEpochs, vTDFunction, vLRFunction;
	double vBaseTD, vBaseLR;
	/* EXEC SQL END DECLARE SECTION; */ 


	//-- Connects to DB only once
	if (vCtx == NULL) {
		if (OraConnect(DebugParms,DBConnInfo) != 0) printf("%s() could not connect to Log Database...\n", __func__);
		vCtx =DBConnInfo->DBCtx;
	}

	sprintf(&stmt[0], "select InputCount, OutputCount, MaxEpochs, TDFunction, BaseTD, LRFunction, BaseLR from CoreParms_SOM where ProcessId=%d and ThreadId=%d", pid, tid);
	/* EXEC SQL CONTEXT USE : vCtx; */ 

	/* EXEC SQL PREPARE sLEPSOM FROM : stmt; */ 

{
 struct sqlexd sqlstm;
 sqlstm.sqlvsn = 13;
 sqlstm.arrsiz = 11;
 sqlstm.sqladtp = &sqladt;
 sqlstm.sqltdsp = &sqltds;
 sqlstm.stmt = "";
 sqlstm.iters = (unsigned int  )1;
 sqlstm.offset = (unsigned int  )1519;
 sqlstm.cud = sqlcud0;
 sqlstm.sqlest = (unsigned char  *)&sqlca;
 sqlstm.sqlety = (unsigned short)4352;
 sqlstm.occurs = (unsigned int  )0;
 sqlstm.sqhstv[0] = (         void  *)stmt;
 sqlstm.sqhstl[0] = (unsigned int  )1000;
 sqlstm.sqhsts[0] = (         int  )0;
 sqlstm.sqindv[0] = (         void  *)0;
 sqlstm.sqinds[0] = (         int  )0;
 sqlstm.sqharm[0] = (unsigned int  )0;
 sqlstm.sqadto[0] = (unsigned short )0;
 sqlstm.sqtdso[0] = (unsigned short )0;
 sqlstm.sqphsv = sqlstm.sqhstv;
 sqlstm.sqphsl = sqlstm.sqhstl;
 sqlstm.sqphss = sqlstm.sqhsts;
 sqlstm.sqpind = sqlstm.sqindv;
 sqlstm.sqpins = sqlstm.sqinds;
 sqlstm.sqparm = sqlstm.sqharm;
 sqlstm.sqparc = sqlstm.sqharc;
 sqlstm.sqpadto = sqlstm.sqadto;
 sqlstm.sqptdso = sqlstm.sqtdso;
 sqlcxt(&vCtx, &sqlctx, &sqlstm, &sqlfpn);
}


	/* EXEC SQL DECLARE cLEPSOM CURSOR FOR sLEPSOM; */ 

	/* EXEC SQL OPEN cLEPSOM; */ 

{
 struct sqlexd sqlstm;
 sqlstm.sqlvsn = 13;
 sqlstm.arrsiz = 11;
 sqlstm.sqladtp = &sqladt;
 sqlstm.sqltdsp = &sqltds;
 sqlstm.stmt = "";
 sqlstm.iters = (unsigned int  )1;
 sqlstm.offset = (unsigned int  )1538;
 sqlstm.selerr = (unsigned short)1;
 sqlstm.sqlpfmem = (unsigned int  )0;
 sqlstm.cud = sqlcud0;
 sqlstm.sqlest = (unsigned char  *)&sqlca;
 sqlstm.sqlety = (unsigned short)4352;
 sqlstm.occurs = (unsigned int  )0;
 sqlstm.sqcmod = (unsigned int )0;
 sqlcxt(&vCtx, &sqlctx, &sqlstm, &sqlfpn);
}


	if (sqlca.sqlcode != 0) {
		LogWrite(DebugParms, LOG_ERROR, "%s: SQL Error %d\n", 2, __func__, sqlca.sqlcode); {printf("Press any key to continue...\n"); getchar();};
		return sqlca.sqlcode;
	}
	/* EXEC SQL FETCH cLEPSOM INTO vInputCount, vOutputCount, vMaxEpochs, vTDFunction, vBaseTD, vLRFunction, vBaseLR; */ 

{
 struct sqlexd sqlstm;
 sqlstm.sqlvsn = 13;
 sqlstm.arrsiz = 11;
 sqlstm.sqladtp = &sqladt;
 sqlstm.sqltdsp = &sqltds;
 sqlstm.iters = (unsigned int  )1;
 sqlstm.offset = (unsigned int  )1553;
 sqlstm.selerr = (unsigned short)1;
 sqlstm.sqlpfmem = (unsigned int  )0;
 sqlstm.cud = sqlcud0;
 sqlstm.sqlest = (unsigned char  *)&sqlca;
 sqlstm.sqlety = (unsigned short)4352;
 sqlstm.occurs = (unsigned int  )0;
 sqlstm.sqfoff = (           int )0;
 sqlstm.sqfmod = (unsigned int )2;
 sqlstm.sqhstv[0] = (         void  *)&vInputCount;
 sqlstm.sqhstl[0] = (unsigned int  )sizeof(int);
 sqlstm.sqhsts[0] = (         int  )0;
 sqlstm.sqindv[0] = (         void  *)0;
 sqlstm.sqinds[0] = (         int  )0;
 sqlstm.sqharm[0] = (unsigned int  )0;
 sqlstm.sqadto[0] = (unsigned short )0;
 sqlstm.sqtdso[0] = (unsigned short )0;
 sqlstm.sqhstv[1] = (         void  *)&vOutputCount;
 sqlstm.sqhstl[1] = (unsigned int  )sizeof(int);
 sqlstm.sqhsts[1] = (         int  )0;
 sqlstm.sqindv[1] = (         void  *)0;
 sqlstm.sqinds[1] = (         int  )0;
 sqlstm.sqharm[1] = (unsigned int  )0;
 sqlstm.sqadto[1] = (unsigned short )0;
 sqlstm.sqtdso[1] = (unsigned short )0;
 sqlstm.sqhstv[2] = (         void  *)&vMaxEpochs;
 sqlstm.sqhstl[2] = (unsigned int  )sizeof(int);
 sqlstm.sqhsts[2] = (         int  )0;
 sqlstm.sqindv[2] = (         void  *)0;
 sqlstm.sqinds[2] = (         int  )0;
 sqlstm.sqharm[2] = (unsigned int  )0;
 sqlstm.sqadto[2] = (unsigned short )0;
 sqlstm.sqtdso[2] = (unsigned short )0;
 sqlstm.sqhstv[3] = (         void  *)&vTDFunction;
 sqlstm.sqhstl[3] = (unsigned int  )sizeof(int);
 sqlstm.sqhsts[3] = (         int  )0;
 sqlstm.sqindv[3] = (         void  *)0;
 sqlstm.sqinds[3] = (         int  )0;
 sqlstm.sqharm[3] = (unsigned int  )0;
 sqlstm.sqadto[3] = (unsigned short )0;
 sqlstm.sqtdso[3] = (unsigned short )0;
 sqlstm.sqhstv[4] = (         void  *)&vBaseTD;
 sqlstm.sqhstl[4] = (unsigned int  )sizeof(double);
 sqlstm.sqhsts[4] = (         int  )0;
 sqlstm.sqindv[4] = (         void  *)0;
 sqlstm.sqinds[4] = (         int  )0;
 sqlstm.sqharm[4] = (unsigned int  )0;
 sqlstm.sqadto[4] = (unsigned short )0;
 sqlstm.sqtdso[4] = (unsigned short )0;
 sqlstm.sqhstv[5] = (         void  *)&vLRFunction;
 sqlstm.sqhstl[5] = (unsigned int  )sizeof(int);
 sqlstm.sqhsts[5] = (         int  )0;
 sqlstm.sqindv[5] = (         void  *)0;
 sqlstm.sqinds[5] = (         int  )0;
 sqlstm.sqharm[5] = (unsigned int  )0;
 sqlstm.sqadto[5] = (unsigned short )0;
 sqlstm.sqtdso[5] = (unsigned short )0;
 sqlstm.sqhstv[6] = (         void  *)&vBaseLR;
 sqlstm.sqhstl[6] = (unsigned int  )sizeof(double);
 sqlstm.sqhsts[6] = (         int  )0;
 sqlstm.sqindv[6] = (         void  *)0;
 sqlstm.sqinds[6] = (         int  )0;
 sqlstm.sqharm[6] = (unsigned int  )0;
 sqlstm.sqadto[6] = (unsigned short )0;
 sqlstm.sqtdso[6] = (unsigned short )0;
 sqlstm.sqphsv = sqlstm.sqhstv;
 sqlstm.sqphsl = sqlstm.sqhstl;
 sqlstm.sqphss = sqlstm.sqhsts;
 sqlstm.sqpind = sqlstm.sqindv;
 sqlstm.sqpins = sqlstm.sqinds;
 sqlstm.sqparm = sqlstm.sqharm;
 sqlstm.sqparc = sqlstm.sqharc;
 sqlstm.sqpadto = sqlstm.sqadto;
 sqlstm.sqptdso = sqlstm.sqtdso;
 sqlcxt(&vCtx, &sqlctx, &sqlstm, &sqlfpn);
}


	if (sqlca.sqlcode == 0) {
		(*oInputCount) = vInputCount; (*oOutputCount) = vOutputCount; (*oMaxEpochs) = vMaxEpochs; (*oTDFunction) = vTDFunction; (*oBaseTD) = vBaseTD; (*oLRFunction) = vLRFunction; (*oBaseLR) = vBaseLR;
	}
	else if (sqlca.sqlcode == 1403) {
		LogWrite(DebugParms, LOG_ERROR, "%s(): Core not found. ProcessId=%d ; ThreadId=%d\n", 3, __func__, pid, tid);
		return sqlca.sqlcode;
	}
	else {
		LogWrite(DebugParms, LOG_ERROR, "%s(): SQL Error %d\n", 2, __func__, sqlca.sqlcode);
		return sqlca.sqlcode;
	}
	/* EXEC SQL CLOSE cLEPSOM; */ 

{
 struct sqlexd sqlstm;
 sqlstm.sqlvsn = 13;
 sqlstm.arrsiz = 11;
 sqlstm.sqladtp = &sqladt;
 sqlstm.sqltdsp = &sqltds;
 sqlstm.iters = (unsigned int  )1;
 sqlstm.offset = (unsigned int  )1596;
 sqlstm.cud = sqlcud0;
 sqlstm.sqlest = (unsigned char  *)&sqlca;
 sqlstm.sqlety = (unsigned short)4352;
 sqlstm.occurs = (unsigned int  )0;
 sqlcxt(&vCtx, &sqlctx, &sqlstm, &sqlfpn);
}



	return 0;
}
EXPORT int Ora_LoadCoreParms_SVM(tDebugInfo* DebugParms, tDBConnection* DBConnInfo, int pid, int tid, 
	int* oInputCount, int* oMaxEpochs, int* osvmIterToShrink, int* oKernelType, int* oPolyDegree, int* oKernelCacheSize,
	double* oC, double* oEpsilon, double* oRBFGamma, double* oCoefLin, double* oCoefConst)
{
	/* EXEC SQL BEGIN DECLARE SECTION; */ 

	sql_context vCtx =DBConnInfo->DBCtx;
	char stmt[1000];
	//-- SVM Properties variables
	int vInputCount, vMaxEpochs, vIterToShrink, vKernelType, vPolyDegree, vKernelCacheSize;
	double vC, vEpsilon, vRBFGamma, vCoefLin, vCoefConst;
	/* EXEC SQL END DECLARE SECTION; */ 


	//-- Connects to DB only once
	if (vCtx == NULL) {
		if (OraConnect(DebugParms,DBConnInfo) != 0) printf("%s() could not connect to Log Database...\n", __func__);
		vCtx =DBConnInfo->DBCtx;
	}

	sprintf(&stmt[0], "select InputCount, MaxEpochs, C, Epsilon, IterToShrink, KernelType, PolyDegree, RBFGamma, CoefLin, CoefConst, KernelCacheSize from CoreParms_SVM where ProcessId=%d and ThreadId=%d", pid, tid);
	/* EXEC SQL CONTEXT USE : vCtx; */ 

	/* EXEC SQL PREPARE sLEPSVM FROM : stmt; */ 

{
 struct sqlexd sqlstm;
 sqlstm.sqlvsn = 13;
 sqlstm.arrsiz = 11;
 sqlstm.sqladtp = &sqladt;
 sqlstm.sqltdsp = &sqltds;
 sqlstm.stmt = "";
 sqlstm.iters = (unsigned int  )1;
 sqlstm.offset = (unsigned int  )1611;
 sqlstm.cud = sqlcud0;
 sqlstm.sqlest = (unsigned char  *)&sqlca;
 sqlstm.sqlety = (unsigned short)4352;
 sqlstm.occurs = (unsigned int  )0;
 sqlstm.sqhstv[0] = (         void  *)stmt;
 sqlstm.sqhstl[0] = (unsigned int  )1000;
 sqlstm.sqhsts[0] = (         int  )0;
 sqlstm.sqindv[0] = (         void  *)0;
 sqlstm.sqinds[0] = (         int  )0;
 sqlstm.sqharm[0] = (unsigned int  )0;
 sqlstm.sqadto[0] = (unsigned short )0;
 sqlstm.sqtdso[0] = (unsigned short )0;
 sqlstm.sqphsv = sqlstm.sqhstv;
 sqlstm.sqphsl = sqlstm.sqhstl;
 sqlstm.sqphss = sqlstm.sqhsts;
 sqlstm.sqpind = sqlstm.sqindv;
 sqlstm.sqpins = sqlstm.sqinds;
 sqlstm.sqparm = sqlstm.sqharm;
 sqlstm.sqparc = sqlstm.sqharc;
 sqlstm.sqpadto = sqlstm.sqadto;
 sqlstm.sqptdso = sqlstm.sqtdso;
 sqlcxt(&vCtx, &sqlctx, &sqlstm, &sqlfpn);
}


	/* EXEC SQL DECLARE cLEPSVM CURSOR FOR sLEPSVM; */ 

	/* EXEC SQL OPEN cLEPSVM; */ 

{
 struct sqlexd sqlstm;
 sqlstm.sqlvsn = 13;
 sqlstm.arrsiz = 11;
 sqlstm.sqladtp = &sqladt;
 sqlstm.sqltdsp = &sqltds;
 sqlstm.stmt = "";
 sqlstm.iters = (unsigned int  )1;
 sqlstm.offset = (unsigned int  )1630;
 sqlstm.selerr = (unsigned short)1;
 sqlstm.sqlpfmem = (unsigned int  )0;
 sqlstm.cud = sqlcud0;
 sqlstm.sqlest = (unsigned char  *)&sqlca;
 sqlstm.sqlety = (unsigned short)4352;
 sqlstm.occurs = (unsigned int  )0;
 sqlstm.sqcmod = (unsigned int )0;
 sqlcxt(&vCtx, &sqlctx, &sqlstm, &sqlfpn);
}


	if (sqlca.sqlcode != 0) {
		LogWrite(DebugParms, LOG_ERROR, "%s: SQL Error %d\n", 2, __func__, sqlca.sqlcode); {printf("Press any key to continue...\n"); getchar();};
		return sqlca.sqlcode;
	}
	/* EXEC SQL FETCH cLEPSVM INTO vInputCount, vMaxEpochs, vC, vEpsilon, vIterToShrink, vKernelType, vPolyDegree, vRBFGamma, vCoefLin, vCoefConst, vKernelCacheSize; */ 

{
 struct sqlexd sqlstm;
 sqlstm.sqlvsn = 13;
 sqlstm.arrsiz = 11;
 sqlstm.sqladtp = &sqladt;
 sqlstm.sqltdsp = &sqltds;
 sqlstm.iters = (unsigned int  )1;
 sqlstm.offset = (unsigned int  )1645;
 sqlstm.selerr = (unsigned short)1;
 sqlstm.sqlpfmem = (unsigned int  )0;
 sqlstm.cud = sqlcud0;
 sqlstm.sqlest = (unsigned char  *)&sqlca;
 sqlstm.sqlety = (unsigned short)4352;
 sqlstm.occurs = (unsigned int  )0;
 sqlstm.sqfoff = (           int )0;
 sqlstm.sqfmod = (unsigned int )2;
 sqlstm.sqhstv[0] = (         void  *)&vInputCount;
 sqlstm.sqhstl[0] = (unsigned int  )sizeof(int);
 sqlstm.sqhsts[0] = (         int  )0;
 sqlstm.sqindv[0] = (         void  *)0;
 sqlstm.sqinds[0] = (         int  )0;
 sqlstm.sqharm[0] = (unsigned int  )0;
 sqlstm.sqadto[0] = (unsigned short )0;
 sqlstm.sqtdso[0] = (unsigned short )0;
 sqlstm.sqhstv[1] = (         void  *)&vMaxEpochs;
 sqlstm.sqhstl[1] = (unsigned int  )sizeof(int);
 sqlstm.sqhsts[1] = (         int  )0;
 sqlstm.sqindv[1] = (         void  *)0;
 sqlstm.sqinds[1] = (         int  )0;
 sqlstm.sqharm[1] = (unsigned int  )0;
 sqlstm.sqadto[1] = (unsigned short )0;
 sqlstm.sqtdso[1] = (unsigned short )0;
 sqlstm.sqhstv[2] = (         void  *)&vC;
 sqlstm.sqhstl[2] = (unsigned int  )sizeof(double);
 sqlstm.sqhsts[2] = (         int  )0;
 sqlstm.sqindv[2] = (         void  *)0;
 sqlstm.sqinds[2] = (         int  )0;
 sqlstm.sqharm[2] = (unsigned int  )0;
 sqlstm.sqadto[2] = (unsigned short )0;
 sqlstm.sqtdso[2] = (unsigned short )0;
 sqlstm.sqhstv[3] = (         void  *)&vEpsilon;
 sqlstm.sqhstl[3] = (unsigned int  )sizeof(double);
 sqlstm.sqhsts[3] = (         int  )0;
 sqlstm.sqindv[3] = (         void  *)0;
 sqlstm.sqinds[3] = (         int  )0;
 sqlstm.sqharm[3] = (unsigned int  )0;
 sqlstm.sqadto[3] = (unsigned short )0;
 sqlstm.sqtdso[3] = (unsigned short )0;
 sqlstm.sqhstv[4] = (         void  *)&vIterToShrink;
 sqlstm.sqhstl[4] = (unsigned int  )sizeof(int);
 sqlstm.sqhsts[4] = (         int  )0;
 sqlstm.sqindv[4] = (         void  *)0;
 sqlstm.sqinds[4] = (         int  )0;
 sqlstm.sqharm[4] = (unsigned int  )0;
 sqlstm.sqadto[4] = (unsigned short )0;
 sqlstm.sqtdso[4] = (unsigned short )0;
 sqlstm.sqhstv[5] = (         void  *)&vKernelType;
 sqlstm.sqhstl[5] = (unsigned int  )sizeof(int);
 sqlstm.sqhsts[5] = (         int  )0;
 sqlstm.sqindv[5] = (         void  *)0;
 sqlstm.sqinds[5] = (         int  )0;
 sqlstm.sqharm[5] = (unsigned int  )0;
 sqlstm.sqadto[5] = (unsigned short )0;
 sqlstm.sqtdso[5] = (unsigned short )0;
 sqlstm.sqhstv[6] = (         void  *)&vPolyDegree;
 sqlstm.sqhstl[6] = (unsigned int  )sizeof(int);
 sqlstm.sqhsts[6] = (         int  )0;
 sqlstm.sqindv[6] = (         void  *)0;
 sqlstm.sqinds[6] = (         int  )0;
 sqlstm.sqharm[6] = (unsigned int  )0;
 sqlstm.sqadto[6] = (unsigned short )0;
 sqlstm.sqtdso[6] = (unsigned short )0;
 sqlstm.sqhstv[7] = (         void  *)&vRBFGamma;
 sqlstm.sqhstl[7] = (unsigned int  )sizeof(double);
 sqlstm.sqhsts[7] = (         int  )0;
 sqlstm.sqindv[7] = (         void  *)0;
 sqlstm.sqinds[7] = (         int  )0;
 sqlstm.sqharm[7] = (unsigned int  )0;
 sqlstm.sqadto[7] = (unsigned short )0;
 sqlstm.sqtdso[7] = (unsigned short )0;
 sqlstm.sqhstv[8] = (         void  *)&vCoefLin;
 sqlstm.sqhstl[8] = (unsigned int  )sizeof(double);
 sqlstm.sqhsts[8] = (         int  )0;
 sqlstm.sqindv[8] = (         void  *)0;
 sqlstm.sqinds[8] = (         int  )0;
 sqlstm.sqharm[8] = (unsigned int  )0;
 sqlstm.sqadto[8] = (unsigned short )0;
 sqlstm.sqtdso[8] = (unsigned short )0;
 sqlstm.sqhstv[9] = (         void  *)&vCoefConst;
 sqlstm.sqhstl[9] = (unsigned int  )sizeof(double);
 sqlstm.sqhsts[9] = (         int  )0;
 sqlstm.sqindv[9] = (         void  *)0;
 sqlstm.sqinds[9] = (         int  )0;
 sqlstm.sqharm[9] = (unsigned int  )0;
 sqlstm.sqadto[9] = (unsigned short )0;
 sqlstm.sqtdso[9] = (unsigned short )0;
 sqlstm.sqhstv[10] = (         void  *)&vKernelCacheSize;
 sqlstm.sqhstl[10] = (unsigned int  )sizeof(int);
 sqlstm.sqhsts[10] = (         int  )0;
 sqlstm.sqindv[10] = (         void  *)0;
 sqlstm.sqinds[10] = (         int  )0;
 sqlstm.sqharm[10] = (unsigned int  )0;
 sqlstm.sqadto[10] = (unsigned short )0;
 sqlstm.sqtdso[10] = (unsigned short )0;
 sqlstm.sqphsv = sqlstm.sqhstv;
 sqlstm.sqphsl = sqlstm.sqhstl;
 sqlstm.sqphss = sqlstm.sqhsts;
 sqlstm.sqpind = sqlstm.sqindv;
 sqlstm.sqpins = sqlstm.sqinds;
 sqlstm.sqparm = sqlstm.sqharm;
 sqlstm.sqparc = sqlstm.sqharc;
 sqlstm.sqpadto = sqlstm.sqadto;
 sqlstm.sqptdso = sqlstm.sqtdso;
 sqlcxt(&vCtx, &sqlctx, &sqlstm, &sqlfpn);
}


	if (sqlca.sqlcode == 0) {
		(*oInputCount) = vInputCount; (*oMaxEpochs) = vMaxEpochs; (*oC) = vC; (*oEpsilon) = vEpsilon; (*osvmIterToShrink) = vIterToShrink; (*oKernelType) = vKernelType; (*oPolyDegree) = vPolyDegree; (*oRBFGamma) = vRBFGamma; (*oCoefLin) = vCoefLin; (*oCoefConst) = vCoefConst; (*oKernelCacheSize) = vKernelCacheSize;
	}
	else if (sqlca.sqlcode == 1403) {
		LogWrite(DebugParms, LOG_ERROR, "%s(): Core not found. ProcessId=%d ; ThreadId=%d\n", 3, __func__, pid, tid);
		return sqlca.sqlcode;
	}
	else {
		LogWrite(DebugParms, LOG_ERROR, "%s(): SQL Error %d\n", 2, __func__, sqlca.sqlcode);
		return sqlca.sqlcode;
	}
	/* EXEC SQL CLOSE cLEPSVM; */ 

{
 struct sqlexd sqlstm;
 sqlstm.sqlvsn = 13;
 sqlstm.arrsiz = 11;
 sqlstm.sqladtp = &sqladt;
 sqlstm.sqltdsp = &sqltds;
 sqlstm.iters = (unsigned int  )1;
 sqlstm.offset = (unsigned int  )1704;
 sqlstm.cud = sqlcud0;
 sqlstm.sqlest = (unsigned char  *)&sqlca;
 sqlstm.sqlety = (unsigned short)4352;
 sqlstm.occurs = (unsigned int  )0;
 sqlcxt(&vCtx, &sqlctx, &sqlstm, &sqlfpn);
}



	return 0;
}

//-- Load Core Image(s)
EXPORT int Ora_LoadCoreImage_NN(tDebugInfo* DebugParms, tDBConnection* DBConnInfo, int pid, int tid, double*** oFinalW) {
	/* EXEC SQL BEGIN DECLARE SECTION; */ 

	int retval = 0;
	sql_context vCtx =DBConnInfo->DBCtx;
	char stmt[1000];
	//-- Network Weights variables
	int vNeuronLevel; int vFromNeuron; int vToNeuron; double vWeight;
	/* EXEC SQL END DECLARE SECTION; */ 


	//-- Connects to DB only once
	if (vCtx == NULL) {
		if (OraConnect(DebugParms,DBConnInfo) != 0) printf("%s() could not connect to Log Database...\n", __func__);
		vCtx =DBConnInfo->DBCtx;
	}

	//-- Load Network Weights from CoreImage_NN
	sprintf(&stmt[0], "select NeuronLevel, FromNeuron, ToNeuron, Weight from CoreImage_NN where ProcessId=%d and ThreadId=%d order by 1,2,3", pid, tid);
	LogWrite(DebugParms, LOG_INFO, "%s() CheckPoint 3 - stmt=%s\n", 2, __func__, stmt);
	/* EXEC SQL CONTEXT USE : vCtx; */ 

	/* EXEC SQL PREPARE sLINN FROM : stmt; */ 

{
 struct sqlexd sqlstm;
 sqlstm.sqlvsn = 13;
 sqlstm.arrsiz = 11;
 sqlstm.sqladtp = &sqladt;
 sqlstm.sqltdsp = &sqltds;
 sqlstm.stmt = "";
 sqlstm.iters = (unsigned int  )1;
 sqlstm.offset = (unsigned int  )1719;
 sqlstm.cud = sqlcud0;
 sqlstm.sqlest = (unsigned char  *)&sqlca;
 sqlstm.sqlety = (unsigned short)4352;
 sqlstm.occurs = (unsigned int  )0;
 sqlstm.sqhstv[0] = (         void  *)stmt;
 sqlstm.sqhstl[0] = (unsigned int  )1000;
 sqlstm.sqhsts[0] = (         int  )0;
 sqlstm.sqindv[0] = (         void  *)0;
 sqlstm.sqinds[0] = (         int  )0;
 sqlstm.sqharm[0] = (unsigned int  )0;
 sqlstm.sqadto[0] = (unsigned short )0;
 sqlstm.sqtdso[0] = (unsigned short )0;
 sqlstm.sqphsv = sqlstm.sqhstv;
 sqlstm.sqphsl = sqlstm.sqhstl;
 sqlstm.sqphss = sqlstm.sqhsts;
 sqlstm.sqpind = sqlstm.sqindv;
 sqlstm.sqpins = sqlstm.sqinds;
 sqlstm.sqparm = sqlstm.sqharm;
 sqlstm.sqparc = sqlstm.sqharc;
 sqlstm.sqpadto = sqlstm.sqadto;
 sqlstm.sqptdso = sqlstm.sqtdso;
 sqlcxt(&vCtx, &sqlctx, &sqlstm, &sqlfpn);
}


	/* EXEC SQL DECLARE cLINN CURSOR FOR sLINN; */ 

	/* EXEC SQL OPEN cLINN; */ 

{
 struct sqlexd sqlstm;
 sqlstm.sqlvsn = 13;
 sqlstm.arrsiz = 11;
 sqlstm.sqladtp = &sqladt;
 sqlstm.sqltdsp = &sqltds;
 sqlstm.stmt = "";
 sqlstm.iters = (unsigned int  )1;
 sqlstm.offset = (unsigned int  )1738;
 sqlstm.selerr = (unsigned short)1;
 sqlstm.sqlpfmem = (unsigned int  )0;
 sqlstm.cud = sqlcud0;
 sqlstm.sqlest = (unsigned char  *)&sqlca;
 sqlstm.sqlety = (unsigned short)4352;
 sqlstm.occurs = (unsigned int  )0;
 sqlstm.sqcmod = (unsigned int )0;
 sqlcxt(&vCtx, &sqlctx, &sqlstm, &sqlfpn);
}


	while (TRUE) {
		/* EXEC SQL FETCH cLINN INTO vNeuronLevel, vFromNeuron, vToNeuron, vWeight; */ 

{
  struct sqlexd sqlstm;
  sqlstm.sqlvsn = 13;
  sqlstm.arrsiz = 11;
  sqlstm.sqladtp = &sqladt;
  sqlstm.sqltdsp = &sqltds;
  sqlstm.iters = (unsigned int  )1;
  sqlstm.offset = (unsigned int  )1753;
  sqlstm.selerr = (unsigned short)1;
  sqlstm.sqlpfmem = (unsigned int  )0;
  sqlstm.cud = sqlcud0;
  sqlstm.sqlest = (unsigned char  *)&sqlca;
  sqlstm.sqlety = (unsigned short)4352;
  sqlstm.occurs = (unsigned int  )0;
  sqlstm.sqfoff = (           int )0;
  sqlstm.sqfmod = (unsigned int )2;
  sqlstm.sqhstv[0] = (         void  *)&vNeuronLevel;
  sqlstm.sqhstl[0] = (unsigned int  )sizeof(int);
  sqlstm.sqhsts[0] = (         int  )0;
  sqlstm.sqindv[0] = (         void  *)0;
  sqlstm.sqinds[0] = (         int  )0;
  sqlstm.sqharm[0] = (unsigned int  )0;
  sqlstm.sqadto[0] = (unsigned short )0;
  sqlstm.sqtdso[0] = (unsigned short )0;
  sqlstm.sqhstv[1] = (         void  *)&vFromNeuron;
  sqlstm.sqhstl[1] = (unsigned int  )sizeof(int);
  sqlstm.sqhsts[1] = (         int  )0;
  sqlstm.sqindv[1] = (         void  *)0;
  sqlstm.sqinds[1] = (         int  )0;
  sqlstm.sqharm[1] = (unsigned int  )0;
  sqlstm.sqadto[1] = (unsigned short )0;
  sqlstm.sqtdso[1] = (unsigned short )0;
  sqlstm.sqhstv[2] = (         void  *)&vToNeuron;
  sqlstm.sqhstl[2] = (unsigned int  )sizeof(int);
  sqlstm.sqhsts[2] = (         int  )0;
  sqlstm.sqindv[2] = (         void  *)0;
  sqlstm.sqinds[2] = (         int  )0;
  sqlstm.sqharm[2] = (unsigned int  )0;
  sqlstm.sqadto[2] = (unsigned short )0;
  sqlstm.sqtdso[2] = (unsigned short )0;
  sqlstm.sqhstv[3] = (         void  *)&vWeight;
  sqlstm.sqhstl[3] = (unsigned int  )sizeof(double);
  sqlstm.sqhsts[3] = (         int  )0;
  sqlstm.sqindv[3] = (         void  *)0;
  sqlstm.sqinds[3] = (         int  )0;
  sqlstm.sqharm[3] = (unsigned int  )0;
  sqlstm.sqadto[3] = (unsigned short )0;
  sqlstm.sqtdso[3] = (unsigned short )0;
  sqlstm.sqphsv = sqlstm.sqhstv;
  sqlstm.sqphsl = sqlstm.sqhstl;
  sqlstm.sqphss = sqlstm.sqhsts;
  sqlstm.sqpind = sqlstm.sqindv;
  sqlstm.sqpins = sqlstm.sqinds;
  sqlstm.sqparm = sqlstm.sqharm;
  sqlstm.sqparc = sqlstm.sqharc;
  sqlstm.sqpadto = sqlstm.sqadto;
  sqlstm.sqptdso = sqlstm.sqtdso;
  sqlcxt(&vCtx, &sqlctx, &sqlstm, &sqlfpn);
}


		if (sqlca.sqlcode == 0) {
			oFinalW[vNeuronLevel][vFromNeuron][vToNeuron] = vWeight;
		} else if (sqlca.sqlcode == 1403) {
			break;
		} else {
			LogWrite(DebugParms, LOG_ERROR, "%s(): SQL Error %d\n", 2, __func__, sqlca.sqlcode);
			retval = sqlca.sqlcode;
			break;
		}
	}
	/* EXEC SQL CLOSE cLINN; */ 

{
 struct sqlexd sqlstm;
 sqlstm.sqlvsn = 13;
 sqlstm.arrsiz = 11;
 sqlstm.sqladtp = &sqladt;
 sqlstm.sqltdsp = &sqltds;
 sqlstm.iters = (unsigned int  )1;
 sqlstm.offset = (unsigned int  )1784;
 sqlstm.cud = sqlcud0;
 sqlstm.sqlest = (unsigned char  *)&sqlca;
 sqlstm.sqlety = (unsigned short)4352;
 sqlstm.occurs = (unsigned int  )0;
 sqlcxt(&vCtx, &sqlctx, &sqlstm, &sqlfpn);
}



	return retval;
}
EXPORT int Ora_LoadCoreImage_SOM(tDebugInfo* DebugParms, tDBConnection* DBConnInfo, int pid, int tid, double** oSOMWeight) {
	/* EXEC SQL BEGIN DECLARE SECTION; */ 

	int retval = 0;
	sql_context vCtx =DBConnInfo->DBCtx;
	char stmt[1000];
	//-- Network Weights variables
	int vFromNeuron; int vToNeuron; double vWeight;
	/* EXEC SQL END DECLARE SECTION; */ 


	//-- Connects to DB only once
	if (vCtx == NULL) {
		if (OraConnect(DebugParms,DBConnInfo) != 0) printf("%s() could not connect to Log Database...\n", __func__);
		vCtx =DBConnInfo->DBCtx;
	}

	//-- Load Network Weights from CoreImage_NN
	sprintf(&stmt[0], "select FromNeuron, ToNeuron, Weight from CoreImage_SOM where ProcessId=%d and ThreadId=%d order by 1,2,3", pid, tid);
	LogWrite(DebugParms, LOG_INFO, "%s() CheckPoint 3 - stmt=%s\n", 2, __func__, stmt);
	/* EXEC SQL CONTEXT USE : vCtx; */ 

	/* EXEC SQL PREPARE sLISOM FROM : stmt; */ 

{
 struct sqlexd sqlstm;
 sqlstm.sqlvsn = 13;
 sqlstm.arrsiz = 11;
 sqlstm.sqladtp = &sqladt;
 sqlstm.sqltdsp = &sqltds;
 sqlstm.stmt = "";
 sqlstm.iters = (unsigned int  )1;
 sqlstm.offset = (unsigned int  )1799;
 sqlstm.cud = sqlcud0;
 sqlstm.sqlest = (unsigned char  *)&sqlca;
 sqlstm.sqlety = (unsigned short)4352;
 sqlstm.occurs = (unsigned int  )0;
 sqlstm.sqhstv[0] = (         void  *)stmt;
 sqlstm.sqhstl[0] = (unsigned int  )1000;
 sqlstm.sqhsts[0] = (         int  )0;
 sqlstm.sqindv[0] = (         void  *)0;
 sqlstm.sqinds[0] = (         int  )0;
 sqlstm.sqharm[0] = (unsigned int  )0;
 sqlstm.sqadto[0] = (unsigned short )0;
 sqlstm.sqtdso[0] = (unsigned short )0;
 sqlstm.sqphsv = sqlstm.sqhstv;
 sqlstm.sqphsl = sqlstm.sqhstl;
 sqlstm.sqphss = sqlstm.sqhsts;
 sqlstm.sqpind = sqlstm.sqindv;
 sqlstm.sqpins = sqlstm.sqinds;
 sqlstm.sqparm = sqlstm.sqharm;
 sqlstm.sqparc = sqlstm.sqharc;
 sqlstm.sqpadto = sqlstm.sqadto;
 sqlstm.sqptdso = sqlstm.sqtdso;
 sqlcxt(&vCtx, &sqlctx, &sqlstm, &sqlfpn);
}


	/* EXEC SQL DECLARE cLISOM CURSOR FOR sLISOM; */ 

	/* EXEC SQL OPEN cLISOM; */ 

{
 struct sqlexd sqlstm;
 sqlstm.sqlvsn = 13;
 sqlstm.arrsiz = 11;
 sqlstm.sqladtp = &sqladt;
 sqlstm.sqltdsp = &sqltds;
 sqlstm.stmt = "";
 sqlstm.iters = (unsigned int  )1;
 sqlstm.offset = (unsigned int  )1818;
 sqlstm.selerr = (unsigned short)1;
 sqlstm.sqlpfmem = (unsigned int  )0;
 sqlstm.cud = sqlcud0;
 sqlstm.sqlest = (unsigned char  *)&sqlca;
 sqlstm.sqlety = (unsigned short)4352;
 sqlstm.occurs = (unsigned int  )0;
 sqlstm.sqcmod = (unsigned int )0;
 sqlcxt(&vCtx, &sqlctx, &sqlstm, &sqlfpn);
}


	while (TRUE) {
		/* EXEC SQL FETCH cLISOM INTO vFromNeuron, vToNeuron, vWeight; */ 

{
  struct sqlexd sqlstm;
  sqlstm.sqlvsn = 13;
  sqlstm.arrsiz = 11;
  sqlstm.sqladtp = &sqladt;
  sqlstm.sqltdsp = &sqltds;
  sqlstm.iters = (unsigned int  )1;
  sqlstm.offset = (unsigned int  )1833;
  sqlstm.selerr = (unsigned short)1;
  sqlstm.sqlpfmem = (unsigned int  )0;
  sqlstm.cud = sqlcud0;
  sqlstm.sqlest = (unsigned char  *)&sqlca;
  sqlstm.sqlety = (unsigned short)4352;
  sqlstm.occurs = (unsigned int  )0;
  sqlstm.sqfoff = (           int )0;
  sqlstm.sqfmod = (unsigned int )2;
  sqlstm.sqhstv[0] = (         void  *)&vFromNeuron;
  sqlstm.sqhstl[0] = (unsigned int  )sizeof(int);
  sqlstm.sqhsts[0] = (         int  )0;
  sqlstm.sqindv[0] = (         void  *)0;
  sqlstm.sqinds[0] = (         int  )0;
  sqlstm.sqharm[0] = (unsigned int  )0;
  sqlstm.sqadto[0] = (unsigned short )0;
  sqlstm.sqtdso[0] = (unsigned short )0;
  sqlstm.sqhstv[1] = (         void  *)&vToNeuron;
  sqlstm.sqhstl[1] = (unsigned int  )sizeof(int);
  sqlstm.sqhsts[1] = (         int  )0;
  sqlstm.sqindv[1] = (         void  *)0;
  sqlstm.sqinds[1] = (         int  )0;
  sqlstm.sqharm[1] = (unsigned int  )0;
  sqlstm.sqadto[1] = (unsigned short )0;
  sqlstm.sqtdso[1] = (unsigned short )0;
  sqlstm.sqhstv[2] = (         void  *)&vWeight;
  sqlstm.sqhstl[2] = (unsigned int  )sizeof(double);
  sqlstm.sqhsts[2] = (         int  )0;
  sqlstm.sqindv[2] = (         void  *)0;
  sqlstm.sqinds[2] = (         int  )0;
  sqlstm.sqharm[2] = (unsigned int  )0;
  sqlstm.sqadto[2] = (unsigned short )0;
  sqlstm.sqtdso[2] = (unsigned short )0;
  sqlstm.sqphsv = sqlstm.sqhstv;
  sqlstm.sqphsl = sqlstm.sqhstl;
  sqlstm.sqphss = sqlstm.sqhsts;
  sqlstm.sqpind = sqlstm.sqindv;
  sqlstm.sqpins = sqlstm.sqinds;
  sqlstm.sqparm = sqlstm.sqharm;
  sqlstm.sqparc = sqlstm.sqharc;
  sqlstm.sqpadto = sqlstm.sqadto;
  sqlstm.sqptdso = sqlstm.sqtdso;
  sqlcxt(&vCtx, &sqlctx, &sqlstm, &sqlfpn);
}


		if (sqlca.sqlcode == 0) {
			oSOMWeight[vFromNeuron][vToNeuron] = vWeight;
		} else if (sqlca.sqlcode == 1403) {
			break;
		} else {
			LogWrite(DebugParms, LOG_ERROR, "%s(): SQL Error %d\n", 2, __func__, sqlca.sqlcode);
			retval = sqlca.sqlcode;
			break;
		}
	}
	/* EXEC SQL CLOSE cLISOM; */ 

{
 struct sqlexd sqlstm;
 sqlstm.sqlvsn = 13;
 sqlstm.arrsiz = 11;
 sqlstm.sqladtp = &sqladt;
 sqlstm.sqltdsp = &sqltds;
 sqlstm.iters = (unsigned int  )1;
 sqlstm.offset = (unsigned int  )1860;
 sqlstm.cud = sqlcud0;
 sqlstm.sqlest = (unsigned char  *)&sqlca;
 sqlstm.sqlety = (unsigned short)4352;
 sqlstm.occurs = (unsigned int  )0;
 sqlcxt(&vCtx, &sqlctx, &sqlstm, &sqlfpn);
}



	return retval;
}
EXPORT int Ora_LoadCoreImage_SVM(tDebugInfo* DebugParms, tDBConnection* DBConnInfo, int pid, int tid, double** oSVMWeight) {
	/* EXEC SQL BEGIN DECLARE SECTION; */ 

	int retval = 0;
	sql_context vCtx =DBConnInfo->DBCtx;
	char stmt[1000];
	//-- Support Vector variables
	int vSVid; int vVarId; double vWeight;
	/* EXEC SQL END DECLARE SECTION; */ 


	//-- Connects to DB only once
	if (vCtx == NULL) {
		if (OraConnect(DebugParms,DBConnInfo) != 0) printf("%s() could not connect to Log Database...\n", __func__);
		vCtx =DBConnInfo->DBCtx;
	}

	//-- Load Support Vectors from CoreImage_SVM
	sprintf(&stmt[0], "select SVid, VarId, Weight from CoreImage_SVM where ProcessId=%d and ThreadId=%d order by 1,2,3", pid, tid);
	LogWrite(DebugParms, LOG_INFO, "%s() CheckPoint 3 - stmt=%s\n", 2, __func__, stmt);
	/* EXEC SQL CONTEXT USE : vCtx; */ 

	/* EXEC SQL PREPARE sLISVM FROM : stmt; */ 

{
 struct sqlexd sqlstm;
 sqlstm.sqlvsn = 13;
 sqlstm.arrsiz = 11;
 sqlstm.sqladtp = &sqladt;
 sqlstm.sqltdsp = &sqltds;
 sqlstm.stmt = "";
 sqlstm.iters = (unsigned int  )1;
 sqlstm.offset = (unsigned int  )1875;
 sqlstm.cud = sqlcud0;
 sqlstm.sqlest = (unsigned char  *)&sqlca;
 sqlstm.sqlety = (unsigned short)4352;
 sqlstm.occurs = (unsigned int  )0;
 sqlstm.sqhstv[0] = (         void  *)stmt;
 sqlstm.sqhstl[0] = (unsigned int  )1000;
 sqlstm.sqhsts[0] = (         int  )0;
 sqlstm.sqindv[0] = (         void  *)0;
 sqlstm.sqinds[0] = (         int  )0;
 sqlstm.sqharm[0] = (unsigned int  )0;
 sqlstm.sqadto[0] = (unsigned short )0;
 sqlstm.sqtdso[0] = (unsigned short )0;
 sqlstm.sqphsv = sqlstm.sqhstv;
 sqlstm.sqphsl = sqlstm.sqhstl;
 sqlstm.sqphss = sqlstm.sqhsts;
 sqlstm.sqpind = sqlstm.sqindv;
 sqlstm.sqpins = sqlstm.sqinds;
 sqlstm.sqparm = sqlstm.sqharm;
 sqlstm.sqparc = sqlstm.sqharc;
 sqlstm.sqpadto = sqlstm.sqadto;
 sqlstm.sqptdso = sqlstm.sqtdso;
 sqlcxt(&vCtx, &sqlctx, &sqlstm, &sqlfpn);
}


	/* EXEC SQL DECLARE cLISVM CURSOR FOR sLISVM; */ 

	/* EXEC SQL OPEN cLISVM; */ 

{
 struct sqlexd sqlstm;
 sqlstm.sqlvsn = 13;
 sqlstm.arrsiz = 11;
 sqlstm.sqladtp = &sqladt;
 sqlstm.sqltdsp = &sqltds;
 sqlstm.stmt = "";
 sqlstm.iters = (unsigned int  )1;
 sqlstm.offset = (unsigned int  )1894;
 sqlstm.selerr = (unsigned short)1;
 sqlstm.sqlpfmem = (unsigned int  )0;
 sqlstm.cud = sqlcud0;
 sqlstm.sqlest = (unsigned char  *)&sqlca;
 sqlstm.sqlety = (unsigned short)4352;
 sqlstm.occurs = (unsigned int  )0;
 sqlstm.sqcmod = (unsigned int )0;
 sqlcxt(&vCtx, &sqlctx, &sqlstm, &sqlfpn);
}


	while (TRUE) {
		/* EXEC SQL FETCH cLISVM INTO vSVid, vVarId, vWeight; */ 

{
  struct sqlexd sqlstm;
  sqlstm.sqlvsn = 13;
  sqlstm.arrsiz = 11;
  sqlstm.sqladtp = &sqladt;
  sqlstm.sqltdsp = &sqltds;
  sqlstm.iters = (unsigned int  )1;
  sqlstm.offset = (unsigned int  )1909;
  sqlstm.selerr = (unsigned short)1;
  sqlstm.sqlpfmem = (unsigned int  )0;
  sqlstm.cud = sqlcud0;
  sqlstm.sqlest = (unsigned char  *)&sqlca;
  sqlstm.sqlety = (unsigned short)4352;
  sqlstm.occurs = (unsigned int  )0;
  sqlstm.sqfoff = (           int )0;
  sqlstm.sqfmod = (unsigned int )2;
  sqlstm.sqhstv[0] = (         void  *)&vSVid;
  sqlstm.sqhstl[0] = (unsigned int  )sizeof(int);
  sqlstm.sqhsts[0] = (         int  )0;
  sqlstm.sqindv[0] = (         void  *)0;
  sqlstm.sqinds[0] = (         int  )0;
  sqlstm.sqharm[0] = (unsigned int  )0;
  sqlstm.sqadto[0] = (unsigned short )0;
  sqlstm.sqtdso[0] = (unsigned short )0;
  sqlstm.sqhstv[1] = (         void  *)&vVarId;
  sqlstm.sqhstl[1] = (unsigned int  )sizeof(int);
  sqlstm.sqhsts[1] = (         int  )0;
  sqlstm.sqindv[1] = (         void  *)0;
  sqlstm.sqinds[1] = (         int  )0;
  sqlstm.sqharm[1] = (unsigned int  )0;
  sqlstm.sqadto[1] = (unsigned short )0;
  sqlstm.sqtdso[1] = (unsigned short )0;
  sqlstm.sqhstv[2] = (         void  *)&vWeight;
  sqlstm.sqhstl[2] = (unsigned int  )sizeof(double);
  sqlstm.sqhsts[2] = (         int  )0;
  sqlstm.sqindv[2] = (         void  *)0;
  sqlstm.sqinds[2] = (         int  )0;
  sqlstm.sqharm[2] = (unsigned int  )0;
  sqlstm.sqadto[2] = (unsigned short )0;
  sqlstm.sqtdso[2] = (unsigned short )0;
  sqlstm.sqphsv = sqlstm.sqhstv;
  sqlstm.sqphsl = sqlstm.sqhstl;
  sqlstm.sqphss = sqlstm.sqhsts;
  sqlstm.sqpind = sqlstm.sqindv;
  sqlstm.sqpins = sqlstm.sqinds;
  sqlstm.sqparm = sqlstm.sqharm;
  sqlstm.sqparc = sqlstm.sqharc;
  sqlstm.sqpadto = sqlstm.sqadto;
  sqlstm.sqptdso = sqlstm.sqtdso;
  sqlcxt(&vCtx, &sqlctx, &sqlstm, &sqlfpn);
}


		if (sqlca.sqlcode == 0) {
			oSVMWeight[vSVid][vVarId] = vWeight;
		} else if (sqlca.sqlcode == 1403) {
			break;
		} else {
			LogWrite(DebugParms, LOG_ERROR, "%s(): SQL Error %d\n", 2, __func__, sqlca.sqlcode);
			retval = sqlca.sqlcode;
			break;
		}
	}
	/* EXEC SQL CLOSE cLISVM; */ 

{
 struct sqlexd sqlstm;
 sqlstm.sqlvsn = 13;
 sqlstm.arrsiz = 11;
 sqlstm.sqladtp = &sqladt;
 sqlstm.sqltdsp = &sqltds;
 sqlstm.iters = (unsigned int  )1;
 sqlstm.offset = (unsigned int  )1936;
 sqlstm.cud = sqlcud0;
 sqlstm.sqlest = (unsigned char  *)&sqlca;
 sqlstm.sqlety = (unsigned short)4352;
 sqlstm.occurs = (unsigned int  )0;
 sqlcxt(&vCtx, &sqlctx, &sqlstm, &sqlfpn);
}



	return retval;
}

//-- Save Core Image(s)
EXPORT int Ora_InsertCoreImage_NN(tDebugInfo* DebugParms, tDBConnection* DBConnInfo, int pid, int tid, int levelsCnt, int* nodesCnt, int Wtotalcnt, double*** NNWeight) {
	/* EXEC SQL BEGIN DECLARE SECTION; */ 

	int i, l, fn, tn;
	sql_context vCtx =DBConnInfo->DBCtx;
	char stmt[1000];
	int vInsertCount = Wtotalcnt;
	int* vProcessId;
	int* vThreadId;
	int* vNeuronLevel;
	int* vFromNeuron;
	int* vToNeuron;
	double* vWeight;
	int dbl_type = 22;	// Oracle SQLT_BDOUBLE
	int int_type = 3;	// 
	unsigned int dbl_len = sizeof(double);
	/* EXEC SQL END DECLARE SECTION; */ 


	//-- Connects to DB only once
	if (vCtx == NULL) {
		if (OraConnect(DebugParms,DBConnInfo) != 0) LogWrite(DebugParms, LOG_ERROR, "%s() could not connect to Log Database...\n", 1, __func__);
		vCtx =DBConnInfo->DBCtx;
	}

	vProcessId = (int*)malloc(vInsertCount * sizeof(int));
	vThreadId = (int*)malloc(vInsertCount * sizeof(int));
	vNeuronLevel = (int*)malloc(vInsertCount * sizeof(int));
	vFromNeuron = (int*)malloc(vInsertCount * sizeof(int));
	vToNeuron = (int*)malloc(vInsertCount * sizeof(int));
	vWeight = (double*)malloc(vInsertCount * sizeof(double));

	i = 0;
	for (l = 0; l < (levelsCnt-1); l++) {
		for (fn = 0; fn < nodesCnt[l]; fn++) {
			for (tn = 0; tn < nodesCnt[l+1]; tn++) {
				vProcessId[i] = pid;
				vThreadId[i] = tid;
				vNeuronLevel[i] = l;
				vFromNeuron[i] = fn;
				vToNeuron[i] = tn;
				vWeight[i] = NNWeight[l][fn][tn];
				i++;
			}
		}
	}
	//-- Then, Build the Insert statement
	sprintf(&stmt[0], "insert into CoreImage_NN (ProcessId, ThreadId, NeuronLevel, FromNeuron, ToNeuron, Weight, CtxValue)");
	strcat(stmt, " values(:WNN01, :WNN02, :WNN03, :WNN04, :WNN05, :WNN06, :WNN07)");

	/* EXEC SQL CONTEXT USE : vCtx; */ 

	/* EXEC SQL FOR : vInsertCount ALLOCATE DESCRIPTOR 'WNN'; */ 

{
 struct sqlexd sqlstm;
 sqlstm.sqlvsn = 13;
 sqlstm.arrsiz = 11;
 sqlstm.sqladtp = &sqladt;
 sqlstm.sqltdsp = &sqltds;
 sqlstm.stmt = "";
 sqlstm.iters = (unsigned int  )vInsertCount;
 sqlstm.offset = (unsigned int  )1951;
 sqlstm.cud = sqlcud0;
 sqlstm.sqlest = (unsigned char  *)&sqlca;
 sqlstm.sqlety = (unsigned short)4352;
 sqlstm.occurs = (unsigned int  )100;
 sqlcxt(&vCtx, &sqlctx, &sqlstm, &sqlfpn);
}


	/* EXEC SQL SET DESCRIPTOR 'WNN' COUNT = 6; */ 

{
 struct sqlexd sqlstm;
 sqlstm.sqlvsn = 13;
 sqlstm.arrsiz = 11;
 sqlstm.sqladtp = &sqladt;
 sqlstm.sqltdsp = &sqltds;
 sqlstm.stmt = "";
 sqlstm.iters = (unsigned int  )1;
 sqlstm.offset = (unsigned int  )1969;
 sqlstm.cud = sqlcud0;
 sqlstm.sqlest = (unsigned char  *)&sqlca;
 sqlstm.sqlety = (unsigned short)4352;
 sqlstm.occurs = (unsigned int  )6;
 sqlcxt(&vCtx, &sqlctx, &sqlstm, &sqlfpn);
}


	/* EXEC SQL SET DESCRIPTOR 'WNN' VALUE 1 TYPE = :int_type; */ 

{
 struct sqlexd sqlstm;
 sqlstm.sqlvsn = 13;
 sqlstm.arrsiz = 11;
 sqlstm.sqladtp = &sqladt;
 sqlstm.sqltdsp = &sqltds;
 sqlstm.stmt = "";
 sqlstm.iters = (unsigned int  )1;
 sqlstm.offset = (unsigned int  )1987;
 sqlstm.cud = sqlcud0;
 sqlstm.sqlest = (unsigned char  *)&sqlca;
 sqlstm.sqlety = (unsigned short)4352;
 sqlstm.occurs = (unsigned int  )1;
 sqlstm.sqhstv[0] = (         void  *)&int_type;
 sqlstm.sqhstl[0] = (unsigned int  )sizeof(int);
 sqlstm.sqhsts[0] = (         int  )0;
 sqlstm.sqindv[0] = (         void  *)0;
 sqlstm.sqinds[0] = (         int  )0;
 sqlstm.sqharm[0] = (unsigned int  )0;
 sqlstm.sqadto[0] = (unsigned short )0;
 sqlstm.sqtdso[0] = (unsigned short )0;
 sqlstm.sqphsv = sqlstm.sqhstv;
 sqlstm.sqphsl = sqlstm.sqhstl;
 sqlstm.sqphss = sqlstm.sqhsts;
 sqlstm.sqpind = sqlstm.sqindv;
 sqlstm.sqpins = sqlstm.sqinds;
 sqlstm.sqparm = sqlstm.sqharm;
 sqlstm.sqparc = sqlstm.sqharc;
 sqlstm.sqpadto = sqlstm.sqadto;
 sqlstm.sqptdso = sqlstm.sqtdso;
 sqlcxt(&vCtx, &sqlctx, &sqlstm, &sqlfpn);
}


	/* EXEC SQL SET DESCRIPTOR 'WNN' VALUE 2 TYPE = :int_type; */ 

{
 struct sqlexd sqlstm;
 sqlstm.sqlvsn = 13;
 sqlstm.arrsiz = 11;
 sqlstm.sqladtp = &sqladt;
 sqlstm.sqltdsp = &sqltds;
 sqlstm.stmt = "";
 sqlstm.iters = (unsigned int  )1;
 sqlstm.offset = (unsigned int  )2009;
 sqlstm.cud = sqlcud0;
 sqlstm.sqlest = (unsigned char  *)&sqlca;
 sqlstm.sqlety = (unsigned short)4352;
 sqlstm.occurs = (unsigned int  )2;
 sqlstm.sqhstv[0] = (         void  *)&int_type;
 sqlstm.sqhstl[0] = (unsigned int  )sizeof(int);
 sqlstm.sqhsts[0] = (         int  )0;
 sqlstm.sqindv[0] = (         void  *)0;
 sqlstm.sqinds[0] = (         int  )0;
 sqlstm.sqharm[0] = (unsigned int  )0;
 sqlstm.sqadto[0] = (unsigned short )0;
 sqlstm.sqtdso[0] = (unsigned short )0;
 sqlstm.sqphsv = sqlstm.sqhstv;
 sqlstm.sqphsl = sqlstm.sqhstl;
 sqlstm.sqphss = sqlstm.sqhsts;
 sqlstm.sqpind = sqlstm.sqindv;
 sqlstm.sqpins = sqlstm.sqinds;
 sqlstm.sqparm = sqlstm.sqharm;
 sqlstm.sqparc = sqlstm.sqharc;
 sqlstm.sqpadto = sqlstm.sqadto;
 sqlstm.sqptdso = sqlstm.sqtdso;
 sqlcxt(&vCtx, &sqlctx, &sqlstm, &sqlfpn);
}


	/* EXEC SQL SET DESCRIPTOR 'WNN' VALUE 3 TYPE = :int_type; */ 

{
 struct sqlexd sqlstm;
 sqlstm.sqlvsn = 13;
 sqlstm.arrsiz = 11;
 sqlstm.sqladtp = &sqladt;
 sqlstm.sqltdsp = &sqltds;
 sqlstm.stmt = "";
 sqlstm.iters = (unsigned int  )1;
 sqlstm.offset = (unsigned int  )2031;
 sqlstm.cud = sqlcud0;
 sqlstm.sqlest = (unsigned char  *)&sqlca;
 sqlstm.sqlety = (unsigned short)4352;
 sqlstm.occurs = (unsigned int  )3;
 sqlstm.sqhstv[0] = (         void  *)&int_type;
 sqlstm.sqhstl[0] = (unsigned int  )sizeof(int);
 sqlstm.sqhsts[0] = (         int  )0;
 sqlstm.sqindv[0] = (         void  *)0;
 sqlstm.sqinds[0] = (         int  )0;
 sqlstm.sqharm[0] = (unsigned int  )0;
 sqlstm.sqadto[0] = (unsigned short )0;
 sqlstm.sqtdso[0] = (unsigned short )0;
 sqlstm.sqphsv = sqlstm.sqhstv;
 sqlstm.sqphsl = sqlstm.sqhstl;
 sqlstm.sqphss = sqlstm.sqhsts;
 sqlstm.sqpind = sqlstm.sqindv;
 sqlstm.sqpins = sqlstm.sqinds;
 sqlstm.sqparm = sqlstm.sqharm;
 sqlstm.sqparc = sqlstm.sqharc;
 sqlstm.sqpadto = sqlstm.sqadto;
 sqlstm.sqptdso = sqlstm.sqtdso;
 sqlcxt(&vCtx, &sqlctx, &sqlstm, &sqlfpn);
}


	/* EXEC SQL SET DESCRIPTOR 'WNN' VALUE 4 TYPE = :int_type; */ 

{
 struct sqlexd sqlstm;
 sqlstm.sqlvsn = 13;
 sqlstm.arrsiz = 11;
 sqlstm.sqladtp = &sqladt;
 sqlstm.sqltdsp = &sqltds;
 sqlstm.stmt = "";
 sqlstm.iters = (unsigned int  )1;
 sqlstm.offset = (unsigned int  )2053;
 sqlstm.cud = sqlcud0;
 sqlstm.sqlest = (unsigned char  *)&sqlca;
 sqlstm.sqlety = (unsigned short)4352;
 sqlstm.occurs = (unsigned int  )4;
 sqlstm.sqhstv[0] = (         void  *)&int_type;
 sqlstm.sqhstl[0] = (unsigned int  )sizeof(int);
 sqlstm.sqhsts[0] = (         int  )0;
 sqlstm.sqindv[0] = (         void  *)0;
 sqlstm.sqinds[0] = (         int  )0;
 sqlstm.sqharm[0] = (unsigned int  )0;
 sqlstm.sqadto[0] = (unsigned short )0;
 sqlstm.sqtdso[0] = (unsigned short )0;
 sqlstm.sqphsv = sqlstm.sqhstv;
 sqlstm.sqphsl = sqlstm.sqhstl;
 sqlstm.sqphss = sqlstm.sqhsts;
 sqlstm.sqpind = sqlstm.sqindv;
 sqlstm.sqpins = sqlstm.sqinds;
 sqlstm.sqparm = sqlstm.sqharm;
 sqlstm.sqparc = sqlstm.sqharc;
 sqlstm.sqpadto = sqlstm.sqadto;
 sqlstm.sqptdso = sqlstm.sqtdso;
 sqlcxt(&vCtx, &sqlctx, &sqlstm, &sqlfpn);
}


	/* EXEC SQL SET DESCRIPTOR 'WNN' VALUE 5 TYPE = :int_type; */ 

{
 struct sqlexd sqlstm;
 sqlstm.sqlvsn = 13;
 sqlstm.arrsiz = 11;
 sqlstm.sqladtp = &sqladt;
 sqlstm.sqltdsp = &sqltds;
 sqlstm.stmt = "";
 sqlstm.iters = (unsigned int  )1;
 sqlstm.offset = (unsigned int  )2075;
 sqlstm.cud = sqlcud0;
 sqlstm.sqlest = (unsigned char  *)&sqlca;
 sqlstm.sqlety = (unsigned short)4352;
 sqlstm.occurs = (unsigned int  )5;
 sqlstm.sqhstv[0] = (         void  *)&int_type;
 sqlstm.sqhstl[0] = (unsigned int  )sizeof(int);
 sqlstm.sqhsts[0] = (         int  )0;
 sqlstm.sqindv[0] = (         void  *)0;
 sqlstm.sqinds[0] = (         int  )0;
 sqlstm.sqharm[0] = (unsigned int  )0;
 sqlstm.sqadto[0] = (unsigned short )0;
 sqlstm.sqtdso[0] = (unsigned short )0;
 sqlstm.sqphsv = sqlstm.sqhstv;
 sqlstm.sqphsl = sqlstm.sqhstl;
 sqlstm.sqphss = sqlstm.sqhsts;
 sqlstm.sqpind = sqlstm.sqindv;
 sqlstm.sqpins = sqlstm.sqinds;
 sqlstm.sqparm = sqlstm.sqharm;
 sqlstm.sqparc = sqlstm.sqharc;
 sqlstm.sqpadto = sqlstm.sqadto;
 sqlstm.sqptdso = sqlstm.sqtdso;
 sqlcxt(&vCtx, &sqlctx, &sqlstm, &sqlfpn);
}


	/* EXEC SQL SET DESCRIPTOR 'WNN' VALUE 6 TYPE = :dbl_type; */ 

{
 struct sqlexd sqlstm;
 sqlstm.sqlvsn = 13;
 sqlstm.arrsiz = 11;
 sqlstm.sqladtp = &sqladt;
 sqlstm.sqltdsp = &sqltds;
 sqlstm.stmt = "";
 sqlstm.iters = (unsigned int  )1;
 sqlstm.offset = (unsigned int  )2097;
 sqlstm.cud = sqlcud0;
 sqlstm.sqlest = (unsigned char  *)&sqlca;
 sqlstm.sqlety = (unsigned short)4352;
 sqlstm.occurs = (unsigned int  )6;
 sqlstm.sqhstv[0] = (         void  *)&dbl_type;
 sqlstm.sqhstl[0] = (unsigned int  )sizeof(int);
 sqlstm.sqhsts[0] = (         int  )0;
 sqlstm.sqindv[0] = (         void  *)0;
 sqlstm.sqinds[0] = (         int  )0;
 sqlstm.sqharm[0] = (unsigned int  )0;
 sqlstm.sqadto[0] = (unsigned short )0;
 sqlstm.sqtdso[0] = (unsigned short )0;
 sqlstm.sqphsv = sqlstm.sqhstv;
 sqlstm.sqphsl = sqlstm.sqhstl;
 sqlstm.sqphss = sqlstm.sqhsts;
 sqlstm.sqpind = sqlstm.sqindv;
 sqlstm.sqpins = sqlstm.sqinds;
 sqlstm.sqparm = sqlstm.sqharm;
 sqlstm.sqparc = sqlstm.sqharc;
 sqlstm.sqpadto = sqlstm.sqadto;
 sqlstm.sqptdso = sqlstm.sqtdso;
 sqlcxt(&vCtx, &sqlctx, &sqlstm, &sqlfpn);
}



	/* EXEC SQL FOR : vInsertCount SET DESCRIPTOR 'WNN' VALUE 1 DATA = : vProcessId; */ 

{
 struct sqlexd sqlstm;
 sqlstm.sqlvsn = 13;
 sqlstm.arrsiz = 11;
 sqlstm.sqladtp = &sqladt;
 sqlstm.sqltdsp = &sqltds;
 sqlstm.stmt = "";
 sqlstm.iters = (unsigned int  )vInsertCount;
 sqlstm.offset = (unsigned int  )2119;
 sqlstm.cud = sqlcud0;
 sqlstm.sqlest = (unsigned char  *)&sqlca;
 sqlstm.sqlety = (unsigned short)4352;
 sqlstm.occurs = (unsigned int  )1;
 sqlstm.sqhstv[0] = (         void  *)vProcessId;
 sqlstm.sqhstl[0] = (unsigned int  )sizeof(int);
 sqlstm.sqhsts[0] = (         int  )sizeof(int);
 sqlstm.sqindv[0] = (         void  *)0;
 sqlstm.sqinds[0] = (         int  )0;
 sqlstm.sqharm[0] = (unsigned int  )0;
 sqlstm.sqadto[0] = (unsigned short )0;
 sqlstm.sqtdso[0] = (unsigned short )0;
 sqlstm.sqphsv = sqlstm.sqhstv;
 sqlstm.sqphsl = sqlstm.sqhstl;
 sqlstm.sqphss = sqlstm.sqhsts;
 sqlstm.sqpind = sqlstm.sqindv;
 sqlstm.sqpins = sqlstm.sqinds;
 sqlstm.sqparm = sqlstm.sqharm;
 sqlstm.sqparc = sqlstm.sqharc;
 sqlstm.sqpadto = sqlstm.sqadto;
 sqlstm.sqptdso = sqlstm.sqtdso;
 sqlcxt(&vCtx, &sqlctx, &sqlstm, &sqlfpn);
}


	/* EXEC SQL FOR : vInsertCount SET DESCRIPTOR 'WNN' VALUE 2 DATA = : vThreadId; */ 

{
 struct sqlexd sqlstm;
 sqlstm.sqlvsn = 13;
 sqlstm.arrsiz = 11;
 sqlstm.sqladtp = &sqladt;
 sqlstm.sqltdsp = &sqltds;
 sqlstm.stmt = "";
 sqlstm.iters = (unsigned int  )vInsertCount;
 sqlstm.offset = (unsigned int  )2141;
 sqlstm.cud = sqlcud0;
 sqlstm.sqlest = (unsigned char  *)&sqlca;
 sqlstm.sqlety = (unsigned short)4352;
 sqlstm.occurs = (unsigned int  )2;
 sqlstm.sqhstv[0] = (         void  *)vThreadId;
 sqlstm.sqhstl[0] = (unsigned int  )sizeof(int);
 sqlstm.sqhsts[0] = (         int  )sizeof(int);
 sqlstm.sqindv[0] = (         void  *)0;
 sqlstm.sqinds[0] = (         int  )0;
 sqlstm.sqharm[0] = (unsigned int  )0;
 sqlstm.sqadto[0] = (unsigned short )0;
 sqlstm.sqtdso[0] = (unsigned short )0;
 sqlstm.sqphsv = sqlstm.sqhstv;
 sqlstm.sqphsl = sqlstm.sqhstl;
 sqlstm.sqphss = sqlstm.sqhsts;
 sqlstm.sqpind = sqlstm.sqindv;
 sqlstm.sqpins = sqlstm.sqinds;
 sqlstm.sqparm = sqlstm.sqharm;
 sqlstm.sqparc = sqlstm.sqharc;
 sqlstm.sqpadto = sqlstm.sqadto;
 sqlstm.sqptdso = sqlstm.sqtdso;
 sqlcxt(&vCtx, &sqlctx, &sqlstm, &sqlfpn);
}


	/* EXEC SQL FOR : vInsertCount SET DESCRIPTOR 'WNN' VALUE 3 DATA = : vNeuronLevel; */ 

{
 struct sqlexd sqlstm;
 sqlstm.sqlvsn = 13;
 sqlstm.arrsiz = 11;
 sqlstm.sqladtp = &sqladt;
 sqlstm.sqltdsp = &sqltds;
 sqlstm.stmt = "";
 sqlstm.iters = (unsigned int  )vInsertCount;
 sqlstm.offset = (unsigned int  )2163;
 sqlstm.cud = sqlcud0;
 sqlstm.sqlest = (unsigned char  *)&sqlca;
 sqlstm.sqlety = (unsigned short)4352;
 sqlstm.occurs = (unsigned int  )3;
 sqlstm.sqhstv[0] = (         void  *)vNeuronLevel;
 sqlstm.sqhstl[0] = (unsigned int  )sizeof(int);
 sqlstm.sqhsts[0] = (         int  )sizeof(int);
 sqlstm.sqindv[0] = (         void  *)0;
 sqlstm.sqinds[0] = (         int  )0;
 sqlstm.sqharm[0] = (unsigned int  )0;
 sqlstm.sqadto[0] = (unsigned short )0;
 sqlstm.sqtdso[0] = (unsigned short )0;
 sqlstm.sqphsv = sqlstm.sqhstv;
 sqlstm.sqphsl = sqlstm.sqhstl;
 sqlstm.sqphss = sqlstm.sqhsts;
 sqlstm.sqpind = sqlstm.sqindv;
 sqlstm.sqpins = sqlstm.sqinds;
 sqlstm.sqparm = sqlstm.sqharm;
 sqlstm.sqparc = sqlstm.sqharc;
 sqlstm.sqpadto = sqlstm.sqadto;
 sqlstm.sqptdso = sqlstm.sqtdso;
 sqlcxt(&vCtx, &sqlctx, &sqlstm, &sqlfpn);
}


	/* EXEC SQL FOR : vInsertCount SET DESCRIPTOR 'WNN' VALUE 4 DATA = : vFromNeuron; */ 

{
 struct sqlexd sqlstm;
 sqlstm.sqlvsn = 13;
 sqlstm.arrsiz = 11;
 sqlstm.sqladtp = &sqladt;
 sqlstm.sqltdsp = &sqltds;
 sqlstm.stmt = "";
 sqlstm.iters = (unsigned int  )vInsertCount;
 sqlstm.offset = (unsigned int  )2185;
 sqlstm.cud = sqlcud0;
 sqlstm.sqlest = (unsigned char  *)&sqlca;
 sqlstm.sqlety = (unsigned short)4352;
 sqlstm.occurs = (unsigned int  )4;
 sqlstm.sqhstv[0] = (         void  *)vFromNeuron;
 sqlstm.sqhstl[0] = (unsigned int  )sizeof(int);
 sqlstm.sqhsts[0] = (         int  )sizeof(int);
 sqlstm.sqindv[0] = (         void  *)0;
 sqlstm.sqinds[0] = (         int  )0;
 sqlstm.sqharm[0] = (unsigned int  )0;
 sqlstm.sqadto[0] = (unsigned short )0;
 sqlstm.sqtdso[0] = (unsigned short )0;
 sqlstm.sqphsv = sqlstm.sqhstv;
 sqlstm.sqphsl = sqlstm.sqhstl;
 sqlstm.sqphss = sqlstm.sqhsts;
 sqlstm.sqpind = sqlstm.sqindv;
 sqlstm.sqpins = sqlstm.sqinds;
 sqlstm.sqparm = sqlstm.sqharm;
 sqlstm.sqparc = sqlstm.sqharc;
 sqlstm.sqpadto = sqlstm.sqadto;
 sqlstm.sqptdso = sqlstm.sqtdso;
 sqlcxt(&vCtx, &sqlctx, &sqlstm, &sqlfpn);
}


	/* EXEC SQL FOR : vInsertCount SET DESCRIPTOR 'WNN' VALUE 5 DATA = : vToNeuron; */ 

{
 struct sqlexd sqlstm;
 sqlstm.sqlvsn = 13;
 sqlstm.arrsiz = 11;
 sqlstm.sqladtp = &sqladt;
 sqlstm.sqltdsp = &sqltds;
 sqlstm.stmt = "";
 sqlstm.iters = (unsigned int  )vInsertCount;
 sqlstm.offset = (unsigned int  )2207;
 sqlstm.cud = sqlcud0;
 sqlstm.sqlest = (unsigned char  *)&sqlca;
 sqlstm.sqlety = (unsigned short)4352;
 sqlstm.occurs = (unsigned int  )5;
 sqlstm.sqhstv[0] = (         void  *)vToNeuron;
 sqlstm.sqhstl[0] = (unsigned int  )sizeof(int);
 sqlstm.sqhsts[0] = (         int  )sizeof(int);
 sqlstm.sqindv[0] = (         void  *)0;
 sqlstm.sqinds[0] = (         int  )0;
 sqlstm.sqharm[0] = (unsigned int  )0;
 sqlstm.sqadto[0] = (unsigned short )0;
 sqlstm.sqtdso[0] = (unsigned short )0;
 sqlstm.sqphsv = sqlstm.sqhstv;
 sqlstm.sqphsl = sqlstm.sqhstl;
 sqlstm.sqphss = sqlstm.sqhsts;
 sqlstm.sqpind = sqlstm.sqindv;
 sqlstm.sqpins = sqlstm.sqinds;
 sqlstm.sqparm = sqlstm.sqharm;
 sqlstm.sqparc = sqlstm.sqharc;
 sqlstm.sqpadto = sqlstm.sqadto;
 sqlstm.sqptdso = sqlstm.sqtdso;
 sqlcxt(&vCtx, &sqlctx, &sqlstm, &sqlfpn);
}


	/* EXEC SQL FOR : vInsertCount SET DESCRIPTOR 'WNN' VALUE 6 DATA = : vWeight; */ 

{
 struct sqlexd sqlstm;
 sqlstm.sqlvsn = 13;
 sqlstm.arrsiz = 11;
 sqlstm.sqladtp = &sqladt;
 sqlstm.sqltdsp = &sqltds;
 sqlstm.stmt = "";
 sqlstm.iters = (unsigned int  )vInsertCount;
 sqlstm.offset = (unsigned int  )2229;
 sqlstm.cud = sqlcud0;
 sqlstm.sqlest = (unsigned char  *)&sqlca;
 sqlstm.sqlety = (unsigned short)4352;
 sqlstm.occurs = (unsigned int  )6;
 sqlstm.sqhstv[0] = (         void  *)vWeight;
 sqlstm.sqhstl[0] = (unsigned int  )sizeof(double);
 sqlstm.sqhsts[0] = (         int  )sizeof(double);
 sqlstm.sqindv[0] = (         void  *)0;
 sqlstm.sqinds[0] = (         int  )0;
 sqlstm.sqharm[0] = (unsigned int  )0;
 sqlstm.sqadto[0] = (unsigned short )0;
 sqlstm.sqtdso[0] = (unsigned short )0;
 sqlstm.sqphsv = sqlstm.sqhstv;
 sqlstm.sqphsl = sqlstm.sqhstl;
 sqlstm.sqphss = sqlstm.sqhsts;
 sqlstm.sqpind = sqlstm.sqindv;
 sqlstm.sqpins = sqlstm.sqinds;
 sqlstm.sqparm = sqlstm.sqharm;
 sqlstm.sqparc = sqlstm.sqharc;
 sqlstm.sqpadto = sqlstm.sqadto;
 sqlstm.sqptdso = sqlstm.sqtdso;
 sqlcxt(&vCtx, &sqlctx, &sqlstm, &sqlfpn);
}



	/* EXEC SQL PREPARE DynWNNs FROM : stmt; */ 

{
 struct sqlexd sqlstm;
 sqlstm.sqlvsn = 13;
 sqlstm.arrsiz = 11;
 sqlstm.sqladtp = &sqladt;
 sqlstm.sqltdsp = &sqltds;
 sqlstm.stmt = "";
 sqlstm.iters = (unsigned int  )1;
 sqlstm.offset = (unsigned int  )2251;
 sqlstm.cud = sqlcud0;
 sqlstm.sqlest = (unsigned char  *)&sqlca;
 sqlstm.sqlety = (unsigned short)4352;
 sqlstm.occurs = (unsigned int  )0;
 sqlstm.sqhstv[0] = (         void  *)stmt;
 sqlstm.sqhstl[0] = (unsigned int  )1000;
 sqlstm.sqhsts[0] = (         int  )0;
 sqlstm.sqindv[0] = (         void  *)0;
 sqlstm.sqinds[0] = (         int  )0;
 sqlstm.sqharm[0] = (unsigned int  )0;
 sqlstm.sqadto[0] = (unsigned short )0;
 sqlstm.sqtdso[0] = (unsigned short )0;
 sqlstm.sqphsv = sqlstm.sqhstv;
 sqlstm.sqphsl = sqlstm.sqhstl;
 sqlstm.sqphss = sqlstm.sqhsts;
 sqlstm.sqpind = sqlstm.sqindv;
 sqlstm.sqpins = sqlstm.sqinds;
 sqlstm.sqparm = sqlstm.sqharm;
 sqlstm.sqparc = sqlstm.sqharc;
 sqlstm.sqpadto = sqlstm.sqadto;
 sqlstm.sqptdso = sqlstm.sqtdso;
 sqlcxt(&vCtx, &sqlctx, &sqlstm, &sqlfpn);
}


	/* EXEC SQL FOR : vInsertCount EXECUTE DynWNNs USING DESCRIPTOR 'WNN'; */ 

{
 struct sqlexd sqlstm;
 sqlstm.sqlvsn = 13;
 sqlstm.arrsiz = 11;
 sqlstm.sqladtp = &sqladt;
 sqlstm.sqltdsp = &sqltds;
 sqlstm.stmt = "";
 sqlstm.iters = (unsigned int  )vInsertCount;
 sqlstm.offset = (unsigned int  )2270;
 sqlstm.cud = sqlcud0;
 sqlstm.sqlest = (unsigned char  *)&sqlca;
 sqlstm.sqlety = (unsigned short)4352;
 sqlstm.occurs = (unsigned int  )0;
 sqlcxt(&vCtx, &sqlctx, &sqlstm, &sqlfpn);
}



	if (sqlca.sqlcode != 0) {
		LogWrite(DebugParms, LOG_ERROR, "%s() failed. SQL Error %d\n", 2, __func__, sqlca.sqlcode);
		return sqlca.sqlcode;
	}
	/* EXEC SQL DEALLOCATE DESCRIPTOR 'WNN'; */ 

{
 struct sqlexd sqlstm;
 sqlstm.sqlvsn = 13;
 sqlstm.arrsiz = 11;
 sqlstm.sqladtp = &sqladt;
 sqlstm.sqltdsp = &sqltds;
 sqlstm.stmt = "";
 sqlstm.iters = (unsigned int  )1;
 sqlstm.offset = (unsigned int  )2288;
 sqlstm.cud = sqlcud0;
 sqlstm.sqlest = (unsigned char  *)&sqlca;
 sqlstm.sqlety = (unsigned short)4352;
 sqlstm.occurs = (unsigned int  )0;
 sqlcxt(&vCtx, &sqlctx, &sqlstm, &sqlfpn);
}




	//-- free()s
	free(vProcessId);
	free(vThreadId);
	free(vNeuronLevel);
	free(vFromNeuron);
	free(vToNeuron);
	free(vWeight);

	return 0;
}

//-- Queries
EXPORT int SymbolLookup(tDebugInfo* DebugParms, tDBConnection* DBConnInfo, sql_context pCtx, char* pSymbol, char* oSymbol, int* oScale) {

	/* EXEC SQL BEGIN DECLARE SECTION; */ 

	sql_context vCtx = pCtx;
	char* SymLkp_stmt_base;
	char SymLkp_stmt[300];
	char vSymbol[10];
	char* pScale_stmt_base;
	char  pScale_stmt[300];
	int vpScale;
	/* EXEC SQL END DECLARE SECTION; */ 


	SymLkp_stmt_base = "select Hst_Symbol from History.Symbol_Lookup where MT4_Symbol='";
	strcpy(SymLkp_stmt, SymLkp_stmt_base);
	strcat(SymLkp_stmt, pSymbol);
	strcat(SymLkp_stmt, "'");
	LogWrite(DebugParms, LOG_INFO, "%s SymbolLookup executing: %s\n", 2, timestamp(), SymLkp_stmt);
	//EXEC SQL ALTER SESSION SET SQL_TRACE=TRUE;
	/* EXEC SQL CONTEXT USE : vCtx; */ 

	/* EXEC SQL PREPARE s5 FROM : SymLkp_stmt; */ 

{
 struct sqlexd sqlstm;
 sqlstm.sqlvsn = 13;
 sqlstm.arrsiz = 11;
 sqlstm.sqladtp = &sqladt;
 sqlstm.sqltdsp = &sqltds;
 sqlstm.stmt = "";
 sqlstm.iters = (unsigned int  )1;
 sqlstm.offset = (unsigned int  )2306;
 sqlstm.cud = sqlcud0;
 sqlstm.sqlest = (unsigned char  *)&sqlca;
 sqlstm.sqlety = (unsigned short)4352;
 sqlstm.occurs = (unsigned int  )0;
 sqlstm.sqhstv[0] = (         void  *)SymLkp_stmt;
 sqlstm.sqhstl[0] = (unsigned int  )300;
 sqlstm.sqhsts[0] = (         int  )0;
 sqlstm.sqindv[0] = (         void  *)0;
 sqlstm.sqinds[0] = (         int  )0;
 sqlstm.sqharm[0] = (unsigned int  )0;
 sqlstm.sqadto[0] = (unsigned short )0;
 sqlstm.sqtdso[0] = (unsigned short )0;
 sqlstm.sqphsv = sqlstm.sqhstv;
 sqlstm.sqphsl = sqlstm.sqhstl;
 sqlstm.sqphss = sqlstm.sqhsts;
 sqlstm.sqpind = sqlstm.sqindv;
 sqlstm.sqpins = sqlstm.sqinds;
 sqlstm.sqparm = sqlstm.sqharm;
 sqlstm.sqparc = sqlstm.sqharc;
 sqlstm.sqpadto = sqlstm.sqadto;
 sqlstm.sqptdso = sqlstm.sqtdso;
 sqlcxt(&vCtx, &sqlctx, &sqlstm, &sqlfpn);
}


	/* EXEC SQL DECLARE c5 CURSOR FOR s5; */ 

	/* EXEC SQL OPEN c5; */ 

{
 struct sqlexd sqlstm;
 sqlstm.sqlvsn = 13;
 sqlstm.arrsiz = 11;
 sqlstm.sqladtp = &sqladt;
 sqlstm.sqltdsp = &sqltds;
 sqlstm.stmt = "";
 sqlstm.iters = (unsigned int  )1;
 sqlstm.offset = (unsigned int  )2325;
 sqlstm.selerr = (unsigned short)1;
 sqlstm.sqlpfmem = (unsigned int  )0;
 sqlstm.cud = sqlcud0;
 sqlstm.sqlest = (unsigned char  *)&sqlca;
 sqlstm.sqlety = (unsigned short)4352;
 sqlstm.occurs = (unsigned int  )0;
 sqlstm.sqcmod = (unsigned int )0;
 sqlcxt(&vCtx, &sqlctx, &sqlstm, &sqlfpn);
}


	/* EXEC SQL FETCH c5 INTO : vSymbol; */ 

{
 struct sqlexd sqlstm;
 sqlstm.sqlvsn = 13;
 sqlstm.arrsiz = 11;
 sqlstm.sqladtp = &sqladt;
 sqlstm.sqltdsp = &sqltds;
 sqlstm.iters = (unsigned int  )1;
 sqlstm.offset = (unsigned int  )2340;
 sqlstm.selerr = (unsigned short)1;
 sqlstm.sqlpfmem = (unsigned int  )0;
 sqlstm.cud = sqlcud0;
 sqlstm.sqlest = (unsigned char  *)&sqlca;
 sqlstm.sqlety = (unsigned short)4352;
 sqlstm.occurs = (unsigned int  )0;
 sqlstm.sqfoff = (           int )0;
 sqlstm.sqfmod = (unsigned int )2;
 sqlstm.sqhstv[0] = (         void  *)vSymbol;
 sqlstm.sqhstl[0] = (unsigned int  )10;
 sqlstm.sqhsts[0] = (         int  )0;
 sqlstm.sqindv[0] = (         void  *)0;
 sqlstm.sqinds[0] = (         int  )0;
 sqlstm.sqharm[0] = (unsigned int  )0;
 sqlstm.sqadto[0] = (unsigned short )0;
 sqlstm.sqtdso[0] = (unsigned short )0;
 sqlstm.sqphsv = sqlstm.sqhstv;
 sqlstm.sqphsl = sqlstm.sqhstl;
 sqlstm.sqphss = sqlstm.sqhsts;
 sqlstm.sqpind = sqlstm.sqindv;
 sqlstm.sqpins = sqlstm.sqinds;
 sqlstm.sqparm = sqlstm.sqharm;
 sqlstm.sqparc = sqlstm.sqharc;
 sqlstm.sqpadto = sqlstm.sqadto;
 sqlstm.sqptdso = sqlstm.sqtdso;
 sqlcxt(&vCtx, &sqlctx, &sqlstm, &sqlfpn);
}


	if (sqlca.sqlcode != 0) {
		LogWrite(DebugParms, LOG_INFO, "SymbolLookup: SQL Error %d\n", 1, sqlca.sqlcode);
		return sqlca.sqlcode;
	}
	/* EXEC SQL CLOSE c5; */ 

{
 struct sqlexd sqlstm;
 sqlstm.sqlvsn = 13;
 sqlstm.arrsiz = 11;
 sqlstm.sqladtp = &sqladt;
 sqlstm.sqltdsp = &sqltds;
 sqlstm.iters = (unsigned int  )1;
 sqlstm.offset = (unsigned int  )2359;
 sqlstm.cud = sqlcud0;
 sqlstm.sqlest = (unsigned char  *)&sqlca;
 sqlstm.sqlety = (unsigned short)4352;
 sqlstm.occurs = (unsigned int  )0;
 sqlcxt(&vCtx, &sqlctx, &sqlstm, &sqlfpn);
}


	//EXEC SQL ALTER SESSION SET SQL_TRACE=FALSE;
	LogWrite(DebugParms, LOG_INFO, "%s SymbolLookup found symbol: %s\n", 2, timestamp(), vSymbol);

	// Then, Look for pScale
	pScale_stmt_base = "select pScale from GridUser.Pairs where Symbol='";
	strcpy(pScale_stmt, pScale_stmt_base);
	Trim(vSymbol); strcat(pScale_stmt, vSymbol);
	strcat(pScale_stmt, "'");
	LogWrite(DebugParms, LOG_INFO, "%s SymbolLookup executing: %s\n", 2, timestamp(), pScale_stmt);

	/* EXEC SQL PREPARE s6 FROM : pScale_stmt; */ 

{
 struct sqlexd sqlstm;
 sqlstm.sqlvsn = 13;
 sqlstm.arrsiz = 11;
 sqlstm.sqladtp = &sqladt;
 sqlstm.sqltdsp = &sqltds;
 sqlstm.stmt = "";
 sqlstm.iters = (unsigned int  )1;
 sqlstm.offset = (unsigned int  )2374;
 sqlstm.cud = sqlcud0;
 sqlstm.sqlest = (unsigned char  *)&sqlca;
 sqlstm.sqlety = (unsigned short)4352;
 sqlstm.occurs = (unsigned int  )0;
 sqlstm.sqhstv[0] = (         void  *)pScale_stmt;
 sqlstm.sqhstl[0] = (unsigned int  )300;
 sqlstm.sqhsts[0] = (         int  )0;
 sqlstm.sqindv[0] = (         void  *)0;
 sqlstm.sqinds[0] = (         int  )0;
 sqlstm.sqharm[0] = (unsigned int  )0;
 sqlstm.sqadto[0] = (unsigned short )0;
 sqlstm.sqtdso[0] = (unsigned short )0;
 sqlstm.sqphsv = sqlstm.sqhstv;
 sqlstm.sqphsl = sqlstm.sqhstl;
 sqlstm.sqphss = sqlstm.sqhsts;
 sqlstm.sqpind = sqlstm.sqindv;
 sqlstm.sqpins = sqlstm.sqinds;
 sqlstm.sqparm = sqlstm.sqharm;
 sqlstm.sqparc = sqlstm.sqharc;
 sqlstm.sqpadto = sqlstm.sqadto;
 sqlstm.sqptdso = sqlstm.sqtdso;
 sqlcxt(&vCtx, &sqlctx, &sqlstm, &sqlfpn);
}


	/* EXEC SQL DECLARE c6 CURSOR FOR s6; */ 

	/* EXEC SQL OPEN c6; */ 

{
 struct sqlexd sqlstm;
 sqlstm.sqlvsn = 13;
 sqlstm.arrsiz = 11;
 sqlstm.sqladtp = &sqladt;
 sqlstm.sqltdsp = &sqltds;
 sqlstm.stmt = "";
 sqlstm.iters = (unsigned int  )1;
 sqlstm.offset = (unsigned int  )2393;
 sqlstm.selerr = (unsigned short)1;
 sqlstm.sqlpfmem = (unsigned int  )0;
 sqlstm.cud = sqlcud0;
 sqlstm.sqlest = (unsigned char  *)&sqlca;
 sqlstm.sqlety = (unsigned short)4352;
 sqlstm.occurs = (unsigned int  )0;
 sqlstm.sqcmod = (unsigned int )0;
 sqlcxt(&vCtx, &sqlctx, &sqlstm, &sqlfpn);
}


	/* EXEC SQL FETCH c6 INTO : vpScale; */ 

{
 struct sqlexd sqlstm;
 sqlstm.sqlvsn = 13;
 sqlstm.arrsiz = 11;
 sqlstm.sqladtp = &sqladt;
 sqlstm.sqltdsp = &sqltds;
 sqlstm.iters = (unsigned int  )1;
 sqlstm.offset = (unsigned int  )2408;
 sqlstm.selerr = (unsigned short)1;
 sqlstm.sqlpfmem = (unsigned int  )0;
 sqlstm.cud = sqlcud0;
 sqlstm.sqlest = (unsigned char  *)&sqlca;
 sqlstm.sqlety = (unsigned short)4352;
 sqlstm.occurs = (unsigned int  )0;
 sqlstm.sqfoff = (           int )0;
 sqlstm.sqfmod = (unsigned int )2;
 sqlstm.sqhstv[0] = (         void  *)&vpScale;
 sqlstm.sqhstl[0] = (unsigned int  )sizeof(int);
 sqlstm.sqhsts[0] = (         int  )0;
 sqlstm.sqindv[0] = (         void  *)0;
 sqlstm.sqinds[0] = (         int  )0;
 sqlstm.sqharm[0] = (unsigned int  )0;
 sqlstm.sqadto[0] = (unsigned short )0;
 sqlstm.sqtdso[0] = (unsigned short )0;
 sqlstm.sqphsv = sqlstm.sqhstv;
 sqlstm.sqphsl = sqlstm.sqhstl;
 sqlstm.sqphss = sqlstm.sqhsts;
 sqlstm.sqpind = sqlstm.sqindv;
 sqlstm.sqpins = sqlstm.sqinds;
 sqlstm.sqparm = sqlstm.sqharm;
 sqlstm.sqparc = sqlstm.sqharc;
 sqlstm.sqpadto = sqlstm.sqadto;
 sqlstm.sqptdso = sqlstm.sqtdso;
 sqlcxt(&vCtx, &sqlctx, &sqlstm, &sqlfpn);
}


	if (sqlca.sqlcode != 0) {
		LogWrite(DebugParms, LOG_ERROR, "GetpScale: SQL Error %d\n", 1, sqlca.sqlcode);
		return sqlca.sqlcode;
	}
	/* EXEC SQL CLOSE c6; */ 

{
 struct sqlexd sqlstm;
 sqlstm.sqlvsn = 13;
 sqlstm.arrsiz = 11;
 sqlstm.sqladtp = &sqladt;
 sqlstm.sqltdsp = &sqltds;
 sqlstm.iters = (unsigned int  )1;
 sqlstm.offset = (unsigned int  )2427;
 sqlstm.cud = sqlcud0;
 sqlstm.sqlest = (unsigned char  *)&sqlca;
 sqlstm.sqlety = (unsigned short)4352;
 sqlstm.occurs = (unsigned int  )0;
 sqlcxt(&vCtx, &sqlctx, &sqlstm, &sqlfpn);
}


	LogWrite(DebugParms, LOG_INFO, "%s SymbolLookup found pScale= %d\n", 2, timestamp(), vpScale);

	Trim(vSymbol);  strcpy(oSymbol, vSymbol);
	(*oScale) = vpScale;

	return 0;
}
EXPORT int FindBestPredictor(tDebugInfo* DebugParms, tDBConnection* DBConnInfo, sql_context pCtx, char* vCSymbol, char* vHSymbol, char* vTimeFrame, int vIsFilled, char* pCurrentStart, int vTotalBars, char* vMeasure, int vOutputType, int pPredictorsCount, tPredictor* pBestPredictor) {

	/* EXEC SQL BEGIN DECLARE SECTION; */ 

	sql_context vCtx = pCtx;
	char* stmt_base;
	char stmt[400];
	char vTotalBarsBuffer[3 + 1];
	int pr_id;
	int vPredictorLen = 0;
	char vPredictorStart[12 + 1];
	char vPredictorMeasure[4 + 1];
	/* EXEC SQL END DECLARE SECTION; */ 

	LogWrite(DebugParms, LOG_INFO, "%s FindBestPredictor(%s) started.\n", 2, timestamp(), (vOutputType == FH) ? "High" : "Low");

	stmt_base = "select to_char(PredictorStart,'YYYYMMDDHH24MI'), PatternLength, ";
	strcpy(&stmt[0], stmt_base);
	strcat(&stmt[0], vMeasure);
	strcat(&stmt[0], " from TConcordance where CurrentData='");
	strcat(&stmt[0], vCSymbol);
	strcat(&stmt[0], "' and CurrentStart=to_date('");
	strcat(&stmt[0], pCurrentStart);
	strcat(&stmt[0], "','YYYYMMDDHH24MI')");
	strcat(&stmt[0], "  and TimeFrame='");
	strcat(&stmt[0], vTimeFrame);
	strcat(&stmt[0], "'  and OutputType='");
	strcat(&stmt[0], (vOutputType == 1) ? "High" : "Low");
	strcat(&stmt[0], "' and PredictorData='");
	strcat(&stmt[0], vHSymbol);
	strcat(&stmt[0], "' and ");
	strcat(&stmt[0], vMeasure);
	strcat(&stmt[0], "<1");
	strcat(&stmt[0], " and PatternLength=");
	sprintf(vTotalBarsBuffer, "%d", vTotalBars);				strcat(&stmt[0], vTotalBarsBuffer);
	strcat(&stmt[0], " order by 3 desc");
	LogWrite(DebugParms, LOG_INFO, "%s FindBestPredictor(%s)  Executing stmt=%s\n", 3, timestamp(), (vOutputType == FH) ? "High" : "Low", stmt);

	/* EXEC SQL CONTEXT USE : vCtx; */ 

	/* EXEC SQL PREPARE S FROM : stmt; */ 

{
 struct sqlexd sqlstm;
 sqlstm.sqlvsn = 13;
 sqlstm.arrsiz = 11;
 sqlstm.sqladtp = &sqladt;
 sqlstm.sqltdsp = &sqltds;
 sqlstm.stmt = "";
 sqlstm.iters = (unsigned int  )1;
 sqlstm.offset = (unsigned int  )2442;
 sqlstm.cud = sqlcud0;
 sqlstm.sqlest = (unsigned char  *)&sqlca;
 sqlstm.sqlety = (unsigned short)4352;
 sqlstm.occurs = (unsigned int  )0;
 sqlstm.sqhstv[0] = (         void  *)stmt;
 sqlstm.sqhstl[0] = (unsigned int  )400;
 sqlstm.sqhsts[0] = (         int  )0;
 sqlstm.sqindv[0] = (         void  *)0;
 sqlstm.sqinds[0] = (         int  )0;
 sqlstm.sqharm[0] = (unsigned int  )0;
 sqlstm.sqadto[0] = (unsigned short )0;
 sqlstm.sqtdso[0] = (unsigned short )0;
 sqlstm.sqphsv = sqlstm.sqhstv;
 sqlstm.sqphsl = sqlstm.sqhstl;
 sqlstm.sqphss = sqlstm.sqhsts;
 sqlstm.sqpind = sqlstm.sqindv;
 sqlstm.sqpins = sqlstm.sqinds;
 sqlstm.sqparm = sqlstm.sqharm;
 sqlstm.sqparc = sqlstm.sqharc;
 sqlstm.sqpadto = sqlstm.sqadto;
 sqlstm.sqptdso = sqlstm.sqtdso;
 sqlcxt(&vCtx, &sqlctx, &sqlstm, &sqlfpn);
}


	/* EXEC SQL DECLARE c3 CURSOR FOR S; */ 

	/* EXEC SQL OPEN c3; */ 

{
 struct sqlexd sqlstm;
 sqlstm.sqlvsn = 13;
 sqlstm.arrsiz = 11;
 sqlstm.sqladtp = &sqladt;
 sqlstm.sqltdsp = &sqltds;
 sqlstm.stmt = "";
 sqlstm.iters = (unsigned int  )1;
 sqlstm.offset = (unsigned int  )2461;
 sqlstm.selerr = (unsigned short)1;
 sqlstm.sqlpfmem = (unsigned int  )0;
 sqlstm.cud = sqlcud0;
 sqlstm.sqlest = (unsigned char  *)&sqlca;
 sqlstm.sqlety = (unsigned short)4352;
 sqlstm.occurs = (unsigned int  )0;
 sqlstm.sqcmod = (unsigned int )0;
 sqlcxt(&vCtx, &sqlctx, &sqlstm, &sqlfpn);
}


	if (sqlca.sqlcode != 0) {
		LogWrite(DebugParms, LOG_INFO, "%s FindBestPredictor: Error raised by stmt: %d\n", 2, timestamp(), sqlca.sqlcode);
		return sqlca.sqlcode;
	}
	//=========================================================================================================================================
	for (pr_id = 0; pr_id<pPredictorsCount; pr_id++) {
		/* EXEC SQL FETCH c3 INTO : vPredictorStart, : vPredictorLen, : vPredictorMeasure; */ 

{
  struct sqlexd sqlstm;
  sqlstm.sqlvsn = 13;
  sqlstm.arrsiz = 11;
  sqlstm.sqladtp = &sqladt;
  sqlstm.sqltdsp = &sqltds;
  sqlstm.iters = (unsigned int  )1;
  sqlstm.offset = (unsigned int  )2476;
  sqlstm.selerr = (unsigned short)1;
  sqlstm.sqlpfmem = (unsigned int  )0;
  sqlstm.cud = sqlcud0;
  sqlstm.sqlest = (unsigned char  *)&sqlca;
  sqlstm.sqlety = (unsigned short)4352;
  sqlstm.occurs = (unsigned int  )0;
  sqlstm.sqfoff = (           int )0;
  sqlstm.sqfmod = (unsigned int )2;
  sqlstm.sqhstv[0] = (         void  *)vPredictorStart;
  sqlstm.sqhstl[0] = (unsigned int  )13;
  sqlstm.sqhsts[0] = (         int  )0;
  sqlstm.sqindv[0] = (         void  *)0;
  sqlstm.sqinds[0] = (         int  )0;
  sqlstm.sqharm[0] = (unsigned int  )0;
  sqlstm.sqadto[0] = (unsigned short )0;
  sqlstm.sqtdso[0] = (unsigned short )0;
  sqlstm.sqhstv[1] = (         void  *)&vPredictorLen;
  sqlstm.sqhstl[1] = (unsigned int  )sizeof(int);
  sqlstm.sqhsts[1] = (         int  )0;
  sqlstm.sqindv[1] = (         void  *)0;
  sqlstm.sqinds[1] = (         int  )0;
  sqlstm.sqharm[1] = (unsigned int  )0;
  sqlstm.sqadto[1] = (unsigned short )0;
  sqlstm.sqtdso[1] = (unsigned short )0;
  sqlstm.sqhstv[2] = (         void  *)vPredictorMeasure;
  sqlstm.sqhstl[2] = (unsigned int  )5;
  sqlstm.sqhsts[2] = (         int  )0;
  sqlstm.sqindv[2] = (         void  *)0;
  sqlstm.sqinds[2] = (         int  )0;
  sqlstm.sqharm[2] = (unsigned int  )0;
  sqlstm.sqadto[2] = (unsigned short )0;
  sqlstm.sqtdso[2] = (unsigned short )0;
  sqlstm.sqphsv = sqlstm.sqhstv;
  sqlstm.sqphsl = sqlstm.sqhstl;
  sqlstm.sqphss = sqlstm.sqhsts;
  sqlstm.sqpind = sqlstm.sqindv;
  sqlstm.sqpins = sqlstm.sqinds;
  sqlstm.sqparm = sqlstm.sqharm;
  sqlstm.sqparc = sqlstm.sqharc;
  sqlstm.sqpadto = sqlstm.sqadto;
  sqlstm.sqptdso = sqlstm.sqtdso;
  sqlcxt(&vCtx, &sqlctx, &sqlstm, &sqlfpn);
}


		if (sqlca.sqlcode != 0) {
			LogWrite(DebugParms, LOG_ERROR, "%s FindBestPredictor: Error raised by stmt: %d\n", 2, timestamp(), sqlca.sqlcode);
			return sqlca.sqlcode;
		}
		pBestPredictor[pr_id].PredType = vOutputType;
		strcpy(pBestPredictor[pr_id].PredStart, vPredictorStart);
		pBestPredictor[pr_id].PredLen = vPredictorLen;
		LogWrite(DebugParms, LOG_INFO, "%s FindBestPredictor(%s) found top %d predictor. PredStart=%s \n", 4, timestamp(), (vOutputType == FH) ? "High" : "Low", pr_id, pBestPredictor[pr_id].PredStart);
	}
	/* EXEC SQL CLOSE c3; */ 

{
 struct sqlexd sqlstm;
 sqlstm.sqlvsn = 13;
 sqlstm.arrsiz = 11;
 sqlstm.sqladtp = &sqladt;
 sqlstm.sqltdsp = &sqltds;
 sqlstm.iters = (unsigned int  )1;
 sqlstm.offset = (unsigned int  )2503;
 sqlstm.cud = sqlcud0;
 sqlstm.sqlest = (unsigned char  *)&sqlca;
 sqlstm.sqlety = (unsigned short)4352;
 sqlstm.occurs = (unsigned int  )0;
 sqlcxt(&vCtx, &sqlctx, &sqlstm, &sqlfpn);
}


	return sqlca.sqlcode;

}
EXPORT int GetCharPFromQuery(tDebugInfo* DebugParms, tDBConnection* DBConnInfo, sql_context pCtx, char* pSQL, char* oRet) {
	/* EXEC SQL BEGIN DECLARE SECTION; */ 

	char vSQL[1000];
	char vRet[1000];
	sql_context vCtx = pCtx;
	/* EXEC SQL END   DECLARE SECTION; */ 

	strcpy(vSQL, pSQL);

	/* EXEC SQL CONTEXT USE : vCtx; */ 

	/* EXEC SQL PREPARE s8 FROM : vSQL; */ 

{
 struct sqlexd sqlstm;
 sqlstm.sqlvsn = 13;
 sqlstm.arrsiz = 11;
 sqlstm.sqladtp = &sqladt;
 sqlstm.sqltdsp = &sqltds;
 sqlstm.stmt = "";
 sqlstm.iters = (unsigned int  )1;
 sqlstm.offset = (unsigned int  )2518;
 sqlstm.cud = sqlcud0;
 sqlstm.sqlest = (unsigned char  *)&sqlca;
 sqlstm.sqlety = (unsigned short)4352;
 sqlstm.occurs = (unsigned int  )0;
 sqlstm.sqhstv[0] = (         void  *)vSQL;
 sqlstm.sqhstl[0] = (unsigned int  )1000;
 sqlstm.sqhsts[0] = (         int  )0;
 sqlstm.sqindv[0] = (         void  *)0;
 sqlstm.sqinds[0] = (         int  )0;
 sqlstm.sqharm[0] = (unsigned int  )0;
 sqlstm.sqadto[0] = (unsigned short )0;
 sqlstm.sqtdso[0] = (unsigned short )0;
 sqlstm.sqphsv = sqlstm.sqhstv;
 sqlstm.sqphsl = sqlstm.sqhstl;
 sqlstm.sqphss = sqlstm.sqhsts;
 sqlstm.sqpind = sqlstm.sqindv;
 sqlstm.sqpins = sqlstm.sqinds;
 sqlstm.sqparm = sqlstm.sqharm;
 sqlstm.sqparc = sqlstm.sqharc;
 sqlstm.sqpadto = sqlstm.sqadto;
 sqlstm.sqptdso = sqlstm.sqtdso;
 sqlcxt(&vCtx, &sqlctx, &sqlstm, &sqlfpn);
}


	/* EXEC SQL DECLARE c8 CURSOR FOR s8; */ 

	/* EXEC SQL OPEN c8; */ 

{
 struct sqlexd sqlstm;
 sqlstm.sqlvsn = 13;
 sqlstm.arrsiz = 11;
 sqlstm.sqladtp = &sqladt;
 sqlstm.sqltdsp = &sqltds;
 sqlstm.stmt = "";
 sqlstm.iters = (unsigned int  )1;
 sqlstm.offset = (unsigned int  )2537;
 sqlstm.selerr = (unsigned short)1;
 sqlstm.sqlpfmem = (unsigned int  )0;
 sqlstm.cud = sqlcud0;
 sqlstm.sqlest = (unsigned char  *)&sqlca;
 sqlstm.sqlety = (unsigned short)4352;
 sqlstm.occurs = (unsigned int  )0;
 sqlstm.sqcmod = (unsigned int )0;
 sqlcxt(&vCtx, &sqlctx, &sqlstm, &sqlfpn);
}


	if (sqlca.sqlcode != 0) {
		LogWrite(DebugParms, LOG_ERROR, "GetCharPFromQuery: SQL Error %d\n", 1, sqlca.sqlcode);
		return sqlca.sqlcode;
	}
	/* EXEC SQL FETCH c8 INTO : vRet; */ 

{
 struct sqlexd sqlstm;
 sqlstm.sqlvsn = 13;
 sqlstm.arrsiz = 11;
 sqlstm.sqladtp = &sqladt;
 sqlstm.sqltdsp = &sqltds;
 sqlstm.iters = (unsigned int  )1;
 sqlstm.offset = (unsigned int  )2552;
 sqlstm.selerr = (unsigned short)1;
 sqlstm.sqlpfmem = (unsigned int  )0;
 sqlstm.cud = sqlcud0;
 sqlstm.sqlest = (unsigned char  *)&sqlca;
 sqlstm.sqlety = (unsigned short)4352;
 sqlstm.occurs = (unsigned int  )0;
 sqlstm.sqfoff = (           int )0;
 sqlstm.sqfmod = (unsigned int )2;
 sqlstm.sqhstv[0] = (         void  *)vRet;
 sqlstm.sqhstl[0] = (unsigned int  )1000;
 sqlstm.sqhsts[0] = (         int  )0;
 sqlstm.sqindv[0] = (         void  *)0;
 sqlstm.sqinds[0] = (         int  )0;
 sqlstm.sqharm[0] = (unsigned int  )0;
 sqlstm.sqadto[0] = (unsigned short )0;
 sqlstm.sqtdso[0] = (unsigned short )0;
 sqlstm.sqphsv = sqlstm.sqhstv;
 sqlstm.sqphsl = sqlstm.sqhstl;
 sqlstm.sqphss = sqlstm.sqhsts;
 sqlstm.sqpind = sqlstm.sqindv;
 sqlstm.sqpins = sqlstm.sqinds;
 sqlstm.sqparm = sqlstm.sqharm;
 sqlstm.sqparc = sqlstm.sqharc;
 sqlstm.sqpadto = sqlstm.sqadto;
 sqlstm.sqptdso = sqlstm.sqtdso;
 sqlcxt(&vCtx, &sqlctx, &sqlstm, &sqlfpn);
}


	if (sqlca.sqlcode != 0) {
		LogWrite(DebugParms, LOG_ERROR, "GetCharPFromQuery: SQL Error %d\n", 1, sqlca.sqlcode);
		return sqlca.sqlcode;
	}
	Trim(vRet); strcpy(oRet, vRet);
	/* EXEC SQL CLOSE c8; */ 

{
 struct sqlexd sqlstm;
 sqlstm.sqlvsn = 13;
 sqlstm.arrsiz = 11;
 sqlstm.sqladtp = &sqladt;
 sqlstm.sqltdsp = &sqltds;
 sqlstm.iters = (unsigned int  )1;
 sqlstm.offset = (unsigned int  )2571;
 sqlstm.cud = sqlcud0;
 sqlstm.sqlest = (unsigned char  *)&sqlca;
 sqlstm.sqlety = (unsigned short)4352;
 sqlstm.occurs = (unsigned int  )0;
 sqlcxt(&vCtx, &sqlctx, &sqlstm, &sqlfpn);
}


	return sqlca.sqlcode;
}
EXPORT int GetStringArrayFromQuery(tDebugInfo* DebugParms, tDBConnection* DBConnInfo, sql_context pCtx, char* pSQL, int ArrLen, char** oRet) {
	/* EXEC SQL BEGIN DECLARE SECTION; */ 

	char vSQL[1000];
	char vRet[1000];
	sql_context vCtx = pCtx;
	/* EXEC SQL END   DECLARE SECTION; */ 

	strcpy(vSQL, pSQL);

	/* EXEC SQL CONTEXT USE : vCtx; */ 

	/* EXEC SQL PREPARE s82 FROM : vSQL; */ 

{
 struct sqlexd sqlstm;
 sqlstm.sqlvsn = 13;
 sqlstm.arrsiz = 11;
 sqlstm.sqladtp = &sqladt;
 sqlstm.sqltdsp = &sqltds;
 sqlstm.stmt = "";
 sqlstm.iters = (unsigned int  )1;
 sqlstm.offset = (unsigned int  )2586;
 sqlstm.cud = sqlcud0;
 sqlstm.sqlest = (unsigned char  *)&sqlca;
 sqlstm.sqlety = (unsigned short)4352;
 sqlstm.occurs = (unsigned int  )0;
 sqlstm.sqhstv[0] = (         void  *)vSQL;
 sqlstm.sqhstl[0] = (unsigned int  )1000;
 sqlstm.sqhsts[0] = (         int  )0;
 sqlstm.sqindv[0] = (         void  *)0;
 sqlstm.sqinds[0] = (         int  )0;
 sqlstm.sqharm[0] = (unsigned int  )0;
 sqlstm.sqadto[0] = (unsigned short )0;
 sqlstm.sqtdso[0] = (unsigned short )0;
 sqlstm.sqphsv = sqlstm.sqhstv;
 sqlstm.sqphsl = sqlstm.sqhstl;
 sqlstm.sqphss = sqlstm.sqhsts;
 sqlstm.sqpind = sqlstm.sqindv;
 sqlstm.sqpins = sqlstm.sqinds;
 sqlstm.sqparm = sqlstm.sqharm;
 sqlstm.sqparc = sqlstm.sqharc;
 sqlstm.sqpadto = sqlstm.sqadto;
 sqlstm.sqptdso = sqlstm.sqtdso;
 sqlcxt(&vCtx, &sqlctx, &sqlstm, &sqlfpn);
}


	/* EXEC SQL DECLARE c82 CURSOR FOR s82; */ 

	/* EXEC SQL OPEN c82; */ 

{
 struct sqlexd sqlstm;
 sqlstm.sqlvsn = 13;
 sqlstm.arrsiz = 11;
 sqlstm.sqladtp = &sqladt;
 sqlstm.sqltdsp = &sqltds;
 sqlstm.stmt = "";
 sqlstm.iters = (unsigned int  )1;
 sqlstm.offset = (unsigned int  )2605;
 sqlstm.selerr = (unsigned short)1;
 sqlstm.sqlpfmem = (unsigned int  )0;
 sqlstm.cud = sqlcud0;
 sqlstm.sqlest = (unsigned char  *)&sqlca;
 sqlstm.sqlety = (unsigned short)4352;
 sqlstm.occurs = (unsigned int  )0;
 sqlstm.sqcmod = (unsigned int )0;
 sqlcxt(&vCtx, &sqlctx, &sqlstm, &sqlfpn);
}


	if (sqlca.sqlcode != 0) {
		LogWrite(DebugParms, LOG_ERROR, "GetStringArrayFromQuery: SQL Error %d\n", 1, sqlca.sqlcode);
		return sqlca.sqlcode;
	}
	for (int i = 0; i<ArrLen; i++) {
		/* EXEC SQL FETCH c82 INTO : vRet; */ 

{
  struct sqlexd sqlstm;
  sqlstm.sqlvsn = 13;
  sqlstm.arrsiz = 11;
  sqlstm.sqladtp = &sqladt;
  sqlstm.sqltdsp = &sqltds;
  sqlstm.iters = (unsigned int  )1;
  sqlstm.offset = (unsigned int  )2620;
  sqlstm.selerr = (unsigned short)1;
  sqlstm.sqlpfmem = (unsigned int  )0;
  sqlstm.cud = sqlcud0;
  sqlstm.sqlest = (unsigned char  *)&sqlca;
  sqlstm.sqlety = (unsigned short)4352;
  sqlstm.occurs = (unsigned int  )0;
  sqlstm.sqfoff = (           int )0;
  sqlstm.sqfmod = (unsigned int )2;
  sqlstm.sqhstv[0] = (         void  *)vRet;
  sqlstm.sqhstl[0] = (unsigned int  )1000;
  sqlstm.sqhsts[0] = (         int  )0;
  sqlstm.sqindv[0] = (         void  *)0;
  sqlstm.sqinds[0] = (         int  )0;
  sqlstm.sqharm[0] = (unsigned int  )0;
  sqlstm.sqadto[0] = (unsigned short )0;
  sqlstm.sqtdso[0] = (unsigned short )0;
  sqlstm.sqphsv = sqlstm.sqhstv;
  sqlstm.sqphsl = sqlstm.sqhstl;
  sqlstm.sqphss = sqlstm.sqhsts;
  sqlstm.sqpind = sqlstm.sqindv;
  sqlstm.sqpins = sqlstm.sqinds;
  sqlstm.sqparm = sqlstm.sqharm;
  sqlstm.sqparc = sqlstm.sqharc;
  sqlstm.sqpadto = sqlstm.sqadto;
  sqlstm.sqptdso = sqlstm.sqtdso;
  sqlcxt(&vCtx, &sqlctx, &sqlstm, &sqlfpn);
}


		if (sqlca.sqlcode != 0) {
			LogWrite(DebugParms, LOG_ERROR, "GetStringArrayFromQuery: SQL Error %d\n", 1, sqlca.sqlcode);
			return sqlca.sqlcode;
		}
		Trim(vRet); strcpy(oRet[i], vRet);
	}
	/* EXEC SQL CLOSE c82; */ 

{
 struct sqlexd sqlstm;
 sqlstm.sqlvsn = 13;
 sqlstm.arrsiz = 11;
 sqlstm.sqladtp = &sqladt;
 sqlstm.sqltdsp = &sqltds;
 sqlstm.iters = (unsigned int  )1;
 sqlstm.offset = (unsigned int  )2639;
 sqlstm.cud = sqlcud0;
 sqlstm.sqlest = (unsigned char  *)&sqlca;
 sqlstm.sqlety = (unsigned short)4352;
 sqlstm.occurs = (unsigned int  )0;
 sqlcxt(&vCtx, &sqlctx, &sqlstm, &sqlfpn);
}


	return sqlca.sqlcode;
}
EXPORT int GetIntFromQuery(tDebugInfo* DebugParms, tDBConnection* DBConnInfo, sql_context pCtx, char* pSQL, int* oRet) {
	/* EXEC SQL BEGIN DECLARE SECTION; */ 

	char vSQL[1000];
	int vRet = 0;
	sql_context vCtx = pCtx;
	/* EXEC SQL END   DECLARE SECTION; */ 

	strcpy(vSQL, pSQL);

	/* EXEC SQL CONTEXT USE : vCtx; */ 

	/* EXEC SQL PREPARE s1 FROM : vSQL; */ 

{
 struct sqlexd sqlstm;
 sqlstm.sqlvsn = 13;
 sqlstm.arrsiz = 11;
 sqlstm.sqladtp = &sqladt;
 sqlstm.sqltdsp = &sqltds;
 sqlstm.stmt = "";
 sqlstm.iters = (unsigned int  )1;
 sqlstm.offset = (unsigned int  )2654;
 sqlstm.cud = sqlcud0;
 sqlstm.sqlest = (unsigned char  *)&sqlca;
 sqlstm.sqlety = (unsigned short)4352;
 sqlstm.occurs = (unsigned int  )0;
 sqlstm.sqhstv[0] = (         void  *)vSQL;
 sqlstm.sqhstl[0] = (unsigned int  )1000;
 sqlstm.sqhsts[0] = (         int  )0;
 sqlstm.sqindv[0] = (         void  *)0;
 sqlstm.sqinds[0] = (         int  )0;
 sqlstm.sqharm[0] = (unsigned int  )0;
 sqlstm.sqadto[0] = (unsigned short )0;
 sqlstm.sqtdso[0] = (unsigned short )0;
 sqlstm.sqphsv = sqlstm.sqhstv;
 sqlstm.sqphsl = sqlstm.sqhstl;
 sqlstm.sqphss = sqlstm.sqhsts;
 sqlstm.sqpind = sqlstm.sqindv;
 sqlstm.sqpins = sqlstm.sqinds;
 sqlstm.sqparm = sqlstm.sqharm;
 sqlstm.sqparc = sqlstm.sqharc;
 sqlstm.sqpadto = sqlstm.sqadto;
 sqlstm.sqptdso = sqlstm.sqtdso;
 sqlcxt(&vCtx, &sqlctx, &sqlstm, &sqlfpn);
}


	/* EXEC SQL DECLARE c1 CURSOR FOR s1; */ 

	/* EXEC SQL OPEN c1; */ 

{
 struct sqlexd sqlstm;
 sqlstm.sqlvsn = 13;
 sqlstm.arrsiz = 11;
 sqlstm.sqladtp = &sqladt;
 sqlstm.sqltdsp = &sqltds;
 sqlstm.stmt = "";
 sqlstm.iters = (unsigned int  )1;
 sqlstm.offset = (unsigned int  )2673;
 sqlstm.selerr = (unsigned short)1;
 sqlstm.sqlpfmem = (unsigned int  )0;
 sqlstm.cud = sqlcud0;
 sqlstm.sqlest = (unsigned char  *)&sqlca;
 sqlstm.sqlety = (unsigned short)4352;
 sqlstm.occurs = (unsigned int  )0;
 sqlstm.sqcmod = (unsigned int )0;
 sqlcxt(&vCtx, &sqlctx, &sqlstm, &sqlfpn);
}


	/* EXEC SQL FETCH c1 INTO : vRet; */ 

{
 struct sqlexd sqlstm;
 sqlstm.sqlvsn = 13;
 sqlstm.arrsiz = 11;
 sqlstm.sqladtp = &sqladt;
 sqlstm.sqltdsp = &sqltds;
 sqlstm.iters = (unsigned int  )1;
 sqlstm.offset = (unsigned int  )2688;
 sqlstm.selerr = (unsigned short)1;
 sqlstm.sqlpfmem = (unsigned int  )0;
 sqlstm.cud = sqlcud0;
 sqlstm.sqlest = (unsigned char  *)&sqlca;
 sqlstm.sqlety = (unsigned short)4352;
 sqlstm.occurs = (unsigned int  )0;
 sqlstm.sqfoff = (           int )0;
 sqlstm.sqfmod = (unsigned int )2;
 sqlstm.sqhstv[0] = (         void  *)&vRet;
 sqlstm.sqhstl[0] = (unsigned int  )sizeof(int);
 sqlstm.sqhsts[0] = (         int  )0;
 sqlstm.sqindv[0] = (         void  *)0;
 sqlstm.sqinds[0] = (         int  )0;
 sqlstm.sqharm[0] = (unsigned int  )0;
 sqlstm.sqadto[0] = (unsigned short )0;
 sqlstm.sqtdso[0] = (unsigned short )0;
 sqlstm.sqphsv = sqlstm.sqhstv;
 sqlstm.sqphsl = sqlstm.sqhstl;
 sqlstm.sqphss = sqlstm.sqhsts;
 sqlstm.sqpind = sqlstm.sqindv;
 sqlstm.sqpins = sqlstm.sqinds;
 sqlstm.sqparm = sqlstm.sqharm;
 sqlstm.sqparc = sqlstm.sqharc;
 sqlstm.sqpadto = sqlstm.sqadto;
 sqlstm.sqptdso = sqlstm.sqtdso;
 sqlcxt(&vCtx, &sqlctx, &sqlstm, &sqlfpn);
}



	if (sqlca.sqlcode != 0) {
		LogWrite(DebugParms, LOG_ERROR, "GetIntFromQuery: SQL Error %d\n", 1, sqlca.sqlcode);
		return sqlca.sqlcode;
	}

	(*oRet) = vRet;
	/* EXEC SQL CLOSE c1; */ 

{
 struct sqlexd sqlstm;
 sqlstm.sqlvsn = 13;
 sqlstm.arrsiz = 11;
 sqlstm.sqladtp = &sqladt;
 sqlstm.sqltdsp = &sqltds;
 sqlstm.iters = (unsigned int  )1;
 sqlstm.offset = (unsigned int  )2707;
 sqlstm.cud = sqlcud0;
 sqlstm.sqlest = (unsigned char  *)&sqlca;
 sqlstm.sqlety = (unsigned short)4352;
 sqlstm.occurs = (unsigned int  )0;
 sqlcxt(&vCtx, &sqlctx, &sqlstm, &sqlfpn);
}


	return sqlca.sqlcode;
}
EXPORT int GetBarsFromQuery(tDebugInfo* DebugInfo, sql_context pCtx, char* pSQL, int pRecCount, int pSkipFirstN, tBar* oBar) {
	/* EXEC SQL BEGIN DECLARE SECTION; */ 

	int i = 0;  int j;
	int retval = 0;
	char vNDT[12 + 1];
	//sql_context vCtx = pCtx;
	struct sBar {
		char NewDateTime[12 + 1];
		double Open;
		double High;
		double Low;
		double Close;
		double OpenD;
		double HighD;
		double LowD;
		double CloseD;
		double Volume;
		double VolumeD;
	} *vBar;
	char vSQL[1000];
	/* EXEC SQL END DECLARE SECTION; */ 

	vBar = (struct sBar*)malloc((pRecCount + pSkipFirstN)*sizeof(struct sBar));
	strcpy(vSQL, pSQL);

	/* EXEC SQL CONTEXT USE : pCtx; */ 

	/* EXEC SQL PREPARE s4 FROM : vSQL; */ 

{
 struct sqlexd sqlstm;
 sqlstm.sqlvsn = 13;
 sqlstm.arrsiz = 11;
 sqlstm.sqladtp = &sqladt;
 sqlstm.sqltdsp = &sqltds;
 sqlstm.stmt = "";
 sqlstm.iters = (unsigned int  )1;
 sqlstm.offset = (unsigned int  )2722;
 sqlstm.cud = sqlcud0;
 sqlstm.sqlest = (unsigned char  *)&sqlca;
 sqlstm.sqlety = (unsigned short)4352;
 sqlstm.occurs = (unsigned int  )0;
 sqlstm.sqhstv[0] = (         void  *)vSQL;
 sqlstm.sqhstl[0] = (unsigned int  )1000;
 sqlstm.sqhsts[0] = (         int  )0;
 sqlstm.sqindv[0] = (         void  *)0;
 sqlstm.sqinds[0] = (         int  )0;
 sqlstm.sqharm[0] = (unsigned int  )0;
 sqlstm.sqadto[0] = (unsigned short )0;
 sqlstm.sqtdso[0] = (unsigned short )0;
 sqlstm.sqphsv = sqlstm.sqhstv;
 sqlstm.sqphsl = sqlstm.sqhstl;
 sqlstm.sqphss = sqlstm.sqhsts;
 sqlstm.sqpind = sqlstm.sqindv;
 sqlstm.sqpins = sqlstm.sqinds;
 sqlstm.sqparm = sqlstm.sqharm;
 sqlstm.sqparc = sqlstm.sqharc;
 sqlstm.sqpadto = sqlstm.sqadto;
 sqlstm.sqptdso = sqlstm.sqtdso;
 sqlcxt(&pCtx, &sqlctx, &sqlstm, &sqlfpn);
}


	/* EXEC SQL DECLARE c4 CURSOR FOR s4; */ 

	/* EXEC SQL OPEN c4; */ 

{
 struct sqlexd sqlstm;
 sqlstm.sqlvsn = 13;
 sqlstm.arrsiz = 11;
 sqlstm.sqladtp = &sqladt;
 sqlstm.sqltdsp = &sqltds;
 sqlstm.stmt = "";
 sqlstm.iters = (unsigned int  )1;
 sqlstm.offset = (unsigned int  )2741;
 sqlstm.selerr = (unsigned short)1;
 sqlstm.sqlpfmem = (unsigned int  )0;
 sqlstm.cud = sqlcud0;
 sqlstm.sqlest = (unsigned char  *)&sqlca;
 sqlstm.sqlety = (unsigned short)4352;
 sqlstm.occurs = (unsigned int  )0;
 sqlstm.sqcmod = (unsigned int )0;
 sqlcxt(&pCtx, &sqlctx, &sqlstm, &sqlfpn);
}


	for (i = 0; i<(pRecCount + pSkipFirstN); i++) {
		/* EXEC SQL FETCH c4 INTO : vNDT, : vBar[i].Open, : vBar[i].High, : vBar[i].Low, : vBar[i].Close, : vBar[i].Volume; */ 

{
  struct sqlexd sqlstm;
  sqlstm.sqlvsn = 13;
  sqlstm.arrsiz = 11;
  sqlstm.sqladtp = &sqladt;
  sqlstm.sqltdsp = &sqltds;
  sqlstm.iters = (unsigned int  )1;
  sqlstm.offset = (unsigned int  )2756;
  sqlstm.selerr = (unsigned short)1;
  sqlstm.sqlpfmem = (unsigned int  )0;
  sqlstm.cud = sqlcud0;
  sqlstm.sqlest = (unsigned char  *)&sqlca;
  sqlstm.sqlety = (unsigned short)4352;
  sqlstm.occurs = (unsigned int  )0;
  sqlstm.sqfoff = (           int )0;
  sqlstm.sqfmod = (unsigned int )2;
  sqlstm.sqhstv[0] = (         void  *)vNDT;
  sqlstm.sqhstl[0] = (unsigned int  )13;
  sqlstm.sqhsts[0] = (         int  )0;
  sqlstm.sqindv[0] = (         void  *)0;
  sqlstm.sqinds[0] = (         int  )0;
  sqlstm.sqharm[0] = (unsigned int  )0;
  sqlstm.sqadto[0] = (unsigned short )0;
  sqlstm.sqtdso[0] = (unsigned short )0;
  sqlstm.sqhstv[1] = (         void  *)&(vBar[i].Open);
  sqlstm.sqhstl[1] = (unsigned int  )sizeof(double);
  sqlstm.sqhsts[1] = (         int  )0;
  sqlstm.sqindv[1] = (         void  *)0;
  sqlstm.sqinds[1] = (         int  )0;
  sqlstm.sqharm[1] = (unsigned int  )0;
  sqlstm.sqadto[1] = (unsigned short )0;
  sqlstm.sqtdso[1] = (unsigned short )0;
  sqlstm.sqhstv[2] = (         void  *)&(vBar[i].High);
  sqlstm.sqhstl[2] = (unsigned int  )sizeof(double);
  sqlstm.sqhsts[2] = (         int  )0;
  sqlstm.sqindv[2] = (         void  *)0;
  sqlstm.sqinds[2] = (         int  )0;
  sqlstm.sqharm[2] = (unsigned int  )0;
  sqlstm.sqadto[2] = (unsigned short )0;
  sqlstm.sqtdso[2] = (unsigned short )0;
  sqlstm.sqhstv[3] = (         void  *)&(vBar[i].Low);
  sqlstm.sqhstl[3] = (unsigned int  )sizeof(double);
  sqlstm.sqhsts[3] = (         int  )0;
  sqlstm.sqindv[3] = (         void  *)0;
  sqlstm.sqinds[3] = (         int  )0;
  sqlstm.sqharm[3] = (unsigned int  )0;
  sqlstm.sqadto[3] = (unsigned short )0;
  sqlstm.sqtdso[3] = (unsigned short )0;
  sqlstm.sqhstv[4] = (         void  *)&(vBar[i].Close);
  sqlstm.sqhstl[4] = (unsigned int  )sizeof(double);
  sqlstm.sqhsts[4] = (         int  )0;
  sqlstm.sqindv[4] = (         void  *)0;
  sqlstm.sqinds[4] = (         int  )0;
  sqlstm.sqharm[4] = (unsigned int  )0;
  sqlstm.sqadto[4] = (unsigned short )0;
  sqlstm.sqtdso[4] = (unsigned short )0;
  sqlstm.sqhstv[5] = (         void  *)&(vBar[i].Volume);
  sqlstm.sqhstl[5] = (unsigned int  )sizeof(double);
  sqlstm.sqhsts[5] = (         int  )0;
  sqlstm.sqindv[5] = (         void  *)0;
  sqlstm.sqinds[5] = (         int  )0;
  sqlstm.sqharm[5] = (unsigned int  )0;
  sqlstm.sqadto[5] = (unsigned short )0;
  sqlstm.sqtdso[5] = (unsigned short )0;
  sqlstm.sqphsv = sqlstm.sqhstv;
  sqlstm.sqphsl = sqlstm.sqhstl;
  sqlstm.sqphss = sqlstm.sqhsts;
  sqlstm.sqpind = sqlstm.sqindv;
  sqlstm.sqpins = sqlstm.sqinds;
  sqlstm.sqparm = sqlstm.sqharm;
  sqlstm.sqparc = sqlstm.sqharc;
  sqlstm.sqpadto = sqlstm.sqadto;
  sqlstm.sqptdso = sqlstm.sqtdso;
  sqlcxt(&pCtx, &sqlctx, &sqlstm, &sqlfpn);
}


		if (sqlca.sqlcode == 0) {
			strcpy(vBar[i].NewDateTime, vNDT);
		}
		else if (sqlca.sqlcode == 1403) {
			break;
		}
		else {
			LogWrite(DebugInfo, LOG_ERROR, "GetBarsFromQuery (Loop): SQL Error %d\n", 1, sqlca.sqlcode);
			retval = sqlca.sqlcode;
			break;
		}
	}
	/* EXEC SQL CLOSE c4; */ 

{
 struct sqlexd sqlstm;
 sqlstm.sqlvsn = 13;
 sqlstm.arrsiz = 11;
 sqlstm.sqladtp = &sqladt;
 sqlstm.sqltdsp = &sqltds;
 sqlstm.iters = (unsigned int  )1;
 sqlstm.offset = (unsigned int  )2795;
 sqlstm.cud = sqlcud0;
 sqlstm.sqlest = (unsigned char  *)&sqlca;
 sqlstm.sqlety = (unsigned short)4352;
 sqlstm.occurs = (unsigned int  )0;
 sqlcxt(&pCtx, &sqlctx, &sqlstm, &sqlfpn);
}



	if (i > 0) {
		for (j = 0; j < pRecCount; j++) {
			memcpy(&oBar[j], &vBar[pSkipFirstN + j], sizeof(tBar));
		}
	}
	free(vBar);
	return retval;
}
EXPORT int GetBarsFromQuery2(tDebugInfo* DebugParms, tDBConnection* DBConnInfo, sql_context pCtx, char* pSQL, int* pRecCount, tBar* oBar) {
	/* EXEC SQL BEGIN DECLARE SECTION; */ 

	int i = 0;
	int retval = 0;
	double tmpd;
	sql_context vCtx = pCtx;

	char vNDT[12 + 1];
	double vOpen; double vHigh; double vLow; double vClose; double vOpenD; double vHighD; double vLowD; double vCloseD;

	char vSQL[1000];
	/* EXEC SQL END DECLARE SECTION; */ 


	strcpy(vSQL, pSQL);
	/* EXEC SQL CONTEXT USE : vCtx; */ 

	/* EXEC SQL PREPARE s9 FROM : vSQL; */ 

{
 struct sqlexd sqlstm;
 sqlstm.sqlvsn = 13;
 sqlstm.arrsiz = 11;
 sqlstm.sqladtp = &sqladt;
 sqlstm.sqltdsp = &sqltds;
 sqlstm.stmt = "";
 sqlstm.iters = (unsigned int  )1;
 sqlstm.offset = (unsigned int  )2810;
 sqlstm.cud = sqlcud0;
 sqlstm.sqlest = (unsigned char  *)&sqlca;
 sqlstm.sqlety = (unsigned short)4352;
 sqlstm.occurs = (unsigned int  )0;
 sqlstm.sqhstv[0] = (         void  *)vSQL;
 sqlstm.sqhstl[0] = (unsigned int  )1000;
 sqlstm.sqhsts[0] = (         int  )0;
 sqlstm.sqindv[0] = (         void  *)0;
 sqlstm.sqinds[0] = (         int  )0;
 sqlstm.sqharm[0] = (unsigned int  )0;
 sqlstm.sqadto[0] = (unsigned short )0;
 sqlstm.sqtdso[0] = (unsigned short )0;
 sqlstm.sqphsv = sqlstm.sqhstv;
 sqlstm.sqphsl = sqlstm.sqhstl;
 sqlstm.sqphss = sqlstm.sqhsts;
 sqlstm.sqpind = sqlstm.sqindv;
 sqlstm.sqpins = sqlstm.sqinds;
 sqlstm.sqparm = sqlstm.sqharm;
 sqlstm.sqparc = sqlstm.sqharc;
 sqlstm.sqpadto = sqlstm.sqadto;
 sqlstm.sqptdso = sqlstm.sqtdso;
 sqlcxt(&vCtx, &sqlctx, &sqlstm, &sqlfpn);
}


	/* EXEC SQL DECLARE c9 CURSOR FOR s9; */ 

	/* EXEC SQL OPEN c9; */ 

{
 struct sqlexd sqlstm;
 sqlstm.sqlvsn = 13;
 sqlstm.arrsiz = 11;
 sqlstm.sqladtp = &sqladt;
 sqlstm.sqltdsp = &sqltds;
 sqlstm.stmt = "";
 sqlstm.iters = (unsigned int  )1;
 sqlstm.offset = (unsigned int  )2829;
 sqlstm.selerr = (unsigned short)1;
 sqlstm.sqlpfmem = (unsigned int  )0;
 sqlstm.cud = sqlcud0;
 sqlstm.sqlest = (unsigned char  *)&sqlca;
 sqlstm.sqlety = (unsigned short)4352;
 sqlstm.occurs = (unsigned int  )0;
 sqlstm.sqcmod = (unsigned int )0;
 sqlcxt(&vCtx, &sqlctx, &sqlstm, &sqlfpn);
}


	for (i = 0; i<(*pRecCount); i++) {
		/* EXEC SQL FETCH c9 INTO : vNDT, : vOpen, : vHigh, : vLow, : vClose, : vOpenD, : vHighD, : vLowD, : vCloseD; */ 

{
  struct sqlexd sqlstm;
  sqlstm.sqlvsn = 13;
  sqlstm.arrsiz = 11;
  sqlstm.sqladtp = &sqladt;
  sqlstm.sqltdsp = &sqltds;
  sqlstm.iters = (unsigned int  )1;
  sqlstm.offset = (unsigned int  )2844;
  sqlstm.selerr = (unsigned short)1;
  sqlstm.sqlpfmem = (unsigned int  )0;
  sqlstm.cud = sqlcud0;
  sqlstm.sqlest = (unsigned char  *)&sqlca;
  sqlstm.sqlety = (unsigned short)4352;
  sqlstm.occurs = (unsigned int  )0;
  sqlstm.sqfoff = (           int )0;
  sqlstm.sqfmod = (unsigned int )2;
  sqlstm.sqhstv[0] = (         void  *)vNDT;
  sqlstm.sqhstl[0] = (unsigned int  )13;
  sqlstm.sqhsts[0] = (         int  )0;
  sqlstm.sqindv[0] = (         void  *)0;
  sqlstm.sqinds[0] = (         int  )0;
  sqlstm.sqharm[0] = (unsigned int  )0;
  sqlstm.sqadto[0] = (unsigned short )0;
  sqlstm.sqtdso[0] = (unsigned short )0;
  sqlstm.sqhstv[1] = (         void  *)&vOpen;
  sqlstm.sqhstl[1] = (unsigned int  )sizeof(double);
  sqlstm.sqhsts[1] = (         int  )0;
  sqlstm.sqindv[1] = (         void  *)0;
  sqlstm.sqinds[1] = (         int  )0;
  sqlstm.sqharm[1] = (unsigned int  )0;
  sqlstm.sqadto[1] = (unsigned short )0;
  sqlstm.sqtdso[1] = (unsigned short )0;
  sqlstm.sqhstv[2] = (         void  *)&vHigh;
  sqlstm.sqhstl[2] = (unsigned int  )sizeof(double);
  sqlstm.sqhsts[2] = (         int  )0;
  sqlstm.sqindv[2] = (         void  *)0;
  sqlstm.sqinds[2] = (         int  )0;
  sqlstm.sqharm[2] = (unsigned int  )0;
  sqlstm.sqadto[2] = (unsigned short )0;
  sqlstm.sqtdso[2] = (unsigned short )0;
  sqlstm.sqhstv[3] = (         void  *)&vLow;
  sqlstm.sqhstl[3] = (unsigned int  )sizeof(double);
  sqlstm.sqhsts[3] = (         int  )0;
  sqlstm.sqindv[3] = (         void  *)0;
  sqlstm.sqinds[3] = (         int  )0;
  sqlstm.sqharm[3] = (unsigned int  )0;
  sqlstm.sqadto[3] = (unsigned short )0;
  sqlstm.sqtdso[3] = (unsigned short )0;
  sqlstm.sqhstv[4] = (         void  *)&vClose;
  sqlstm.sqhstl[4] = (unsigned int  )sizeof(double);
  sqlstm.sqhsts[4] = (         int  )0;
  sqlstm.sqindv[4] = (         void  *)0;
  sqlstm.sqinds[4] = (         int  )0;
  sqlstm.sqharm[4] = (unsigned int  )0;
  sqlstm.sqadto[4] = (unsigned short )0;
  sqlstm.sqtdso[4] = (unsigned short )0;
  sqlstm.sqhstv[5] = (         void  *)&vOpenD;
  sqlstm.sqhstl[5] = (unsigned int  )sizeof(double);
  sqlstm.sqhsts[5] = (         int  )0;
  sqlstm.sqindv[5] = (         void  *)0;
  sqlstm.sqinds[5] = (         int  )0;
  sqlstm.sqharm[5] = (unsigned int  )0;
  sqlstm.sqadto[5] = (unsigned short )0;
  sqlstm.sqtdso[5] = (unsigned short )0;
  sqlstm.sqhstv[6] = (         void  *)&vHighD;
  sqlstm.sqhstl[6] = (unsigned int  )sizeof(double);
  sqlstm.sqhsts[6] = (         int  )0;
  sqlstm.sqindv[6] = (         void  *)0;
  sqlstm.sqinds[6] = (         int  )0;
  sqlstm.sqharm[6] = (unsigned int  )0;
  sqlstm.sqadto[6] = (unsigned short )0;
  sqlstm.sqtdso[6] = (unsigned short )0;
  sqlstm.sqhstv[7] = (         void  *)&vLowD;
  sqlstm.sqhstl[7] = (unsigned int  )sizeof(double);
  sqlstm.sqhsts[7] = (         int  )0;
  sqlstm.sqindv[7] = (         void  *)0;
  sqlstm.sqinds[7] = (         int  )0;
  sqlstm.sqharm[7] = (unsigned int  )0;
  sqlstm.sqadto[7] = (unsigned short )0;
  sqlstm.sqtdso[7] = (unsigned short )0;
  sqlstm.sqhstv[8] = (         void  *)&vCloseD;
  sqlstm.sqhstl[8] = (unsigned int  )sizeof(double);
  sqlstm.sqhsts[8] = (         int  )0;
  sqlstm.sqindv[8] = (         void  *)0;
  sqlstm.sqinds[8] = (         int  )0;
  sqlstm.sqharm[8] = (unsigned int  )0;
  sqlstm.sqadto[8] = (unsigned short )0;
  sqlstm.sqtdso[8] = (unsigned short )0;
  sqlstm.sqphsv = sqlstm.sqhstv;
  sqlstm.sqphsl = sqlstm.sqhstl;
  sqlstm.sqphss = sqlstm.sqhsts;
  sqlstm.sqpind = sqlstm.sqindv;
  sqlstm.sqpins = sqlstm.sqinds;
  sqlstm.sqparm = sqlstm.sqharm;
  sqlstm.sqparc = sqlstm.sqharc;
  sqlstm.sqpadto = sqlstm.sqadto;
  sqlstm.sqptdso = sqlstm.sqtdso;
  sqlcxt(&vCtx, &sqlctx, &sqlstm, &sqlfpn);
}


		if (sqlca.sqlcode == 0) {
			strcpy(oBar[i].NewDateTime, vNDT);
			oBar[i].Open = vOpen; oBar[i].OpenD = vOpenD;
			oBar[i].High = vHigh; oBar[i].HighD = vHighD;
			oBar[i].Low = vLow; oBar[i].LowD = vLowD;
			oBar[i].Close = vClose; oBar[i].CloseD = vCloseD;
		}
		else if (sqlca.sqlcode == 1403) {
			(*pRecCount) = i;
			break;
		}
		else {
			LogWrite(DebugParms, LOG_ERROR, "GetBarsFromQuery (Loop): SQL Error %d\n", 1, sqlca.sqlcode);
			retval = sqlca.sqlcode;
			(*pRecCount) = i;
			break;
		}
	}
	/* EXEC SQL CLOSE c9; */ 

{
 struct sqlexd sqlstm;
 sqlstm.sqlvsn = 13;
 sqlstm.arrsiz = 11;
 sqlstm.sqladtp = &sqladt;
 sqlstm.sqltdsp = &sqltds;
 sqlstm.iters = (unsigned int  )1;
 sqlstm.offset = (unsigned int  )2895;
 sqlstm.cud = sqlcud0;
 sqlstm.sqlest = (unsigned char  *)&sqlca;
 sqlstm.sqlety = (unsigned short)4352;
 sqlstm.occurs = (unsigned int  )0;
 sqlcxt(&vCtx, &sqlctx, &sqlstm, &sqlfpn);
}



	for (i = 0; i < (*pRecCount) / 2; i++) {
		tmpd = oBar[(*pRecCount) - i].Open;
		oBar[(*pRecCount) - i].Open = oBar[i].Open;
		oBar[i].Open = tmpd;
	}

	return retval;
}

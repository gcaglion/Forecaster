
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
5,0,0,0,0,0,58,147,0,0,1,1,0,1,0,3,109,0,0,
24,0,0,0,0,0,27,149,0,0,4,4,0,1,0,1,97,0,0,1,97,0,0,1,97,0,0,1,10,0,0,
55,0,0,2,0,0,30,171,0,0,0,0,0,1,0,
70,0,0,3,0,0,29,179,0,0,0,0,0,1,0,
85,0,0,4,0,0,24,204,0,0,1,1,0,1,0,1,97,0,0,
104,0,0,5,0,0,24,226,0,0,1,1,0,1,0,1,97,0,0,
123,0,0,6,0,0,24,248,0,0,1,1,0,1,0,1,97,0,0,
142,0,0,7,0,0,24,275,0,0,1,1,0,1,0,1,97,0,0,
161,0,0,8,0,0,24,301,0,0,1,1,0,1,0,1,97,0,0,
180,0,0,9,0,0,24,330,0,0,1,1,0,1,0,1,97,0,0,
199,0,0,0,0,0,90,404,0,64,0,0,3,87,78,78,1,0,
217,0,0,0,0,0,93,405,0,64,0,0,3,87,78,78,1,0,
235,0,0,0,0,0,93,406,0,64,1,1,3,87,78,78,1,0,513,3,0,0,
257,0,0,0,0,0,93,407,0,64,1,1,3,87,78,78,1,0,513,3,0,0,
279,0,0,0,0,0,93,408,0,64,1,1,3,87,78,78,1,0,513,3,0,0,
301,0,0,0,0,0,93,409,0,64,1,1,3,87,78,78,1,0,513,3,0,0,
323,0,0,0,0,0,93,410,0,64,1,1,3,87,78,78,1,0,513,3,0,0,
345,0,0,0,0,0,93,411,0,64,1,1,3,87,78,78,1,0,513,3,0,0,
367,0,0,0,0,0,93,412,0,64,1,1,3,87,78,78,1,0,513,3,0,0,
389,0,0,0,0,0,93,413,0,64,1,1,3,87,78,78,1,0,513,3,0,0,
411,0,0,0,0,0,93,414,0,64,1,1,3,87,78,78,1,0,513,3,0,0,
433,0,0,0,0,0,93,415,0,64,1,1,3,87,78,78,1,0,513,3,0,0,
455,0,0,0,0,0,93,416,0,64,1,1,3,87,78,78,1,0,513,3,0,0,
477,0,0,0,0,0,93,418,0,64,1,1,3,87,78,78,1,0,3329,3,0,0,
499,0,0,0,0,0,93,419,0,64,1,1,3,87,78,78,1,0,3329,3,0,0,
521,0,0,0,0,0,93,420,0,64,1,1,3,87,78,78,1,0,3329,3,0,0,
543,0,0,0,0,0,93,421,0,64,1,1,3,87,78,78,1,0,3329,3,0,0,
565,0,0,0,0,0,93,422,0,64,1,1,3,87,78,78,1,0,3329,3,0,0,
587,0,0,0,0,0,93,423,0,64,1,1,3,87,78,78,1,0,3329,3,0,0,
609,0,0,0,0,0,93,424,0,64,1,1,3,87,78,78,1,0,3329,3,0,0,
631,0,0,0,0,0,93,425,0,64,1,1,3,87,78,78,1,0,3329,3,0,0,
653,0,0,0,0,0,93,426,0,64,1,1,3,87,78,78,1,0,3329,3,0,0,
675,0,0,0,0,0,93,427,0,64,1,1,3,87,78,78,1,0,3329,4,0,0,
697,0,0,0,0,0,93,428,0,64,1,1,3,87,78,78,1,0,3329,4,0,0,
719,0,0,10,0,0,17,430,0,0,1,1,0,1,0,1,97,0,0,
738,0,0,10,0,0,23,431,0,64,0,0,3,87,78,78,1,0,
756,0,0,0,0,0,91,437,0,64,0,0,3,87,78,78,1,0,
774,0,0,0,0,0,90,512,0,64,0,0,4,87,83,79,77,1,0,
793,0,0,0,0,0,93,513,0,64,0,0,4,87,83,79,77,1,0,
812,0,0,0,0,0,93,514,0,64,1,1,4,87,83,79,77,1,0,513,3,0,0,
835,0,0,0,0,0,93,515,0,64,1,1,4,87,83,79,77,1,0,513,3,0,0,
858,0,0,0,0,0,93,516,0,64,1,1,4,87,83,79,77,1,0,513,3,0,0,
881,0,0,0,0,0,93,517,0,64,1,1,4,87,83,79,77,1,0,513,3,0,0,
904,0,0,0,0,0,93,518,0,64,1,1,4,87,83,79,77,1,0,513,3,0,0,
927,0,0,0,0,0,93,519,0,64,1,1,4,87,83,79,77,1,0,513,3,0,0,
950,0,0,0,0,0,93,520,0,64,1,1,4,87,83,79,77,1,0,513,3,0,0,
973,0,0,0,0,0,93,521,0,64,1,1,4,87,83,79,77,1,0,513,3,0,0,
996,0,0,0,0,0,93,522,0,64,1,1,4,87,83,79,77,1,0,513,3,0,0,
1019,0,0,0,0,0,93,524,0,64,1,1,4,87,83,79,77,1,0,3329,3,0,0,
1042,0,0,0,0,0,93,525,0,64,1,1,4,87,83,79,77,1,0,3329,3,0,0,
1065,0,0,0,0,0,93,526,0,64,1,1,4,87,83,79,77,1,0,3329,3,0,0,
1088,0,0,0,0,0,93,527,0,64,1,1,4,87,83,79,77,1,0,3329,3,0,0,
1111,0,0,0,0,0,93,528,0,64,1,1,4,87,83,79,77,1,0,3329,3,0,0,
1134,0,0,0,0,0,93,529,0,64,1,1,4,87,83,79,77,1,0,3329,3,0,0,
1157,0,0,0,0,0,93,530,0,64,1,1,4,87,83,79,77,1,0,3329,3,0,0,
1180,0,0,0,0,0,93,531,0,64,1,1,4,87,83,79,77,1,0,3329,3,0,0,
1203,0,0,0,0,0,93,532,0,64,1,1,4,87,83,79,77,1,0,3329,4,0,0,
1226,0,0,11,0,0,17,534,0,0,1,1,0,1,0,1,97,0,0,
1245,0,0,11,0,0,23,535,0,64,0,0,4,87,83,79,77,1,0,
1264,0,0,0,0,0,91,541,0,64,0,0,4,87,83,79,77,1,0,
1283,0,0,0,0,0,90,615,0,64,0,0,4,87,83,86,77,1,0,
1302,0,0,0,0,0,93,616,0,64,0,0,4,87,83,86,77,1,0,
1321,0,0,0,0,0,93,617,0,64,1,1,4,87,83,86,77,1,0,513,3,0,0,
1344,0,0,0,0,0,93,618,0,64,1,1,4,87,83,86,77,1,0,513,3,0,0,
1367,0,0,0,0,0,93,619,0,64,1,1,4,87,83,86,77,1,0,513,3,0,0,
1390,0,0,0,0,0,93,620,0,64,1,1,4,87,83,86,77,1,0,513,3,0,0,
1413,0,0,0,0,0,93,621,0,64,1,1,4,87,83,86,77,1,0,513,3,0,0,
1436,0,0,0,0,0,93,622,0,64,1,1,4,87,83,86,77,1,0,513,3,0,0,
1459,0,0,0,0,0,93,623,0,64,1,1,4,87,83,86,77,1,0,513,3,0,0,
1482,0,0,0,0,0,93,624,0,64,1,1,4,87,83,86,77,1,0,513,3,0,0,
1505,0,0,0,0,0,93,625,0,64,1,1,4,87,83,86,77,1,0,513,3,0,0,
1528,0,0,0,0,0,93,627,0,64,1,1,4,87,83,86,77,1,0,3329,3,0,0,
1551,0,0,0,0,0,93,628,0,64,1,1,4,87,83,86,77,1,0,3329,3,0,0,
1574,0,0,0,0,0,93,629,0,64,1,1,4,87,83,86,77,1,0,3329,3,0,0,
1597,0,0,0,0,0,93,630,0,64,1,1,4,87,83,86,77,1,0,3329,3,0,0,
1620,0,0,0,0,0,93,631,0,64,1,1,4,87,83,86,77,1,0,3329,3,0,0,
1643,0,0,0,0,0,93,632,0,64,1,1,4,87,83,86,77,1,0,3329,3,0,0,
1666,0,0,0,0,0,93,633,0,64,1,1,4,87,83,86,77,1,0,3329,3,0,0,
1689,0,0,0,0,0,93,634,0,64,1,1,4,87,83,86,77,1,0,3329,3,0,0,
1712,0,0,0,0,0,93,635,0,64,1,1,4,87,83,86,77,1,0,3329,4,0,0,
1735,0,0,12,0,0,17,637,0,0,1,1,0,1,0,1,97,0,0,
1754,0,0,12,0,0,23,638,0,64,0,0,4,87,83,86,77,1,0,
1773,0,0,0,0,0,91,644,0,64,0,0,4,87,83,86,77,1,0,
1792,0,0,0,0,0,90,698,0,64,0,0,6,105,110,67,76,78,78,1,0,
1813,0,0,0,0,0,93,751,0,64,0,0,6,105,110,67,76,78,78,1,0,
1834,0,0,0,0,0,93,752,0,64,1,1,6,105,110,67,76,78,78,1,0,3329,3,0,0,
1859,0,0,0,0,0,93,753,0,64,1,1,6,105,110,67,76,78,78,1,0,3329,3,0,0,
1884,0,0,0,0,0,93,754,0,64,1,1,6,105,110,67,76,78,78,1,0,3329,3,0,0,
1909,0,0,0,0,0,93,755,0,64,1,1,6,105,110,67,76,78,78,1,0,3329,3,0,0,
1934,0,0,0,0,0,93,756,0,64,1,1,6,105,110,67,76,78,78,1,0,3329,3,0,0,
1959,0,0,0,0,0,93,757,0,64,1,1,6,105,110,67,76,78,78,1,0,3329,4,0,0,
1984,0,0,0,0,0,93,758,0,64,1,1,6,105,110,67,76,78,78,1,0,3329,4,0,0,
2009,0,0,0,0,0,93,759,0,64,1,1,6,105,110,67,76,78,78,1,0,3329,4,0,0,
2034,0,0,0,0,0,93,760,0,64,1,1,6,105,110,67,76,78,78,1,0,3329,4,0,0,
2059,0,0,0,0,0,93,761,0,64,1,1,6,105,110,67,76,78,78,1,0,3329,4,0,0,
2084,0,0,0,0,0,93,762,0,64,1,1,6,105,110,67,76,78,78,1,0,3329,4,0,0,
2109,0,0,0,0,0,93,763,0,64,1,1,6,105,110,67,76,78,78,1,0,3329,4,0,0,
2134,0,0,0,0,0,93,764,0,64,1,1,6,105,110,67,76,78,78,1,0,3329,4,0,0,
2159,0,0,0,0,0,93,765,0,64,1,1,6,105,110,67,76,78,78,1,0,3329,4,0,0,
2184,0,0,13,0,0,17,774,0,0,1,1,0,1,0,1,97,0,0,
2203,0,0,13,0,0,23,775,0,64,0,0,6,105,110,67,76,78,78,1,0,
2224,0,0,0,0,0,91,783,0,64,0,0,6,105,110,67,76,78,78,1,0,
2245,0,0,14,0,0,24,810,0,0,1,1,0,1,0,1,97,0,0,
2264,0,0,0,0,0,90,881,0,64,0,0,5,105,110,77,83,69,1,0,
2284,0,0,0,0,0,93,882,0,64,0,0,5,105,110,77,83,69,1,0,
2304,0,0,0,0,0,93,883,0,64,1,1,5,105,110,77,83,69,1,0,3329,3,0,0,
2328,0,0,0,0,0,93,884,0,64,1,1,5,105,110,77,83,69,1,0,3329,3,0,0,
2352,0,0,0,0,0,93,885,0,64,1,1,5,105,110,77,83,69,1,0,3329,3,0,0,
2376,0,0,0,0,0,93,886,0,64,1,1,5,105,110,77,83,69,1,0,3329,3,0,0,
2400,0,0,0,0,0,93,887,0,64,1,1,5,105,110,77,83,69,1,0,3329,3,0,0,
2424,0,0,0,0,0,93,888,0,64,1,1,5,105,110,77,83,69,1,0,3329,3,0,0,
2448,0,0,0,0,0,93,889,0,64,1,1,5,105,110,77,83,69,1,0,3329,4,0,0,
2472,0,0,0,0,0,93,890,0,64,1,1,5,105,110,77,83,69,1,0,3329,4,0,0,
2496,0,0,13,0,0,17,891,0,0,1,1,0,1,0,1,97,0,0,
2515,0,0,13,0,0,23,892,0,64,0,0,5,105,110,77,83,69,1,0,
2535,0,0,0,0,0,91,902,0,64,0,0,5,105,110,77,83,69,1,0,
2555,0,0,0,0,0,90,998,0,64,0,0,5,105,110,82,117,110,1,0,
2575,0,0,0,0,0,93,999,0,64,1,1,5,105,110,82,117,110,1,0,513,3,0,0,
2599,0,0,0,0,0,93,1000,0,64,1,1,5,105,110,82,117,110,1,0,513,3,0,0,
2623,0,0,0,0,0,93,1001,0,64,1,1,5,105,110,82,117,110,1,0,513,3,0,0,
2647,0,0,0,0,0,93,1002,0,64,1,1,5,105,110,82,117,110,1,0,513,3,0,0,
2671,0,0,0,0,0,93,1003,0,64,1,1,5,105,110,82,117,110,1,0,513,3,0,0,
2695,0,0,0,0,0,93,1004,0,64,1,1,5,105,110,82,117,110,1,0,513,3,0,0,
2719,0,0,0,0,0,93,1005,0,64,1,1,5,105,110,82,117,110,1,0,513,3,0,0,
2743,0,0,0,0,0,93,1006,0,64,1,1,5,105,110,82,117,110,1,0,513,3,0,0,
2767,0,0,0,0,0,93,1007,0,64,1,1,5,105,110,82,117,110,1,0,513,3,0,0,
2791,0,0,0,0,0,93,1008,0,64,1,1,5,105,110,82,117,110,1,0,513,3,0,0,
2815,0,0,0,0,0,93,1009,0,64,1,1,5,105,110,82,117,110,1,0,513,3,0,0,
2839,0,0,0,0,0,93,1010,0,64,1,1,5,105,110,82,117,110,1,0,513,3,0,0,
2863,0,0,0,0,0,93,1011,0,64,1,1,5,105,110,82,117,110,1,0,513,3,0,0,
2887,0,0,0,0,0,93,1012,0,64,1,1,5,105,110,82,117,110,1,0,513,3,0,0,
2911,0,0,0,0,0,93,1013,0,64,1,1,5,105,110,82,117,110,1,0,513,3,0,0,
2935,0,0,0,0,0,93,1014,0,64,1,1,5,105,110,82,117,110,1,0,513,3,0,0,
2959,0,0,0,0,0,93,1016,0,64,0,0,5,105,110,82,117,110,1,0,
2979,0,0,0,0,0,93,1017,0,64,1,1,5,105,110,82,117,110,1,0,3329,3,0,0,
3003,0,0,0,0,0,93,1018,0,64,1,1,5,105,110,82,117,110,1,0,3329,3,0,0,
3027,0,0,0,0,0,93,1019,0,64,1,1,5,105,110,82,117,110,1,0,3329,3,0,0,
3051,0,0,0,0,0,93,1020,0,64,1,1,5,105,110,82,117,110,1,0,3329,3,0,0,
3075,0,0,0,0,0,93,1021,0,64,1,1,5,105,110,82,117,110,1,0,3329,3,0,0,
3099,0,0,0,0,0,93,1022,0,64,1,1,5,105,110,82,117,110,1,0,3329,3,0,0,
3123,0,0,0,0,0,93,1023,0,64,1,1,5,105,110,82,117,110,1,0,3329,3,0,0,
3147,0,0,0,0,0,93,1024,0,64,1,1,5,105,110,82,117,110,1,0,3329,3,0,0,
3171,0,0,0,0,0,93,1025,0,64,1,1,5,105,110,82,117,110,1,0,3329,4,0,0,
3195,0,0,0,0,0,93,1026,0,64,1,1,5,105,110,82,117,110,1,0,3329,4,0,0,
3219,0,0,0,0,0,93,1027,0,64,1,1,5,105,110,82,117,110,1,0,3329,4,0,0,
3243,0,0,0,0,0,93,1028,0,64,1,1,5,105,110,82,117,110,1,0,3329,4,0,0,
3267,0,0,0,0,0,93,1029,0,64,1,1,5,105,110,82,117,110,1,0,3329,4,0,0,
3291,0,0,0,0,0,93,1030,0,64,1,1,5,105,110,82,117,110,1,0,3329,4,0,0,
3315,0,0,0,0,0,93,1031,0,64,1,1,5,105,110,82,117,110,1,0,3329,4,0,0,
3339,0,0,0,0,0,93,1032,0,64,1,1,5,105,110,82,117,110,1,0,3329,4,0,0,
3363,0,0,13,0,0,17,1034,0,0,1,1,0,1,0,1,97,0,0,
3382,0,0,13,0,0,23,1035,0,64,0,0,5,105,110,82,117,110,1,0,
3402,0,0,15,0,0,24,1052,0,0,1,1,0,1,0,1,97,0,0,
3421,0,0,0,0,0,91,1059,0,64,0,0,5,105,110,82,117,110,1,0,
3441,0,0,16,0,0,24,1063,0,0,1,1,0,1,0,1,97,0,0,
3460,0,0,17,0,0,24,1072,0,0,1,1,0,1,0,1,97,0,0,
3479,0,0,0,0,0,90,1156,0,64,0,0,6,105,110,73,78,84,78,1,0,
3500,0,0,0,0,0,93,1182,0,64,0,0,6,105,110,73,78,84,78,1,0,
3521,0,0,0,0,0,93,1183,0,64,1,1,6,105,110,73,78,84,78,1,0,3329,3,0,0,
3546,0,0,0,0,0,93,1184,0,64,1,1,6,105,110,73,78,84,78,1,0,3329,3,0,0,
3571,0,0,0,0,0,93,1185,0,64,1,1,6,105,110,73,78,84,78,1,0,3329,3,0,0,
3596,0,0,0,0,0,93,1186,0,64,1,1,6,105,110,73,78,84,78,1,0,3329,3,0,0,
3621,0,0,0,0,0,93,1187,0,64,1,1,6,105,110,73,78,84,78,1,0,3329,3,0,0,
3646,0,0,0,0,0,93,1188,0,64,1,1,6,105,110,73,78,84,78,1,0,3329,3,0,0,
3671,0,0,0,0,0,93,1189,0,64,1,1,6,105,110,73,78,84,78,1,0,3329,4,0,0,
3696,0,0,0,0,0,93,1190,0,64,1,1,6,105,110,73,78,84,78,1,0,3329,4,0,0,
3721,0,0,13,0,0,17,1191,0,0,1,1,0,1,0,1,97,0,0,
3740,0,0,13,0,0,23,1192,0,64,0,0,6,105,110,73,78,84,78,1,0,
3761,0,0,0,0,0,91,1211,0,64,0,0,6,105,110,73,78,84,78,1,0,
3782,0,0,0,0,0,90,1268,0,64,0,0,6,105,110,73,78,84,87,1,0,
3803,0,0,0,0,0,93,1297,0,64,0,0,6,105,110,73,78,84,87,1,0,
3824,0,0,0,0,0,93,1298,0,64,1,1,6,105,110,73,78,84,87,1,0,3329,3,0,0,
3849,0,0,0,0,0,93,1299,0,64,1,1,6,105,110,73,78,84,87,1,0,3329,3,0,0,
3874,0,0,0,0,0,93,1300,0,64,1,1,6,105,110,73,78,84,87,1,0,3329,3,0,0,
3899,0,0,0,0,0,93,1301,0,64,1,1,6,105,110,73,78,84,87,1,0,3329,3,0,0,
3924,0,0,0,0,0,93,1302,0,64,1,1,6,105,110,73,78,84,87,1,0,3329,3,0,0,
3949,0,0,0,0,0,93,1303,0,64,1,1,6,105,110,73,78,84,87,1,0,3329,3,0,0,
3974,0,0,0,0,0,93,1304,0,64,1,1,6,105,110,73,78,84,87,1,0,3329,3,0,0,
3999,0,0,0,0,0,93,1305,0,64,1,1,6,105,110,73,78,84,87,1,0,3329,4,0,0,
4024,0,0,13,0,0,17,1306,0,0,1,1,0,1,0,1,97,0,0,
4043,0,0,13,0,0,23,1307,0,64,0,0,6,105,110,73,78,84,87,1,0,
4064,0,0,0,0,0,91,1326,0,64,0,0,6,105,110,73,78,84,87,1,0,
4085,0,0,0,0,0,90,1392,0,64,0,0,5,105,110,78,78,80,1,0,
4105,0,0,0,0,0,93,1426,0,64,0,0,5,105,110,78,78,80,1,0,
4125,0,0,0,0,0,93,1427,0,64,1,1,5,105,110,78,78,80,1,0,3329,3,0,0,
4149,0,0,0,0,0,93,1428,0,64,1,1,5,105,110,78,78,80,1,0,3329,3,0,0,
4173,0,0,0,0,0,93,1429,0,64,1,1,5,105,110,78,78,80,1,0,3329,3,0,0,
4197,0,0,0,0,0,93,1430,0,64,1,1,5,105,110,78,78,80,1,0,3329,3,0,0,
4221,0,0,0,0,0,93,1431,0,64,1,1,5,105,110,78,78,80,1,0,3329,3,0,0,
4245,0,0,0,0,0,93,1432,0,64,1,1,5,105,110,78,78,80,1,0,3329,3,0,0,
4269,0,0,0,0,0,93,1433,0,64,1,1,5,105,110,78,78,80,1,0,3329,3,0,0,
4293,0,0,0,0,0,93,1434,0,64,1,1,5,105,110,78,78,80,1,0,3329,4,0,0,
4317,0,0,0,0,0,93,1435,0,64,1,1,5,105,110,78,78,80,1,0,3329,4,0,0,
4341,0,0,0,0,0,93,1436,0,64,1,1,5,105,110,78,78,80,1,0,3329,4,0,0,
4365,0,0,0,0,0,93,1437,0,64,1,1,5,105,110,78,78,80,1,0,3329,3,0,0,
4389,0,0,0,0,0,93,1438,0,64,1,1,5,105,110,78,78,80,1,0,3329,3,0,0,
4413,0,0,0,0,0,93,1439,0,64,1,1,5,105,110,78,78,80,1,0,3329,4,0,0,
4437,0,0,0,0,0,93,1440,0,64,1,1,5,105,110,78,78,80,1,0,3329,4,0,0,
4461,0,0,0,0,0,93,1441,0,64,1,1,5,105,110,78,78,80,1,0,3329,4,0,0,
4485,0,0,13,0,0,17,1442,0,0,1,1,0,1,0,1,97,0,0,
4504,0,0,13,0,0,23,1443,0,64,0,0,5,105,110,78,78,80,1,0,
4524,0,0,0,0,0,91,1468,0,64,0,0,5,105,110,78,78,80,1,0,
4544,0,0,18,0,0,17,1505,0,0,1,1,0,1,0,1,97,0,0,
4563,0,0,18,0,0,45,1507,0,0,0,0,0,1,0,
4578,0,0,18,0,0,13,1513,0,0,11,0,0,1,0,2,3,0,0,2,3,0,0,2,97,0,0,2,3,0,0,2,3,0,
0,2,3,0,0,2,4,0,0,2,4,0,0,2,3,0,0,2,4,0,0,2,4,0,0,
4637,0,0,18,0,0,15,1526,0,0,0,0,0,1,0,
4652,0,0,19,0,0,17,1569,0,0,1,1,0,1,0,1,97,0,0,
4671,0,0,19,0,0,45,1571,0,0,0,0,0,1,0,
4686,0,0,19,0,0,13,1573,0,0,4,0,0,1,0,2,3,0,0,2,3,0,0,2,3,0,0,2,4,0,0,
4717,0,0,19,0,0,15,1586,0,0,0,0,0,1,0,
4732,0,0,20,0,0,17,1626,0,0,1,1,0,1,0,1,97,0,0,
4751,0,0,20,0,0,45,1628,0,0,0,0,0,1,0,
4766,0,0,20,0,0,13,1629,0,0,5,0,0,1,0,2,3,0,0,2,3,0,0,2,3,0,0,2,3,0,0,2,4,0,0,
4801,0,0,20,0,0,15,1635,0,0,0,0,0,1,0,
4816,0,0,21,0,0,17,1671,0,0,1,1,0,1,0,1,97,0,0,
4835,0,0,21,0,0,45,1673,0,0,0,0,0,1,0,
4850,0,0,21,0,0,13,1674,0,0,1,0,0,1,0,2,97,0,0,
4869,0,0,21,0,0,15,1679,0,0,0,0,0,1,0,
4884,0,0,22,0,0,17,1690,0,0,1,1,0,1,0,1,97,0,0,
4903,0,0,22,0,0,45,1692,0,0,0,0,0,1,0,
4918,0,0,22,0,0,13,1693,0,0,1,0,0,1,0,2,3,0,0,
4937,0,0,22,0,0,15,1698,0,0,0,0,0,1,0,
4952,0,0,23,0,0,17,1743,0,0,1,1,0,1,0,1,97,0,0,
4971,0,0,23,0,0,45,1745,0,0,0,0,0,1,0,
4986,0,0,23,0,0,13,1752,0,0,3,0,0,1,0,2,97,0,0,2,3,0,0,2,97,0,0,
5013,0,0,23,0,0,15,1762,0,0,0,0,0,1,0,
5028,0,0,24,0,0,17,1775,0,0,1,1,0,1,0,1,97,0,0,
5047,0,0,24,0,0,45,1777,0,0,0,0,0,1,0,
5062,0,0,24,0,0,13,1782,0,0,1,0,0,1,0,2,97,0,0,
5081,0,0,24,0,0,15,1788,0,0,0,0,0,1,0,
5096,0,0,25,0,0,17,1800,0,0,1,1,0,1,0,1,97,0,0,
5115,0,0,25,0,0,45,1802,0,0,0,0,0,1,0,
5130,0,0,25,0,0,13,1808,0,0,1,0,0,1,0,2,97,0,0,
5149,0,0,25,0,0,15,1815,0,0,0,0,0,1,0,
5164,0,0,18,0,0,17,1827,0,0,1,1,0,1,0,1,97,0,0,
5183,0,0,18,0,0,45,1829,0,0,0,0,0,1,0,
5198,0,0,18,0,0,13,1830,0,0,1,0,0,1,0,2,3,0,0,
5217,0,0,18,0,0,15,1838,0,0,0,0,0,1,0,
5232,0,0,26,0,0,17,1866,0,0,1,1,0,1,0,1,97,0,0,
5251,0,0,26,0,0,45,1868,0,0,0,0,0,1,0,
5266,0,0,26,0,0,13,1870,0,0,6,0,0,1,0,2,97,0,0,2,4,0,0,2,4,0,0,2,4,0,0,2,4,0,0,
2,4,0,0,
5305,0,0,26,0,0,15,1883,0,0,0,0,0,1,0,
5320,0,0,27,0,0,17,1908,0,0,1,1,0,1,0,1,97,0,0,
5339,0,0,27,0,0,45,1910,0,0,0,0,0,1,0,
5354,0,0,27,0,0,13,1912,0,0,9,0,0,1,0,2,97,0,0,2,4,0,0,2,4,0,0,2,4,0,0,2,4,0,0,
2,4,0,0,2,4,0,0,2,4,0,0,2,4,0,0,
5405,0,0,27,0,0,15,1931,0,0,0,0,0,1,0,
5420,0,0,28,52,0,1,2018,0,0,0,0,0,1,0,
5435,0,0,29,0,0,24,2019,0,0,1,1,0,1,0,1,97,0,0,
5454,0,0,30,0,0,29,2022,0,0,0,0,0,1,0,
5469,0,0,0,0,0,58,2037,0,0,1,1,0,1,0,3,109,0,0,
5488,0,0,0,0,0,60,2043,0,0,0,0,0,1,0,
5503,0,0,31,0,0,30,2051,0,0,0,0,0,1,0,
5518,0,0,0,0,0,59,2052,0,0,1,1,0,1,0,3,109,0,0,
};


#include <vld.h>

#include <sqlca.h>
#include <time.h>
#include <Windows.h>

#include <MyLogDefs.h>

#include <MyWNN.h>
#include <MyNN.h>
#include <MySOM.h>
#include <MySVM.h>
#include <MyGA.h>

#include <Concordance.h>

/*#include <FXData.h>
#include <DataShape.h>
#include <FileData.h>

*/

#undef EXPORT
#ifdef __cplusplus
#define EXPORT extern "C" __declspec(dllexport)
#else
#define EXPORT __declspec(dllexport)
#endif

#define MAX_CONTEXTS 6
// Forecast High/Low (replaces OutputType)
#define FH 1	
#define FL 0

//--
char* __stdcall timestamp_C(){
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
void  __stdcall Trim_C(char* str){
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
void  __stdcall LogWrite_C(tDebugInfo* DebugParms, int LogType, char* msg, int argcount, ...){
	// pLogLevel=	0 (No screen, No file) | 1 (Screen, No file) | 2 (Screen AND File)
	int n;
	char*			arg_s;
	int				arg_d;
	double			arg_f;
	//long			arg_l;
	va_list			arguments;
	//char*			submsg=(char*)malloc(strlen(msg));
	char submsg[MAX_PATH];
	char fullfname[MAX_PATH];
	unsigned int	im = 0;
	int				prev_im = 0;
	//HANDLE			FileMutex;
	//HANDLE			ScreenMutex;

	if (DebugParms->DebugLevel == 0 && LogType == LOG_INFO) return;
	//if (DebugParms->DebugLevel >1){
	if (DebugParms->fIsOpen != 1){
		strcpy(fullfname, DebugParms->fPath); strcat(fullfname, "/"); strcat(fullfname, DebugParms->fName);
		DebugParms->fHandle = fopen(fullfname, "w");
		DebugParms->fIsOpen = 1;
	}
	//}

	va_start(arguments, argcount);
	n = 0;

	//ScreenMutex=CreateMutex(NULL, FALSE, NULL);
	//FileMutex=  CreateMutex(NULL, FALSE, NULL);

	//	while(FileMutex==NULL) FileMutex=CreateMutex(NULL, TRUE, NULL);
	//	WaitForSingleObject(FileMutex, INFINITE);

	do {
		if (msg[im] == 37){                // "%"
			memcpy(submsg, &msg[prev_im], (im - prev_im + 2)); submsg[im - prev_im + 2] = '\0';
			n++;
			prev_im = im + 2;
			if (msg[im + 1] == 115){   // "s"
				arg_s = va_arg(arguments, char*);
				if (DebugParms->DebugLevel == 1 || DebugParms->DebugLevel == 3 || LogType == LOG_ERROR) printf(submsg, arg_s);
				if (DebugParms->DebugLevel == 2 || DebugParms->DebugLevel == 3 || LogType == LOG_ERROR)	fprintf(DebugParms->fHandle, submsg, arg_s);
			}
			else if (msg[im + 1] == 100){   // "d"
				arg_d = va_arg(arguments, int);
				if (DebugParms->DebugLevel == 1 || DebugParms->DebugLevel == 3 || LogType == LOG_ERROR) printf(submsg, arg_d);
				if (DebugParms->DebugLevel == 2 || DebugParms->DebugLevel == 3 || LogType == LOG_ERROR)	fprintf(DebugParms->fHandle, submsg, arg_d);
			}
			else if (msg[im + 1] == 112){   // "p"
				arg_d = va_arg(arguments, long);
				if (DebugParms->DebugLevel == 1 || DebugParms->DebugLevel == 3 || LogType == LOG_ERROR) printf(submsg, arg_d);
				if (DebugParms->DebugLevel == 2 || DebugParms->DebugLevel == 3 || LogType == LOG_ERROR)	fprintf(DebugParms->fHandle, submsg, arg_d);
			}
			else                   {   // this could be 67 ("f") or any mask before "f" -> in any case, it's a double
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
	if (LogType == LOG_ERROR) system("pause");
	va_end(arguments);
}
//--

//=== DB common functions
EXPORT int  __stdcall OraConnect(tDebugInfo* DebugInfo, tDBConnection* DBConnInfo){

	/* EXEC SQL BEGIN DECLARE SECTION; */ 

	char* username = DBConnInfo->DBUser;
	char* password = DBConnInfo->DBPassword;
	char* dbstring = DBConnInfo->DBConnString;
	sql_context vCtx = NULL;
	/* EXEC SQL END DECLARE SECTION; */ 


	//LogWrite_C(DebugParms, "%s About to execute connect with %s , %s , %s\n", 4, timestamp_C, pUserName, pPassword, pDBString);

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
		//memcpy(DBConnInfo->Ctx, vCtx, sizeof(sql_context));
		DBConnInfo->DBCtx = vCtx;
		DebugInfo->DBCtx = vCtx;
		LogWrite_C(DebugInfo, LOG_INFO, "OraConnect() - Connected to ORACLE as user: %s ; DBConnInfo->DBCtx=%p\n", 2, username, DBConnInfo->DBCtx);
	}
	else {
		LogWrite_C(DebugInfo, LOG_ERROR, "%s Error %d connecting to ORACLE as user: %s\n", 3, timestamp_C(), sqlca.sqlcode, DBConnInfo->DBUser);
		LogWrite_C(DebugInfo, LOG_ERROR, "PATH=%s\n", 1, vPath);
		LogWrite_C(DebugInfo, LOG_ERROR, "ORACLE_HOME=%s\n", 1, vOH);
		system("pause");
	}
	return(sqlca.sqlcode);
}
EXPORT void __stdcall OraDisconnect(sql_context pCtx) {
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
EXPORT void __stdcall OraCommit(void* pCtx) {
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
//===

//=== Basic Logs
EXPORT int __stdcall Ora_InsertTesterParms(tDebugInfo* DebugParms, int pSimulationLen, char* pSimulationStart, double pElapsedSecs, int pTesterEngine, int pDoTraining, int pDoRun, int pDataSourceType, char* pDataSourceFileName) {
	/* EXEC SQL BEGIN DECLARE SECTION; */ 

	sql_context vCtx = DebugParms->DebugDB->DBCtx;
	char stmt[1000];
	/* EXEC SQL END DECLARE SECTION; */ 


	//-- Connects to DB only once
	if (vCtx == NULL) {
		if (OraConnect(DebugParms, DebugParms->DebugDB) != 0) {
			printf("WriteTesterLog could not connect to Log Database...\n");
			return -1;
		}
		vCtx = DebugParms->DebugDB->DBCtx;
	}
	//-- Builds Insert statement
	sprintf(&stmt[0], "insert into TesterParms(ProcessId, TesterStart,	SimulationLen,	Duration, 	  SimulationStart,					Engine,			DoTraining, DoRun, DataSourceType, DataSourceFileName) \
						values(					%d,			sysdate,	%d,				%f,			  to_date('%s','YYYYMMDDHH24MI'),	 %d,			%d,			%d,			%d,			'%s')",
		GetCurrentProcessId(), pSimulationLen, pElapsedSecs, pSimulationStart, pTesterEngine, pDoTraining, pDoRun, pDataSourceType, pDataSourceFileName);
	//-- Executes Insert statements
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
 sqlstm.offset = (unsigned int  )85;
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
		if (sqlca.sqlcode != 1) LogWrite_C(DebugParms, LOG_ERROR, "WriteTesterLog failed. SQL Error %d\n", 1, sqlca.sqlcode);
		return sqlca.sqlcode;
	}
	return 0;
}
EXPORT int __stdcall Ora_InsertDataParms  (tDebugInfo* pDebugParms, int pid, int pTestId, int pDatasetId, int pDSType, char* pDSFileName, char* pSymbol, char* pTimeFrame, int pIsFilled, int pBarData, int pDataTransformation, double pwiggleRoom, int pHistoryLen, int pSampleLen, int pPredictionLen) {
	/* EXEC SQL BEGIN DECLARE SECTION; */ 

	sql_context vCtx = pDebugParms->DebugDB->DBCtx;
	char stmt[1000];
	/* EXEC SQL END   DECLARE SECTION; */ 


	if (vCtx == NULL) {
		if (OraConnect(pDebugParms, pDebugParms->DebugDB) != 0) LogWrite_C(pDebugParms, LOG_ERROR, "Ora_InsertDataParms() could not connect to Log Database...\n", 0);
		vCtx = pDebugParms->DebugDB->DBCtx;
	}
	LogWrite_C(pDebugParms, LOG_INFO, "Ora_InsertDataParms() CheckPoint 2 - LogDB->DBCtx=%p , vCtx=%p\n", 2, pDebugParms->DebugDB->DBCtx, vCtx);

	sprintf(&stmt[0], "insert into DataParms (ProcessId, DatasetId, TestId, DatasourceType, DatasourceFileName, Symbol, Timeframe, IsFilled, BarData, DataTransformation, WiggleRoom, HistoryLen, SampleLen, PredictionLen)\
					  values				(%d,			%d,		%d,			%d,				'%s',					'%s',		'%s',		%d,			%d,		%d,					%f,			%d,			%d,			%d)", \
		pid, pDatasetId, pTestId, pDSType, pDSFileName, pSymbol, pTimeFrame, pIsFilled, pBarData, pDataTransformation, pwiggleRoom, pHistoryLen, pSampleLen, pPredictionLen);
	/* EXEC SQL EXECUTE IMMEDIATE : stmt; */ 

{
 struct sqlexd sqlstm;
 sqlstm.sqlvsn = 13;
 sqlstm.arrsiz = 4;
 sqlstm.sqladtp = &sqladt;
 sqlstm.sqltdsp = &sqltds;
 sqlstm.stmt = "";
 sqlstm.iters = (unsigned int  )1;
 sqlstm.offset = (unsigned int  )104;
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
		LogWrite_C(pDebugParms, LOG_ERROR, "Ora_InsertDataParms() Insert into DataParms failed. SQL Error %d\n", 1, sqlca.sqlcode);
		return sqlca.sqlcode;
	}

	return 0;
}
EXPORT int __stdcall Ora_InsertEngineParms(tDebugInfo* pDebugParms, int pid, int pTestId, int pEngineType, int pLayersCount, int pWNNDecompLevel, char* pWNNWaveletType) {
	/* EXEC SQL BEGIN DECLARE SECTION; */ 

	sql_context vCtx = pDebugParms->DebugDB->DBCtx;
	char stmt[1000];
	/* EXEC SQL END   DECLARE SECTION; */ 


	if (vCtx == NULL) {
		if (OraConnect(pDebugParms, pDebugParms->DebugDB) != 0) LogWrite_C(pDebugParms, LOG_ERROR, "Ora_InsertEngineParms() could not connect to Log Database...\n", 0);
		vCtx = pDebugParms->DebugDB->DBCtx;
	}
	LogWrite_C(pDebugParms, LOG_INFO, "Ora_InsertEngineParms() CheckPoint 2 - LogDB->DBCtx=%p , vCtx=%p\n", 2, pDebugParms->DebugDB->DBCtx, vCtx);

	//-- 1. Insert into EngineParms
	sprintf(&stmt[0], "insert into EngineParms(ProcessId, TestId, EngineType, LayersCount, WNN_DecompLevel, WNN_WaveletType) values(%d, %d, %d, %d, %d, '%s')",	pid, pTestId, pEngineType, pLayersCount, pWNNDecompLevel, pWNNWaveletType);
	/* EXEC SQL EXECUTE IMMEDIATE : stmt; */ 

{
 struct sqlexd sqlstm;
 sqlstm.sqlvsn = 13;
 sqlstm.arrsiz = 4;
 sqlstm.sqladtp = &sqladt;
 sqlstm.sqltdsp = &sqltds;
 sqlstm.stmt = "";
 sqlstm.iters = (unsigned int  )1;
 sqlstm.offset = (unsigned int  )123;
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
		LogWrite_C(pDebugParms, LOG_ERROR, "Ora_InsertEngineParms() Insert into EngineParms failed. SQL Error %d\n", 1, sqlca.sqlcode);
		return sqlca.sqlcode;
	}

	return 0;
}
//--
EXPORT int __stdcall Ora_InsertCoreParms_NN(tDebugInfo* DebugParms, int pid, int pTestId, int pLayerId, int pCoreId, NN_Parms* NNParms) {
	/* EXEC SQL BEGIN DECLARE SECTION; */ 

	sql_context vCtx = DebugParms->DebugDB->DBCtx;
	char stmt[1000];
	/* EXEC SQL END DECLARE SECTION; */ 


	//-- Connects to DB only once
	if (vCtx == NULL) {
		if (OraConnect(DebugParms, DebugParms->DebugDB) != 0) {
			printf("Ora_InsertCoreParms_NN could not connect to Log Database...\n");
			return -1;
		}
		vCtx = DebugParms->DebugDB->DBCtx;
	}
	//-- Builds Insert statement
	sprintf(&stmt[0], "insert into CoreParms_NN(ProcessId, TestId, LayerId, CoreId, InputCount, OutputCount, LevelsCount, LevelRatioS, MaxEpochs, TargetMSE, UseContext, BP_Algo, TrainingProtocol, StopAtDivergence, LearningRate, LearningMomentum, ActivationFunction, HCPbeta, Mu) values(%d, %d, %d, %d, %d, %d, %d, '%s', %d, %f, %d, %d, %d, %d, %f, %f, %d, %f, %f)", pid, pTestId, pLayerId, pCoreId, NNParms->InputCount, NNParms->OutputCount, NNParms->LevelsCount, NNParms->LevelRatioS, NNParms->MaxEpochs, NNParms->TargetMSE, NNParms->UseContext, NNParms->BP_Algo, NNParms->TrainingProtocol, NNParms->StopAtDivergence, NNParms->LearningRate, NNParms->LearningMomentum, NNParms->ActivationFunction, NNParms->HCPbeta, NNParms->mu);
	//-- Executes Insert statements
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
 sqlstm.offset = (unsigned int  )142;
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
		if (sqlca.sqlcode != 1) LogWrite_C(DebugParms, LOG_ERROR, "Ora_InsertCoreParms_NN failed. SQL Error %d\n", 1, sqlca.sqlcode);
		return sqlca.sqlcode;
	}
	return 0;
}
EXPORT int __stdcall Ora_InsertCoreParms_SOM(tDebugInfo* DebugParms, int pid, int pTestId, int pLayerId, int pCoreId, SOM_Parms* SOMParms) {
	/* EXEC SQL BEGIN DECLARE SECTION; */ 

	sql_context vCtx = DebugParms->DebugDB->DBCtx;
	char stmt[1000];
	/* EXEC SQL END DECLARE SECTION; */ 


	//-- Connects to DB only once
	if (vCtx == NULL) {
		if (OraConnect(DebugParms, DebugParms->DebugDB) != 0) {
			printf("Ora_InsertCoreParms_SOM() could not connect to Log Database...\n");
			return -1;
		}
		vCtx = DebugParms->DebugDB->DBCtx;
	}
	//-- Builds Insert statement
	sprintf(&stmt[0], "insert into EngineParms_SOM	(ProcessId, TestId, LayerId, CoreId, InputCount, OutputCount, MaxEpochs, TDFunction, BaseTD, LRFunction, BaseLR) values(%d, %d, %d, %d, %d, %d, %d, %d, %f, %d, %f )", pid, pTestId, pLayerId, pCoreId, SOMParms->InputCount, SOMParms->OutputCount, SOMParms->MaxEpochs, SOMParms->TDFunction, SOMParms->BaseTD, SOMParms->LRFunction, SOMParms->BaseLR);

	//-- Executes Insert statements
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
 sqlstm.offset = (unsigned int  )161;
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
		if (sqlca.sqlcode != 1) LogWrite_C(DebugParms, LOG_ERROR, "Ora_InsertCoreParms_SOM() failed. SQL Error %d\n", 1, sqlca.sqlcode);
		return sqlca.sqlcode;
	}
	return 0;

}
EXPORT int __stdcall Ora_InsertCoreParms_SVM(tDebugInfo* DebugParms, int pid, int pTestId, int pLayerId, int pCoreId, SVM_Parms* SVMParms) {
	/* EXEC SQL BEGIN DECLARE SECTION; */ 

	sql_context vCtx = DebugParms->DebugDB->DBCtx;
	char stmt[1000];
	/* EXEC SQL END DECLARE SECTION; */ 


	//-- Connects to DB only once
	if (vCtx == NULL) {
		if (OraConnect(DebugParms, DebugParms->DebugDB) != 0) {
			printf("Ora_InsertCoreParms_SVM() could not connect to Log Database...\n");
			return -1;
		}
		vCtx = DebugParms->DebugDB->DBCtx;
	}
	//-- Builds Insert statement
	sprintf(&stmt[0], "insert into CoreParms_SVM	(ProcessId, TestId, LayerId, CoreId, InputCount, MaxEpochs, C, Epsilon, IterToShrink, KernelType, PolyDegree, RBFGamma, CoefLin, CoefConst, KernelCacheSize)\
												 values(%d, %d, %d, %d, %d, %d, %f, %f, %d, %d, %d, %f, %f, %f, %d)",\
												pid, pTestId, pLayerId, pCoreId, SVMParms->InputCount, SVMParms->MaxEpochs, SVMParms->C, SVMParms->epsilon, SVMParms->svmIterToShrink, SVMParms->KernelType, SVMParms->PolyDegree, SVMParms->RBFGamma, SVMParms->CoefLin, SVMParms->CoefConst, SVMParms->KernelCacheSize);

	//-- Executes Insert statements
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
 sqlstm.offset = (unsigned int  )180;
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
		if (sqlca.sqlcode != 1) LogWrite_C(DebugParms, LOG_ERROR, "Ora_InsertCoreParms_SVM() failed. SQL Error %d\n", 1, sqlca.sqlcode);
		return sqlca.sqlcode;
	}
	return 0;

}

//--
EXPORT int __stdcall Ora_InsertCoreImage_NN(tDebugInfo* DebugParms, int pLayerId, int pCoreId, int pDatasetId, int pTestId, NN_Parms* NNParms, tNNWeight*** NNWeight) {
	/* EXEC SQL BEGIN DECLARE SECTION; */ 

	int i, l, fn, tn;
	sql_context vCtx = DebugParms->DebugDB->DBCtx;
	char stmt[1000];
	int vInsertCount = NNParms->WeightsCountTotal;
	int* vProcessId;
	int* vThreadId;
	int* vTestId;
	int* vLayerId;
	int* vCoreId;
	int* vDatasetId;
	int* vNeuronLevel;
	int* vFromNeuron;
	int* vToNeuron;
	double* vWeight;
	double* vCtxValue;
	int dbl_type = 22;	// Oracle SQLT_BDOUBLE
	int int_type = 3;	// 
	unsigned int dbl_len = sizeof(double);
	/* EXEC SQL END DECLARE SECTION; */ 


	//-- Connects to DB only once
	if (vCtx == NULL) {
		if (OraConnect(DebugParms, DebugParms->DebugDB) != 0) printf("Ora_BulkWeightInsert_NN() could not connect to Log Database...\n");
		vCtx = DebugParms->DebugDB->DBCtx;
	}

	vProcessId = (int*)malloc(vInsertCount * sizeof(int));
	vThreadId = (int*)malloc(vInsertCount * sizeof(int));
	vTestId = (int*)malloc(vInsertCount * sizeof(int));
	vLayerId = (int*)malloc(vInsertCount * sizeof(int));
	vCoreId = (int*)malloc(vInsertCount * sizeof(int));
	vDatasetId = (int*)malloc(vInsertCount * sizeof(int));
	vNeuronLevel = (int*)malloc(vInsertCount * sizeof(int));
	vFromNeuron = (int*)malloc(vInsertCount * sizeof(int));
	vToNeuron = (int*)malloc(vInsertCount * sizeof(int));
	vWeight = (double*)malloc(vInsertCount * sizeof(double));
	vCtxValue = (double*)malloc(vInsertCount * sizeof(double));

	i = 0;
	for (l = 0; l < (NNParms->LevelsCount - 1); l++) {
		for (fn = 0; fn < NNParms->NodesCount[l + 1]; fn++) {
			for (tn = 0; tn < NNParms->NodesCount[l]; tn++) {
				vLayerId[i] = pLayerId;
				vCoreId[i] = pCoreId;
				vDatasetId[i] = pDatasetId;
				vTestId[i] = pTestId;
				vProcessId[i] = NNWeight[l][fn][tn].ProcessId;
				vThreadId[i] = NNWeight[l][fn][tn].ThreadId;
				vNeuronLevel[i] = NNWeight[l][fn][tn].NeuronLevel;
				vFromNeuron[i] = NNWeight[l][fn][tn].FromNeuron;
				vToNeuron[i] = NNWeight[l][fn][tn].ToNeuron;
				vWeight[i] = NNWeight[l][fn][tn].Weight;
				vCtxValue[i] = NNWeight[l][fn][tn].CtxValue;
				i++;
			}
		}
	}
	//-- Then, Build the Insert statement
	sprintf(&stmt[0], "insert into CoreImage_NN (ProcessId, ThreadId, TestId, LayerId, CoreId, DatasetId, NeuronLevel, FromNeuron, ToNeuron, Weight, CtxValue)");
	strcat(stmt, " values(:WNN01, :WNN02, :WNN03, :WNN04, :WNN05, :WNN06, :WNN07, :WNN08, :WNN09, :WNN10, :WNN11)");

	/* EXEC SQL CONTEXT USE : vCtx; */ 

	/* EXEC SQL FOR : vInsertCount ALLOCATE DESCRIPTOR 'WNN'; */ 

{
 struct sqlexd sqlstm;
 sqlstm.sqlvsn = 13;
 sqlstm.arrsiz = 4;
 sqlstm.sqladtp = &sqladt;
 sqlstm.sqltdsp = &sqltds;
 sqlstm.stmt = "";
 sqlstm.iters = (unsigned int  )vInsertCount;
 sqlstm.offset = (unsigned int  )199;
 sqlstm.cud = sqlcud0;
 sqlstm.sqlest = (unsigned char  *)&sqlca;
 sqlstm.sqlety = (unsigned short)4352;
 sqlstm.occurs = (unsigned int  )100;
 sqlcxt(&vCtx, &sqlctx, &sqlstm, &sqlfpn);
}


	/* EXEC SQL SET DESCRIPTOR 'WNN' COUNT = 11; */ 

{
 struct sqlexd sqlstm;
 sqlstm.sqlvsn = 13;
 sqlstm.arrsiz = 4;
 sqlstm.sqladtp = &sqladt;
 sqlstm.sqltdsp = &sqltds;
 sqlstm.stmt = "";
 sqlstm.iters = (unsigned int  )1;
 sqlstm.offset = (unsigned int  )217;
 sqlstm.cud = sqlcud0;
 sqlstm.sqlest = (unsigned char  *)&sqlca;
 sqlstm.sqlety = (unsigned short)4352;
 sqlstm.occurs = (unsigned int  )11;
 sqlcxt(&vCtx, &sqlctx, &sqlstm, &sqlfpn);
}


	/* EXEC SQL SET DESCRIPTOR 'WNN' VALUE 1 TYPE = :int_type; */ 

{
 struct sqlexd sqlstm;
 sqlstm.sqlvsn = 13;
 sqlstm.arrsiz = 4;
 sqlstm.sqladtp = &sqladt;
 sqlstm.sqltdsp = &sqltds;
 sqlstm.stmt = "";
 sqlstm.iters = (unsigned int  )1;
 sqlstm.offset = (unsigned int  )235;
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
 sqlstm.arrsiz = 4;
 sqlstm.sqladtp = &sqladt;
 sqlstm.sqltdsp = &sqltds;
 sqlstm.stmt = "";
 sqlstm.iters = (unsigned int  )1;
 sqlstm.offset = (unsigned int  )257;
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
 sqlstm.arrsiz = 4;
 sqlstm.sqladtp = &sqladt;
 sqlstm.sqltdsp = &sqltds;
 sqlstm.stmt = "";
 sqlstm.iters = (unsigned int  )1;
 sqlstm.offset = (unsigned int  )279;
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
 sqlstm.arrsiz = 4;
 sqlstm.sqladtp = &sqladt;
 sqlstm.sqltdsp = &sqltds;
 sqlstm.stmt = "";
 sqlstm.iters = (unsigned int  )1;
 sqlstm.offset = (unsigned int  )301;
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
 sqlstm.arrsiz = 4;
 sqlstm.sqladtp = &sqladt;
 sqlstm.sqltdsp = &sqltds;
 sqlstm.stmt = "";
 sqlstm.iters = (unsigned int  )1;
 sqlstm.offset = (unsigned int  )323;
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


	/* EXEC SQL SET DESCRIPTOR 'WNN' VALUE 6 TYPE = :int_type; */ 

{
 struct sqlexd sqlstm;
 sqlstm.sqlvsn = 13;
 sqlstm.arrsiz = 4;
 sqlstm.sqladtp = &sqladt;
 sqlstm.sqltdsp = &sqltds;
 sqlstm.stmt = "";
 sqlstm.iters = (unsigned int  )1;
 sqlstm.offset = (unsigned int  )345;
 sqlstm.cud = sqlcud0;
 sqlstm.sqlest = (unsigned char  *)&sqlca;
 sqlstm.sqlety = (unsigned short)4352;
 sqlstm.occurs = (unsigned int  )6;
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


	/* EXEC SQL SET DESCRIPTOR 'WNN' VALUE 7 TYPE = :int_type; */ 

{
 struct sqlexd sqlstm;
 sqlstm.sqlvsn = 13;
 sqlstm.arrsiz = 4;
 sqlstm.sqladtp = &sqladt;
 sqlstm.sqltdsp = &sqltds;
 sqlstm.stmt = "";
 sqlstm.iters = (unsigned int  )1;
 sqlstm.offset = (unsigned int  )367;
 sqlstm.cud = sqlcud0;
 sqlstm.sqlest = (unsigned char  *)&sqlca;
 sqlstm.sqlety = (unsigned short)4352;
 sqlstm.occurs = (unsigned int  )7;
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


	/* EXEC SQL SET DESCRIPTOR 'WNN' VALUE 8 TYPE = :int_type; */ 

{
 struct sqlexd sqlstm;
 sqlstm.sqlvsn = 13;
 sqlstm.arrsiz = 4;
 sqlstm.sqladtp = &sqladt;
 sqlstm.sqltdsp = &sqltds;
 sqlstm.stmt = "";
 sqlstm.iters = (unsigned int  )1;
 sqlstm.offset = (unsigned int  )389;
 sqlstm.cud = sqlcud0;
 sqlstm.sqlest = (unsigned char  *)&sqlca;
 sqlstm.sqlety = (unsigned short)4352;
 sqlstm.occurs = (unsigned int  )8;
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


	/* EXEC SQL SET DESCRIPTOR 'WNN' VALUE 9 TYPE = :int_type; */ 

{
 struct sqlexd sqlstm;
 sqlstm.sqlvsn = 13;
 sqlstm.arrsiz = 4;
 sqlstm.sqladtp = &sqladt;
 sqlstm.sqltdsp = &sqltds;
 sqlstm.stmt = "";
 sqlstm.iters = (unsigned int  )1;
 sqlstm.offset = (unsigned int  )411;
 sqlstm.cud = sqlcud0;
 sqlstm.sqlest = (unsigned char  *)&sqlca;
 sqlstm.sqlety = (unsigned short)4352;
 sqlstm.occurs = (unsigned int  )9;
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


	/* EXEC SQL SET DESCRIPTOR 'WNN' VALUE 10 TYPE = :dbl_type; */ 

{
 struct sqlexd sqlstm;
 sqlstm.sqlvsn = 13;
 sqlstm.arrsiz = 4;
 sqlstm.sqladtp = &sqladt;
 sqlstm.sqltdsp = &sqltds;
 sqlstm.stmt = "";
 sqlstm.iters = (unsigned int  )1;
 sqlstm.offset = (unsigned int  )433;
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


	/* EXEC SQL SET DESCRIPTOR 'WNN' VALUE 11 TYPE = :dbl_type; */ 

{
 struct sqlexd sqlstm;
 sqlstm.sqlvsn = 13;
 sqlstm.arrsiz = 4;
 sqlstm.sqladtp = &sqladt;
 sqlstm.sqltdsp = &sqltds;
 sqlstm.stmt = "";
 sqlstm.iters = (unsigned int  )1;
 sqlstm.offset = (unsigned int  )455;
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



	/* EXEC SQL FOR : vInsertCount SET DESCRIPTOR 'WNN' VALUE 1 DATA = : vProcessId; */ 

{
 struct sqlexd sqlstm;
 sqlstm.sqlvsn = 13;
 sqlstm.arrsiz = 4;
 sqlstm.sqladtp = &sqladt;
 sqlstm.sqltdsp = &sqltds;
 sqlstm.stmt = "";
 sqlstm.iters = (unsigned int  )vInsertCount;
 sqlstm.offset = (unsigned int  )477;
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
 sqlstm.arrsiz = 4;
 sqlstm.sqladtp = &sqladt;
 sqlstm.sqltdsp = &sqltds;
 sqlstm.stmt = "";
 sqlstm.iters = (unsigned int  )vInsertCount;
 sqlstm.offset = (unsigned int  )499;
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


	/* EXEC SQL FOR : vInsertCount SET DESCRIPTOR 'WNN' VALUE 3 DATA = : vTestId; */ 

{
 struct sqlexd sqlstm;
 sqlstm.sqlvsn = 13;
 sqlstm.arrsiz = 4;
 sqlstm.sqladtp = &sqladt;
 sqlstm.sqltdsp = &sqltds;
 sqlstm.stmt = "";
 sqlstm.iters = (unsigned int  )vInsertCount;
 sqlstm.offset = (unsigned int  )521;
 sqlstm.cud = sqlcud0;
 sqlstm.sqlest = (unsigned char  *)&sqlca;
 sqlstm.sqlety = (unsigned short)4352;
 sqlstm.occurs = (unsigned int  )3;
 sqlstm.sqhstv[0] = (         void  *)vTestId;
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


	/* EXEC SQL FOR : vInsertCount SET DESCRIPTOR 'WNN' VALUE 4 DATA = : vLayerId; */ 

{
 struct sqlexd sqlstm;
 sqlstm.sqlvsn = 13;
 sqlstm.arrsiz = 4;
 sqlstm.sqladtp = &sqladt;
 sqlstm.sqltdsp = &sqltds;
 sqlstm.stmt = "";
 sqlstm.iters = (unsigned int  )vInsertCount;
 sqlstm.offset = (unsigned int  )543;
 sqlstm.cud = sqlcud0;
 sqlstm.sqlest = (unsigned char  *)&sqlca;
 sqlstm.sqlety = (unsigned short)4352;
 sqlstm.occurs = (unsigned int  )4;
 sqlstm.sqhstv[0] = (         void  *)vLayerId;
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


	/* EXEC SQL FOR : vInsertCount SET DESCRIPTOR 'WNN' VALUE 5 DATA = : vCoreId; */ 

{
 struct sqlexd sqlstm;
 sqlstm.sqlvsn = 13;
 sqlstm.arrsiz = 4;
 sqlstm.sqladtp = &sqladt;
 sqlstm.sqltdsp = &sqltds;
 sqlstm.stmt = "";
 sqlstm.iters = (unsigned int  )vInsertCount;
 sqlstm.offset = (unsigned int  )565;
 sqlstm.cud = sqlcud0;
 sqlstm.sqlest = (unsigned char  *)&sqlca;
 sqlstm.sqlety = (unsigned short)4352;
 sqlstm.occurs = (unsigned int  )5;
 sqlstm.sqhstv[0] = (         void  *)vCoreId;
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


	/* EXEC SQL FOR : vInsertCount SET DESCRIPTOR 'WNN' VALUE 6 DATA = : vDatasetId; */ 

{
 struct sqlexd sqlstm;
 sqlstm.sqlvsn = 13;
 sqlstm.arrsiz = 4;
 sqlstm.sqladtp = &sqladt;
 sqlstm.sqltdsp = &sqltds;
 sqlstm.stmt = "";
 sqlstm.iters = (unsigned int  )vInsertCount;
 sqlstm.offset = (unsigned int  )587;
 sqlstm.cud = sqlcud0;
 sqlstm.sqlest = (unsigned char  *)&sqlca;
 sqlstm.sqlety = (unsigned short)4352;
 sqlstm.occurs = (unsigned int  )6;
 sqlstm.sqhstv[0] = (         void  *)vDatasetId;
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


	/* EXEC SQL FOR : vInsertCount SET DESCRIPTOR 'WNN' VALUE 7 DATA = : vNeuronLevel; */ 

{
 struct sqlexd sqlstm;
 sqlstm.sqlvsn = 13;
 sqlstm.arrsiz = 4;
 sqlstm.sqladtp = &sqladt;
 sqlstm.sqltdsp = &sqltds;
 sqlstm.stmt = "";
 sqlstm.iters = (unsigned int  )vInsertCount;
 sqlstm.offset = (unsigned int  )609;
 sqlstm.cud = sqlcud0;
 sqlstm.sqlest = (unsigned char  *)&sqlca;
 sqlstm.sqlety = (unsigned short)4352;
 sqlstm.occurs = (unsigned int  )7;
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


	/* EXEC SQL FOR : vInsertCount SET DESCRIPTOR 'WNN' VALUE 8 DATA = : vFromNeuron; */ 

{
 struct sqlexd sqlstm;
 sqlstm.sqlvsn = 13;
 sqlstm.arrsiz = 4;
 sqlstm.sqladtp = &sqladt;
 sqlstm.sqltdsp = &sqltds;
 sqlstm.stmt = "";
 sqlstm.iters = (unsigned int  )vInsertCount;
 sqlstm.offset = (unsigned int  )631;
 sqlstm.cud = sqlcud0;
 sqlstm.sqlest = (unsigned char  *)&sqlca;
 sqlstm.sqlety = (unsigned short)4352;
 sqlstm.occurs = (unsigned int  )8;
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


	/* EXEC SQL FOR : vInsertCount SET DESCRIPTOR 'WNN' VALUE 9 DATA = : vToNeuron; */ 

{
 struct sqlexd sqlstm;
 sqlstm.sqlvsn = 13;
 sqlstm.arrsiz = 4;
 sqlstm.sqladtp = &sqladt;
 sqlstm.sqltdsp = &sqltds;
 sqlstm.stmt = "";
 sqlstm.iters = (unsigned int  )vInsertCount;
 sqlstm.offset = (unsigned int  )653;
 sqlstm.cud = sqlcud0;
 sqlstm.sqlest = (unsigned char  *)&sqlca;
 sqlstm.sqlety = (unsigned short)4352;
 sqlstm.occurs = (unsigned int  )9;
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


	/* EXEC SQL FOR : vInsertCount SET DESCRIPTOR 'WNN' VALUE 10 DATA = : vWeight; */ 

{
 struct sqlexd sqlstm;
 sqlstm.sqlvsn = 13;
 sqlstm.arrsiz = 4;
 sqlstm.sqladtp = &sqladt;
 sqlstm.sqltdsp = &sqltds;
 sqlstm.stmt = "";
 sqlstm.iters = (unsigned int  )vInsertCount;
 sqlstm.offset = (unsigned int  )675;
 sqlstm.cud = sqlcud0;
 sqlstm.sqlest = (unsigned char  *)&sqlca;
 sqlstm.sqlety = (unsigned short)4352;
 sqlstm.occurs = (unsigned int  )10;
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


	/* EXEC SQL FOR : vInsertCount SET DESCRIPTOR 'WNN' VALUE 11 DATA = : vCtxValue; */ 

{
 struct sqlexd sqlstm;
 sqlstm.sqlvsn = 13;
 sqlstm.arrsiz = 4;
 sqlstm.sqladtp = &sqladt;
 sqlstm.sqltdsp = &sqltds;
 sqlstm.stmt = "";
 sqlstm.iters = (unsigned int  )vInsertCount;
 sqlstm.offset = (unsigned int  )697;
 sqlstm.cud = sqlcud0;
 sqlstm.sqlest = (unsigned char  *)&sqlca;
 sqlstm.sqlety = (unsigned short)4352;
 sqlstm.occurs = (unsigned int  )11;
 sqlstm.sqhstv[0] = (         void  *)vCtxValue;
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
 sqlstm.arrsiz = 4;
 sqlstm.sqladtp = &sqladt;
 sqlstm.sqltdsp = &sqltds;
 sqlstm.stmt = "";
 sqlstm.iters = (unsigned int  )1;
 sqlstm.offset = (unsigned int  )719;
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
 sqlstm.arrsiz = 4;
 sqlstm.sqladtp = &sqladt;
 sqlstm.sqltdsp = &sqltds;
 sqlstm.stmt = "";
 sqlstm.iters = (unsigned int  )vInsertCount;
 sqlstm.offset = (unsigned int  )738;
 sqlstm.cud = sqlcud0;
 sqlstm.sqlest = (unsigned char  *)&sqlca;
 sqlstm.sqlety = (unsigned short)4352;
 sqlstm.occurs = (unsigned int  )0;
 sqlcxt(&vCtx, &sqlctx, &sqlstm, &sqlfpn);
}



	if (sqlca.sqlcode != 0) {
		LogWrite_C(DebugParms, LOG_ERROR, "BulkWeightInsert_NN failed. SQL Error %d\n", 1, sqlca.sqlcode);
		return sqlca.sqlcode;
	}
	/* EXEC SQL DEALLOCATE DESCRIPTOR 'WNN'; */ 

{
 struct sqlexd sqlstm;
 sqlstm.sqlvsn = 13;
 sqlstm.arrsiz = 4;
 sqlstm.sqladtp = &sqladt;
 sqlstm.sqltdsp = &sqltds;
 sqlstm.stmt = "";
 sqlstm.iters = (unsigned int  )1;
 sqlstm.offset = (unsigned int  )756;
 sqlstm.cud = sqlcud0;
 sqlstm.sqlest = (unsigned char  *)&sqlca;
 sqlstm.sqlety = (unsigned short)4352;
 sqlstm.occurs = (unsigned int  )0;
 sqlcxt(&vCtx, &sqlctx, &sqlstm, &sqlfpn);
}




	//-- free()s
	free(vProcessId);
	free(vThreadId);
	free(vTestId);
	free(vLayerId);
	free(vCoreId);
	free(vDatasetId);
	free(vNeuronLevel);
	free(vFromNeuron);
	free(vToNeuron);
	free(vWeight);
	free(vCtxValue);

	return 0;

}
EXPORT int __stdcall Ora_InsertCoreImage_SOM(tDebugInfo* DebugParms, int pLayerId, int pCoreId, int pDatasetId, int pTestId, SOM_Parms* SOMParms, tSOMWeight** SOMWeight) {
	/* EXEC SQL BEGIN DECLARE SECTION; */ 

	int i, fn, tn;
	sql_context vCtx = DebugParms->DebugDB->DBCtx;
	char stmt[1000];
	int vInsertCount = SOMParms->InputCount*SOMParms->OutputCount;
	int* vProcessId;
	int* vThreadId;
	int* vTestId;
	int* vLayerId;
	int* vCoreId;
	int* vDatasetId;
	int* vFromNeuron;
	int* vToNeuron;
	double* vWeight;
	int dbl_type = 22;	// Oracle SQLT_BDOUBLE
	int int_type = 3;	// 
	unsigned int dbl_len = sizeof(double);
	/* EXEC SQL END DECLARE SECTION; */ 


	//-- Connects to DB only once
	if (vCtx == NULL) {
		if (OraConnect(DebugParms, DebugParms->DebugDB) != 0) printf("Ora_InsertCoreImage_SOM() could not connect to Log Database...\n");
		vCtx = DebugParms->DebugDB->DBCtx;
	}

	vProcessId = (int*)malloc(vInsertCount * sizeof(int));
	vThreadId = (int*)malloc(vInsertCount * sizeof(int));
	vTestId = (int*)malloc(vInsertCount * sizeof(int));
	vLayerId = (int*)malloc(vInsertCount * sizeof(int));
	vCoreId = (int*)malloc(vInsertCount * sizeof(int));
	vDatasetId = (int*)malloc(vInsertCount * sizeof(int));
	vFromNeuron = (int*)malloc(vInsertCount * sizeof(int));
	vToNeuron = (int*)malloc(vInsertCount * sizeof(int));
	vWeight = (double*)malloc(vInsertCount * sizeof(double));

	i = 0;
	for (fn = 0; fn < SOMParms->InputCount; fn++) {
		for (tn = 0; tn < SOMParms->OutputCount; tn++) {
			vProcessId[i] = SOMWeight[fn][tn].ProcessId;
			vThreadId[i] = SOMWeight[fn][tn].ThreadId;
			vTestId[i] = pTestId;
			vLayerId[i] = pLayerId;
			vCoreId[i] = pCoreId;
			vDatasetId[i] = pDatasetId;
			vFromNeuron[i] = SOMWeight[fn][tn].FromNeuron;
			vToNeuron[i] = SOMWeight[fn][tn].ToNeuron;
			vWeight[i] = SOMWeight[fn][tn].Weight;
			i++;
		}
	}
	//-- Then, Build the Insert statement
	sprintf(&stmt[0], "insert into CoreImage_SOM (ProcessId, ThreadId, TestId, CoreId, DatasetId, NeuronLevel, FromNeuron, ToNeuron, Weight)");
	strcat(stmt, " values(:WSOM01, :WSOM02, :WSOM03, :WSOM04, :WSOM05, :WSOM06, :WSOM07, :WSOM08, :WSOM09, :WSOM10)");

	/* EXEC SQL CONTEXT USE : vCtx; */ 

	/* EXEC SQL FOR : vInsertCount ALLOCATE DESCRIPTOR 'WSOM'; */ 

{
 struct sqlexd sqlstm;
 sqlstm.sqlvsn = 13;
 sqlstm.arrsiz = 4;
 sqlstm.sqladtp = &sqladt;
 sqlstm.sqltdsp = &sqltds;
 sqlstm.stmt = "";
 sqlstm.iters = (unsigned int  )vInsertCount;
 sqlstm.offset = (unsigned int  )774;
 sqlstm.cud = sqlcud0;
 sqlstm.sqlest = (unsigned char  *)&sqlca;
 sqlstm.sqlety = (unsigned short)4352;
 sqlstm.occurs = (unsigned int  )100;
 sqlcxt(&vCtx, &sqlctx, &sqlstm, &sqlfpn);
}


	/* EXEC SQL SET DESCRIPTOR 'WSOM' COUNT = 9; */ 

{
 struct sqlexd sqlstm;
 sqlstm.sqlvsn = 13;
 sqlstm.arrsiz = 4;
 sqlstm.sqladtp = &sqladt;
 sqlstm.sqltdsp = &sqltds;
 sqlstm.stmt = "";
 sqlstm.iters = (unsigned int  )1;
 sqlstm.offset = (unsigned int  )793;
 sqlstm.cud = sqlcud0;
 sqlstm.sqlest = (unsigned char  *)&sqlca;
 sqlstm.sqlety = (unsigned short)4352;
 sqlstm.occurs = (unsigned int  )9;
 sqlcxt(&vCtx, &sqlctx, &sqlstm, &sqlfpn);
}


	/* EXEC SQL SET DESCRIPTOR 'WSOM' VALUE 1 TYPE = :int_type; */ 

{
 struct sqlexd sqlstm;
 sqlstm.sqlvsn = 13;
 sqlstm.arrsiz = 4;
 sqlstm.sqladtp = &sqladt;
 sqlstm.sqltdsp = &sqltds;
 sqlstm.stmt = "";
 sqlstm.iters = (unsigned int  )1;
 sqlstm.offset = (unsigned int  )812;
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


	/* EXEC SQL SET DESCRIPTOR 'WSOM' VALUE 2 TYPE = :int_type; */ 

{
 struct sqlexd sqlstm;
 sqlstm.sqlvsn = 13;
 sqlstm.arrsiz = 4;
 sqlstm.sqladtp = &sqladt;
 sqlstm.sqltdsp = &sqltds;
 sqlstm.stmt = "";
 sqlstm.iters = (unsigned int  )1;
 sqlstm.offset = (unsigned int  )835;
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


	/* EXEC SQL SET DESCRIPTOR 'WSOM' VALUE 3 TYPE = :int_type; */ 

{
 struct sqlexd sqlstm;
 sqlstm.sqlvsn = 13;
 sqlstm.arrsiz = 4;
 sqlstm.sqladtp = &sqladt;
 sqlstm.sqltdsp = &sqltds;
 sqlstm.stmt = "";
 sqlstm.iters = (unsigned int  )1;
 sqlstm.offset = (unsigned int  )858;
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


	/* EXEC SQL SET DESCRIPTOR 'WSOM' VALUE 4 TYPE = :int_type; */ 

{
 struct sqlexd sqlstm;
 sqlstm.sqlvsn = 13;
 sqlstm.arrsiz = 4;
 sqlstm.sqladtp = &sqladt;
 sqlstm.sqltdsp = &sqltds;
 sqlstm.stmt = "";
 sqlstm.iters = (unsigned int  )1;
 sqlstm.offset = (unsigned int  )881;
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


	/* EXEC SQL SET DESCRIPTOR 'WSOM' VALUE 5 TYPE = :int_type; */ 

{
 struct sqlexd sqlstm;
 sqlstm.sqlvsn = 13;
 sqlstm.arrsiz = 4;
 sqlstm.sqladtp = &sqladt;
 sqlstm.sqltdsp = &sqltds;
 sqlstm.stmt = "";
 sqlstm.iters = (unsigned int  )1;
 sqlstm.offset = (unsigned int  )904;
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


	/* EXEC SQL SET DESCRIPTOR 'WSOM' VALUE 6 TYPE = :int_type; */ 

{
 struct sqlexd sqlstm;
 sqlstm.sqlvsn = 13;
 sqlstm.arrsiz = 4;
 sqlstm.sqladtp = &sqladt;
 sqlstm.sqltdsp = &sqltds;
 sqlstm.stmt = "";
 sqlstm.iters = (unsigned int  )1;
 sqlstm.offset = (unsigned int  )927;
 sqlstm.cud = sqlcud0;
 sqlstm.sqlest = (unsigned char  *)&sqlca;
 sqlstm.sqlety = (unsigned short)4352;
 sqlstm.occurs = (unsigned int  )6;
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


	/* EXEC SQL SET DESCRIPTOR 'WSOM' VALUE 7 TYPE = :int_type; */ 

{
 struct sqlexd sqlstm;
 sqlstm.sqlvsn = 13;
 sqlstm.arrsiz = 4;
 sqlstm.sqladtp = &sqladt;
 sqlstm.sqltdsp = &sqltds;
 sqlstm.stmt = "";
 sqlstm.iters = (unsigned int  )1;
 sqlstm.offset = (unsigned int  )950;
 sqlstm.cud = sqlcud0;
 sqlstm.sqlest = (unsigned char  *)&sqlca;
 sqlstm.sqlety = (unsigned short)4352;
 sqlstm.occurs = (unsigned int  )7;
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


	/* EXEC SQL SET DESCRIPTOR 'WSOM' VALUE 8 TYPE = :int_type; */ 

{
 struct sqlexd sqlstm;
 sqlstm.sqlvsn = 13;
 sqlstm.arrsiz = 4;
 sqlstm.sqladtp = &sqladt;
 sqlstm.sqltdsp = &sqltds;
 sqlstm.stmt = "";
 sqlstm.iters = (unsigned int  )1;
 sqlstm.offset = (unsigned int  )973;
 sqlstm.cud = sqlcud0;
 sqlstm.sqlest = (unsigned char  *)&sqlca;
 sqlstm.sqlety = (unsigned short)4352;
 sqlstm.occurs = (unsigned int  )8;
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


	/* EXEC SQL SET DESCRIPTOR 'WSOM' VALUE 9 TYPE = :dbl_type; */ 

{
 struct sqlexd sqlstm;
 sqlstm.sqlvsn = 13;
 sqlstm.arrsiz = 4;
 sqlstm.sqladtp = &sqladt;
 sqlstm.sqltdsp = &sqltds;
 sqlstm.stmt = "";
 sqlstm.iters = (unsigned int  )1;
 sqlstm.offset = (unsigned int  )996;
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



	/* EXEC SQL FOR : vInsertCount SET DESCRIPTOR 'WSOM' VALUE 1 DATA = : vProcessId; */ 

{
 struct sqlexd sqlstm;
 sqlstm.sqlvsn = 13;
 sqlstm.arrsiz = 4;
 sqlstm.sqladtp = &sqladt;
 sqlstm.sqltdsp = &sqltds;
 sqlstm.stmt = "";
 sqlstm.iters = (unsigned int  )vInsertCount;
 sqlstm.offset = (unsigned int  )1019;
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


	/* EXEC SQL FOR : vInsertCount SET DESCRIPTOR 'WSOM' VALUE 2 DATA = : vThreadId; */ 

{
 struct sqlexd sqlstm;
 sqlstm.sqlvsn = 13;
 sqlstm.arrsiz = 4;
 sqlstm.sqladtp = &sqladt;
 sqlstm.sqltdsp = &sqltds;
 sqlstm.stmt = "";
 sqlstm.iters = (unsigned int  )vInsertCount;
 sqlstm.offset = (unsigned int  )1042;
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


	/* EXEC SQL FOR : vInsertCount SET DESCRIPTOR 'WSOM' VALUE 3 DATA = : vTestId; */ 

{
 struct sqlexd sqlstm;
 sqlstm.sqlvsn = 13;
 sqlstm.arrsiz = 4;
 sqlstm.sqladtp = &sqladt;
 sqlstm.sqltdsp = &sqltds;
 sqlstm.stmt = "";
 sqlstm.iters = (unsigned int  )vInsertCount;
 sqlstm.offset = (unsigned int  )1065;
 sqlstm.cud = sqlcud0;
 sqlstm.sqlest = (unsigned char  *)&sqlca;
 sqlstm.sqlety = (unsigned short)4352;
 sqlstm.occurs = (unsigned int  )3;
 sqlstm.sqhstv[0] = (         void  *)vTestId;
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


	/* EXEC SQL FOR : vInsertCount SET DESCRIPTOR 'WSOM' VALUE 4 DATA = : vLayerId; */ 

{
 struct sqlexd sqlstm;
 sqlstm.sqlvsn = 13;
 sqlstm.arrsiz = 4;
 sqlstm.sqladtp = &sqladt;
 sqlstm.sqltdsp = &sqltds;
 sqlstm.stmt = "";
 sqlstm.iters = (unsigned int  )vInsertCount;
 sqlstm.offset = (unsigned int  )1088;
 sqlstm.cud = sqlcud0;
 sqlstm.sqlest = (unsigned char  *)&sqlca;
 sqlstm.sqlety = (unsigned short)4352;
 sqlstm.occurs = (unsigned int  )4;
 sqlstm.sqhstv[0] = (         void  *)vLayerId;
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


	/* EXEC SQL FOR : vInsertCount SET DESCRIPTOR 'WSOM' VALUE 5 DATA = : vCoreId; */ 

{
 struct sqlexd sqlstm;
 sqlstm.sqlvsn = 13;
 sqlstm.arrsiz = 4;
 sqlstm.sqladtp = &sqladt;
 sqlstm.sqltdsp = &sqltds;
 sqlstm.stmt = "";
 sqlstm.iters = (unsigned int  )vInsertCount;
 sqlstm.offset = (unsigned int  )1111;
 sqlstm.cud = sqlcud0;
 sqlstm.sqlest = (unsigned char  *)&sqlca;
 sqlstm.sqlety = (unsigned short)4352;
 sqlstm.occurs = (unsigned int  )5;
 sqlstm.sqhstv[0] = (         void  *)vCoreId;
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


	/* EXEC SQL FOR : vInsertCount SET DESCRIPTOR 'WSOM' VALUE 6 DATA = : vDatasetId; */ 

{
 struct sqlexd sqlstm;
 sqlstm.sqlvsn = 13;
 sqlstm.arrsiz = 4;
 sqlstm.sqladtp = &sqladt;
 sqlstm.sqltdsp = &sqltds;
 sqlstm.stmt = "";
 sqlstm.iters = (unsigned int  )vInsertCount;
 sqlstm.offset = (unsigned int  )1134;
 sqlstm.cud = sqlcud0;
 sqlstm.sqlest = (unsigned char  *)&sqlca;
 sqlstm.sqlety = (unsigned short)4352;
 sqlstm.occurs = (unsigned int  )6;
 sqlstm.sqhstv[0] = (         void  *)vDatasetId;
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


	/* EXEC SQL FOR : vInsertCount SET DESCRIPTOR 'WSOM' VALUE 7 DATA = : vFromNeuron; */ 

{
 struct sqlexd sqlstm;
 sqlstm.sqlvsn = 13;
 sqlstm.arrsiz = 4;
 sqlstm.sqladtp = &sqladt;
 sqlstm.sqltdsp = &sqltds;
 sqlstm.stmt = "";
 sqlstm.iters = (unsigned int  )vInsertCount;
 sqlstm.offset = (unsigned int  )1157;
 sqlstm.cud = sqlcud0;
 sqlstm.sqlest = (unsigned char  *)&sqlca;
 sqlstm.sqlety = (unsigned short)4352;
 sqlstm.occurs = (unsigned int  )7;
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


	/* EXEC SQL FOR : vInsertCount SET DESCRIPTOR 'WSOM' VALUE 8 DATA = : vToNeuron; */ 

{
 struct sqlexd sqlstm;
 sqlstm.sqlvsn = 13;
 sqlstm.arrsiz = 4;
 sqlstm.sqladtp = &sqladt;
 sqlstm.sqltdsp = &sqltds;
 sqlstm.stmt = "";
 sqlstm.iters = (unsigned int  )vInsertCount;
 sqlstm.offset = (unsigned int  )1180;
 sqlstm.cud = sqlcud0;
 sqlstm.sqlest = (unsigned char  *)&sqlca;
 sqlstm.sqlety = (unsigned short)4352;
 sqlstm.occurs = (unsigned int  )8;
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


	/* EXEC SQL FOR : vInsertCount SET DESCRIPTOR 'WSOM' VALUE 9 DATA = : vWeight; */ 

{
 struct sqlexd sqlstm;
 sqlstm.sqlvsn = 13;
 sqlstm.arrsiz = 4;
 sqlstm.sqladtp = &sqladt;
 sqlstm.sqltdsp = &sqltds;
 sqlstm.stmt = "";
 sqlstm.iters = (unsigned int  )vInsertCount;
 sqlstm.offset = (unsigned int  )1203;
 sqlstm.cud = sqlcud0;
 sqlstm.sqlest = (unsigned char  *)&sqlca;
 sqlstm.sqlety = (unsigned short)4352;
 sqlstm.occurs = (unsigned int  )9;
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



	/* EXEC SQL PREPARE DynWSOMs FROM : stmt; */ 

{
 struct sqlexd sqlstm;
 sqlstm.sqlvsn = 13;
 sqlstm.arrsiz = 4;
 sqlstm.sqladtp = &sqladt;
 sqlstm.sqltdsp = &sqltds;
 sqlstm.stmt = "";
 sqlstm.iters = (unsigned int  )1;
 sqlstm.offset = (unsigned int  )1226;
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


	/* EXEC SQL FOR : vInsertCount EXECUTE DynWSOMs USING DESCRIPTOR 'WSOM'; */ 

{
 struct sqlexd sqlstm;
 sqlstm.sqlvsn = 13;
 sqlstm.arrsiz = 4;
 sqlstm.sqladtp = &sqladt;
 sqlstm.sqltdsp = &sqltds;
 sqlstm.stmt = "";
 sqlstm.iters = (unsigned int  )vInsertCount;
 sqlstm.offset = (unsigned int  )1245;
 sqlstm.cud = sqlcud0;
 sqlstm.sqlest = (unsigned char  *)&sqlca;
 sqlstm.sqlety = (unsigned short)4352;
 sqlstm.occurs = (unsigned int  )0;
 sqlcxt(&vCtx, &sqlctx, &sqlstm, &sqlfpn);
}



	if (sqlca.sqlcode != 0) {
		LogWrite_C(DebugParms, LOG_ERROR, "Ora_InsertCoreImage_SOM() failed. SQL Error %d\n", 1, sqlca.sqlcode);
		return sqlca.sqlcode;
	}
	/* EXEC SQL DEALLOCATE DESCRIPTOR 'WSOM'; */ 

{
 struct sqlexd sqlstm;
 sqlstm.sqlvsn = 13;
 sqlstm.arrsiz = 4;
 sqlstm.sqladtp = &sqladt;
 sqlstm.sqltdsp = &sqltds;
 sqlstm.stmt = "";
 sqlstm.iters = (unsigned int  )1;
 sqlstm.offset = (unsigned int  )1264;
 sqlstm.cud = sqlcud0;
 sqlstm.sqlest = (unsigned char  *)&sqlca;
 sqlstm.sqlety = (unsigned short)4352;
 sqlstm.occurs = (unsigned int  )0;
 sqlcxt(&vCtx, &sqlctx, &sqlstm, &sqlfpn);
}




	//-- free()s
	free(vProcessId);
	free(vThreadId);
	free(vTestId);
	free(vLayerId);
	free(vCoreId);
	free(vDatasetId);
	free(vFromNeuron);
	free(vToNeuron);
	free(vWeight);

	return 0;

}
EXPORT int __stdcall Ora_InsertCoreImage_SVM(tDebugInfo* DebugParms, int pLayerId, int pCoreId, int pDatasetId, int pTestId, SVM_Parms* SVMParms, tSVMResult* SVMResult, tSVMWeight** SVMWeight) {
	/* EXEC SQL BEGIN DECLARE SECTION; */ 

	int i, sv, var;
	sql_context vCtx = DebugParms->DebugDB->DBCtx;
	char stmt[1000];
	int vInsertCount = (SVMParms->InputCount+1)*(SVMResult->SVcount-1);	// +1 is for alpha
	int* vProcessId;
	int* vThreadId;
	int* vTestId;
	int* vLayerId;
	int* vCoreId;
	int* vDatasetId;
	int* vSVId;
	int* vVarId;
	double* vWeight;
	int dbl_type = 22;	// Oracle SQLT_BDOUBLE
	int int_type = 3;	// 
	unsigned int dbl_len = sizeof(double);
	/* EXEC SQL END DECLARE SECTION; */ 


	//-- Connects to DB only once
	if (vCtx == NULL) {
		if (OraConnect(DebugParms, DebugParms->DebugDB) != 0) printf("Ora_InsertCoreImage_SVM() could not connect to Log Database...\n");
		vCtx = DebugParms->DebugDB->DBCtx;
	}

	vProcessId = (int*)malloc(vInsertCount * sizeof(int));
	vThreadId = (int*)malloc(vInsertCount * sizeof(int));
	vTestId = (int*)malloc(vInsertCount * sizeof(int));
	vLayerId = (int*)malloc(vInsertCount * sizeof(int));
	vCoreId = (int*)malloc(vInsertCount * sizeof(int));
	vDatasetId = (int*)malloc(vInsertCount * sizeof(int));
	vSVId = (int*)malloc(vInsertCount * sizeof(int));
	vVarId = (int*)malloc(vInsertCount * sizeof(int));
	vWeight = (double*)malloc(vInsertCount * sizeof(double));

	i = 0;
	for (sv = 1; sv < SVMResult->SVcount; sv++) {
		for (var = 0; var <= SVMParms->InputCount; var++) {	// +1 is for alpha
			vProcessId[i] = SVMWeight[sv][var].ProcessId;
			vThreadId[i] = SVMWeight[sv][var].ThreadId;
			vTestId[i] = pTestId;
			vLayerId[i] = pLayerId;
			vCoreId[i] = pCoreId;
			vDatasetId[i] = pDatasetId;
			vSVId[i] = SVMWeight[sv][var].SVId;
			vVarId[i] = SVMWeight[sv][var].VarId;
			vWeight[i] = SVMWeight[sv][var].Weight;
			i++;
		}
	}

	//-- Then, Build the Insert statement
	sprintf(&stmt[0], "insert into CoreImage_SVM (ProcessId, ThreadId, TestId, LayerId, CoreId, DatasetId, SVId, VarId, Weight)");
	strcat(stmt, " values(:WSVM01, :WSVM02, :WSVM03, :WSVM04, :WSVM05, :WSVM06, :WSVM07, :WSVM08, :WSVM09)");

	/* EXEC SQL CONTEXT USE : vCtx; */ 

	/* EXEC SQL FOR : vInsertCount ALLOCATE DESCRIPTOR 'WSVM'; */ 

{
 struct sqlexd sqlstm;
 sqlstm.sqlvsn = 13;
 sqlstm.arrsiz = 4;
 sqlstm.sqladtp = &sqladt;
 sqlstm.sqltdsp = &sqltds;
 sqlstm.stmt = "";
 sqlstm.iters = (unsigned int  )vInsertCount;
 sqlstm.offset = (unsigned int  )1283;
 sqlstm.cud = sqlcud0;
 sqlstm.sqlest = (unsigned char  *)&sqlca;
 sqlstm.sqlety = (unsigned short)4352;
 sqlstm.occurs = (unsigned int  )100;
 sqlcxt(&vCtx, &sqlctx, &sqlstm, &sqlfpn);
}


	/* EXEC SQL SET DESCRIPTOR 'WSVM' COUNT = 9; */ 

{
 struct sqlexd sqlstm;
 sqlstm.sqlvsn = 13;
 sqlstm.arrsiz = 4;
 sqlstm.sqladtp = &sqladt;
 sqlstm.sqltdsp = &sqltds;
 sqlstm.stmt = "";
 sqlstm.iters = (unsigned int  )1;
 sqlstm.offset = (unsigned int  )1302;
 sqlstm.cud = sqlcud0;
 sqlstm.sqlest = (unsigned char  *)&sqlca;
 sqlstm.sqlety = (unsigned short)4352;
 sqlstm.occurs = (unsigned int  )9;
 sqlcxt(&vCtx, &sqlctx, &sqlstm, &sqlfpn);
}


	/* EXEC SQL SET DESCRIPTOR 'WSVM' VALUE 1 TYPE = :int_type; */ 

{
 struct sqlexd sqlstm;
 sqlstm.sqlvsn = 13;
 sqlstm.arrsiz = 4;
 sqlstm.sqladtp = &sqladt;
 sqlstm.sqltdsp = &sqltds;
 sqlstm.stmt = "";
 sqlstm.iters = (unsigned int  )1;
 sqlstm.offset = (unsigned int  )1321;
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


	/* EXEC SQL SET DESCRIPTOR 'WSVM' VALUE 2 TYPE = :int_type; */ 

{
 struct sqlexd sqlstm;
 sqlstm.sqlvsn = 13;
 sqlstm.arrsiz = 4;
 sqlstm.sqladtp = &sqladt;
 sqlstm.sqltdsp = &sqltds;
 sqlstm.stmt = "";
 sqlstm.iters = (unsigned int  )1;
 sqlstm.offset = (unsigned int  )1344;
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


	/* EXEC SQL SET DESCRIPTOR 'WSVM' VALUE 3 TYPE = :int_type; */ 

{
 struct sqlexd sqlstm;
 sqlstm.sqlvsn = 13;
 sqlstm.arrsiz = 4;
 sqlstm.sqladtp = &sqladt;
 sqlstm.sqltdsp = &sqltds;
 sqlstm.stmt = "";
 sqlstm.iters = (unsigned int  )1;
 sqlstm.offset = (unsigned int  )1367;
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


	/* EXEC SQL SET DESCRIPTOR 'WSVM' VALUE 4 TYPE = :int_type; */ 

{
 struct sqlexd sqlstm;
 sqlstm.sqlvsn = 13;
 sqlstm.arrsiz = 4;
 sqlstm.sqladtp = &sqladt;
 sqlstm.sqltdsp = &sqltds;
 sqlstm.stmt = "";
 sqlstm.iters = (unsigned int  )1;
 sqlstm.offset = (unsigned int  )1390;
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


	/* EXEC SQL SET DESCRIPTOR 'WSVM' VALUE 5 TYPE = :int_type; */ 

{
 struct sqlexd sqlstm;
 sqlstm.sqlvsn = 13;
 sqlstm.arrsiz = 4;
 sqlstm.sqladtp = &sqladt;
 sqlstm.sqltdsp = &sqltds;
 sqlstm.stmt = "";
 sqlstm.iters = (unsigned int  )1;
 sqlstm.offset = (unsigned int  )1413;
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


	/* EXEC SQL SET DESCRIPTOR 'WSVM' VALUE 6 TYPE = :int_type; */ 

{
 struct sqlexd sqlstm;
 sqlstm.sqlvsn = 13;
 sqlstm.arrsiz = 4;
 sqlstm.sqladtp = &sqladt;
 sqlstm.sqltdsp = &sqltds;
 sqlstm.stmt = "";
 sqlstm.iters = (unsigned int  )1;
 sqlstm.offset = (unsigned int  )1436;
 sqlstm.cud = sqlcud0;
 sqlstm.sqlest = (unsigned char  *)&sqlca;
 sqlstm.sqlety = (unsigned short)4352;
 sqlstm.occurs = (unsigned int  )6;
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


	/* EXEC SQL SET DESCRIPTOR 'WSVM' VALUE 7 TYPE = :int_type; */ 

{
 struct sqlexd sqlstm;
 sqlstm.sqlvsn = 13;
 sqlstm.arrsiz = 4;
 sqlstm.sqladtp = &sqladt;
 sqlstm.sqltdsp = &sqltds;
 sqlstm.stmt = "";
 sqlstm.iters = (unsigned int  )1;
 sqlstm.offset = (unsigned int  )1459;
 sqlstm.cud = sqlcud0;
 sqlstm.sqlest = (unsigned char  *)&sqlca;
 sqlstm.sqlety = (unsigned short)4352;
 sqlstm.occurs = (unsigned int  )7;
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


	/* EXEC SQL SET DESCRIPTOR 'WSVM' VALUE 8 TYPE = :int_type; */ 

{
 struct sqlexd sqlstm;
 sqlstm.sqlvsn = 13;
 sqlstm.arrsiz = 4;
 sqlstm.sqladtp = &sqladt;
 sqlstm.sqltdsp = &sqltds;
 sqlstm.stmt = "";
 sqlstm.iters = (unsigned int  )1;
 sqlstm.offset = (unsigned int  )1482;
 sqlstm.cud = sqlcud0;
 sqlstm.sqlest = (unsigned char  *)&sqlca;
 sqlstm.sqlety = (unsigned short)4352;
 sqlstm.occurs = (unsigned int  )8;
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


	/* EXEC SQL SET DESCRIPTOR 'WSVM' VALUE 9 TYPE = :dbl_type; */ 

{
 struct sqlexd sqlstm;
 sqlstm.sqlvsn = 13;
 sqlstm.arrsiz = 4;
 sqlstm.sqladtp = &sqladt;
 sqlstm.sqltdsp = &sqltds;
 sqlstm.stmt = "";
 sqlstm.iters = (unsigned int  )1;
 sqlstm.offset = (unsigned int  )1505;
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



	/* EXEC SQL FOR : vInsertCount SET DESCRIPTOR 'WSVM' VALUE 1 DATA = : vProcessId; */ 

{
 struct sqlexd sqlstm;
 sqlstm.sqlvsn = 13;
 sqlstm.arrsiz = 4;
 sqlstm.sqladtp = &sqladt;
 sqlstm.sqltdsp = &sqltds;
 sqlstm.stmt = "";
 sqlstm.iters = (unsigned int  )vInsertCount;
 sqlstm.offset = (unsigned int  )1528;
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


	/* EXEC SQL FOR : vInsertCount SET DESCRIPTOR 'WSVM' VALUE 2 DATA = : vThreadId; */ 

{
 struct sqlexd sqlstm;
 sqlstm.sqlvsn = 13;
 sqlstm.arrsiz = 4;
 sqlstm.sqladtp = &sqladt;
 sqlstm.sqltdsp = &sqltds;
 sqlstm.stmt = "";
 sqlstm.iters = (unsigned int  )vInsertCount;
 sqlstm.offset = (unsigned int  )1551;
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


	/* EXEC SQL FOR : vInsertCount SET DESCRIPTOR 'WSVM' VALUE 3 DATA = : vTestId; */ 

{
 struct sqlexd sqlstm;
 sqlstm.sqlvsn = 13;
 sqlstm.arrsiz = 4;
 sqlstm.sqladtp = &sqladt;
 sqlstm.sqltdsp = &sqltds;
 sqlstm.stmt = "";
 sqlstm.iters = (unsigned int  )vInsertCount;
 sqlstm.offset = (unsigned int  )1574;
 sqlstm.cud = sqlcud0;
 sqlstm.sqlest = (unsigned char  *)&sqlca;
 sqlstm.sqlety = (unsigned short)4352;
 sqlstm.occurs = (unsigned int  )3;
 sqlstm.sqhstv[0] = (         void  *)vTestId;
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


	/* EXEC SQL FOR : vInsertCount SET DESCRIPTOR 'WSVM' VALUE 4 DATA = : vLayerId; */ 

{
 struct sqlexd sqlstm;
 sqlstm.sqlvsn = 13;
 sqlstm.arrsiz = 4;
 sqlstm.sqladtp = &sqladt;
 sqlstm.sqltdsp = &sqltds;
 sqlstm.stmt = "";
 sqlstm.iters = (unsigned int  )vInsertCount;
 sqlstm.offset = (unsigned int  )1597;
 sqlstm.cud = sqlcud0;
 sqlstm.sqlest = (unsigned char  *)&sqlca;
 sqlstm.sqlety = (unsigned short)4352;
 sqlstm.occurs = (unsigned int  )4;
 sqlstm.sqhstv[0] = (         void  *)vLayerId;
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


	/* EXEC SQL FOR : vInsertCount SET DESCRIPTOR 'WSVM' VALUE 5 DATA = : vCoreId; */ 

{
 struct sqlexd sqlstm;
 sqlstm.sqlvsn = 13;
 sqlstm.arrsiz = 4;
 sqlstm.sqladtp = &sqladt;
 sqlstm.sqltdsp = &sqltds;
 sqlstm.stmt = "";
 sqlstm.iters = (unsigned int  )vInsertCount;
 sqlstm.offset = (unsigned int  )1620;
 sqlstm.cud = sqlcud0;
 sqlstm.sqlest = (unsigned char  *)&sqlca;
 sqlstm.sqlety = (unsigned short)4352;
 sqlstm.occurs = (unsigned int  )5;
 sqlstm.sqhstv[0] = (         void  *)vCoreId;
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


	/* EXEC SQL FOR : vInsertCount SET DESCRIPTOR 'WSVM' VALUE 6 DATA = : vDatasetId; */ 

{
 struct sqlexd sqlstm;
 sqlstm.sqlvsn = 13;
 sqlstm.arrsiz = 4;
 sqlstm.sqladtp = &sqladt;
 sqlstm.sqltdsp = &sqltds;
 sqlstm.stmt = "";
 sqlstm.iters = (unsigned int  )vInsertCount;
 sqlstm.offset = (unsigned int  )1643;
 sqlstm.cud = sqlcud0;
 sqlstm.sqlest = (unsigned char  *)&sqlca;
 sqlstm.sqlety = (unsigned short)4352;
 sqlstm.occurs = (unsigned int  )6;
 sqlstm.sqhstv[0] = (         void  *)vDatasetId;
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


	/* EXEC SQL FOR : vInsertCount SET DESCRIPTOR 'WSVM' VALUE 7 DATA = : vSVId; */ 

{
 struct sqlexd sqlstm;
 sqlstm.sqlvsn = 13;
 sqlstm.arrsiz = 4;
 sqlstm.sqladtp = &sqladt;
 sqlstm.sqltdsp = &sqltds;
 sqlstm.stmt = "";
 sqlstm.iters = (unsigned int  )vInsertCount;
 sqlstm.offset = (unsigned int  )1666;
 sqlstm.cud = sqlcud0;
 sqlstm.sqlest = (unsigned char  *)&sqlca;
 sqlstm.sqlety = (unsigned short)4352;
 sqlstm.occurs = (unsigned int  )7;
 sqlstm.sqhstv[0] = (         void  *)vSVId;
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


	/* EXEC SQL FOR : vInsertCount SET DESCRIPTOR 'WSVM' VALUE 8 DATA = : vVarId; */ 

{
 struct sqlexd sqlstm;
 sqlstm.sqlvsn = 13;
 sqlstm.arrsiz = 4;
 sqlstm.sqladtp = &sqladt;
 sqlstm.sqltdsp = &sqltds;
 sqlstm.stmt = "";
 sqlstm.iters = (unsigned int  )vInsertCount;
 sqlstm.offset = (unsigned int  )1689;
 sqlstm.cud = sqlcud0;
 sqlstm.sqlest = (unsigned char  *)&sqlca;
 sqlstm.sqlety = (unsigned short)4352;
 sqlstm.occurs = (unsigned int  )8;
 sqlstm.sqhstv[0] = (         void  *)vVarId;
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


	/* EXEC SQL FOR : vInsertCount SET DESCRIPTOR 'WSVM' VALUE 9 DATA = : vWeight; */ 

{
 struct sqlexd sqlstm;
 sqlstm.sqlvsn = 13;
 sqlstm.arrsiz = 4;
 sqlstm.sqladtp = &sqladt;
 sqlstm.sqltdsp = &sqltds;
 sqlstm.stmt = "";
 sqlstm.iters = (unsigned int  )vInsertCount;
 sqlstm.offset = (unsigned int  )1712;
 sqlstm.cud = sqlcud0;
 sqlstm.sqlest = (unsigned char  *)&sqlca;
 sqlstm.sqlety = (unsigned short)4352;
 sqlstm.occurs = (unsigned int  )9;
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



	/* EXEC SQL PREPARE DynWSVMs FROM : stmt; */ 

{
 struct sqlexd sqlstm;
 sqlstm.sqlvsn = 13;
 sqlstm.arrsiz = 4;
 sqlstm.sqladtp = &sqladt;
 sqlstm.sqltdsp = &sqltds;
 sqlstm.stmt = "";
 sqlstm.iters = (unsigned int  )1;
 sqlstm.offset = (unsigned int  )1735;
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


	/* EXEC SQL FOR : vInsertCount EXECUTE DynWSVMs USING DESCRIPTOR 'WSVM'; */ 

{
 struct sqlexd sqlstm;
 sqlstm.sqlvsn = 13;
 sqlstm.arrsiz = 4;
 sqlstm.sqladtp = &sqladt;
 sqlstm.sqltdsp = &sqltds;
 sqlstm.stmt = "";
 sqlstm.iters = (unsigned int  )vInsertCount;
 sqlstm.offset = (unsigned int  )1754;
 sqlstm.cud = sqlcud0;
 sqlstm.sqlest = (unsigned char  *)&sqlca;
 sqlstm.sqlety = (unsigned short)4352;
 sqlstm.occurs = (unsigned int  )0;
 sqlcxt(&vCtx, &sqlctx, &sqlstm, &sqlfpn);
}



	if (sqlca.sqlcode != 0) {
		LogWrite_C(DebugParms, LOG_ERROR, "Ora_InsertCoreImage_SVM() failed. SQL Error %d\n", 1, sqlca.sqlcode);
		return sqlca.sqlcode;
	}
	/* EXEC SQL DEALLOCATE DESCRIPTOR 'WSVM'; */ 

{
 struct sqlexd sqlstm;
 sqlstm.sqlvsn = 13;
 sqlstm.arrsiz = 4;
 sqlstm.sqladtp = &sqladt;
 sqlstm.sqltdsp = &sqltds;
 sqlstm.stmt = "";
 sqlstm.iters = (unsigned int  )1;
 sqlstm.offset = (unsigned int  )1773;
 sqlstm.cud = sqlcud0;
 sqlstm.sqlest = (unsigned char  *)&sqlca;
 sqlstm.sqlety = (unsigned short)4352;
 sqlstm.occurs = (unsigned int  )0;
 sqlcxt(&vCtx, &sqlctx, &sqlstm, &sqlfpn);
}




	//-- free()s
	free(vProcessId);
	free(vThreadId);
	free(vTestId);
	free(vLayerId);
	free(vCoreId);
	free(vDatasetId);
	free(vSVId);
	free(vVarId);
	free(vWeight);

	return 0;

}
//--
EXPORT int __stdcall Ora_InsertCoreLogs_NN(tDebugInfo* DebugParms, int BPAlgo, int pInsertCount, tLogInt* IntLogs) {
	/* EXEC SQL BEGIN DECLARE SECTION; */ 

	sql_context vCtx = DebugParms->DebugDB->DBCtx;
	char stmt[1000];
	int i;
	int vInsertCount = pInsertCount;
	//-- Common
	int* vProcessId;
	int* vThreadId;
	//-- BP_SCGD
	int* vEpoch;
	int* vBPid;
	int* vK;
	double* vdelta;
	double* vmu;
	double* valpha;
	double* vbeta;
	double* vlambda;
	double* vlambdau;
	double* vrnorm;
	double* venorm;
	double* vcomp;
	//--
	/* EXEC SQL END DECLARE SECTION; */ 


	//-- 1. Connects to DB only once
	if (vCtx == NULL) {
		if (OraConnect(DebugParms, DebugParms->DebugDB) != 0) {
			printf("Ora_InsertCoreLogs_NN() could not connect to Log Database...\n");
			return -1;
		}
		vCtx = DebugParms->DebugDB->DBCtx;
	}

	//-- 2. set Context & allocate descriptor
	/* EXEC SQL CONTEXT USE : vCtx; */ 

	/* EXEC SQL FOR :vInsertCount ALLOCATE DESCRIPTOR 'inCLNN'; */ 

{
 struct sqlexd sqlstm;
 sqlstm.sqlvsn = 13;
 sqlstm.arrsiz = 4;
 sqlstm.sqladtp = &sqladt;
 sqlstm.sqltdsp = &sqltds;
 sqlstm.stmt = "";
 sqlstm.iters = (unsigned int  )vInsertCount;
 sqlstm.offset = (unsigned int  )1792;
 sqlstm.cud = sqlcud0;
 sqlstm.sqlest = (unsigned char  *)&sqlca;
 sqlstm.sqlety = (unsigned short)4352;
 sqlstm.occurs = (unsigned int  )100;
 sqlcxt(&vCtx, &sqlctx, &sqlstm, &sqlfpn);
}



	//-- 3. actual Insert statement depends on BP_ALGO
	switch (BPAlgo) {
	case BP_QING:
		//-- 3.1. malloc() column arrays
		//-- 3.2. Assign struct fields to column arrays
		//-- 3.3. Build Array Insert statement
		return 0;
		break;
	case BP_QUICKPROP:
		//-- 3.1. malloc() column arrays
		//-- 3.2. Assign struct fields to column arrays
		//-- 3.3. Build Array Insert statement
		return 0;
		break;
	case BP_SCGD:
		//-- 3.1. malloc() column arrays
		vProcessId = (int*)malloc(vInsertCount * sizeof(int));
		vThreadId = (int*)malloc(vInsertCount * sizeof(int));
		vEpoch = (int*)malloc(vInsertCount * sizeof(int));
		vBPid = (int*)malloc(vInsertCount * sizeof(int));
		vK = (int*)malloc(vInsertCount * sizeof(int));
		vdelta = (double*)malloc(vInsertCount * sizeof(double));
		vmu = (double*)malloc(vInsertCount * sizeof(double));
		valpha = (double*)malloc(vInsertCount * sizeof(double));
		vbeta = (double*)malloc(vInsertCount * sizeof(double));
		vlambda = (double*)malloc(vInsertCount * sizeof(double));
		vlambdau = (double*)malloc(vInsertCount * sizeof(double));
		vrnorm = (double*)malloc(vInsertCount * sizeof(double));
		venorm = (double*)malloc(vInsertCount * sizeof(double));
		vcomp = (double*)malloc(vInsertCount * sizeof(double));

		//-- 3.2. Assign struct fields to column arrays
		for (i = 0; i < pInsertCount; i++) {
			vProcessId[i] = IntLogs[i].ProcessId;
			vThreadId[i] = IntLogs[i].ThreadId;
			vEpoch[i] = IntLogs[i].Epoch;
			vBPid[i] = IntLogs[i].BPid;
			vK[i] = IntLogs[i].K;
			vdelta[i] = IntLogs[i].delta;
			vmu[i] = IntLogs[i].mu;
			valpha[i] = IntLogs[i].alpha;
			vbeta[i] = IntLogs[i].beta;
			vlambda[i] = IntLogs[i].lambda;
			vlambdau[i] = IntLogs[i].lambdau;
			vrnorm[i] = IntLogs[i].rnorm;
			venorm[i] = IntLogs[i].enorm;
			vcomp[i] = IntLogs[i].comp;
		}

		//-- 3.3. Build Array Insert statement
		sprintf(&stmt[0], "insert into CoreLogs_NN_SCGD(ProcessId, ThreadId, Epoch, BPId, K, Delta, Mu, Alpha, Beta, Lambda, Lambdau, Rnorm, Enorm, Comp) values(:SCGD01, :SCGD02, :SCGD03, :SCGD04, :SCGD05, :SCGD06, :SCGD07, :SCGD08, :SCGD09, :SCGD10, :SCGD11, :SCGD12, :SCGD13, :SCGD14)");
		/* EXEC SQL SET DESCRIPTOR 'inCLNN' COUNT = 14; */ 

{
  struct sqlexd sqlstm;
  sqlstm.sqlvsn = 13;
  sqlstm.arrsiz = 4;
  sqlstm.sqladtp = &sqladt;
  sqlstm.sqltdsp = &sqltds;
  sqlstm.stmt = "";
  sqlstm.iters = (unsigned int  )1;
  sqlstm.offset = (unsigned int  )1813;
  sqlstm.cud = sqlcud0;
  sqlstm.sqlest = (unsigned char  *)&sqlca;
  sqlstm.sqlety = (unsigned short)4352;
  sqlstm.occurs = (unsigned int  )14;
  sqlcxt(&vCtx, &sqlctx, &sqlstm, &sqlfpn);
}


		/* EXEC SQL FOR :vInsertCount SET DESCRIPTOR 'inCLNN' VALUE 1 DATA = :vProcessId; */ 

{
  struct sqlexd sqlstm;
  sqlstm.sqlvsn = 13;
  sqlstm.arrsiz = 4;
  sqlstm.sqladtp = &sqladt;
  sqlstm.sqltdsp = &sqltds;
  sqlstm.stmt = "";
  sqlstm.iters = (unsigned int  )vInsertCount;
  sqlstm.offset = (unsigned int  )1834;
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


		/* EXEC SQL FOR :vInsertCount SET DESCRIPTOR 'inCLNN' VALUE 2 DATA = :vThreadId; */ 

{
  struct sqlexd sqlstm;
  sqlstm.sqlvsn = 13;
  sqlstm.arrsiz = 4;
  sqlstm.sqladtp = &sqladt;
  sqlstm.sqltdsp = &sqltds;
  sqlstm.stmt = "";
  sqlstm.iters = (unsigned int  )vInsertCount;
  sqlstm.offset = (unsigned int  )1859;
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


		/* EXEC SQL FOR :vInsertCount SET DESCRIPTOR 'inCLNN' VALUE 3 DATA = :vEpoch; */ 

{
  struct sqlexd sqlstm;
  sqlstm.sqlvsn = 13;
  sqlstm.arrsiz = 4;
  sqlstm.sqladtp = &sqladt;
  sqlstm.sqltdsp = &sqltds;
  sqlstm.stmt = "";
  sqlstm.iters = (unsigned int  )vInsertCount;
  sqlstm.offset = (unsigned int  )1884;
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


		/* EXEC SQL FOR :vInsertCount SET DESCRIPTOR 'inCLNN' VALUE 4 DATA = :vBPid; */ 

{
  struct sqlexd sqlstm;
  sqlstm.sqlvsn = 13;
  sqlstm.arrsiz = 4;
  sqlstm.sqladtp = &sqladt;
  sqlstm.sqltdsp = &sqltds;
  sqlstm.stmt = "";
  sqlstm.iters = (unsigned int  )vInsertCount;
  sqlstm.offset = (unsigned int  )1909;
  sqlstm.cud = sqlcud0;
  sqlstm.sqlest = (unsigned char  *)&sqlca;
  sqlstm.sqlety = (unsigned short)4352;
  sqlstm.occurs = (unsigned int  )4;
  sqlstm.sqhstv[0] = (         void  *)vBPid;
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


		/* EXEC SQL FOR :vInsertCount SET DESCRIPTOR 'inCLNN' VALUE 5 DATA = :vK; */ 

{
  struct sqlexd sqlstm;
  sqlstm.sqlvsn = 13;
  sqlstm.arrsiz = 4;
  sqlstm.sqladtp = &sqladt;
  sqlstm.sqltdsp = &sqltds;
  sqlstm.stmt = "";
  sqlstm.iters = (unsigned int  )vInsertCount;
  sqlstm.offset = (unsigned int  )1934;
  sqlstm.cud = sqlcud0;
  sqlstm.sqlest = (unsigned char  *)&sqlca;
  sqlstm.sqlety = (unsigned short)4352;
  sqlstm.occurs = (unsigned int  )5;
  sqlstm.sqhstv[0] = (         void  *)vK;
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


		/* EXEC SQL FOR :vInsertCount SET DESCRIPTOR 'inCLNN' VALUE 6 DATA = :vdelta; */ 

{
  struct sqlexd sqlstm;
  sqlstm.sqlvsn = 13;
  sqlstm.arrsiz = 4;
  sqlstm.sqladtp = &sqladt;
  sqlstm.sqltdsp = &sqltds;
  sqlstm.stmt = "";
  sqlstm.iters = (unsigned int  )vInsertCount;
  sqlstm.offset = (unsigned int  )1959;
  sqlstm.cud = sqlcud0;
  sqlstm.sqlest = (unsigned char  *)&sqlca;
  sqlstm.sqlety = (unsigned short)4352;
  sqlstm.occurs = (unsigned int  )6;
  sqlstm.sqhstv[0] = (         void  *)vdelta;
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


		/* EXEC SQL FOR :vInsertCount SET DESCRIPTOR 'inCLNN' VALUE 7 DATA = :vmu; */ 

{
  struct sqlexd sqlstm;
  sqlstm.sqlvsn = 13;
  sqlstm.arrsiz = 4;
  sqlstm.sqladtp = &sqladt;
  sqlstm.sqltdsp = &sqltds;
  sqlstm.stmt = "";
  sqlstm.iters = (unsigned int  )vInsertCount;
  sqlstm.offset = (unsigned int  )1984;
  sqlstm.cud = sqlcud0;
  sqlstm.sqlest = (unsigned char  *)&sqlca;
  sqlstm.sqlety = (unsigned short)4352;
  sqlstm.occurs = (unsigned int  )7;
  sqlstm.sqhstv[0] = (         void  *)vmu;
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


		/* EXEC SQL FOR :vInsertCount SET DESCRIPTOR 'inCLNN' VALUE 8 DATA = :valpha; */ 

{
  struct sqlexd sqlstm;
  sqlstm.sqlvsn = 13;
  sqlstm.arrsiz = 4;
  sqlstm.sqladtp = &sqladt;
  sqlstm.sqltdsp = &sqltds;
  sqlstm.stmt = "";
  sqlstm.iters = (unsigned int  )vInsertCount;
  sqlstm.offset = (unsigned int  )2009;
  sqlstm.cud = sqlcud0;
  sqlstm.sqlest = (unsigned char  *)&sqlca;
  sqlstm.sqlety = (unsigned short)4352;
  sqlstm.occurs = (unsigned int  )8;
  sqlstm.sqhstv[0] = (         void  *)valpha;
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


		/* EXEC SQL FOR :vInsertCount SET DESCRIPTOR 'inCLNN' VALUE 9 DATA = :vbeta; */ 

{
  struct sqlexd sqlstm;
  sqlstm.sqlvsn = 13;
  sqlstm.arrsiz = 4;
  sqlstm.sqladtp = &sqladt;
  sqlstm.sqltdsp = &sqltds;
  sqlstm.stmt = "";
  sqlstm.iters = (unsigned int  )vInsertCount;
  sqlstm.offset = (unsigned int  )2034;
  sqlstm.cud = sqlcud0;
  sqlstm.sqlest = (unsigned char  *)&sqlca;
  sqlstm.sqlety = (unsigned short)4352;
  sqlstm.occurs = (unsigned int  )9;
  sqlstm.sqhstv[0] = (         void  *)vbeta;
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


		/* EXEC SQL FOR :vInsertCount SET DESCRIPTOR 'inCLNN' VALUE 10 DATA = :vlambda; */ 

{
  struct sqlexd sqlstm;
  sqlstm.sqlvsn = 13;
  sqlstm.arrsiz = 4;
  sqlstm.sqladtp = &sqladt;
  sqlstm.sqltdsp = &sqltds;
  sqlstm.stmt = "";
  sqlstm.iters = (unsigned int  )vInsertCount;
  sqlstm.offset = (unsigned int  )2059;
  sqlstm.cud = sqlcud0;
  sqlstm.sqlest = (unsigned char  *)&sqlca;
  sqlstm.sqlety = (unsigned short)4352;
  sqlstm.occurs = (unsigned int  )10;
  sqlstm.sqhstv[0] = (         void  *)vlambda;
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


		/* EXEC SQL FOR :vInsertCount SET DESCRIPTOR 'inCLNN' VALUE 11 DATA = :vlambdau; */ 

{
  struct sqlexd sqlstm;
  sqlstm.sqlvsn = 13;
  sqlstm.arrsiz = 4;
  sqlstm.sqladtp = &sqladt;
  sqlstm.sqltdsp = &sqltds;
  sqlstm.stmt = "";
  sqlstm.iters = (unsigned int  )vInsertCount;
  sqlstm.offset = (unsigned int  )2084;
  sqlstm.cud = sqlcud0;
  sqlstm.sqlest = (unsigned char  *)&sqlca;
  sqlstm.sqlety = (unsigned short)4352;
  sqlstm.occurs = (unsigned int  )11;
  sqlstm.sqhstv[0] = (         void  *)vlambdau;
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


		/* EXEC SQL FOR :vInsertCount SET DESCRIPTOR 'inCLNN' VALUE 12 DATA = :vrnorm; */ 

{
  struct sqlexd sqlstm;
  sqlstm.sqlvsn = 13;
  sqlstm.arrsiz = 4;
  sqlstm.sqladtp = &sqladt;
  sqlstm.sqltdsp = &sqltds;
  sqlstm.stmt = "";
  sqlstm.iters = (unsigned int  )vInsertCount;
  sqlstm.offset = (unsigned int  )2109;
  sqlstm.cud = sqlcud0;
  sqlstm.sqlest = (unsigned char  *)&sqlca;
  sqlstm.sqlety = (unsigned short)4352;
  sqlstm.occurs = (unsigned int  )12;
  sqlstm.sqhstv[0] = (         void  *)vrnorm;
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


		/* EXEC SQL FOR :vInsertCount SET DESCRIPTOR 'inCLNN' VALUE 13 DATA = :venorm; */ 

{
  struct sqlexd sqlstm;
  sqlstm.sqlvsn = 13;
  sqlstm.arrsiz = 4;
  sqlstm.sqladtp = &sqladt;
  sqlstm.sqltdsp = &sqltds;
  sqlstm.stmt = "";
  sqlstm.iters = (unsigned int  )vInsertCount;
  sqlstm.offset = (unsigned int  )2134;
  sqlstm.cud = sqlcud0;
  sqlstm.sqlest = (unsigned char  *)&sqlca;
  sqlstm.sqlety = (unsigned short)4352;
  sqlstm.occurs = (unsigned int  )13;
  sqlstm.sqhstv[0] = (         void  *)venorm;
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


		/* EXEC SQL FOR :vInsertCount SET DESCRIPTOR 'inCLNN' VALUE 14 DATA = :vcomp; */ 

{
  struct sqlexd sqlstm;
  sqlstm.sqlvsn = 13;
  sqlstm.arrsiz = 4;
  sqlstm.sqladtp = &sqladt;
  sqlstm.sqltdsp = &sqltds;
  sqlstm.stmt = "";
  sqlstm.iters = (unsigned int  )vInsertCount;
  sqlstm.offset = (unsigned int  )2159;
  sqlstm.cud = sqlcud0;
  sqlstm.sqlest = (unsigned char  *)&sqlca;
  sqlstm.sqlety = (unsigned short)4352;
  sqlstm.occurs = (unsigned int  )14;
  sqlstm.sqhstv[0] = (         void  *)vcomp;
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



		break;
	case BP_STD:
		return 0;
		break;
	}

	//-- 4. Execute Array Insert statement
	/* EXEC SQL PREPARE DynIns FROM :stmt; */ 

{
 struct sqlexd sqlstm;
 sqlstm.sqlvsn = 13;
 sqlstm.arrsiz = 4;
 sqlstm.sqladtp = &sqladt;
 sqlstm.sqltdsp = &sqltds;
 sqlstm.stmt = "";
 sqlstm.iters = (unsigned int  )1;
 sqlstm.offset = (unsigned int  )2184;
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


	/* EXEC SQL FOR :vInsertCount EXECUTE DynIns USING DESCRIPTOR 'inCLNN'; */ 

{
 struct sqlexd sqlstm;
 sqlstm.sqlvsn = 13;
 sqlstm.arrsiz = 4;
 sqlstm.sqladtp = &sqladt;
 sqlstm.sqltdsp = &sqltds;
 sqlstm.stmt = "";
 sqlstm.iters = (unsigned int  )vInsertCount;
 sqlstm.offset = (unsigned int  )2203;
 sqlstm.cud = sqlcud0;
 sqlstm.sqlest = (unsigned char  *)&sqlca;
 sqlstm.sqlety = (unsigned short)4352;
 sqlstm.occurs = (unsigned int  )0;
 sqlcxt(&vCtx, &sqlctx, &sqlstm, &sqlfpn);
}


	LogWrite_C(DebugParms, LOG_INFO, "Ora_InsertCoreLogs_NN() inserted %d rows.\n", 1, sqlca.sqlerrd[2]);
	if (sqlca.sqlcode != 0) {
		LogWrite_C(DebugParms, LOG_ERROR, "Ora_InsertCoreLogs_NN() failed. SQL Error %d\n", 1, sqlca.sqlcode);
		return sqlca.sqlcode;
	}

	//-- 5. free()s
	/* EXEC SQL DEALLOCATE DESCRIPTOR 'inCLNN'; */ 

{
 struct sqlexd sqlstm;
 sqlstm.sqlvsn = 13;
 sqlstm.arrsiz = 4;
 sqlstm.sqladtp = &sqladt;
 sqlstm.sqltdsp = &sqltds;
 sqlstm.stmt = "";
 sqlstm.iters = (unsigned int  )1;
 sqlstm.offset = (unsigned int  )2224;
 sqlstm.cud = sqlcud0;
 sqlstm.sqlest = (unsigned char  *)&sqlca;
 sqlstm.sqlety = (unsigned short)4352;
 sqlstm.occurs = (unsigned int  )0;
 sqlcxt(&vCtx, &sqlctx, &sqlstm, &sqlfpn);
}


	free(vProcessId); free(vThreadId); free(vEpoch); free(vBPid); free(vK); free(vdelta); free(vmu); free(valpha); free(vbeta); free(vlambda); free(vlambdau); free(vrnorm); free(venorm); free(vcomp);

	return 0;
}
EXPORT int __stdcall Ora_InsertCoreLogs_SOM(tDebugInfo* pDebugParms, int BPAlgo, int pInsertCount, tLogInt* IntLogs) {
	return 0;
}
EXPORT int __stdcall Ora_InsertCoreLogs_SVM(tDebugInfo* DebugParms, tSVMResult* SVMResult) {
	/* EXEC SQL BEGIN DECLARE SECTION; */ 

	sql_context vCtx = DebugParms->DebugDB->DBCtx;
	char stmt[1000];
	/* EXEC SQL END DECLARE SECTION; */ 


	//-- Connects to DB only once
	if (vCtx == NULL) {
		if (OraConnect(DebugParms, DebugParms->DebugDB) != 0) {
			printf("Ora_InsertCoreLogs_SVM() could not connect to Log Database...\n");
			return -1;
		}
		vCtx = DebugParms->DebugDB->DBCtx;
	}
	//-- Builds Insert statement
	sprintf(&stmt[0], "insert into CoreLogs_SVM (ProcessId, ThreadId, SVCount, ThresholdB, maxdiff, L1loss, WVnorm, LEVnorm, KEvCount) values(%d, %d, %d, %f, %f, %f, %f, %f, %d)", SVMResult->ProcessId, SVMResult->ThreadId, SVMResult->SVcount, SVMResult->ThresholdB, SVMResult->maxdiff, SVMResult->L1loss, SVMResult->WVnorm, SVMResult->LEVnorm, SVMResult->KEvCount);

	//-- Executes Insert statements
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
 sqlstm.offset = (unsigned int  )2245;
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
		if (sqlca.sqlcode != 1) LogWrite_C(DebugParms, LOG_ERROR, "Ora_InsertCoreLogs_SVM() failed. SQL Error %d\n", 1, sqlca.sqlcode);
		return sqlca.sqlcode;
	}
	return 0;

}
//--
EXPORT int __stdcall Ora_BulkMSEInsert(tDebugInfo* DebugParms, int* pInsertCount, tLogMSE* MSEData){
	/* EXEC SQL BEGIN DECLARE SECTION; */ 

	int i;
	int vInsertCount;
	sql_context vCtx = DebugParms->DebugDB->DBCtx;
	char stmt[1000];
	//--
	int* vProcessId;
	int* vThreadId;
	int* vTestId;
	int* vLayerId;
	int* vCoreId;
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
	LogWrite_C(DebugParms, LOG_INFO, "BulkMSEInsert() CheckPoint 1 - LogDB->DBCtx=%p\n", 1, DebugParms->DebugDB->DBCtx);

	if (vCtx == NULL){
		if (OraConnect(DebugParms, DebugParms->DebugDB) != 0) LogWrite_C(DebugParms, LOG_ERROR, "BulkMSEInsert could not connect to Log Database...\n", 0);
		vCtx = DebugParms->DebugDB->DBCtx;
	}
	LogWrite_C(DebugParms, LOG_INFO, "BulkMSEInsert() CheckPoint 2 - LogDB->DBCtx=%p , vCtx=%p\n", 2, DebugParms->DebugDB->DBCtx, vCtx);

	vInsertCount = (*pInsertCount);
	vProcessId = (int*)malloc(vInsertCount*sizeof(int));
	vThreadId = (int*)malloc(vInsertCount*sizeof(int));
	vTestId = (int*)malloc(vInsertCount*sizeof(int));
	vLayerId = (int*)malloc(vInsertCount*sizeof(int));
	vCoreId = (int*)malloc(vInsertCount*sizeof(int));
	vEpoch = (int*)malloc(vInsertCount*sizeof(int));
	vMSE_T = (double*)malloc(vInsertCount*sizeof(double));
	vMSE_V = (double*)malloc(vInsertCount*sizeof(double));

	for (i = 0; i < vInsertCount; i++){
		vProcessId[i] = MSEData[i].ProcessId;
		vThreadId[i] = MSEData[i].ThreadId;
		vTestId[i] = MSEData[i].TestId;
		vLayerId[i] = MSEData[i].LayerId;
		vCoreId[i] = MSEData[i].CoreId;
		vEpoch[i] = MSEData[i].Epoch;
		vMSE_T[i] = MSEData[i].MSE_T;
		vMSE_V[i] = MSEData[i].MSE_V;
		//LogWrite_C(DebugParms, LOG_INFO, "BulkMSEInsert() CheckPoint 3.1 - vProcessId[%d][%d]=%d ; vThreadId[%d][%d]=%d ; vTestId[%d][%d]=%d ; vEpoch[%d][%d]=%d ; vMSE_T[%d][%d]=%f \n", 15, d, i, vProcessId[d][i], d, i, vThreadId[d][i], d, i, vTestId[d][i], d, i, vCoreId[d][i], d, i, vEpoch[d][i], d, i, vMSE_T[d][i]);
	}

	//-- Then, Build the Insert statement
	sprintf(&stmt[0], "insert into MyLog_MSE (ProcessId, ThreadId, TestId, LayerId, CoreId, Epoch, MSE_T, MSE_V) values(:P01, :P02, :P03, :P04, :P05, :P06, :P07, :P08)");
	LogWrite_C(DebugParms, LOG_INFO, "BulkMSEInsert() CheckPoint 4 - stmt='%s'\n", 1, stmt);

	/* EXEC SQL CONTEXT USE :vCtx; */ 

	//EXEC SQL ALTER SESSION SET EVENTS '10046 trace name context forever, level 4';
	//EXEC SQL ALTER SESSION SET SQL_TRACE = TRUE;
	/* EXEC SQL FOR :vInsertCount ALLOCATE DESCRIPTOR 'inMSE'; */ 

{
 struct sqlexd sqlstm;
 sqlstm.sqlvsn = 13;
 sqlstm.arrsiz = 4;
 sqlstm.sqladtp = &sqladt;
 sqlstm.sqltdsp = &sqltds;
 sqlstm.stmt = "";
 sqlstm.iters = (unsigned int  )vInsertCount;
 sqlstm.offset = (unsigned int  )2264;
 sqlstm.cud = sqlcud0;
 sqlstm.sqlest = (unsigned char  *)&sqlca;
 sqlstm.sqlety = (unsigned short)4352;
 sqlstm.occurs = (unsigned int  )100;
 sqlcxt(&vCtx, &sqlctx, &sqlstm, &sqlfpn);
}


	/* EXEC SQL SET DESCRIPTOR 'inMSE' COUNT = 8; */ 

{
 struct sqlexd sqlstm;
 sqlstm.sqlvsn = 13;
 sqlstm.arrsiz = 4;
 sqlstm.sqladtp = &sqladt;
 sqlstm.sqltdsp = &sqltds;
 sqlstm.stmt = "";
 sqlstm.iters = (unsigned int  )1;
 sqlstm.offset = (unsigned int  )2284;
 sqlstm.cud = sqlcud0;
 sqlstm.sqlest = (unsigned char  *)&sqlca;
 sqlstm.sqlety = (unsigned short)4352;
 sqlstm.occurs = (unsigned int  )8;
 sqlcxt(&vCtx, &sqlctx, &sqlstm, &sqlfpn);
}


	/* EXEC SQL FOR :vInsertCount SET DESCRIPTOR 'inMSE' VALUE 1 DATA = :vProcessId; */ 

{
 struct sqlexd sqlstm;
 sqlstm.sqlvsn = 13;
 sqlstm.arrsiz = 4;
 sqlstm.sqladtp = &sqladt;
 sqlstm.sqltdsp = &sqltds;
 sqlstm.stmt = "";
 sqlstm.iters = (unsigned int  )vInsertCount;
 sqlstm.offset = (unsigned int  )2304;
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


	/* EXEC SQL FOR :vInsertCount SET DESCRIPTOR 'inMSE' VALUE 2 DATA = :vThreadId; */ 

{
 struct sqlexd sqlstm;
 sqlstm.sqlvsn = 13;
 sqlstm.arrsiz = 4;
 sqlstm.sqladtp = &sqladt;
 sqlstm.sqltdsp = &sqltds;
 sqlstm.stmt = "";
 sqlstm.iters = (unsigned int  )vInsertCount;
 sqlstm.offset = (unsigned int  )2328;
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


	/* EXEC SQL FOR :vInsertCount SET DESCRIPTOR 'inMSE' VALUE 3 DATA = :vTestId; */ 

{
 struct sqlexd sqlstm;
 sqlstm.sqlvsn = 13;
 sqlstm.arrsiz = 4;
 sqlstm.sqladtp = &sqladt;
 sqlstm.sqltdsp = &sqltds;
 sqlstm.stmt = "";
 sqlstm.iters = (unsigned int  )vInsertCount;
 sqlstm.offset = (unsigned int  )2352;
 sqlstm.cud = sqlcud0;
 sqlstm.sqlest = (unsigned char  *)&sqlca;
 sqlstm.sqlety = (unsigned short)4352;
 sqlstm.occurs = (unsigned int  )3;
 sqlstm.sqhstv[0] = (         void  *)vTestId;
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


	/* EXEC SQL FOR :vInsertCount SET DESCRIPTOR 'inMSE' VALUE 4 DATA = :vLayerId; */ 

{
 struct sqlexd sqlstm;
 sqlstm.sqlvsn = 13;
 sqlstm.arrsiz = 4;
 sqlstm.sqladtp = &sqladt;
 sqlstm.sqltdsp = &sqltds;
 sqlstm.stmt = "";
 sqlstm.iters = (unsigned int  )vInsertCount;
 sqlstm.offset = (unsigned int  )2376;
 sqlstm.cud = sqlcud0;
 sqlstm.sqlest = (unsigned char  *)&sqlca;
 sqlstm.sqlety = (unsigned short)4352;
 sqlstm.occurs = (unsigned int  )4;
 sqlstm.sqhstv[0] = (         void  *)vLayerId;
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


	/* EXEC SQL FOR :vInsertCount SET DESCRIPTOR 'inMSE' VALUE 5 DATA = :vCoreId; */ 

{
 struct sqlexd sqlstm;
 sqlstm.sqlvsn = 13;
 sqlstm.arrsiz = 4;
 sqlstm.sqladtp = &sqladt;
 sqlstm.sqltdsp = &sqltds;
 sqlstm.stmt = "";
 sqlstm.iters = (unsigned int  )vInsertCount;
 sqlstm.offset = (unsigned int  )2400;
 sqlstm.cud = sqlcud0;
 sqlstm.sqlest = (unsigned char  *)&sqlca;
 sqlstm.sqlety = (unsigned short)4352;
 sqlstm.occurs = (unsigned int  )5;
 sqlstm.sqhstv[0] = (         void  *)vCoreId;
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


	/* EXEC SQL FOR :vInsertCount SET DESCRIPTOR 'inMSE' VALUE 6 DATA = :vEpoch; */ 

{
 struct sqlexd sqlstm;
 sqlstm.sqlvsn = 13;
 sqlstm.arrsiz = 4;
 sqlstm.sqladtp = &sqladt;
 sqlstm.sqltdsp = &sqltds;
 sqlstm.stmt = "";
 sqlstm.iters = (unsigned int  )vInsertCount;
 sqlstm.offset = (unsigned int  )2424;
 sqlstm.cud = sqlcud0;
 sqlstm.sqlest = (unsigned char  *)&sqlca;
 sqlstm.sqlety = (unsigned short)4352;
 sqlstm.occurs = (unsigned int  )6;
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


	/* EXEC SQL FOR :vInsertCount SET DESCRIPTOR 'inMSE' VALUE 7 DATA = :vMSE_T; */ 

{
 struct sqlexd sqlstm;
 sqlstm.sqlvsn = 13;
 sqlstm.arrsiz = 4;
 sqlstm.sqladtp = &sqladt;
 sqlstm.sqltdsp = &sqltds;
 sqlstm.stmt = "";
 sqlstm.iters = (unsigned int  )vInsertCount;
 sqlstm.offset = (unsigned int  )2448;
 sqlstm.cud = sqlcud0;
 sqlstm.sqlest = (unsigned char  *)&sqlca;
 sqlstm.sqlety = (unsigned short)4352;
 sqlstm.occurs = (unsigned int  )7;
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


	/* EXEC SQL FOR :vInsertCount SET DESCRIPTOR 'inMSE' VALUE 8 DATA = :vMSE_V; */ 

{
 struct sqlexd sqlstm;
 sqlstm.sqlvsn = 13;
 sqlstm.arrsiz = 4;
 sqlstm.sqladtp = &sqladt;
 sqlstm.sqltdsp = &sqltds;
 sqlstm.stmt = "";
 sqlstm.iters = (unsigned int  )vInsertCount;
 sqlstm.offset = (unsigned int  )2472;
 sqlstm.cud = sqlcud0;
 sqlstm.sqlest = (unsigned char  *)&sqlca;
 sqlstm.sqlety = (unsigned short)4352;
 sqlstm.occurs = (unsigned int  )8;
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


	/* EXEC SQL PREPARE DynIns FROM :stmt; */ 

{
 struct sqlexd sqlstm;
 sqlstm.sqlvsn = 13;
 sqlstm.arrsiz = 4;
 sqlstm.sqladtp = &sqladt;
 sqlstm.sqltdsp = &sqltds;
 sqlstm.stmt = "";
 sqlstm.iters = (unsigned int  )1;
 sqlstm.offset = (unsigned int  )2496;
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


	/* EXEC SQL FOR :vInsertCount EXECUTE DynIns USING DESCRIPTOR 'inMSE'; */ 

{
 struct sqlexd sqlstm;
 sqlstm.sqlvsn = 13;
 sqlstm.arrsiz = 4;
 sqlstm.sqladtp = &sqladt;
 sqlstm.sqltdsp = &sqltds;
 sqlstm.stmt = "";
 sqlstm.iters = (unsigned int  )vInsertCount;
 sqlstm.offset = (unsigned int  )2515;
 sqlstm.cud = sqlcud0;
 sqlstm.sqlest = (unsigned char  *)&sqlca;
 sqlstm.sqlety = (unsigned short)4352;
 sqlstm.occurs = (unsigned int  )0;
 sqlcxt(&vCtx, &sqlctx, &sqlstm, &sqlfpn);
}


	LogWrite_C(DebugParms, LOG_INFO, "BulkMSEInsert() CheckPoint 5\n", 0);
	//EXEC SQL ALTER SESSION SET SQL_TRACE = FALSE;

	//pInsertCount[vNetLevel] = sqlca.sqlerrd[2];
	LogWrite_C(DebugParms, LOG_INFO, "BulkMSEInsert() inserted %d rows.\n", 1, sqlca.sqlerrd[2]);
	if (sqlca.sqlcode != 0){
		if (sqlca.sqlcode != 1) LogWrite_C(DebugParms, LOG_ERROR, "BulkMSEInsert failed. SQL Error %d\n", 1, sqlca.sqlcode);
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
 sqlstm.offset = (unsigned int  )2535;
 sqlstm.cud = sqlcud0;
 sqlstm.sqlest = (unsigned char  *)&sqlca;
 sqlstm.sqlety = (unsigned short)4352;
 sqlstm.occurs = (unsigned int  )0;
 sqlcxt(&vCtx, &sqlctx, &sqlstm, &sqlfpn);
}



	//-- free()s
	free(vProcessId);
	free(vThreadId);
	free(vTestId);
	free(vLayerId);
	free(vCoreId);
	free(vEpoch);
	free(vMSE_T);
	free(vMSE_V);

	return sqlca.sqlcode;
}
EXPORT int __stdcall Ora_BulkRunInsert(tDebugInfo* DebugParms, int* pInsertCount, int pHistoryLen, tLogRUN* RunData){
	//-- pHistoryLen only needed to know where to insert the "spacer"
	/* EXEC SQL BEGIN DECLARE SECTION; */ 

	int i;
	sql_context vCtx = DebugParms->DebugDB->DBCtx;
	int vInsertCount;
	char stmt[1000];
	//--
	int* vProcessId;
	int* vThreadId;
	int* vNetProcessId;
	int* vNetThreadId;
	int* vTestId;
	int* vLayerId;
	int* vCoreId;
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
	if (vCtx == NULL){
		if (OraConnect(DebugParms, DebugParms->DebugDB) != 0) printf("Ora_BulkRunInsert() could not connect to Log Database...\n");
		vCtx = DebugParms->DebugDB->DBCtx;
	}

	vInsertCount = (*pInsertCount);

	vProcessId = (int*)malloc(vInsertCount*sizeof(int));
	vThreadId = (int*)malloc(vInsertCount*sizeof(int));
	vNetProcessId = (int*)malloc(vInsertCount*sizeof(int));
	vNetThreadId = (int*)malloc(vInsertCount*sizeof(int));
	vTestId = (int*)malloc(vInsertCount*sizeof(int));
	vLayerId = (int*)malloc(vInsertCount*sizeof(int));
	vCoreId = (int*)malloc(vInsertCount*sizeof(int));
	vPos = (int*)malloc(vInsertCount*sizeof(int));
	vActual = (double*)malloc(vInsertCount*sizeof(double));
	vPredicted = (double*)malloc(vInsertCount*sizeof(double));
	vError = (double*)malloc(vInsertCount*sizeof(double));
	vActual_TRS = (double*)malloc(vInsertCount*sizeof(double));
	vPredicted_TRS = (double*)malloc(vInsertCount*sizeof(double));
	vError_TRS = (double*)malloc(vInsertCount*sizeof(double));
	vBarWidth = (double*)malloc(vInsertCount*sizeof(double));
	vErrorP = (double*)malloc(vInsertCount*sizeof(double));
	for (i = 0; i < vInsertCount; i++){
		vProcessId[i] = RunData[i].ProcessId;
		vThreadId[i] = RunData[i].ThreadId;
		vNetProcessId[i] = RunData[i].NetProcessId;
		vNetThreadId[i] = RunData[i].NetThreadId;
		vTestId[i] = RunData[i].TestId;
		vLayerId[i] = RunData[i].LayerId;
		vCoreId[i] = RunData[i].CoreId;
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
		//LogWrite_C(DebugParms, LOG_INFO, "vProcessId[%d][%d][%d]=%d , vThreadId[%d][%d][%d]=%d , vTestId[%d][%d][%d]=%d , vNetId[%d][%d][%d]=%d, vPos[%d][%d][%d]=%d \n", 20, d, n, i, vProcessId[n][i], d, n, i, vThreadId[n][i], d, n, i, vTestId[n][i], d, n, i, vNetId[n][i], d, n, i, vPos[n][i]);
	}
	//-- Then, Build the Insert statement
	sprintf(&stmt[0], "insert into MyLog_Run (ProcessId, ThreadId, NetProcessId, NetThreadId, TestId, LayerId, CoreId, Pos, Actual, Predicted, Error, ActualC, PredictedC, ErrorC, BarWidth, ErrorP)");
	strcat(stmt, " values(:Run1, :Run2, :Run3, :Run4, :Run5, :Run6, :Run7, :Run8, :Run9, :Run10, :Run11, :Run12, :Run13, :Run14, :Run15, :Run16)");

	/* EXEC SQL CONTEXT USE :vCtx; */ 

	//EXEC SQL ALTER SESSION SET EVENTS '10046 trace name context forever, level 4';
	//EXEC SQL ALTER SESSION SET SQL_TRACE = TRUE;
	/* EXEC SQL FOR :vInsertCount ALLOCATE DESCRIPTOR 'inRun'; */ 

{
 struct sqlexd sqlstm;
 sqlstm.sqlvsn = 13;
 sqlstm.arrsiz = 4;
 sqlstm.sqladtp = &sqladt;
 sqlstm.sqltdsp = &sqltds;
 sqlstm.stmt = "";
 sqlstm.iters = (unsigned int  )vInsertCount;
 sqlstm.offset = (unsigned int  )2555;
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
 sqlstm.offset = (unsigned int  )2575;
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
 sqlstm.offset = (unsigned int  )2599;
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
 sqlstm.offset = (unsigned int  )2623;
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
 sqlstm.offset = (unsigned int  )2647;
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
 sqlstm.offset = (unsigned int  )2671;
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


	/* EXEC SQL SET DESCRIPTOR 'inRun' VALUE 6 TYPE = :int_type; */ 

{
 struct sqlexd sqlstm;
 sqlstm.sqlvsn = 13;
 sqlstm.arrsiz = 4;
 sqlstm.sqladtp = &sqladt;
 sqlstm.sqltdsp = &sqltds;
 sqlstm.stmt = "";
 sqlstm.iters = (unsigned int  )1;
 sqlstm.offset = (unsigned int  )2695;
 sqlstm.cud = sqlcud0;
 sqlstm.sqlest = (unsigned char  *)&sqlca;
 sqlstm.sqlety = (unsigned short)4352;
 sqlstm.occurs = (unsigned int  )6;
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


	/* EXEC SQL SET DESCRIPTOR 'inRun' VALUE 7 TYPE = :int_type; */ 

{
 struct sqlexd sqlstm;
 sqlstm.sqlvsn = 13;
 sqlstm.arrsiz = 4;
 sqlstm.sqladtp = &sqladt;
 sqlstm.sqltdsp = &sqltds;
 sqlstm.stmt = "";
 sqlstm.iters = (unsigned int  )1;
 sqlstm.offset = (unsigned int  )2719;
 sqlstm.cud = sqlcud0;
 sqlstm.sqlest = (unsigned char  *)&sqlca;
 sqlstm.sqlety = (unsigned short)4352;
 sqlstm.occurs = (unsigned int  )7;
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


	/* EXEC SQL SET DESCRIPTOR 'inRun' VALUE 8 TYPE = :int_type; */ 

{
 struct sqlexd sqlstm;
 sqlstm.sqlvsn = 13;
 sqlstm.arrsiz = 4;
 sqlstm.sqladtp = &sqladt;
 sqlstm.sqltdsp = &sqltds;
 sqlstm.stmt = "";
 sqlstm.iters = (unsigned int  )1;
 sqlstm.offset = (unsigned int  )2743;
 sqlstm.cud = sqlcud0;
 sqlstm.sqlest = (unsigned char  *)&sqlca;
 sqlstm.sqlety = (unsigned short)4352;
 sqlstm.occurs = (unsigned int  )8;
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


	/* EXEC SQL SET DESCRIPTOR 'inRun' VALUE 9 TYPE = :dbl_type; */ 

{
 struct sqlexd sqlstm;
 sqlstm.sqlvsn = 13;
 sqlstm.arrsiz = 4;
 sqlstm.sqladtp = &sqladt;
 sqlstm.sqltdsp = &sqltds;
 sqlstm.stmt = "";
 sqlstm.iters = (unsigned int  )1;
 sqlstm.offset = (unsigned int  )2767;
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
 sqlstm.offset = (unsigned int  )2791;
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
 sqlstm.offset = (unsigned int  )2815;
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
 sqlstm.offset = (unsigned int  )2839;
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
 sqlstm.offset = (unsigned int  )2863;
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


	/* EXEC SQL SET DESCRIPTOR 'inRun' VALUE 14 TYPE = :dbl_type; */ 

{
 struct sqlexd sqlstm;
 sqlstm.sqlvsn = 13;
 sqlstm.arrsiz = 4;
 sqlstm.sqladtp = &sqladt;
 sqlstm.sqltdsp = &sqltds;
 sqlstm.stmt = "";
 sqlstm.iters = (unsigned int  )1;
 sqlstm.offset = (unsigned int  )2887;
 sqlstm.cud = sqlcud0;
 sqlstm.sqlest = (unsigned char  *)&sqlca;
 sqlstm.sqlety = (unsigned short)4352;
 sqlstm.occurs = (unsigned int  )14;
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


	/* EXEC SQL SET DESCRIPTOR 'inRun' VALUE 15 TYPE = :dbl_type; */ 

{
 struct sqlexd sqlstm;
 sqlstm.sqlvsn = 13;
 sqlstm.arrsiz = 4;
 sqlstm.sqladtp = &sqladt;
 sqlstm.sqltdsp = &sqltds;
 sqlstm.stmt = "";
 sqlstm.iters = (unsigned int  )1;
 sqlstm.offset = (unsigned int  )2911;
 sqlstm.cud = sqlcud0;
 sqlstm.sqlest = (unsigned char  *)&sqlca;
 sqlstm.sqlety = (unsigned short)4352;
 sqlstm.occurs = (unsigned int  )15;
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


	/* EXEC SQL SET DESCRIPTOR 'inRun' VALUE 16 TYPE = :dbl_type; */ 

{
 struct sqlexd sqlstm;
 sqlstm.sqlvsn = 13;
 sqlstm.arrsiz = 4;
 sqlstm.sqladtp = &sqladt;
 sqlstm.sqltdsp = &sqltds;
 sqlstm.stmt = "";
 sqlstm.iters = (unsigned int  )1;
 sqlstm.offset = (unsigned int  )2935;
 sqlstm.cud = sqlcud0;
 sqlstm.sqlest = (unsigned char  *)&sqlca;
 sqlstm.sqlety = (unsigned short)4352;
 sqlstm.occurs = (unsigned int  )16;
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



	/* EXEC SQL SET DESCRIPTOR 'inRun' COUNT = 16; */ 

{
 struct sqlexd sqlstm;
 sqlstm.sqlvsn = 13;
 sqlstm.arrsiz = 4;
 sqlstm.sqladtp = &sqladt;
 sqlstm.sqltdsp = &sqltds;
 sqlstm.stmt = "";
 sqlstm.iters = (unsigned int  )1;
 sqlstm.offset = (unsigned int  )2959;
 sqlstm.cud = sqlcud0;
 sqlstm.sqlest = (unsigned char  *)&sqlca;
 sqlstm.sqlety = (unsigned short)4352;
 sqlstm.occurs = (unsigned int  )16;
 sqlcxt(&vCtx, &sqlctx, &sqlstm, &sqlfpn);
}


	/* EXEC SQL FOR :vInsertCount SET DESCRIPTOR 'inRun' VALUE 1 DATA = :vProcessId; */ 

{
 struct sqlexd sqlstm;
 sqlstm.sqlvsn = 13;
 sqlstm.arrsiz = 4;
 sqlstm.sqladtp = &sqladt;
 sqlstm.sqltdsp = &sqltds;
 sqlstm.stmt = "";
 sqlstm.iters = (unsigned int  )vInsertCount;
 sqlstm.offset = (unsigned int  )2979;
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


	/* EXEC SQL FOR :vInsertCount SET DESCRIPTOR 'inRun' VALUE 2 DATA = :vThreadId; */ 

{
 struct sqlexd sqlstm;
 sqlstm.sqlvsn = 13;
 sqlstm.arrsiz = 4;
 sqlstm.sqladtp = &sqladt;
 sqlstm.sqltdsp = &sqltds;
 sqlstm.stmt = "";
 sqlstm.iters = (unsigned int  )vInsertCount;
 sqlstm.offset = (unsigned int  )3003;
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


	/* EXEC SQL FOR :vInsertCount SET DESCRIPTOR 'inRun' VALUE 3 DATA = :vNetProcessId; */ 

{
 struct sqlexd sqlstm;
 sqlstm.sqlvsn = 13;
 sqlstm.arrsiz = 4;
 sqlstm.sqladtp = &sqladt;
 sqlstm.sqltdsp = &sqltds;
 sqlstm.stmt = "";
 sqlstm.iters = (unsigned int  )vInsertCount;
 sqlstm.offset = (unsigned int  )3027;
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


	/* EXEC SQL FOR :vInsertCount SET DESCRIPTOR 'inRun' VALUE 4 DATA = :vNetThreadId; */ 

{
 struct sqlexd sqlstm;
 sqlstm.sqlvsn = 13;
 sqlstm.arrsiz = 4;
 sqlstm.sqladtp = &sqladt;
 sqlstm.sqltdsp = &sqltds;
 sqlstm.stmt = "";
 sqlstm.iters = (unsigned int  )vInsertCount;
 sqlstm.offset = (unsigned int  )3051;
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


	/* EXEC SQL FOR :vInsertCount SET DESCRIPTOR 'inRun' VALUE 5 DATA = :vTestId; */ 

{
 struct sqlexd sqlstm;
 sqlstm.sqlvsn = 13;
 sqlstm.arrsiz = 4;
 sqlstm.sqladtp = &sqladt;
 sqlstm.sqltdsp = &sqltds;
 sqlstm.stmt = "";
 sqlstm.iters = (unsigned int  )vInsertCount;
 sqlstm.offset = (unsigned int  )3075;
 sqlstm.cud = sqlcud0;
 sqlstm.sqlest = (unsigned char  *)&sqlca;
 sqlstm.sqlety = (unsigned short)4352;
 sqlstm.occurs = (unsigned int  )5;
 sqlstm.sqhstv[0] = (         void  *)vTestId;
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


	/* EXEC SQL FOR :vInsertCount SET DESCRIPTOR 'inRun' VALUE 6 DATA = :vLayerId; */ 

{
 struct sqlexd sqlstm;
 sqlstm.sqlvsn = 13;
 sqlstm.arrsiz = 4;
 sqlstm.sqladtp = &sqladt;
 sqlstm.sqltdsp = &sqltds;
 sqlstm.stmt = "";
 sqlstm.iters = (unsigned int  )vInsertCount;
 sqlstm.offset = (unsigned int  )3099;
 sqlstm.cud = sqlcud0;
 sqlstm.sqlest = (unsigned char  *)&sqlca;
 sqlstm.sqlety = (unsigned short)4352;
 sqlstm.occurs = (unsigned int  )6;
 sqlstm.sqhstv[0] = (         void  *)vLayerId;
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


	/* EXEC SQL FOR :vInsertCount SET DESCRIPTOR 'inRun' VALUE 7 DATA = :vCoreId; */ 

{
 struct sqlexd sqlstm;
 sqlstm.sqlvsn = 13;
 sqlstm.arrsiz = 4;
 sqlstm.sqladtp = &sqladt;
 sqlstm.sqltdsp = &sqltds;
 sqlstm.stmt = "";
 sqlstm.iters = (unsigned int  )vInsertCount;
 sqlstm.offset = (unsigned int  )3123;
 sqlstm.cud = sqlcud0;
 sqlstm.sqlest = (unsigned char  *)&sqlca;
 sqlstm.sqlety = (unsigned short)4352;
 sqlstm.occurs = (unsigned int  )7;
 sqlstm.sqhstv[0] = (         void  *)vCoreId;
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


	/* EXEC SQL FOR :vInsertCount SET DESCRIPTOR 'inRun' VALUE 8 DATA = :vPos; */ 

{
 struct sqlexd sqlstm;
 sqlstm.sqlvsn = 13;
 sqlstm.arrsiz = 4;
 sqlstm.sqladtp = &sqladt;
 sqlstm.sqltdsp = &sqltds;
 sqlstm.stmt = "";
 sqlstm.iters = (unsigned int  )vInsertCount;
 sqlstm.offset = (unsigned int  )3147;
 sqlstm.cud = sqlcud0;
 sqlstm.sqlest = (unsigned char  *)&sqlca;
 sqlstm.sqlety = (unsigned short)4352;
 sqlstm.occurs = (unsigned int  )8;
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


	/* EXEC SQL FOR :vInsertCount SET DESCRIPTOR 'inRun' VALUE 9 DATA = :vActual; */ 

{
 struct sqlexd sqlstm;
 sqlstm.sqlvsn = 13;
 sqlstm.arrsiz = 4;
 sqlstm.sqladtp = &sqladt;
 sqlstm.sqltdsp = &sqltds;
 sqlstm.stmt = "";
 sqlstm.iters = (unsigned int  )vInsertCount;
 sqlstm.offset = (unsigned int  )3171;
 sqlstm.cud = sqlcud0;
 sqlstm.sqlest = (unsigned char  *)&sqlca;
 sqlstm.sqlety = (unsigned short)4352;
 sqlstm.occurs = (unsigned int  )9;
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


	/* EXEC SQL FOR :vInsertCount SET DESCRIPTOR 'inRun' VALUE 10 DATA = :vPredicted; */ 

{
 struct sqlexd sqlstm;
 sqlstm.sqlvsn = 13;
 sqlstm.arrsiz = 4;
 sqlstm.sqladtp = &sqladt;
 sqlstm.sqltdsp = &sqltds;
 sqlstm.stmt = "";
 sqlstm.iters = (unsigned int  )vInsertCount;
 sqlstm.offset = (unsigned int  )3195;
 sqlstm.cud = sqlcud0;
 sqlstm.sqlest = (unsigned char  *)&sqlca;
 sqlstm.sqlety = (unsigned short)4352;
 sqlstm.occurs = (unsigned int  )10;
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


	/* EXEC SQL FOR :vInsertCount SET DESCRIPTOR 'inRun' VALUE 11 DATA = :vError; */ 

{
 struct sqlexd sqlstm;
 sqlstm.sqlvsn = 13;
 sqlstm.arrsiz = 4;
 sqlstm.sqladtp = &sqladt;
 sqlstm.sqltdsp = &sqltds;
 sqlstm.stmt = "";
 sqlstm.iters = (unsigned int  )vInsertCount;
 sqlstm.offset = (unsigned int  )3219;
 sqlstm.cud = sqlcud0;
 sqlstm.sqlest = (unsigned char  *)&sqlca;
 sqlstm.sqlety = (unsigned short)4352;
 sqlstm.occurs = (unsigned int  )11;
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


	/* EXEC SQL FOR :vInsertCount SET DESCRIPTOR 'inRun' VALUE 12 DATA = :vActual_TRS; */ 

{
 struct sqlexd sqlstm;
 sqlstm.sqlvsn = 13;
 sqlstm.arrsiz = 4;
 sqlstm.sqladtp = &sqladt;
 sqlstm.sqltdsp = &sqltds;
 sqlstm.stmt = "";
 sqlstm.iters = (unsigned int  )vInsertCount;
 sqlstm.offset = (unsigned int  )3243;
 sqlstm.cud = sqlcud0;
 sqlstm.sqlest = (unsigned char  *)&sqlca;
 sqlstm.sqlety = (unsigned short)4352;
 sqlstm.occurs = (unsigned int  )12;
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


	/* EXEC SQL FOR :vInsertCount SET DESCRIPTOR 'inRun' VALUE 13 DATA = :vPredicted_TRS; */ 

{
 struct sqlexd sqlstm;
 sqlstm.sqlvsn = 13;
 sqlstm.arrsiz = 4;
 sqlstm.sqladtp = &sqladt;
 sqlstm.sqltdsp = &sqltds;
 sqlstm.stmt = "";
 sqlstm.iters = (unsigned int  )vInsertCount;
 sqlstm.offset = (unsigned int  )3267;
 sqlstm.cud = sqlcud0;
 sqlstm.sqlest = (unsigned char  *)&sqlca;
 sqlstm.sqlety = (unsigned short)4352;
 sqlstm.occurs = (unsigned int  )13;
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


	/* EXEC SQL FOR :vInsertCount SET DESCRIPTOR 'inRun' VALUE 14 DATA = :vError_TRS; */ 

{
 struct sqlexd sqlstm;
 sqlstm.sqlvsn = 13;
 sqlstm.arrsiz = 4;
 sqlstm.sqladtp = &sqladt;
 sqlstm.sqltdsp = &sqltds;
 sqlstm.stmt = "";
 sqlstm.iters = (unsigned int  )vInsertCount;
 sqlstm.offset = (unsigned int  )3291;
 sqlstm.cud = sqlcud0;
 sqlstm.sqlest = (unsigned char  *)&sqlca;
 sqlstm.sqlety = (unsigned short)4352;
 sqlstm.occurs = (unsigned int  )14;
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


	/* EXEC SQL FOR :vInsertCount SET DESCRIPTOR 'inRun' VALUE 15 DATA = :vBarWidth; */ 

{
 struct sqlexd sqlstm;
 sqlstm.sqlvsn = 13;
 sqlstm.arrsiz = 4;
 sqlstm.sqladtp = &sqladt;
 sqlstm.sqltdsp = &sqltds;
 sqlstm.stmt = "";
 sqlstm.iters = (unsigned int  )vInsertCount;
 sqlstm.offset = (unsigned int  )3315;
 sqlstm.cud = sqlcud0;
 sqlstm.sqlest = (unsigned char  *)&sqlca;
 sqlstm.sqlety = (unsigned short)4352;
 sqlstm.occurs = (unsigned int  )15;
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


	/* EXEC SQL FOR :vInsertCount SET DESCRIPTOR 'inRun' VALUE 16 DATA = :vErrorP; */ 

{
 struct sqlexd sqlstm;
 sqlstm.sqlvsn = 13;
 sqlstm.arrsiz = 4;
 sqlstm.sqladtp = &sqladt;
 sqlstm.sqltdsp = &sqltds;
 sqlstm.stmt = "";
 sqlstm.iters = (unsigned int  )vInsertCount;
 sqlstm.offset = (unsigned int  )3339;
 sqlstm.cud = sqlcud0;
 sqlstm.sqlest = (unsigned char  *)&sqlca;
 sqlstm.sqlety = (unsigned short)4352;
 sqlstm.occurs = (unsigned int  )16;
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



	/* EXEC SQL PREPARE DynIns FROM :stmt; */ 

{
 struct sqlexd sqlstm;
 sqlstm.sqlvsn = 13;
 sqlstm.arrsiz = 4;
 sqlstm.sqladtp = &sqladt;
 sqlstm.sqltdsp = &sqltds;
 sqlstm.stmt = "";
 sqlstm.iters = (unsigned int  )1;
 sqlstm.offset = (unsigned int  )3363;
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


	/* EXEC SQL FOR :vInsertCount EXECUTE DynIns USING DESCRIPTOR 'inRun'; */ 

{
 struct sqlexd sqlstm;
 sqlstm.sqlvsn = 13;
 sqlstm.arrsiz = 4;
 sqlstm.sqladtp = &sqladt;
 sqlstm.sqltdsp = &sqltds;
 sqlstm.stmt = "";
 sqlstm.iters = (unsigned int  )vInsertCount;
 sqlstm.offset = (unsigned int  )3382;
 sqlstm.cud = sqlcud0;
 sqlstm.sqlest = (unsigned char  *)&sqlca;
 sqlstm.sqlety = (unsigned short)4352;
 sqlstm.occurs = (unsigned int  )0;
 sqlcxt(&vCtx, &sqlctx, &sqlstm, &sqlfpn);
}


	//EXEC SQL ALTER SESSION SET SQL_TRACE = FALSE;

	(*pInsertCount) = sqlca.sqlerrd[2];
	LogWrite_C(DebugParms, LOG_INFO, "BulkRunInsert() CheckPoint 3 - InsertCount=%d\n", 1, (*pInsertCount));
	LogWrite_C(DebugParms, LOG_INFO, "BulkRunInsert() CheckPoint 4 - sqlca.sqlcode=%d\n", 1, sqlca.sqlcode);
	if (sqlca.sqlcode != 0){
		if (sqlca.sqlcode != 1){
			LogWrite_C(DebugParms, LOG_ERROR, "BulkRunInsert failed. SQL Error %d\n", 1, sqlca.sqlcode);
		}
		return sqlca.sqlcode;
	}

	//-- Need to insert the spacer that is no longer created in MyNN.cpp
	sprintf(&stmt[0], "insert into MyLog_Run (ProcessId, ThreadId, NetProcessId, NetThreadId, TestId, LayerId, CoreId, Pos, Actual, Predicted, Error, ActualC, PredictedC, ErrorC) \
						  						values(%d, %d, %d, %d, %d, %d, %d, %f, NULL, NULL, NULL, NULL, NULL, NULL)", \
												vProcessId[0], vThreadId[0], vNetProcessId[0], vNetThreadId[0], vTestId[0], vLayerId[0], vCoreId[0], (vPos[pHistoryLen - 1] + 0.5) );
	/* EXEC SQL EXECUTE IMMEDIATE :stmt; */ 

{
 struct sqlexd sqlstm;
 sqlstm.sqlvsn = 13;
 sqlstm.arrsiz = 4;
 sqlstm.sqladtp = &sqladt;
 sqlstm.sqltdsp = &sqltds;
 sqlstm.stmt = "";
 sqlstm.iters = (unsigned int  )1;
 sqlstm.offset = (unsigned int  )3402;
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


	if (sqlca.sqlcode != 0){
		if (sqlca.sqlcode != 1403){
			LogWrite_C(DebugParms, LOG_ERROR, "Inserting spacer in MyLog_Run failed. SQL Error %d\n", 1, sqlca.sqlcode);
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
 sqlstm.offset = (unsigned int  )3421;
 sqlstm.cud = sqlcud0;
 sqlstm.sqlest = (unsigned char  *)&sqlca;
 sqlstm.sqlety = (unsigned short)4352;
 sqlstm.occurs = (unsigned int  )0;
 sqlcxt(&vCtx, &sqlctx, &sqlstm, &sqlfpn);
}



	//-- Fixing the '0' values on actual that mess up excel charts
	strcpy(&stmt[0], "update MyLog_Run set Predicted=NULL, Error=NULL, PredictedC=NULL, ErrorC=NULL, BarWidth=NULL, ErrorP=NULL where Predicted=0");
	/* EXEC SQL EXECUTE IMMEDIATE :stmt; */ 

{
 struct sqlexd sqlstm;
 sqlstm.sqlvsn = 13;
 sqlstm.arrsiz = 4;
 sqlstm.sqladtp = &sqladt;
 sqlstm.sqltdsp = &sqltds;
 sqlstm.stmt = "";
 sqlstm.iters = (unsigned int  )1;
 sqlstm.offset = (unsigned int  )3441;
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
			LogWrite_C(DebugParms, LOG_ERROR, "Updating 0s in MyLog_Run failed. SQL Error %d\n", 1, sqlca.sqlcode);
			return sqlca.sqlcode;
		}
	}

	strcpy(&stmt[0], "update MyLog_Run set Actual=NULL, ActualC=NULL, Error=NULL, ErrorP=NULL where Actual=0");
	/* EXEC SQL EXECUTE IMMEDIATE :stmt; */ 

{
 struct sqlexd sqlstm;
 sqlstm.sqlvsn = 13;
 sqlstm.arrsiz = 4;
 sqlstm.sqladtp = &sqladt;
 sqlstm.sqltdsp = &sqltds;
 sqlstm.stmt = "";
 sqlstm.iters = (unsigned int  )1;
 sqlstm.offset = (unsigned int  )3460;
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


	if (sqlca.sqlcode != 0){
		if (sqlca.sqlcode != 1403){
			LogWrite_C(DebugParms, LOG_ERROR, "Updating 0s in MyLog_Run failed. SQL Error %d\n", 1, sqlca.sqlcode);
			return sqlca.sqlcode;
		}
	}

	//-- free()s
	free(vProcessId);
	free(vThreadId);
	free(vNetProcessId);
	free(vNetThreadId);
	free(vTestId);
	free(vLayerId);
	free(vCoreId);
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
//===

//=== Internals Logs (unused)
EXPORT int __stdcall Ora_BulkInternalsInsert_NN_aF(tDebugInfo* DebugParms, NN_Parms* NN, tCoreLog* NNLogs, int pid, int testid, int pDatasetsCount, int pTimeSteps, double****a, double**** F) {
	/* EXEC SQL BEGIN DECLARE SECTION; */ 

	int d, l, t, j;
	int vInsertCount; int idx;
	sql_context vCtx = DebugParms->DebugDB->DBCtx;
	char stmt[1000];
	int dbl_type = 22;	// Oracle SQLT_BDOUBLE
	int int_type = 3;	// 
	unsigned int dbl_len = sizeof(double);
	unsigned int vchar_type = 96;
	unsigned int vchar_len = 12 + 1;

	int* vProcessId;
	int* vThreadId;
	int* vTestId;
	int* vDatasetId;
	int* vLayerId;
	int* vTimeStepId;

	int* vNeuron;
	double*  vInVal;
	double*  vOutVal;

	/* EXEC SQL END DECLARE SECTION; */ 


	//-- Connects to DB only once
	if (vCtx == NULL) {
		if (OraConnect(DebugParms, DebugParms->DebugDB) != 0) LogWrite_C(DebugParms, LOG_ERROR, "Ora_BulkInternalsInsert_NN_W() could not connect to Log Database...\n", 0);
		vCtx = DebugParms->DebugDB->DBCtx;
	}

	//-- mallocs
	vInsertCount = 0; idx = 0;
	for (d = 0; d < pDatasetsCount; d++) {
		for (l = 0; l < NN->LevelsCount; l++) {
			for (t = 0; t < pTimeSteps; t++) {
				for (j = 0; j < NN->NodesCount[l]; j++) {
					vInsertCount++;
				}
			}
		}
	}
	vProcessId = (int*)malloc(vInsertCount * sizeof(int));
	vThreadId = (int*)malloc(vInsertCount * sizeof(int));
	vTestId = (int*)malloc(vInsertCount * sizeof(int));
	vDatasetId = (int*)malloc(vInsertCount * sizeof(int));
	vLayerId = (int*)malloc(vInsertCount * sizeof(int));
	vTimeStepId = (int*)malloc(vInsertCount * sizeof(int));
	vNeuron = (int*)malloc(vInsertCount * sizeof(int));
	vInVal = (double*)malloc(vInsertCount * sizeof(double));
	vOutVal = (double*)malloc(vInsertCount * sizeof(double));

	/* EXEC SQL CONTEXT USE : vCtx; */ 

	/* EXEC SQL FOR : vInsertCount ALLOCATE DESCRIPTOR 'inINTN'; */ 

{
 struct sqlexd sqlstm;
 sqlstm.sqlvsn = 13;
 sqlstm.arrsiz = 4;
 sqlstm.sqladtp = &sqladt;
 sqlstm.sqltdsp = &sqltds;
 sqlstm.stmt = "";
 sqlstm.iters = (unsigned int  )vInsertCount;
 sqlstm.offset = (unsigned int  )3479;
 sqlstm.cud = sqlcud0;
 sqlstm.sqlest = (unsigned char  *)&sqlca;
 sqlstm.sqlety = (unsigned short)4352;
 sqlstm.occurs = (unsigned int  )100;
 sqlcxt(&vCtx, &sqlctx, &sqlstm, &sqlfpn);
}



	//-- assignments
	for (d = 0; d < pDatasetsCount; d++) {
		for (l = 0; l < NN->LevelsCount; l++) {
			for (t = 0; t < pTimeSteps; t++) {
				for (j = 0; j < NN->NodesCount[l]; j++) {
					vProcessId[idx] = pid;
					vThreadId[idx] = 0;	// NNLogs->TrainingTid[d];
					vTestId[idx] = testid;
					vDatasetId[idx] = d;
					vLayerId[idx] = l;
					vTimeStepId[idx] = t;
					vNeuron[idx] = j;
					vInVal[idx] = a[d][l][t][j];
					vOutVal[idx] = F[d][l][t][j];

					idx++;
				}
			}
		}
	}
	//-- Then, Build the Insert statement
	sprintf(&stmt[0], "insert into Internals_NN_N (ProcessId, ThreadId, TestId, TimeStep, NeuronLevel, Neuron, INVal, OUTVal) values(:P01, :P02, :P03, :P04, :P05, :P06, :P07, :P08)");
	LogWrite_C(DebugParms, LOG_INFO, "BulkInternalsInsert() CheckPoint 4 - stmt='%s'\n", 1, stmt);

	/* EXEC SQL SET DESCRIPTOR 'inINTN' COUNT = 8; */ 

{
 struct sqlexd sqlstm;
 sqlstm.sqlvsn = 13;
 sqlstm.arrsiz = 4;
 sqlstm.sqladtp = &sqladt;
 sqlstm.sqltdsp = &sqltds;
 sqlstm.stmt = "";
 sqlstm.iters = (unsigned int  )1;
 sqlstm.offset = (unsigned int  )3500;
 sqlstm.cud = sqlcud0;
 sqlstm.sqlest = (unsigned char  *)&sqlca;
 sqlstm.sqlety = (unsigned short)4352;
 sqlstm.occurs = (unsigned int  )8;
 sqlcxt(&vCtx, &sqlctx, &sqlstm, &sqlfpn);
}


	/* EXEC SQL FOR : vInsertCount SET DESCRIPTOR 'inINTN' VALUE 1 DATA = : vProcessId; */ 

{
 struct sqlexd sqlstm;
 sqlstm.sqlvsn = 13;
 sqlstm.arrsiz = 4;
 sqlstm.sqladtp = &sqladt;
 sqlstm.sqltdsp = &sqltds;
 sqlstm.stmt = "";
 sqlstm.iters = (unsigned int  )vInsertCount;
 sqlstm.offset = (unsigned int  )3521;
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


	/* EXEC SQL FOR : vInsertCount SET DESCRIPTOR 'inINTN' VALUE 2 DATA = : vThreadId; */ 

{
 struct sqlexd sqlstm;
 sqlstm.sqlvsn = 13;
 sqlstm.arrsiz = 4;
 sqlstm.sqladtp = &sqladt;
 sqlstm.sqltdsp = &sqltds;
 sqlstm.stmt = "";
 sqlstm.iters = (unsigned int  )vInsertCount;
 sqlstm.offset = (unsigned int  )3546;
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


	/* EXEC SQL FOR : vInsertCount SET DESCRIPTOR 'inINTN' VALUE 3 DATA = : vTestId; */ 

{
 struct sqlexd sqlstm;
 sqlstm.sqlvsn = 13;
 sqlstm.arrsiz = 4;
 sqlstm.sqladtp = &sqladt;
 sqlstm.sqltdsp = &sqltds;
 sqlstm.stmt = "";
 sqlstm.iters = (unsigned int  )vInsertCount;
 sqlstm.offset = (unsigned int  )3571;
 sqlstm.cud = sqlcud0;
 sqlstm.sqlest = (unsigned char  *)&sqlca;
 sqlstm.sqlety = (unsigned short)4352;
 sqlstm.occurs = (unsigned int  )3;
 sqlstm.sqhstv[0] = (         void  *)vTestId;
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


	/* EXEC SQL FOR : vInsertCount SET DESCRIPTOR 'inINTN' VALUE 4 DATA = : vTimeStepId; */ 

{
 struct sqlexd sqlstm;
 sqlstm.sqlvsn = 13;
 sqlstm.arrsiz = 4;
 sqlstm.sqladtp = &sqladt;
 sqlstm.sqltdsp = &sqltds;
 sqlstm.stmt = "";
 sqlstm.iters = (unsigned int  )vInsertCount;
 sqlstm.offset = (unsigned int  )3596;
 sqlstm.cud = sqlcud0;
 sqlstm.sqlest = (unsigned char  *)&sqlca;
 sqlstm.sqlety = (unsigned short)4352;
 sqlstm.occurs = (unsigned int  )4;
 sqlstm.sqhstv[0] = (         void  *)vTimeStepId;
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


	/* EXEC SQL FOR : vInsertCount SET DESCRIPTOR 'inINTN' VALUE 5 DATA = : vLayerId; */ 

{
 struct sqlexd sqlstm;
 sqlstm.sqlvsn = 13;
 sqlstm.arrsiz = 4;
 sqlstm.sqladtp = &sqladt;
 sqlstm.sqltdsp = &sqltds;
 sqlstm.stmt = "";
 sqlstm.iters = (unsigned int  )vInsertCount;
 sqlstm.offset = (unsigned int  )3621;
 sqlstm.cud = sqlcud0;
 sqlstm.sqlest = (unsigned char  *)&sqlca;
 sqlstm.sqlety = (unsigned short)4352;
 sqlstm.occurs = (unsigned int  )5;
 sqlstm.sqhstv[0] = (         void  *)vLayerId;
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


	/* EXEC SQL FOR : vInsertCount SET DESCRIPTOR 'inINTN' VALUE 6 DATA = : vNeuron; */ 

{
 struct sqlexd sqlstm;
 sqlstm.sqlvsn = 13;
 sqlstm.arrsiz = 4;
 sqlstm.sqladtp = &sqladt;
 sqlstm.sqltdsp = &sqltds;
 sqlstm.stmt = "";
 sqlstm.iters = (unsigned int  )vInsertCount;
 sqlstm.offset = (unsigned int  )3646;
 sqlstm.cud = sqlcud0;
 sqlstm.sqlest = (unsigned char  *)&sqlca;
 sqlstm.sqlety = (unsigned short)4352;
 sqlstm.occurs = (unsigned int  )6;
 sqlstm.sqhstv[0] = (         void  *)vNeuron;
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


	/* EXEC SQL FOR : vInsertCount SET DESCRIPTOR 'inINTN' VALUE 7 DATA = : vInVal; */ 

{
 struct sqlexd sqlstm;
 sqlstm.sqlvsn = 13;
 sqlstm.arrsiz = 4;
 sqlstm.sqladtp = &sqladt;
 sqlstm.sqltdsp = &sqltds;
 sqlstm.stmt = "";
 sqlstm.iters = (unsigned int  )vInsertCount;
 sqlstm.offset = (unsigned int  )3671;
 sqlstm.cud = sqlcud0;
 sqlstm.sqlest = (unsigned char  *)&sqlca;
 sqlstm.sqlety = (unsigned short)4352;
 sqlstm.occurs = (unsigned int  )7;
 sqlstm.sqhstv[0] = (         void  *)vInVal;
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


	/* EXEC SQL FOR : vInsertCount SET DESCRIPTOR 'inINTN' VALUE 8 DATA = : vOutVal; */ 

{
 struct sqlexd sqlstm;
 sqlstm.sqlvsn = 13;
 sqlstm.arrsiz = 4;
 sqlstm.sqladtp = &sqladt;
 sqlstm.sqltdsp = &sqltds;
 sqlstm.stmt = "";
 sqlstm.iters = (unsigned int  )vInsertCount;
 sqlstm.offset = (unsigned int  )3696;
 sqlstm.cud = sqlcud0;
 sqlstm.sqlest = (unsigned char  *)&sqlca;
 sqlstm.sqlety = (unsigned short)4352;
 sqlstm.occurs = (unsigned int  )8;
 sqlstm.sqhstv[0] = (         void  *)vOutVal;
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
 sqlstm.offset = (unsigned int  )3721;
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


	/* EXEC SQL FOR : vInsertCount EXECUTE DynIns USING DESCRIPTOR 'inINTN'; */ 

{
 struct sqlexd sqlstm;
 sqlstm.sqlvsn = 13;
 sqlstm.arrsiz = 4;
 sqlstm.sqladtp = &sqladt;
 sqlstm.sqltdsp = &sqltds;
 sqlstm.stmt = "";
 sqlstm.iters = (unsigned int  )vInsertCount;
 sqlstm.offset = (unsigned int  )3740;
 sqlstm.cud = sqlcud0;
 sqlstm.sqlest = (unsigned char  *)&sqlca;
 sqlstm.sqlety = (unsigned short)4352;
 sqlstm.occurs = (unsigned int  )0;
 sqlcxt(&vCtx, &sqlctx, &sqlstm, &sqlfpn);
}



	LogWrite_C(DebugParms, LOG_INFO, "Ora_BulkInternalsInsert_NN_N() inserted %d rows.\n", 1, sqlca.sqlerrd[2]);
	if (sqlca.sqlcode != 0) {
		LogWrite_C(DebugParms, LOG_ERROR, "Ora_BulkInternalsInsert_NN_N() failed. SQL Error %d\n", 1, sqlca.sqlcode);
		return sqlca.sqlcode;
	}

	//-- free()s
	free(vProcessId);
	free(vThreadId);
	free(vTestId);
	free(vDatasetId);
	free(vLayerId);
	free(vTimeStepId);
	free(vNeuron);
	free(vInVal);
	free(vOutVal);

	/* EXEC SQL DEALLOCATE DESCRIPTOR 'inINTN'; */ 

{
 struct sqlexd sqlstm;
 sqlstm.sqlvsn = 13;
 sqlstm.arrsiz = 4;
 sqlstm.sqladtp = &sqladt;
 sqlstm.sqltdsp = &sqltds;
 sqlstm.stmt = "";
 sqlstm.iters = (unsigned int  )1;
 sqlstm.offset = (unsigned int  )3761;
 sqlstm.cud = sqlcud0;
 sqlstm.sqlest = (unsigned char  *)&sqlca;
 sqlstm.sqlety = (unsigned short)4352;
 sqlstm.occurs = (unsigned int  )0;
 sqlcxt(&vCtx, &sqlctx, &sqlstm, &sqlfpn);
}


	return 0;
}
EXPORT int __stdcall Ora_BulkInternalsInsert_NN_W(tDebugInfo* DebugParms, NN_Parms* NN, tCoreLog* NNLogs, int pid, int testid, int pDatasetsCount, int pTimeSteps, double***** W) {
	/* EXEC SQL BEGIN DECLARE SECTION; */ 

	int d, l, t, j, i;
	int vInsertCount, idx;
	sql_context vCtx = DebugParms->DebugDB->DBCtx;
	char stmt[1000];
	int dbl_type = 22;	// Oracle SQLT_BDOUBLE
	int int_type = 3;	// 
	unsigned int dbl_len = sizeof(double);
	unsigned int vchar_type = 96;
	unsigned int vchar_len = 12 + 1;

	int* vProcessId;
	int* vThreadId;
	int* vTestId;
	int* vDatasetId;
	int* vLayerId;
	int* vTimeStepId;
	int* vFromNeuron;
	int* vToNeuron;
	double* vWeight;

	/* EXEC SQL END   DECLARE SECTION; */ 


	//-- Connects to DB only once
	if (vCtx == NULL) {
		if (OraConnect(DebugParms, DebugParms->DebugDB) != 0) LogWrite_C(DebugParms, LOG_ERROR, "Ora_BulkInternalsInsert_NN_W() could not connect to Log Database...\n", 0);
		vCtx = DebugParms->DebugDB->DBCtx;
	}

	//-- mallocs
	vInsertCount = 0; idx = 0;
	for (d = 0; d < pDatasetsCount; d++) {
		for (l = 0; l < (NN->LevelsCount - 1); l++) {
			for (t = 0; t < pTimeSteps; t++) {
				for (j = 0; j < NN->NodesCount[l + 1]; j++) {
					for (i = 0; i < NN->NodesCount[l]; i++) {
						vInsertCount++;
					}
				}
			}
		}
	}
	vProcessId = (int*)malloc(vInsertCount * sizeof(int));
	vThreadId = (int*)malloc(vInsertCount * sizeof(int));
	vTestId = (int*)malloc(vInsertCount * sizeof(int));
	vDatasetId = (int*)malloc(vInsertCount * sizeof(int));
	vLayerId = (int*)malloc(vInsertCount * sizeof(int));
	vTimeStepId = (int*)malloc(vInsertCount * sizeof(int));
	vFromNeuron = (int*)malloc(vInsertCount * sizeof(int));
	vToNeuron = (int*)malloc(vInsertCount * sizeof(int));
	vWeight = (double*)malloc(vInsertCount * sizeof(double));

	/* EXEC SQL CONTEXT USE : vCtx; */ 

	/* EXEC SQL FOR : vInsertCount ALLOCATE DESCRIPTOR 'inINTW'; */ 

{
 struct sqlexd sqlstm;
 sqlstm.sqlvsn = 13;
 sqlstm.arrsiz = 4;
 sqlstm.sqladtp = &sqladt;
 sqlstm.sqltdsp = &sqltds;
 sqlstm.stmt = "";
 sqlstm.iters = (unsigned int  )vInsertCount;
 sqlstm.offset = (unsigned int  )3782;
 sqlstm.cud = sqlcud0;
 sqlstm.sqlest = (unsigned char  *)&sqlca;
 sqlstm.sqlety = (unsigned short)4352;
 sqlstm.occurs = (unsigned int  )100;
 sqlcxt(&vCtx, &sqlctx, &sqlstm, &sqlfpn);
}



	//-- assignments
	for (d = 0; d < pDatasetsCount; d++) {
		for (l = 0; l < (NN->LevelsCount - 1); l++) {
			for (t = 0; t < pTimeSteps; t++) {
				for (j = 0; j < NN->NodesCount[l + 1]; j++) {
					for (i = 0; i < NN->NodesCount[l]; i++) {
						vProcessId[idx] = pid;
						vThreadId[idx] = 0;	// NNLogs->TrainingTid[d];
						vTestId[idx] = testid;
						vDatasetId[idx] = d;
						vLayerId[idx] = l;
						vTimeStepId[idx] = t;
						vFromNeuron[idx] = j;
						vToNeuron[idx] = i;
						vWeight[idx] = W[d][l][t][j][i];

						idx++;
					}
				}
			}
		}
	}

	//-- Then, Build the Insert statement
	sprintf(&stmt[0], "insert into Internals_NN_W (ProcessId, ThreadId, TestId, TimeStep, NeuronLevel, FromNeuron, ToNeuron, Weight) values(:P01, :P02, :P03, :P04, :P05, :P06, :P07, :P08)");
	LogWrite_C(DebugParms, LOG_INFO, "BulkInternalsInsert() CheckPoint 4 - stmt='%s'\n", 1, stmt);

	/* EXEC SQL SET DESCRIPTOR 'inINTW' COUNT = 8; */ 

{
 struct sqlexd sqlstm;
 sqlstm.sqlvsn = 13;
 sqlstm.arrsiz = 4;
 sqlstm.sqladtp = &sqladt;
 sqlstm.sqltdsp = &sqltds;
 sqlstm.stmt = "";
 sqlstm.iters = (unsigned int  )1;
 sqlstm.offset = (unsigned int  )3803;
 sqlstm.cud = sqlcud0;
 sqlstm.sqlest = (unsigned char  *)&sqlca;
 sqlstm.sqlety = (unsigned short)4352;
 sqlstm.occurs = (unsigned int  )8;
 sqlcxt(&vCtx, &sqlctx, &sqlstm, &sqlfpn);
}


	/* EXEC SQL FOR : vInsertCount SET DESCRIPTOR 'inINTW' VALUE 1 DATA = : vProcessId; */ 

{
 struct sqlexd sqlstm;
 sqlstm.sqlvsn = 13;
 sqlstm.arrsiz = 4;
 sqlstm.sqladtp = &sqladt;
 sqlstm.sqltdsp = &sqltds;
 sqlstm.stmt = "";
 sqlstm.iters = (unsigned int  )vInsertCount;
 sqlstm.offset = (unsigned int  )3824;
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


	/* EXEC SQL FOR : vInsertCount SET DESCRIPTOR 'inINTW' VALUE 2 DATA = : vThreadId; */ 

{
 struct sqlexd sqlstm;
 sqlstm.sqlvsn = 13;
 sqlstm.arrsiz = 4;
 sqlstm.sqladtp = &sqladt;
 sqlstm.sqltdsp = &sqltds;
 sqlstm.stmt = "";
 sqlstm.iters = (unsigned int  )vInsertCount;
 sqlstm.offset = (unsigned int  )3849;
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


	/* EXEC SQL FOR : vInsertCount SET DESCRIPTOR 'inINTW' VALUE 3 DATA = : vTestId; */ 

{
 struct sqlexd sqlstm;
 sqlstm.sqlvsn = 13;
 sqlstm.arrsiz = 4;
 sqlstm.sqladtp = &sqladt;
 sqlstm.sqltdsp = &sqltds;
 sqlstm.stmt = "";
 sqlstm.iters = (unsigned int  )vInsertCount;
 sqlstm.offset = (unsigned int  )3874;
 sqlstm.cud = sqlcud0;
 sqlstm.sqlest = (unsigned char  *)&sqlca;
 sqlstm.sqlety = (unsigned short)4352;
 sqlstm.occurs = (unsigned int  )3;
 sqlstm.sqhstv[0] = (         void  *)vTestId;
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


	/* EXEC SQL FOR : vInsertCount SET DESCRIPTOR 'inINTW' VALUE 4 DATA = : vTimeStepId; */ 

{
 struct sqlexd sqlstm;
 sqlstm.sqlvsn = 13;
 sqlstm.arrsiz = 4;
 sqlstm.sqladtp = &sqladt;
 sqlstm.sqltdsp = &sqltds;
 sqlstm.stmt = "";
 sqlstm.iters = (unsigned int  )vInsertCount;
 sqlstm.offset = (unsigned int  )3899;
 sqlstm.cud = sqlcud0;
 sqlstm.sqlest = (unsigned char  *)&sqlca;
 sqlstm.sqlety = (unsigned short)4352;
 sqlstm.occurs = (unsigned int  )4;
 sqlstm.sqhstv[0] = (         void  *)vTimeStepId;
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


	/* EXEC SQL FOR : vInsertCount SET DESCRIPTOR 'inINTW' VALUE 5 DATA = : vLayerId; */ 

{
 struct sqlexd sqlstm;
 sqlstm.sqlvsn = 13;
 sqlstm.arrsiz = 4;
 sqlstm.sqladtp = &sqladt;
 sqlstm.sqltdsp = &sqltds;
 sqlstm.stmt = "";
 sqlstm.iters = (unsigned int  )vInsertCount;
 sqlstm.offset = (unsigned int  )3924;
 sqlstm.cud = sqlcud0;
 sqlstm.sqlest = (unsigned char  *)&sqlca;
 sqlstm.sqlety = (unsigned short)4352;
 sqlstm.occurs = (unsigned int  )5;
 sqlstm.sqhstv[0] = (         void  *)vLayerId;
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


	/* EXEC SQL FOR : vInsertCount SET DESCRIPTOR 'inINTW' VALUE 6 DATA = : vFromNeuron; */ 

{
 struct sqlexd sqlstm;
 sqlstm.sqlvsn = 13;
 sqlstm.arrsiz = 4;
 sqlstm.sqladtp = &sqladt;
 sqlstm.sqltdsp = &sqltds;
 sqlstm.stmt = "";
 sqlstm.iters = (unsigned int  )vInsertCount;
 sqlstm.offset = (unsigned int  )3949;
 sqlstm.cud = sqlcud0;
 sqlstm.sqlest = (unsigned char  *)&sqlca;
 sqlstm.sqlety = (unsigned short)4352;
 sqlstm.occurs = (unsigned int  )6;
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


	/* EXEC SQL FOR : vInsertCount SET DESCRIPTOR 'inINTW' VALUE 7 DATA = : vToNeuron; */ 

{
 struct sqlexd sqlstm;
 sqlstm.sqlvsn = 13;
 sqlstm.arrsiz = 4;
 sqlstm.sqladtp = &sqladt;
 sqlstm.sqltdsp = &sqltds;
 sqlstm.stmt = "";
 sqlstm.iters = (unsigned int  )vInsertCount;
 sqlstm.offset = (unsigned int  )3974;
 sqlstm.cud = sqlcud0;
 sqlstm.sqlest = (unsigned char  *)&sqlca;
 sqlstm.sqlety = (unsigned short)4352;
 sqlstm.occurs = (unsigned int  )7;
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


	/* EXEC SQL FOR : vInsertCount SET DESCRIPTOR 'inINTW' VALUE 8 DATA = : vWeight; */ 

{
 struct sqlexd sqlstm;
 sqlstm.sqlvsn = 13;
 sqlstm.arrsiz = 4;
 sqlstm.sqladtp = &sqladt;
 sqlstm.sqltdsp = &sqltds;
 sqlstm.stmt = "";
 sqlstm.iters = (unsigned int  )vInsertCount;
 sqlstm.offset = (unsigned int  )3999;
 sqlstm.cud = sqlcud0;
 sqlstm.sqlest = (unsigned char  *)&sqlca;
 sqlstm.sqlety = (unsigned short)4352;
 sqlstm.occurs = (unsigned int  )8;
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


	/* EXEC SQL PREPARE DynIns FROM : stmt; */ 

{
 struct sqlexd sqlstm;
 sqlstm.sqlvsn = 13;
 sqlstm.arrsiz = 4;
 sqlstm.sqladtp = &sqladt;
 sqlstm.sqltdsp = &sqltds;
 sqlstm.stmt = "";
 sqlstm.iters = (unsigned int  )1;
 sqlstm.offset = (unsigned int  )4024;
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


	/* EXEC SQL FOR : vInsertCount EXECUTE DynIns USING DESCRIPTOR 'inINTW'; */ 

{
 struct sqlexd sqlstm;
 sqlstm.sqlvsn = 13;
 sqlstm.arrsiz = 4;
 sqlstm.sqladtp = &sqladt;
 sqlstm.sqltdsp = &sqltds;
 sqlstm.stmt = "";
 sqlstm.iters = (unsigned int  )vInsertCount;
 sqlstm.offset = (unsigned int  )4043;
 sqlstm.cud = sqlcud0;
 sqlstm.sqlest = (unsigned char  *)&sqlca;
 sqlstm.sqlety = (unsigned short)4352;
 sqlstm.occurs = (unsigned int  )0;
 sqlcxt(&vCtx, &sqlctx, &sqlstm, &sqlfpn);
}



	LogWrite_C(DebugParms, LOG_INFO, "Ora_BulkInternalsInsert_NN_W() inserted %d rows.\n", 1, sqlca.sqlerrd[2]);
	if (sqlca.sqlcode != 0) {
		LogWrite_C(DebugParms, LOG_ERROR, "Ora_BulkInternalsInsert_NN_W() failed. SQL Error %d\n", 1, sqlca.sqlcode);
		return sqlca.sqlcode;
	}

	//-- free()s
	free(vProcessId);
	free(vThreadId);
	free(vTestId);
	free(vDatasetId);
	free(vLayerId);
	free(vTimeStepId);
	free(vFromNeuron);
	free(vToNeuron);
	free(vWeight);

	/* EXEC SQL DEALLOCATE DESCRIPTOR 'inINTW'; */ 

{
 struct sqlexd sqlstm;
 sqlstm.sqlvsn = 13;
 sqlstm.arrsiz = 4;
 sqlstm.sqladtp = &sqladt;
 sqlstm.sqltdsp = &sqltds;
 sqlstm.stmt = "";
 sqlstm.iters = (unsigned int  )1;
 sqlstm.offset = (unsigned int  )4064;
 sqlstm.cud = sqlcud0;
 sqlstm.sqlest = (unsigned char  *)&sqlca;
 sqlstm.sqlety = (unsigned short)4352;
 sqlstm.occurs = (unsigned int  )0;
 sqlcxt(&vCtx, &sqlctx, &sqlstm, &sqlfpn);
}


	return 0;
}
EXPORT int __stdcall Ora_BulkInternalsInsert_NN_P(tDebugInfo* DebugParms, NN_Parms* NN, tCoreLog* NNLogs, int pid, int testid, int pDatasetsCount, int pTimeSteps, tLogInt*** IntParms) {
	/* EXEC SQL BEGIN DECLARE SECTION; */ 

	int d, l, t;
	int vInsertCount; int idx;
	sql_context vCtx = DebugParms->DebugDB->DBCtx;
	char stmt[1000];
	int dbl_type = 22;	// Oracle SQLT_BDOUBLE
	int int_type = 3;	// 
	unsigned int dbl_len = sizeof(double);
	unsigned int vchar_type = 96;
	unsigned int vchar_len = 12 + 1;

	int* vProcessId;
	int* vThreadId;
	int* vTestId;
	int* vDatasetId;
	int* vLayerId;
	int* vTimeStepId;

	int* vsigma10;
	double* vro10;
	double* vD10W;
	double* vadzev10;
	int* vhcp10;
	int* vsigma21;
	double* vro21;
	double* vadzev21norm;
	double* vnorm_e;

	/* EXEC SQL END DECLARE SECTION; */ 


	//-- Connects to DB only once
	if (vCtx == NULL) {
		if (OraConnect(DebugParms, DebugParms->DebugDB) != 0) LogWrite_C(DebugParms, LOG_ERROR, "Ora_BulkInternalsInsert_NN_P() could not connect to Log Database...\n", 0);
		vCtx = DebugParms->DebugDB->DBCtx;
	}

	//-- mallocs
	vInsertCount = 0; idx = 0;
	for (d = 0; d < pDatasetsCount; d++) {
		l = 0;	// For now, all parameters are associated to layer 0
		for (t = 0; t < pTimeSteps; t++) {
			vInsertCount++;
		}
	}
	vProcessId = (int*)malloc(vInsertCount * sizeof(int));
	vThreadId = (int*)malloc(vInsertCount * sizeof(int));
	vTestId = (int*)malloc(vInsertCount * sizeof(int));
	vDatasetId = (int*)malloc(vInsertCount * sizeof(int));
	vLayerId = (int*)malloc(vInsertCount * sizeof(int));
	vTimeStepId = (int*)malloc(vInsertCount * sizeof(int));

	vsigma10 = (int*)malloc(vInsertCount * sizeof(int));
	vro10 = (double*)malloc(vInsertCount * sizeof(double));
	vD10W = (double*)malloc(vInsertCount * sizeof(double));
	vadzev10 = (double*)malloc(vInsertCount * sizeof(double));
	vhcp10 = (int*)malloc(vInsertCount * sizeof(int));
	vsigma21 = (int*)malloc(vInsertCount * sizeof(int));
	vro21 = (double*)malloc(vInsertCount * sizeof(double));
	vadzev21norm = (double*)malloc(vInsertCount * sizeof(double));
	vnorm_e = (double*)malloc(vInsertCount * sizeof(double));

	/* EXEC SQL CONTEXT USE : vCtx; */ 

	/* EXEC SQL FOR : vInsertCount ALLOCATE DESCRIPTOR 'inNNP'; */ 

{
 struct sqlexd sqlstm;
 sqlstm.sqlvsn = 13;
 sqlstm.arrsiz = 4;
 sqlstm.sqladtp = &sqladt;
 sqlstm.sqltdsp = &sqltds;
 sqlstm.stmt = "";
 sqlstm.iters = (unsigned int  )vInsertCount;
 sqlstm.offset = (unsigned int  )4085;
 sqlstm.cud = sqlcud0;
 sqlstm.sqlest = (unsigned char  *)&sqlca;
 sqlstm.sqlety = (unsigned short)4352;
 sqlstm.occurs = (unsigned int  )100;
 sqlcxt(&vCtx, &sqlctx, &sqlstm, &sqlfpn);
}



	//-- assignments
	for (d = 0; d < pDatasetsCount; d++) {
		l = 0;	// For now, all parameters are associated to layer 0
		for (t = 0; t < pTimeSteps; t++) {
			vProcessId[idx] = pid;
			vThreadId[idx] = 0;	// NNLogs->TrainingTid[d];
			vTestId[idx] = testid;
			vDatasetId[idx] = d;
			vLayerId[idx] = l;
			vTimeStepId[idx] = t;
			vadzev10[idx] = IntParms[d][l][t].adzev10;
			vadzev21norm[idx] = IntParms[d][l][t].adzev21N;
			vD10W[idx] = IntParms[d][l][t].D10W;
			vhcp10[idx] = IntParms[d][l][t].hcp10;
			vnorm_e[idx] = IntParms[d][l][t].norm_e;
			vProcessId[idx] = IntParms[d][l][t].ProcessId;
			vro10[idx] = IntParms[d][l][t].ro10;
			vro21[idx] = IntParms[d][l][t].ro21;
			vsigma10[idx] = IntParms[d][l][t].sigma10;
			vsigma21[idx] = IntParms[d][l][t].sigma21;
			vTimeStepId[idx] = IntParms[d][l][t].TimeStep;
			vThreadId[idx] = IntParms[d][l][t].ThreadId;

			idx++;
		}
	}
	//-- Then, Build the Insert statement
	sprintf(&stmt[0], "insert into Internals_NN_P (ProcessId, ThreadId, TestId, DatasetId, LayerId, TimeStep,\
					  					   sigma10, ro10, D10W, adzev10, hcp10, sigma21, ro21, adzev21norm, norm_e)\
										   					   values(:P01, :P02, :P03, :P04, :P05, :P06, :P07, :P08, :P09, :P10, :P11, :P12, :P13, :P14, :P15)");
	LogWrite_C(DebugParms, LOG_INFO, "BulkInternalsInsert() CheckPoint 4 - stmt='%s'\n", 1, stmt);

	/* EXEC SQL SET DESCRIPTOR 'inNNP' COUNT = 15; */ 

{
 struct sqlexd sqlstm;
 sqlstm.sqlvsn = 13;
 sqlstm.arrsiz = 4;
 sqlstm.sqladtp = &sqladt;
 sqlstm.sqltdsp = &sqltds;
 sqlstm.stmt = "";
 sqlstm.iters = (unsigned int  )1;
 sqlstm.offset = (unsigned int  )4105;
 sqlstm.cud = sqlcud0;
 sqlstm.sqlest = (unsigned char  *)&sqlca;
 sqlstm.sqlety = (unsigned short)4352;
 sqlstm.occurs = (unsigned int  )15;
 sqlcxt(&vCtx, &sqlctx, &sqlstm, &sqlfpn);
}


	/* EXEC SQL FOR : vInsertCount SET DESCRIPTOR 'inNNP' VALUE 1 DATA = : vProcessId; */ 

{
 struct sqlexd sqlstm;
 sqlstm.sqlvsn = 13;
 sqlstm.arrsiz = 4;
 sqlstm.sqladtp = &sqladt;
 sqlstm.sqltdsp = &sqltds;
 sqlstm.stmt = "";
 sqlstm.iters = (unsigned int  )vInsertCount;
 sqlstm.offset = (unsigned int  )4125;
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


	/* EXEC SQL FOR : vInsertCount SET DESCRIPTOR 'inNNP' VALUE 2 DATA = : vThreadId; */ 

{
 struct sqlexd sqlstm;
 sqlstm.sqlvsn = 13;
 sqlstm.arrsiz = 4;
 sqlstm.sqladtp = &sqladt;
 sqlstm.sqltdsp = &sqltds;
 sqlstm.stmt = "";
 sqlstm.iters = (unsigned int  )vInsertCount;
 sqlstm.offset = (unsigned int  )4149;
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


	/* EXEC SQL FOR : vInsertCount SET DESCRIPTOR 'inNNP' VALUE 3 DATA = : vTestId; */ 

{
 struct sqlexd sqlstm;
 sqlstm.sqlvsn = 13;
 sqlstm.arrsiz = 4;
 sqlstm.sqladtp = &sqladt;
 sqlstm.sqltdsp = &sqltds;
 sqlstm.stmt = "";
 sqlstm.iters = (unsigned int  )vInsertCount;
 sqlstm.offset = (unsigned int  )4173;
 sqlstm.cud = sqlcud0;
 sqlstm.sqlest = (unsigned char  *)&sqlca;
 sqlstm.sqlety = (unsigned short)4352;
 sqlstm.occurs = (unsigned int  )3;
 sqlstm.sqhstv[0] = (         void  *)vTestId;
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


	/* EXEC SQL FOR : vInsertCount SET DESCRIPTOR 'inNNP' VALUE 4 DATA = : vDatasetId; */ 

{
 struct sqlexd sqlstm;
 sqlstm.sqlvsn = 13;
 sqlstm.arrsiz = 4;
 sqlstm.sqladtp = &sqladt;
 sqlstm.sqltdsp = &sqltds;
 sqlstm.stmt = "";
 sqlstm.iters = (unsigned int  )vInsertCount;
 sqlstm.offset = (unsigned int  )4197;
 sqlstm.cud = sqlcud0;
 sqlstm.sqlest = (unsigned char  *)&sqlca;
 sqlstm.sqlety = (unsigned short)4352;
 sqlstm.occurs = (unsigned int  )4;
 sqlstm.sqhstv[0] = (         void  *)vDatasetId;
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


	/* EXEC SQL FOR : vInsertCount SET DESCRIPTOR 'inNNP' VALUE 5 DATA = : vLayerId; */ 

{
 struct sqlexd sqlstm;
 sqlstm.sqlvsn = 13;
 sqlstm.arrsiz = 4;
 sqlstm.sqladtp = &sqladt;
 sqlstm.sqltdsp = &sqltds;
 sqlstm.stmt = "";
 sqlstm.iters = (unsigned int  )vInsertCount;
 sqlstm.offset = (unsigned int  )4221;
 sqlstm.cud = sqlcud0;
 sqlstm.sqlest = (unsigned char  *)&sqlca;
 sqlstm.sqlety = (unsigned short)4352;
 sqlstm.occurs = (unsigned int  )5;
 sqlstm.sqhstv[0] = (         void  *)vLayerId;
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


	/* EXEC SQL FOR : vInsertCount SET DESCRIPTOR 'inNNP' VALUE 6 DATA = : vTimeStepId; */ 

{
 struct sqlexd sqlstm;
 sqlstm.sqlvsn = 13;
 sqlstm.arrsiz = 4;
 sqlstm.sqladtp = &sqladt;
 sqlstm.sqltdsp = &sqltds;
 sqlstm.stmt = "";
 sqlstm.iters = (unsigned int  )vInsertCount;
 sqlstm.offset = (unsigned int  )4245;
 sqlstm.cud = sqlcud0;
 sqlstm.sqlest = (unsigned char  *)&sqlca;
 sqlstm.sqlety = (unsigned short)4352;
 sqlstm.occurs = (unsigned int  )6;
 sqlstm.sqhstv[0] = (         void  *)vTimeStepId;
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


	/* EXEC SQL FOR : vInsertCount SET DESCRIPTOR 'inNNP' VALUE 7 DATA = : vsigma10; */ 

{
 struct sqlexd sqlstm;
 sqlstm.sqlvsn = 13;
 sqlstm.arrsiz = 4;
 sqlstm.sqladtp = &sqladt;
 sqlstm.sqltdsp = &sqltds;
 sqlstm.stmt = "";
 sqlstm.iters = (unsigned int  )vInsertCount;
 sqlstm.offset = (unsigned int  )4269;
 sqlstm.cud = sqlcud0;
 sqlstm.sqlest = (unsigned char  *)&sqlca;
 sqlstm.sqlety = (unsigned short)4352;
 sqlstm.occurs = (unsigned int  )7;
 sqlstm.sqhstv[0] = (         void  *)vsigma10;
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


	/* EXEC SQL FOR : vInsertCount SET DESCRIPTOR 'inNNP' VALUE 8 DATA = : vro10; */ 

{
 struct sqlexd sqlstm;
 sqlstm.sqlvsn = 13;
 sqlstm.arrsiz = 4;
 sqlstm.sqladtp = &sqladt;
 sqlstm.sqltdsp = &sqltds;
 sqlstm.stmt = "";
 sqlstm.iters = (unsigned int  )vInsertCount;
 sqlstm.offset = (unsigned int  )4293;
 sqlstm.cud = sqlcud0;
 sqlstm.sqlest = (unsigned char  *)&sqlca;
 sqlstm.sqlety = (unsigned short)4352;
 sqlstm.occurs = (unsigned int  )8;
 sqlstm.sqhstv[0] = (         void  *)vro10;
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


	/* EXEC SQL FOR : vInsertCount SET DESCRIPTOR 'inNNP' VALUE 9 DATA = : vD10W; */ 

{
 struct sqlexd sqlstm;
 sqlstm.sqlvsn = 13;
 sqlstm.arrsiz = 4;
 sqlstm.sqladtp = &sqladt;
 sqlstm.sqltdsp = &sqltds;
 sqlstm.stmt = "";
 sqlstm.iters = (unsigned int  )vInsertCount;
 sqlstm.offset = (unsigned int  )4317;
 sqlstm.cud = sqlcud0;
 sqlstm.sqlest = (unsigned char  *)&sqlca;
 sqlstm.sqlety = (unsigned short)4352;
 sqlstm.occurs = (unsigned int  )9;
 sqlstm.sqhstv[0] = (         void  *)vD10W;
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


	/* EXEC SQL FOR : vInsertCount SET DESCRIPTOR 'inNNP' VALUE 10 DATA = : vadzev10; */ 

{
 struct sqlexd sqlstm;
 sqlstm.sqlvsn = 13;
 sqlstm.arrsiz = 4;
 sqlstm.sqladtp = &sqladt;
 sqlstm.sqltdsp = &sqltds;
 sqlstm.stmt = "";
 sqlstm.iters = (unsigned int  )vInsertCount;
 sqlstm.offset = (unsigned int  )4341;
 sqlstm.cud = sqlcud0;
 sqlstm.sqlest = (unsigned char  *)&sqlca;
 sqlstm.sqlety = (unsigned short)4352;
 sqlstm.occurs = (unsigned int  )10;
 sqlstm.sqhstv[0] = (         void  *)vadzev10;
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


	/* EXEC SQL FOR : vInsertCount SET DESCRIPTOR 'inNNP' VALUE 11 DATA = : vhcp10; */ 

{
 struct sqlexd sqlstm;
 sqlstm.sqlvsn = 13;
 sqlstm.arrsiz = 4;
 sqlstm.sqladtp = &sqladt;
 sqlstm.sqltdsp = &sqltds;
 sqlstm.stmt = "";
 sqlstm.iters = (unsigned int  )vInsertCount;
 sqlstm.offset = (unsigned int  )4365;
 sqlstm.cud = sqlcud0;
 sqlstm.sqlest = (unsigned char  *)&sqlca;
 sqlstm.sqlety = (unsigned short)4352;
 sqlstm.occurs = (unsigned int  )11;
 sqlstm.sqhstv[0] = (         void  *)vhcp10;
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


	/* EXEC SQL FOR : vInsertCount SET DESCRIPTOR 'inNNP' VALUE 12 DATA = : vsigma21; */ 

{
 struct sqlexd sqlstm;
 sqlstm.sqlvsn = 13;
 sqlstm.arrsiz = 4;
 sqlstm.sqladtp = &sqladt;
 sqlstm.sqltdsp = &sqltds;
 sqlstm.stmt = "";
 sqlstm.iters = (unsigned int  )vInsertCount;
 sqlstm.offset = (unsigned int  )4389;
 sqlstm.cud = sqlcud0;
 sqlstm.sqlest = (unsigned char  *)&sqlca;
 sqlstm.sqlety = (unsigned short)4352;
 sqlstm.occurs = (unsigned int  )12;
 sqlstm.sqhstv[0] = (         void  *)vsigma21;
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


	/* EXEC SQL FOR : vInsertCount SET DESCRIPTOR 'inNNP' VALUE 13 DATA = : vro21; */ 

{
 struct sqlexd sqlstm;
 sqlstm.sqlvsn = 13;
 sqlstm.arrsiz = 4;
 sqlstm.sqladtp = &sqladt;
 sqlstm.sqltdsp = &sqltds;
 sqlstm.stmt = "";
 sqlstm.iters = (unsigned int  )vInsertCount;
 sqlstm.offset = (unsigned int  )4413;
 sqlstm.cud = sqlcud0;
 sqlstm.sqlest = (unsigned char  *)&sqlca;
 sqlstm.sqlety = (unsigned short)4352;
 sqlstm.occurs = (unsigned int  )13;
 sqlstm.sqhstv[0] = (         void  *)vro21;
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


	/* EXEC SQL FOR : vInsertCount SET DESCRIPTOR 'inNNP' VALUE 14 DATA = : vadzev21norm; */ 

{
 struct sqlexd sqlstm;
 sqlstm.sqlvsn = 13;
 sqlstm.arrsiz = 4;
 sqlstm.sqladtp = &sqladt;
 sqlstm.sqltdsp = &sqltds;
 sqlstm.stmt = "";
 sqlstm.iters = (unsigned int  )vInsertCount;
 sqlstm.offset = (unsigned int  )4437;
 sqlstm.cud = sqlcud0;
 sqlstm.sqlest = (unsigned char  *)&sqlca;
 sqlstm.sqlety = (unsigned short)4352;
 sqlstm.occurs = (unsigned int  )14;
 sqlstm.sqhstv[0] = (         void  *)vadzev21norm;
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


	/* EXEC SQL FOR : vInsertCount SET DESCRIPTOR 'inNNP' VALUE 15 DATA = : vnorm_e; */ 

{
 struct sqlexd sqlstm;
 sqlstm.sqlvsn = 13;
 sqlstm.arrsiz = 4;
 sqlstm.sqladtp = &sqladt;
 sqlstm.sqltdsp = &sqltds;
 sqlstm.stmt = "";
 sqlstm.iters = (unsigned int  )vInsertCount;
 sqlstm.offset = (unsigned int  )4461;
 sqlstm.cud = sqlcud0;
 sqlstm.sqlest = (unsigned char  *)&sqlca;
 sqlstm.sqlety = (unsigned short)4352;
 sqlstm.occurs = (unsigned int  )15;
 sqlstm.sqhstv[0] = (         void  *)vnorm_e;
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
 sqlstm.offset = (unsigned int  )4485;
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


	/* EXEC SQL FOR : vInsertCount EXECUTE DynIns USING DESCRIPTOR 'inNNP'; */ 

{
 struct sqlexd sqlstm;
 sqlstm.sqlvsn = 13;
 sqlstm.arrsiz = 4;
 sqlstm.sqladtp = &sqladt;
 sqlstm.sqltdsp = &sqltds;
 sqlstm.stmt = "";
 sqlstm.iters = (unsigned int  )vInsertCount;
 sqlstm.offset = (unsigned int  )4504;
 sqlstm.cud = sqlcud0;
 sqlstm.sqlest = (unsigned char  *)&sqlca;
 sqlstm.sqlety = (unsigned short)4352;
 sqlstm.occurs = (unsigned int  )0;
 sqlcxt(&vCtx, &sqlctx, &sqlstm, &sqlfpn);
}



	LogWrite_C(DebugParms, LOG_INFO, "Ora_BulkInternalsInsert_NN_P() inserted %d rows.\n", 1, sqlca.sqlerrd[2]);
	if (sqlca.sqlcode != 0) {
		LogWrite_C(DebugParms, LOG_ERROR, "Ora_BulkInternalsInsert_NN_P() failed. SQL Error %d\n", 1, sqlca.sqlcode);
		return sqlca.sqlcode;
	}

	//-- free()s
	free(vProcessId);
	free(vThreadId);
	free(vTestId);
	free(vDatasetId);
	free(vLayerId);
	free(vTimeStepId);
	free(vsigma10);
	free(vro10);
	free(vD10W);
	free(vadzev10);
	free(vhcp10);
	free(vsigma21);
	free(vro21);
	free(vadzev21norm);
	free(vnorm_e);

	/* EXEC SQL DEALLOCATE DESCRIPTOR 'inNNP'; */ 

{
 struct sqlexd sqlstm;
 sqlstm.sqlvsn = 13;
 sqlstm.arrsiz = 4;
 sqlstm.sqladtp = &sqladt;
 sqlstm.sqltdsp = &sqltds;
 sqlstm.stmt = "";
 sqlstm.iters = (unsigned int  )1;
 sqlstm.offset = (unsigned int  )4524;
 sqlstm.cud = sqlcud0;
 sqlstm.sqlest = (unsigned char  *)&sqlca;
 sqlstm.sqlety = (unsigned short)4352;
 sqlstm.occurs = (unsigned int  )0;
 sqlcxt(&vCtx, &sqlctx, &sqlstm, &sqlfpn);
}


	return 0;
}
//===

//=== Engine Load stuff
EXPORT int __stdcall Ora_LoadEngineParms(tDebugInfo* DebugParms, int pEngineType, tEngineHandle* pEngineHandle, int pDatasetsCount, void* oEngineParms){
	/* EXEC SQL BEGIN DECLARE SECTION; */ 

	int retval = 0;
	sql_context vCtx = DebugParms->DebugDB->DBCtx;
	char stmt[1000];
	//-- Network Properties variables
	int vInputCount, vOutputCount, vUseContext, vMaxEpochs, vBP_Algo, vActivationFunction;
	char vLevelRatios[256];
	double vLearningRate, vLearningMomentum, vHCPBeta, vTargetMSE;
	/* EXEC SQL END DECLARE SECTION; */ 


	NN_Parms* vNNParms;
	//GA_Parms* vGAParms;
	//SOM_Parms* vSOMParms;
	//SVM_Parms* vSVMParms;

	//vLevelRatios = (char*)malloc(256*sizeof(char));
	//-- Connects to DB only once
	if (vCtx == NULL){
		if (OraConnect(DebugParms, DebugParms->DebugDB) != 0) printf("Ora_LoadEngine could not connect to Log Database...\n");
		vCtx = DebugParms->DebugDB->DBCtx;
	}

	switch (pEngineType){
	case ENGINE_NN:
		vNNParms = (NN_Parms*)oEngineParms;

		//-- Load Network properties from EngineParms_NN
		sprintf(&stmt[0], "select InputCount, OutputCount, LevelRatioS, UseContext, MaxEpochs, BP_Algo, LearningRate, LearningMomentum, ActivationFunction, HCPBeta, TargetMSE from EngineParms_NN where ProcessId=%d and ThreadId=%d", pEngineHandle->ProcessId, pEngineHandle->ThreadId);
		//LogWrite_C(DebugParms, "LoadEngine() CheckPoint 2\n", 0);
		/* EXEC SQL CONTEXT USE :vCtx; */ 

		/* EXEC SQL PREPARE s1 FROM :stmt; */ 

{
  struct sqlexd sqlstm;
  sqlstm.sqlvsn = 13;
  sqlstm.arrsiz = 4;
  sqlstm.sqladtp = &sqladt;
  sqlstm.sqltdsp = &sqltds;
  sqlstm.stmt = "";
  sqlstm.iters = (unsigned int  )1;
  sqlstm.offset = (unsigned int  )4544;
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


		/* EXEC SQL DECLARE cle CURSOR FOR s1; */ 

		/* EXEC SQL OPEN cle; */ 

{
  struct sqlexd sqlstm;
  sqlstm.sqlvsn = 13;
  sqlstm.arrsiz = 4;
  sqlstm.sqladtp = &sqladt;
  sqlstm.sqltdsp = &sqltds;
  sqlstm.stmt = "";
  sqlstm.iters = (unsigned int  )1;
  sqlstm.offset = (unsigned int  )4563;
  sqlstm.selerr = (unsigned short)1;
  sqlstm.sqlpfmem = (unsigned int  )0;
  sqlstm.cud = sqlcud0;
  sqlstm.sqlest = (unsigned char  *)&sqlca;
  sqlstm.sqlety = (unsigned short)4352;
  sqlstm.occurs = (unsigned int  )0;
  sqlstm.sqcmod = (unsigned int )0;
  sqlcxt(&vCtx, &sqlctx, &sqlstm, &sqlfpn);
}


		if (sqlca.sqlcode != 0){
			LogWrite_C(DebugParms, LOG_ERROR, "Ora_LoadEngineParms: SQL Error %d\n", 1, sqlca.sqlcode); system("pause");
			retval = sqlca.sqlcode;
			break;
		}
		/* EXEC SQL FETCH cle INTO vInputCount, vOutputCount, vLevelRatios, vUseContext, vMaxEpochs, vBP_Algo, vLearningRate, vLearningMomentum, vActivationFunction, vHCPBeta, vTargetMSE; */ 

{
  struct sqlexd sqlstm;
  sqlstm.sqlvsn = 13;
  sqlstm.arrsiz = 11;
  sqlstm.sqladtp = &sqladt;
  sqlstm.sqltdsp = &sqltds;
  sqlstm.iters = (unsigned int  )1;
  sqlstm.offset = (unsigned int  )4578;
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


		if (sqlca.sqlcode == 0){
			vNNParms->InputCount = vInputCount; vNNParms->OutputCount = vOutputCount; vNNParms->UseContext = vUseContext; vNNParms->MaxEpochs = vMaxEpochs; vNNParms->BP_Algo = vBP_Algo; vNNParms->LearningRate = vLearningRate; vNNParms->LearningMomentum = vLearningMomentum; vNNParms->ActivationFunction = vActivationFunction; vNNParms->HCPbeta = vHCPBeta; vNNParms->TargetMSE = vTargetMSE;
			strcpy(vNNParms->LevelRatioS, vLevelRatios);
		}
		else if (sqlca.sqlcode == 1403){
			LogWrite_C(DebugParms, LOG_ERROR, "Ora_LoadEngineParms: Engine not found. ProcessId=%d ; ThreadId=%d ; TestId=%d\n", 3, pEngineHandle->ProcessId, pEngineHandle->ThreadId, pEngineHandle->TestId);
			retval = sqlca.sqlcode;
		}
		else{
			LogWrite_C(DebugParms, LOG_ERROR, "Ora_LoadEngineParms: SQL Error %d\n", 1, sqlca.sqlcode);
			retval = sqlca.sqlcode;
		}
		/* EXEC SQL CLOSE cle; */ 

{
  struct sqlexd sqlstm;
  sqlstm.sqlvsn = 13;
  sqlstm.arrsiz = 11;
  sqlstm.sqladtp = &sqladt;
  sqlstm.sqltdsp = &sqltds;
  sqlstm.iters = (unsigned int  )1;
  sqlstm.offset = (unsigned int  )4637;
  sqlstm.cud = sqlcud0;
  sqlstm.sqlest = (unsigned char  *)&sqlca;
  sqlstm.sqlety = (unsigned short)4352;
  sqlstm.occurs = (unsigned int  )0;
  sqlcxt(&vCtx, &sqlctx, &sqlstm, &sqlfpn);
}


		//free(vLevelRatios);

		break;
	case ENGINE_GA:
		break;
	case ENGINE_SVM:
		break;
	case ENGINE_SOM:
		break;
	}

	return retval;
}
EXPORT int __stdcall Ora_LoadEngineData(tDebugInfo* DebugParms, int pEngineType, tEngineHandle* pEngineHandle, int pDatasetsCount, void* oEngineParms, tCoreLog* oEngineLogs){
	/* EXEC SQL BEGIN DECLARE SECTION; */ 

	int retval = 0;
	sql_context vCtx = DebugParms->DebugDB->DBCtx;
	char stmt[1000];
	//-- Network Weights variables
	int vNeuronLevel; int vFromNeuron; int vToNeuron; double vWeight;
	/* EXEC SQL END DECLARE SECTION; */ 


	NN_Parms* vNNParms;
	tCoreLog* coreLog;
	//GA_Parms* vGAParms;
	//SOM_Parms* vSOMParms;
	//SVM_Parms* vSVMParms;

	//-- Connects to DB only once
	if (vCtx == NULL){
		if (OraConnect(DebugParms, DebugParms->DebugDB) != 0) printf("Ora_LoadEngineData could not connect to Log Database...\n");
		vCtx = DebugParms->DebugDB->DBCtx;
	}

	coreLog = oEngineLogs;
	switch (pEngineType){
	case ENGINE_NN:
		vNNParms = (NN_Parms*)oEngineParms;
		//-- Load Network Weights from NetImage_NN
		sprintf(&stmt[0], "select NeuronLevel, FromNeuron, ToNeuron, Weight from NetImage_NN where ProcessId=%d and ThreadId=%d order by 1,2,3", pEngineHandle->ProcessId, pEngineHandle->ThreadId);
		LogWrite_C(DebugParms, LOG_INFO, "Ora_LoadEngineData() CheckPoint 3 - stmt=%s\n", 1, stmt);
		/* EXEC SQL CONTEXT USE :vCtx; */ 

		/* EXEC SQL PREPARE s2 FROM :stmt; */ 

{
  struct sqlexd sqlstm;
  sqlstm.sqlvsn = 13;
  sqlstm.arrsiz = 11;
  sqlstm.sqladtp = &sqladt;
  sqlstm.sqltdsp = &sqltds;
  sqlstm.stmt = "";
  sqlstm.iters = (unsigned int  )1;
  sqlstm.offset = (unsigned int  )4652;
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


		/* EXEC SQL DECLARE c2 CURSOR FOR s2; */ 

		/* EXEC SQL OPEN c2; */ 

{
  struct sqlexd sqlstm;
  sqlstm.sqlvsn = 13;
  sqlstm.arrsiz = 11;
  sqlstm.sqladtp = &sqladt;
  sqlstm.sqltdsp = &sqltds;
  sqlstm.stmt = "";
  sqlstm.iters = (unsigned int  )1;
  sqlstm.offset = (unsigned int  )4671;
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
			/* EXEC SQL FETCH c2 INTO vNeuronLevel, vFromNeuron, vToNeuron, vWeight; */ 

{
   struct sqlexd sqlstm;
   sqlstm.sqlvsn = 13;
   sqlstm.arrsiz = 11;
   sqlstm.sqladtp = &sqladt;
   sqlstm.sqltdsp = &sqltds;
   sqlstm.iters = (unsigned int  )1;
   sqlstm.offset = (unsigned int  )4686;
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


			if (sqlca.sqlcode == 0){
				coreLog->NNFinalW[vNeuronLevel][vFromNeuron][vToNeuron].Weight = vWeight;
			}
			else if (sqlca.sqlcode == 1403){
				break;
			}
			else{
				LogWrite_C(DebugParms, LOG_ERROR, "Ora_LoadEngineData: SQL Error %d\n", 1, sqlca.sqlcode);
				retval = sqlca.sqlcode;
				break;
			}
		}
		/* EXEC SQL CLOSE c2; */ 

{
  struct sqlexd sqlstm;
  sqlstm.sqlvsn = 13;
  sqlstm.arrsiz = 11;
  sqlstm.sqladtp = &sqladt;
  sqlstm.sqltdsp = &sqltds;
  sqlstm.iters = (unsigned int  )1;
  sqlstm.offset = (unsigned int  )4717;
  sqlstm.cud = sqlcud0;
  sqlstm.sqlest = (unsigned char  *)&sqlca;
  sqlstm.sqlety = (unsigned short)4352;
  sqlstm.occurs = (unsigned int  )0;
  sqlcxt(&vCtx, &sqlctx, &sqlstm, &sqlfpn);
}




		break;
	case ENGINE_GA:
		break;
	case ENGINE_SVM:
		break;
	case ENGINE_SOM:
		break;
	}

	return retval;
}
EXPORT int __stdcall Ora_LoadDataShape(tDebugInfo* pDebugParms, tDBConnection* pLogDB, tEngineHandle* pEngineHandle, tDataShape* oTestData) {
	/* EXEC SQL BEGIN DECLARE SECTION; */ 

	int ret;
	sql_context vCtx = pLogDB->DBCtx;
	char stmt[300];
	int vHistoryLen, vSampleLen, vPredictionLen, vDataTransformation;
	double /*vScaleMin, vScaleMax,*/ vWiggleRoom;
	/* EXEC SQL END   DECLARE SECTION; */ 


	LogWrite_C(pDebugParms, LOG_INFO, "GetDataShapeFromDB CheckPoint 1\n", 0);
	LogWrite_C(pDebugParms, LOG_INFO, "GetDataShapeFromDB CheckPoint 2\n", 0);

	//-- Connects to DB only once
	if (vCtx == NULL) {
		if (OraConnect(pDebugParms, pLogDB) != 0) printf("LoadEngine could not connect to Log Database...\n");
		vCtx = pLogDB->DBCtx;
	}

	LogWrite_C(pDebugParms, LOG_INFO, "GetDataShapeFromDB CheckPoint 2 - pEngine->ProcessId=%d ; pEngine->ThreadId=%d\n", 2, pEngineHandle->ProcessId, pEngineHandle->ThreadId);
	//sprintf(&stmt[0], "select HistoryLen, SampleLen, PredictionLen, DataTransformation/*, ScaleMin, ScaleMax, WiggleRoom from DataParms where ProcessId=%d and ThreadId=%d", pEngineHandle->ProcessId, pEngineHandle->ThreadId);
	sprintf(&stmt[0], "select HistoryLen, SampleLen, PredictionLen, DataTransformation, WiggleRoom from DataParms where ProcessId=%d and ThreadId=%d", pEngineHandle->ProcessId, pEngineHandle->ThreadId);
	LogWrite_C(pDebugParms, LOG_INFO, "GetDataShapeFromDB CheckPoint 3 - stmt = %s\n", 1, stmt);

	//-- Executes SQL 
	vCtx = pLogDB->DBCtx;
	/* EXEC SQL CONTEXT USE : vCtx; */ 

	/* EXEC SQL PREPARE s15 FROM : stmt; */ 

{
 struct sqlexd sqlstm;
 sqlstm.sqlvsn = 13;
 sqlstm.arrsiz = 11;
 sqlstm.sqladtp = &sqladt;
 sqlstm.sqltdsp = &sqltds;
 sqlstm.stmt = "";
 sqlstm.iters = (unsigned int  )1;
 sqlstm.offset = (unsigned int  )4732;
 sqlstm.cud = sqlcud0;
 sqlstm.sqlest = (unsigned char  *)&sqlca;
 sqlstm.sqlety = (unsigned short)4352;
 sqlstm.occurs = (unsigned int  )0;
 sqlstm.sqhstv[0] = (         void  *)stmt;
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


	/* EXEC SQL DECLARE c15 CURSOR FOR s15; */ 

	/* EXEC SQL OPEN c15; */ 

{
 struct sqlexd sqlstm;
 sqlstm.sqlvsn = 13;
 sqlstm.arrsiz = 11;
 sqlstm.sqladtp = &sqladt;
 sqlstm.sqltdsp = &sqltds;
 sqlstm.stmt = "";
 sqlstm.iters = (unsigned int  )1;
 sqlstm.offset = (unsigned int  )4751;
 sqlstm.selerr = (unsigned short)1;
 sqlstm.sqlpfmem = (unsigned int  )0;
 sqlstm.cud = sqlcud0;
 sqlstm.sqlest = (unsigned char  *)&sqlca;
 sqlstm.sqlety = (unsigned short)4352;
 sqlstm.occurs = (unsigned int  )0;
 sqlstm.sqcmod = (unsigned int )0;
 sqlcxt(&vCtx, &sqlctx, &sqlstm, &sqlfpn);
}


	/* EXEC SQL FETCH c15 INTO : vHistoryLen, : vSampleLen, : vPredictionLen, : vDataTransformation/o, :vScaleMin, :vScaleMaxo/, : vWiggleRoom; */ 

{
 struct sqlexd sqlstm;
 sqlstm.sqlvsn = 13;
 sqlstm.arrsiz = 11;
 sqlstm.sqladtp = &sqladt;
 sqlstm.sqltdsp = &sqltds;
 sqlstm.iters = (unsigned int  )1;
 sqlstm.offset = (unsigned int  )4766;
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
		LogWrite_C(pDebugParms, LOG_ERROR, "GetDataShapeFromDB: SQL Error %d\n", 1, sqlca.sqlcode);
		return sqlca.sqlcode;
	}
	/* EXEC SQL CLOSE c15; */ 

{
 struct sqlexd sqlstm;
 sqlstm.sqlvsn = 13;
 sqlstm.arrsiz = 11;
 sqlstm.sqladtp = &sqladt;
 sqlstm.sqltdsp = &sqltds;
 sqlstm.iters = (unsigned int  )1;
 sqlstm.offset = (unsigned int  )4801;
 sqlstm.cud = sqlcud0;
 sqlstm.sqlest = (unsigned char  *)&sqlca;
 sqlstm.sqlety = (unsigned short)4352;
 sqlstm.occurs = (unsigned int  )0;
 sqlcxt(&vCtx, &sqlctx, &sqlstm, &sqlfpn);
}


	ret = sqlca.sqlcode;

	//-- Fill oTestData, and returns
	oTestData->HistoryLen = vHistoryLen;
	oTestData->SampleLen = vSampleLen;
	oTestData->PredictionLen = vPredictionLen;
	oTestData->DataTransformation = vDataTransformation;
	//oTestData->ScaleMin = vScaleMin;
	//oTestData->ScaleMax = vScaleMax;
	oTestData->wiggleRoom = vWiggleRoom;
	LogWrite_C(pDebugParms, LOG_INFO, "GetDataShapeFromDB(): HistoryLen=%d ; SampleLen=%d ; PredictionLen=%d \n", 3, oTestData->HistoryLen, oTestData->SampleLen, oTestData->PredictionLen);
	return 0;
}
//===

//=== Queries
EXPORT int __stdcall SymbolLookup(tDebugInfo* DebugParms, sql_context pCtx, char* pSymbol, char* oSymbol, int* oScale){

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
	LogWrite_C(DebugParms, LOG_INFO, "%s SymbolLookup executing: %s\n", 2, timestamp_C, SymLkp_stmt);
	//EXEC SQL ALTER SESSION SET SQL_TRACE=TRUE;
	/* EXEC SQL CONTEXT USE :vCtx; */ 

	/* EXEC SQL PREPARE s5 FROM :SymLkp_stmt; */ 

{
 struct sqlexd sqlstm;
 sqlstm.sqlvsn = 13;
 sqlstm.arrsiz = 11;
 sqlstm.sqladtp = &sqladt;
 sqlstm.sqltdsp = &sqltds;
 sqlstm.stmt = "";
 sqlstm.iters = (unsigned int  )1;
 sqlstm.offset = (unsigned int  )4816;
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
 sqlstm.offset = (unsigned int  )4835;
 sqlstm.selerr = (unsigned short)1;
 sqlstm.sqlpfmem = (unsigned int  )0;
 sqlstm.cud = sqlcud0;
 sqlstm.sqlest = (unsigned char  *)&sqlca;
 sqlstm.sqlety = (unsigned short)4352;
 sqlstm.occurs = (unsigned int  )0;
 sqlstm.sqcmod = (unsigned int )0;
 sqlcxt(&vCtx, &sqlctx, &sqlstm, &sqlfpn);
}


	/* EXEC SQL FETCH c5 INTO :vSymbol; */ 

{
 struct sqlexd sqlstm;
 sqlstm.sqlvsn = 13;
 sqlstm.arrsiz = 11;
 sqlstm.sqladtp = &sqladt;
 sqlstm.sqltdsp = &sqltds;
 sqlstm.iters = (unsigned int  )1;
 sqlstm.offset = (unsigned int  )4850;
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


	if (sqlca.sqlcode != 0){
		LogWrite_C(DebugParms, LOG_INFO, "SymbolLookup: SQL Error %d\n", 1, sqlca.sqlcode);
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
 sqlstm.offset = (unsigned int  )4869;
 sqlstm.cud = sqlcud0;
 sqlstm.sqlest = (unsigned char  *)&sqlca;
 sqlstm.sqlety = (unsigned short)4352;
 sqlstm.occurs = (unsigned int  )0;
 sqlcxt(&vCtx, &sqlctx, &sqlstm, &sqlfpn);
}


	//EXEC SQL ALTER SESSION SET SQL_TRACE=FALSE;
	LogWrite_C(DebugParms, LOG_INFO, "%s SymbolLookup found symbol: %s\n", 2, timestamp_C, vSymbol);

	// Then, Look for pScale
	pScale_stmt_base = "select pScale from GridUser.Pairs where Symbol='";
	strcpy(pScale_stmt, pScale_stmt_base);
	Trim_C(vSymbol); strcat(pScale_stmt, vSymbol);
	strcat(pScale_stmt, "'");
	LogWrite_C(DebugParms, LOG_INFO, "%s SymbolLookup executing: %s\n", 2, timestamp_C, pScale_stmt);

	/* EXEC SQL PREPARE s6 FROM :pScale_stmt; */ 

{
 struct sqlexd sqlstm;
 sqlstm.sqlvsn = 13;
 sqlstm.arrsiz = 11;
 sqlstm.sqladtp = &sqladt;
 sqlstm.sqltdsp = &sqltds;
 sqlstm.stmt = "";
 sqlstm.iters = (unsigned int  )1;
 sqlstm.offset = (unsigned int  )4884;
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
 sqlstm.offset = (unsigned int  )4903;
 sqlstm.selerr = (unsigned short)1;
 sqlstm.sqlpfmem = (unsigned int  )0;
 sqlstm.cud = sqlcud0;
 sqlstm.sqlest = (unsigned char  *)&sqlca;
 sqlstm.sqlety = (unsigned short)4352;
 sqlstm.occurs = (unsigned int  )0;
 sqlstm.sqcmod = (unsigned int )0;
 sqlcxt(&vCtx, &sqlctx, &sqlstm, &sqlfpn);
}


	/* EXEC SQL FETCH c6 INTO :vpScale; */ 

{
 struct sqlexd sqlstm;
 sqlstm.sqlvsn = 13;
 sqlstm.arrsiz = 11;
 sqlstm.sqladtp = &sqladt;
 sqlstm.sqltdsp = &sqltds;
 sqlstm.iters = (unsigned int  )1;
 sqlstm.offset = (unsigned int  )4918;
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


	if (sqlca.sqlcode != 0){
		LogWrite_C(DebugParms, LOG_ERROR, "GetpScale: SQL Error %d\n", 1, sqlca.sqlcode);
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
 sqlstm.offset = (unsigned int  )4937;
 sqlstm.cud = sqlcud0;
 sqlstm.sqlest = (unsigned char  *)&sqlca;
 sqlstm.sqlety = (unsigned short)4352;
 sqlstm.occurs = (unsigned int  )0;
 sqlcxt(&vCtx, &sqlctx, &sqlstm, &sqlfpn);
}


	LogWrite_C(DebugParms, LOG_INFO, "%s SymbolLookup found pScale= %d\n", 2, timestamp_C, vpScale);

	Trim_C(vSymbol);  strcpy(oSymbol, vSymbol);
	(*oScale) = vpScale;

	return 0;
}
EXPORT int __stdcall FindBestPredictor(tDebugInfo* DebugParms, sql_context pCtx, char* vCSymbol, char* vHSymbol, char* vTimeFrame, int vIsFilled, char* pCurrentStart, int vTotalBars, char* vMeasure, int vOutputType, int pPredictorsCount, tPredictor* pBestPredictor){

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

	LogWrite_C(DebugParms, LOG_INFO, "%s FindBestPredictor(%s) started.\n", 2, timestamp_C, (vOutputType == FH) ? "High" :"Low");

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
	strcat(&stmt[0], (vOutputType == 1) ? "High" :"Low");
	strcat(&stmt[0], "' and PredictorData='");
	strcat(&stmt[0], vHSymbol);
	strcat(&stmt[0], "' and ");
	strcat(&stmt[0], vMeasure);
	strcat(&stmt[0], "<1");
	strcat(&stmt[0], " and PatternLength=");
	sprintf(vTotalBarsBuffer, "%d", vTotalBars);				strcat(&stmt[0], vTotalBarsBuffer);
	strcat(&stmt[0], " order by 3 desc");
	LogWrite_C(DebugParms, LOG_INFO, "%s FindBestPredictor(%s)  Executing stmt=%s\n", 3, timestamp_C, (vOutputType == FH)?"High":"Low", stmt);

	/* EXEC SQL CONTEXT USE :vCtx; */ 

	/* EXEC SQL PREPARE S FROM :stmt; */ 

{
 struct sqlexd sqlstm;
 sqlstm.sqlvsn = 13;
 sqlstm.arrsiz = 11;
 sqlstm.sqladtp = &sqladt;
 sqlstm.sqltdsp = &sqltds;
 sqlstm.stmt = "";
 sqlstm.iters = (unsigned int  )1;
 sqlstm.offset = (unsigned int  )4952;
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
 sqlstm.offset = (unsigned int  )4971;
 sqlstm.selerr = (unsigned short)1;
 sqlstm.sqlpfmem = (unsigned int  )0;
 sqlstm.cud = sqlcud0;
 sqlstm.sqlest = (unsigned char  *)&sqlca;
 sqlstm.sqlety = (unsigned short)4352;
 sqlstm.occurs = (unsigned int  )0;
 sqlstm.sqcmod = (unsigned int )0;
 sqlcxt(&vCtx, &sqlctx, &sqlstm, &sqlfpn);
}


	if (sqlca.sqlcode != 0){
		LogWrite_C(DebugParms, LOG_INFO, "%s FindBestPredictor: Error raised by stmt: %d\n", 2, timestamp_C, sqlca.sqlcode);
		return sqlca.sqlcode;
	}
	//=========================================================================================================================================
	for (pr_id = 0; pr_id<pPredictorsCount; pr_id++){
		/* EXEC SQL FETCH c3 INTO :vPredictorStart, :vPredictorLen, :vPredictorMeasure; */ 

{
  struct sqlexd sqlstm;
  sqlstm.sqlvsn = 13;
  sqlstm.arrsiz = 11;
  sqlstm.sqladtp = &sqladt;
  sqlstm.sqltdsp = &sqltds;
  sqlstm.iters = (unsigned int  )1;
  sqlstm.offset = (unsigned int  )4986;
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


		if (sqlca.sqlcode != 0){
			LogWrite_C(DebugParms, LOG_ERROR, "%s FindBestPredictor: Error raised by stmt: %d\n", 2, timestamp_C, sqlca.sqlcode);
			return sqlca.sqlcode;
		}
		pBestPredictor[pr_id].PredType = vOutputType;
		strcpy(pBestPredictor[pr_id].PredStart, vPredictorStart);
		pBestPredictor[pr_id].PredLen = vPredictorLen;
		LogWrite_C(DebugParms, LOG_INFO, "%s FindBestPredictor(%s) found top %d predictor. PredStart=%s \n", 4, timestamp_C, (vOutputType == FH) ? "High" : "Low", pr_id, pBestPredictor[pr_id].PredStart);
	}
	/* EXEC SQL CLOSE c3; */ 

{
 struct sqlexd sqlstm;
 sqlstm.sqlvsn = 13;
 sqlstm.arrsiz = 11;
 sqlstm.sqladtp = &sqladt;
 sqlstm.sqltdsp = &sqltds;
 sqlstm.iters = (unsigned int  )1;
 sqlstm.offset = (unsigned int  )5013;
 sqlstm.cud = sqlcud0;
 sqlstm.sqlest = (unsigned char  *)&sqlca;
 sqlstm.sqlety = (unsigned short)4352;
 sqlstm.occurs = (unsigned int  )0;
 sqlcxt(&vCtx, &sqlctx, &sqlstm, &sqlfpn);
}


	return sqlca.sqlcode;

}
EXPORT int __stdcall GetCharPFromQuery(tDebugInfo* DebugParms, sql_context pCtx, char* pSQL, char* oRet){
	/* EXEC SQL BEGIN DECLARE SECTION; */ 

	char vSQL[1000];
	char vRet[1000];
	sql_context vCtx = pCtx;
	/* EXEC SQL END   DECLARE SECTION; */ 

	strcpy(vSQL, pSQL);

	/* EXEC SQL CONTEXT USE :vCtx; */ 

	/* EXEC SQL PREPARE s8 FROM :vSQL; */ 

{
 struct sqlexd sqlstm;
 sqlstm.sqlvsn = 13;
 sqlstm.arrsiz = 11;
 sqlstm.sqladtp = &sqladt;
 sqlstm.sqltdsp = &sqltds;
 sqlstm.stmt = "";
 sqlstm.iters = (unsigned int  )1;
 sqlstm.offset = (unsigned int  )5028;
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
 sqlstm.offset = (unsigned int  )5047;
 sqlstm.selerr = (unsigned short)1;
 sqlstm.sqlpfmem = (unsigned int  )0;
 sqlstm.cud = sqlcud0;
 sqlstm.sqlest = (unsigned char  *)&sqlca;
 sqlstm.sqlety = (unsigned short)4352;
 sqlstm.occurs = (unsigned int  )0;
 sqlstm.sqcmod = (unsigned int )0;
 sqlcxt(&vCtx, &sqlctx, &sqlstm, &sqlfpn);
}


	if (sqlca.sqlcode != 0){
		LogWrite_C(DebugParms, LOG_ERROR, "GetCharPFromQuery: SQL Error %d\n", 1, sqlca.sqlcode);
		return sqlca.sqlcode;
	}
	/* EXEC SQL FETCH c8 INTO :vRet; */ 

{
 struct sqlexd sqlstm;
 sqlstm.sqlvsn = 13;
 sqlstm.arrsiz = 11;
 sqlstm.sqladtp = &sqladt;
 sqlstm.sqltdsp = &sqltds;
 sqlstm.iters = (unsigned int  )1;
 sqlstm.offset = (unsigned int  )5062;
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


	if (sqlca.sqlcode != 0){
		LogWrite_C(DebugParms, LOG_ERROR, "GetCharPFromQuery: SQL Error %d\n", 1, sqlca.sqlcode);
		return sqlca.sqlcode;
	}
	Trim_C(vRet); strcpy(oRet, vRet);
	/* EXEC SQL CLOSE c8; */ 

{
 struct sqlexd sqlstm;
 sqlstm.sqlvsn = 13;
 sqlstm.arrsiz = 11;
 sqlstm.sqladtp = &sqladt;
 sqlstm.sqltdsp = &sqltds;
 sqlstm.iters = (unsigned int  )1;
 sqlstm.offset = (unsigned int  )5081;
 sqlstm.cud = sqlcud0;
 sqlstm.sqlest = (unsigned char  *)&sqlca;
 sqlstm.sqlety = (unsigned short)4352;
 sqlstm.occurs = (unsigned int  )0;
 sqlcxt(&vCtx, &sqlctx, &sqlstm, &sqlfpn);
}


	return sqlca.sqlcode;
}
EXPORT int __stdcall GetStringArrayFromQuery(tDebugInfo* DebugParms, sql_context pCtx, char* pSQL, int ArrLen, char** oRet){
	/* EXEC SQL BEGIN DECLARE SECTION; */ 

	char vSQL[1000];
	char vRet[1000];
	sql_context vCtx = pCtx;
	/* EXEC SQL END   DECLARE SECTION; */ 

	strcpy(vSQL, pSQL);

	/* EXEC SQL CONTEXT USE :vCtx; */ 

	/* EXEC SQL PREPARE s82 FROM :vSQL; */ 

{
 struct sqlexd sqlstm;
 sqlstm.sqlvsn = 13;
 sqlstm.arrsiz = 11;
 sqlstm.sqladtp = &sqladt;
 sqlstm.sqltdsp = &sqltds;
 sqlstm.stmt = "";
 sqlstm.iters = (unsigned int  )1;
 sqlstm.offset = (unsigned int  )5096;
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
 sqlstm.offset = (unsigned int  )5115;
 sqlstm.selerr = (unsigned short)1;
 sqlstm.sqlpfmem = (unsigned int  )0;
 sqlstm.cud = sqlcud0;
 sqlstm.sqlest = (unsigned char  *)&sqlca;
 sqlstm.sqlety = (unsigned short)4352;
 sqlstm.occurs = (unsigned int  )0;
 sqlstm.sqcmod = (unsigned int )0;
 sqlcxt(&vCtx, &sqlctx, &sqlstm, &sqlfpn);
}


	if (sqlca.sqlcode != 0){
		LogWrite_C(DebugParms, LOG_ERROR, "GetStringArrayFromQuery: SQL Error %d\n", 1, sqlca.sqlcode);
		return sqlca.sqlcode;
	}
	for(int i=0;i<ArrLen;i++){
		/* EXEC SQL FETCH c82 INTO :vRet; */ 

{
  struct sqlexd sqlstm;
  sqlstm.sqlvsn = 13;
  sqlstm.arrsiz = 11;
  sqlstm.sqladtp = &sqladt;
  sqlstm.sqltdsp = &sqltds;
  sqlstm.iters = (unsigned int  )1;
  sqlstm.offset = (unsigned int  )5130;
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


		if (sqlca.sqlcode != 0){
			LogWrite_C(DebugParms, LOG_ERROR, "GetStringArrayFromQuery: SQL Error %d\n", 1, sqlca.sqlcode);
			return sqlca.sqlcode;
		}
		Trim_C(vRet); strcpy(oRet[i], vRet);
	}
	/* EXEC SQL CLOSE c82; */ 

{
 struct sqlexd sqlstm;
 sqlstm.sqlvsn = 13;
 sqlstm.arrsiz = 11;
 sqlstm.sqladtp = &sqladt;
 sqlstm.sqltdsp = &sqltds;
 sqlstm.iters = (unsigned int  )1;
 sqlstm.offset = (unsigned int  )5149;
 sqlstm.cud = sqlcud0;
 sqlstm.sqlest = (unsigned char  *)&sqlca;
 sqlstm.sqlety = (unsigned short)4352;
 sqlstm.occurs = (unsigned int  )0;
 sqlcxt(&vCtx, &sqlctx, &sqlstm, &sqlfpn);
}


	return sqlca.sqlcode;
}
EXPORT int __stdcall GetIntFromQuery(tDebugInfo* DebugParms, sql_context pCtx, char* pSQL, int* oRet){
	/* EXEC SQL BEGIN DECLARE SECTION; */ 

	char vSQL[1000];
	int vRet = 0;
	sql_context vCtx = pCtx;
	/* EXEC SQL END   DECLARE SECTION; */ 

	strcpy(vSQL, pSQL);

	/* EXEC SQL CONTEXT USE :vCtx; */ 

	/* EXEC SQL PREPARE s1 FROM :vSQL; */ 

{
 struct sqlexd sqlstm;
 sqlstm.sqlvsn = 13;
 sqlstm.arrsiz = 11;
 sqlstm.sqladtp = &sqladt;
 sqlstm.sqltdsp = &sqltds;
 sqlstm.stmt = "";
 sqlstm.iters = (unsigned int  )1;
 sqlstm.offset = (unsigned int  )5164;
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
 sqlstm.offset = (unsigned int  )5183;
 sqlstm.selerr = (unsigned short)1;
 sqlstm.sqlpfmem = (unsigned int  )0;
 sqlstm.cud = sqlcud0;
 sqlstm.sqlest = (unsigned char  *)&sqlca;
 sqlstm.sqlety = (unsigned short)4352;
 sqlstm.occurs = (unsigned int  )0;
 sqlstm.sqcmod = (unsigned int )0;
 sqlcxt(&vCtx, &sqlctx, &sqlstm, &sqlfpn);
}


	/* EXEC SQL FETCH c1 INTO :vRet; */ 

{
 struct sqlexd sqlstm;
 sqlstm.sqlvsn = 13;
 sqlstm.arrsiz = 11;
 sqlstm.sqladtp = &sqladt;
 sqlstm.sqltdsp = &sqltds;
 sqlstm.iters = (unsigned int  )1;
 sqlstm.offset = (unsigned int  )5198;
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



	if (sqlca.sqlcode != 0){
		LogWrite_C(DebugParms, LOG_ERROR, "GetIntFromQuery: SQL Error %d\n", 1, sqlca.sqlcode);
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
 sqlstm.offset = (unsigned int  )5217;
 sqlstm.cud = sqlcud0;
 sqlstm.sqlest = (unsigned char  *)&sqlca;
 sqlstm.sqlety = (unsigned short)4352;
 sqlstm.occurs = (unsigned int  )0;
 sqlcxt(&vCtx, &sqlctx, &sqlstm, &sqlfpn);
}


	return sqlca.sqlcode;
}
EXPORT int __stdcall GetBarsFromQuery(tDebugInfo* DebugInfo, sql_context pCtx, char* pSQL, int pRecCount, int pSkipFirstN, tBar* oBar){
	/* EXEC SQL BEGIN DECLARE SECTION; */ 

	int i = 0;  int j;
	int retval = 0;
	char vNDT[12 + 1];
	//sql_context vCtx = pCtx;
	struct sBar{
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

	/* EXEC SQL CONTEXT USE :pCtx; */ 

	/* EXEC SQL PREPARE s4 FROM :vSQL; */ 

{
 struct sqlexd sqlstm;
 sqlstm.sqlvsn = 13;
 sqlstm.arrsiz = 11;
 sqlstm.sqladtp = &sqladt;
 sqlstm.sqltdsp = &sqltds;
 sqlstm.stmt = "";
 sqlstm.iters = (unsigned int  )1;
 sqlstm.offset = (unsigned int  )5232;
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
 sqlstm.offset = (unsigned int  )5251;
 sqlstm.selerr = (unsigned short)1;
 sqlstm.sqlpfmem = (unsigned int  )0;
 sqlstm.cud = sqlcud0;
 sqlstm.sqlest = (unsigned char  *)&sqlca;
 sqlstm.sqlety = (unsigned short)4352;
 sqlstm.occurs = (unsigned int  )0;
 sqlstm.sqcmod = (unsigned int )0;
 sqlcxt(&pCtx, &sqlctx, &sqlstm, &sqlfpn);
}


	for (i = 0; i<(pRecCount + pSkipFirstN); i++){
		/* EXEC SQL FETCH c4 INTO :vNDT, :vBar[i].Open, :vBar[i].High, :vBar[i].Low, :vBar[i].Close, :vBar[i].Volume; */ 

{
  struct sqlexd sqlstm;
  sqlstm.sqlvsn = 13;
  sqlstm.arrsiz = 11;
  sqlstm.sqladtp = &sqladt;
  sqlstm.sqltdsp = &sqltds;
  sqlstm.iters = (unsigned int  )1;
  sqlstm.offset = (unsigned int  )5266;
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


		if (sqlca.sqlcode == 0){
			strcpy(vBar[i].NewDateTime, vNDT);
		}
		else if (sqlca.sqlcode == 1403){
			break;
		}
		else{
			LogWrite_C(DebugInfo, LOG_ERROR, "GetBarsFromQuery (Loop): SQL Error %d\n", 1, sqlca.sqlcode);
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
 sqlstm.offset = (unsigned int  )5305;
 sqlstm.cud = sqlcud0;
 sqlstm.sqlest = (unsigned char  *)&sqlca;
 sqlstm.sqlety = (unsigned short)4352;
 sqlstm.occurs = (unsigned int  )0;
 sqlcxt(&pCtx, &sqlctx, &sqlstm, &sqlfpn);
}



	if (i > 0) {
		for (j = 0; j < pRecCount; j++){
			memcpy(&oBar[j], &vBar[pSkipFirstN + j], sizeof(tBar));
		}
	}
	free(vBar);
	return retval;
}
EXPORT int __stdcall GetBarsFromQuery2(tDebugInfo* DebugParms, sql_context pCtx, char* pSQL, int* pRecCount, tBar* oBar){
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
	/* EXEC SQL CONTEXT USE :vCtx; */ 

	/* EXEC SQL PREPARE s9 FROM :vSQL; */ 

{
 struct sqlexd sqlstm;
 sqlstm.sqlvsn = 13;
 sqlstm.arrsiz = 11;
 sqlstm.sqladtp = &sqladt;
 sqlstm.sqltdsp = &sqltds;
 sqlstm.stmt = "";
 sqlstm.iters = (unsigned int  )1;
 sqlstm.offset = (unsigned int  )5320;
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
 sqlstm.offset = (unsigned int  )5339;
 sqlstm.selerr = (unsigned short)1;
 sqlstm.sqlpfmem = (unsigned int  )0;
 sqlstm.cud = sqlcud0;
 sqlstm.sqlest = (unsigned char  *)&sqlca;
 sqlstm.sqlety = (unsigned short)4352;
 sqlstm.occurs = (unsigned int  )0;
 sqlstm.sqcmod = (unsigned int )0;
 sqlcxt(&vCtx, &sqlctx, &sqlstm, &sqlfpn);
}


	for (i = 0; i<(*pRecCount); i++){
		/* EXEC SQL FETCH c9 INTO :vNDT, :vOpen, :vHigh, :vLow, :vClose, :vOpenD, :vHighD, :vLowD, :vCloseD; */ 

{
  struct sqlexd sqlstm;
  sqlstm.sqlvsn = 13;
  sqlstm.arrsiz = 11;
  sqlstm.sqladtp = &sqladt;
  sqlstm.sqltdsp = &sqltds;
  sqlstm.iters = (unsigned int  )1;
  sqlstm.offset = (unsigned int  )5354;
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


		if (sqlca.sqlcode == 0){
			strcpy(oBar[i].NewDateTime, vNDT);
			oBar[i].Open = vOpen; oBar[i].OpenD = vOpenD;
			oBar[i].High = vHigh; oBar[i].HighD = vHighD;
			oBar[i].Low = vLow; oBar[i].LowD = vLowD;
			oBar[i].Close = vClose; oBar[i].CloseD = vCloseD;
		}
		else if (sqlca.sqlcode == 1403){
			(*pRecCount) = i;
			break;
		}
		else{
			LogWrite_C(DebugParms, LOG_ERROR, "GetBarsFromQuery (Loop): SQL Error %d\n", 1, sqlca.sqlcode);
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
 sqlstm.offset = (unsigned int  )5405;
 sqlstm.cud = sqlcud0;
 sqlstm.sqlest = (unsigned char  *)&sqlca;
 sqlstm.sqlety = (unsigned short)4352;
 sqlstm.occurs = (unsigned int  )0;
 sqlcxt(&vCtx, &sqlctx, &sqlstm, &sqlfpn);
}



	for (i = 0; i < (*pRecCount) / 2; i++){
		tmpd = oBar[(*pRecCount) - i].Open;
		oBar[(*pRecCount) - i].Open = oBar[i].Open;
		oBar[i].Open = tmpd;
	}

	return retval;
}
//===

//=== ConcordanceCalc() stuff
EXPORT int __stdcall GetHRecCount(tDebugInfo* DebugParms, void* pCtx, char* pHSymbol, char* pTimeFrame, char* pCFromDate, int pDelta, int pIsFilled, int* HRecCount){
	//--- Select... 
	char stmt[1000];
	strcpy(stmt, "select count(*) from History.");
	strcat(stmt, pHSymbol);
	strcat(stmt, "_");
	strcat(stmt, pTimeFrame);
	strcat(stmt, (pIsFilled == 1) ? "_FILLED " : " ");
	strcat(stmt, "where NewDateTime < to_date('");
	strcat(stmt, pCFromDate);
	strcat(stmt, "','YYYYMMDDHH24MI')");

	return(GetIntFromQuery(DebugParms, pCtx, stmt, HRecCount));

}
EXPORT int __stdcall LoadCurrentRecord(tDebugInfo* DebugParms, void* pCtx, char* pCSymbol, char* pTimeFrame, char* pCToDate, int pPastDepth, int pDelta, int pIsFilled, int pCRecCount, tBar* oCRec){
	char stmt[1000];
	char vPastDepth[4];

	strcpy(stmt, "select * from (");
	strcat(stmt, "select to_char(NewDateTime, 'YYYYMMDDHH24MI'), Open, High, Low, Close, Open-nvl(lag(Open) over(order by NewDateTime), 0), High-nvl(lag(High) over(order by NewDateTime), 0), Low-nvl(lag(Low) over(order by NewDateTime), 0), Close-nvl(lag(Close) over(order by NewDateTime), 0) from History.");
	strcat(stmt, pCSymbol);
	strcat(stmt, "_");
	strcat(stmt, pTimeFrame);
	strcat(stmt, (pIsFilled == 1) ? "_FILLED " : " ");
	strcat(stmt, "where NewDateTime <= to_date('");
	strcat(stmt, pCToDate);
	strcat(stmt, "','YYYYMMDDHH24MI') order by NewDateTime desc");
	strcat(stmt, ") where rownum<=");
	sprintf(&vPastDepth[0], "%d", pPastDepth);
	strcat(stmt, vPastDepth);
	strcat(stmt, " order by 1");
	//LogWrite_C(pDebugLevel, pLogFile, "%s LoadCurrentRecord() executing: %s\n", 2, timestamp_C, stmt);

	return (GetBarsFromQuery(DebugParms, pCtx, stmt, pPastDepth, 0, oCRec));
}
EXPORT int __stdcall LoadHistoryRecord(tDebugInfo* DebugParms, void* pCtx, char* pCSymbol, char* pTimeFrame, char* pCFromDate, int pDelta, int pIsFilled, int pHRecCount, tBar* oHRec){
	char stmt[1000];

	strcpy(stmt, "select to_char(NewDateTime, 'YYYYMMDDHH24MI'), Open, High, Low, Close, Open-nvl(lag(Open) over(order by NewDateTime), 0), High-nvl(lag(High) over(order by NewDateTime), 0), Low-nvl(lag(Low) over(order by NewDateTime), 0), Close-nvl(lag(Close) over(order by NewDateTime), 0) from History.");
	strcat(stmt, pCSymbol);
	strcat(stmt, "_");
	strcat(stmt, pTimeFrame);
	strcat(stmt, (pIsFilled == 1) ? "_FILLED " : " ");
	strcat(stmt, "where NewDateTime < to_date('");
	strcat(stmt, pCFromDate);
	strcat(stmt, "','YYYYMMDDHH24MI') order by 1");

	return (GetBarsFromQuery(DebugParms, pCtx, stmt, pHRecCount, 0, oHRec));
}
EXPORT int __stdcall LoadTimeSeries(tDebugInfo* DebugParms, void* pCtx, char* pSymbol, char* pTimeFrame, char* pFromDate, int pDelta, int pIsFilled, int pRecCount, tBar* oRec){
	char stmt[1000];

	strcpy(stmt, "select to_char(NewDateTime, 'YYYYMMDDHH24MI'), Open, High, Low, Close, Open-nvl(lag(Open) over(order by NewDateTime), 0), High-nvl(lag(High) over(order by NewDateTime), 0), Low-nvl(lag(Low) over(order by NewDateTime), 0), Close-nvl(lag(Close) over(order by NewDateTime), 0) from History.");
	strcat(stmt, pSymbol);
	strcat(stmt, "_");
	strcat(stmt, pTimeFrame);
	strcat(stmt, (pIsFilled == 1) ? "_FILLED " : " ");
	strcat(stmt, "where NewDateTime >= to_date('");
	strcat(stmt, pFromDate);
	strcat(stmt, "','YYYYMMDDHH24MI') order by 1");

	return (GetBarsFromQuery(DebugParms, pCtx, stmt, pRecCount, 0, oRec));
}
//===

//=== OBSOLETE STUFF ===
EXPORT int  __stdcall OraInsert(tDebugInfo* DebugInfo, sql_context pCtx, char* pSQL) {
	/* EXEC SQL BEGIN DECLARE SECTION; */ 

	char* vCtx = pCtx;
	char* vSQL = pSQL;
	/* EXEC SQL END   DECLARE SECTION; */ 


	/* EXEC SQL CONTEXT USE : vCtx; */ 

	/* EXEC SQL ALTER SESSION SET NLS_DATE_FORMAT = 'YYYYMMDDHH24MI'; */ 

{
 struct sqlexd sqlstm;
 sqlstm.sqlvsn = 13;
 sqlstm.arrsiz = 11;
 sqlstm.sqladtp = &sqladt;
 sqlstm.sqltdsp = &sqltds;
 sqlstm.stmt = "alter SESSION SET NLS_DATE_FORMAT = 'YYYYMMDDHH24MI'";
 sqlstm.iters = (unsigned int  )1;
 sqlstm.offset = (unsigned int  )5420;
 sqlstm.cud = sqlcud0;
 sqlstm.sqlest = (unsigned char  *)&sqlca;
 sqlstm.sqlety = (unsigned short)4352;
 sqlstm.occurs = (unsigned int  )0;
 sqlcxt(&vCtx, &sqlctx, &sqlstm, &sqlfpn);
}


	/* EXEC SQL EXECUTE IMMEDIATE : vSQL; */ 

{
 struct sqlexd sqlstm;
 sqlstm.sqlvsn = 13;
 sqlstm.arrsiz = 11;
 sqlstm.sqladtp = &sqladt;
 sqlstm.sqltdsp = &sqltds;
 sqlstm.stmt = "";
 sqlstm.iters = (unsigned int  )1;
 sqlstm.offset = (unsigned int  )5435;
 sqlstm.cud = sqlcud0;
 sqlstm.sqlest = (unsigned char  *)&sqlca;
 sqlstm.sqlety = (unsigned short)4352;
 sqlstm.occurs = (unsigned int  )0;
 sqlstm.sqhstv[0] = (         void  *)vSQL;
 sqlstm.sqhstl[0] = (unsigned int  )0;
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



	if (sqlca.sqlcode == 0) {
		/* EXEC SQL COMMIT; */ 

{
  struct sqlexd sqlstm;
  sqlstm.sqlvsn = 13;
  sqlstm.arrsiz = 11;
  sqlstm.sqladtp = &sqladt;
  sqlstm.sqltdsp = &sqltds;
  sqlstm.iters = (unsigned int  )1;
  sqlstm.offset = (unsigned int  )5454;
  sqlstm.cud = sqlcud0;
  sqlstm.sqlest = (unsigned char  *)&sqlca;
  sqlstm.sqlety = (unsigned short)4352;
  sqlstm.occurs = (unsigned int  )0;
  sqlcxt(&vCtx, &sqlctx, &sqlstm, &sqlfpn);
}


		return 0;
	}
	else {
		LogWrite_C(DebugInfo, LOG_ERROR, "Insert Failed: SQL Error %d\n", 1, sqlca.sqlcode);
		return sqlca.sqlcode;
	}


}
EXPORT void __stdcall OraAllocateCtx(sql_context pCtx[MAX_CONTEXTS]) {
	/* EXEC SQL BEGIN DECLARE SECTION; */ 

	sql_context vCtx[6];
	/* EXEC SQL END   DECLARE SECTION; */ 

	for (int i = 0; i < MAX_CONTEXTS; i++) {
		/* EXEC SQL CONTEXT ALLOCATE : vCtx[i]; */ 

{
  struct sqlexd sqlstm;
  sqlstm.sqlvsn = 13;
  sqlstm.arrsiz = 11;
  sqlstm.sqladtp = &sqladt;
  sqlstm.sqltdsp = &sqltds;
  sqlstm.stmt = "";
  sqlstm.iters = (unsigned int  )1;
  sqlstm.offset = (unsigned int  )5469;
  sqlstm.cud = sqlcud0;
  sqlstm.sqlest = (unsigned char  *)&sqlca;
  sqlstm.sqlety = (unsigned short)4352;
  sqlstm.occurs = (unsigned int  )0;
  sqlstm.sqhstv[0] = (         void  *)&vCtx[i];
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


		pCtx[i] = vCtx[i];
	}
	return;
}
EXPORT void __stdcall OraEnableThreads() {
	/* EXEC SQL ENABLE THREADS; */ 

{
 struct sqlexd sqlstm;
 sqlstm.sqlvsn = 13;
 sqlstm.arrsiz = 11;
 sqlstm.sqladtp = &sqladt;
 sqlstm.sqltdsp = &sqltds;
 sqlstm.stmt = "";
 sqlstm.iters = (unsigned int  )1;
 sqlstm.offset = (unsigned int  )5488;
 sqlstm.cud = sqlcud0;
 sqlstm.sqlest = (unsigned char  *)&sqlca;
 sqlstm.sqlety = (unsigned short)4352;
 sqlstm.occurs = (unsigned int  )0;
 sqlcxt((void **)0, &sqlctx, &sqlstm, &sqlfpn);
}


	return;
}
EXPORT void __stdcall OraContextFree(sql_context pCtx) {
	/* EXEC SQL BEGIN DECLARE SECTION; */ 

	sql_context vCtx = pCtx;
	/* EXEC SQL END   DECLARE SECTION; */ 

	/* EXEC SQL CONTEXT USE : vCtx; */ 

	/* EXEC SQL COMMIT WORK RELEASE; */ 

{
 struct sqlexd sqlstm;
 sqlstm.sqlvsn = 13;
 sqlstm.arrsiz = 11;
 sqlstm.sqladtp = &sqladt;
 sqlstm.sqltdsp = &sqltds;
 sqlstm.iters = (unsigned int  )1;
 sqlstm.offset = (unsigned int  )5503;
 sqlstm.cud = sqlcud0;
 sqlstm.sqlest = (unsigned char  *)&sqlca;
 sqlstm.sqlety = (unsigned short)4352;
 sqlstm.occurs = (unsigned int  )0;
 sqlcxt(&vCtx, &sqlctx, &sqlstm, &sqlfpn);
}


	/* EXEC SQL CONTEXT FREE : vCtx; */ 

{
 struct sqlexd sqlstm;
 sqlstm.sqlvsn = 13;
 sqlstm.arrsiz = 11;
 sqlstm.sqladtp = &sqladt;
 sqlstm.sqltdsp = &sqltds;
 sqlstm.stmt = "";
 sqlstm.iters = (unsigned int  )1;
 sqlstm.offset = (unsigned int  )5518;
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


}


//===

create or replace package ConcMQ4 as
	-- Data Structures to hold/pass OHLC data from MT4

	type t_cBar is record(
		cBarOpenTime	number,
		cBarOpen  		number,
		cBarHigh  		number,
		cBarLow   		number,
		cBarClose 		number	
	);

	--type t_cBarArray is table of t_cBar index by binary_integer;
	type t_cBarArray is table of number index by binary_integer;
	
	-------------------------------------------------------------
	--TotalBars number;
	CFromDate varchar2(15);
	CToDate   varchar2(15);

	LogFileName varchar2(30) := 'ConcMQ4.log';
	LogFile utl_file.file_type;

	--procedure Run(CSymbol varchar2, pDelta boolean, CToDate varchar2, TotalBars number, OOSBars number, HSymbol varchar2, TimeFrame varchar2, isFilled boolean, OutputType varchar2, Measure varchar2, nPeriods number);
	--procedure WriteFiles(CSymbol varchar2, pDelta boolean, CToDate varchar2, TotalBars number, OOSBars number, HSymbol varchar2, TimeFrame varchar2, isFilled boolean, Measure varchar2, OutputType varchar2, nPeriods number);
	-- OOSLen: Current Length, Out-of-Sample (Bars)
	procedure MyLog(pDebug number, pDebugPath varchar2, pmsg varchar2, pFlush boolean default false);
	function Calc (pCSymbol varchar2, pDelta number, pTotalBars number, pBarO dbms_sql.number_table, pBarH dbms_sql.number_table, pBarL dbms_sql.number_table, pBarC dbms_sql.number_table, pBarYY dbms_sql.number_table, pBarMM dbms_sql.number_table, pBarDD dbms_sql.number_table, pBarHH dbms_sql.number_table, pBarMI dbms_sql.number_table, pHSymbol varchar2, TimeFrame varchar2, isFilled number, OutputType varchar2, Measure varchar2, pDebug number, pDebugPath varchar2) return number;
	--procedure Chart(CSymbol varchar2, CFromDate varchar2, HSymbol varchar2, TimeFrame varchar2, isFilled boolean, OutputType varchar2);
	--function Load_Hst (HToDate varchar2, HSymbol varchar2, TimeFrame varchar2, isFilled boolean, OutputType varchar2) return number;
	--function Load_Cur (CToDate varchar2, TotalBars number, CSymbol varchar2, TimeFrame varchar2, isFilled boolean, OutputType varchar2) return number;
	--function Load_Hst(HSymbol varchar2, TimeFrame varchar2, CFromDate varchar2, isFilled number, OutputType varchar2) return number;

	pRank dbms_sql.number_table;
	hndt dbms_sql.date_table; cndt dbms_sql.date_table;
	cur dbms_sql.number_table;
	hst dbms_sql.number_table;
	curD dbms_sql.number_table;
	hstD dbms_sql.number_table;
	BestPredictorStart dbms_sql.date_table;	
	Max_Predictors number :=10;
	Cnrec number :=0; Hnrec number :=0; 
	type rc is ref cursor;

	end ConcMQ4;
/
show errors;

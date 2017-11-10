create or replace package Concordance as
	procedure Run(CSymbol varchar2, pDelta boolean, CToDate varchar2, TotalBars number, OOSBars number, HSymbol varchar2, TimeFrame varchar2, isFilled boolean, OutputType varchar2, Measure varchar2, nPeriods number);
	procedure WriteFiles(CSymbol varchar2, pDelta boolean, CToDate varchar2, TotalBars number, OOSBars number, HSymbol varchar2, TimeFrame varchar2, isFilled boolean, Measure varchar2, OutputType varchar2, nPeriods number);
	-- OOSLen: Current Length, Out-of-Sample (Bars)
	procedure Calc (CSymbol varchar2, pDelta boolean, CToDate varchar2, TotalBars number, HSymbol varchar2, TimeFrame varchar2, isFilled boolean, OutputType varchar2);
	--procedure Chart(CSymbol varchar2, CFromDate varchar2, HSymbol varchar2, TimeFrame varchar2, isFilled boolean, OutputType varchar2);
	function Load_Hst (HToDate varchar2, HSymbol varchar2, TimeFrame varchar2, isFilled boolean, OutputType varchar2) return number;
	function Load_Cur (CToDate varchar2, TotalBars number, CSymbol varchar2, TimeFrame varchar2, isFilled boolean, OutputType varchar2) return number;
	procedure Load_AllData (CToDate varchar2, TotalBars number, CSymbol varchar2, HSymbol varchar2, TimeFrame varchar2, isFilled boolean, OutputType varchar2);
	function IIf (ckexpr boolean, iftrue varchar2, iffalse varchar2) return varchar2;
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
end Concordance;
/
show errors;

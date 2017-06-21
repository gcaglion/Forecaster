create or replace package body ConcMQ4 as

procedure MyLog(pDebug number, pDebugPath varchar2, pmsg varchar2, pFlush boolean default false) is
	CurrentTime varchar2(30);
	msg varchar2(1000);
begin
	execute immediate 'select to_char(sysdate,'||chr(39)||'YYYY-MM-DD HH24:MI:SS'||chr(39)||') from dual' into CurrentTime;
	msg:=CurrentTime||' '||pmsg;

	dbms_output.put_line(msg);
	if pDebug>1 then
		if utl_file.is_open(LogFile)=FALSE then
			LogFile:=utl_file.fopen(pDebugPath, LogFileName, 'A', 32767);
		end if;
		utl_file.put_line(LogFile, msg);
		if pFlush then
			utl_file.fflush(LogFile);
		end if;
		--utl_file.fclose(LogFile);
	end if;

/*
	execute immediate 'insert into MyLog(Timestamp, Msg) values(:a, :b)' using CurrentTime, pmsg;
	commit;
*/
end MyLog;

procedure sRank(pList dbms_sql.number_table, pLength number, pStart number) is
	cC rc; ndt date;  swapped boolean; tmp number; 
	px dbms_sql.number_table; prx dbms_sql.number_table;
	SumRank number; itoavgcount number; 
begin
	--dbms_output.put_line('sRank called with pLength='||pLength||' , pStart='||pStart);
	for i in 1..pLength loop
		px(i):=pList(i+pStart-1);	-- copio x() in px()
	end loop;
	
	loop
		swapped:=false;
		for i in 2..pLength loop
			if px(i-1)<px(i) then
				tmp:=px(i);
				px(i):=px(i-1); 
				px(i-1):=tmp;
				swapped:=true;
			end if;
		end loop;
		exit when not swapped;
	end loop;	
	
	for i in 1..pLength loop
		SumRank:=0; itoavgcount:=0; 
		for j in 1..pLength loop			
			if px(j)=pList(i+pStart-1) then
				itoavgcount:=itoavgcount+1;
				SumRank:=SumRank+j;
			end if;
		end loop;
		pRank(i):=SumRank/itoavgcount;
		--dbms_output.put_line('i='||i||'; px('||i||')='||px(i)||'; pRank('||i||')='||pRank(i));
	end loop;
end sRank;

function Load_Hst(vDebug number, vDebugPath varchar2, HSymbol varchar2, TimeFrame varchar2, CFromDate varchar2, CToDate varchar2, isFilled number, OutputType varchar2, pDebug number, pDebugPath varchar2) return number is
	cH rc;
	ndt_h date; vValue_h number; vValued_h number;
	nrec number:=0;
	AllBarsH number;
	Filled_Suffix varchar2(7);
	LoadStmt varchar2(1000);
	err_code number; err_msg varchar2(200); err_timestamp date;
begin
	if isFilled=1 then Filled_Suffix:='_FILLED'; else Filled_Suffix:=''; end if;
	--execute immediate 'select count(*) from History.'||HSymbol||'_'||TimeFrame||Filled_Suffix||' where NewDateTime < to_date('||chr(39)||CFromDate||chr(39)||',''YYYY-MM-DD-HH24MI'')' into AllBarsH;
	--utl_file.put_line(LogFile, 'Load_Hst:     AllBarsH='||AllBarsH);
	--dbms_output.put_line('Load_Hst: CFromDate='||CFromDate);
	LoadStmt:='select NewDateTime,'||OutputType||', '||OutputType||'-lag('||OutputType||') over (order by NewDateTime) from History.'||HSymbol||'_'||TimeFrame||Filled_Suffix||' where NewDateTime <= to_date('||chr(39)||CToDate  ||chr(39)||',''YYYYMMDDHH24MI'') order by 1';
	MyLog(pDebug, pDebugPath, 'Load_Hst: '||LoadStmt);
	BEGIN
		open cH for LoadStmt;
		loop
			fetch cH into ndt_h, vValue_h, vValued_h;
			--utl_file.put_line(LogFile, 'Load_Hst: vValue_h='||vValue_h);
			nrec:=nrec+1; 
			--utl_file.put_line(LogFile, 'nrec='||nrec);
			if (cH%NOTFOUND) then
				--utl_file.put_line(LogFile, 'Load_Hst: Exiting loop; nrec='||nrec);
				close cH;
				return (nrec-1);
			end if;
			hndt(nrec):=ndt_h;
			hst(nrec):=vValue_h;
			hstD(nrec):=vValued_h;
		end loop;
		return (nrec);
	EXCEPTION
		WHEN OTHERS THEN
			err_code := SQLCODE;
			err_msg := SUBSTR(SQLERRM, 1, 200);
			MyLog(vDebug, vDebugPath, 'Load_Hst raised error '||err_code||': '||err_msg);
	END;
end Load_Hst;

	function Calc (
					pCSymbol varchar2, 
					pDelta number, 
					pTotalBars number, 
					pBarO dbms_sql.number_table, 
					pBarH dbms_sql.number_table, 
					pBarL dbms_sql.number_table, 
					pBarC dbms_sql.number_table, 
					pBarYY dbms_sql.number_table, 
					pBarMM dbms_sql.number_table, 
					pBarDD dbms_sql.number_table, 
					pBarHH dbms_sql.number_table, 
					pBarMI dbms_sql.number_table, 
					pHSymbol varchar2, 
					TimeFrame varchar2, 
					isFilled number, 
					OutputType varchar2, 
					Measure varchar2,
					pDebug number,
					pDebugPath varchar2
					) return number is
	vTF number;
	rcur dbms_sql.number_table;
	rhst dbms_sql.number_table;
	vSRho number; vKTau number; vGini number; vWeakC number;
	Knumer number:=0; Snumer number:=0; Wnumer number:=0;
	GSum number; GSumR number; gAvg number; GSumA number; GAvgA number;
	h number; l number; 
	vExistingDataQuery varchar2(10000);
	vExistingData number;
	CFromDate varchar2(20); 
	CToDate varchar2(20); 
	Hnrec number;
	instmt varchar2(10000);	
	CSymbol varchar2(6);
	HSymbol varchar2(6);
	vDebug number;
	vDebugPath varchar2(1000);
	CurrentTime date;
	TotalBars number;
	kaz number;
	selstmt varchar2(1000);
begin
	vDebug:=pDebug;
	vDebugPath:=pDebugPath; --vDebugPath:=substr(pDebugPath,1,length(pDebugPath)-1);
	
	MyLog(vDebug, vDebugPath, 'Starting Calc()...');
	
	selstmt:='select Hst_Symbol from History.Symbol_Lookup where MT4_Symbol=trim('||chr(39)||pCSymbol||chr(39)||')';
	MyLog(vDebug, vDebugPath, selstmt);
	execute immediate selstmt into CSymbol;
	if CSymbol='' then 
		MyLog(vDebug, vDebugPath, 'Could not find CSymbol ('||pCSymbol||' in Symbol_Lookup. Exiting.');
		utl_file.fclose(LogFile);
		return -1;
	end if;
	selstmt:='select Hst_Symbol from History.Symbol_Lookup where MT4_Symbol=trim('||chr(39)||pHSymbol||chr(39)||')';
	execute immediate selstmt into HSymbol;
	if HSymbol='' then 
		MyLog(vDebug, vDebugPath,'Could not find HSymbol ('||pHSymbol||' in Symbol_Lookup. Exiting.');
		utl_file.fclose(LogFile);
		return -1;
	end if;
	MyLog(vDebug, vDebugPath, 'CSymbol='||pCSymbol||' ; HSymbol='||pHSymbol||' ; pTotalBars='||pTotalBars);

	TotalBars:=pTotalBars;
	/*
	for i in 1..pTotalBars loop
		MyLog(vDebug, vDebugPath, 'CFromDate['||i||']='||trim(' ' from to_char(pBarYY(i),'9999'))||trim(' ' from to_char(pBarMM(i),'09'))||trim(' ' from to_char(pBarDD(i),'09'))||trim(' ' from to_char(pBarHH(i),'09'))||trim(' ' from to_char(pBarMI(i),'09')));
	end loop;
	*/
	--CFromDate:=trim(' ' from to_char(pBarYY(pTotalBars),'9999'))||trim(' ' from to_char(pBarMM(pTotalBars),'09'))||trim(' ' from to_char(pBarDD(pTotalBars),'09'))||trim(' ' from to_char(pBarHH(pTotalBars),'09'))||trim(' ' from to_char(pBarMI(pTotalBars),'09'));
	MyLog(vDebug, vDebugPath, '---------------------- Procedure started --------------------');
	MyLog(vDebug, vDebugPath, 'Latest   Current Bar: '||trim(' ' from to_char(pBarYY(1),'9999'))||trim(' ' from to_char(pBarMM(1),'09'))||trim(' ' from to_char(pBarDD(1),'09'))||trim(' ' from to_char(pBarHH(1),'09'))||trim(' ' from to_char(pBarMI(1),'09')));
	MyLog(vDebug, vDebugPath, 'Earliest Current Bar: '||trim(' ' from to_char(pBarYY(pTotalBars),'9999'))||trim(' ' from to_char(pBarMM(pTotalBars),'09'))||trim(' ' from to_char(pBarDD(pTotalBars),'09'))||trim(' ' from to_char(pBarHH(pTotalBars),'09'))||trim(' ' from to_char(pBarMI(pTotalBars),'09')));
	CFromDate:=										    trim(' ' from to_char(pBarYY(pTotalBars),'9999'))||trim(' ' from to_char(pBarMM(pTotalBars),'09'))||trim(' ' from to_char(pBarDD(pTotalBars),'09'))||trim(' ' from to_char(pBarHH(pTotalBars),'09'))||trim(' ' from to_char(pBarMI(pTotalBars),'09'));
	MyLog(vDebug, vDebugPath, 'CFromDate:            '||CFromDate);
	CToDate:=										    trim(' ' from to_char(pBarYY(1),'9999'))||trim(' ' from to_char(pBarMM(1),'09'))||trim(' ' from to_char(pBarDD(1),'09'))||trim(' ' from to_char(pBarHH(1),'09'))||trim(' ' from to_char(pBarMI(1),'09'));
	MyLog(vDebug, vDebugPath, 'CToDate:              '||CToDate);
/*	
	-- === Don't even start if TConcordance has already the same data ===
	vExistingDataQuery:=					 'select count(*) from TConcordance where ';
	vExistingDataQuery:=vExistingDataQuery ||'CurrentData=' ||chr(39)||CSymbol  ||chr(39)||' and ';
	vExistingDataQuery:=vExistingDataQuery ||'TimeFrame='   ||chr(39)||TimeFrame||chr(39)||' and ';
	vExistingDataQuery:=vExistingDataQuery ||'PatternLength='||pTotalBars||' and ';
	vExistingDataQuery:=vExistingDataQuery ||'CurrentStart=to_date('||chr(39)||CFromDate||chr(39)||','||chr(39)||'YYYYMMDDHH24MI'||chr(39)||')';
	MyLog(vDebug, vDebugPath, 'ExistingDataQuery='||vExistingDataQuery, true);	
	execute immediate vExistingDataQuery into vExistingData;
	MyLog(vDebug, vDebugPath, 'ExistingData='||vExistingData);
	if vExistingData>0 then
		MyLog(vDebug, vDebugPath, 'No need to run Calc. Exiting.');
		utl_file.fclose(LogFile);
		return 0;
	end if;
*/
	--====================================================================
	Hnrec:=Load_Hst(vDebug, vDebugPath, HSymbol, TimeFrame, CFromDate, CToDate, isFilled, OutputType, vDebug, vDebugPath);
	MyLog(vDebug, vDebugPath, 'Calc: Hnrec='||Hnrec||' ; TotalBars='||TotalBars);
	if Hnrec=0 then
		MyLog(vDebug, vDebugPath, 'No History found. Cannot continue....');
		utl_file.fclose(LogFile);
		return -1;
	end if;
	-- ---- Load Current Data, outside Load_cur ---
	for i in 1..TotalBars loop
		if OutputType='Open' then
			cur(i):=pBarO(TotalBars-i+1);
		elsif OutputType='High' then
			cur(i):=pBarH(TotalBars-i+1);
		elsif OutputType='Low' then
			cur(i):=pBarL(TotalBars-i+1);
		elsif OutputType='Close' then
			cur(i):=pBarC(TotalBars-i+1);
		end if;
	end loop;
	-- --------------------------------------------
	-- Main Loop --
	-- --------------------------------------------
	execute immediate 'select sysdate from dual' into CurrentTime;
	MyLog(vDebug, vDebugPath, 'Main Loop started.', true);
	for h in 1..Hnrec-TotalBars-1 loop
		for l in TotalBars..TotalBars loop
		--for l in TotalBars/2..TotalBars loop
		--for l in 60..TotalBars loop
			-- == Calc SRho ==
			Snumer:=0;
			-- Rank l elements of cur(), starting from the 1st
			sRank(cur,l,1);
			for i in 1..l loop
				rcur(i):=pRank(i);
			end loop;
			-- Rank l elements of y(), starting from the <h>st
			sRank(hst,l,h);
			for i in 1..l loop
				rhst(i):=pRank(i);
			end loop;
			--
			for i in 1..l loop
				Snumer:=Snumer+(rcur(i)-rhst(i))**2;
			end loop;
			--vSRho:= ( 1-6*Snumer/(Cnrec**3-Cnrec) ); --dbms_output.put_line('h='||h||'; l='||l||'; vSRho='||vSRho);
			vSRho:= ( 1-6*Snumer/(l**3-l) ); --dbms_output.put_line('h='||h||'; l='||l||'; vSRho='||vSRho);

			-- == Calc KTau ==
			Knumer:=0; GSum:=0; GSumR:=0; GSumA:=0;
			for i in 2..l loop
				for j in 1..(i-1) loop
					Knumer:=Knumer+ Sign(cur(i)-cur(j)) * Sign(hst(h+i)-hst(h+j));		
					GSum:=GSum+Abs(hst(i)-hst(j));
					GSumA:=GSumA+hst(i);
					GSumR:=GSumR+hst(i)*rhst(i);
				end loop;
			end loop;
			--vKTau:=2*Knumer/(Cnrec*(Cnrec-1)); --dbms_output.put_line('h='||h||'; l='||l||'; vSRho='||vSRho||' ; vKTau='||vKTau);
			vKTau:=2*Knumer/(l*(l-1)); --dbms_output.put_line('h='||h||'; l='||l||'; vSRho='||vSRho||' ; vKTau='||vKTau);

			-- == Calc Gini ==
			GAvg:=GSum/l; GAvgA:=GSumA/l; 
			vGini:=GSum/(l*l*GAvg);

			-- == Calc WeakC ==
			Wnumer:=0;
			for i in 2..l loop
				if (cur(i)-cur(i-1))*(hst(i)-hst(i-1)) >0 then
					Wnumer:=Wnumer+1;
				else
					Wnumer:=Wnumer-1;
				end if;
			end loop;
			--vWeakC:=Wnumer/(Cnrec-1); --dbms_output.put_line('h='||h||'; l='||l||'; vWeakC:='||vWeakC);
			vWeakC:=Wnumer/(l-1); --dbms_output.put_line('h='||h||'; l='||l||'; vWeakC:='||vWeakC);
			
			-- == Populate TConcordance ==
			--dbms_output.put_line('h='||h||'; l='||l||'; vSRho='||vSRho||' ; vKTau='||vKTau||' ; vWeakC='||vWeakC);
			instmt:='insert into TConcordance(CurrentData, CurrentStart, PredictorData, TimeFrame, OutputType, PredictorStart, PatternLength, PatternShift, KTau, SRho, Gini, WeakC) values ('||chr(39)||CSymbol||chr(39)||', to_date('||chr(39)||CFromDate||chr(39)||','||chr(39)||'YYYYMMDDHH24MI'||chr(39)||'),'||chr(39)||HSymbol||chr(39)||','||chr(39)||TimeFrame||chr(39)||','||chr(39)||OutputType||chr(39)||', to_date('||chr(39)||to_char(hndt(h),'YYYYMMDDHH24MI')||chr(39)||','||chr(39)||'YYYYMMDDHH24MI'||chr(39)||'), '||l||', '||h||', '||vKTau||', '||vSRho||', '||vGini||', '||vWeakC||')';
			begin
				--MyLog(vDebug, vDebugPath, instmt);
				execute immediate instmt;
			exception
				when DUP_VAL_ON_INDEX then
					kaz:=0;
					--MyLog(vDebug, vDebugPath, 'Cannot Insert in TConcordance. Duplication.... NOT Exiting Calc...');
				when OTHERS then
					MyLog(vDebug, vDebugPath, 'Cannot Insert in TConcordance. ORA'||SQLCODE||'. Exiting Calc...');
					return -1;
			end;
		end loop;
	end loop;
	commit;
	MyLog(vDebug, vDebugPath, 'Main Loop completed.', true);
	
	-- BestPredictorStart:=PickBestPredictor(HSymbol, Measure);
	
	-- == Write Output files
	--WriteFiles (CSymbol, CFromDate, CToDate, HSymbol, TimeFrame, isFilled, OutputType, nPeriods);
	-- == Write Chart files
	--Chart (CSymbol, CFromDate, HSymbol, TimeFrame, isFilled, OutputType);
	utl_file.fclose(LogFile);
	return 0;
end Calc;

end ConcMQ4;
/
show errors;

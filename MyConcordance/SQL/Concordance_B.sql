create or replace package body Concordance as
	HistoryLength number;
FUNCTION IIf (ckexpr boolean, iftrue varchar2, iffalse varchar2) return varchar2 AS
	retval varchar2(30);
BEGIN
	if ckexpr=TRUE then
		return iftrue;
	else
		return iffalse;
	end if;
END;
	
procedure Run(CSymbol varchar2, pDelta boolean, CToDate varchar2, TotalBars number, OOSBars number, HSymbol varchar2, TimeFrame varchar2, isFilled boolean, OutputType varchar2, Measure varchar2, nPeriods number) is
begin
	Calc      (CSymbol, pDelta, CToDate, TotalBars, HSymbol, TimeFrame, isFilled, OutputType);
	WriteFiles(CSymbol, pDelta, CToDate, TotalBars, OOSBars, HSymbol, TimeFrame, isFilled, Measure, OutputType, nPeriods);
end Run;
procedure WriteFile_Current(OutputFileNameC varchar2, pDelta boolean, StartRec number, EndRec number, nPeriods number) is
	OutputFileC utl_file.file_type;  -- Current Data File
	vLine varchar2(10000); vLineCount number:=0;
	vDataSrc number; vDatesrc date;
	WrittenBars number;
begin
	--dbms_output.put_line('WriteFile_Current:   StartRec='||StartRec||' ; EndRec='||EndRec);
	--dbms_output.put_line('WriteFile_Current:   OutputFileNameC='||OutputFileNameC);
	OutputFileC := utl_file.fopen ('C:\Users\gcaglion\Documents\MyGA\Data', OutputFileNameC, 'W', 32767); 
	WrittenBars:=0; vLine:='';
	for i in StartRec..EndRec loop
		--dbms_output.put_line('WriteFile_Current:   i-StartRec='||to_char(i-StartRec,'999999'));
		if i<1 then
			vDataSrc:=IIf(pDelta, hstD(Hnrec+i), hst(Hnrec+i)); vDateSrc:=hndt(Hnrec+i);
		else
			vDataSrc:=IIf(pDelta, curD(i), cur(i)); vDateSrc:=cndt(i);
		end if;
		if ((i-StartRec)<nPeriods) then
			vLine:=vLine||' '||vDataSrc;
		else
			utl_file.put_line(OutputFileC,vLine); --dbms_output.put_line('Current - vLine='||vLine);
			vLine:=substr(vLine,instr(vLine,' ',1,2),length(vLine)-(instr(vLine,' ',1,2)-instr(vLine,' ',1,1)))||' '||vDataSrc;
			--utl_file.put_line(OutputFileC,vDataSrc||' ('||to_char(vDateSrc,'DD-MON-YYYY HH24:MI')||')');
			utl_file.put_line(OutputFileC,vDataSrc);
		end if;
	end loop;
	utl_file.fclose(OutputFileC);	
end;
procedure WriteFile_Predictor(FileNameRoot varchar2, pDelta boolean, nPeriods number, TopN number, BarsToWrite_Train number, BarsToWrite_Test number) is
	OutputFilePTest utl_file.file_type;  -- Predictor Data File
	OutputFilePTrain utl_file.file_type;  -- Predictor Data File
	vLine_Train varchar2(10000); vLine_Test varchar2(10000); 
	WrittenBars_Train number; WrittenBars_Test number;
begin
	OutputFilePTrain := utl_file.fopen ('C:\Users\gcaglion\Documents\MyGA\Data', FileNameRoot||'_Train.txt', 'W', 32767); 
	OutputFilePTest  := utl_file.fopen ('C:\Users\gcaglion\Documents\MyGA\Data', FileNameRoot||'_Test.txt', 'W', 32767);
	WrittenBars_Train:=0; WrittenBars_Test:=0; vLine_Train:=''; vLine_Test:='';
	for i in 1..Hnrec loop
		if hndt(i)>=BestPredictorStart(TopN) then
			if WrittenBars_Train<(BarsToWrite_Train+BarsToWrite_Test+nPeriods) then
				WrittenBars_Train:=WrittenBars_Train+1;
				if (WrittenBars_Train<=nPeriods) then
					vLine_Train:=vLine_Train||' '||IIf(pDelta, hstD(i-nPeriods), hst(i-nPeriods)); --dbms_output.put_line('i<nPeriods; vLine_Train='||vLine_Train);
				else
					utl_file.put_line(OutputFilePTrain,vLine_Train); --dbms_output.put_line('BestSRho - vLine_Train='||vLine_Train);
					vLine_Train:=substr(vLine_Train,instr(vLine_Train,' ',1,2),length(vLine_Train)-(instr(vLine_Train,' ',1,2)-instr(vLine_Train,' ',1,1)))||' '||IIf(pDelta, hstD(i-nPeriods), hst(i-nPeriods));
					utl_file.put_line(OutputFilePTrain,IIf(pDelta, hstD(i-nPeriods), hst(i-nPeriods)));	--||' ('||to_char(hndt(i-nPeriods),'DD-MON-YYYY HH24:MI')||')');
				end if;
			else
				if WrittenBars_Test<(BarsToWrite_Test+nPeriods) then
					WrittenBars_Test:=WrittenBars_Test+1;
					if (WrittenBars_Test<=nPeriods) then
						vLine_Test:=vLine_Test||' '||IIf(pDelta, hstD(i-nPeriods-BarsToWrite_Test+2), hst(i-nPeriods-BarsToWrite_Test+2)); --dbms_output.put_line('i<nPeriods; vLine_Test='||vLine_Test);
					else
						utl_file.put_line(OutputFilePTest,vLine_Test); --dbms_output.put_line('BestSRho - vLine_Test='||vLine_Test);
						vLine_Test:=substr(vLine_Test,instr(vLine_Test,' ',1,2),length(vLine_Test)-(instr(vLine_Test,' ',1,2)-instr(vLine_Test,' ',1,1)))||' '||IIf(pDelta, hstD(i-nPeriods-BarsToWrite_Test+2), hst(i-nPeriods-BarsToWrite_Test+2));
						utl_file.put_line(OutputFilePTest,IIf(pDelta, hstD(i-nPeriods-BarsToWrite_Test+2), hst(i-nPeriods-BarsToWrite_Test+2)));	--||' ('||to_char(hndt(i-nPeriods-BarsToWrite_Test+2),'DD-MON-YYYY HH24:MI')||')');
					end if;
				end if;
			end if;
		end if;
	end loop;
	utl_file.fclose(OutputFilePTrain);	
	utl_file.fclose(OutputFilePTest);	
end;

procedure WriteFiles(CSymbol varchar2, pDelta boolean, CToDate varchar2, TotalBars number, OOSBars number, HSymbol varchar2, TimeFrame varchar2, isFilled boolean, Measure varchar2, OutputType varchar2, nPeriods number) is
	--  Measure   can be ['K' (KTau), 'S' (SRho), 'G' (Gini), 'W' (WeakC), 'ALL' (All 4)]
	-- OutputType can be ['OPEN','HIGH','LOW','CLOSE']
	type rc is ref cursor;
	c1 rc;
	--HToDate varchar2(15) := CFromDate;
	MinLength number:=3;
	BestStart timestamp;
	SourceView varchar2(100);
	l number; f number; kaz number;
	
	function PickBestPredictor(pMeasure varchar2) return dbms_sql.date_table is
		bps dbms_sql.date_table;
		np number :=1;
	begin
		-- == Pick best Predictor DataSets
		SourceView:='VConcordance_'||HSymbol||'_'||TimeFrame||'_'||pMeasure;
		open c1 for 'select PredictorStart from '||SourceView||' where rownum<=10';
		loop
			fetch c1 into bps(np);
			exit when c1%NOTFOUND;
			--dbms_output.put_line('BestPredictorStart('||np||')='||bps(np));
			np:=np+1;
		end loop;
		np:=np-1;
		close c1;
		return bps;
		
	end PickBestPredictor;
begin
	-- == Load History and Current Data
	Load_AllData(CToDate, TotalBars, CSymbol, HSymbol, TimeFrame, isFilled, OutputType);
	--dbms_output.put_line('Hnrec='||Hnrec||' ; Cnrec='||Cnrec);
	
	-- == Write Output File - Current - InSample
	WriteFile_Current(CSymbol||'_'||TimeFrame||'_'||CToDate||'_Current_Train.txt', pDelta, Cnrec-OOSBars-TotalBars-NPeriods+1, Cnrec-OOSBars, nPeriods); 
	-- == Write Output File - Current - OutOfSample
	--dbms_output.put_line('Calling WriteFile_Current with:     1 - '||to_char(Cnrec-OOSLen,'9999990'));
	WriteFile_Current(CSymbol||'_'||TimeFrame||'_'||CToDate||'_Current_Test.txt', pDelta, Cnrec-OOSBars-nPeriods+1, Cnrec, nPeriods); 
	
	if (Measure='ALL') then
		BestPredictorStart := PickBestPredictor('S');
		for f in 1..Max_Predictors loop
			WriteFile_Predictor(CSymbol||'_'||TimeFrame||'_'||CToDate||'_'||HSymbol||'_'||'S'||'_'||to_char(BestPredictorStart(f),'YYYY-MM-DD-HH24MI')||'_Top'||trim(to_char(f,'09')), pDelta, nPeriods, f, TotalBars-OOSBars, OOSBars);
		end loop;
		BestPredictorStart:=PickBestPredictor('K');
		for f in 1..Max_Predictors loop
			WriteFile_Predictor(CSymbol||'_'||TimeFrame||'_'||CToDate||'_'||HSymbol||'_'||'K'||'_'||to_char(BestPredictorStart(f),'YYYY-MM-DD-HH24MI')||'_Top'||trim(to_char(f,'09')), pDelta, nPeriods, f, TotalBars-OOSBars, OOSBars);
		end loop;
		BestPredictorStart:=PickBestPredictor('G');
		for f in 1..Max_Predictors loop
			WriteFile_Predictor(CSymbol||'_'||TimeFrame||'_'||CToDate||'_'||HSymbol||'_'||'G'||'_'||to_char(BestPredictorStart(f),'YYYY-MM-DD-HH24MI')||'_Top'||trim(to_char(f,'09')), pDelta, nPeriods, f, TotalBars-OOSBars, OOSBars);
		end loop;
		BestPredictorStart:=PickBestPredictor('W');
		for f in 1..Max_Predictors loop
			WriteFile_Predictor(CSymbol||'_'||TimeFrame||'_'||CToDate||'_'||HSymbol||'_'||'W'||'_'||to_char(BestPredictorStart(f),'YYYY-MM-DD-HH24MI')||'_Top'||trim(to_char(f,'09')), pDelta, nPeriods, f, TotalBars-OOSBars, OOSBars);
		end loop;
	else
		BestPredictorStart:=PickBestPredictor(Measure);
		for f in 1..Max_Predictors loop
			WriteFile_Predictor(CSymbol||'_'||TimeFrame||'_'||CToDate||'_'||HSymbol||'_'||Measure||'_'||to_char(BestPredictorStart(f),'YYYY-MM-DD-HH24MI')||'_Top'||trim(to_char(f,'09')), pDelta, nPeriods, f, TotalBars-OOSBars, OOSBars);
		end loop;
	end if;
end WriteFiles;


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

function Load_Hst (HToDate varchar2, HSymbol varchar2, TimeFrame varchar2, isFilled boolean, OutputType varchar2) return number is
	cH rc;
	ndt date;
	Hnrec number:=0;
begin
	open cH for 'select NewDateTime,'||OutputType||' from History.'||HSymbol||'_'||TimeFrame||IIf(isFilled,'_FILLED','')||' where NewDateTime <=
						to_date('||chr(39)||HToDate  ||chr(39)||',''YYYY-MM-DD-HH24MI'') order by 1 desc';
	loop
		Hnrec:=Hnrec+1;
		fetch cH into hndt(Hnrec), hst(Hnrec);	-- Carico TUTTI i valori di H
		if cH%NOTFOUND then
			Hnrec:=Hnrec-1;
			--dbms_output.put_line('Load_Hst  : Hnrec='||Hnrec||' ; hndt(Hnrec)='||hndt(Hnrec)||' ; hst(Hnrec)='||hst(Hnrec));
			return Hnrec;
		end if;
	end loop;
	close cH;	
end Load_Hst;

function Load_Cur (CToDate varchar2, TotalBars number, CSymbol varchar2, TimeFrame varchar2, isFilled boolean, OutputType varchar2) return number is
	cC rc;
	ndt date;
	Cnrec number :=0;
begin
	--dbms_output.put_line('Load_Cur  : select NewDateTime,'||OutputType||' from History.'||CSymbol||'_'||TimeFrame||IIf(isFilled,'_FILLED','')||' where NewDateTime between to_date('||chr(39)||CFromDate||'0000'||chr(39)||',''YYYY-MM-DD-HH24MI'') and to_date('||chr(39)||CToDate  ||'2359'||chr(39)||',''YYYY-MM-DD-HH24MI'') order by 1');
	open cC for 'select NewDateTime,'||OutputType||' from History.'||CSymbol||'_'||TimeFrame||IIf(isFilled,'_FILLED','')||' where NewDateTime <=
						to_date('||chr(39)||CToDate  ||chr(39)||',''YYYY-MM-DD-HH24MI'') order by 1 desc';
	loop
		Cnrec:=Cnrec+1;
		fetch cC into ndt, cur(Cnrec);	-- Carico TUTTI i valori di C
		if (cC%NOTFOUND or Cnrec>TotalBars) then
			Cnrec:=Cnrec-1;
			--dbms_output.put_line('Load_Cur  : Cnrec='||Cnrec||' ; ndt='||ndt||' ; cur(Cnrec)='||cur(Cnrec));
			return Cnrec;
		end if;
	end loop;
	close cC;	
end Load_Cur;

procedure Load_AllData (CToDate varchar2, TotalBars number, CSymbol varchar2, HSymbol varchar2, TimeFrame varchar2, isFilled boolean, OutputType varchar2) is
	cC rc; cH rc;
	ndt_c date; vValue_c number; vValued_c number;
	ndt_h date; vValue_h number; vValued_h number;
	nrec number:=0;
	AllBarsH number;
begin
	dbms_output.put_line('stmt= '||'select count(*) from History.'||HSymbol||'_'||TimeFrame||IIf(isFilled,'_FILLED','')||' where NewDateTime <= to_date('||chr(39)||CToDate  ||chr(39)||',''YYYY-MM-DD-HH24MI'')');
	execute immediate 'select count(*) from History.'||HSymbol||'_'||TimeFrame||IIf(isFilled,'_FILLED','')||' where NewDateTime <= to_date('||chr(39)||CToDate  ||chr(39)||',''YYYY-MM-DD-HH24MI'')' into AllBarsH;
	Cnrec:=0; Hnrec:=0;
	dbms_output.put_line('AllBarsH='||AllBarsH||' ; TotalBars='||TotalBars);
	--dbms_output.put_line('cC: '||'select NewDateTime,'||OutputType||' from History.'||CSymbol||'_'||TimeFrame||IIf(isFilled,'_FILLED','')||' where NewDateTime <= to_date('||chr(39)||CToDate  ||chr(39)||',''YYYY-MM-DD-HH24MI'') order by 1');
	--dbms_output.put_line('cH: '||'select NewDateTime,'||OutputType||' from History.'||HSymbol||'_'||TimeFrame||IIf(isFilled,'_FILLED','')||' where NewDateTime <= to_date('||chr(39)||CToDate  ||chr(39)||',''YYYY-MM-DD-HH24MI'') order by 1');
	--open cC for 'select NewDateTime,'||OutputType||' from History.'||CSymbol||'_'||TimeFrame||IIf(isFilled,'_FILLED','')||' where NewDateTime <= to_date('||chr(39)||CToDate  ||chr(39)||',''YYYY-MM-DD-HH24MI'') order by 1';
	--open cH for 'select NewDateTime,'||OutputType||' from History.'||HSymbol||'_'||TimeFrame||IIf(isFilled,'_FILLED','')||' where NewDateTime <= to_date('||chr(39)||CToDate  ||chr(39)||',''YYYY-MM-DD-HH24MI'') order by 1';
	open cC for 'select NewDateTime,'||OutputType||', '||OutputType||'-lag('||OutputType||') over (order by NewDateTime) from History.'||CSymbol||'_'||TimeFrame||IIf(isFilled,'_FILLED','')||' where NewDateTime <= to_date('||chr(39)||CToDate  ||chr(39)||',''YYYY-MM-DD-HH24MI'') order by 1';
	open cH for 'select NewDateTime,'||OutputType||', '||OutputType||'-lag('||OutputType||') over (order by NewDateTime) from History.'||HSymbol||'_'||TimeFrame||IIf(isFilled,'_FILLED','')||' where NewDateTime <= to_date('||chr(39)||CToDate  ||chr(39)||',''YYYY-MM-DD-HH24MI'') order by 1';
	loop
		fetch cC into ndt_c, vValue_c, vValued_c;	fetch cH into ndt_h, vValue_h, vValued_h;
		--fetch cC into ndt_c, vValue_c;	fetch cH into ndt_h, vValue_h;
		nrec:=nrec+1; 
		if (cH%NOTFOUND) then
			--dbms_output.put_line('cH EOF! nrec='||nrec);
			return;
		end if;
		if (cC%NOTFOUND) then
			--dbms_output.put_line('cC EOF! nrec='||nrec);
			return;
		end if;
		if nrec<=(AllBarsH-TotalBars) then
			Hnrec:=Hnrec+1;
			hndt(Hnrec):=ndt_h;
			hst(Hnrec):=vValue_h;
			hstD(Hnrec):=vValued_h;
		else
			Cnrec:=Cnrec+1;
			if Cnrec=1 then 
				dbms_output.put_line('Cnrec=1 ; nrec='||nrec||' ; NewDateTime='||to_char(ndt_c,'YYYY-MM-DD-HH24MI'));
			end if;
			cndt(Cnrec):=ndt_c;
			cur(Cnrec):=vValue_c;
			curD(Cnrec):=vValued_c;
		end if;
	end loop;
	close cC; close cH;
end Load_AllData;

procedure Calc (
				CSymbol varchar2, 
				pDelta boolean, 
				CToDate varchar2, 
				TotalBars number, 
				HSymbol varchar2, 
				TimeFrame varchar2, 
				isFilled boolean, 
				OutputType varchar2) is
	vTF number;
	rcur dbms_sql.number_table;
	rhst dbms_sql.number_table;
	vSRho number; vKTau number; vGini number; vWeakC number;
	Knumer number:=0; Snumer number:=0; Wnumer number:=0;
	GSum number; GSumR number; gAvg number; GSumA number; GAvgA number;
	h number; l number; 

--	rx dbms_sql.number_table; ry dbms_sql.number_table;
	instmt varchar2(10000);
	CFromDate date;	-- Mi serve solo per la insert
	
begin
	
	--Cnrec := Load_Cur (CToDate, TotalBars, CSymbol, TimeFrame, isFilled, OutputType);
	--Hnrec := Load_Hst (HToDate, TotalBars, HSymbol, TimeFrame, isFilled, OutputType);
	--execute immediate 'truncate table TConcordance';
	Load_AllData(CToDate, TotalBars, CSymbol, HSymbol, TimeFrame, isFilled, OutputType);
	dbms_output.put_line('Calc: Hnrec='||Hnrec||' ; Cnrec='||Cnrec);

	for h in 1..Hnrec-Cnrec-1 loop
	--for h in 1..100 loop
		--ry(1):=1; ry(2):=7; ry(3):=4.5; ry(4):=3; ry(5):=6; ry(6):=2; ry(7):=4.5;
		--for l in 2..MaxSearchLen loop
		--for l in Cnrec..Cnrec loop
		for l in 60..Cnrec loop
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
			
			Concordance.HistoryLength:=l;	-- Mi serve per WriteFiles
			-- == Populate TConcordance ==
			--dbms_output.put_line('h='||h||'; l='||l||'; vSRho='||vSRho||' ; vKTau='||vKTau||' ; vWeakC='||vWeakC);
/*
			if    TimeFrame='M1' then
				CFromDate:=to_date(CToDate,'YYYY-MM-DD-HH24MI')-TotalBars/1440;
			elsif TimeFrame='M5' then
				CFromDate:=to_date(CToDate,'YYYY-MM-DD-HH24MI')-TotalBars/288;
			elsif TimeFrame='M15' then
				CFromDate:=to_date(CToDate,'YYYY-MM-DD-HH24MI')-TotalBars/96;
			elsif TimeFrame='M30' then
				CFromDate:=to_date(CToDate,'YYYY-MM-DD-HH24MI')-TotalBars/48;
			elsif TimeFrame='H1' then
				CFromDate:=to_date(CToDate,'YYYY-MM-DD-HH24MI')-TotalBars/24;
			elsif TimeFrame='H4' then
				CFromDate:=to_date(CToDate,'YYYY-MM-DD-HH24MI')-TotalBars/6;
			elsif TimeFrame='D1' then
				CFromDate:=to_date(CToDate,'YYYY-MM-DD-HH24MI')-TotalBars/1;
			end if;
*/
			instmt:='insert into TConcordance(CurrentData, CurrentStart, PredictorData, TimeFrame, OutputType, PredictorStart, PatternLength, PatternShift, KTau, SRho, Gini, WeakC) values ('||chr(39)||CSymbol||chr(39)||', :d1 ,'||chr(39)||HSymbol||chr(39)||','||chr(39)||TimeFrame||chr(39)||','||chr(39)||OutputType||chr(39)||', to_date('||chr(39)||to_char(hndt(h),'YYYY-MM-DD-HH24MI')||chr(39)||','||chr(39)||'YYYY-MM-DD-HH24MI'||chr(39)||'), '||l||', '||h||', '||vKTau||', '||vSRho||', '||vGini||', '||vWeakC||')';
			--dbms_output.put_line(instmt);
			--execute immediate instmt using CFromDate;	
			execute immediate instmt using cndt(1);	
		end loop;
	end loop;
	commit;

	dbms_output.put_line('CFromDate='||to_char(cndt(1),'YYYY-MM-DD-HH24MI'));
	dbms_output.put_line('CToDate=  '||CToDate);

	-- == Write Output files
	--WriteFiles (CSymbol, CFromDate, CToDate, HSymbol, TimeFrame, isFilled, OutputType, nPeriods);
	-- == Write Chart files
	--Chart (CSymbol, CFromDate, HSymbol, TimeFrame, isFilled, OutputType);
end Calc;

end Concordance;
/
show errors;

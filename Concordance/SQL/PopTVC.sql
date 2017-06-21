drop type TVC_Tab;
drop type TVC_Obj;
create or replace 	type TVC_Obj is object(	CurrentData		varchar2(6), TimeFrame		varchar2(4), PredictorData	varchar2(6), CurrentStart	date, PatternLength number, NewDateTime		date, CurrentBaseH	number, CurrentExtraH	number, PredictorBaseH	number, PredictorExtraH	number, CurrentBaseL	number, CurrentExtraL	number, PredictorBaseL	number, PredictorExtraL	number);
/
show errors;
create or replace type TVC_tab is table of TVC_obj;
/
show errors;

--create or replace procedure PopulateTVC(tname varchar2, tf varchar2, PredictionLength number) as
create or replace function TVC(PredictionLength number) return TVC_Tab is
	type rc is ref cursor;
	cBPs rc; cHst rc;
	l_TVC_Tab TVC_Tab := TVC_Tab();
	type T_CurrentData 		is table of varchar2(6) index by binary_integer;	TVC_CurrentData T_CurrentData;
	type T_TimeFrame 		is table of varchar2(4) index by binary_integer;	TVC_TimeFrame T_TimeFrame;
	type T_PredictorData 	is table of varchar2(6) index by binary_integer;	TVC_PredictorData T_PredictorData;
	type T_CurrentStart 	is table of date index by binary_integer;			TVC_CurrentStart T_CurrentStart;
	type T_PatternLength	is table of number index by binary_integer;			TVC_PatternLength T_PatternLength;
	type T_NewDateTime 		is table of date index by binary_integer;			TVC_NewDateTime T_NewDateTime;
	type T_CurrentBaseH 	is table of number index by binary_integer;			TVC_CurrentBaseH T_CurrentBaseH;
	type T_CurrentExtraH 	is table of number index by binary_integer;			TVC_CurrentExtraH T_CurrentExtraH;
	type T_PredictorBaseH 	is table of number index by binary_integer;			TVC_PredictorBaseH T_PredictorBaseH;
	type T_PredictorExtraH	is table of number index by binary_integer;			TVC_PredictorExtraH T_PredictorExtraH;
	type T_CurrentBaseL 	is table of number index by binary_integer;			TVC_CurrentBaseL T_CurrentBaseL;
	type T_CurrentExtraL 	is table of number index by binary_integer;			TVC_CurrentExtraL T_CurrentExtraL;
	type T_PredictorBaseL 	is table of number index by binary_integer;			TVC_PredictorBaseL T_PredictorBaseL;
	type T_PredictorExtraL 	is table of number index by binary_integer;			TVC_PredictorExtraL T_PredictorExtraL;
	selBPs varchar2(1000);
	selHst varchar2(1000);
	vCurrentData varchar2(8); vTimeFrame varchar2(6); vCurrentStart date; vOutputType varchar2(6); vMaxSRho number; vPredictorData varchar2(8); vPatternLength number; vPredictorStart date;
	CTableName varchar2(24); PTableName varchar2(24);	-- Current and Predictor
	vNewDateTime date; vHigh number; vLow number;
	BaseRec number :=0;
	
begin
	selBPs:='select distinct t.CurrentData, t.TimeFrame, t.CurrentStart, t.OutputType, 
			  first_value(t.SRho)
			   over (partition by t.CurrentData, t.TimeFrame, t.CurrentStart, t.OutputType
				order by t.SRho desc) MaxSRho,
			  first_value(t.PredictorData)
			   over (partition by t.CurrentData, t.TimeFrame, t.CurrentStart, t.OutputType
				order by t.SRho desc) PredictorData,
			  first_value(t.PatternLength)
			   over (partition by t.CurrentData, t.TimeFrame, t.CurrentStart, t.OutputType
				order by t.SRho desc) PatternLength,
			  first_value(t.PredictorStart)
			   over (partition by t.CurrentData, t.TimeFrame, t.CurrentStart, t.OutputType
				order by t.SRho desc) PredictorStart
			 from TConcordance t
			 where t.SRho<1
			order by 1,2,3,4,6';
	
	
	open cBPs for selBPS;
	loop
		fetch cBPs into vCurrentData, vTimeFrame, vCurrentStart, vOutputType, vMaxSRho, vPredictorData, vPatternLength, vPredictorStart;
		if (cBPs%NOTFOUND) then 
			exit;
		end if;
		CTableName:='History.'||vCurrentData  ||'_'||vTimeFrame; --dbms_output.put_line('CTableName='||CTableName);
		pTableName:='History.'||vPredictorData||'_'||vTimeFrame; --dbms_output.put_line('pTableName='||pTableName);
		selHst:='select NewDateTime, High, Low from '||CTableName||' where NewDateTime>=:d2 order by NewDateTime'; --dbms_output.put_line('selHst='||selHst);
		open cHst for selHst using vCurrentStart;
		dbms_output.put_line('vPatternLength='||vPatternLength);
		for i in 1..vPatternLength loop											-- Current-Base
			--dbms_output.put_line('Current-Base i='||i);
			fetch cHst into vNewDateTime, vHigh, vLow;
			TVC_CurrentData(i):=vCurrentData;
			TVC_TimeFrame(i):=vTimeFrame;
			TVC_PredictorData(i):=vPredictorData;
			TVC_CurrentStart(i):=vCurrentStart;
			TVC_NewDateTime(i):=vNewDateTime;
			TVC_PatternLength(i):=vPatternLength;
			if vOutputType='High' then
				TVC_CurrentBaseH(i):=vHigh; TVC_CurrentBaseL(i):=NULL;
			else
				TVC_CurrentBaseH(i):=NULL;  TVC_CurrentBaseL(i):=vLow;
			end if;
			TVC_CurrentExtraH(i):=NULL;	  TVC_CurrentExtraL(i):=NULL;
			TVC_PredictorBaseH(i):=NULL; TVC_PredictorBaseL(i):=NULL;
			TVC_PredictorExtraH(i):=NULL; TVC_PredictorExtraL(i):=NULL;
		end loop;
		for i in vPatternLength+1..vPatternLength+PredictionLength loop			-- Current-Extra
			--dbms_output.put_line('Current-Extra i='||i);
			fetch cHst into vNewDateTime, vHigh, vLow;
			TVC_CurrentData(i):=vCurrentData;
			TVC_TimeFrame(i):=vTimeFrame;
			TVC_PredictorData(i):=vPredictorData;
			TVC_CurrentStart(i):=vCurrentStart;
			TVC_NewDateTime(i):=vNewDateTime;
			TVC_PatternLength(i):=vPatternLength;
			TVC_CurrentBaseH(i):=NULL;    TVC_CurrentBaseL(i):=NULL;
			if vOutputType='High' then
				TVC_CurrentExtraH(i):=vHigh; TVC_CurrentExtraL(i):=NULL;
			else
				TVC_CurrentExtraH(i):=NULL;  TVC_CurrentExtraL(i):=vLow;
			end if;			  
			TVC_PredictorBaseH(i):=NULL; TVC_PredictorBaseL(i):=NULL;
			TVC_PredictorExtraH(i):=NULL; TVC_PredictorExtraL(i):=NULL;
		end loop;
		close cHst;
		open cHst for selHst using vPredictorStart;
		for i in vPatternLength+PredictionLength+1..vPatternLength+PredictionLength+vPatternLength loop											-- Predictor-Base
			--dbms_output.put_line('Predictor-Base i='||i);
			fetch cHst into vNewDateTime, vHigh, vLow;
			TVC_CurrentData(i):=vCurrentData;
			TVC_TimeFrame(i):=vTimeFrame;
			TVC_PredictorData(i):=vPredictorData;
			TVC_CurrentStart(i):=vCurrentStart;
			TVC_NewDateTime(i):=vNewDateTime;
			TVC_PatternLength(i):=vPatternLength;
			TVC_CurrentBaseH(i):=NULL;    TVC_CurrentBaseL(i):=NULL;
			TVC_CurrentExtraH(i):=NULL;	  TVC_CurrentExtraL(i):=NULL;
			if vOutputType='High' then
				TVC_PredictorBaseH(i):=vHigh; TVC_PredictorBaseL(i):=NULL; 
			else
				TVC_PredictorBaseH(i):=NULL;  TVC_PredictorBaseL(i):=vLow;
			end if;			  			
			TVC_PredictorExtraH(i):=NULL; TVC_PredictorExtraL(i):=NULL;
		end loop;
		for i in vPatternLength+PredictionLength+vPatternLength+1..vPatternLength+PredictionLength+vPatternLength+PredictionLength loop			-- Predictor-Extra
			--dbms_output.put_line('Predictor-Extra i='||i);
			fetch cHst into vNewDateTime, vHigh, vLow;
			TVC_CurrentData(i):=vCurrentData;
			TVC_TimeFrame(i):=vTimeFrame;
			TVC_PredictorData(i):=vPredictorData;
			TVC_CurrentStart(i):=vCurrentStart;
			TVC_NewDateTime(i):=vNewDateTime;
			TVC_PatternLength(i):=vPatternLength;
			TVC_CurrentBaseH(i):=NULL;    TVC_CurrentBaseL(i):=NULL;
			TVC_CurrentExtraH(i):=NULL;	  TVC_CurrentExtraL(i):=NULL;
			TVC_PredictorBaseH(i):=NULL; TVC_PredictorBaseL(i):=NULL;
			if vOutputType='High' then
				TVC_PredictorExtraH(i):=vHigh; TVC_PredictorExtraL(i):=NULL; 
			else
				TVC_PredictorExtraH(i):=NULL;  TVC_PredictorExtraL(i):=vLow;
			end if;			  			
		end loop;
		close cHst;
		
		for i in 1..vPatternLength+PredictionLength+vPatternLength+PredictionLength loop
			--dbms_output.put_line('Adding line '||i);
			--dbms_output.put_line(TVC_CurrentData(i)||' | '||TVC_TimeFrame(i)||' | '||TVC_PredictorData(i)||' | '||TVC_CurrentStart(i)||' | '||TVC_NewDateTime(i)||' | '||TVC_CurrentBaseH(i)||' | '||TVC_CurrentBaseL(i)||' | '||TVC_PredictorBaseH(i)||' | '||TVC_PredictorBaseL(i)||' | '||TVC_CurrentExtraH(i)||' | '||TVC_CurrentExtraL(i)||' | '||TVC_PredictorExtraH(i)||' | '||TVC_PredictorExtraL(i));
			l_TVC_Tab.extend;
			l_TVC_Tab(BaseRec+i):=TVC_Obj(TVC_CurrentData(i), TVC_TimeFrame(i), TVC_PredictorData(i), TVC_CurrentStart(i), TVC_PatternLength(i), TVC_NewDateTime(i), TVC_CurrentBaseH(i), TVC_CurrentExtraH(i), TVC_PredictorBaseH(i), TVC_PredictorExtraH(i), TVC_CurrentBaseL(i), TVC_CurrentExtraL(i), TVC_PredictorBaseL(i), TVC_PredictorExtraL(i) );
			--l_TVC_Tab(i):=TVC_Obj(TVC_CurrentData(i), TVC_TimeFrame(i), TVC_PredictorData(i), TVC_CurrentStart(i), TVC_NewDateTime(i), TVC_CurrentBaseH(i), TVC_CurrentExtraH(i), null, null, TVC_CurrentBaseL(i), TVC_CurrentExtraL(i), null, null );
		end loop;
		BaseRec:=BaseRec+vPatternLength+PredictionLength+vPatternLength+PredictionLength;
	end loop;

	close cBPs;
	return l_TVC_Tab;
end;
/
show errors;

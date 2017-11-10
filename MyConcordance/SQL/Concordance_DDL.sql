create user ConcUser identified by ConcPwd default tablespace ConcData;
grant dba to ConcUser;
grant select any table to ConcUser;

drop table TConcordance;
create table TConcordance (
CurrentData varchar2(6),
CurrentStart date,
TimeFrame varchar2(3),
OutputType varchar2(5),
PredictorData varchar2(6),
PredictorStart date,
PatternLength number,	-- l
PatternShift number,	-- h
KTau number,
SRho number,
Gini number,
WeakC number
) tablespace ConcData storage (MINEXTENTS 2 initial 1024M next 1024M PCTINCREASE 0);
alter table TConcordance add constraint TConcordance_PK primary key (CurrentData, CurrentStart, TimeFrame, OutputType, PredictorData, PredictorStart, PatternLength) using index tablespace ConcIdx storage (initial 100M minextents 10 next 100M);
create index TConcordance_KTau on TConcordance(KTau) tablespace ConcIdx;
create index TConcordance_SRho on TConcordance(SRho) tablespace ConcIdx;

-- ====== VConcordance_* views are created from MyGA_New.xlsx!DDL ===

/*
create snapshot SNConcordanceS tablespace MyNNDat refresh start with sysdate next sysdate +1/24 as select PredictorStart from VConcordanceS where rownum<2;
create snapshot SNConcordanceK tablespace MyNNDat refresh start with sysdate next sysdate +1/24 as select PredictorStart from VConcordanceK where rownum<2;
create snapshot SNConcordanceG tablespace MyNNDat refresh start with sysdate next sysdate +1/24 as select PredictorStart from VConcordanceG where rownum<2;
create snapshot SNConcordanceW tablespace MyNNDat refresh start with sysdate next sysdate +1/24 as select PredictorStart from VConcordanceW where rownum<2;
*/

/*
create or replace view AllHistory as 
select 'CATTLE' 	Symbol, 'M1'  Timeframe, OrigDate, OrigTime, Open, High, Low, Close, Volume, NewDateTime from History.CATTLE_M1 union all
select 'CORN' 		Symbol, 'M1'  Timeframe, OrigDate, OrigTime, Open, High, Low, Close, Volume, NewDateTime from History.CORN_M1 union all
select 'FTSE' 		Symbol, 'M1'  Timeframe, OrigDate, OrigTime, Open, High, Low, Close, Volume, NewDateTime from History.FTSE_M1 union all
select 'HOIL' 		Symbol, 'M1'  Timeframe, OrigDate, OrigTime, Open, High, Low, Close, Volume, NewDateTime from History.HOIL_M1 union all
select 'NGAS' 		Symbol, 'M1'  Timeframe, OrigDate, OrigTime, Open, High, Low, Close, Volume, NewDateTime from History.NGAS_M1 union all
select 'OIL' 		Symbol, 'M1'  Timeframe, OrigDate, OrigTime, Open, High, Low, Close, Volume, NewDateTime from History.OIL_M1 union all
select 'PLATINUM' 	Symbol, 'M1'  Timeframe, OrigDate, OrigTime, Open, High, Low, Close, Volume, NewDateTime from History.PLATINUM_M1 union all
select 'RICE' 		Symbol, 'M1'  Timeframe, OrigDate, OrigTime, Open, High, Low, Close, Volume, NewDateTime from History.RICE_M1 union all
select 'SBO' 		Symbol, 'M1'  Timeframe, OrigDate, OrigTime, Open, High, Low, Close, Volume, NewDateTime from History.SBO_M1 union all
select 'SOYBEANS' 	Symbol, 'M1'  Timeframe, OrigDate, OrigTime, Open, High, Low, Close, Volume, NewDateTime from History.SOYBEANS_M1 union all
select 'SPX' 		Symbol, 'M1'  Timeframe, OrigDate, OrigTime, Open, High, Low, Close, Volume, NewDateTime from History.SPX_M1 union all
select 'SUGAR' 		Symbol, 'M1'  Timeframe, OrigDate, OrigTime, Open, High, Low, Close, Volume, NewDateTime from History.SUGAR_M1 union all
select 'AUDUSD' 	Symbol, 'M1'  Timeframe, OrigDate, OrigTime, Open, High, Low, Close, Volume, NewDateTime from History.AUDUSD_M1 union all
select 'GBPUSD' 	Symbol, 'M1'  Timeframe, OrigDate, OrigTime, Open, High, Low, Close, Volume, NewDateTime from History.GBPUSD_M1 union all
select 'EURUSD' 	Symbol, 'M1'  Timeframe, OrigDate, OrigTime, Open, High, Low, Close, Volume, NewDateTime from History.EURUSD_M1 union all
select 'NZDUSD' 	Symbol, 'M1'  Timeframe, OrigDate, OrigTime, Open, High, Low, Close, Volume, NewDateTime from History.NZDUSD_M1 union all
select 'USDJPY' 	Symbol, 'M1'  Timeframe, OrigDate, OrigTime, Open, High, Low, Close, Volume, NewDateTime from History.USDJPY_M1 union all
select 'US10YR' 	Symbol, 'M1'  Timeframe, OrigDate, OrigTime, Open, High, Low, Close, Volume, NewDateTime from History.US10YR_M1 union all
select 'WHEAT' 		Symbol, 'M1'  Timeframe, OrigDate, OrigTime, Open, High, Low, Close, Volume, NewDateTime from History.WHEAT_M1 union all
select 'XRB' 		Symbol, 'M1'  Timeframe, OrigDate, OrigTime, Open, High, Low, Close, Volume, NewDateTime from History.XRB_M1 union all
select 'CATTLE' 	Symbol, 'M5'  Timeframe, OrigDate, OrigTime, Open, High, Low, Close, Volume, NewDateTime from History.CATTLE_M5 union all
select 'CORN' 		Symbol, 'M5'  Timeframe, OrigDate, OrigTime, Open, High, Low, Close, Volume, NewDateTime from History.CORN_M5 union all
select 'FTSE' 		Symbol, 'M5'  Timeframe, OrigDate, OrigTime, Open, High, Low, Close, Volume, NewDateTime from History.FTSE_M5 union all
select 'HOIL' 		Symbol, 'M5'  Timeframe, OrigDate, OrigTime, Open, High, Low, Close, Volume, NewDateTime from History.HOIL_M5 union all
select 'NGAS' 		Symbol, 'M5'  Timeframe, OrigDate, OrigTime, Open, High, Low, Close, Volume, NewDateTime from History.NGAS_M5 union all
select 'OIL' 		Symbol, 'M5'  Timeframe, OrigDate, OrigTime, Open, High, Low, Close, Volume, NewDateTime from History.OIL_M5 union all
select 'PLATINUM' 	Symbol, 'M5'  Timeframe, OrigDate, OrigTime, Open, High, Low, Close, Volume, NewDateTime from History.PLATINUM_M5 union all
select 'RICE' 		Symbol, 'M5'  Timeframe, OrigDate, OrigTime, Open, High, Low, Close, Volume, NewDateTime from History.RICE_M5 union all
select 'SBO' 		Symbol, 'M5'  Timeframe, OrigDate, OrigTime, Open, High, Low, Close, Volume, NewDateTime from History.SBO_M5 union all
select 'SOYBEANS' 	Symbol, 'M5'  Timeframe, OrigDate, OrigTime, Open, High, Low, Close, Volume, NewDateTime from History.SOYBEANS_M5 union all
select 'SPX' 		Symbol, 'M5'  Timeframe, OrigDate, OrigTime, Open, High, Low, Close, Volume, NewDateTime from History.SPX_M5 union all
select 'SUGAR' 		Symbol, 'M5'  Timeframe, OrigDate, OrigTime, Open, High, Low, Close, Volume, NewDateTime from History.SUGAR_M5 union all
select 'AUDUSD' 	Symbol, 'M5'  Timeframe, OrigDate, OrigTime, Open, High, Low, Close, Volume, NewDateTime from History.AUDUSD_M5 union all
select 'GBPUSD' 	Symbol, 'M5'  Timeframe, OrigDate, OrigTime, Open, High, Low, Close, Volume, NewDateTime from History.GBPUSD_M5 union all
select 'EURUSD' 	Symbol, 'M5'  Timeframe, OrigDate, OrigTime, Open, High, Low, Close, Volume, NewDateTime from History.EURUSD_M5 union all
select 'NZDUSD' 	Symbol, 'M5'  Timeframe, OrigDate, OrigTime, Open, High, Low, Close, Volume, NewDateTime from History.NZDUSD_M5 union all
select 'USDJPY' 	Symbol, 'M5'  Timeframe, OrigDate, OrigTime, Open, High, Low, Close, Volume, NewDateTime from History.USDJPY_M5 union all
select 'US10YR' 	Symbol, 'M5'  Timeframe, OrigDate, OrigTime, Open, High, Low, Close, Volume, NewDateTime from History.US10YR_M5 union all
select 'WHEAT' 		Symbol, 'M5'  Timeframe, OrigDate, OrigTime, Open, High, Low, Close, Volume, NewDateTime from History.WHEAT_M5 union all
select 'XRB' 		Symbol, 'M5'  Timeframe, OrigDate, OrigTime, Open, High, Low, Close, Volume, NewDateTime from History.XRB_M5 union all
select 'CATTLE' 	Symbol, 'M15'  Timeframe, OrigDate, OrigTime, Open, High, Low, Close, Volume, NewDateTime from History.CATTLE_M15 union all
select 'CORN' 		Symbol, 'M15'  Timeframe, OrigDate, OrigTime, Open, High, Low, Close, Volume, NewDateTime from History.CORN_M15 union all
select 'FTSE' 		Symbol, 'M15'  Timeframe, OrigDate, OrigTime, Open, High, Low, Close, Volume, NewDateTime from History.FTSE_M15 union all
select 'HOIL' 		Symbol, 'M15'  Timeframe, OrigDate, OrigTime, Open, High, Low, Close, Volume, NewDateTime from History.HOIL_M15 union all
select 'NGAS' 		Symbol, 'M15'  Timeframe, OrigDate, OrigTime, Open, High, Low, Close, Volume, NewDateTime from History.NGAS_M15 union all
select 'OIL' 		Symbol, 'M15'  Timeframe, OrigDate, OrigTime, Open, High, Low, Close, Volume, NewDateTime from History.OIL_M15 union all
select 'PLATINUM' 	Symbol, 'M15'  Timeframe, OrigDate, OrigTime, Open, High, Low, Close, Volume, NewDateTime from History.PLATINUM_M15 union all
select 'RICE' 		Symbol, 'M15'  Timeframe, OrigDate, OrigTime, Open, High, Low, Close, Volume, NewDateTime from History.RICE_M15 union all
select 'SBO' 		Symbol, 'M15'  Timeframe, OrigDate, OrigTime, Open, High, Low, Close, Volume, NewDateTime from History.SBO_M15 union all
select 'SOYBEANS' 	Symbol, 'M15'  Timeframe, OrigDate, OrigTime, Open, High, Low, Close, Volume, NewDateTime from History.SOYBEANS_M15 union all
select 'SPX' 		Symbol, 'M15'  Timeframe, OrigDate, OrigTime, Open, High, Low, Close, Volume, NewDateTime from History.SPX_M15 union all
select 'SUGAR' 		Symbol, 'M15'  Timeframe, OrigDate, OrigTime, Open, High, Low, Close, Volume, NewDateTime from History.SUGAR_M15 union all
select 'AUDUSD' 	Symbol, 'M15'  Timeframe, OrigDate, OrigTime, Open, High, Low, Close, Volume, NewDateTime from History.AUDUSD_M15 union all
select 'GBPUSD' 	Symbol, 'M15'  Timeframe, OrigDate, OrigTime, Open, High, Low, Close, Volume, NewDateTime from History.GBPUSD_M15 union all
select 'EURUSD' 	Symbol, 'M15'  Timeframe, OrigDate, OrigTime, Open, High, Low, Close, Volume, NewDateTime from History.EURUSD_M15 union all
select 'NZDUSD' 	Symbol, 'M15'  Timeframe, OrigDate, OrigTime, Open, High, Low, Close, Volume, NewDateTime from History.NZDUSD_M15 union all
select 'USDJPY' 	Symbol, 'M15'  Timeframe, OrigDate, OrigTime, Open, High, Low, Close, Volume, NewDateTime from History.USDJPY_M15 union all
select 'US10YR' 	Symbol, 'M15'  Timeframe, OrigDate, OrigTime, Open, High, Low, Close, Volume, NewDateTime from History.US10YR_M15 union all
select 'WHEAT' 		Symbol, 'M15'  Timeframe, OrigDate, OrigTime, Open, High, Low, Close, Volume, NewDateTime from History.WHEAT_M15 union all
select 'XRB' 		Symbol, 'M15'  Timeframe, OrigDate, OrigTime, Open, High, Low, Close, Volume, NewDateTime from History.XRB_M15 union all
select 'CATTLE' 	Symbol, 'M30'  Timeframe, OrigDate, OrigTime, Open, High, Low, Close, Volume, NewDateTime from History.CATTLE_M30 union all
select 'CORN' 		Symbol, 'M30'  Timeframe, OrigDate, OrigTime, Open, High, Low, Close, Volume, NewDateTime from History.CORN_M30 union all
select 'FTSE' 		Symbol, 'M30'  Timeframe, OrigDate, OrigTime, Open, High, Low, Close, Volume, NewDateTime from History.FTSE_M30 union all
select 'HOIL' 		Symbol, 'M30'  Timeframe, OrigDate, OrigTime, Open, High, Low, Close, Volume, NewDateTime from History.HOIL_M30 union all
select 'NGAS' 		Symbol, 'M30'  Timeframe, OrigDate, OrigTime, Open, High, Low, Close, Volume, NewDateTime from History.NGAS_M30 union all
select 'OIL' 		Symbol, 'M30'  Timeframe, OrigDate, OrigTime, Open, High, Low, Close, Volume, NewDateTime from History.OIL_M30 union all
select 'PLATINUM' 	Symbol, 'M30'  Timeframe, OrigDate, OrigTime, Open, High, Low, Close, Volume, NewDateTime from History.PLATINUM_M30 union all
select 'RICE' 		Symbol, 'M30'  Timeframe, OrigDate, OrigTime, Open, High, Low, Close, Volume, NewDateTime from History.RICE_M30 union all
select 'SBO' 		Symbol, 'M30'  Timeframe, OrigDate, OrigTime, Open, High, Low, Close, Volume, NewDateTime from History.SBO_M30 union all
select 'SOYBEANS' 	Symbol, 'M30'  Timeframe, OrigDate, OrigTime, Open, High, Low, Close, Volume, NewDateTime from History.SOYBEANS_M30 union all
select 'SPX' 		Symbol, 'M30'  Timeframe, OrigDate, OrigTime, Open, High, Low, Close, Volume, NewDateTime from History.SPX_M30 union all
select 'SUGAR' 		Symbol, 'M30'  Timeframe, OrigDate, OrigTime, Open, High, Low, Close, Volume, NewDateTime from History.SUGAR_M30 union all
select 'AUDUSD' 	Symbol, 'M30'  Timeframe, OrigDate, OrigTime, Open, High, Low, Close, Volume, NewDateTime from History.AUDUSD_M30 union all
select 'GBPUSD' 	Symbol, 'M30'  Timeframe, OrigDate, OrigTime, Open, High, Low, Close, Volume, NewDateTime from History.GBPUSD_M30 union all
select 'EURUSD' 	Symbol, 'M30'  Timeframe, OrigDate, OrigTime, Open, High, Low, Close, Volume, NewDateTime from History.EURUSD_M30 union all
select 'NZDUSD' 	Symbol, 'M30'  Timeframe, OrigDate, OrigTime, Open, High, Low, Close, Volume, NewDateTime from History.NZDUSD_M30 union all
select 'USDJPY' 	Symbol, 'M30'  Timeframe, OrigDate, OrigTime, Open, High, Low, Close, Volume, NewDateTime from History.USDJPY_M30 union all
select 'US10YR' 	Symbol, 'M30'  Timeframe, OrigDate, OrigTime, Open, High, Low, Close, Volume, NewDateTime from History.US10YR_M30 union all
select 'WHEAT' 		Symbol, 'M30'  Timeframe, OrigDate, OrigTime, Open, High, Low, Close, Volume, NewDateTime from History.WHEAT_M30 union all
select 'XRB' 		Symbol, 'M30'  Timeframe, OrigDate, OrigTime, Open, High, Low, Close, Volume, NewDateTime from History.XRB_M30 union all
select 'CATTLE' 	Symbol, 'H1'  Timeframe, OrigDate, OrigTime, Open, High, Low, Close, Volume, NewDateTime from History.CATTLE_H1 union all
select 'CORN' 		Symbol, 'H1'  Timeframe, OrigDate, OrigTime, Open, High, Low, Close, Volume, NewDateTime from History.CORN_H1 union all
select 'FTSE' 		Symbol, 'H1'  Timeframe, OrigDate, OrigTime, Open, High, Low, Close, Volume, NewDateTime from History.FTSE_H1 union all
select 'HOIL' 		Symbol, 'H1'  Timeframe, OrigDate, OrigTime, Open, High, Low, Close, Volume, NewDateTime from History.HOIL_H1 union all
select 'NGAS' 		Symbol, 'H1'  Timeframe, OrigDate, OrigTime, Open, High, Low, Close, Volume, NewDateTime from History.NGAS_H1 union all
select 'OIL' 		Symbol, 'H1'  Timeframe, OrigDate, OrigTime, Open, High, Low, Close, Volume, NewDateTime from History.OIL_H1 union all
select 'PLATINUM' 	Symbol, 'H1'  Timeframe, OrigDate, OrigTime, Open, High, Low, Close, Volume, NewDateTime from History.PLATINUM_H1 union all
select 'RICE' 		Symbol, 'H1'  Timeframe, OrigDate, OrigTime, Open, High, Low, Close, Volume, NewDateTime from History.RICE_H1 union all
select 'SBO' 		Symbol, 'H1'  Timeframe, OrigDate, OrigTime, Open, High, Low, Close, Volume, NewDateTime from History.SBO_H1 union all
select 'SOYBEANS' 	Symbol, 'H1'  Timeframe, OrigDate, OrigTime, Open, High, Low, Close, Volume, NewDateTime from History.SOYBEANS_H1 union all
select 'SPX' 		Symbol, 'H1'  Timeframe, OrigDate, OrigTime, Open, High, Low, Close, Volume, NewDateTime from History.SPX_H1 union all
select 'SUGAR' 		Symbol, 'H1'  Timeframe, OrigDate, OrigTime, Open, High, Low, Close, Volume, NewDateTime from History.SUGAR_H1 union all
select 'AUDUSD' 	Symbol, 'H1'  Timeframe, OrigDate, OrigTime, Open, High, Low, Close, Volume, NewDateTime from History.AUDUSD_H1 union all
select 'GBPUSD' 	Symbol, 'H1'  Timeframe, OrigDate, OrigTime, Open, High, Low, Close, Volume, NewDateTime from History.GBPUSD_H1 union all
select 'EURUSD' 	Symbol, 'H1'  Timeframe, OrigDate, OrigTime, Open, High, Low, Close, Volume, NewDateTime from History.EURUSD_H1 union all
select 'NZDUSD' 	Symbol, 'H1'  Timeframe, OrigDate, OrigTime, Open, High, Low, Close, Volume, NewDateTime from History.NZDUSD_H1 union all
select 'USDJPY' 	Symbol, 'H1'  Timeframe, OrigDate, OrigTime, Open, High, Low, Close, Volume, NewDateTime from History.USDJPY_H1 union all
select 'US10YR' 	Symbol, 'H1'  Timeframe, OrigDate, OrigTime, Open, High, Low, Close, Volume, NewDateTime from History.US10YR_H1 union all
select 'WHEAT' 		Symbol, 'H1'  Timeframe, OrigDate, OrigTime, Open, High, Low, Close, Volume, NewDateTime from History.WHEAT_H1 union all
select 'XRB' 		Symbol, 'H1'  Timeframe, OrigDate, OrigTime, Open, High, Low, Close, Volume, NewDateTime from History.XRB_H1 union all
select 'CATTLE' 	Symbol, 'H4'  Timeframe, OrigDate, OrigTime, Open, High, Low, Close, Volume, NewDateTime from History.CATTLE_H4 union all
select 'CORN' 		Symbol, 'H4'  Timeframe, OrigDate, OrigTime, Open, High, Low, Close, Volume, NewDateTime from History.CORN_H4 union all
select 'FTSE' 		Symbol, 'H4'  Timeframe, OrigDate, OrigTime, Open, High, Low, Close, Volume, NewDateTime from History.FTSE_H4 union all
select 'HOIL' 		Symbol, 'H4'  Timeframe, OrigDate, OrigTime, Open, High, Low, Close, Volume, NewDateTime from History.HOIL_H4 union all
select 'NGAS' 		Symbol, 'H4'  Timeframe, OrigDate, OrigTime, Open, High, Low, Close, Volume, NewDateTime from History.NGAS_H4 union all
select 'OIL' 		Symbol, 'H4'  Timeframe, OrigDate, OrigTime, Open, High, Low, Close, Volume, NewDateTime from History.OIL_H4 union all
select 'PLATINUM' 	Symbol, 'H4'  Timeframe, OrigDate, OrigTime, Open, High, Low, Close, Volume, NewDateTime from History.PLATINUM_H4 union all
select 'RICE' 		Symbol, 'H4'  Timeframe, OrigDate, OrigTime, Open, High, Low, Close, Volume, NewDateTime from History.RICE_H4 union all
select 'SBO' 		Symbol, 'H4'  Timeframe, OrigDate, OrigTime, Open, High, Low, Close, Volume, NewDateTime from History.SBO_H4 union all
select 'SOYBEANS' 	Symbol, 'H4'  Timeframe, OrigDate, OrigTime, Open, High, Low, Close, Volume, NewDateTime from History.SOYBEANS_H4 union all
select 'SPX' 		Symbol, 'H4'  Timeframe, OrigDate, OrigTime, Open, High, Low, Close, Volume, NewDateTime from History.SPX_H4 union all
select 'SUGAR' 		Symbol, 'H4'  Timeframe, OrigDate, OrigTime, Open, High, Low, Close, Volume, NewDateTime from History.SUGAR_H4 union all
select 'AUDUSD' 	Symbol, 'H4'  Timeframe, OrigDate, OrigTime, Open, High, Low, Close, Volume, NewDateTime from History.AUDUSD_H4 union all
select 'GBPUSD' 	Symbol, 'H4'  Timeframe, OrigDate, OrigTime, Open, High, Low, Close, Volume, NewDateTime from History.GBPUSD_H4 union all
select 'EURUSD' 	Symbol, 'H4'  Timeframe, OrigDate, OrigTime, Open, High, Low, Close, Volume, NewDateTime from History.EURUSD_H4 union all
select 'NZDUSD' 	Symbol, 'H4'  Timeframe, OrigDate, OrigTime, Open, High, Low, Close, Volume, NewDateTime from History.NZDUSD_H4 union all
select 'USDJPY' 	Symbol, 'H4'  Timeframe, OrigDate, OrigTime, Open, High, Low, Close, Volume, NewDateTime from History.USDJPY_H4 union all
select 'US10YR' 	Symbol, 'H4'  Timeframe, OrigDate, OrigTime, Open, High, Low, Close, Volume, NewDateTime from History.US10YR_H4 union all
select 'WHEAT' 		Symbol, 'H4'  Timeframe, OrigDate, OrigTime, Open, High, Low, Close, Volume, NewDateTime from History.WHEAT_H4 union all
select 'XRB' 		Symbol, 'H4'  Timeframe, OrigDate, OrigTime, Open, High, Low, Close, Volume, NewDateTime from History.XRB_H4 union all
select 'CATTLE' 	Symbol, 'D1'  Timeframe, OrigDate, OrigTime, Open, High, Low, Close, Volume, NewDateTime from History.CATTLE_D1 union all
select 'CORN' 		Symbol, 'D1'  Timeframe, OrigDate, OrigTime, Open, High, Low, Close, Volume, NewDateTime from History.CORN_D1 union all
select 'FTSE' 		Symbol, 'D1'  Timeframe, OrigDate, OrigTime, Open, High, Low, Close, Volume, NewDateTime from History.FTSE_D1 union all
select 'HOIL' 		Symbol, 'D1'  Timeframe, OrigDate, OrigTime, Open, High, Low, Close, Volume, NewDateTime from History.HOIL_D1 union all
select 'NGAS' 		Symbol, 'D1'  Timeframe, OrigDate, OrigTime, Open, High, Low, Close, Volume, NewDateTime from History.NGAS_D1 union all
select 'OIL' 		Symbol, 'D1'  Timeframe, OrigDate, OrigTime, Open, High, Low, Close, Volume, NewDateTime from History.OIL_D1 union all
select 'PLATINUM' 	Symbol, 'D1'  Timeframe, OrigDate, OrigTime, Open, High, Low, Close, Volume, NewDateTime from History.PLATINUM_D1 union all
select 'RICE' 		Symbol, 'D1'  Timeframe, OrigDate, OrigTime, Open, High, Low, Close, Volume, NewDateTime from History.RICE_D1 union all
select 'SBO' 		Symbol, 'D1'  Timeframe, OrigDate, OrigTime, Open, High, Low, Close, Volume, NewDateTime from History.SBO_D1 union all
select 'SOYBEANS' 	Symbol, 'D1'  Timeframe, OrigDate, OrigTime, Open, High, Low, Close, Volume, NewDateTime from History.SOYBEANS_D1 union all
select 'SPX' 		Symbol, 'D1'  Timeframe, OrigDate, OrigTime, Open, High, Low, Close, Volume, NewDateTime from History.SPX_D1 union all
select 'SUGAR' 		Symbol, 'D1'  Timeframe, OrigDate, OrigTime, Open, High, Low, Close, Volume, NewDateTime from History.SUGAR_D1 union all
select 'AUDUSD' 	Symbol, 'D1'  Timeframe, OrigDate, OrigTime, Open, High, Low, Close, Volume, NewDateTime from History.AUDUSD_D1 union all
select 'GBPUSD' 	Symbol, 'D1'  Timeframe, OrigDate, OrigTime, Open, High, Low, Close, Volume, NewDateTime from History.GBPUSD_D1 union all
select 'EURUSD' 	Symbol, 'D1'  Timeframe, OrigDate, OrigTime, Open, High, Low, Close, Volume, NewDateTime from History.EURUSD_D1 union all
select 'NZDUSD' 	Symbol, 'D1'  Timeframe, OrigDate, OrigTime, Open, High, Low, Close, Volume, NewDateTime from History.NZDUSD_D1 union all
select 'USDJPY' 	Symbol, 'D1'  Timeframe, OrigDate, OrigTime, Open, High, Low, Close, Volume, NewDateTime from History.USDJPY_D1 union all
select 'US10YR' 	Symbol, 'D1'  Timeframe, OrigDate, OrigTime, Open, High, Low, Close, Volume, NewDateTime from History.US10YR_D1 union all
select 'WHEAT' 		Symbol, 'D1'  Timeframe, OrigDate, OrigTime, Open, High, Low, Close, Volume, NewDateTime from History.WHEAT_D1 union all
select 'XRB' 		Symbol, 'D1'  Timeframe, OrigDate, OrigTime, Open, High, Low, Close, Volume, NewDateTime from History.XRB_D1 
;
*/

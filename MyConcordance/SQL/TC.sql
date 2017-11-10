connect GAUser/GAPwd
select CurrentData, Timeframe, PredictorData, CurrentStart, OutputType, PatternLength, count(*) from TConcordance
group by CurrentData, Timeframe, PredictorData, CurrentStart, OutputType, PatternLength 
order by 1,2,3,4,5,6
/
select count(*) from tconcordance
/

--create or replace view vBestPredictors as
select distinct t.CurrentData, t.TimeFrame, t.CurrentStart, t.OutputType, 
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
order by 1,2,3,4,6
/

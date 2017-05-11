select 
tp.ProcessId, tp.TesterStart, tp.Duration, tp.SimulationLen, tp.SimulationStart, tp.DoTraining, tp.DoRun,
dp.DatasetId, dp.HistoryLen, dp.SampleLen, dp.PredictionLen, dp.WiggleRoom, 
dp.DataSourceType, dp.DataSourceFileName, dp.Symbol, dp.TimeFrame, dp.IsFilled,
decode(dp.DataSourceType,0,'FXDB',1,'FILE',2,'METATRADER','UNKNOWN') "DataSource",
decode(dp.datasourcetype,1,'', decode(dp.bardata,0,'OPEN',1,'HIGH',2,'LOW',3,'CLOSE',4,'VOLUME',5,'OTHER','UNKNOWN')) "FXBarData",
decode(datatransformation,0,'DT_NONE',1,'DT_DELTA',2,'DT_DELTA',3,'DT_DELTALOG','UNKNOWN') "DataTransformation",
decode(ep.EngineType,0,'ENGINE_NN',1,'ENGINE_GA',2,'ENGINE_SVM',3,'ENGINE_SOM',4,'ENGINE_WNN',5,'ENGINE_XIE','UNKNOWN') "EngineType",
ep.LayersCount, ep.WNN_DecompLevel, ep.WNN_WaveletType,
et.LayerId, et.CoreId, et.DatasetId, et.ThreadId
from TesterParms tp, DataParms dp, EngineParms ep, EngineThreads et
where dp.ProcessId=tp.ProcessId
and   ep.ProcessId=tp.ProcessId
and   et.ProcessId=tp.ProcessId and et.DatasetId=dp.DatasetId
order by tp.ProcessId, dp.DatasetId;

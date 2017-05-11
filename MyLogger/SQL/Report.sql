select 
tp.ProcessId, tp.TesterStart, tp.Duration, tp.SimulationLen, tp.SimulationStart, tp.DoTraining, tp.DoRun,
dp.DatasetId, dp.HistoryLen, dp.SampleLen, dp.PredictionLen, dp.WiggleRoom, 
dp.DataSourceType, dp.DataSourceFileName, dp.Symbol, dp.TimeFrame, dp.IsFilled,
decode(dp.DataSourceType,0,'FXDB',1,'FILE',2,'METATRADER','UNKNOWN') "DataSource",
decode(dp.datasourcetype,1,'', decode(dp.bardata,0,'OPEN',1,'HIGH',2,'LOW',3,'CLOSE',4,'VOLUME',5,'OTHER','UNKNOWN')) "FXBarData",
decode(datatransformation,0,'DT_NONE',1,'DT_DELTA',2,'DT_DELTA',3,'DT_DELTALOG','UNKNOWN') "DataTransformation",
decode(ep.EngineType,0,'ENGINE_NN',1,'ENGINE_GA',2,'ENGINE_SVM',3,'ENGINE_SOM',4,'ENGINE_WNN',5,'ENGINE_XIE','UNKNOWN') "EngineType",
ep.LayersCount, ep.WNN_DecompLevel, ep.WNN_WaveletType,
et.LayerId, et.CoreId, et.ThreadId,
run.error, run.errorp, run.barwidth,
mse.MSE_T
from TesterParms tp, DataParms dp, EngineParms ep, EngineThreads et, MyLog_Run run, MyLog_MSE mse,
	CoreParms_NN cpNN, CoreParms_GA cpGA, CoreParms_SOM cpSOM, CoreParms_SVM cpSVM,
	CoreLogs_NN clNN, CoreLogs_GA clGA, CoreLogs_SOM clSOM, CoreLogs_SVM clSVM
where dp.ProcessId=tp.ProcessId
and   ep.ProcessId=tp.ProcessId
and   et.ProcessId=tp.ProcessId and et.DatasetId=dp.DatasetId
and   run.ProcessId(+)=et.ProcessId and run.ThreadId(+)=et.ThreadId and run.pos(+)=dp.HistoryLen
and   mse.ProcessId=et.ProcessId and mse.ThreadId=et.ThreadId 
and   (
		mse.Epoch=clNN.ActualEpochs-1 or
		mse.Epoch=clGA.ActualGenerations-1 or
		mse.Epoch=clSOM.ActualEpochs-1 or
		mse.Epoch=clSVM.ActualEpochs-1
    )
and   cpNN.ProcessId(+)=et.ProcessId and cpNN.ThreadId(+)=et.ThreadId
and   cpGA.ProcessId(+)=et.ProcessId and cpGA.ThreadId(+)=et.ThreadId
and   cpSOM.ProcessId(+)=et.ProcessId and cpSOM.ThreadId(+)=et.ThreadId
and   cpSVM.ProcessId(+)=et.ProcessId and cpSVM.ThreadId(+)=et.ThreadId
and   clNN.ProcessId(+)=et.ProcessId and clNN.ThreadId(+)=et.ThreadId
and   clGA.ProcessId(+)=et.ProcessId and clGA.ThreadId(+)=et.ThreadId
and   clSOM.ProcessId(+)=et.ProcessId and clSOM.ThreadId(+)=et.ThreadId
and   clSVM.ProcessId(+)=et.ProcessId and clSVM.ThreadId(+)=et.ThreadId
and tp.processid=74692
order by tp.ProcessId, dp.DatasetId;

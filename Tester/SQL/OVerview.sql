--explain plan for 
select tp.processid, et.testid, et.layerid, et.coreid,
decode(et.coretype,0,'CORE_NN',1,'CORE_GA',2,'CORE_SVM',3,'CORE_SOM','UNKNOWN') CoreType,
 et.datasetid, et.threadid,
run.error, run.barwidth, run.errorp,
--mse.mse_t, mse.mse_v,
dp.DatasetId, dp.HistoryLen, dp.SampleLen, dp.PredictionLen, dp.WiggleRoom,
dp.DataSourceType, dp.DataSourceFileName, dp.Symbol, dp.TimeFrame, dp.IsFilled,
decode(dp.DataSourceType,0,'FXDB',1,'FILE',2,'METATRADER','UNKNOWN') "DataSource",
decode(dp.datasourcetype,1,'', decode(dp.bardata,0,'OPEN',1,'HIGH',2,'LOW',3,'CLOSE',4,'VOLUME',5,'OTHER','UNKNOWN')) "FXBarData",
decode(dp.datatransformation,0,'DT_NONE',1,'DT_DELTA',2,'DT_DELTA',3,'DT_DELTALOG','UNKNOWN') "DataTransformation",
decode(ep.EngineType,0,'ENGINE_NN',1,'ENGINE_GA',2,'ENGINE_SVM',3,'ENGINE_SOM',4,'ENGINE_WNN',5,'ENGINE_XIE','UNKNOWN') "EngineType", ep.WNN_DecompLevel, ep.WNN_WaveletType,
cpSVM.C, cpSVM.Epsilon, decode(cpSVM.KernelType,0,'LINEAR',1,'POLY',2,'RBF',3,'TANH',4,'CUSTOM','UNKNOWN') "SVM_Kernel", cpSVM.RBFGamma,
cpNN.LevelsCount, cpNN.LevelRatios, cpNN.UseContext, decode(cpNN.BP_Algo,0,'BP_STD',1,'BP_QING',5,'BP_SCGD',6,'BP_QUICKPROP','UNKNOWN') "BPAlgo", decode(cpNN.TrainingProtocol,0,'TP_STOCHASTIC',1,'TP_BATCH',2,'TP_ONLINE','UNKNOWN') TrainingProtocol, cpNN.StopAtDivergence, cpNN.LearningRate, cpNN.LearningMomentum, decode(cpNN.ActivationFunction,1,'TANH',2,'EXP4','UNKNOWN'), cpNN.HCPbeta, cpNN.MU
from testerparms tp, engineparms ep, enginethreads et, dataparms dp,
coreparms_nn cpnn, coreparms_ga cpga, coreparms_svm cpsvm, coreparms_som cpsom,
CoreLogs_NN clNN, CoreLogs_GA clGA, CoreLogs_SOM clSOM, CoreLogs_SVM clSVM,
--MyLog_MSE mse, 
MyLog_Run run
where
    et.processid=tp.processid
and ep.processid=tp.processid
and dp.processid=tp.processid
and dp.datasetid=et.datasetid
and cpsvm.processid(+)=et.processid
and cpnn.processid(+) =et.processid
--and   mse.ProcessId=et.ProcessId and mse.ThreadId=et.ThreadId
--and   (
--           mse.Epoch=clNN.ActualEpochs-1 or
--           mse.Epoch=clGA.ActualGenerations-1 or
--           mse.Epoch=clSOM.ActualEpochs-1 or
--           mse.Epoch=clSVM.ActualEpochs-1
--    )
and   cpNN.ProcessId(+)=et.ProcessId and cpNN.LayerId(+)=et.LayerId and cpNN.CoreId(+)=et.CoreId
and   cpGA.ProcessId(+)=et.ProcessId and cpGA.LayerId(+)=et.LayerId and cpGA.CoreId(+)=et.CoreId
and   cpSOM.ProcessId(+)=et.ProcessId and cpSOM.LayerId(+)=et.LayerId and cpSOM.CoreId(+)=et.CoreId
and   cpSVM.ProcessId(+)=et.ProcessId and cpSVM.LayerId(+)=et.LayerId and cpSVM.CoreId(+)=et.CoreId
and   clNN.ProcessId(+)=et.ProcessId and clNN.ThreadId(+)=et.ThreadId
and   clGA.ProcessId(+)=et.ProcessId and clGA.ThreadId(+)=et.ThreadId
and   clSOM.ProcessId(+)=et.ProcessId and clSOM.ThreadId(+)=et.ThreadId
and   clSVM.ProcessId(+)=et.ProcessId and clSVM.ThreadId(+)=et.ThreadId
and run.processid=et.processid and run.threadid=et.threadid and run.pos=dp.HistoryLen
--and tp.processid in(99692, 97052)
and tp.processid=99692
order by tp.processid, et.testid, et.layerid, et.coreid, dp.datasetid;

--SELECT PLAN_TABLE_OUTPUT FROM TABLE(DBMS_XPLAN.DISPLAY(NULL));

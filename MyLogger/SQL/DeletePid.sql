undefine pid
set verify off
delete from testerparms where processid not in(&&pid);
delete from dataparms where processid not in(&&pid);
delete from engineparms_NN where processid not in(&&pid);
delete from engineparms_NN_internals where processid not in(&&pid);
delete from engineparms_dummy where processid not in(&&pid);
delete from engineparms_wNN where processid not in(&&pid);
delete from engineparms_ga where processid not in(&&pid);
delete from engineparms_som where processid not in(&&pid);
delete from mylog_run where processid not in(&&pid);
delete from mylog_mse where processid not in(&&pid);
delete from netimage_NN where processid not in(&&pid);
delete from netimage_wNN where processid not in(&&pid);
delete from netimage_ga where processid not in(&&pid);
delete from netimage_som where processid not in(&&pid);

define pid=85100
delete from COREIMAGE_NN where processid=&&pid;
delete from COREIMAGE_SOM where processid=&&pid;
delete from COREIMAGE_SVM where processid=&&pid;
delete from CORELOGS_GA where processid=&&pid;
delete from CORELOGS_NN where processid=&&pid;
delete from CORELOGS_NN_SCGD where processid=&&pid;
delete from CORELOGS_SOM where processid=&&pid;
delete from CORELOGS_SVM where processid=&&pid;
delete from COREPARMS_GA where processid=&&pid;
delete from COREPARMS_NN where processid=&&pid;
delete from COREPARMS_SOM where processid=&&pid;
delete from COREPARMS_SVM where processid=&&pid;
delete from DATAPARMS where processid=&&pid;
delete from MYLOG_MSE where processid=&&pid;
delete from MYLOG_RUN where processid=&&pid;
delete from ENGINETHREADS where processid=&&pid;
delete from ENGINEPARMS where processid=&&pid;
delete from TESTERPARMS where processid=&&pid;

delete from COREIMAGE_NN where processid in(select processid from(select processid, datasetid, count(threadid) from enginethreads having(count(threadid)<100) group by processid, datasetid));
delete from COREIMAGE_SOM where processid in(select processid from(select processid, datasetid, count(threadid) from enginethreads having(count(threadid)<100) group by processid, datasetid));
delete from COREIMAGE_SVM where processid in(select processid from(select processid, datasetid, count(threadid) from enginethreads having(count(threadid)<100) group by processid, datasetid));
delete from CORELOGS_GA where processid in(select processid from(select processid, datasetid, count(threadid) from enginethreads having(count(threadid)<100) group by processid, datasetid));
delete from CORELOGS_NN where processid in(select processid from(select processid, datasetid, count(threadid) from enginethreads having(count(threadid)<100) group by processid, datasetid));
delete from CORELOGS_NN_SCGD where processid in(select processid from(select processid, datasetid, count(threadid) from enginethreads having(count(threadid)<100) group by processid, datasetid));
delete from CORELOGS_SOM where processid in(select processid from(select processid, datasetid, count(threadid) from enginethreads having(count(threadid)<100) group by processid, datasetid));
delete from CORELOGS_SVM where processid in(select processid from(select processid, datasetid, count(threadid) from enginethreads having(count(threadid)<100) group by processid, datasetid));
delete from COREPARMS_GA where processid in(select processid from(select processid, datasetid, count(threadid) from enginethreads having(count(threadid)<100) group by processid, datasetid));
delete from COREPARMS_NN where processid in(select processid from(select processid, datasetid, count(threadid) from enginethreads having(count(threadid)<100) group by processid, datasetid));
delete from COREPARMS_SOM where processid in(select processid from(select processid, datasetid, count(threadid) from enginethreads having(count(threadid)<100) group by processid, datasetid));
delete from COREPARMS_SVM where processid in(select processid from(select processid, datasetid, count(threadid) from enginethreads having(count(threadid)<100) group by processid, datasetid));
delete from DATAPARMS where processid in(select processid from(select processid, datasetid, count(threadid) from enginethreads having(count(threadid)<100) group by processid, datasetid));
delete from MYLOG_MSE where processid in(select processid from(select processid, datasetid, count(threadid) from enginethreads having(count(threadid)<100) group by processid, datasetid));
delete from MYLOG_RUN where processid in(select processid from(select processid, datasetid, count(threadid) from enginethreads having(count(threadid)<100) group by processid, datasetid));
delete from ENGINETHREADS where processid in(select processid from(select processid, datasetid, count(threadid) from enginethreads having(count(threadid)<100) group by processid, datasetid));
delete from ENGINEPARMS where processid in(select processid from(select processid, datasetid, count(threadid) from enginethreads having(count(threadid)<100) group by processid, datasetid));
delete from TESTERPARMS where processid in(select processid from(select processid, datasetid, count(threadid) from enginethreads having(count(threadid)<100) group by processid, datasetid));
commit;

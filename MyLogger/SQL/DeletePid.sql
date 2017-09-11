set verify off
define pid=1092,80524,3944
delete from COREIMAGE_NN where processid in(&&pid);
delete from COREIMAGE_SOM where processid in(&&pid);
delete from COREIMAGE_SVM where processid in(&&pid);
delete from CORELOGS_GA where processid in(&&pid);
delete from CORELOGS_NN where processid in(&&pid);
delete from CORELOGS_NN_SCGD where processid in(&&pid);
delete from CORELOGS_SOM where processid in(&&pid);
delete from CORELOGS_SVM where processid in(&&pid);
delete from COREPARMS_GA where processid in(&&pid);
delete from COREPARMS_NN where processid in(&&pid);
delete from COREPARMS_SOM where processid in(&&pid);
delete from COREPARMS_SVM where processid in(&&pid);
delete from MYLOG_MSE where processid in(&&pid);
delete from MYLOG_RUN where processid in(&&pid);
delete from ENGINETHREADS where processid in(&&pid);
delete from DATAPARMS where processid in(&&pid);
delete from ENGINEPARMS where processid in(&&pid);
delete from CLIENTINFO where processid in(&&pid);
//commit;


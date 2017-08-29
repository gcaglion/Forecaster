set verify off
define pid=43988
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
delete from MYLOG_MSE where processid=&&pid;
delete from MYLOG_RUN where processid=&&pid;
delete from ENGINETHREADS where processid=&&pid;
delete from DATAPARMS where processid=&&pid;
delete from ENGINEPARMS where processid=&&pid;
delete from TESTERPARMS where processid=&&pid;
//commit;


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

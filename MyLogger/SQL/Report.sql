select dp.processid, dp.threadid, epnn.inputcount, epsom.inputcount
from dataparms dp, engineparms_nn epnn, engineparms_som epsom where 
dp.processid=epnn.processid and dp.threadid=epnn.threadid
and dp.testid=0
/

declare 
ret number;
arrO dbms_sql.number_table;
arrH dbms_sql.number_table;
arrL dbms_sql.number_table;
arrC dbms_sql.number_table;
arrDD dbms_sql.number_table;
arrMM dbms_sql.number_table;
arrYY dbms_sql.number_table;
arrHH dbms_sql.number_table;
arrMI dbms_sql.number_table;
begin
for i in 1..30 loop 
	arrO(i):=i; 
	arrH(i):=i; 
	arrL(i):=i; 
	arrC(i):=i; 
	arrDD(i):=i; 
	arrMM(i):=5; 
	arrYY(i):=2014; 
	arrHH(i):=15; 
	arrMI(i):=30; 
end loop;
for i in 31..60 loop 
	arrO(i):=i; 
	arrH(i):=i; 
	arrL(i):=i; 
	arrC(i):=i; 
	arrDD(i):=i-30; 
	arrMM(i):=6; 
	arrYY(i):=2014; 
	arrHH(i):=16; 
	arrMI(i):=30; 
end loop;
for i in 61..90 loop 
	arrO(i):=i; 
	arrH(i):=i; 
	arrL(i):=i; 
	arrC(i):=i; 
	arrDD(i):=i-60; 
	arrMM(i):=7; 
	arrYY(i):=2014; 
	arrHH(i):=16; 
	arrMI(i):=30; 
end loop;
ret:=ConcMQ4.Calc('EURUSD',0,90,arrO,arrH,arrL,arrC,arrYY,arrMM,arrDD,arrHH,arrMI,'EURUSD','H1',0,'High','SRHO',1,'C/temp');
dbms_output.put_line('ret='||ret);
end;
/

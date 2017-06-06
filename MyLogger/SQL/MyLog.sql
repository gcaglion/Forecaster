-- connect system/manager@Algo
--create user LogUser identified by LogPwd default tablespace LogData;
--grant dba to LogUser;

--connect LogUser/LogPwd@Algo

----------------------------------------------------------------------------
alter table Dataparms drop constraint DataParms_FK_TesterParms;
alter table Engineparms drop constraint EngineParms_FK_TesterParms;
alter table EngineThreads drop constraint EngineThreads_FK_EngineParms;
alter table CoreImage_NN drop constraint CoreImage_NN_FK_EngineThreads;
alter table CoreImage_SOM drop constraint CoreImage_SOM_FK_EngineThreads;
alter table CoreImage_SVM drop constraint CoreImage_SVM_FK_EngineThreads;
alter table CoreParms_NN drop constraint CoreParms_NN_FK_EngineThreads;
alter table CoreParms_SOM drop constraint CoreParms_SOM_FK_EngineThreads;
alter table CoreParms_SVM drop constraint CoreParms_SVM_FK_EngineThreads;
alter table MyLog_MSE drop constraint MyLog_MSE_FK_EngineThreads;
alter table MyLog_Run drop constraint MyLog_Run_FK_EngineThreads;
alter table CoreLogs_GA drop constraint CoreLogs_GA_FK_ET;
alter table CoreLogs_NN_SCGD drop constraint CoreLog_NN_SCGD_FK_ET;
alter table CoreLogs_NN drop constraint CoreLog_NN_FK_ET;
alter table CoreLogs_GA drop constraint CoreLog_GA_FK_EngineThreads;
alter table CoreLogs_SVM drop constraint CoreLog_SVM_FK_EngineThreads;
alter table CoreLogs_SOM drop constraint CoreLog_SOM_FK_EngineThreads;
----------------------------------------------------------------------------

drop table TesterParms;
create table TesterParms(
	ProcessId number,
	TesterStart date,
	Duration number,
	SimulationLen number,
	SimulationStart date,
	DoTraining number,
	DoRun number
);
alter table TesterParms add constraint TesterParms_PK primary key( ProcessId );

drop table DataParms;
create table DataParms(
	ProcessId number,
	DatasetId number,
	DataSourceType number,
	DataSourceFileName varchar2(100),
	Symbol varchar2(8),
	TimeFrame varchar2(5),
	IsFilled number,
	BarData number,
	DataTransformation number,
	WiggleRoom number,
	HistoryLen number,
	SampleLen number,
	PredictionLen number
);
alter table DataParms add constraint DataParms_PK primary key( ProcessId, DatasetId);

drop table EngineParms;
create table EngineParms(
	ProcessId number,
	EngineType number,
	InputCount number,
	OutputCount number,
	WNN_DecompLevel number,
	WNN_WaveletType varchar2(16)
);
alter table EngineParms add constraint EngineParms_PK primary key( ProcessId );

drop table EngineThreads;
create table EngineThreads(
	ProcessId number,
	TestId number,
	LayerId number,
	CoreId number,
	CoreType number,
	DatasetId number,
	ThreadId number
);
alter table EngineThreads add primary key (ProcessId, TestId, LayerId, CoreId, DatasetId);
alter table EngineThreads add unique (ProcessId, ThreadId);

drop table CoreImage_NN;
create table CoreImage_NN(
	ProcessId number,
	ThreadId number,
	NeuronLevel number,
	FromNeuron number,
	toNeuron number, 
	Weight number,
	CtxValue number
);
alter table CoreImage_NN add constraint CoreImage_NN_PK primary key( ProcessId, ThreadId, NeuronLevel, FromNeuron, ToNeuron );

drop table CoreImage_SOM;
create table CoreImage_SOM(
	ProcessId number,
	ThreadId number,
	FromNeuron number,
	toNeuron number, 
	Weight number
);
alter table CoreImage_SOM add constraint CoreImage_SOM_PK primary key( ProcessId, ThreadId, FromNeuron, ToNeuron );

drop table CoreImage_SVM;
create table CoreImage_SVM(
	ProcessId number,
	ThreadId number,
	SVId number,
	VarId number,
	Weight number
);
alter table CoreImage_SVM add constraint CoreImage_SVM_PK primary key( ProcessId, ThreadId, SVId, VarId );

drop table CoreParms_NN;
create table CoreParms_NN(
	ProcessId number,
	ThreadId number,
	InputCount number,
	OutputCount number,
	LevelsCount number,
	LevelRatioS varchar2(60),
	MaxEpochs number,
	TargetMSE number,
	UseContext number,
	BP_Algo number, 
	TrainingProtocol number,
	StopAtDivergence number,
	LearningRate number,
	LearningMomentum number,
	ActivationFunction number,
	HCPbeta number,
	Mu number
);
alter table CoreParms_NN add primary key( ProcessId, ThreadId );

drop table CoreParms_GA;
create table CoreParms_GA(
	ProcessId number,
	ThreadId number,
	InputCount number,
	OutputCount number,
	FitnessSizeThreshold number, 
	PopulationSize number, 
	MaxGenerations number,
	Levels number, 
	FitnessSkewingFactor number, 
	TargetFitness number, 
	CrossOverProbability number, 
	MutationProbability number, 
	CrossSelfRate number, 
	Roulette_Max_Tries number, 
	ADF_Force_Presence number, 
	ADF_Tree_FixedValues_Ratio number, 
	ADF_Tree_DataPoints_Ratio number, 
	ADF_Leaf_FixedValues_Ratio number
);
alter table CoreParms_GA add primary key( ProcessId, ThreadId );

drop table CoreParms_SOM;
create table CoreParms_SOM(
	ProcessId number,
	ThreadId number,
	InputCount number,
	OutputCount number,
	MaxEpochs number, 
	TDFunction number, 
	BaseTD number, 
	LRFunction number, 
	BaseLR number
);
alter table CoreParms_SOM add primary key( ProcessId, ThreadId );

drop table CoreParms_SVM;
create table CoreParms_SVM(
	ProcessId number,
	ThreadId number,
	InputCount number,
	MaxEpochs number, 
	C number,
	Epsilon number,
	IterToShrink number,
	KernelType number,
	PolyDegree number,
	RBFGamma number,
	CoefLin number,
	CoefConst number,
	KernelCacheSize number
);
alter table CoreParms_SVM add primary key( ProcessId, ThreadId );

drop table MyLog_MSE;
create table MyLog_MSE(
	ProcessId number,
	ThreadId number,
	Epoch number,
	MSE_T number,
	MSE_V number
);
alter table MyLog_MSE add constraint MyLog_MSE_PK primary key( ProcessId, ThreadId, Epoch );

drop table MyLog_Run;
create table MyLog_Run(
	ProcessId number,
	ThreadId number,
	NetProcessId number,
	NetThreadId number,
	Pos number,
	Actual number,
	Predicted number,
	Error number,
	ActualC number,
	PredictedC number,
	ErrorC number,
	BarWidth number,
	ErrorP number
);
alter table MyLog_Run add constraint MyLog_Run_PK primary key( ProcessId, ThreadId, Pos );

drop table CoreLogs_GA;
create table CoreLogs_GA(
	ProcessId number,
	ThreadId number,
	ActualGenerations number
);
alter table CoreLogs_GA add primary key(ProcessId, ThreadId);

drop table CoreLogs_NN;
create table CoreLogs_NN(
	ProcessId number,
	ThreadId number,
	ActualEpochs number
);
alter table CoreLogs_NN add primary key(ProcessId, ThreadId);

drop   table CoreLogs_NN_SCGD;
create table CoreLogs_NN_SCGD(
	ProcessId number,
	ThreadId number,
	Epoch number,
	BPid number,
	K number,
	delta number,
	mu number,
	alpha number,
	beta number,
	lambda number,
	lambdau number,
	rnorm number,
	enorm number,
	comp number
);
alter table CoreLogs_NN_SCGD add primary key(ProcessId, ThreadId, Epoch, BPid, K);

drop   table CoreLogs_SVM;
create table CoreLogs_SVM(
	ProcessId number,
	ThreadId number,
	SVcount number,
	ActualEpochs number,
	ThresholdB number,
	maxdiff number,
	L1loss number,
	WVnorm number,
	LEVnorm number,
	KEvCount number
);
alter table CoreLogs_SVM add primary key(ProcessId, ThreadId);

drop   table CoreLogs_SOM;
create table CoreLogs_SOM(
	ProcessId number,
	ThreadId number,
	ActualEpochs number
);
alter table CoreLogs_SOM add primary key(ProcessId, ThreadId);

-------------------------------------------------------------------------------------- Foreign Key Constraints --------------------------------------------------------------------------------------
alter table Dataparms add constraint DataParms_FK_TesterParms foreign key(ProcessId) references TesterParms(ProcessId);
alter table Engineparms add constraint EngineParms_FK_TesterParms foreign key(ProcessId) references TesterParms(ProcessId);
alter table EngineThreads add constraint EngineThreads_FK_EngineParms foreign key(ProcessId) references EngineParms(ProcessId);
alter table CoreImage_NN add constraint CoreImage_NN_FK_EngineThreads foreign key(ProcessId, ThreadId) references EngineThreads(ProcessId, ThreadId);
alter table CoreImage_SOM add constraint CoreImage_SOM_FK_EngineThreads foreign key(ProcessId, ThreadId) references EngineThreads(ProcessId, ThreadId);
alter table CoreImage_SVM add constraint CoreImage_SVM_FK_EngineThreads foreign key(ProcessId, ThreadId) references EngineThreads(ProcessId, ThreadId);
alter table CoreParms_NN add constraint CoreParms_NN_FK_EngineThreads foreign key(ProcessId, ThreadId) references EngineThreads(ProcessId, ThreadId);
alter table CoreParms_SOM add constraint CoreParms_SOM_FK_EngineThreads foreign key(ProcessId, ThreadId) references EngineThreads(ProcessId, ThreadId);
alter table CoreParms_SVM add constraint CoreParms_SVM_FK_EngineThreads foreign key(ProcessId, ThreadId) references EngineThreads(ProcessId, ThreadId);
alter table MyLog_MSE add constraint MyLog_MSE_FK_EngineThreads foreign key(ProcessId, ThreadId) references EngineThreads(ProcessId, ThreadId);
alter table MyLog_Run add constraint MyLog_Run_FK_EngineThreads foreign key(ProcessId, ThreadId) references EngineThreads(ProcessId, ThreadId);
alter table CoreLogs_GA add constraint CoreLogs_GA_FK_ET foreign key(ProcessId, ThreadId) references EngineThreads(ProcessId, ThreadId);
alter table CoreLogs_NN add constraint CoreLogs_NN_FK_ET foreign key(ProcessId, ThreadId) references EngineThreads(ProcessId, ThreadId);
alter table CoreLogs_NN_SCGD add constraint CoreLog_NN_SCGD_FK_ET foreign key(ProcessId, ThreadId) references EngineThreads(ProcessId, ThreadId);
alter table CoreLogs_SVM add constraint CoreLog_SVM_FK_EngineThreads foreign key(ProcessId, ThreadId) references EngineThreads(ProcessId, ThreadId);
alter table CoreLogs_SOM add constraint CoreLog_SOM_FK_EngineThreads foreign key(ProcessId, ThreadId) references EngineThreads(ProcessId, ThreadId);
-----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
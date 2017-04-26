connect system/manager@Algo
create user LogUser identified by LogPwd default tablespace LogData;
grant dba to LogUser;

connect LogUser/LogPwd@Algo

drop table CoreImage_NN;
create table CoreImage_NN(
	ProcessId number,
	ThreadId number,
	TestId number,
	LayerId number,
	CoreId number,
	DatasetId number,
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
	TestId number,
	LayerId number,
	CoreId number,
	DatasetId number,
	FromNeuron number,
	toNeuron number, 
	Weight number
);
alter table CoreImage_SOM add constraint CoreImage_SOM_PK primary key( ProcessId, ThreadId, FromNeuron, ToNeuron );

drop table CoreImage_SVM;
create table CoreImage_SVM(
	ProcessId number,
	ThreadId number,
	TestId number,
	LayerId number,
	CoreId number,
	DatasetId number,
	SVId number,
	VarId number,
	Weight number
);
alter table CoreImage_SVM add constraint CoreImage_SVM_PK primary key( ProcessId, ThreadId, SVId, VarId );

drop table TesterParms;
create table TesterParms(
	ProcessId number,
	TesterStart date,
	Duration number,
	SimulationLen number,
	SimulationStart date,
	Engine number,
	DoTraining number,
	DoRun number,
	DataSourceType number,
	DataSourceFileName varchar2(100)
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
	LayersCount number,
	WNN_DecompLevel number,
	WNN_WaveletType varchar2(16)
);
alter table EngineParms add constraint EngineParms_PK primary key( ProcessId );

drop table CoreParms_NN;
create table CoreParms_NN(
	ProcessId number,
	LayerId number,
	CoreId number,
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
alter table CoreParms_NN add primary key( ProcessId, LayerId, CoreId );

drop table CoreParms_GA;
create table CoreParms_GA(
	ProcessId number,
	LayerId number,
	CoreId number,
	InputCount number,
	OutputCount number,
	FitnessSizeThreshold number, 
	PopulationSize number, 
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
alter table CoreParms_GA add primary key( ProcessId, LayerId, CoreId );

drop table CoreParms_SOM;
create table CoreParms_SOM(
	ProcessId number,
	LayerId number,
	CoreId number,
	UseContext number,
	InputCount number,
	OutputCount number,
	MaxEpochs number, 
	TDFunction number, 
	BaseTD number, 
	LRFunction number, 
	BaseLR number
);
alter table CoreParms_SOM add primary key( ProcessId, LayerId, CoreId );

drop table CoreParms_SVM;
create table CoreParms_SVM(
	ProcessId number,
	LayerId number,
	CoreId number,
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
alter table CoreParms_SVM add primary key( ProcessId, LayerId, CoreId );

drop table MyLog_MSE;
create table MyLog_MSE(
	ProcessId number,
	ThreadId number,
	TestId number,
	LayerId number,
	CoreId number,
	Epoch number,
	MSE_T number,
	MSE_V number
);
alter table MyLog_MSE add constraint MyLog_MSE_PK primary key( ProcessId, ThreadId, TestId, LayerId, CoreId, Epoch );

drop table MyLog_Run;
create table MyLog_Run(
	ProcessId number,
	ThreadId number,
	NetProcessId number,
	NetThreadId number,
	TestId number,
	LayerId number,
	CoreId number,
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
alter table MyLog_Run add constraint MyLog_Run_PK primary key( ProcessId, ThreadId, TestId, LayerId, CoreId, Pos );

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
	ThresholdB number,
	maxdiff number,
	L1loss number,
	WVnorm number,
	LEVnorm number,
	KEvCount number
);
alter table CoreLogs_SVM add primary key(ProcessId, ThreadId);

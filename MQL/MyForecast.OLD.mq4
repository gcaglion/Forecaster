//+------------------------------------------------------------------+
//|   		                                             MyForecast.mq4 |
//|                                                         gcaglion |
//|                                           https://algoinvest.org |
//+------------------------------------------------------------------+
#property copyright "gcaglion"
#property link      "https://algoinvest.org"
#property version   "1.00"
#property strict
//#property script_show_inputs

#import "MyForecast.dll"
int MT4_GetForecast(
	/* Debug Info */
   int pDebugLevel, int pResultsDest, int pThreadSafeLogging, int pSaveMSE, int pSaveRun, uchar &pLogFileDir[], uchar &pLogFileName[],
	/* Log DB */
	uchar &pDBUser[], uchar &pDBPassword[], uchar &pDBConnString[],
	/* MT4 Instrument Parms */
   uchar &pSymbol[], uchar &pTimeFrame[], /*int pScale,*/
	/* Data Parms */
	int pHistoryLen, int pSampleLen, int pPredictionLen, int pDataTransformation, double pScaleMin, double pScaleMax, double pWiggleRoom, int pUseTSFeatures, uchar& pTSFeatures[],
	/* Engine Parms */
	int pForecastEngine, int pDoTraining, int pSavedEnginePid, int pSavedEngineTid,
	/* Forecast Engine parms */
	double ForecastInfo_HI_Ratio, int ForecastInfo_UseCtx, int ForecastInfo_TrainingProtocol, int ForecastInfo_BP_Algo, int ForecastInfo_ActivationFunction, int ForecastInfo_StopAtDivergence, int ForecastInfo_MaxEpochs, double ForecastInfo_LearningRate, double ForecastInfo_LearningMomentum, double ForecastInfo_TargetMSE, double ForecastInfo_HCPbeta, double ForecastInfo_mu,
	/* SOM Engine parms */
	int SOMInfo_OutputCount, int SOMInfo_MaxEpochs, double SOMInfo_BaseTD, int SOMInfo_TDFunction, double SOMInfo_BaseLR, int SOMInfo_LRFunction,
	/* History and Forecast data */
	uchar &pNDTStart[], uchar &pNDTEnd[], uchar &pNDTStart_V[], uchar &pNDTEnd_V[], double &pHistoryDataH[], double &pHistoryDataL[],double &pValidationDataH[], double &pValidationDataL[], double &pHistoryBW[], double &oForecastH[], double &oForecastL[], double pBaseValH, double pBaseValL
	);

int MT4_GetDataShapeFromDB(
	/* Debug Info */
	int pDebugLevel, uchar &pLogFileDir[], uchar &pLogFileName[],
	/* Log DB */
	uchar &pDBUser[], uchar &pDBPassword[], uchar &pDBConnString[],
	/* Engine Parms */
	int pForecastEngine, int pSavedEnginePid, int pSavedEngineTid,
	/* Output Data Shape Parameters */
	int &oHistoryLen, int &oSampleLen, int &oPredictionLen, int &oDataTransformation, double &oScaleMin, double &oScaleMax, double &owiggleRoom,
	/* TimeSeries Features Parameters */
	int pUseTSFeatures, uchar &pTSFeatures[]
); 
#import

#import "kernel32.dll"
int GetModuleHandleA(string lpString);
int FreeLibrary(int hModule);
#import

enum ENUM_ENGINE{
   NN=0,
   GA=1,
   SVM=2,
   SOM=3,
   WNN=4,
   Dummy=5
};
enum ENUM_DT{
   NONE=0,
   DELTA=1,
   LOG=2,
   DELTALOG=3
};

enum ENUM_TrainProt{
   TP_STOCHASTIC=0,
   TP_BATCH=1,
   TP_ONLINE=2
};

enum ENUM_BP_Algo{
   BP_STD=0,
   BP_Qing=1,
   BP_CGD=4,
   BP_QUICKPROP=5
};

enum ENUM_Activation{
   Act_STD=1,
   Act_QING=3,
   Act_GAIN=4
};

enum ENUM_TDFunc{
   TDConstant=0,
   TDLinear=1,
   TDStepped=2,
   TDExp=3
};

enum ENUM_LRFunc{
   LRConstant=0,
   LRLinear=1,
   LRStepped=2,
   LRExp=3
};

enum ENUM_LOGDESTS{
   LOG_TO_TEXT=1,
   LOG_TO_ORCL=2
};

#define MAX_PREDICTIONLEN 24
#define ForecastMaxObjects 100
string ForecastObjName[1000];

//--- input parameters
//-- Trade
input double TradeSizeMin   = 0.01;
input double TradeSizeMax   = 2.00;
input double TradeSizeDef   = 0.30;
input double RiskRatio      = 0.20;
input bool   CloseOpenTrades= TRUE;
//-- Logging
input int    DebugLevel=2;
input string LogDir="C:/temp";
input string LogFileName="MyForecast.MQ4.log";
input int    ThreadSafeLogging=0;     
input int    SaveMSE=0;
input int    SaveRUN=0;
input ENUM_LOGDESTS ResultsDestination=LOG_TO_ORCL;
//-- Logging DB Info
input string      DBUser="LogUser";
input string      DBPassword="LogPwd";
input string      DBConnString="Algo";
//-- Data Shape Info
input int         HistoryLen=1000;
input int         SampleLen=24;
input int         PredictionLen=5;
input int         ValidationShift=1000;
input ENUM_DT     DataTransformation=DELTA;
input double      ScaleMin=-1;
input double      ScaleMax=1;
input double      WiggleRoom=0.0;
input int         UseTSFeatures=1;
input string      TSFeatures="TSF_MEAN, TSF_MAD, TSF_VARIANCE, TSF_SKEWNESS, TSF_KURTOSIS, TSF_TURNINGPOINTS, TSF_SHE, TSF_HISTVOL";
//-- Engine Info
input ENUM_ENGINE ForecastEngine=NN;
input int         DoTraining=1;
input int         SavedEnginePid=2528;
input int         SavedEngineTid=216;
//-- Engine Params, Forecast
input int               NN_UseContext=1;
input double            NN_HI_Ratio=0.5;
input ENUM_TrainProt    NN_TrainingProtocol=TP_STOCHASTIC;
input ENUM_BP_Algo      NN_BP_Algo=BP_STD;
input ENUM_Activation   NN_ActivationFunction=Act_STD;
input int               NN_StopAtDivergence=1;
input int               NN_MaxEpochs=200;
input double            NN_LearningRate=0.05;
input double            NN_LearningMomentum=0.8;
input double            NN_TargetMSE=0.0001;
input double            NN_HCPbeta=5;
input double            NN_Mu=1.75;
//-- Engine Params, SOM
input int         SOM_OutputCount=24;
input int         SOM_MaxEpochs=500;
input double      SOM_BaseTD=1;
input ENUM_TDFunc SOM_TDFunction=TDExp;
input double      SOM_BaseLR=0.5;
input ENUM_LRFunc SOM_LRFunction=LRExp;
//---
//--- Common variables ---
int i;
uchar vLogDir[], vLogFileName[], vDBUser[], vDBPassword[], vDBConnString[];
uchar vSymbol[], vTimeFrame[];
uchar vNDTStart[], vNDTEnd[];uchar vNDTStart_V[], vNDTEnd_V[];
uchar vTSFeatures[];

int vHistoryLen=HistoryLen;
int vSampleLen=SampleLen;
int vPredictionLen=PredictionLen;
int vValidationShift=ValidationShift;
int vDataTransform=DataTransformation;
double vScaleMin=ScaleMin;
double vScaleMax=ScaleMax;
double vWiggleRoom=WiggleRoom;
int vForecastEngine=ForecastEngine;
int vUseTSFeatures=UseTSFeatures;

int vNN_UseCtx=NN_UseContext;
double vNN_HI_Ratio=NN_HI_Ratio;
int vNN_TrainingProtocol=NN_TrainingProtocol;
int vNN_BP_Algo=NN_BP_Algo;
int vNN_ActivationFunction=NN_ActivationFunction;
int vNN_StopAtDivergence=NN_StopAtDivergence;
int vNN_MaxEpochs=NN_MaxEpochs;
double vNN_LearningRate=NN_LearningRate;
double vNN_LearningMomentum=NN_LearningMomentum;
double vNN_TargetMSE=NN_TargetMSE;
double vNN_HCPbeta=NN_HCPbeta;
double vNN_Mu=NN_Mu;


string vBarT[], vBarT_V[];
double vBarH[], vBarH_V[]; 
double vBarL[], vBarL_V[]; 
double vBarBW[];
double vForecastH[];
double vForecastL[];
double vKazH[];
double vKazL[];

string vBaseNDT;
double vBaseH, vBaseL;
//double vBaseBW;

int    Default_Slippage=5;     
int    NN_Retries = 5;
int    vBarId;
double vPrevFH0, vPrevFL0;
bool   fLog;
//---

int OnInit(){
   //--- LogFile
   fLog=FileOpen("MyForecast.csv", FILE_CSV|FILE_WRITE, ",");
   if(fLog<1){
      Alert("Could not open LogFile. Exiting");
      return (false);
   } else{
      FileWrite(fLog, "Trade#", "Prev_Forecast_H", "Prev_Forecast_L", "Prev_Actual_H", "Prev_Actual_L", "Prev_BW", "Prev_Error_H", "Prev_Error_L", "Prev_Error_H%", "Prev_Error_L%", "Forecast_H", "Forecast_L");
   }
   //--- convert strings to char arrays
   StringToCharArray(LogDir, vLogDir);
   StringToCharArray(LogFileName, vLogFileName);
   StringToCharArray(DBUser, vDBUser);
   StringToCharArray(DBPassword, vDBPassword);
   StringToCharArray(DBConnString, vDBConnString);
   StringToCharArray(Symbol(), vSymbol);
   StringToCharArray(GetCurrentTimeFrame(), vTimeFrame);
   StringToCharArray(TSFeatures, vTSFeatures);
   
   //-- If we load a trained network, we need to overwrite paramenters with the ones from GetDataShapeFromDB()
   if(DoTraining==0){
      printf("Getting Data Shape from DB for pid=%d , tid=%d", SavedEnginePid, SavedEngineTid);
      if(MT4_GetDataShapeFromDB(DebugLevel, vLogDir, vLogFileName, vDBUser, vDBPassword, vDBConnString, vForecastEngine, SavedEnginePid, SavedEngineTid, vHistoryLen, vSampleLen, vPredictionLen, vDataTransform, vScaleMin, vScaleMax, vWiggleRoom, vUseTSFeatures, vTSFeatures)!=0) return(INIT_FAILED);
   }
   
   vBarId=0;
   printf("Init(): Bars=%d ; vHistoryLen=%d ; vSampleLen=%d ; vPredictionLen=%d", Bars, vHistoryLen, vSampleLen, vPredictionLen);
   
   //--- Resize History and Prediction arrays
   ArrayResize(vBarT,vHistoryLen);
   ArrayResize(vBarH,vHistoryLen);
   ArrayResize(vBarL,vHistoryLen);
   ArrayResize(vBarT_V,vHistoryLen);
   ArrayResize(vBarH_V,vHistoryLen);
   ArrayResize(vBarL_V,vHistoryLen);
   ArrayResize(vKazH,vHistoryLen);
   ArrayResize(vKazL,vHistoryLen);
   ArrayResize(vBarBW, vHistoryLen);
   ArrayResize(vForecastH, vPredictionLen);
   ArrayResize(vForecastL, vPredictionLen);
   
   //if(GlobalVariableCheck("vTestId")==FALSE) GlobalVariableSet("vTestId",0);
   if(GlobalVariableCheck("PrevFH0")==FALSE) GlobalVariableSet("PrevFH0",0);
   if(GlobalVariableCheck("PrevFL0")==FALSE) GlobalVariableSet("PrevFL0",0);

   RunForecast();
      
   return(INIT_SUCCEEDED);
}

void OnDeinit(const int reason){
   ObjectsDeleteAll(0,OBJ_RECTANGLE);
   int HMOD = GetModuleHandleA("expert.dll");
   if (HMOD != 0) FreeLibrary(HMOD);
   FileClose(fLog);
}

void OnTick(){
   // Only do this if there's a new bar
   static datetime Time0; if (Time0 == Time[0]) return; Time0 = Time[0];
   //vTestId=GlobalVariableGet("vTestId");
   //GlobalVariableSet("vTestId",vTestId+1);
   RunForecast();
   vBarId++;
   //for(int i=0;i<PredictionLen;i++) printf("ForecastH[%d]=%f ; ForecastL[%d]=%f",i, vForecastH[i], i, vForecastL[i]);
   
}

void RunForecast(){
      int retries=0;

      printf("RunForecast() CheckPoint 0: BarId=%d ; Getting Forecast...", vBarId);
      //-- First, Invert bars sequence
      for(i=0; i<vHistoryLen; i++){    // (i=0 is the current bar)
         vBarT[i]=StringConcatenate(TimeToStr(Time[vHistoryLen-i],TIME_DATE)," ",TimeToStr(Time[vHistoryLen-i],TIME_MINUTES));
         vBarH[i]=High[vHistoryLen-i];
         vBarL[i]=Low [vHistoryLen-i];
         vBarBW[i]=vBarH[i]-vBarL[i];
         vBarT_V[i]=StringConcatenate(TimeToStr(Time[vHistoryLen+vValidationShift-i],TIME_DATE)," ",TimeToStr(Time[vHistoryLen+vValidationShift-i],TIME_MINUTES));
         vBarH_V[i]=High[vHistoryLen+vValidationShift-i];
         vBarL_V[i]=Low [vHistoryLen+vValidationShift-i];
         //printf("vBar[%d]: High=%f, Low=%f", i, vBarH[i], vBarL[i]);     
         //printf("vKaz[%d]: High=%f, Low=%f", i, vKazH[i], vKazL[i]);     
      }
      //-- Add "Base" bar, needed for Delta Transformation
      vBaseNDT=StringConcatenate(TimeToStr(Time[vHistoryLen+1],TIME_DATE)," ",TimeToStr(Time[vHistoryLen+1],TIME_MINUTES));
      vBaseH = High[vHistoryLen+1];
      vBaseL = Low [vHistoryLen+1];

      printf("RunForecast() CheckPoint 1: vBar[%d]: DateTime=%s, High=%f, Low=%f, vBar[%d]: DateTime=%s, High=%f, Low=%f", 0, vBarT[0], vBarH[0], vBarL[0], vHistoryLen-1, vBarT[vHistoryLen-1], vBarH[vHistoryLen-1], vBarL[vHistoryLen-1]);     
      printf("RunForecast() CheckPoint 1: vBar_V[%d]: DateTime=%s, High=%f, Low=%f, vBar_V[%d]: DateTime=%s, High=%f, Low=%f", 0, vBarT_V[0], vBarH_V[0], vBarL_V[0], vHistoryLen-1, vBarT_V[vHistoryLen-1], vBarH_V[vHistoryLen-1], vBarL_V[vHistoryLen-1]);     


      if(vBarId>0){
         vPrevFH0=GlobalVariableGet("PrevFH0");
         vPrevFL0=GlobalVariableGet("PrevFL0");
         printf("RunForecast() CheckPoint 2: Previous Forecast (H|L)=%f|%f ; Previous Actual (H|L)=%f|%f => Previous Error (H|L)=%f|%f", vPrevFH0, vPrevFL0, High[1],Low[1], MathAbs(vPrevFH0-High[1]),MathAbs(vPrevFL0-Low[1]) );
      }
      StringToCharArray(vBarT[0], vNDTStart);
      StringToCharArray(vBarT[vHistoryLen-1], vNDTEnd);
      StringToCharArray(vBarT_V[0], vNDTStart_V);
      StringToCharArray(vBarT_V[vHistoryLen-1], vNDTEnd_V);

      //-- Then, Call DLL to get Next Bar H,L
      while(retries<NN_Retries){
         int ret = MT4_GetForecast(DebugLevel, ResultsDestination, ThreadSafeLogging, SaveMSE, SaveRUN, vLogDir, vLogFileName, vDBUser, vDBPassword, vDBConnString, vSymbol, vTimeFrame, vHistoryLen, vSampleLen, vPredictionLen, vDataTransform, vScaleMin, vScaleMax, vWiggleRoom, vUseTSFeatures, vTSFeatures, vForecastEngine, DoTraining, SavedEnginePid, SavedEngineTid, vNN_HI_Ratio, vNN_UseCtx, vNN_TrainingProtocol, NN_BP_Algo, vNN_ActivationFunction, vNN_StopAtDivergence, vNN_MaxEpochs, vNN_LearningRate, vNN_LearningMomentum, vNN_TargetMSE, vNN_HCPbeta, vNN_Mu, SOM_OutputCount, SOM_MaxEpochs, SOM_BaseTD, SOM_TDFunction, SOM_BaseLR, SOM_LRFunction, vNDTStart, vNDTEnd, vNDTStart_V, vNDTEnd_V, vBarH, vBarL, vBarH_V, vBarL_V, vBarBW, vForecastH, vForecastL, vBaseH, vBaseL);
         printf("RunForecast() CheckPoint 3: MT4_GetForecast() returned vForecast[0] (H|L) = %f|%f", vForecastH[0], vForecastL[0]);
         if (ret!=0){
            Alert("GetNextBars returned ", DoubleToString(ret,0));
            return;
         }
        //-- Make sure forecast bar makes sense... 
        if (vForecastH[0]<vForecastL[0]){
            printf("Invalid Forecast: H=%5.4f , L=%5.4f . retries=%f", vForecastH[0], vForecastL[0], retries);
            retries++;
            if(retries>NN_Retries) return;
         } else {
            break;
         }
     }   
     GlobalVariableSet("PrevFH0", vForecastH[0]);
     GlobalVariableSet("PrevFL0", vForecastL[0]);   
     
     //-- Save All Information before Trade
     if(vBarId>0){
      FileWrite(fLog, vBarId, vPrevFH0, vPrevFL0, High[1],Low[1], MathAbs(High[1]-Low[1]), MathAbs(vPrevFH0-High[1]), MathAbs(vPrevFL0-Low[1]), (MathAbs(vPrevFH0-High[1])/MathAbs(High[1]-Low[1])), (MathAbs(vPrevFL0-Low[1])/MathAbs(High[1]-Low[1])), vForecastH[0], vForecastL[0]);
     }
     //-- Determine Trade
     RefreshRates();
     double FH             = vForecastH[0];
     double FL             = vForecastL[0];
     double RR             = RiskRatio;          // Risk Ratio (PIPS to SL / PIPS to TP)
     double SL, TP;
     double StopLevel=MarketInfo(Symbol(), MODE_STOPLEVEL)*MarketInfo(Symbol(), MODE_TICKSIZE);   
     //int    Ferr           =5;            // Expected Forecast error (in PIPs)
     int    MinProfitPIPs      =5;            // in PIPs
     double MinProfit=MinProfitPIPs*MarketInfo(Symbol(), MODE_TICKSIZE)*10;
     
     printf("1. Current Bar Ask=%5.4f ; Bid=%5.4f ; FH=%5.4f ; FL=%5.4f", Ask, Bid, FH, FL);
     //-- Current price (Ask) is below   ForecastL                                     => BUY (1)
     if(Ask<FL){
         TP=FH; //printf("Original TP=%f", TP);  //-Ferr*MarketInfo(Symbol(),MODE_TICKSIZE)*10;
         if( (TP-Ask)<MinProfit ){
            printf("Profit too small. No Trade.");
            return;
         } 
         SL=Bid-(TP-Ask)*RR; //printf("Original SL=%f", SL);
         if( (Bid-SL)<StopLevel ) SL=Bid-StopLevel;
         printf("Ask<FL (1); TP=%5.4f ; SL=%5.4f", TP, SL);
         NewTrade(OP_BUY, Ask, SL, TP);
     }
     //-- Current price is above   ForecastH                                     => SELL (2)
     if(Bid>FH){
         TP=FL; //printf("Original TP=%f", TP);   //+Ferr*MarketInfo(Symbol(),MODE_TICKSIZE)*10;
         if( (Bid-TP)<MinProfit ){
            printf("Profit too small. No Trade.");
            return;
         } 
         SL=Ask+(Bid-TP)*RR; //printf("Original SL=%f", SL);
         if( (SL-Ask)<StopLevel ) SL=Ask+StopLevel;
         printf("Bid>FH (2) ; TP=%5.4f ; SL=%5.4f", TP, SL);
         NewTrade(OP_SELL, Bid, SL, TP);
     }
     //-- Current price is between ForecastL and ForecastH, closer to ForecastL  => BUY (3)
     if( Ask<=FH && Bid>=FL &&(Bid-FL)<=(FH-Ask) ){
         TP=FH; //printf("Original TP=%f", TP);   //-Ferr*MarketInfo(Symbol(),MODE_TICKSIZE)*10;
         if( (TP-Ask)<MinProfit ){
            printf("Profit too small. No Trade.");
            return;
         } 
         SL=Bid-(TP-Ask)*RR; //printf("Original SL=%f", SL);
         if( (Bid-SL)<StopLevel ) SL=Bid-StopLevel;
         printf("(3)");
         NewTrade(OP_BUY, Ask, SL, TP);
     }
     //-- Current price is between ForecastL and ForecastH, closer to ForecastH  => SELL (4)
     if( Ask<=FH && Bid>=FL && (FH-Ask)<=(Bid-FL) ){
         TP=FL; //printf("Original TP=%f", TP);   //+Ferr*MarketInfo(Symbol(),MODE_TICKSIZE)*10;
         if( (Bid-TP)<MinProfit ){
            printf("Profit too small. No Trade.");
            return;
         } 
         SL=Ask+(Bid-TP)*RR; //printf("Original SL=%f", SL);
         if( (SL-Ask)<StopLevel ) SL=Ask+StopLevel;
         printf("(4)");
         NewTrade(OP_SELL, Bid, SL, TP);
     }
     //-- Display Forecasts (only for the next bar)
      DrawForecast(vForecastH[0], vForecastL[0]);
}


//===============================================================================================================
//--------------------------------------------------------------------------------------------------------------
// Trading Functions
//--------------------------------------------------------------------------------------------------------------
void CloseOpenPos(string pComment){
   int PriceMod;
   for (i=OrdersTotal(); i>0; i--){
      if(OrderSelect(i-1,SELECT_BY_POS)){
         if(OrderComment()==pComment){ 
            if(OrderType()==OP_SELL) {PriceMod=MODE_ASK;} else{PriceMod=MODE_BID;}
            RefreshRates();
            if ( !OrderClose(OrderTicket(),OrderLots(),MarketInfo(OrderSymbol(),PriceMod),20) ) printf("CloseOpenPos(%s) failed with error:%d",pComment,GetLastError());
         }
      }
   }
}

double GetLastPL(string pComment){
   string pCommentSL=pComment; StringAdd(pCommentSL,"[sl]");
   double PL=0;
   for (i=OrdersHistoryTotal(); i>0; i--){
      if(OrderSelect(i-1,SELECT_BY_POS, MODE_HISTORY)){
         if(OrderComment()==pComment || OrderComment()==pCommentSL){ 
             PL=OrderProfit();
             break;
         }
      } else{
         Print("OrderSelect() failed with error: ", GetLastError());
      }
   }
   return PL;
}

int NewTrade(int cmd, double price, double stoploss, double takeprofit){
   static double volume=TradeSizeDef;
   int TktId;
   double prevPL;
   printf("NewTrade() called with cmd=%d , volume=%f , price=%5.4f , stoploss=%5.4f , takeprofit=%5.4f",cmd,volume,price,stoploss,takeprofit);

   // Use Comments string to avoid duplicates: 
   string vComment="MyEL"+"_"+Symbol();   //+"_"+IntegerToString(Period())+"_"+IntegerToString(TimeYear(Time[0]))+"-"+IntegerToString(TimeMonth(Time[0]))+"-"+IntegerToString(TimeDay(Time[0]))+"-"+IntegerToString(TimeHour(Time[0]))+"-"+IntegerToString(TimeMinute(Time[0]));   
   
   if(CloseOpenTrades) CloseOpenPos(vComment);       // Close Previous Position
   prevPL=GetLastPL(vComment);                       // Get last closed position P/L
   //printf("<NewTrade() volume=%f ; PrevPL=%f",volume, prevPL);
   // Anti-Martingale: if last trade was at profit, double TradeSize, otherwise halve it.
   if(prevPL>0) volume=volume*2; if(volume>TradeSizeMax) volume=volume/2;
   if(prevPL<0) volume=volume/2; if(volume<TradeSizeMin) volume=volume*2;
  
   
   // Open Trade
   TktId=OrderSend(Symbol(), cmd, volume, price, Default_Slippage, stoploss, takeprofit, vComment, 15081970);
 
   if (TktId==-1) Alert("NewTrade() failed with error: ",GetLastError());
   return TktId;
}

//--------------------------------------------------------------------------------------------------------------
// LogFile Functions
//--------------------------------------------------------------------------------------------------------------
//--------------------------------------------------------------------------------------------------------------
// Miscellaneous Functions
//--------------------------------------------------------------------------------------------------------------
string GetCurrentTimeFrame(){
switch (_Period){
      case PERIOD_M1:
         return ("M1");
      case PERIOD_M5:
         return ("M5");
      case PERIOD_M15:
         return ("M15");
      case PERIOD_M30:
         return ("M30");
      case PERIOD_H1:
         return ("H1");
      case PERIOD_H4:
         return ("H4");
      case PERIOD_D1:
         return ("D1"); 
      default:     
      Print("Timeframe not supported. Exiting.");
      ExpertRemove(); 
      return("");
   }
}
void DrawForecast(double H, double L){
   static int Fidx=0;
   double price1, price2;
   static double prevH=0;
   static double prevL=0;
   if(prevH==0) prevH=High[0];
   if(prevL==0) prevL=Low[0];
   
   //First, draw High
   price1=H;
   price2=H+0.005;
   Fidx++; if(Fidx>(ForecastMaxObjects-1)) Fidx=0;
   ForecastObjName[Fidx]="High"+IntegerToString(Fidx);
   ObjectDelete(ForecastObjName[Fidx]);   // don't care if this fails
   //ObjectCreate(ForecastObjName[Fidx], OBJ_TRIANGLE, 0, Time[0]-Period()*60, price1, Time[0], price2, Time[0]+Period()*60, price1);   
   ObjectCreate(ForecastObjName[Fidx], OBJ_TREND, 0, Time[0], prevH, Time[0]+Period()*60, H); 
   ObjectSetInteger(0, ForecastObjName[Fidx], OBJPROP_RAY_RIGHT, false);
   ObjectSetInteger(0, ForecastObjName[Fidx], OBJPROP_COLOR, clrBlue);
   prevH=H;
  
   //Then, draw Low
   price1=L;
   price2=L-0.005;
   Fidx++; if(Fidx>ForecastMaxObjects) Fidx=1;
   //printf("Fidx=%d",Fidx);
   ForecastObjName[Fidx]="Low"+IntegerToString(Fidx-1);
   ObjectDelete(ForecastObjName[Fidx]);   // don't care if this fails
   //ObjectCreate(ForecastObjName[Fidx], OBJ_TRIANGLE, 0, Time[0]-Period()*60, price1, Time[0], price2, Time[0]+Period()*60, price1);   
   ObjectCreate(ForecastObjName[Fidx], OBJ_TREND, 0, Time[0], prevL, Time[0]+Period()*60, L);
   ObjectSetInteger(0, ForecastObjName[Fidx], OBJPROP_RAY_RIGHT, false);
   ObjectSetInteger(0, ForecastObjName[Fidx], OBJPROP_COLOR, clrRed);
   prevL=L;
}

//+------------------------------------------------------------------+
//|                                                     dioporco.mq4 |
//|                        Copyright 2017, MetaQuotes Software Corp. |
//|                                             https://www.mql5.com |
//+------------------------------------------------------------------+
#property copyright "gcaglion"
#property link      "https://algoinvest.org"
#property version   "1.00"
#property strict


#import "MyMtWrapper.dll"
int MTgetForecast(
   int paramOverrideCnt, uchar &paramOverride[], 
   uchar& pDBCtxS[], 
   int progId,
	double &pHistoryDataH[], double pHistoryBaseValH,
	double &pHistoryDataL[], double pHistoryBaseValL,
	double &pHistoryBW[],
	double &pValidationDataH[], double pValidationBaseValH,
	double &pValidationDataL[], double pValidationBaseValL,
	double &pFutureDataH[],
	double &pFutureDataL[],
	double &pFutureBW[],
	double &oPredictedDataH[], double &oPredictedDataL[]
);

int  MTOraConnect(int paramOverrideCnt, uchar &paramOverride[], uchar& oCtxS[]);
void MTOraDisconnect(int paramOverrideCnt, uchar &paramOverride[], uchar& oCtxS[], int pCommit);
void MTOraCommit(int paramOverrideCnt, uchar &paramOverride[], uchar& oCtxS[]);
int  MTSaveClientInfo( int paramOverrideCnt, uchar &paramOverride[], uchar& pDBCtxS[], uchar &currentBar[], int pDoTraining, int pDoRun);

#import

//--- input parameters

//-- Parameters File
input string ParametersFile="C:/temp/Forecaster.ini";
//-- Data Shape
input int HistoryLen    = 1000;
input int PredictionLen = 5;
input int ValidationShift = 0;
input int Action        = 0;  // TRAIN_SAVE_RUN
//-- Trade
input double TradeSizeMin   = 0.01;
input double TradeSizeMax   = 2.00;
input double TradeSizeDef   = 0.30;
input double RiskRatio      = 0.20;
input bool   CloseOpenTrades= TRUE;

//--- local variables
string vIniFile=ParametersFile;
int vHistoryLen=HistoryLen;
int vPredictionLen=PredictionLen;
int vValidationShift=-ValidationShift;

//--- data variables to be passed in MTgetForecast() call
int vParamOverrideCnt;
uchar vParamOverride[];
double vHistoryDataH[], vHistoryBaseValH;
double vHistoryDataL[], vHistoryBaseValL;
double vHistoryBW[];
double vValidationDataH[], vValidationBaseValH;
double vValidationDataL[], vValidationBaseValL;
double vFutureDataH[];
double vFutureDataL[];
double vFutureBW[];
double vPredictedDataH[], vPredictedDataL[];

//--- bars timestamps
string sCurrentBarTime; uchar vCurrentBarTime[];
string vHistoryTime[], vValidationTime[];
string vHistoryBaseTime, vValidationBaseTime;

//--- miscellaneous variables
uchar vCtxS[]; // DBCtx in char* format
int DllRetVal=0;  // used from OnDeinit() to determine whether to commit changes to DB
string sParamOverride="MT4";
int    Default_Slippage=8;     
int    NN_Retries = 5;
int    vBarId;
double vPrevFH0, vPrevFL0;
bool   fLog;

//+------------------------------------------------------------------+
//| Expert initialization function                                   |
//+------------------------------------------------------------------+
int OnInit()
  {
  //---
   //--- Resize History and Prediction arrays
   ArrayResize(vHistoryDataH, vHistoryLen); 
   ArrayResize(vHistoryDataL, vHistoryLen);
   ArrayResize(vHistoryBW, vHistoryLen);
   ArrayResize(vValidationDataH, vHistoryLen); 
   ArrayResize(vValidationDataL, vHistoryLen); 
   ArrayResize(vFutureDataH, vPredictionLen);
   ArrayResize(vFutureDataL, vPredictionLen);
   ArrayResize(vFutureBW, vPredictionLen);
   ArrayResize(vPredictedDataH, vPredictionLen);
   ArrayResize(vPredictedDataL, vPredictionLen);
   ArrayResize(vHistoryTime, vHistoryLen); 
   ArrayResize(vValidationTime, vHistoryLen); 
  
   //--- counters used to keep track of graphic objects on chart
   if(GlobalVariableCheck("PrevFH0")==FALSE) GlobalVariableSet("PrevFH0",0);
   if(GlobalVariableCheck("PrevFL0")==FALSE) GlobalVariableSet("PrevFL0",0);

   //--- 0. prepare parameter override string
   sParamOverride=sParamOverride+" --IniFile="+vIniFile;
   sParamOverride=sParamOverride+" --Forecaster.HaveFutureData=0";
   sParamOverride=sParamOverride+" --DataSource.Symbol="+Symbol();
   sParamOverride=sParamOverride+" --DataSource.TimeFrame="+IntegerToString(Period());
   sParamOverride=sParamOverride+" --DataSource.BarDataTypes=HIGH,LOW";
   sParamOverride=sParamOverride+" --DataParms.HistoryLen="+IntegerToString(vHistoryLen);
   sParamOverride=sParamOverride+" --DataParms.PredictionLen="+IntegerToString(vPredictionLen);
   sParamOverride=sParamOverride+" --DataParms.ValidationShift="+IntegerToString(-vValidationShift);
   vParamOverrideCnt=8;
   StringToCharArray(sParamOverride, vParamOverride);

   //--- 1. Connect to DB and keep session Context
   string CtxS="0000000000000000000000000000000000";
   StringToCharArray(CtxS, vCtxS);
   DllRetVal=MTOraConnect(vParamOverrideCnt, vParamOverride, vCtxS);
   Print("MTOraConnect() returns ", DllRetVal);
	if (DllRetVal!=0) return -1;   
   CtxS=CharArrayToString(vCtxS); Print("vCtxS=",CtxS);

  	//--- 2. Save Client Log (elapsedTime is 0)
   if(!IsTesting()) {
     	sCurrentBarTime=StringConcatenate(TimeToString(Time[0], TIME_DATE),TimeToString(Time[0], TIME_MINUTES));
     	StringToCharArray(sCurrentBarTime, vCurrentBarTime);
     	DllRetVal=MTSaveClientInfo(vParamOverrideCnt, vParamOverride, vCtxS, vCurrentBarTime, 1, 1);
      Print("MTSaveClientInfo() returns ", DllRetVal);
      if (DllRetVal!=0) ExpertRemove();
   }
//---
   return(INIT_SUCCEEDED);
  }
//+------------------------------------------------------------------+
//| Expert deinitialization function                                 |
//+------------------------------------------------------------------+
void OnDeinit(const int reason)
  {
   //--- Disconnect from DB upon exiting
   if(reason==REASON_INITFAILED || reason==REASON_PROGRAM){
      MTOraDisconnect(vParamOverrideCnt, vParamOverride, vCtxS, 0);
   } else{
      MTOraDisconnect(vParamOverrideCnt, vParamOverride, vCtxS, 1);
   }
  }
//+------------------------------------------------------------------+
//| Expert tick function                                             |
//+------------------------------------------------------------------+
void OnTick()
  {
   // Only do this if there's a new bar
   static datetime Time0; if (Time0 == Time[0]) return; Time0 = Time[0];
   //vTestId=GlobalVariableGet("vTestId");
   //GlobalVariableSet("vTestId",vTestId+1);
   DllRetVal=GetForecast();
   if (DllRetVal!=0) ExpertRemove();
   MTOraCommit(vParamOverrideCnt, vParamOverride, vCtxS);
   
   int TradeRet=DoTrade();
   //for(int i=0;i<PredictionLen;i++) printf("ForecastH[%d]=%f ; ForecastL[%d]=%f",i, vForecastH[i], i, vForecastL[i]);
  }
//+------------------------------------------------------------------+

//+------------------------------------------------------------------+
//| Main routines                                            |
//+------------------------------------------------------------------+
int DoTrade(){
     //-- Determine Trade
     RefreshRates();
     double FH             = vPredictedDataH[0];
     double FL             = vPredictedDataL[0];
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
            return (1);
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
            return(1);
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
            return(1);
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
            return(1);
         } 
         SL=Ask+(Bid-TP)*RR; //printf("Original SL=%f", SL);
         if( (SL-Ask)<StopLevel ) SL=Ask+StopLevel;
         printf("(4)");
         NewTrade(OP_SELL, Bid, SL, TP);
     }
     //-- Display Forecasts (only for the next bar)
     DrawForecast(vPredictedDataH[0], vPredictedDataL[0]);
      
     return 0;
}



int GetForecast()
  {
 
      int retries=0;

      if(!IsTesting()) printf("RunForecast() CheckPoint 0: BarId=%d ; Getting Forecast...", vBarId);
      //-- First, Invert bars sequence
      for(int i=0; i<vHistoryLen; i++){    // (i=0 is the current bar)
         vHistoryTime[i]=StringConcatenate(TimeToStr(Time[vHistoryLen-i],TIME_DATE)," ",TimeToStr(Time[vHistoryLen-i],TIME_MINUTES));
         vHistoryDataH[i]=High[vHistoryLen-i];
         vHistoryDataL[i]=Low [vHistoryLen-i];
         vHistoryBW[i]=vHistoryDataH[i]-vHistoryDataL[i];
         vValidationTime[i]=StringConcatenate(TimeToStr(Time[vHistoryLen+vValidationShift-i],TIME_DATE)," ",TimeToStr(Time[vHistoryLen+vValidationShift-i],TIME_MINUTES));
         vValidationDataH[i]=High[vHistoryLen+vValidationShift-i];
         vValidationDataL[i]=Low [vHistoryLen+vValidationShift-i];
         //printf("vBar[%d]: High=%f, Low=%f", i, vBarH[i], vBarL[i]);     
         //printf("vKaz[%d]: High=%f, Low=%f", i, vKazH[i], vKazL[i]);     
      }
      //-- Add "Base" bar, needed for Delta Transformation
      vHistoryBaseTime=StringConcatenate(TimeToStr(Time[vHistoryLen+1],TIME_DATE)," ",TimeToStr(Time[vHistoryLen+1],TIME_MINUTES));
      vHistoryBaseValH = High[vHistoryLen+1];
      vHistoryBaseValL = Low [vHistoryLen+1];

      if(!IsTesting()) printf("RunForecast() CheckPoint 1: vBar[%d]: DateTime=%s, High=%f, Low=%f, vBar[%d]: DateTime=%s, High=%f, Low=%f", 0, vHistoryTime[0], vHistoryDataH[0], vHistoryDataL[0], vHistoryLen-1, vHistoryTime[vHistoryLen-1], vHistoryDataH[vHistoryLen-1], vHistoryDataL[vHistoryLen-1]);     
      if(!IsTesting()) printf("RunForecast() CheckPoint 1: vBar_V[%d]: DateTime=%s, High=%f, Low=%f, vBar_V[%d]: DateTime=%s, High=%f, Low=%f", 0, vValidationTime[0], vValidationDataH[0], vValidationDataL[0], vHistoryLen-1, vValidationTime[vHistoryLen-1], vValidationDataH[vHistoryLen-1], vValidationDataL[vHistoryLen-1]);     


      if(vBarId>0){
         vPrevFH0=GlobalVariableGet("PrevFH0");
         vPrevFL0=GlobalVariableGet("PrevFL0");
         if(!IsTesting()) printf("RunForecast() CheckPoint 2: Previous Forecast (H|L)=%f|%f ; Previous Actual (H|L)=%f|%f => Previous Error (H|L)=%f|%f", vPrevFH0, vPrevFL0, High[1],Low[1], MathAbs(vPrevFH0-High[1]),MathAbs(vPrevFL0-Low[1]) );
      }
      /*
      StringToCharArray(vBarT[0], vNDTStart);
      StringToCharArray(vBarT[vHistoryLen-1], vNDTEnd);
      StringToCharArray(vBarT_V[0], vNDTStart_V);
      StringToCharArray(vBarT_V[vHistoryLen-1], vNDTEnd_V);
      */
      
      //-- Then, Call DLL to get Next Bar H,L
      while(retries<NN_Retries){
      int ret=MTgetForecast(
         vParamOverrideCnt, vParamOverride,
         vCtxS,
         vBarId,
         vHistoryDataH, vHistoryBaseValH,
         vHistoryDataL, vHistoryBaseValL,
         vHistoryBW,
         vValidationDataH, vValidationBaseValH,
         vValidationDataL, vValidationBaseValL,
         vFutureDataH,
         vFutureDataL,
         vFutureBW,
         vPredictedDataH, vPredictedDataL
         );
         printf("RunForecast() CheckPoint 3: MT4_GetForecast() returned vForecast[0] (H|L) = %f|%f", vPredictedDataH[0], vPredictedDataL[0]);
         if (ret!=0){
            Alert("GetNextBars returned ", DoubleToString(ret,0));
            return -1;
         }
        //-- Make sure forecast bar makes sense... 
        if (vPredictedDataH[0]<vPredictedDataL[0]){
            printf("Invalid Forecast: H=%5.4f , L=%5.4f . retries=%f", vPredictedDataH[0], vPredictedDataL[0], retries);
            retries++;
            if(retries>NN_Retries) return 0;
         } else {
            break;
         }
     }   
     GlobalVariableSet("PrevFH0", vPredictedDataH[0]);
     GlobalVariableSet("PrevFL0", vPredictedDataL[0]);   
     vBarId++;

     return 0;
 }
//+------------------------------------------------------------------+

//--------------------------------------------------------------------------------------------------------------
// Trading Functions
//--------------------------------------------------------------------------------------------------------------
void CloseOpenPos(string pComment){
   int PriceMod;
   for (int i=OrdersTotal(); i>0; i--){
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
   for (int i=OrdersHistoryTotal(); i>0; i--){
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
   printf("NewTrade() called with cmd=%s , volume=%f , price=%5.4f , stoploss=%5.4f , takeprofit=%5.4f",(cmd==1?"BUY":"SELL"),volume,price,stoploss,takeprofit);

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

void DrawForecast(double H, double L){
   const int ForecastMaxObjects=100;
   string ForecastObjName[1000];
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

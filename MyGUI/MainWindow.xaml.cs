using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows;
using System.Windows.Controls;
using System.Windows.Data;
using System.Windows.Documents;
using System.Windows.Input;
using System.Windows.Media;
using System.Windows.Media.Imaging;
using System.Windows.Navigation;
using System.Windows.Shapes;
using System.Windows.Forms;
using System.IO;
using System.Text.RegularExpressions;
using System.Diagnostics;
using System.Windows.Threading;

namespace MyGUI
{
    /// <summary>
    /// Interaction logic for MainWindow.xaml
    /// </summary>
    /// 
    public partial class MainWindow : Window
    {
        public int SourceType;
        //bool WindowLoadingComplete;

        public MainWindow() {
            //WindowLoadingComplete = false;

            InitializeComponent();
            System.Threading.Thread.Sleep(3000);
            //if(WindowLoadingComplete)
            LoadIniFile(App.LastIniFile);
        }
        /*
        void setWindowLoadingComplete() {
            WindowLoadingComplete = true;
        }
        private void OnWindowLoaded(object sender, RoutedEventArgs e)
        {
            Dispatcher.BeginInvoke(new Action(() => setWindowLoadingComplete()), DispatcherPriority.ContextIdle, null);
        }
        */
        private void frame_Navigated(object sender, NavigationEventArgs e)
        {

        }

        private int LoadIniFile(string fname) {
            MatchCollection ma;
            string[] IniParm = File.ReadAllLines(fname);
            string Pattern = @"^(.+)\s+=\s+(.+)";
            string pname, pval;

            foreach (string parm in IniParm) {
                ma = Regex.Matches(parm, Pattern, RegexOptions.Singleline);
                if (ma.Count > 0) {
                    pname = ma[0].Groups[1].ToString().TrimEnd();
                    pval = ma[0].Groups[2].ToString();
                    //-- Client General Parameters
                    if (pname.Equals("Tester.SimulationLength")) txt_SimulationLength.Text = pval;
                    if (pname.Equals("Tester.SimulationStart")) txt_SimulationStart.Text = pval;
                    if (pname.Equals("Tester.PauseAtEnd")) cb_PauseAtEnd.IsChecked = (pval.Equals("1"));
                    //-- Forecaster General Parameters
                    if (pname.Equals("Forecaster.Engine")) cbo_EngineType.Text = pval.Substring(7);                    
                    if (pname.Equals("Forecaster.Action")) cbo_Action.Text = pval;
                    if (pname.Equals("Forecaster.HaveFutureData")) cb_HaveFutureData.IsChecked = (pval.Equals("1"));
                    //-- Saved Engine Retrieval Parameters
                    if (pname.Equals("SavedEngine.ProcessId")) txt_SavedEnginePid.Text = pval;
                    if (pname.Equals("SavedEngine.ThreadId")) txt_SavedEngineTid.Text = pval;
                    if (pname.Equals("SavedEngine.DatasetId")) txt_SavedEngineDSid.Text = pval;
                    //-- Forecaster Results Parameters
                    if (pname.Equals("Results.SaveNothing")) cb_SaveNothing.IsChecked = (pval.Equals("1"));
                    if (pname.Equals("Results.SaveMSE")) cb_SaveMSE.IsChecked = (pval.Equals("1"));
                    if (pname.Equals("Results.SaveRun")) cb_SaveRun.IsChecked = (pval.Equals("1"));
                    if (pname.Equals("Results.SaveInternals")) cb_SaveInternals.IsChecked = (pval.Equals("1"));
                    if (pname.Equals("Results.SaveImages")) cb_SaveImages.IsChecked = (pval.Equals("1"));
                    if (pname.Equals("Results.Destination")) cbo_ResultsDest.Text = pval.Substring(7);
                    if (pname.Equals("Results.DBUser")) txt_ResultsDBUser.Text = pval;
                    if (pname.Equals("Results.DBPassword")) txt_ResultsDBPassword.Text = pval;
                    if (pname.Equals("Results.DBConnString")) txt_ResultsDBConnString.Text = pval;
                    //-- Forecaster Debug Parameters 
                    if (pname.Equals("Forecaster.DebugLevel")) txt_DebugLevel.Text = pval;
                    if (pname.Equals("Forecaster.DebugFilePath")) txt_DebugFilePath.Text = pval;
                    if (pname.Equals("Forecaster.DebugFileName")) txt_DebugFileName.Text = pval;
                    if (pname.Equals("Forecaster.ThreadSafeLogging")) cb_ThreadSafeLogging.IsChecked = (pval.Equals("1"));
                    if (pname.Equals("Forecaster.PauseOnError")) cb_PauseOnError.IsChecked = (pval.Equals("1"));
                    if (pname.Equals("Forecaster.DumpSampleData")) cb_DumpSampleData.IsChecked = (pval.Equals("1"));
                    //-- Data Shape Parameters
                    if (pname.Equals("DataParms.HistoryLen")) txt_HistoryLen.Text = pval;
                    if (pname.Equals("DataParms.SampleLen")) txt_SampleLen.Text = pval;
                    if (pname.Equals("DataParms.PredictionLen")) txt_PredictionLen.Text = pval;
                    //-- Data PreProcessing Parameters
                    if (pname.Equals("DataParms.ValidationShift")) txt_ValidationShift.Text = pval;
                    if (pname.Equals("DataParms.DataTransformation")) cbo_DataTransformation.Text = pval;
                    if (pname.Equals("DataParms.WiggleRoom")) txt_WiggleRoom.Text = pval;
                    if (pname.Equals("DataParms.TSFeatures")) cb_UseTSF.IsChecked = (pval.Equals("1"));
                    /*
                     * ... select specific TSF checkboxes
                     */
                    //-- Data Source Parameters
                    if (pname.Equals("DataSource.SourceType")) rb_SOURCE_DATA_FROM_FILE.IsChecked = (pval.Equals("SOURCE_DATA_FROM_FILE"));
                    if (pname.Equals("DataSource.DBConn.DBUser")) txt_DBUser.Text = pval;
                    if (pname.Equals("DataSource.DBConn.DBPassword")) txt_DBPassword.Text = pval;
                    if (pname.Equals("DataSource.DBConn.DBConnString")) txt_DBConnString.Text = pval;
                    if (pname.Equals("DataSource.Symbol")) txt_Symbol.Text = pval;
                    if (pname.Equals("DataSource.TimeFrame")) cbo_TimeFrame.Text = pval;
                    if (pname.Equals("DataSource.IsFilled")) cb_IsFilled.IsChecked = (pval.Equals("1"));
                    /*
                     * ... select specific BarDataTypes
                     */
                    if (pname.Equals("DataSource.FileName")) txt_DataSource_FileName.Text = pval;
                    if (pname.Equals("DataSource.TextFieldSeparator")) cbo_TextFieldSeparator.Text = pval;
                    if (pname.Equals("DataSource.FileDataSets")) txt_FileDataSets.Text = pval;
                    if (pname.Equals("DataSource.CalcFileDataBW")) cb_CalcFileDataBW.IsChecked = (pval.Equals("1"));
                    if (pname.Equals("DataSource.DStoCalcBWFrom")) txt_DStoCalcBWFrom.Text = pval;
                    //-- NN Engine Prameters
                    if (pname.Equals("NNInfo.LevelRatios")) txt_LevelRatios.Text = pval;
                    if (pname.Equals("NNInfo.UseContext")) cb_UseContext.IsChecked = (pval.Equals("1"));
                    if (pname.Equals("NNInfo.TrainingBatchCount")) txt_TrainingBatchCount.Text = pval;
                    if (pname.Equals("NNInfo.BP_Algo")) cbo_BPAlgo.Text = pval.Substring(3);
                    if (pname.Equals("NNInfo.ActivationFunction")) cbo_ActivationFunction.Text = pval.Substring(14);
                    if (pname.Equals("NNInfo.StopAtDivergence")) cb_StopAtDivergence.IsChecked = (pval.Equals("1"));
                    if (pname.Equals("NNInfo.MaxEpochs")) txt_MaxEpochs.Text = pval;
                    if (pname.Equals("NNInfo.TargetMSE")) txt_TargetMSE.Text = pval;
                    if (pname.Equals("NNInfo.LearningRate")) txt_LearningRate.Text = pval;
                    if (pname.Equals("NNInfo.Std.LearningMomentum")) txt_LearningMomentum.Text = pval;
                    if (pname.Equals("NNInfo.Qing.HCPbeta")) txt_Qing_HCPbeta.Text = pval;
                    if (pname.Equals("NNInfo.QProp.mu")) txt_Qprop_mu.Text = pval;
                    if (pname.Equals("NNInfo.RProp.d0")) txt_Rprop_d0.Text = pval;
                    if (pname.Equals("NNInfo.SCGD.maxK")) txt_SCGD_maxK.Text = pval;
                    //-- SVM Engine Parameters
                    if (pname.Equals("SVMInfo.DebugLevel")) txt_SVMDebugLevel.Text = pval;
                    if (pname.Equals("SVMInfo.C")) txt_C.Text = pval;
                    if (pname.Equals("SVMInfo.epsilon")) txt_epsilon.Text = pval;
                    if (pname.Equals("SVMInfo.IterToShrink")) txt_IterToShrink.Text = pval;
                    if (pname.Equals("SVMInfo.MaxEpochs")) txt_SVMMaxEpochs.Text = pval;
                    if (pname.Equals("SVMInfo.DebugLevel")) txt_SVMDebugLevel.Text = pval;
                    if (pname.Equals("SVMInfo.KernelType")) cbo_KernelType.Text = pval.Substring(12);
                    if (pname.Equals("SVMInfo.PolyDegree")) txt_PolyDegree.Text = pval;
                    if (pname.Equals("SVMInfo.RBFgamma")) txt_RBFgamma.Text = pval;
                    if (pname.Equals("SVMInfo.CoefLin")) txt_CoefLin.Text = pval;
                    if (pname.Equals("SVMInfo.CoefConst")) txt_CoefConst.Text = pval;
                    if (pname.Equals("SVMInfo.KernelCacheSize")) txt_KernelCacheSize.Text = pval;
                    if (pname.Equals("SVMInfo.SlackNorm")) cbo_SlackNorm.Text = pval.Substring(11);
                    if (pname.Equals("SVMInfo.RescalingMethod")) cbo_RescalingMethod.Text = pval.Substring(17);
                    if (pname.Equals("SVMInfo.LossFunction")) cbo_LossFunction.Text = pval.Substring(14);
                    if (pname.Equals("SVMInfo.LearningAlgo")) cbo_LearningAlgo.Text = pval.Substring(14);
                    if (pname.Equals("SVMInfo.NewConstrEtrain")) txt_NewConstrEtrain.Text = pval;
                    if (pname.Equals("SVMInfo.CCacheSize")) txt_CCacheSize.Text = pval;
                    if (pname.Equals("SVMInfo.BatchSize")) txt_BatchSize.Text = pval;
                    if (pname.Equals("SVMInfo.NewVarSinQP")) txt_NewVarSinQP.Text = pval;
                    if (pname.Equals("SVMInfo.CustomKernel")) txt_CustomKernel.Text = pval;
                    //-- WNN Engine Parameters
                    if (cbo_EngineType.Text.Equals("WNN")) {
                        if (pname.Equals("WNNInfo.L0.LevelRatios")) txt_LevelRatios.Text = pval;
                        if (pname.Equals("WNNInfo.L0.UseContext")) cb_UseContext.IsChecked = (pval.Equals("1"));
                        if (pname.Equals("WNNInfo.L0.TrainingBatchCount")) txt_TrainingBatchCount.Text = pval;
                        if (pname.Equals("WNNInfo.L0.BP_Algo")) cbo_BPAlgo.Text = pval.Substring(3);
                        if (pname.Equals("WNNInfo.L0.ActivationFunction")) cbo_ActivationFunction.Text = pval.Substring(14);
                        if (pname.Equals("WNNInfo.L0.StopAtDivergence")) cb_StopAtDivergence.IsChecked = (pval.Equals("1"));
                        if (pname.Equals("WNNInfo.L0.MaxEpochs")) txt_MaxEpochs.Text = pval;
                        if (pname.Equals("WNNInfo.L0.TargetMSE")) txt_TargetMSE.Text = pval;
                        if (pname.Equals("WNNInfo.L0.LearningRate")) txt_LearningRate.Text = pval;
                        if (pname.Equals("WNNInfo.L0.Std.LearningMomentum")) txt_LearningMomentum.Text = pval;
                        if (pname.Equals("WNNInfo.L0.Qing.HCPbeta")) txt_Qing_HCPbeta.Text = pval;
                        if (pname.Equals("WNNInfo.L0.QProp.mu")) txt_Qprop_mu.Text = pval;
                        if (pname.Equals("WNNInfo.L0.RProp.d0")) txt_Rprop_d0.Text = pval;
                        if (pname.Equals("WNNInfo.L0.SCGD.maxK")) txt_SCGD_maxK.Text = pval;
                        if (pname.Equals("WNNInfo.L1.LevelRatios")) txt1_LevelRatios.Text = pval;
                        if (pname.Equals("WNNInfo.L1.UseContext")) cb1_UseContext.IsChecked = (pval.Equals("1"));
                        if (pname.Equals("WNNInfo.L1.TrainingBatchCount")) txt1_TrainingBatchCount.Text = pval;
                        if (pname.Equals("WNNInfo.L1.BP_Algo")) cbo1_BPAlgo.Text = pval.Substring(3);
                        if (pname.Equals("WNNInfo.L1.ActivationFunction")) cbo1_ActivationFunction.Text = pval.Substring(14);
                        if (pname.Equals("WNNInfo.L1.StopAtDivergence")) cb1_StopAtDivergence.IsChecked = (pval.Equals("1"));
                        if (pname.Equals("WNNInfo.L1.MaxEpochs")) txt1_MaxEpochs.Text = pval;
                        if (pname.Equals("WNNInfo.L1.TargetMSE")) txt1_TargetMSE.Text = pval;
                        if (pname.Equals("WNNInfo.L1.LearningRate")) txt1_LearningRate.Text = pval;
                        if (pname.Equals("WNNInfo.L1.Std.LearningMomentum")) txt1_LearningMomentum.Text = pval;
                        if (pname.Equals("WNNInfo.L1.Qing.HCPbeta")) txt1_Qing_HCPbeta.Text = pval;
                        if (pname.Equals("WNNInfo.L1.QProp.mu")) txt1_Qprop_mu.Text = pval;
                        if (pname.Equals("WNNInfo.L1.RProp.d0")) txt1_Rprop_d0.Text = pval;
                        if (pname.Equals("WNNInfo.L1.SCGD.maxK")) txt1_SCGD_maxK.Text = pval;
                    }
                    //-- XIE Engine Parameters
                    if (cbo_EngineType.Text.Equals("XIE")) {
                        if (pname.Equals("XIEInfo.SVM.DebugLevel")) txt_SVMDebugLevel.Text = pval;
                        if (pname.Equals("XIEInfo.SVM.C")) txt_C.Text = pval;
                        if (pname.Equals("XIEInfo.SVM.epsilon")) txt_epsilon.Text = pval;
                        if (pname.Equals("XIEInfo.SVM.IterToShrink")) txt_IterToShrink.Text = pval;
                        if (pname.Equals("XIEInfo.SVM.MaxEpochs")) txt_SVMMaxEpochs.Text = pval;
                        if (pname.Equals("XIEInfo.SVM.DebugLevel")) txt_SVMDebugLevel.Text = pval;
                        if (pname.Equals("XIEInfo.SVM.KernelType")) cbo_KernelType.Text = pval.Substring(12);
                        if (pname.Equals("XIEInfo.SVM.PolyDegree")) txt_PolyDegree.Text = pval;
                        if (pname.Equals("XIEInfo.SVM.RBFgamma")) txt_RBFgamma.Text = pval;
                        if (pname.Equals("XIEInfo.SVM.CoefLin")) txt_CoefLin.Text = pval;
                        if (pname.Equals("XIEInfo.SVM.CoefConst")) txt_CoefConst.Text = pval;
                        if (pname.Equals("XIEInfo.SVM.KernelCacheSize")) txt_KernelCacheSize.Text = pval;
                        if (pname.Equals("XIEInfo.SVM.SlackNorm")) cbo_SlackNorm.Text = pval.Substring(11);
                        if (pname.Equals("XIEInfo.SVM.RescalingMethod")) cbo_RescalingMethod.Text = pval.Substring(17);
                        if (pname.Equals("XIEInfo.SVM.LossFunction")) cbo_LossFunction.Text = pval.Substring(14);
                        if (pname.Equals("XIEInfo.SVM.LearningAlgo")) cbo_LearningAlgo.Text = pval.Substring(14);
                        if (pname.Equals("XIEInfo.SVM.NewConstrEtrain")) txt_NewConstrEtrain.Text = pval;
                        if (pname.Equals("XIEInfo.SVM.CCacheSize")) txt_CCacheSize.Text = pval;
                        if (pname.Equals("XIEInfo.SVM.BatchSize")) txt_BatchSize.Text = pval;
                        if (pname.Equals("XIEInfo.SVM.NewVarSinQP")) txt_NewVarSinQP.Text = pval;
                        if (pname.Equals("XIEInfo.SVM.CustomKernel")) txt_CustomKernel.Text = pval;
                        if (pname.Equals("XIEInfo.NN0.LevelRatios")) txt_LevelRatios.Text = pval;
                        if (pname.Equals("XIEInfo.NN0.UseContext")) cb_UseContext.IsChecked = (pval.Equals("1"));
                        if (pname.Equals("XIEInfo.NN0.TrainingBatchCount")) txt_TrainingBatchCount.Text = pval;
                        if (pname.Equals("XIEInfo.NN0.BP_Algo")) cbo_BPAlgo.Text = pval.Substring(3);
                        if (pname.Equals("XIEInfo.NN0.ActivationFunction")) cbo_ActivationFunction.Text = pval.Substring(14);
                        if (pname.Equals("XIEInfo.NN0.StopAtDivergence")) cb_StopAtDivergence.IsChecked = (pval.Equals("1"));
                        if (pname.Equals("XIEInfo.NN0.MaxEpochs")) txt_MaxEpochs.Text = pval;
                        if (pname.Equals("XIEInfo.NN0.TargetMSE")) txt_TargetMSE.Text = pval;
                        if (pname.Equals("XIEInfo.NN0.LearningRate")) txt_LearningRate.Text = pval;
                        if (pname.Equals("XIEInfo.NN0.Std.LearningMomentum")) txt_LearningMomentum.Text = pval;
                        if (pname.Equals("XIEInfo.NN0.Qing.HCPbeta")) txt_Qing_HCPbeta.Text = pval;
                        if (pname.Equals("XIEInfo.NN0.QProp.mu")) txt_Qprop_mu.Text = pval;
                        if (pname.Equals("XIEInfo.NN0.RProp.d0")) txt_Rprop_d0.Text = pval;
                        if (pname.Equals("XIEInfo.NN0.SCGD.maxK")) txt_SCGD_maxK.Text = pval;
                        if (pname.Equals("XIEInfo.NN1.LevelRatios")) txt1_LevelRatios.Text = pval;
                        if (pname.Equals("XIEInfo.NN1.UseContext")) cb1_UseContext.IsChecked = (pval.Equals("1"));
                        if (pname.Equals("XIEInfo.NN1.TrainingBatchCount")) txt1_TrainingBatchCount.Text = pval;
                        if (pname.Equals("XIEInfo.NN1.BP_Algo")) cbo1_BPAlgo.Text = pval.Substring(3);
                        if (pname.Equals("XIEInfo.NN1.ActivationFunction")) cbo1_ActivationFunction.Text = pval.Substring(14);
                        if (pname.Equals("XIEInfo.NN1.StopAtDivergence")) cb1_StopAtDivergence.IsChecked = (pval.Equals("1"));
                        if (pname.Equals("XIEInfo.NN1.MaxEpochs")) txt1_MaxEpochs.Text = pval;
                        if (pname.Equals("XIEInfo.NN1.TargetMSE")) txt1_TargetMSE.Text = pval;
                        if (pname.Equals("XIEInfo.NN1.LearningRate")) txt1_LearningRate.Text = pval;
                        if (pname.Equals("XIEInfo.NN1.Std.LearningMomentum")) txt1_LearningMomentum.Text = pval;
                        if (pname.Equals("XIEInfo.NN1.Qing.HCPbeta")) txt1_Qing_HCPbeta.Text = pval;
                        if (pname.Equals("XIEInfo.NN1.QProp.mu")) txt1_Qprop_mu.Text = pval;
                        if (pname.Equals("XIEInfo.NN1.RProp.d0")) txt1_Rprop_d0.Text = pval;
                        if (pname.Equals("XIEInfo.NN1.SCGD.maxK")) txt1_SCGD_maxK.Text = pval;
                    }
                }
            }

            return 0;
        }

        private void SaveIniFile() {
            string sParms="";
            sParms = sParms + "//-------------------------------//" + Environment.NewLine;
            sParms = sParms + "//-- Client General Parameters --//" + Environment.NewLine;
            sParms = sParms + "//-------------------------------//" + Environment.NewLine;
            sParms = sParms + "Tester.SimulationLength \t= " + txt_SimulationLength.Text + Environment.NewLine;
            sParms = sParms + "Tester.SimulationStart \t= " + txt_SimulationStart.Text + Environment.NewLine;
            sParms = sParms + "Tester.PauseAtEnd \t= " + ((cb_PauseAtEnd.IsChecked.Value)?"1":"0") + Environment.NewLine;
            sParms = sParms + "//-----------------------------------//" + Environment.NewLine;
            sParms = sParms + "//-- Forecaster General Parameters --//" + Environment.NewLine;
            sParms = sParms + "//-----------------------------------//" + Environment.NewLine;
            sParms = sParms + "Forecaster.Engine \t= ENGINE_" + cbo_EngineType.Text + Environment.NewLine;
            sParms = sParms + "Forecaster.Action \t= " + cbo_Action.Text + Environment.NewLine;
            sParms = sParms + "Forecaster.HaveFutureData \t= " + ((cb_HaveFutureData.IsChecked.Value)?"1":"0") + Environment.NewLine;
            sParms = sParms + "//---------------------------------------//" + Environment.NewLine;
            sParms = sParms + "//-- Saved Engine Retrieval Parameters --//" + Environment.NewLine;
            sParms = sParms + "//---------------------------------------//" + Environment.NewLine;
            sParms = sParms + "SavedEngine.ProcessId \t= " + txt_SavedEnginePid.Text + Environment.NewLine;
            sParms = sParms + "SavedEngine.ThreadId \t= " + txt_SavedEngineTid.Text + Environment.NewLine;
            sParms = sParms + "SavedEngine.DatasetId \t= " + txt_SavedEngineDSid.Text + Environment.NewLine;
            sParms = sParms + "//-----------------------------------//" + Environment.NewLine;
            sParms = sParms + "//-- Forecaster Results Parameters --//" + Environment.NewLine;
            sParms = sParms + "//-----------------------------------//" + Environment.NewLine;
            sParms = sParms + "Results.SaveNothing \t= " + ((cb_SaveNothing.IsChecked.Value) ? "1" : "0") + Environment.NewLine;
            sParms = sParms + "Results.SaveMSE \t= " + ((cb_SaveMSE.IsChecked.Value) ? "1" : "0") + Environment.NewLine;
            sParms = sParms + "Results.SaveRun \t= " + ((cb_SaveRun.IsChecked.Value) ? "1" : "0") + Environment.NewLine;
            sParms = sParms + "Results.SaveInternals \t= " + ((cb_SaveInternals.IsChecked.Value) ? "1" : "0") + Environment.NewLine;
            sParms = sParms + "Results.SaveImages \t= " + ((cb_SaveImages.IsChecked.Value) ? "1" : "0") + Environment.NewLine;
            sParms = sParms + "Results.Destination \t= LOG_TO_" + cbo_ResultsDest.Text + Environment.NewLine;
            sParms = sParms + "Results.DBUser \t= " + txt_ResultsDBUser.Text + Environment.NewLine;
            sParms = sParms + "Results.DBPassword \t= " + txt_ResultsDBPassword.Text + Environment.NewLine;
            sParms = sParms + "Results.DBConnString \t= " + txt_ResultsDBConnString.Text + Environment.NewLine;
            sParms = sParms + "//---------------------------------//" + Environment.NewLine;
            sParms = sParms + "//-- Forecaster Debug Parameters --//" + Environment.NewLine;
            sParms = sParms + "//---------------------------------//" + Environment.NewLine;
            sParms = sParms + "Forecaster.DebugLevel \t= " + txt_DebugLevel.Text + Environment.NewLine;
            sParms = sParms + "Forecaster.DebugFilePath \t= " + txt_DebugFilePath.Text + Environment.NewLine;
            sParms = sParms + "Forecaster.DebugFileName \t= " + txt_DebugFileName.Text + Environment.NewLine;
            sParms = sParms + "Forecaster.ThreadSafeLogging \t= " + ((cb_ThreadSafeLogging.IsChecked.Value) ? "1" : "0") + Environment.NewLine;
            sParms = sParms + "Forecaster.PauseOnError \t= " + ((cb_PauseOnError.IsChecked.Value) ? "1" : "0") + Environment.NewLine;
            sParms = sParms + "Forecaster.DumpSampleData \t= " + ((cb_DumpSampleData.IsChecked.Value) ? "1" : "0") + Environment.NewLine;
            sParms = sParms + "//---------------------------//" + Environment.NewLine;
            sParms = sParms + "//-- Data Shape Parameters --//" + Environment.NewLine;
            sParms = sParms + "//---------------------------//" + Environment.NewLine;
            sParms = sParms + "DataParms.HistoryLen \t= " + txt_HistoryLen.Text + Environment.NewLine;
            sParms = sParms + "DataParms.SampleLen \t= " + txt_SampleLen.Text + Environment.NewLine;
            sParms = sParms + "DataParms.PredictionLen \t= " + txt_PredictionLen.Text + Environment.NewLine;
            sParms = sParms + "//-----------------------------------//" + Environment.NewLine;
            sParms = sParms + "//-- Data PreProcessing Parameters --//" + Environment.NewLine;
            sParms = sParms + "//-----------------------------------//" + Environment.NewLine;
            sParms = sParms + "DataParms.ValidationShift \t= " + txt_ValidationShift.Text + Environment.NewLine;
            sParms = sParms + "DataParms.DataTransformation \t= " + cbo_DataTransformation.Text + Environment.NewLine;
            sParms = sParms + "DataParms.WiggleRoom \t= " + txt_WiggleRoom.Text + Environment.NewLine;
            sParms = sParms + "DataParms.UseTSFeatures \t= " + ((cb_UseTSF.IsChecked.Value) ? "1" : "0") + Environment.NewLine;
            sParms = sParms + "DataParms.TSFeatures \t= " + ((cb_TSFMean.IsChecked.Value) ? "TSF_MEAN, " : "") + ((cb_TSFMAD.IsChecked.Value) ? "TSF_MAD, " : "") + ((cb_TSFSHE.IsChecked.Value) ? "TSF_SHE, " : "") + ((cb_TSFTP.IsChecked.Value) ? "TSF_TURNINGPOINTS, " : "") + ((cb_TSFVariance.IsChecked.Value) ? "TSF_VARIANCE, " : "") + ((cb_TSFSkewness.IsChecked.Value) ? "TSF_SKEWNESS, " : "") + ((cb_TSFKurtosis.IsChecked.Value) ? "TSF_KURTOSIS, " : "") + ((cb_TSHistVol.IsChecked.Value) ? "TSF_HISTVOL, " : "");
            //if (cb_UseTSF.IsChecked.Value) {
                sParms = sParms.Remove(sParms.Length - 2);
                sParms = sParms + Environment.NewLine;
            //}
            sParms = sParms + "//----------------------------//" + Environment.NewLine;
            sParms = sParms + "//-- Data Source Parameters --//" + Environment.NewLine;
            sParms = sParms + "//----------------------------//" + Environment.NewLine;
            sParms = sParms + "DataSource.SourceType \t= " + ((rb_SOURCE_DATA_FROM_FILE.IsChecked.Value) ? "SOURCE_DATA_FROM_FILE" : "SOURCE_DATA_FROM_FXDB") + Environment.NewLine;
            sParms = sParms + "DataSource.DBConn.DBUser \t= " + txt_DBUser.Text + Environment.NewLine;
            sParms = sParms + "DataSource.DBConn.DBPassword \t= " + txt_DBPassword.Text + Environment.NewLine;
            sParms = sParms + "DataSource.DBConn.DBConnString \t= " + txt_DBConnString.Text + Environment.NewLine;
            sParms = sParms + "DataSource.Symbol \t= " + txt_Symbol.Text + Environment.NewLine;
            sParms = sParms + "DataSource.TimeFrame \t= " + cbo_TimeFrame.Text + Environment.NewLine;
            sParms = sParms + "DataSource.IsFilled \t= " + ((cb_IsFilled.IsChecked.Value) ? "1" : "0") + Environment.NewLine;
            sParms = sParms + "DataSource.BarDataTypes \t= " + ((cb_OPEN.IsChecked.Value) ? "OPEN, " : "") + ((cb_HIGH.IsChecked.Value) ? "HIGH, " : "") + ((cb_LOW.IsChecked.Value) ? "LOW, " : "") + ((cb_CLOSE.IsChecked.Value) ? "CLOSE, " : "") + ((cb_VOLUME.IsChecked.Value) ? "VOLUME, " : "");
            sParms = sParms.Remove(sParms.Length - 2); sParms = sParms + Environment.NewLine;
            sParms = sParms + "DataSource.FileName \t= " + txt_DataSource_FileName.Text + Environment.NewLine;
            sParms = sParms + "DataSource.TextFieldSeparator \t= " + cbo_TextFieldSeparator.Text + Environment.NewLine;
            sParms = sParms + "DataSource.FileDataSets \t= " + txt_FileDataSets.Text + Environment.NewLine;
            sParms = sParms + "DataSource.CalcFileDataBW \t= " + ((cb_CalcFileDataBW.IsChecked.Value) ? "1" : "0") + Environment.NewLine;
            sParms = sParms + "DataSource.DStoCalcBWFrom \t= " + txt_DStoCalcBWFrom.Text + Environment.NewLine;
            sParms = sParms + "//--------------------------//" + Environment.NewLine;
            sParms = sParms + "//-- NN Engine Parameters --//" + Environment.NewLine;
            sParms = sParms + "//--------------------------//" + Environment.NewLine;
            sParms = sParms + "NNInfo.LevelRatios \t= " + txt_LevelRatios.Text + Environment.NewLine;
            sParms = sParms + "NNInfo.UseContext \t= " + ((cb_UseContext.IsChecked.Value) ? "1" : "0") + Environment.NewLine;
            sParms = sParms + "NNInfo.TrainingBatchCount \t= " + txt_TrainingBatchCount.Text + Environment.NewLine;
            sParms = sParms + "NNInfo.BP_Algo \t= BP_" + cbo_BPAlgo.Text + Environment.NewLine;
            sParms = sParms + "NNInfo.ActivationFunction \t= NN_ACTIVATION_" + cbo_ActivationFunction.Text + Environment.NewLine;
            sParms = sParms + "NNInfo.StopAtDivergence \t= " + ((cb_StopAtDivergence.IsChecked.Value) ? "1" : "0") + Environment.NewLine;
            sParms = sParms + "NNInfo.MaxEpochs \t= " + txt_MaxEpochs.Text + Environment.NewLine;
            sParms = sParms + "NNInfo.TargetMSE \t= " + txt_TargetMSE.Text + Environment.NewLine;
            sParms = sParms + "NNInfo.LearningRate \t= " + txt_LearningRate.Text + Environment.NewLine;
            sParms = sParms + "NNInfo.Std.LearningMomentum \t= " + txt_LearningMomentum.Text + Environment.NewLine;
            sParms = sParms + "NNInfo.Qing.HCPbeta \t= " + txt_Qing_HCPbeta.Text + Environment.NewLine;
            sParms = sParms + "NNInfo.QProp.mu \t= " + txt_Qprop_mu.Text + Environment.NewLine;
            sParms = sParms + "NNInfo.RProp.d0 \t= " + txt_Rprop_d0.Text + Environment.NewLine;
            sParms = sParms + "NNInfo.SCGD.maxK \t= " + txt_SCGD_maxK.Text + Environment.NewLine;
            sParms = sParms + "//---------------------------//" + Environment.NewLine;
            sParms = sParms + "//-- SVM Engine Parameters --//" + Environment.NewLine;
            sParms = sParms + "//---------------------------//" + Environment.NewLine;
            sParms = sParms + "SVMInfo.DebugLevel \t= " + txt_SVMDebugLevel.Text + Environment.NewLine;
            sParms = sParms + "SVMInfo.C \t= " + txt_C.Text + Environment.NewLine;
            sParms = sParms + "SVMInfo.epsilon \t= " + txt_epsilon.Text + Environment.NewLine;
            sParms = sParms + "SVMInfo.IterToShrink \t= " + txt_IterToShrink.Text + Environment.NewLine;
            sParms = sParms + "SVMInfo.MaxEpochs \t= " + txt_SVMMaxEpochs.Text + Environment.NewLine;
            sParms = sParms + "SVMInfo.KernelType \t= KERNEL_TYPE_" + cbo_KernelType.Text + Environment.NewLine;
            sParms = sParms + "SVMInfo.PolyDegree \t= " + txt_PolyDegree.Text + Environment.NewLine;
            sParms = sParms + "SVMInfo.RBFgamma \t= " + txt_RBFgamma.Text + Environment.NewLine;
            sParms = sParms + "SVMInfo.CoefLin \t= " + txt_CoefLin.Text + Environment.NewLine;
            sParms = sParms + "SVMInfo.CoefConst \t= " + txt_CoefConst.Text + Environment.NewLine;
            sParms = sParms + "SVMInfo.KernelCacheSize \t= " + txt_KernelCacheSize.Text + Environment.NewLine;
            sParms = sParms + "SVMInfo.SlackNorm \t= SLACK_NORM_" + cbo_SlackNorm.Text + Environment.NewLine;
            sParms = sParms + "SVMInfo.RescalingMethod \t= RESCALING_METHOD_" + cbo_RescalingMethod.Text + Environment.NewLine;
            sParms = sParms + "SVMInfo.LossFunction \t= LOSS_FUNCTION_" + cbo_LossFunction.Text + Environment.NewLine;
            sParms = sParms + "SVMInfo.LearningAlgo \t= LEARNING_ALGO_" + cbo_LearningAlgo.Text + Environment.NewLine;
            sParms = sParms + "SVMInfo.NewConstrEtrain \t= " + txt_NewConstrEtrain.Text + Environment.NewLine;
            sParms = sParms + "SVMInfo.CCacheSize \t= " + txt_CCacheSize.Text + Environment.NewLine;
            sParms = sParms + "SVMInfo.BatchSize \t= " + txt_BatchSize.Text + Environment.NewLine;
            sParms = sParms + "SVMInfo.NewVarSinQP \t= " + txt_NewVarSinQP.Text + Environment.NewLine;
            sParms = sParms + "SVMInfo.CustomKernel \t= " + txt_CustomKernel.Text + Environment.NewLine;
            sParms = sParms + "//---------------------------//" + Environment.NewLine;
            sParms = sParms + "//-- WNN Engine Parameters --//" + Environment.NewLine;
            sParms = sParms + "//---------------------------//" + Environment.NewLine;
            sParms = sParms + "WNNInfo.DecompLevel \t= " + txt_DecompLevel.Text + Environment.NewLine;
            sParms = sParms + "WNNInfo.WaveletType \t= " + cbo_WaveletType.Text + Environment.NewLine;
            sParms = sParms + "WNNInfo.L0.LevelRatios \t= " + txt_LevelRatios.Text + Environment.NewLine;
            sParms = sParms + "WNNInfo.L0.UseContext \t= " + ((cb_UseContext.IsChecked.Value) ? "1" : "0") + Environment.NewLine;
            sParms = sParms + "WNNInfo.L0.TrainingBatchCount \t= " + txt_TrainingBatchCount.Text + Environment.NewLine;
            sParms = sParms + "WNNInfo.L0.BP_Algo \t= BP_" + cbo_BPAlgo.Text + Environment.NewLine;
            sParms = sParms + "WNNInfo.L0.ActivationFunction \t= NN_ACTIVATION_" + cbo_ActivationFunction.Text + Environment.NewLine;
            sParms = sParms + "WNNInfo.L0.StopAtDivergence \t= " + ((cb_StopAtDivergence.IsChecked.Value) ? "1" : "0") + Environment.NewLine;
            sParms = sParms + "WNNInfo.L0.MaxEpochs \t= " + txt_MaxEpochs.Text + Environment.NewLine;
            sParms = sParms + "WNNInfo.L0.TargetMSE \t= " + txt_TargetMSE.Text + Environment.NewLine;
            sParms = sParms + "WNNInfo.L0.LearningRate \t= " + txt_LearningRate.Text + Environment.NewLine;
            sParms = sParms + "WNNInfo.L0.Std.LearningMomentum \t= " + txt_LearningMomentum.Text + Environment.NewLine;
            sParms = sParms + "WNNInfo.L0.Qing.HCPbeta \t= " + txt_Qing_HCPbeta.Text + Environment.NewLine;
            sParms = sParms + "WNNInfo.L0.QProp.mu \t= " + txt_Qprop_mu.Text + Environment.NewLine;
            sParms = sParms + "WNNInfo.L0.RProp.d0 \t= " + txt_Rprop_d0.Text + Environment.NewLine;
            sParms = sParms + "WNNInfo.L0.SCGD.maxK \t= " + txt_SCGD_maxK.Text + Environment.NewLine;
            sParms = sParms + "WNNInfo.L1.LevelRatios \t= " + txt1_LevelRatios.Text + Environment.NewLine;
            sParms = sParms + "WNNInfo.L1.UseContext \t= " + ((cb1_UseContext.IsChecked.Value) ? "1" : "0") + Environment.NewLine;
            sParms = sParms + "WNNInfo.L1.TrainingBatchCount \t= " + txt1_TrainingBatchCount.Text + Environment.NewLine;
            sParms = sParms + "WNNInfo.L1.BP_Algo \t= BP_" + cbo1_BPAlgo.Text + Environment.NewLine;
            sParms = sParms + "WNNInfo.L1.ActivationFunction \t= NN_ACTIVATION_" + cbo1_ActivationFunction.Text + Environment.NewLine;
            sParms = sParms + "WNNInfo.L1.StopAtDivergence \t= " + ((cb1_StopAtDivergence.IsChecked.Value) ? "1" : "0") + Environment.NewLine;
            sParms = sParms + "WNNInfo.L1.MaxEpochs \t= " + txt1_MaxEpochs.Text + Environment.NewLine;
            sParms = sParms + "WNNInfo.L1.TargetMSE \t= " + txt1_TargetMSE.Text + Environment.NewLine;
            sParms = sParms + "WNNInfo.L1.LearningRate \t= " + txt1_LearningRate.Text + Environment.NewLine;
            sParms = sParms + "WNNInfo.L1.Std.LearningMomentum \t= " + txt1_LearningMomentum.Text + Environment.NewLine;
            sParms = sParms + "WNNInfo.L1.Qing.HCPbeta \t= " + txt1_Qing_HCPbeta.Text + Environment.NewLine;
            sParms = sParms + "WNNInfo.L1.QProp.mu \t= " + txt1_Qprop_mu.Text + Environment.NewLine;
            sParms = sParms + "WNNInfo.L1.RProp.d0 \t= " + txt1_Rprop_d0.Text + Environment.NewLine;
            sParms = sParms + "WNNInfo.L1.SCGD.maxK \t= " + txt1_SCGD_maxK.Text + Environment.NewLine;
            sParms = sParms + "//---------------------------//" + Environment.NewLine;
            sParms = sParms + "//-- XIE Engine Parameters --//" + Environment.NewLine;
            sParms = sParms + "//---------------------------//" + Environment.NewLine;
            sParms = sParms + "XIEInfo.SVM.DebugLevel \t= " + txt_SVMDebugLevel.Text + Environment.NewLine;
            sParms = sParms + "XIEInfo.SVM.C \t= " + txt_C.Text + Environment.NewLine;
            sParms = sParms + "XIEInfo.SVM.epsilon \t= " + txt_epsilon.Text + Environment.NewLine;
            sParms = sParms + "XIEInfo.SVM.IterToShrink \t= " + txt_IterToShrink.Text + Environment.NewLine;
            sParms = sParms + "XIEInfo.SVM.MaxEpochs \t= " + txt_SVMMaxEpochs.Text + Environment.NewLine;
            sParms = sParms + "XIEInfo.SVM.KernelType \t= KERNEL_TYPE_" + cbo_KernelType.Text + Environment.NewLine;
            sParms = sParms + "XIEInfo.SVM.PolyDegree \t= " + txt_PolyDegree.Text + Environment.NewLine;
            sParms = sParms + "XIEInfo.SVM.RBFgamma \t= " + txt_RBFgamma.Text + Environment.NewLine;
            sParms = sParms + "XIEInfo.SVM.CoefLin \t= " + txt_CoefLin.Text + Environment.NewLine;
            sParms = sParms + "XIEInfo.SVM.CoefConst \t= " + txt_CoefConst.Text + Environment.NewLine;
            sParms = sParms + "XIEInfo.SVM.KernelCacheSize \t= " + txt_KernelCacheSize.Text + Environment.NewLine;
            sParms = sParms + "XIEInfo.SVM.SlackNorm \t= SLACK_NORM_" + cbo_SlackNorm.Text + Environment.NewLine;
            sParms = sParms + "XIEInfo.SVM.RescalingMethod \t= RESCALING_METHOD_" + cbo_RescalingMethod.Text + Environment.NewLine;
            sParms = sParms + "XIEInfo.SVM.LossFunction \t= LOSS_FUNCTION_" + cbo_LossFunction.Text + Environment.NewLine;
            sParms = sParms + "XIEInfo.SVM.LearningAlgo \t= LEARNING_ALGO_" + cbo_LearningAlgo.Text + Environment.NewLine;
            sParms = sParms + "XIEInfo.SVM.NewConstrEtrain \t= " + txt_NewConstrEtrain.Text + Environment.NewLine;
            sParms = sParms + "XIEInfo.SVM.CCacheSize \t= " + txt_CCacheSize.Text + Environment.NewLine;
            sParms = sParms + "XIEInfo.SVM.BatchSize \t= " + txt_BatchSize.Text + Environment.NewLine;
            sParms = sParms + "XIEInfo.SVM.NewVarSinQP \t= " + txt_NewVarSinQP.Text + Environment.NewLine;
            sParms = sParms + "XIEInfo.SVM.CustomKernel \t= " + txt_CustomKernel.Text + Environment.NewLine;
            sParms = sParms + "XIEInfo.NN0.LevelRatios \t= " + txt_LevelRatios.Text + Environment.NewLine;
            sParms = sParms + "XIEInfo.NN0.UseContext \t= " + ((cb_UseContext.IsChecked.Value) ? "1" : "0") + Environment.NewLine;
            sParms = sParms + "XIEInfo.NN0.TrainingBatchCount \t= " + txt_TrainingBatchCount.Text + Environment.NewLine;
            sParms = sParms + "XIEInfo.NN0.BP_Algo \t= BP_" + cbo_BPAlgo.Text + Environment.NewLine;
            sParms = sParms + "XIEInfo.NN0.ActivationFunction \t= NN_ACTIVATION_" + cbo_ActivationFunction.Text + Environment.NewLine;
            sParms = sParms + "XIEInfo.NN0.StopAtDivergence \t= " + ((cb_StopAtDivergence.IsChecked.Value) ? "1" : "0") + Environment.NewLine;
            sParms = sParms + "XIEInfo.NN0.MaxEpochs \t= " + txt_MaxEpochs.Text + Environment.NewLine;
            sParms = sParms + "XIEInfo.NN0.TargetMSE \t= " + txt_TargetMSE.Text + Environment.NewLine;
            sParms = sParms + "XIEInfo.NN0.LearningRate \t= " + txt_LearningRate.Text + Environment.NewLine;
            sParms = sParms + "XIEInfo.NN0.Std.LearningMomentum \t= " + txt_LearningMomentum.Text + Environment.NewLine;
            sParms = sParms + "XIEInfo.NN0.Qing.HCPbeta \t= " + txt_Qing_HCPbeta.Text + Environment.NewLine;
            sParms = sParms + "XIEInfo.NN0.QProp.mu \t= " + txt_Qprop_mu.Text + Environment.NewLine;
            sParms = sParms + "XIEInfo.NN0.RProp.d0 \t= " + txt_Rprop_d0.Text + Environment.NewLine;
            sParms = sParms + "XIEInfo.NN0.SCGD.maxK \t= " + txt_SCGD_maxK.Text + Environment.NewLine;
            sParms = sParms + "XIEInfo.NN1.LevelRatios \t= " + txt1_LevelRatios.Text + Environment.NewLine;
            sParms = sParms + "XIEInfo.NN1.UseContext \t= " + ((cb1_UseContext.IsChecked.Value) ? "1" : "0") + Environment.NewLine;
            sParms = sParms + "XIEInfo.NN1.TrainingBatchCount \t= " + txt1_TrainingBatchCount.Text + Environment.NewLine;
            sParms = sParms + "XIEInfo.NN1.BP_Algo \t= BP_" + cbo1_BPAlgo.Text + Environment.NewLine;
            sParms = sParms + "XIEInfo.NN1.ActivationFunction \t= NN_ACTIVATION_" + cbo1_ActivationFunction.Text + Environment.NewLine;
            sParms = sParms + "XIEInfo.NN1.StopAtDivergence \t= " + ((cb1_StopAtDivergence.IsChecked.Value) ? "1" : "0") + Environment.NewLine;
            sParms = sParms + "XIEInfo.NN1.MaxEpochs \t= " + txt1_MaxEpochs.Text + Environment.NewLine;
            sParms = sParms + "XIEInfo.NN1.TargetMSE \t= " + txt1_TargetMSE.Text + Environment.NewLine;
            sParms = sParms + "XIEInfo.NN1.LearningRate \t= " + txt1_LearningRate.Text + Environment.NewLine;
            sParms = sParms + "XIEInfo.NN1.Std.LearningMomentum \t= " + txt1_LearningMomentum.Text + Environment.NewLine;
            sParms = sParms + "XIEInfo.NN1.Qing.HCPbeta \t= " + txt1_Qing_HCPbeta.Text + Environment.NewLine;
            sParms = sParms + "XIEInfo.NN1.QProp.mu \t= " + txt1_Qprop_mu.Text + Environment.NewLine;
            sParms = sParms + "XIEInfo.NN1.RProp.d0 \t= " + txt1_Rprop_d0.Text + Environment.NewLine;
            sParms = sParms + "XIEInfo.NN1.SCGD.maxK \t= " + txt1_SCGD_maxK.Text + Environment.NewLine;

            File.WriteAllText(txt_IniFile.Text, sParms);
            //-- also, save name of last-saved ini file in "LastParmsFile.ini", in current directory
            File.WriteAllText("LastParmsFile.ini", txt_IniFile.Text);
        }

        private void DrawWNNLayout() {
            if (txt_DecompLevel.Text.Length == 0) return;

            int DecompLevel = Convert.ToInt32(txt_DecompLevel.Text);
            double vdist = (brd_EngineLayout.Height -50-2)/DecompLevel;
            double y;
            TextBlock tb0, tb1, tb2, tb3;

            cnv_WNNLayout.Children.Clear();

            //-- Labels
            System.Windows.Controls.Label l0 = new System.Windows.Controls.Label();
            l0.FontSize = 12; l0.Height = 25; l0.VerticalAlignment = VerticalAlignment.Top;
            Canvas.SetLeft(l0, 20);
            cnv_WNNLayout.Children.Add(l0);
            System.Windows.Controls.Label l1 = new System.Windows.Controls.Label();
            l1.FontSize = 12; l1.Height = 25; l1.VerticalAlignment = VerticalAlignment.Top;
            Canvas.SetLeft(l1, 160);
            cnv_WNNLayout.Children.Add(l1);

            //-- L0 cores
            for (int i=0; i<(DecompLevel+1); i++) {

                Ellipse e = new Ellipse();
                e.Width = 70; e.Height = 50; e.Stroke = Brushes.Black; e.Fill = Brushes.LightGray;
                y = i * vdist;
                Canvas.SetLeft(e, 10);
                Canvas.SetTop(e, y);
                cnv_WNNLayout.Children.Add(e);

                tb0 = new TextBlock(); tb1 = new TextBlock();
                tb0.Text = "Core 0:" + i.ToString(); tb1.Text = "NN";
                Canvas.SetLeft(tb0, 25); Canvas.SetLeft(tb1, 35);
                Canvas.SetTop(tb0, y + 15); Canvas.SetTop(tb1, y + 25);
                cnv_WNNLayout.Children.Add(tb0); cnv_WNNLayout.Children.Add(tb1);

            }

            //-- L1 cores
            Ellipse e1 = new Ellipse();
            e1.Width = 70; e1.Height = 50; e1.Stroke = Brushes.Black; e1.Fill = Brushes.LightGray;
            Canvas.SetLeft(e1, 150); Canvas.SetTop(e1, 45);
            cnv_WNNLayout.Children.Add(e1);

            tb2 = new TextBlock(); tb3 = new TextBlock();
            tb2.Text = "Core 1:0"; tb3.Text = "NN";
            Canvas.SetLeft(tb2, 165); Canvas.SetLeft(tb3, 180);
            Canvas.SetTop(tb2, 60); Canvas.SetTop(tb3, 75);
            cnv_WNNLayout.Children.Add(tb2); cnv_WNNLayout.Children.Add(tb3);

        }

        private void rb_SOURCE_DATA_FROM_FXDB_Checked(object sender, RoutedEventArgs e) {
            if (brd_TxtDataSourceProperties != null) brd_TxtDataSourceProperties.Visibility = Visibility.Hidden;
            if (brd_DBDataSourceProperties != null)  brd_DBDataSourceProperties.Visibility = Visibility.Visible;
        }

        private void rb_SOURCE_DATA_FROM_FILE_Checked(object sender, RoutedEventArgs e) {
            if (brd_TxtDataSourceProperties != null) brd_TxtDataSourceProperties.Visibility = Visibility.Visible;
            if (brd_DBDataSourceProperties != null) brd_DBDataSourceProperties.Visibility = Visibility.Hidden;
            
        }

        private void btn_DataSourceFileName_Click(object sender, RoutedEventArgs e)
        {
            var fileDialog = new System.Windows.Forms.OpenFileDialog();
            var result = fileDialog.ShowDialog();
            switch (result)
            {
                case System.Windows.Forms.DialogResult.OK:
                    var file = fileDialog.FileName;
                    txt_DataSource_FileName.Text = file;
                    txt_DataSource_FileName.ToolTip = file;
                    break;
                case System.Windows.Forms.DialogResult.Cancel:
                default:
                    txt_DataSource_FileName.Text = null;
                    txt_DataSource_FileName.ToolTip = null;
                    break;
            }
        }

        private void cbo_Action_SelectionChanged(object sender, SelectionChangedEventArgs e)
        {
            if(cnv_SavedEngine != null) cnv_SavedEngine.Visibility = (cbo_Action.SelectedIndex == 0)?Visibility.Hidden:Visibility.Visible;
        }

        private void cbo_BPAlgo_SelectionChanged(object sender, SelectionChangedEventArgs e) {
            switch (cbo_BPAlgo.SelectedIndex) {
                case DEF.NN.BP_STD:
                    if(cnv_LearningRate!=null) cnv_LearningRate.Visibility = Visibility.Visible;
                    if(cnv_LearningMomentum!=null) cnv_LearningMomentum.Visibility = Visibility.Visible;
                    if(cnv_Qing_HCPbeta!=null) cnv_Qing_HCPbeta.Visibility = Visibility.Hidden;
                    if(cnv_QProp_mu!=null) cnv_QProp_mu.Visibility = Visibility.Hidden;
                    if(cnv_RProp_d0!=null) cnv_RProp_d0.Visibility = Visibility.Hidden;
                    if(cnv_SCGD_maxK!=null) cnv_SCGD_maxK.Visibility = Visibility.Hidden;
                    break;
                case DEF.NN.BP_QING:
                    cnv_LearningRate.Visibility = Visibility.Visible;
                    cnv_LearningMomentum.Visibility = Visibility.Hidden;
                    cnv_Qing_HCPbeta.Visibility = Visibility.Visible;
                    cnv_QProp_mu.Visibility = Visibility.Hidden;
                    cnv_RProp_d0.Visibility = Visibility.Hidden;
                    cnv_SCGD_maxK.Visibility = Visibility.Hidden;
                    break;
                case DEF.NN.BP_SCGD:
                    cnv_LearningRate.Visibility = Visibility.Hidden;
                    cnv_LearningMomentum.Visibility = Visibility.Hidden;
                    cnv_Qing_HCPbeta.Visibility = Visibility.Hidden;
                    cnv_QProp_mu.Visibility = Visibility.Hidden;
                    cnv_RProp_d0.Visibility = Visibility.Hidden;
                    cnv_SCGD_maxK.Visibility = Visibility.Visible;
                    break;
                case DEF.NN.BP_LM:
                    break;
                case DEF.NN.BP_QUICKPROP:
                    cnv_LearningRate.Visibility = Visibility.Visible;
                    cnv_LearningMomentum.Visibility = Visibility.Hidden;
                    cnv_Qing_HCPbeta.Visibility = Visibility.Hidden;
                    cnv_QProp_mu.Visibility = Visibility.Visible;
                    cnv_RProp_d0.Visibility = Visibility.Hidden;
                    cnv_SCGD_maxK.Visibility = Visibility.Hidden;
                    break;
                case DEF.NN.BP_RPROP:
                    cnv_LearningRate.Visibility = Visibility.Visible;
                    cnv_LearningMomentum.Visibility = Visibility.Hidden;
                    cnv_Qing_HCPbeta.Visibility = Visibility.Hidden;
                    cnv_QProp_mu.Visibility = Visibility.Hidden;
                    cnv_RProp_d0.Visibility = Visibility.Visible;
                    cnv_SCGD_maxK.Visibility = Visibility.Hidden;
                    break;
            }
        }

        private void cbo_EngineType_SelectionChanged(object sender, SelectionChangedEventArgs e) {
            System.Windows.Controls.ComboBoxItem selItem = (System.Windows.Controls.ComboBoxItem)cbo_EngineType.SelectedItem;
            if (selItem == null) return;

            String engineDesc = selItem.Content.ToString();

            if (cnv_SingleEngineLayout == null) return;

            //if (lbl_Conf != null) lbl_Conf.Content = engineDesc + " Configuration";

            //-- Show/Hide additional WNN engine paramenters
            if (engineDesc.Equals("WNN")) {
                if (cnv_Wavelet != null) cnv_Wavelet.Visibility = Visibility.Visible;
            } else { 
                if (cnv_Wavelet != null) cnv_Wavelet.Visibility = Visibility.Hidden;
            }

            //-- Draw Engine Layout
            if (engineDesc.Equals("WNN")) {
                cnv_SingleEngineLayout.Visibility = Visibility.Hidden;
                cnv_WNNLayout.Visibility = Visibility.Visible;
                cnv_XIELayout.Visibility = Visibility.Hidden;
                DrawWNNLayout();
            } else if (engineDesc.Equals("XIE")) {
                cnv_SingleEngineLayout.Visibility = Visibility.Hidden;
                cnv_WNNLayout.Visibility = Visibility.Hidden;
                cnv_XIELayout.Visibility = Visibility.Visible;
            } else {
                cnv_SingleEngineLayout.Visibility = Visibility.Visible;
                cnv_WNNLayout.Visibility = Visibility.Hidden;
                cnv_XIELayout.Visibility = Visibility.Hidden;

                tb_EngineCoreTpe.Text = engineDesc;
            }

            //-- Show/Hide appropriate Cores configuration parameters
            switch (cbo_EngineType.SelectedIndex) {
                case 0: // NN
                    brd_NNParms.Visibility = Visibility.Visible;
                    brd_NNParms.HorizontalAlignment = System.Windows.HorizontalAlignment.Center;
                    brd_SVMParms.Visibility = Visibility.Hidden;
                    brd_SOMParms.Visibility = Visibility.Hidden;
                    brd_NN1Parms.Visibility = Visibility.Hidden;
                    break;
                case 1: // GA
                    break;
                case 2: // SVM
                    brd_SVMParms.Visibility = Visibility.Visible;
                    brd_SVMParms.HorizontalAlignment = System.Windows.HorizontalAlignment.Center;
                    brd_SOMParms.Visibility = Visibility.Hidden;
                    brd_NNParms.Visibility = Visibility.Hidden;
                    brd_NN1Parms.Visibility = Visibility.Hidden;
                    break;
                case 3: // SOM
                    brd_SOMParms.Visibility = Visibility.Visible;
                    brd_SOMParms.HorizontalAlignment = System.Windows.HorizontalAlignment.Center;
                    brd_SVMParms.Visibility = Visibility.Hidden;
                    brd_NNParms.Visibility = Visibility.Hidden;
                    brd_NN1Parms.Visibility = Visibility.Hidden;
                    break;
                case 4: // WNN
                    brd_NNParms.Visibility = Visibility.Visible;
                    brd_NNParms.HorizontalAlignment = System.Windows.HorizontalAlignment.Left;
                    brd_SVMParms.Visibility = Visibility.Hidden;
                    brd_SOMParms.Visibility = Visibility.Hidden;
                    brd_NN1Parms.Visibility = Visibility.Visible;
                    brd_NN1Parms.HorizontalAlignment = System.Windows.HorizontalAlignment.Right;
                    break;
                case 5: // XIE
                    brd_NNParms.Visibility = Visibility.Visible;
                    brd_NNParms.HorizontalAlignment = System.Windows.HorizontalAlignment.Center;
                    brd_SVMParms.Visibility = Visibility.Visible;
                    brd_SVMParms.HorizontalAlignment = System.Windows.HorizontalAlignment.Left;
                    brd_SOMParms.Visibility = Visibility.Hidden;
                    brd_NN1Parms.Visibility = Visibility.Visible;
                    brd_NN1Parms.HorizontalAlignment = System.Windows.HorizontalAlignment.Right;
                    break;
            }
        }

        private void cbo_KernelType_SelectionChanged(object sender, SelectionChangedEventArgs e) {
            if (cnv_PolyDegree != null) {
                System.Windows.Controls.ComboBoxItem selItem = (System.Windows.Controls.ComboBoxItem)cbo_KernelType.SelectedItem;
                if (selItem == null) return;
                if (selItem.Content.ToString().CompareTo("RBF") == 0) {
                    cnv_PolyDegree.Visibility = Visibility.Hidden;
                    cnv_RBFGamma.Visibility = Visibility.Visible;
                } else {
                    cnv_PolyDegree.Visibility = Visibility.Visible;
                    cnv_RBFGamma.Visibility = Visibility.Hidden;
                }
            }
        }

        private void btn_DebugFilePath_Click(object sender, RoutedEventArgs e)
        {
            var pathDialog = new System.Windows.Forms.FolderBrowserDialog();
            var result = pathDialog.ShowDialog();
            switch (result)
            {
                case System.Windows.Forms.DialogResult.OK:
                    var path = pathDialog.SelectedPath;
                    txt_DebugFilePath.Text = path;
                    txt_DebugFilePath.ToolTip = path;
                    break;
                case System.Windows.Forms.DialogResult.Cancel:
                default:
                    txt_DebugFilePath.Text = null;
                    txt_DebugFilePath.ToolTip = null;
                    break;
            }
        }

        private void btn_IniFile_Click(object sender, RoutedEventArgs e)
        {
            var fileDialog = new System.Windows.Forms.OpenFileDialog();
            var result = fileDialog.ShowDialog();
            switch (result)
            {
                case System.Windows.Forms.DialogResult.OK:
                    var file = fileDialog.FileName;
                    txt_IniFile.Text = file;
                    txt_IniFile.ToolTip = file;
                    break;
                case System.Windows.Forms.DialogResult.Cancel:
                default:
                    txt_IniFile.Text = null;
                    txt_IniFile.ToolTip = null;
                    break;
            }
        }

        private void btn_fftlibdir_Click(object sender, RoutedEventArgs e)
        {
            var fileDialog = new System.Windows.Forms.OpenFileDialog();
            var result = fileDialog.ShowDialog();
            switch (result)
            {
                case System.Windows.Forms.DialogResult.OK:
                    var file = fileDialog.FileName;
                    txt_fftlibdir.Text = file;
                    txt_fftlibdir.ToolTip = file;
                    break;
                case System.Windows.Forms.DialogResult.Cancel:
                default:
                    txt_fftlibdir.Text = null;
                    txt_fftlibdir.ToolTip = null;
                    break;
            }
        }

        private void cb_SaveNothing_Checked(object sender, RoutedEventArgs e) {
            if (cb_SaveNothing != null) {
                cb_SaveMSE.IsEnabled = false;
                cb_SaveRun.IsEnabled = false;
                cb_SaveInternals.IsEnabled = false;
                cb_SaveImages.IsEnabled = false;
            }
        }

        private void cb_SaveNothing_UnChecked(object sender, RoutedEventArgs e) {
            if (cb_SaveNothing != null) {
                cb_SaveMSE.IsEnabled = true;
                cb_SaveRun.IsEnabled = true;
                cb_SaveInternals.IsEnabled = true;
                cb_SaveImages.IsEnabled = true;
            }
        }

        private void cbo_ResultsDest_SelectionChanged(object sender, SelectionChangedEventArgs e) {
            if (cnv_ResultsDB != null) {
                if (cbo_ResultsDest.SelectedIndex == 0) {
                    cnv_ResultsDB.Visibility = Visibility.Visible;
                } else {
                    cnv_ResultsDB.Visibility = Visibility.Hidden;
                }
            }
        }

        private void txt_DecompLevel_TextChanged(object sender, TextChangedEventArgs e) {
            if(txt_DecompLevel!=null && brd_EngineLayout!=null) DrawWNNLayout();
        }

        private void cb_UseTSF_Checked(object sender, RoutedEventArgs e) {
            if (cnv_TSF != null) cnv_TSF.Visibility = (cb_UseTSF.IsChecked.Value)?Visibility.Visible:Visibility.Hidden;
        }
        private void cb_UseTSF_Unchecked(object sender, RoutedEventArgs e)
        {
            if (cnv_TSF != null) cnv_TSF.Visibility = (cb_UseTSF.IsChecked.Value) ? Visibility.Visible : Visibility.Hidden;
        }

        private void cbo_TDFunction_SelectionChanged(object sender, SelectionChangedEventArgs e)
        {

        }

        private void btn_Go_Click(object sender, RoutedEventArgs e) {
            SaveIniFile();
            string exepath = System.AppDomain.CurrentDomain.BaseDirectory + "Tester.exe";

            string newPath = txt_fftlibdir.Text + ";" + Environment.GetEnvironmentVariable("PATH");
            Environment.SetEnvironmentVariable("PATH", newPath);
            Process.Start(exepath, (" --IniFile=" + App.LastIniFile));
        }

        private void btn_Load_Click(object sender, RoutedEventArgs e) {
            LoadIniFile(App.LastIniFile);
        }
    }
}

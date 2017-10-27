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

namespace MyGUI
{
    /// <summary>
    /// Interaction logic for MainWindow.xaml
    /// </summary>
    /// 
    public partial class MainWindow : Window
    {
        public int SourceType;

        public MainWindow()
        {
            InitializeComponent();
        }

        private void frame_Navigated(object sender, NavigationEventArgs e)
        {

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
                if (selItem.Content.ToString().CompareTo("RBF") == 0) {
                    cnv_PolyDegree.Visibility = Visibility.Hidden;
                    cnv_RBFGamma.Visibility = Visibility.Visible;
                } else {
                    cnv_PolyDegree.Visibility = Visibility.Visible;
                    cnv_RBFGamma.Visibility = Visibility.Hidden;
                }
            }
        }

        private void btn_DebugFile_Click(object sender, RoutedEventArgs e) {
            var fileDialog = new System.Windows.Forms.OpenFileDialog();
            var result = fileDialog.ShowDialog();
            switch (result) {
                case System.Windows.Forms.DialogResult.OK:
                    var file = fileDialog.FileName;
                    txt_DebugFile.Text = file;
                    txt_DebugFile.ToolTip = file;
                    break;
                case System.Windows.Forms.DialogResult.Cancel:
                default:
                    txt_DebugFile.Text = null;
                    txt_DebugFile.ToolTip = null;
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

        private void cb_UseTSF_Checked(object sender, RoutedEventArgs e)
        {
            if (cnv_TSF != null) cnv_TSF.Visibility = (cb_UseTSF.IsChecked.Value)?Visibility.Visible:Visibility.Hidden;
        }
        private void cb_UseTSF_Unchecked(object sender, RoutedEventArgs e)
        {
            if (cnv_TSF != null) cnv_TSF.Visibility = (cb_UseTSF.IsChecked.Value) ? Visibility.Visible : Visibility.Hidden;
        }

        private void cbo_TDFunction_SelectionChanged(object sender, SelectionChangedEventArgs e)
        {

        }
    }
}

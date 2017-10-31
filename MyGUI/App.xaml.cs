using System;
using System.Collections.Generic;
using System.Configuration;
using System.Data;
using System.Linq;
using System.Threading.Tasks;
using System.Windows;
using System.Runtime.InteropServices;
using System.IO;

namespace MyGUI
{
    /// <summary>
    /// Interaction logic for App.xaml
    /// </summary>
    /// 

    public class MyUtils
    {
        [DllImport("MyUtils.dll")]
        public static extern int MyRndInt(int fromn, int ton);
    }

    // implementation of C/C++ include files
    public static class DEF
    {
        public static class NN { 
            public const int BP_STD         = 0;
            public const int BP_QING        = 1;
            public const int BP_RPROP       = 2;
            public const int BP_QUICKPROP   = 3;
            public const int BP_SCGD        = 4;
            public const int BP_LM          = 5;
        }
    }

    public partial class App : Application
    {

        //int rnd = MyUtils.MyRndInt(1, 10);
        //int kaz = 0;


        //-- inizialize parameters from existing .ini file. The name of that will be in "LastParmsFile.ini" in current directory
         public static string LastIniFile = File.ReadAllText("LastParmsFile.ini");

    }
}

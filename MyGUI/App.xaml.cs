using System;
using System.Collections.Generic;
using System.Configuration;
using System.Data;
using System.Linq;
using System.Threading.Tasks;
using System.Windows;

namespace MyGUI
{
    /// <summary>
    /// Interaction logic for App.xaml
    /// </summary>
    /// 

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
    }
}

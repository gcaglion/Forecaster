// stdafx.h : include file for standard system include files,
// or project specific include files that are used frequently, but
// are changed infrequently
//

#pragma once

#include "targetver.h"

#define WIN32_LEAN_AND_MEAN             // Exclude rarely-used stuff from Windows headers
// Windows Header Files:
#include <stdlib.h>
#include <windows.h>
#include <math.h>


// TODO: reference additional headers your program requires here

//-- definitions
#include <MyEnums.h>
#include <DataShape.h>
#include <MyLogDefs.h>
#include <FXData.h>
#include <MyEngines.h>
#include <MyUtils.h>
#include <MyMatrix.h>
//-- libraries
#include <MyOraUtils.h>	// only needed to call OraDisconnect() at the end of MTgetForecast()
#include <MyTimeSeries.h>
#include <MyLogger.h>
#include <MyNN.h>
#include <MyWNN.h>
#include <MyGA.h>
#include <MySOM.h>
#include <MySVM.h>
#include <MyXIE.h>
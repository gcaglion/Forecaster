// stdafx.h : include file for standard system include files,
// or project specific include files that are used frequently, but
// are changed infrequently
//

#pragma once


#include "targetver.h"

#define WIN32_LEAN_AND_MEAN             // Exclude rarely-used stuff from Windows headers
// Windows Header Files:
#include <windows.h>
#include <stdlib.h>

// TODO: reference additional headers your program requires here
#include <MyLogDefs.h>
#include <DBConnection.h>
#include <FileData.h>
#include <FXData.h>
#include <MyTimeSeries.h>
#include <MyEnums.h>	// Need this for Log Destination
#include <MyUtils.h>

// Engines
#include <MyNN.h>	// temporary, to allow saveinternalsdata
#include <MyWNN.h>	// temporary, to allow saveinternalsdata
#include <MyGA.h>	// temporary, to allow saveinternalsdata
#include <MySOM.h>	// temporary, to allow saveinternalsdata
#include <MySVM.h>	// temporary, to allow saveinternalsdata

// Oracle Utilities
#ifndef _NO_ORCL
#include <MyOraUtils.h>
#endif

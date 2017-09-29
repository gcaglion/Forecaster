#pragma once
#include <MyUtils.h>
#include <DataShape.h>
#include <FXData.h>
#include <FileData.h>
#include <Tester.h>
#include <MyEngines.h>
#include <MyNN.h>
#include <TSF.h>
#include <MySOM.h>
#include <MySVM.h>
#include <MyParamMgr.h>

#define MAXPARAMDESCLEN 20	// Max length for comma-separated lists of descriptions
#define ARRAY_PARAMETER_MAX_LEN	100

#define enumlist true

//-- Forecaster Actions
#define TRAIN_SAVE_RUN 0
#define ADD_SAMPLES 1
#define JUST_RUN 2

//-- Data Tranformations
#define DT_NONE		 0
#define DT_DELTA	 1
#define DT_LOG		 2
#define DT_DELTALOG	 3

//-- DataFile field separators
#define COMMA ','
#define TAB '\t'
#define SPACE ' '

#undef EXPORT
#define EXPORT __declspec(dllexport)

EXPORT int getEnumVal(char* edesc, char* eVal, int* oVal);

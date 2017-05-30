#pragma once

#include <stdio.h>
#include <Windows.h>
#include<time.h>

#undef EXPORT
#ifdef __cplusplus
#define EXPORT extern "C" __declspec(dllexport)
#else
#define EXPORT __declspec(dllexport)
#endif

EXPORT void Trim(char* str);
EXPORT char* timestamp();

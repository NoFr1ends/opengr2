/*!
	Project: libopengrn
	File: debug.h
	Debug utilities

	Copyright (C) 2021 Arves100
*/
#pragma once

#include <stdio.h>

#ifdef _DEBUG

#ifdef _MSC_VER
#define _CRTDBG_MAP_ALLOC
#include <stdlib.h>
#include <crtdbg.h>

#define DumpMemLeak() _CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
#else
#define DumpMemLeak()
#endif

extern void dbg_printf_real(const char* file, size_t line, const char* fmt, ...);
extern void dbg_printf_no_line(const char* fmt, ...);
extern void dbg_printelement(struct SElementInfo* element);

#define dbg_printf2(fmt, ...) dbg_printf_real(__FILE__, __LINE__, fmt, ##__VA_ARGS__)
#define dbg_printf(fmt, ...) dbg_printf_real(__FILE__, __LINE__, fmt "\n", ##__VA_ARGS__)
#define dbg_printf3(fmt, ...) dbg_printf_no_line(fmt, ##__VA_ARGS__)
#else
#define dbg_printf2(fmt, ...)
#define dbg_printf(fmt, ...)
#define dbg_printf3(fmt, ...)

#define DumpMemLeak()

#endif // _DEBUG

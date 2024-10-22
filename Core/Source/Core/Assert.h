#pragma once

#include "Core/Logging.h"
#include "Core/Miscdef.h"

#ifdef HS_PLATFORM_WINDOWS
	#define HS_DEBUGBREAK_BASE() __debugbreak()
#else
	#include <signal.h>
	#define HS_DEBUGBREAK_BASE() raise(SIGTRAP)
#endif

#ifndef HS_SHIPPING
	#define HS_ASSERT_DETAIL(expr, logger, ...)  if (!(expr)) { HS_##logger##_ERROR("Assertion failed in file '" __FILE__ "' at line " HS_STRINGIFY(__LINE__) "! Expression '" #expr "' evalued to false. " __VA_ARGS__); HS_DEBUGBREAK_BASE(); }
#else
	#define HS_ASSERT_DETAIL(expr, logger, ...)
#endif

#define HS_CORE_ASSERT(expr, ...)    HS_ASSERT_DETAIL(expr, CORE,    __VA_ARGS__)
#define HS_EDITOR_ASSERT(expr, ...)  HS_ASSERT_DETAIL(expr, EDITOR,  __VA_ARGS__)
#define HS_RUNTIME_ASSERT(expr, ...) HS_ASSERT_DETAIL(expr, RUNTIME, __VA_ARGS__)

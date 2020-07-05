﻿#pragma once

#pragma warning(disable: 4100)
#pragma warning(disable: 4189)


#ifdef _WIN32
	#ifdef _WIN64
		#define NW_PLATFORM_WINDOWS
	#else
		#error "x86 builds are not supported"
	#endif
#endif

#define NW_LOG
#define NW_CORE_LOG
#define NW_CLIENT_LOG

#define NW_ENABLE_ASSERT

#ifdef NW_ENABLE_ASSERT

#define NW_CLIENT_ASSERT(x, ...) do { if(!(x)) { NW_CLIENT_ERROR("Assertion failed: {0}", __VA_ARGS__); __debugbreak(); } } while(false)
#define NW_CORE_ASSERT(x, ...) do { if(!(x)) { NW_CORE_ERROR("Assertion failed: {0}", __VA_ARGS__); __debugbreak(); } } while(false)

#else

#define NW_CLIENT_ASSERT(x, ...)
#define NW_CORE_ASSERT(x, ...)

#endif
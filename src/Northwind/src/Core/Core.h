#pragma once

#ifdef _WIN32
	#ifdef _WIN64
		#define NW_PLATFORM_WINDOWS
	#else
		#error "x86 builds are not supported"
	#endif
#endif

#define BIT(x) (1 << x)

#define NW_LOG
#define NW_CORE_LOG
#define NW_CLIENT_LOG
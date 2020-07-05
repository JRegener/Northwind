#pragma once
#include "nwpch.h"

#include "Northwind.h"

#include "spdlog/spdlog.h"
#include "spdlog/fmt/ostr.h"

// TODO: Replace shared_ptr on custom alias

namespace Northwind {

	class Log {
	public:

		static void Init();

		inline static std::shared_ptr<spdlog::logger>& getCoreLogger() { return s_CoreLogger; }
		inline static std::shared_ptr<spdlog::logger>& getClientLogger() { return s_ClientLogger; }

	private:
		static std::shared_ptr<spdlog::logger> s_CoreLogger;
		static std::shared_ptr<spdlog::logger> s_ClientLogger;
	};

}

#ifdef NW_LOG
	#ifdef NW_CORE_LOG
		#define NW_CORE_TRACE(...)	     ::Northwind::Log::getCoreLogger()->trace(__VA_ARGS__)
		#define NW_CORE_INFO(...)        ::Northwind::Log::getCoreLogger()->info(__VA_ARGS__)
		#define NW_CORE_WARN(...)        ::Northwind::Log::getCoreLogger()->warn(__VA_ARGS__)
		#define NW_CORE_ERROR(...)       ::Northwind::Log::getCoreLogger()->error(__VA_ARGS__)
		#define NW_CORE_CRITICAL(...)    ::Northwind::Log::getCoreLogger()->critical(__VA_ARGS__)
	#else
		#define NW_CORE_TRACE(...)	   
		#define NW_CORE_INFO(...)      
		#define NW_CORE_WARN(...)      
		#define NW_CORE_ERROR(...)     
		#define NW_CORE_CRITICAL(...)  
	#endif

	#ifdef NW_CLIENT_LOG
		#define NW_CLIENT_TRACE(...)	 ::Northwind::Log::getClientLogger()->trace(__VA_ARGS__)
		#define NW_CLIENT_INFO(...)      ::Northwind::Log::getClientLogger()->info(__VA_ARGS__)
		#define NW_CLIENT_WARN(...)      ::Northwind::Log::getClientLogger()->warn(__VA_ARGS__)
		#define NW_CLIENT_ERROR(...)     ::Northwind::Log::getClientLogger()->error(__VA_ARGS__)
		#define NW_CLIENT_CRITICAL(...)  ::Northwind::Log::getClientLogger()->critical(__VA_ARGS__)
	#else
		#define NW_CLIENT_TRACE(...)	   
		#define NW_CLIENT_INFO(...)      
		#define NW_CLIENT_WARN(...)      
		#define NW_CLIENT_ERROR(...)     
		#define NW_CLIENT_CRITICAL(...)  
	#endif
#else
	#define NW_CORE_TRACE(...)	   
	#define NW_CORE_INFO(...)      
	#define NW_CORE_WARN(...)      
	#define NW_CORE_ERROR(...)     
	#define NW_CORE_CRITICAL(...)  

	#define NW_CLIENT_TRACE(...)	   
	#define NW_CLIENT_INFO(...)      
	#define NW_CLIENT_WARN(...)      
	#define NW_CLIENT_ERROR(...)     
	#define NW_CLIENT_CRITICAL(...)  
#endif
#pragma once

#include <chrono>
#include <mutex>
#include <sstream>
#include <iostream>
#include <iomanip>
#include <fstream>
#include <thread>



namespace Northwind {

	class MeasurementHandler {
	public:
		MeasurementHandler() : m_sessionRunning(false) {}

		MeasurementHandler(const MeasurementHandler&) = delete;
		MeasurementHandler(MeasurementHandler&&) = delete;

		MeasurementHandler& operator=(const MeasurementHandler&) = delete;
		MeasurementHandler& operator=(MeasurementHandler&&) = delete;

		static MeasurementHandler& get() {
			static MeasurementHandler measurement;
			return measurement;
		}

		void begin(const std::string & filename) {
			std::lock_guard lock(m_mutex);
			if (!m_sessionRunning) {
				// restart session
				stopSession();
			}

			m_profileOut.open(filename);

			if (m_profileOut.is_open()) {
				writeHeader();
				m_sessionRunning = true;
			}
			else {
				// TODO: out error
			}
		}

		void end() {
			std::lock_guard lock(m_mutex);
			stopSession();
		}

		void writeProfile(std::string name, std::chrono::duration<double, std::micro> start, 
			std::chrono::microseconds duration, std::thread::id threadId) {
			
			if (!m_sessionRunning) {
				return;
			}

			std::stringstream json;

			std::string fixName = name;
			std::replace(fixName.begin(), fixName.end(), '"', '\'');

			json << std::setprecision(4) << std::fixed;
			json << ",{";
			json << "\"cat\":\"function\",";
			json << "\"dur\":" << (duration.count()) << ',';
			json << "\"name\":\"" << fixName << "\",";
			json << "\"ph\":\"X\",";
			json << "\"pid\":0,";
			json << "\"tid\":" << threadId << ",";
			json << "\"ts\":" << start.count();
			json << "}";

			
			std::lock_guard lock(m_mutex);

			m_profileOut << json.str();
			m_profileOut.flush();
		}

	private:

		void writeHeader() {
			m_profileOut << "{\"otherData\": {},\"traceEvents\":[{}";
			m_profileOut.flush();
		}

		void writeFooter() {
			m_profileOut << "]}";
			m_profileOut.flush();
		}

		void stopSession() {
			if (m_sessionRunning) {
				writeFooter();
				m_profileOut.close();
				m_sessionRunning = false;
			}
		}

	private:
		bool m_sessionRunning;
		std::mutex m_mutex;
		std::ofstream m_profileOut;
	};

	class TimeMeasurement {

	public:
		explicit TimeMeasurement(const char* name) : 
			m_name(name), m_running(true)
		{
			m_begin = std::chrono::steady_clock::now();
		}

		~TimeMeasurement() {
			if (m_running) {
				stop();
			}
		}


	private:
		void stop() {
			std::chrono::steady_clock::time_point end = std::chrono::steady_clock::now();
			std::chrono::steady_clock::duration diff = end - m_begin;
			std::chrono::microseconds duration = std::chrono::duration_cast<std::chrono::microseconds>(diff);

			MeasurementHandler::get().writeProfile(m_name, m_begin.time_since_epoch(), duration, std::this_thread::get_id());

			m_running = false;
		}


	private:
		const char* m_name;
		std::chrono::steady_clock::time_point m_begin;
		bool m_running;
	};

}

#ifdef NW_PROFILE

#define NW_PROFILE_BEGIN(filename)		::Northwind::MeasurementHandler::get().begin(filename)
#define NW_PROFILE_END()				::Northwind::MeasurementHandler::get().end()

#define NW_PROFILE_SCOPE(name)			::Northwind::TimeMeasurement timer(name)
#define NW_PROFILE_FUNC()				NW_PROFILE_SCOPE(__func__)

#else

#define NW_PROFILE_BEGIN(filename)	
#define NW_PROFILE_END()			

#define NW_PROFILE_SCOPE(name)		
#define NW_PROFILE_FUNC()

#endif
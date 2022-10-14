#pragma once
#include <iostream>
#include <string>
#include <memory>
#include <time.h>
#include <chrono>
#include "spdlog/spdlog.h"
#include "spdlog/async.h"
#include "spdlog/sinks/stdout_color_sinks.h" // or "../stdout_sinks.h" if no color needed
#include "spdlog/sinks/basic_file_sink.h"
#include "spdlog/sinks/rotating_file_sink.h"
 
static inline int NowDateToInt()
{
	time_t now;
	time(&now);
 
	// choose thread save version in each platform
	tm p;
#ifdef _WIN32
	localtime_s(&p, &now);
#else
	localtime_r(&now, &p);
#endif // _WIN32
	int now_date = (1900 + p.tm_year) * 10000 + (p.tm_mon + 1) * 100 + p.tm_mday;
	return now_date;
}
 
static inline int NowTimeToInt()
{
	time_t now;
	time(&now);
	// choose thread save version in each platform
	tm p;
#ifdef _WIN32
	localtime_s(&p, &now);
#else
	localtime_r(&now, &p);
#endif // _WIN32
 
	int now_int = p.tm_hour * 10000 + p.tm_min * 100 + p.tm_sec;
	return now_int;
}
 
class XLogger
{
public:
	static XLogger* getInstance()
	{
		static XLogger xlogger;
		return &xlogger;
	}
 
	std::shared_ptr<spdlog::logger> getLogger()
	{
		return m_logger;
	}

	void Init(std::string console_level, std::string file_level)
	{
		// hardcode log path
		const std::string log_dir = "logs/"; // should create the folder if not exist
		const std::string logger_name_prefix = "gateway_";

		try
		{
			// logger name with timestamp
			int date = NowDateToInt();
			int time = NowTimeToInt();
			const std::string logger_name = log_dir + logger_name_prefix + std::to_string(date) + "_" + std::to_string(time) + ".log";

			spdlog::init_thread_pool(8192, 1);
			auto stdout_sink = std::make_shared<spdlog::sinks::stdout_color_sink_mt >();
			if (console_level == "trace")
			{
				stdout_sink->set_level(spdlog::level::trace);
			}
			else if (console_level == "debug")
			{
				stdout_sink->set_level(spdlog::level::debug);
			}
			else if (console_level == "info")
			{
				stdout_sink->set_level(spdlog::level::info);
			}
			else if (console_level == "warn")
			{
				stdout_sink->set_level(spdlog::level::warn);
			}
			else if (console_level == "error")
			{
				stdout_sink->set_level(spdlog::level::err);
			}

			auto rotating_sink = std::make_shared<spdlog::sinks::rotating_file_sink_mt>(logger_name, 1024 * 1024 * 10, 3);

			if (file_level == "trace")
			{
				rotating_sink->set_level(spdlog::level::trace);
			}
			else if (file_level == "debug")
			{
				rotating_sink->set_level(spdlog::level::debug);
			}
			else if (file_level == "info")
			{
				rotating_sink->set_level(spdlog::level::info);
			}
			else if (file_level == "warn")
			{
				rotating_sink->set_level(spdlog::level::warn);
			}
			else if (file_level == "error")
			{
				rotating_sink->set_level(spdlog::level::err);
			}

			std::vector<spdlog::sink_ptr> sinks{ stdout_sink, rotating_sink };
			m_logger = std::make_shared<spdlog::async_logger>("loggername", sinks.begin(), sinks.end(), spdlog::thread_pool(), spdlog::async_overflow_policy::block);
			//spdlog::register_logger(logger);

			// custom format
			//m_logger->set_pattern("%Y-%m-%d %H:%M:%S.%f <thread %t> [%l] [%@] %v"); // with timestamp, thread_id, filename and line number
			m_logger->set_pattern("%Y-%m-%d %H:%M:%S.%f <thread %t> [%l] %v"); // with timestamp, thread_id, filename and line number

			m_logger->set_level(spdlog::level::debug);

			m_logger->flush_on(spdlog::level::debug);
		}
		catch (const spdlog::spdlog_ex& ex)
		{
			std::cout << "Log initialization failed: " << ex.what() << std::endl;
		}
	}
 
private:
	// make constructor private to avoid outside instance
	XLogger()
	{
		//Init("warn","debug");
	}
 
	~XLogger()
	{
		spdlog::drop_all(); // must do this
	}
 
	void* operator new(size_t size)
	{}
 
	XLogger(const XLogger&) = delete;
	XLogger& operator=(const XLogger&) = delete;
 
private:
	std::shared_ptr<spdlog::logger> m_logger;
};
 
// use embedded macro to support file and line number
#define XLOG_TRACE(...) SPDLOG_LOGGER_CALL(XLogger::getInstance()->getLogger().get(), spdlog::level::trace, __VA_ARGS__)
#define XLOG_DEBUG(...) SPDLOG_LOGGER_CALL(XLogger::getInstance()->getLogger().get(), spdlog::level::debug, __VA_ARGS__)
#define XLOG_INFO(...) SPDLOG_LOGGER_CALL(XLogger::getInstance()->getLogger().get(), spdlog::level::info, __VA_ARGS__)
#define XLOG_WARN(...) SPDLOG_LOGGER_CALL(XLogger::getInstance()->getLogger().get(), spdlog::level::warn, __VA_ARGS__)
#define XLOG_ERROR(...) SPDLOG_LOGGER_CALL(XLogger::getInstance()->getLogger().get(), spdlog::level::err, __VA_ARGS__)
 
#pragma once

#define SPDLOG_LEVEL_NAMES { "trace", "__unused__", "info", "warn", "error", "fatal", "__unused__" }
#define SPDLOG_SHORT_LEVEL_NAMES { "T", "D", "NULL", "I", "W", "E", "F", "NULL" }
#include <spdlog/spdlog.h>

namespace HSFW
{
	extern std::shared_ptr<spdlog::logger> g_CoreLogger, g_EditorLogger, g_RuntimeLogger;
	void InitLog();

#ifdef HS_PLATFORM_WINDOWS
	void Windows_CreateErrorMessageBox(std::string_view caption, std::string_view text);

	template <typename... Args>
	void Windows_RuntimeError(spdlog::level::level_enum lvl, std::string_view logger, std::string_view fmt, Args&&... args)
	{
		std::string_view caption;
		bool fatal = false;

		switch (lvl)
		{
		case spdlog::level::err:
			caption = "Runtime error!";
			break;
		case spdlog::level::critical:
			caption = "Fatal error!";
			fatal = true;
			break;
		default:
			return;
		}

		std::string message = fmt::vformat(fmt, fmt::make_format_args(args...));
		Windows_CreateErrorMessageBox(caption, message);

		if (fatal)
		{
			std::exit(EXIT_FAILURE);
		}
	}
#endif
}

#define HS_LOGGER_TRACE(logger, ...) (logger).trace(__VA_ARGS__)
#define HS_LOGGER_INFO(logger, ...)  (logger).info(__VA_ARGS__)
#define HS_LOGGER_WARN(logger, ...)  (logger).warn(__VA_ARGS__)

#if defined HS_SHIPPING && defined HS_PLATFORM_WINDOWS

#define HS_LOGGER_ERROR(logger, ...) { (logger).error(__VA_ARGS__);    ::HSFW::Windows_RuntimeError(spdlog::level::err,      (logger).name(), __VA_ARGS__); }
#define HS_LOGGER_FATAL(logger, ...) { (logger).critical(__VA_ARGS__); ::HSFW::Windows_RuntimeError(spdlog::level::critical, (logger).name(), __VA_ARGS__); }

#else

#define HS_LOGGER_ERROR(logger, ...) (logger).error(__VA_ARGS__)
#define HS_LOGGER_FATAL(logger, ...) { (logger).critical(__VA_ARGS__); ::std::exit(EXIT_FAILURE); }

#endif

#define HS_CORE_TRACE(...)    HS_LOGGER_TRACE(*::HSFW::g_CoreLogger, __VA_ARGS__)
#define HS_CORE_INFO(...)     HS_LOGGER_INFO (*::HSFW::g_CoreLogger, __VA_ARGS__)
#define HS_CORE_WARN(...)     HS_LOGGER_WARN (*::HSFW::g_CoreLogger, __VA_ARGS__)
#define HS_CORE_ERROR(...)    HS_LOGGER_ERROR(*::HSFW::g_CoreLogger, __VA_ARGS__)
#define HS_CORE_FATAL(...)    HS_LOGGER_FATAL(*::HSFW::g_CoreLogger, __VA_ARGS__)

#define HS_EDITOR_TRACE(...)  HS_LOGGER_TRACE(*::HSFW::g_EditorLogger, __VA_ARGS__)
#define HS_EDITOR_INFO(...)   HS_LOGGER_INFO (*::HSFW::g_EditorLogger, __VA_ARGS__)
#define HS_EDITOR_WARN(...)   HS_LOGGER_WARN (*::HSFW::g_EditorLogger, __VA_ARGS__)
#define HS_EDITOR_ERROR(...)  HS_LOGGER_ERROR(*::HSFW::g_EditorLogger, __VA_ARGS__)
#define HS_EDITOR_FATAL(...)  HS_LOGGER_FATAL(*::HSFW::g_EditorLogger, __VA_ARGS__)

#define HS_RUNTIME_TRACE(...) HS_LOGGER_TRACE(*::HSFW::g_RuntimeLogger, __VA_ARGS__)
#define HS_RUNTIME_INFO(...)  HS_LOGGER_INFO (*::HSFW::g_RuntimeLogger, __VA_ARGS__)
#define HS_RUNTIME_WARN(...)  HS_LOGGER_WARN (*::HSFW::g_RuntimeLogger, __VA_ARGS__)
#define HS_RUNTIME_ERROR(...) HS_LOGGER_ERROR(*::HSFW::g_RuntimeLogger, __VA_ARGS__)
#define HS_RUNTIME_FATAL(...) HS_LOGGER_FATAL(*::HSFW::g_RuntimeLogger, __VA_ARGS__)

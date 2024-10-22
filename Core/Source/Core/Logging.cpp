#include "Corepch.h"
#include "Logging.h"

#include <spdlog/sinks/stdout_color_sinks.h>
#include <spdlog/sinks/basic_file_sink.h>

namespace HSFW
{
	std::shared_ptr<spdlog::logger> g_CoreLogger, g_EditorLogger, g_RuntimeLogger;

	void InitLog()
	{
		spdlog::sink_ptr sinks[] =
		{
			std::make_shared<spdlog::sinks::stdout_color_sink_mt>(),
			std::make_shared<spdlog::sinks::basic_file_sink_mt>("HSFramework.log", true)
		};

		sinks[0]->set_pattern("%^[%T] %n: %v%$");
		sinks[1]->set_pattern("[%T] (%l) %n: %v");

		auto CreateLogger = [sinks](const std::string& name) -> std::shared_ptr<spdlog::logger>
		{
			std::shared_ptr<spdlog::logger> logger = std::make_shared<spdlog::logger>(name, begin(sinks), end(sinks));
			spdlog::register_logger(logger);

			logger->flush_on(spdlog::level::trace);
			logger->set_level(spdlog::level::trace);

			return logger;
		};

		g_CoreLogger    = CreateLogger("HSFW");
		g_EditorLogger  = CreateLogger("HSED");
		g_RuntimeLogger = CreateLogger("HSRT");
	}

#ifdef HS_PLATFORM_WINDOWS
	void Windows_CreateErrorMessageBox(std::string_view caption, std::string_view text)
	{
		MessageBoxA(NULL, text.data(), caption.data(), MB_ICONHAND | MB_OK);
	}
#endif
}

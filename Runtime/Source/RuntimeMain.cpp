#include "Core/Graphics/Window.h"
#include "Core/Assert.h"

namespace HSFW::Runtime
{
	int Main(int argc, char** argv)
	{
		InitLog();
		HS_RUNTIME_INFO("Initialized logging.");

		Window window;
		if (!window.Init())
			return 1;

		while (!window.ShouldClose())
		{
			window.Update();
		}
		window.Destroy();

		return 0;
	}
}

#if defined HS_SHIPPING && defined HS_PLATFORM_WINDOWS

#include <Windows.h>

int WinMain
(
	_In_     HINSTANCE hInstance,
	_In_opt_ HINSTANCE hPrevInstance,
	_In_     LPSTR     lpCmdLine,
	_In_     int       nCmdShow
)
{
	return HSFW::Runtime::Main(__argc, __argv);
}

#else

int main(int argc, char** argv)
{
	return HSFW::Runtime::Main(argc, argv);
}

#endif

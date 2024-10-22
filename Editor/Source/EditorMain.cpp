#include "Core/Logging.h"

namespace HSFW::Editor
{
	int Main(int argc, char** argv)
	{
		InitLog();

		return 0;
	}
}

#if defined HS_SHIPPING && defined HS_PLATFORM_WINDOWS

#include <Windows.h>

int CALLBACK WinMain
(
	_In_     HINSTANCE hInstance,
	_In_opt_ HINSTANCE hPrevInstance,
	_In_     LPSTR     lpCmdLine,
	_In_     int       nCmdShow
)
{
	return HSFW::Editor::Main(__argc, __argv);
}

#else

int main(int argc, char** argv)
{
	return HSFW::Editor::Main(argc, argv);
}

#endif

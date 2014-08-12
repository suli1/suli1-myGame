#include "vld.h"
#include "main.h"
#include "AppDelegate.h"
#include "cocos2d.h"

USING_NS_CC;


int APIENTRY _tWinMain(HINSTANCE hInstance,
                       HINSTANCE hPrevInstance,
                       LPTSTR    lpCmdLine,
                       int       nCmdShow)
{
	//_CrtSetBreakAlloc(4625);

    UNREFERENCED_PARAMETER(hPrevInstance);
    UNREFERENCED_PARAMETER(lpCmdLine);


    // create the application instance
    AppDelegate app;
    Application::getInstance()->run();

	//_CrtDumpMemoryLeaks();
	//int* i = new int();

	return 0;
}

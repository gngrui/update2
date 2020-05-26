#pragma comment(lib, "d2d1.lib")

#include "application.h"

#include <d2d1.h>
#include <Windows.h>

Application* application;

int _stdcall wWinMain(
    HINSTANCE hInstance,
    HINSTANCE hPrevInstance,
    LPTSTR lpCmdLine,
    int nCmdShow
)
{
    application = new Application();
    HRESULT hr = application->Initialze(hInstance);
    if (FAILED(hr)) { return -1; }
    application->Run();

    return 0;
}
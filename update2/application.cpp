#include "application.h"

HRESULT Application::Initialze(HINSTANCE hInstance)
{
    HRESULT hr = S_OK;
    m_hInstance = hInstance;
    hr = InitializeWindow(hInstance);
    if (SUCCEEDED(hr))
    {
        hr = m_pD2DResource->Initialize(m_hwnd);
    }
    return hr;
}

HRESULT Application::NextFrame(float deltaTime)
{

    HRESULT hr = S_OK;
    m_pGameControl->UpdateGameStatus(deltaTime, m_pGameResource);
    hr = Render();
    return hr;
}

LRESULT Application::ApplicationMSGProc(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    switch (message)
    {
    case WM_KEYDOWN:
        application->DispatchKeyBoardMsg(wParam, lParam, application->m_pGameResource);
        break;
    case WM_DESTROY:
        DestroyMenu(application->m_hmenu);
        PostQuitMessage(0);
        break;
    default:
        return DefWindowProc(hwnd, message, wParam, lParam);
    }
    return 0;
}

INT_PTR CALLBACK Application::SettingsMSGProc(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
    UNREFERENCED_PARAMETER(lParam);
    switch (message)
    {
    case WM_INITDIALOG:
        return (INT_PTR)TRUE;

    case WM_COMMAND:
        if (LOWORD(wParam) == IDOK || LOWORD(wParam) == IDCANCEL)
        {
            EndDialog(hDlg, LOWORD(wParam));
            return (INT_PTR)TRUE;
        }
        break;
    }
    return (INT_PTR)FALSE;
}

void Application::Run()
{
    MSG msg = { 0 };
    m_Timer.Reset();
    while (msg.message != WM_QUIT)
    {
        if (PeekMessage(&msg, NULL, NULL, NULL, PM_REMOVE))
        {
            TranslateMessage(&msg);
            DispatchMessage(&msg);
        }
        else
        {
            if (!m_appPause)
            {
                m_Timer.Tick();
                HRESULT hr = NextFrame(m_Timer.DeltaTime());
                if (FAILED(hr)) { return; }
            }
        }
    }
}

void Application::Pause()
{
    if (!m_appPause)
    {
        m_appPause = true;
        m_Timer.Pause();
    }
}

void Application::Start()
{
    if (m_appPause)
    {
        m_appPause = false;
        m_Timer.Pause();
    }
}

HRESULT Application::InitializeWindow(HINSTANCE hInstance)
{
    HRESULT hr = S_OK;
    WNDCLASSEX wcex = { sizeof(WNDCLASSEX) };
    wcex.style = CS_HREDRAW | CS_VREDRAW;
    wcex.lpfnWndProc = Application::ApplicationMSGProc;
    wcex.cbClsExtra = 0;
    wcex.cbWndExtra = sizeof(LONG_PTR);
    wcex.hInstance = hInstance;
    wcex.hbrBackground = NULL;
    wcex.lpszMenuName = NULL;
    wcex.hCursor = LoadCursor(NULL, IDI_APPLICATION);
    wcex.lpszClassName = L"D2DDemoApp";

    RegisterClassEx(&wcex);

    RECT rc;
    rc.top = 0;
    rc.left = 0;
    rc.bottom = 480;
    rc.right = 640;
    AdjustWindowRect(&rc, WS_OVERLAPPEDWINDOW ^ WS_MAXIMIZEBOX ^ WS_THICKFRAME, FALSE);
    m_hwnd = CreateWindow(
        L"D2DDemoApp",
        L"Direct2D Demo App",
        WS_OVERLAPPEDWINDOW ^ WS_MAXIMIZEBOX ^ WS_THICKFRAME,
        CW_USEDEFAULT,
        CW_USEDEFAULT,
        rc.right - rc.left,
        rc.bottom - rc.top,
        NULL,
        NULL,
        hInstance,
        nullptr
    );
    hr = m_hwnd ? S_OK : E_FAIL;
    if (SUCCEEDED(hr))
    {
        ShowWindow(m_hwnd, SW_SHOWNORMAL);
        UpdateWindow(m_hwnd);
    }
    return hr;
}

HRESULT Application::Render()
{
    HRESULT hr = S_OK;
    m_pD2DResource->getRenderTarget().BeginDraw();
    m_pD2DResource->getRenderTarget().Clear(D2D1::ColorF(D2D1::ColorF::DarkBlue));
    m_pD2DResource->getRenderTarget().DrawRectangle(
        m_pGameResource->getFrameRect(),
        &m_pD2DResource->getSolidYellowBrush(),
        1.5f
    );
    m_pD2DResource->getRenderTarget().DrawRectangle(
        m_pGameResource->getClientRect(),
        &m_pD2DResource->getSolidYellowBrush(),
        1.5f
    );
    for (int y = 0; y < GameResource::m_Vblock; y++)
        for (int x = 0; x < GameResource::m_Hblock; x++)
        {
            /*m_pD2DResource->getRenderTarget().DrawRectangle(
                m_pGameResource->getCellRect(x, y),
                &m_pD2DResource->getSolidYellowBrush(),
                1.f
            );*/
            if (m_pGameResource->getisExist(x, y))
                m_pD2DResource->getRenderTarget().FillRectangle(
                    m_pGameResource->getCellRect(x, y),
                    m_pD2DResource->getBrushByColor(m_pGameResource->getCellColor(x, y))
                );
        }
    if (m_pGameResource->getBlock().getBlockStatus() == BLOCK_STATUS::UNDEFINE)
        ;
    else
    {
        std::vector<POINT> v = m_pGameResource->getBlock().getCordination();
        for (POINT p : v)
        {
            ID2D1SolidColorBrush* brush = m_pD2DResource->getBrushByColor(m_pGameResource->getBlock().getColor());
            m_pD2DResource->getRenderTarget().FillRectangle(
                m_pGameResource->getCellRect(p.x, p.y),
                m_pD2DResource->getBrushByColor(m_pGameResource->getBlock().getColor())
            );
        }
    }

    hr = m_pD2DResource->getRenderTarget().EndDraw();
    return hr;
}

void Application::RespondKeyBoard(WPARAM wParam, LPARAM lParam, GameResource* g)
{   
    if (wParam == VK_ESCAPE)
    {
        if (!application->m_appPause)
            application->Pause();
        else
            application->Start();
    }
}

void Application::DispatchKeyBoardMsg(WPARAM wParam, LPARAM lParam, GameResource* g)
{
    if (wParam == VK_ESCAPE || application->m_appPause)
    {
        RespondKeyBoard(wParam, lParam, g);
    }
    else
    {
        m_pGameControl->RespondKeyBoardMSG(wParam, lParam, g);
    }

}

void Application::CreateMenuAndItem()
{
}

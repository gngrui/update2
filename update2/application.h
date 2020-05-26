#pragma once

#include "d2dresource.h"
#include "gamecontrol.h"
#include "gameresource.h"
#include "timer.h"

#include <Windows.h>

#define RESUME 453
#define RESTART 234
#define OPTION 341

class Application
{
public:
	Application() : m_hwnd(nullptr)
	{
		m_pD2DResource = new D2DResource();
		m_pGameControl = new GameControl();
		m_pGameResource = new GameResource();
	}
	~Application()
	{
		delete m_pD2DResource;
		delete m_pGameControl;
		delete m_pGameResource;
	}

	HRESULT Initialze(HINSTANCE hInstance);

	HRESULT NextFrame(float deltaTime);

	static LRESULT CALLBACK ApplicationMSGProc(
		HWND hwnd,
		UINT message,
		WPARAM wParam,
		LPARAM lParam
	);

	static INT_PTR CALLBACK SettingsMSGProc(
		HWND hDlg,
		UINT message,
		WPARAM wParam,
		LPARAM lParam
	);

	void Run();
	void Pause();
	void Start();

	const static UINT width = 640;
	const static UINT height = 480;
private:
	HRESULT InitializeWindow(HINSTANCE hInstance);

	HRESULT Render();

	void RespondKeyBoard(WPARAM wParam, LPARAM lParam, GameResource* g);

	void DispatchKeyBoardMsg(WPARAM wParam, LPARAM lParam, GameResource* g);

	void CreateMenuAndItem();
private:
	HWND m_hwnd;
	HMENU m_hmenu;
	HINSTANCE m_hInstance;
	D2DResource* m_pD2DResource;
	GameControl* m_pGameControl;
	GameResource* m_pGameResource;
	Timer m_Timer;

	bool m_appPause = false;
};

extern Application* application;
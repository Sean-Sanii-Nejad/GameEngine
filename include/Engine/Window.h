#pragma once
#include <windows.h>
#include <GraphicsEngine.h>
#include <SwapChain.h>
#include <iostream>

using namespace std;

class Window {
public:
	Window();
	~Window();
	bool init();
	bool broadcast();
	bool release();
	bool isRun();

	RECT getClientWindowRect();
	void setHWND(HWND hwnd);

	//EVENTS
	virtual void onCreate() = 0;
	virtual void onUpdate() = 0;
	virtual void onDestroy() = 0;
protected:
	HWND m_hwnd = nullptr;
	bool m_is_run = false;
};
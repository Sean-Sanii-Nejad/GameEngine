#pragma once
#include <Window.h>
#include <DeviceContext.h>



class AppWindow : public Window {

public:
	AppWindow();
	~AppWindow();

	// Inherited via Window
	void onCreate() override;
	void onUpdate() override;
	void onDestroy() override;

private:
	SwapChain* m_swap_chain = nullptr; // Pointer to the swap chain instance.

};
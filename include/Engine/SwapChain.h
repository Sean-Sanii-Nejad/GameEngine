#pragma once
#include <d3d11.h>

class DeviceContext;

class SwapChain {

public:
	SwapChain();
	~SwapChain();
	bool init(HWND hwnd, UINT width, UINT height);
	bool release();


	bool present(bool vsync);

private:
	IDXGISwapChain* m_swap_chain = nullptr; // Pointer to the swap chain interface.
	ID3D11RenderTargetView* m_rtv = nullptr; // Pointer to the render target view for the swap chain.

	friend class DeviceContext; // Allow DeviceContext to access private members of SwapChain.
};

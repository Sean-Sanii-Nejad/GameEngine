#pragma once
#include <d3d11.h>


class SwapChain {

public:
	SwapChain();
	bool init(HWND hwnd, UINT width, UINT height);
	bool release();
	~SwapChain();

private:
	IDXGISwapChain* m_swap_chain = nullptr; // Pointer to the swap chain interface.
};

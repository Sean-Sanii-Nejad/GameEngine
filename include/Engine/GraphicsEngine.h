#pragma once
#include <d3d11.h>

class SwapChain;
class DeviceContext;

class GraphicsEngine {
public:
	GraphicsEngine();
	~GraphicsEngine();

	bool init();
	bool release();

	static GraphicsEngine* get();
	SwapChain* createSwapChain();
	DeviceContext* getImmediateContext();

private:
	DeviceContext* m_imm_device_context = nullptr; // Pointer to the device context instance.

	ID3D11Device* m_d3d_device = nullptr;
	D3D_FEATURE_LEVEL m_feature_level = D3D_FEATURE_LEVEL_11_0;

	IDXGIDevice* m_dxgi_device = nullptr;
	IDXGIAdapter* m_dxgi_adapter = nullptr;
	IDXGIFactory* m_dxgi_factory = nullptr;

	friend class SwapChain;
};
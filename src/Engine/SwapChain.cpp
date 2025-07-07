#include "SwapChain.h"
#include "GraphicsEngine.h"

SwapChain::SwapChain() {
}

SwapChain::~SwapChain() {
}

bool SwapChain::init(HWND hwnd, UINT width, UINT height) {
	ID3D11Device* device = GraphicsEngine::get()->m_d3d_device;

	DXGI_SWAP_CHAIN_DESC desc;
	ZeroMemory(&desc, sizeof(desc)); // Fill desc with zeros, to ensure all fields are initialised.
	desc.BufferCount = 1; // Number of buffers in the swap chain.
	desc.BufferDesc.Width = width; 
	desc.BufferDesc.Height = height; 
	desc.BufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM; // Format of the back buffer.
	desc.BufferDesc.RefreshRate.Numerator = 60; 
	desc.BufferDesc.RefreshRate.Denominator = 1; // Refresh rate of the back buffer.
	desc.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT; 
	desc.OutputWindow = hwnd; 
	desc.SampleDesc.Count = 1; 
	desc.SampleDesc.Quality = 0; 
	desc.Windowed = TRUE; // Windowed mode.

	HRESULT hr = GraphicsEngine::get()->m_dxgi_factory->CreateSwapChain(device, &desc, &m_swap_chain); // Create the swap chain using the factory and the device.
	if( FAILED(hr)) {
		return false; // If the swap chain creation fails, return false.
	}
	return true;
}

bool SwapChain::release() {
	m_swap_chain->Release(); 
	delete this;
	return true;
}


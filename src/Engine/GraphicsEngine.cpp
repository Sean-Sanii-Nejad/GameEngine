#include <GraphicsEngine.h>
#include <SwapChain.h>
#include <DeviceContext.h>
#include <iostream>

using namespace std;

GraphicsEngine::GraphicsEngine() {
}

GraphicsEngine::~GraphicsEngine() {
}

bool GraphicsEngine::init() {
	D3D_DRIVER_TYPE driver_types[] = {
		D3D_DRIVER_TYPE_HARDWARE,
		D3D_DRIVER_TYPE_WARP,
		D3D_DRIVER_TYPE_REFERENCE
	};

	D3D_FEATURE_LEVEL feature_levels[] = {
		D3D_FEATURE_LEVEL_11_0,
	};

	HRESULT res = 0;
	ID3D11DeviceContext* m_imm_context = nullptr;
	for (auto& types : driver_types) {
		res = D3D11CreateDevice(NULL, types, NULL, NULL, feature_levels, ARRAYSIZE(feature_levels), D3D11_SDK_VERSION, &m_d3d_device, &m_feature_level, &m_imm_context);
		if( SUCCEEDED(res)) {
			break;
		}
	}

	if(FAILED(res)) {
		return false;
	}

	m_imm_device_context = new DeviceContext(m_imm_context);

	m_d3d_device->QueryInterface(__uuidof(IDXGIDevice), (void**)&m_dxgi_device);
	m_dxgi_device->GetParent(_uuidof(IDXGIAdapter), (void**)&m_dxgi_adapter);
	m_dxgi_adapter->GetParent(_uuidof(IDXGIFactory), (void**)&m_dxgi_factory);

	cout << "Direct3D 11 initialized successfully." << endl;
	return true;
}

bool GraphicsEngine::release() {
	m_dxgi_device->Release();
	m_dxgi_adapter->Release();
	m_dxgi_factory->Release();

	m_imm_device_context->release();
	m_d3d_device->Release();
	return true;
}

GraphicsEngine* GraphicsEngine::get() {
	static GraphicsEngine engine;
	return &engine;
}

SwapChain* GraphicsEngine::createSwapChain(){
	return new SwapChain(); // Create a new swap chain instance and return it.
}

DeviceContext* GraphicsEngine::getImmediateContext() {
	return this->m_imm_device_context; 
}

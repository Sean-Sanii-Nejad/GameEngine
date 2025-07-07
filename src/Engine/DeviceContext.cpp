#include <DeviceContext.h>
#include <SwapChain.h>

DeviceContext::DeviceContext(ID3D11DeviceContext* device_context) : m_device_context(device_context){

}

DeviceContext::~DeviceContext() {

}

bool DeviceContext::clearRenderTargetColour(SwapChain* swap_chain, float r, float g, float b, float alpha) {
	
	FLOAT clear_color[4] = { r, g, b, alpha }; 
	m_device_context->ClearRenderTargetView(swap_chain->m_rtv, clear_color);
	return false;
}

bool DeviceContext::init() {

	return true;
}

bool DeviceContext::release() {
	m_device_context->Release(); 
	delete this; // Delete the DeviceContext instance.
	return true;
}

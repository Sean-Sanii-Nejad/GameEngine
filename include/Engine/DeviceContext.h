#pragma once
#include <d3d11.h>

class DeviceContext {
public:
	DeviceContext(ID3D11DeviceContext* device_context);
	~DeviceContext();

	bool clearRenderTargetColour(float r, float g, float b, float alpha);

	bool init();
	bool release();

private:
	ID3D11DeviceContext* m_device_context;
};
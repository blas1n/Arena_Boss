#pragma once

#include <d3d11.h>
#include "Color.h"

class D3D final
{
public:
	D3D(class Windows* inWindows, uint32_t sampleCount, uint32_t sampleQuality);

	D3D(const D3D&) = delete;
	D3D(D3D&&) noexcept = default;

	D3D& operator=(const D3D&) = delete;
	D3D& operator=(D3D&&) noexcept = default;

	~D3D();

	inline void Present()
	{
		swapChain->Present(static_cast<UINT>(vsync), 0);
	}

	inline bool IsVsync() const noexcept { return vsync; }
	inline void SetVsync(bool isVsync) noexcept { vsync = isVsync; }

	void SetDefaultViewport();

	inline void SetDefaultRTVAndDSV()
	{
		deviceContext->OMSetRenderTargets(1, &renderTargetView, depthStencilView);
	}

	inline void SetBackgroundColor(const Color& color)
	{
		backgroundColor = color;
	}

	inline void ClearRenderTarget()
	{
		float color[4];
		backgroundColor.AsPtr(color);
		deviceContext->ClearRenderTargetView(renderTargetView, color);
	}

	inline void ClearDepthStencil()
	{
		deviceContext->ClearDepthStencilView(
			depthStencilView, D3D11_CLEAR_DEPTH | D3D11_CLEAR_STENCIL, 1.0f, 0);
	}

	inline void SetFullScreen(bool isFullScreen)
	{
		swapChain->SetFullscreenState(static_cast<BOOL>(isFullScreen), nullptr);
	}

	inline ID3D11Device* GetD3DDevice() const noexcept { return device; }
	inline ID3D11DeviceContext* GetD3DDeviceContext() const noexcept { return deviceContext; }

private:
	bool CreateD3DDevice();
	bool CreateSwapChain(uint32_t sampleCount, uint32_t sampleQuality);
	bool CreateRenderTargetView();
	bool CreateDepthStencilBuffer(uint32_t sampleCount, uint32_t sampleQuality);

private:
	constexpr static auto SWAPCHAIN_BUFFER_FORMAT = DXGI_FORMAT_R8G8B8A8_UNORM;
	constexpr static auto DEPTHSTENCIL_BUFFER_FORMAT = DXGI_FORMAT_D24_UNORM_S8_UINT;
	constexpr static auto PRIMITIVE_TOPOLOGY = D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST;

	Color backgroundColor;

	Windows* windows;

	IDXGISwapChain* swapChain = nullptr;

	ID3D11Device* device = nullptr;
	ID3D11DeviceContext* deviceContext = nullptr;

	ID3D11RenderTargetView* renderTargetView = nullptr;

	ID3D11Texture2D* depthStencilBuffer = nullptr;
	ID3D11DepthStencilView* depthStencilView = nullptr;

	bool isFullscreen = false;
	bool vsync = true;
};


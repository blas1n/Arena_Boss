#pragma once

#include "Common.h"
#include <d3d11.h>
#include "Color.h"
#include "Vector2.h"

class Windows
{
public:
	Windows(const tstring& title, uint32_t width, uint32_t height,
		uint32_t sampleCount, uint32_t sampleQuality);

	~Windows();

	inline bool IsWindowAvailable() const noexcept { return hWnd != nullptr; }
	inline bool IsD3DAvailable() const noexcept { return device != nullptr; }

	inline const Math::Vector2& GetCenterPos() const noexcept { return center; }
	inline const Math::Vector2& GetSize() const noexcept { return size; }

	inline float GetAspectRatio() const noexcept { return size.GetX() / size.GetY(); }

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

	void DoEvents();

	inline void Present()
	{
		swapChain->Present(static_cast<UINT>(vsync), 0);
	}

	inline void SetFullScreen(bool isFullScreen)
	{
		swapChain->SetFullscreenState(static_cast<BOOL>(isFullScreen), nullptr);
	}

	inline HWND GetWindowHandle() const noexcept { return hWnd; }
	inline HINSTANCE GetProgramHandle() const noexcept { return hInstance; }

	inline ID3D11Device* GetD3DDevice() const noexcept { return device; }
	inline ID3D11DeviceContext* GetD3DDeviceContext() const noexcept { return deviceContext; }

	const tstring& GetProgramPath() const noexcept { return programPath; }

	void ShowErrorBox(const tstring& errMsg)
	{
		MessageBox(hWnd, errMsg.c_str(), TEXT("Error"), MB_ICONERROR | MB_OK);
	}

private:
	void InitWindows(uint32_t width, uint32_t height);
	void InitD3D(uint32_t sampleCount, uint32_t sampleQuality);

	void UpdateClientPos();

	bool CreateD3DDevice();
	bool CreateSwapChain(uint32_t sampleCount, uint32_t sampleQuality);
	bool CreateRenderTargetView();
	bool CreateDepthStencilBuffer(uint32_t sampleCount, uint32_t sampleQuality);

	void DestroyWindows();
	void DestroyD3D();

private:
	constexpr static auto SWAPCHAIN_BUFFER_FORMAT = DXGI_FORMAT_R8G8B8A8_UNORM;
	constexpr static auto DEPTHSTENCIL_BUFFER_FORMAT = DXGI_FORMAT_D24_UNORM_S8_UINT;
	constexpr static auto PRIMITIVE_TOPOLOGY = D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST;

	tstring programPath;

	HWND hWnd = nullptr;
	HINSTANCE hInstance = nullptr;

	tstring windowClassName;
	tstring windowTitle;

	Math::Vector2 pos;
	Math::Vector2 size;
	Math::Vector2 center;

	Color backgroundColor;

	IDXGISwapChain* swapChain = nullptr;

	ID3D11Device* device = nullptr;
	ID3D11DeviceContext* deviceContext = nullptr;

	ID3D11RenderTargetView* renderTargetView = nullptr;

	ID3D11Texture2D* depthStencilBuffer = nullptr;
	ID3D11DepthStencilView* depthStencilView = nullptr;

	bool isFullscreen = false;
	bool vsync = true;
};
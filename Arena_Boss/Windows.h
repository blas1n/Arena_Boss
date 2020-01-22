#pragma once

#include "Common.h"
#include <d3d11.h>
#include "Vector2.h"

class Windows
{
public:
	Windows(int width, int height, const tstring& title);
	~Windows();

	int GetWidth() const noexcept;
	int GetHeight() const noexcept;

	float GetAspectRatio() const noexcept;

	bool IsVsync() const noexcept;
	void SetVsync() noexcept;

	void SetDefaultViewport();
	void SetDefaultRTVAndDSV();

	void SetBackgroundColor(const class Color& color);
	void ClearRenderTarget();
	void ClearDepthStencil();

	Math::Vector2 GetCenterPos();
	Math::Vector2 GetSize();

	void DoEvents();
	void Present();

	void SetFullScreen(bool isFullScreen);

	ID3D11Device* GetD3DDevice();
	ID3D11DeviceContext* GetD3DDeviceContext();

	HWND GetWindowHandle();
	HINSTANCE GetProgramHandle();

	const tstring& GetProgramPath();

	void ShowErrorMessage(const tstring& errMsg);
};
#pragma once

#include "Common.h"
#include "Vector2.h"

class Windows final
{
public:
	Windows(const tstring& title, uint32_t width, uint32_t height);

	Windows(const Windows&) = delete;
	Windows(Windows&&) = default;

	Windows& operator=(const Windows&) = delete;
	Windows& operator=(Windows&&) = default;

	~Windows();

	void DoEvents();

	inline const Math::Vector2& GetCenterPos() const noexcept { return center; }
	inline const Math::Vector2& GetSize() const noexcept { return size; }

	inline float GetAspectRatio() const noexcept { return size.GetX() / size.GetY(); }

	inline HWND GetWindowsHandle() const noexcept { return hWnd; }
	inline HINSTANCE GetProgramHandle() const noexcept { return hInstance; }

	const tstring& GetProgramPath() const noexcept { return programPath; }

	void ShowErrorBox(const tstring& errMsg)
	{
		MessageBox(hWnd, errMsg.c_str(), TEXT("Error"), MB_ICONERROR | MB_OK);
	}

private:
	void UpdateClientPos();

private:
	tstring programPath;

	HWND hWnd = nullptr;
	HINSTANCE hInstance = nullptr;

	tstring windowClassName;
	tstring windowTitle;

	Math::Vector2 pos;
	Math::Vector2 size;
	Math::Vector2 center;
};
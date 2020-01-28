#include "InputSystem.h"
#include <cassert>
#include <memory>
#include "MathFunctions.h"
#include "Util.h"

InputSystem::InputSystem(HINSTANCE hInstance, HWND hWnd, int width, int height)
	: screenWidth(width), screenHeight(height)
{
	auto hr = DirectInput8Create(hInstance, DIRECTINPUT_VERSION,
		IID_IDirectInput8, reinterpret_cast<void**>(&input), nullptr);
	
	assert(SUCCEEDED(hr));

	hr = input->CreateDevice(GUID_SysKeyboard, &keyboard, nullptr);
	assert(SUCCEEDED(hr));

	hr = keyboard->SetDataFormat(&c_dfDIKeyboard);
	assert(SUCCEEDED(hr));

	hr = keyboard->SetCooperativeLevel(hWnd, DISCL_FOREGROUND | DISCL_EXCLUSIVE);
	assert(SUCCEEDED(hr));

	hr = keyboard->Acquire();
	assert(SUCCEEDED(hr));

	hr = input->CreateDevice(GUID_SysMouse, &mouse, nullptr);
	assert(SUCCEEDED(hr));

	hr = mouse->SetDataFormat(&c_dfDIMouse);
	assert(SUCCEEDED(hr));

	hr = mouse->SetCooperativeLevel(hWnd, DISCL_FOREGROUND | DISCL_NONEXCLUSIVE);
	assert(SUCCEEDED(hr));

	hr = mouse->Acquire();
	assert(SUCCEEDED(hr));
}

InputSystem::~InputSystem()
{
	mouse->Unacquire();
	keyboard->Unacquire();

	Util::ReleaseObjects(mouse, keyboard, input);
}

bool InputSystem::IsCurDown(Key key) const noexcept
{
	constexpr auto minMouse = static_cast<byte>(Key::MouseLeft);
	const auto code = static_cast<byte>(key);

	if (code < minMouse)
		return curKeyState[code] & 0x80;
	else
		return curMouseState.rgbButtons[code - minMouse] & 0x80;
}

bool InputSystem::IsOldDown(Key key) const noexcept
{
	constexpr auto minMouse = static_cast<byte>(Key::MouseLeft);
	const auto code = static_cast<byte>(key);

	if (code < minMouse)
		return oldKeyState[code] & 0x80;
	else
		return oldMouseState.rgbButtons[code - minMouse] & 0x80;
}

bool InputSystem::ReadKeyboard()
{
	memcpy(oldKeyState, curKeyState, 256 * sizeof(byte));
	auto hr = keyboard->GetDeviceState(sizeof(curKeyState), reinterpret_cast<LPVOID>(&curKeyState));
	if (FAILED(hr))
	{
		if ((hr == DIERR_INPUTLOST) || (hr = DIERR_NOTACQUIRED))
			keyboard->Acquire();
		else
			return false;
	}

	return true;
}

bool InputSystem::ReadMouse()
{
	oldMouseState = curMouseState;
	auto hr = mouse->GetDeviceState(sizeof(DIMOUSESTATE2), reinterpret_cast<LPVOID>(&curMouseState));
	if (FAILED(hr))
	{
		if ((hr == DIERR_INPUTLOST) || (hr = DIERR_NOTACQUIRED))
			mouse->Acquire();
		else
			return false;
	}

	return true;
}

void InputSystem::ProcessInput()
{
	Math::Clamp(mouseX += curMouseState.lX, 0, screenWidth);
	Math::Clamp(mouseY += curMouseState.lY, 0, screenHeight);
}
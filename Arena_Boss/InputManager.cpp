#include "InputManager.h"
#include <cassert>
#include <memory>
#include "MathFunctions.h"
#include "Util.h"
#include "Windows.h"

InputManager::InputManager(const Windows& windows)
	: curKeyState(), oldKeyState(), curMouseState(), oldMouseState(),
	screenWidth(static_cast<uint32_t>(windows.GetSize().GetX())),
	screenHeight(static_cast<uint32_t>(windows.GetSize().GetY()))
{
	const auto hWnd = windows.GetWindowsHandle();

	auto hr = DirectInput8Create(windows.GetProgramHandle(), DIRECTINPUT_VERSION,
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

InputManager::~InputManager()
{
	mouse->Unacquire();
	keyboard->Unacquire();

	Util::ReleaseObjects(mouse, keyboard, input);
}

bool InputManager::IsCurDown(Key key) const noexcept
{
	constexpr auto minMouse = static_cast<byte>(Key::MouseLeft);
	const auto code = static_cast<byte>(key);

	if (code < minMouse)
		return curKeyState[code] & 0x80;
	else
		return curMouseState.rgbButtons[code - minMouse] & 0x80;
}

bool InputManager::IsOldDown(Key key) const noexcept
{
	constexpr auto minMouse = static_cast<byte>(Key::MouseLeft);
	const auto code = static_cast<byte>(key);

	if (code < minMouse)
		return oldKeyState[code] & 0x80;
	else
		return oldMouseState.rgbButtons[code - minMouse] & 0x80;
}

bool InputManager::ReadKeyboard()
{
	memcpy(oldKeyState, curKeyState, 256 * sizeof(byte));
	auto hr = keyboard->GetDeviceState(sizeof(curKeyState), reinterpret_cast<LPVOID>(&curKeyState));
	if (FAILED(hr))
	{
		if ((hr == DIERR_INPUTLOST) || (hr == DIERR_NOTACQUIRED))
			keyboard->Acquire();
		else
			return false;
	}

	return true;
}

bool InputManager::ReadMouse()
{
	oldMouseState = curMouseState;
	auto hr = mouse->GetDeviceState(sizeof(DIMOUSESTATE2), reinterpret_cast<LPVOID>(&curMouseState));
	if (FAILED(hr))
	{
		if ((hr == DIERR_INPUTLOST) || (hr == DIERR_NOTACQUIRED))
			mouse->Acquire();
		else
			return false;
	}

	return true;
}

void InputManager::ProcessInput()
{
	Math::Clamp(mouseX += curMouseState.lX, 0u, screenWidth);
	Math::Clamp(mouseY += curMouseState.lY, 0u, screenHeight);
}
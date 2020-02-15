#include "WindowManager.h"

namespace ArenaBoss
{
	WindowManager::WindowManager(const char* inTitle,
		uint32_t inWidth, uint32_t inHeight, ScreenMode inScreenMode)
		: window(nullptr),
		title(inTitle),
		width(inWidth),
		height(inHeight),
		screenMode(inScreenMode)
	{
		uint32_t flag = SDL_WINDOW_OPENGL;

		if (screenMode == ScreenMode::FullScreen)
			flag |= SDL_WINDOW_FULLSCREEN;
		else if (screenMode == ScreenMode::Borderless)
			flag |= SDL_WINDOW_FULLSCREEN_DESKTOP;

		window = SDL_CreateWindow(
			title,
			SDL_WINDOWPOS_CENTERED,
			SDL_WINDOWPOS_CENTERED,
			width,
			height,
			flag);
	}

	WindowManager::~WindowManager()
	{
		SDL_DestroyWindow(window);
	}

	void WindowManager::SetTitle(const char* inTitle) noexcept
	{
		title = inTitle;
		SDL_SetWindowTitle(window, title);
	}

	void WindowManager::SetSize(uint32_t inWidth, uint32_t inHeight) noexcept
	{
		width = inWidth;
		height = inHeight;
		SDL_SetWindowSize(window, width, height);
	}

	void WindowManager::SetScreenMode(ScreenMode inScreenMode) noexcept
	{
		screenMode = inScreenMode;

		uint32_t flag = 0;
		if (screenMode == ScreenMode::FullScreen)
			flag = SDL_WINDOW_FULLSCREEN;
		else if (screenMode == ScreenMode::Borderless)
			flag = SDL_WINDOW_FULLSCREEN_DESKTOP;

		SDL_SetWindowFullscreen(window, flag);
	}
}
#pragma once

#include <cstdint>
#include <SDL2/SDL.h>
#include "Vector2.h"

namespace ArenaBoss
{
	enum class ScreenMode
	{
		Window,
		FullScreen,
		Borderless
	};

	class WindowManager
	{
	public:
		WindowManager(const char* inTitle, uint32_t inWidth,
			uint32_t inHeight, ScreenMode inScreenMode);

		WindowManager(const WindowManager&) = delete;
		WindowManager(WindowManager&&) = delete;

		WindowManager& operator=(const WindowManager&) = delete;
		WindowManager& operator=(WindowManager&&) = delete;

		~WindowManager();

		inline SDL_Window* GetWindow() noexcept
		{
			return window;
		}

		inline const char* GetTitle() const noexcept
		{
			return title;
		}

		inline uint32_t GetWidth() const noexcept
		{
			return width;
		}

		inline uint32_t GetHeight() const noexcept
		{
			return height;
		}

		inline Math::Vector2 GetSize() const noexcept
		{
			return Math::Vector2
			{
				static_cast<float>(width),
				static_cast<float>(height)
			};
		}

		inline ScreenMode GetScreenMode() const noexcept
		{
			return screenMode;
		}

		void SetTitle(const char* inTitle) noexcept;
		void SetSize(uint32_t inWidth, uint32_t inHeight) noexcept;
		void SetScreenMode(ScreenMode inScreenMode) noexcept;

	private:
		SDL_Window* window;

		const char* title;
		uint32_t width;
		uint32_t height;
		ScreenMode screenMode;
	};
}
#include "WindowManager.h"
#include <exception>

namespace ArenaBoss
{
	WindowManager::WindowManager(const char* title,
		uint32_t width, uint32_t height, ScreenMode inScreenMode)
		: window(nullptr),
		screenMode(inScreenMode)
	{
		if (!glfwInit())
			throw std::exception{ "Failed to initialze GLFW" };

		auto* monitor = glfwGetPrimaryMonitor();
		auto* mode = glfwGetVideoMode(monitor);

		glfwWindowHint(GLFW_RED_BITS, mode->redBits);
		glfwWindowHint(GLFW_GREEN_BITS, mode->greenBits);
		glfwWindowHint(GLFW_BLUE_BITS, mode->blueBits);
		glfwWindowHint(GLFW_REFRESH_RATE, mode->refreshRate);

		glfwWindowHint(GLFW_SAMPLES, 4);
		glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
		glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
		glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
		glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

		window = glfwCreateWindow(width, height, title, nullptr, nullptr);
		glfwMakeContextCurrent(window);
	}

	WindowManager::~WindowManager()
	{
		glfwDestroyWindow(window);
		glfwTerminate();
	}

	Math::UintVector2 WindowManager::GetSize() const noexcept
	{
		int w, h;
		glfwGetWindowSize(window, &w, &h);
		return Math::UintVector2{ static_cast<uint32_t>(w), static_cast<uint32_t>(h) };
	}

	void WindowManager::SetScreenMode(ScreenMode inScreenMode) noexcept
	{
		screenMode = inScreenMode;
		
		auto* monitor = glfwGetPrimaryMonitor();
		auto* mode = glfwGetVideoMode(monitor);

		switch (screenMode)
		{
		case ScreenMode::Window:
		{
			int x, y, w, h;
			glfwGetWindowPos(window, &x, &y);
			glfwGetWindowSize(window, &w, &h);

			glfwSetWindowMonitor(window, nullptr, x, y, w, h, 0);
			break;
		}
		case ScreenMode::FullScreen:
		{
			glfwSetWindowMonitor(window, monitor, 0, 0, mode->width, mode->height, 0);
			break;
		}
		case ScreenMode::Borderless:
		{
			glfwSetWindowMonitor(window, monitor, 0, 0, mode->width, mode->height, mode->refreshRate);
			break;
		}
		}
	}
}
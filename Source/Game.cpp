#include "Game.h"
#include <exception>
#include <SDL2/SDL.h>
#include "Accessor.h"
#include "ComponentManager.h"
#include "ConfigFile.h"
#include "InputManager.h"
#include "Log.h"
#include "MathFunctions.h"
#include "RenderManager.h"
#include "ResourceManager.h"
#include "SceneManager.h"
#include "WindowManager.h"

namespace ArenaBoss
{
	Game::Game()
	{
		try
		{
			ConfigFile config{ "Config.txt" };

			const char* name = config("Common", "Name")->c_str();
			uint32_t width = std::stoi(*config("Common", "Width"));
			uint32_t height = std::stoi(*config("Common", "Height"));
			std::string screenStr = *config("Common", "ScreenMode");

			ScreenMode screenMode = ScreenMode::Window;
			if (screenStr == "FullScreen")
				screenMode = ScreenMode::FullScreen;
			else if (screenStr == "Borderless")
				screenMode = ScreenMode::Borderless;

			windowManager = new WindowManager{ name, width, height, screenMode };
			Accessor<WindowManager>::manager = windowManager;

			resourceManager = new ResourceManager{};
			Accessor<ResourceManager>::manager = resourceManager;

			renderManager = new RenderManager{};
			Accessor<RenderManager>::manager = renderManager;

			inputManager = new InputManager{};
			Accessor<InputManager>::manager = inputManager;

			sceneManager = new SceneManager{ *config("Scene", "StartName") };
			Accessor<SceneManager>::manager = sceneManager;

			componentManager = new ComponentManager{};
			Accessor<ComponentManager>::manager = componentManager;
		}
		catch (std::exception& e)
		{
			Log(e.what());
		}
	}

	Game::~Game()
	{
		delete componentManager;
		delete sceneManager;
		delete inputManager;
		delete renderManager;
		delete resourceManager;
		delete windowManager;
		SDL_Quit();
	}

	int Game::Run()
	{
		try
		{
			while (isRun)
			{
				while (!SDL_TICKS_PASSED(SDL_GetTicks(), ticksCount + 16));
				const auto deltaTime = Math::Min(static_cast<float>(SDL_GetTicks() - ticksCount) / 1000.0f, 0.05f);
				ticksCount = SDL_GetTicks();

				inputManager->Update();
				sceneManager->Update();
				componentManager->Update();
				renderManager->Draw();
			}
		}
		catch (std::exception& e)
		{
			Log(e.what());
		}

		return 0;
	}
}
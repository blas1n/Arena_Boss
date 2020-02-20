#include "Game.h"
#include <exception>
#include <SDL2/SDL.h>
#include "Accessor.h"
#include "ConfigFile.h"
#include "InputManager.h"
#include "Log.h"
#include "MathFunctions.h"
#include "RenderManager.h"
#include "SceneManager.h"
#include "WindowManager.h"

namespace ArenaBoss
{
	Game::Game()
		: windowManager(nullptr),
		renderManager(nullptr),
		inputManager(nullptr),
		ticksCount(0u)
	{
		if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO))
		{
			Log("Unable to initialize SDL: %s", SDL_GetError());
		}

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

			renderManager = new RenderManager{};
			Accessor<RenderManager>::manager = renderManager;

			inputManager = new InputManager{};
			Accessor<InputManager>::manager = inputManager;

			sceneManager = new SceneManager{};
			Accessor<SceneManager>::manager = sceneManager;
		}
		catch (std::exception& e)
		{
			Log(e.what());
		}
	}

	Game::~Game()
	{
		delete sceneManager;
		delete inputManager;
		delete renderManager;
		delete windowManager;
		SDL_Quit();
	}

	int Game::Run()
	{
		bool isRun = true;

		while (isRun)
		{
			while (!SDL_TICKS_PASSED(SDL_GetTicks(), ticksCount + 16));
			const auto deltaTime = Math::Min(static_cast<float>(SDL_GetTicks() - ticksCount) / 1000.0f, 0.05f);
			ticksCount = SDL_GetTicks();

			isRun = isRun && inputManager->Update();
			isRun = isRun && sceneManager->Update();
			isRun = isRun && renderManager->Update();
		}

		return 0;
	}
}
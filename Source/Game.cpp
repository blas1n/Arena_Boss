#include "Game.h"
#include <exception>
#include <SDL2/SDL.h>
#include "Accessor.h"
#include "ConfigFile.h"
#include "InputManager.h"
#include "Log.h"
#include "Util.h"
#include "WindowManager.h"

namespace ArenaBoss
{
	Game::Game()
	{
		if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO))
		{
			Log("Unable to initialize SDL: %s", SDL_GetError());
		}

		try
		{
			ConfigFile config{ "Config.txt" };

			std::string name = *config("Common", "Name");
			uint32_t width = std::stoi(*config("Common", "Width"));
			uint32_t height = std::stoi(*config("Common", "Height"));
			std::string screenStr = *config("Common", "ScreenMode");

			ScreenMode screenMode = ScreenMode::Window;
			if (screenStr == "FullScreen")
				screenMode = ScreenMode::FullScreen;
			else if (screenStr == "Borderless")
				screenMode = ScreenMode::Borderless;

		
			Accessor<WindowManager>::manager = new WindowManager
			{
				name.c_str(),
				width, height,
				screenMode
			};

			Accessor<InputManager>::manager = new InputManager{};
		}
		catch (std::exception& e)
		{
			Log(e.what());
		}
	}

	Game::~Game()
	{
		Util::DeleteObjects(Accessor<InputManager>::manager);
		Util::DeleteObjects(Accessor<WindowManager>::manager);
		SDL_Quit();
	}

	int Game::Run()
	{
		while (true)
		{
			if (!Accessor<InputManager>::manager->Update())
				break;
		}

		return 0;
	}
}
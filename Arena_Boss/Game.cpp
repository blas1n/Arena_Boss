#include "Game.h"
#include <exception>
#include <SDL2/SDL.h>
#include "Accessor.h"
#include "InputManager.h"
#include "Log.h"
#include "Util.h"

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
			Accessor<InputManager>::manager = new InputManager{};
		}
		catch (std::exception& e)
		{
			Log(e.what());
		}
	}

	Game::~Game()
	{
		Util::DeleteObjects(&Accessor<InputManager>::Get());
		SDL_Quit();
	}

	int Game::Run()
	{
		while (true)
		{
			// Game update code
		}

		return 0;
	}
}
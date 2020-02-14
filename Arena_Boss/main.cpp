#define SDL_MAIN_HANDLED

#include <SDL2/SDL.h>
#include "Game.h"

int main(int argc, char** argv)
{
	ArenaBoss::Game game;
	return game.Run();
}
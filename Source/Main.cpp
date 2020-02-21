#define SDL_MAIN_HANDLED

#include <SDL2/SDL.h>
#include "Game.h"

int main(int argc, char** argv)
{
	return ArenaBoss::Game{}.Run();
}
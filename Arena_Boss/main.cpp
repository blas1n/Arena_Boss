#define WIN32_LEAN_AND_MEAN
#include <Windows.h>
#include "Game.h"

int APIENTRY WinMain(_In_ HINSTANCE hInstance,
    _In_opt_ HINSTANCE hPrevInstance,
    _In_ LPSTR lpCmdLine,
    _In_ int nShowCmd)
{
	ArenaBoss::Game game;
	return game.Run();
}
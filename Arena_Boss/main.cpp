#include "Common.h"
#include "Game.h"

int APIENTRY _tWinMain(_In_ HINSTANCE hInstance,
    _In_opt_ HINSTANCE hPrevInstance,
    _In_ LPTSTR lpCmdLine,
    _In_ int nShowCmd)
{
	ArenaBoss::Game game;
	return game.Run();
}
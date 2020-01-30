#include "Game.h"
#include "Accessor.h"
#include "D3D.h"
#include "InputManager.h"
#include "Windows.h"

namespace ArenaBoss
{
	Game::Game()
		: windows(new Windows{ TEXT("Arena Boss"), 1920, 1080 }),
		d3d(new D3D{ *windows, 1, 0 })
	{
		Accessor<InputManager>::manager = new InputManager{ *windows };
	}

	Game::~Game()
	{
		delete& Accessor<InputManager>::Get();
	}

	int Game::Run()
	{
		while (true)
		{
			windows->ProcessEvent();
			Accessor<InputManager>::Get().Update();
			d3d->ClearRenderTarget();
			d3d->ClearDepthStencil();

			// Game update code

			d3d->Present();
		}

		return 0;
	}
}
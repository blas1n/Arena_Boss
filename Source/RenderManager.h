#pragma once

#include <SDL2/SDL.h>
#include "Accessor.h"

namespace ArenaBoss
{
	class RenderManager : Accessor<class WindowManager>
	{
	public:
		RenderManager();
		~RenderManager();

		void Draw();

	private:
		SDL_Window* window;
		SDL_GLContext context;
	};
}
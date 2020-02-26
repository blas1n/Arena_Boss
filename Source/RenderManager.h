#pragma once

#include <SDL2/SDL.h>
#include <vector>
#include "Accessor.h"

namespace ArenaBoss
{
	class DrawableComponent;

	class RenderManager : Accessor<class WindowManager>
	{
	public:
		RenderManager();
		~RenderManager();

		void Draw();

	private:
		friend class ComponentManager;

		void RegisterComponent(DrawableComponent* component);
		void UnregisterComponent(DrawableComponent* component);

	private:
		SDL_Window* window;
		SDL_GLContext context;

		std::vector<DrawableComponent*> meshComponents;
		std::vector<DrawableComponent*> spriteComponents;
	};
}
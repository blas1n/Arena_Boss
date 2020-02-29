#pragma once

#include <SDL2/SDL.h>
#include <vector>
#include "Accessor.h"

namespace ArenaBoss
{
	class MeshDrawableComponent;
	class SpriteDrawableComponent;
	class RenderTree;

	class RenderManager final : Accessor<class WindowManager>, Accessor<class ResourceManager>
	{
	public:
		RenderManager();

		RenderManager(const RenderManager&) = delete;
		RenderManager(RenderManager&&) = delete;

		RenderManager& operator=(const RenderManager&) = delete;
		RenderManager& operator=(RenderManager&&) = delete;

		~RenderManager();

		void Draw();

		void SetComponentInTree(MeshDrawableComponent* component);

	private:
		friend class ComponentManager;

		void RegisterComponent(MeshDrawableComponent* component);

		inline void RegisterComponent(SpriteDrawableComponent* component)
		{
			spriteComponents.push_back(component);
		}

		void UnregisterComponent(MeshDrawableComponent* component);
		void UnregisterComponent(SpriteDrawableComponent* component);

	private:
		using WindowAccessor = Accessor<WindowManager>;
		using ResourceAccessor = Accessor<ResourceManager>;

		std::vector<MeshDrawableComponent*> meshComponents;
		std::vector<SpriteDrawableComponent*> spriteComponents;

		RenderTree* renderTree;
		SDL_Window* window;

		ResourceManager& resourceManager;
		SDL_GLContext context;
	};
}
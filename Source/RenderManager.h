#pragma once

#include <SDL2/SDL.h>
#include <vector>
#include "Accessor.h"
#include "Matrix4x4.h"

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

		inline void SetViewMatrix(const Math::Matrix4x4& inView) { view = inView; }

	private:
		friend class ComponentManager;

		void RegisterComponent(MeshDrawableComponent* component);

		inline void RegisterComponent(SpriteDrawableComponent* component)
		{
			spriteComponents.push_back(component);
		}

		void UnregisterComponent(MeshDrawableComponent* component);
		void UnregisterComponent(SpriteDrawableComponent* component);

		void GenerateSpriteResource();

	private:
		using WindowAccessor = Accessor<WindowManager>;
		using ResourceAccessor = Accessor<ResourceManager>;

		std::vector<MeshDrawableComponent*> meshComponents;
		std::vector<SpriteDrawableComponent*> spriteComponents;

		RenderTree* renderTree;
		SDL_Window* window;

		ResourceManager& resourceManager;
		SDL_GLContext context;

		Math::Matrix4x4 view;
		Math::Matrix4x4 projection;

		uint32_t width;
		uint32_t height;
	};
}
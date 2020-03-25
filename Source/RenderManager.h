#pragma once

#include <SDL2/SDL.h>
#include <vector>
#include "Accessor.h"
#include "Matrix4x4.h"

namespace ArenaBoss
{
	class MeshComponent;
	class SpriteComponent;
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

		void SetComponentInTree(MeshComponent* component);

		inline void SetViewMatrix(const Math::Matrix4x4& inView) { view = inView; }

	private:
		friend class ComponentManager;

		void RegisterComponent(MeshComponent* component);

		inline void RegisterComponent(SpriteComponent* component)
		{
			spriteComponents.push_back(component);
		}

		void UnregisterComponent(MeshComponent* component);
		void UnregisterComponent(SpriteComponent* component);

		void GenerateSpriteResource();

	private:
		using WindowAccessor = Accessor<WindowManager>;
		using ResourceAccessor = Accessor<ResourceManager>;

		std::vector<MeshComponent*> meshComponents;
		std::vector<SpriteComponent*> spriteComponents;

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
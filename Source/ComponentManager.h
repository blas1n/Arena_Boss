#pragma once

#include <vector>
#include "Accessor.h"

namespace ArenaBoss
{
	class Component;
	class MeshDrawableComponent;
	class SpriteDrawableComponent;
	class UpdatableComponent;

	class ComponentManager final : private Accessor<class RenderManager>
	{
	public:
		ComponentManager() = default;

		ComponentManager(const ComponentManager&) = delete;
		ComponentManager(ComponentManager&&) = delete;

		ComponentManager& operator=(const ComponentManager&) = delete;
		ComponentManager& operator=(ComponentManager&&) = delete;

		~ComponentManager() = default;

		void Update();

		template <class ComponentType>
		ComponentType* CreateComponent()
		{
			auto* component = new ComponentType{};
			RegisterComponent(component);
			return component;
		}
		
		void DeleteComponent(Component* component);
		void DeleteComponent(MeshDrawableComponent* component);
		void DeleteComponent(SpriteDrawableComponent* component);
		void DeleteComponent(UpdatableComponent* component);

	private:
		inline void RegisterComponent(Component* component) {}

		void RegisterComponent(MeshDrawableComponent* component);
		void RegisterComponent(SpriteDrawableComponent* component);

		inline void RegisterComponent(UpdatableComponent* component)
			{ updatableComponents.push_back(component); }

	private:
		std::vector<UpdatableComponent*> updatableComponents;
	};
}
#pragma once

#include <vector>
#include "Accessor.h"

namespace ArenaBoss
{
	class Component;
	class DrawableComponent;
	class UpdatableComponent;

	class ComponentManager : private Accessor<class RenderManager>
	{
	public:
		void Update();

		template <class ComponentType>
		ComponentType* CreateComponent()
		{
			auto* component = new ComponentType{};
			RegisterComponent(component);
			return component;
		}
		
		void DeleteComponent(Component* component);
		void DeleteComponent(DrawableComponent* component);
		void DeleteComponent(UpdatableComponent* component);

	private:
		inline void RegisterComponent(Component* component) {}

		void RegisterComponent(DrawableComponent* component);

		inline void RegisterComponent(UpdatableComponent* component)
			{ updatableComponents.push_back(component); }

	private:
		std::vector<UpdatableComponent*> updatableComponents;
	};
}
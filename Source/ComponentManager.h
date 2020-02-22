#pragma once

#include <vector>

namespace ArenaBoss
{
	class Component;

	class ComponentManager
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

	private:
		void RegisterComponent(Component* component);

	private:
		std::vector<Component*> updatableComponents;
	};
}
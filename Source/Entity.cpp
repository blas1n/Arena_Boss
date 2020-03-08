#include "Entity.h"
#include "Component.h"

namespace ArenaBoss
{
	void Entity::Init()
	{
		for (auto* component : components)
			component->Init();
	}

	void Entity::Release()
	{
		for (auto* component : components)
			component->Release();
	}

	Component* Entity::FindComponent(const std::string& componentName)
	{
		for (auto& component : components)
			if (component->ClassName() == componentName)
				return component;

		throw std::exception{ "No corresponding component exists." };
	}
}
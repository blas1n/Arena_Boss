#include "ComponentManager.h"
#include <algorithm>
#include <exception>
#include "Component.h"

namespace ArenaBoss
{
	void ComponentManager::Update()
	{
		for (auto& component : updatableComponents)
			component->Update();
	}

	void ComponentManager::DeleteComponent(Component* component)
	{
		switch (component->GetTag())
		{
		case ComponentTag::None: break;
		case ComponentTag::Input: break;
		case ComponentTag::Updatable:
		{
			const auto iter = std::find(updatableComponents.begin(), updatableComponents.end(), component);
			updatableComponents.erase(iter);
			break;
		}

		default:
			throw std::exception{ "Unknown component" };
		}

		delete component;
	}

	void ComponentManager::RegisterComponent(Component* component)
	{
		switch (component->GetTag())
		{
		case ComponentTag::None: break;
		case ComponentTag::Input: break;
		case ComponentTag::Updatable:
			updatableComponents.push_back(component);
			break;

		default:
			throw std::exception{ "Unknown component" };
		}
	}
}
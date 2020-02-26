#include "ComponentManager.h"
#include <algorithm>
#include <exception>
#include "DrawableComponent.h"
#include "RenderManager.h"
#include "UpdatableComponent.h"

namespace ArenaBoss
{
	void ComponentManager::Update()
	{
		for (auto& component : updatableComponents)
			component->Update();
	}

	void ComponentManager::DeleteComponent(Component* component)
	{
		delete component;
	}

	void ComponentManager::DeleteComponent(MeshDrawableComponent* component)
	{
		Accessor<RenderManager>::GetManager().UnregisterComponent(component);
		delete component;
	}

	void ComponentManager::DeleteComponent(SpriteDrawableComponent* component)
	{
		Accessor<RenderManager>::GetManager().UnregisterComponent(component);
		delete component;
	}

	void ComponentManager::DeleteComponent(UpdatableComponent* component)
	{
		const auto iter = std::find(updatableComponents.begin(), updatableComponents.end(), component);
		updatableComponents.erase(iter);
		delete component;
	}

	void ComponentManager::RegisterComponent(MeshDrawableComponent* component)
	{
		Accessor<RenderManager>::GetManager().RegisterComponent(component);
	}

	void ComponentManager::RegisterComponent(SpriteDrawableComponent* component)
	{
		Accessor<RenderManager>::GetManager().RegisterComponent(component);
	}
}
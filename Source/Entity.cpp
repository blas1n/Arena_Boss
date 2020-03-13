#include "Entity.h"
#include "Transform.h"

namespace ArenaBoss
{
	Entity::Entity(const std::string& inName)
		: name(inName), transform(nullptr), components()
	{
		transform = GetManager().CreateComponent<Transform>(this);
	}

	Entity::~Entity() { delete transform; }

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

	void Entity::Load(const Json::Object& object)
	{
		for (auto component : components)
			delete component;

		components.clear();

		// Load Component
	}

	void Entity::Save(Json::JsonSaver& saver)
	{

	}

	Component* Entity::FindComponent(const std::string& componentName)
	{
		for (auto& component : components)
			if (component->ClassName() == componentName)
				return component;

		throw std::exception{ "No corresponding component exists." };
	}
}
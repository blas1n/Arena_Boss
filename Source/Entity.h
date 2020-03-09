#pragma once

#include <string>
#include <vector>
#include "Accessor.h"
#include "ComponentManager.h"
#include "Game.h"
#include "Log.h"

namespace ArenaBoss
{
	class Component;
	class Transform;

	class Entity final : private Accessor<ComponentManager>
	{
	public:
		void Init();
		void Release();

		template <class ComponentType>
		ComponentType& GetComponent() 
		{
			const auto component = FindComponent(ComponentType::StaticClassName());
			return *(static_cast<ComponentType*>(component));
		}

		template <class ComponentType>
		const ComponentType& GetComponent() const
		{
			const auto component = FindComponent(ComponentType::StaticClassName());
			return *(static_cast<ComponentType*>(component));
		}

		template <>
		inline Transform& GetComponent<Transform>() noexcept { return *transform; }

		template <>
		inline const Transform& GetComponent<Transform>() const noexcept { return *transform; }

		template <class ComponentType>
		ComponentType& AddComponent()
		{
			auto* component = GetManager().CreateComponent<ComponentType>(this);
			components.push_back(component);
			return component;
		}

		template <>
		Transform& AddComponent<Transform>() noexcept
		{
			Log("Transform cannot be added.");
			Game::Exit();
		}

	private:
		Component* FindComponent(const std::string& componentName);

	private:
		std::string name;
		Transform* transform;
		std::vector<Component*> components;
	};
}
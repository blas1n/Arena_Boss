#pragma once

#include <cassert>
#include <type_traits>
#include <vector>
#include "Accessor.h"
#include "Component.h"
#include "ComponentManager.h"
#include "Log.h"

namespace ArenaBoss
{
	class Transform;

	class Entity : private Accessor<ComponentManager>
	{
	public:
		void Init();
		void Release();

		template <class ComponentType>
		ComponentType& GetComponent() 
		{
			static_assert(std::is_base_of<Component, ComponentType>::value,
				"ComponentType is not Component");

			return *(static_cast<ComponentType*>(FindComponent()));
		}

		template <class ComponentType>
		const ComponentType& GetComponent() const
		{
			static_assert(std::is_base_of<Component, ComponentType>::value,
				"ComponentType is not Component");

			return *(static_cast<ComponentType*>(FindComponent()));
		}

		template <>
		inline Transform& GetComponent<Transform>() noexcept { return *transform; }

		template <>
		inline const Transform& GetComponent<Transform>() const noexcept { return *transform; }

		template <class ComponentType>
		ComponentType& AddComponent()
		{
			static_assert(std::is_base_of<Component, ComponentType>::value,
				"ComponentType is not Component");

			auto* component = GetManager().CreateComponent<ComponentType>();
			components.push_back(component);
			return component;
		}

		template <>
		Transform& AddComponent<Transform>() noexcept
		{
			Log("Transform cannot be added.");
			std::abort();
		}

	private:
		Component* FindComponent(const std::string& componentName);

	private:
		std::string name;
		Transform* transform;
		std::vector<Component*> components;
	};
}
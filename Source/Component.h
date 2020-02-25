#pragma once

#include <string>

namespace ArenaBoss
{
	class Entity;

	class Component
	{
	public:
		Component(const Component&) = delete;
		Component(Component&&) = delete;

		Component& operator=(const Component&) = delete;
		Component& operator=(Component&&) = delete;

		virtual ~Component() = default;

		inline static const std::string& StaticName() noexcept
		{
			static const std::string name{ "Component" };
			return name;
		}

		inline virtual const std::string& Name() const noexcept
		{
			return Component::StaticName();
		}

		Entity* GetEntity() noexcept { return entity; }
		void SetEntity(Entity* inEntity) noexcept { entity = inEntity; }

	private:
		friend class ComponentManager;
		Component() = default;

		Entity* entity;
	};
}

#define GENERATE_COMPONENT(name) \
public: \
	inline static const std::string& StaticName() noexcept \
	{ \
		static const std::string componentName{ #name }; \
		return componentName; \
	} \
\
	inline const std::string& Name() const noexcept override \
	{ \
		return name::StaticName(); \
	}
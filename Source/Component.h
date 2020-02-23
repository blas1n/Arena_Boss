#pragma once

#include <string>

namespace ArenaBoss
{
	class Entity;

	enum class ComponentTag
	{
		None,
		Updatable,
		Input,
		Render
	};

	class Component
	{
	public:
		Component() = default;

		Component(const Component&) = delete;
		Component(Component&&) = delete;

		Component& operator=(const Component&) = delete;
		Component& operator=(Component&&) = delete;

		virtual ~Component() = default;

		virtual void Update() = 0;
		virtual ComponentTag GetTag() const noexcept = 0;

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
		Entity* entity;
	};
}
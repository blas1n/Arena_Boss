#pragma once

#include <string>

namespace ArenaBoss
{
	class Entity;

	enum class ComponentKind
	{
		None,
		Updatable,
		Input
	};

	class Component
	{
	public:
		~Component() = default;

		virtual void Update() = 0;
		virtual ComponentKind GetKind() const noexcept = 0;

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
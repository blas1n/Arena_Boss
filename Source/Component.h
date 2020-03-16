#pragma once

#include <string>
#include "JsonForwarder.h"

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
		
		virtual void Init() {}
		virtual void Release() {}

		virtual void Load(const Json::Object& object) {}
		virtual void Save(Json::JsonSaver& saver) const;

		inline static const std::string& StaticClassName() noexcept
		{
			static const std::string name{ "Component" };
			return name;
		}

		inline virtual const std::string& ClassName() const noexcept
		{
			return Component::StaticClassName();
		}

		Entity* GetEntity() noexcept { return entity; }

	protected:
		Component(Entity* inEntity) : entity(inEntity) {}

	private:
		friend class ComponentManager;
		Entity* entity;
	};

#define GET_MACRO(_1, _2, NAME, ...) NAME
#define GENERATE_COMPONENT(...) GET_MACRO(__VA_ARGS__, GENERATE_COMPONENT_CUSTOM, GENERATE_COMPONENT_DEFAULT)(__VA_ARGS__)

#define GENERATE_COMPONENT_SHARE(name) \
public: \
	inline static const std::string& StaticClassName() noexcept \
	{ \
		static const std::string componentName{ #name }; \
		return componentName; \
	} \
\
	inline const std::string& ClassName() const noexcept override \
	{ \
		return name::StaticClassName(); \
	} \
\
private: \
	friend class ComponentManager;

#define GENERATE_COMPONENT_DEFAULT(name) \
GENERATE_COMPONENT_SHARE(name) \
protected: \
	name(Entity* inEntity) : Component(inEntity) {}

#define GENERATE_COMPONENT_CUSTOM(name, super) \
GENERATE_COMPONENT_SHARE(name) \
protected: \
	name(Entity* inEntity) : super(inEntity) {}
}
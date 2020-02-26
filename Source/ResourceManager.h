#pragma once

#include <string>
#include <vector>

namespace ArenaBoss
{
	class Resource;

	class ResourceManager
	{
	public:
		ResourceManager() = default;

		ResourceManager(const ResourceManager&) = delete;
		ResourceManager(ResourceManager&&) = delete;

		ResourceManager& operator=(const ResourceManager&) = delete;
		ResourceManager& operator=(ResourceManager&&) = delete;

		~ResourceManager() = default;

		template <class ResourceType>
		ResourceType* CreateResource(const std::string& name)
		{
			auto* resource = new ResourceType{ name };
			RegisterResource(resource);
			return resource;
		}

		void DeleteResource(const std::string& name);

		template <class ResourceType>
		ResourceType* GetResource(const std::string& name)
		{
			return static_cast<ResourceType*>(GetResourceImpl(name));
		}

	private:
		void RegisterResource(Resource* name);
		Resource* GetResourceImpl(const std::string& name);

	private:
		std::vector<Resource*> resources;
	};
}
#pragma once

#include <string>
#include <vector>

namespace ArenaBoss
{
	class Resource;

	class ResourceManager final
	{
	public:
		ResourceManager() = default;

		ResourceManager(const ResourceManager&) = delete;
		ResourceManager(ResourceManager&&) = delete;

		ResourceManager& operator=(const ResourceManager&) = delete;
		ResourceManager& operator=(ResourceManager&&) = delete;

		~ResourceManager() = default;

		template <class ResourceType, class... Args>
		ResourceType* CreateResource(const std::string& name, Args&&... args)
		{
			std::vector<Resource*>::iterator iter;

			try
			{
				iter = IteratorFinder::FindLowerIterator(resources, name);
			}
			catch (std::exception&)
			{
				return *iter;
			}

			auto* resource = new ResourceType{ name, std::forward<Args>(args)... };
			RegisterResource(resource, iter);
			return resource;
		}

		void DeleteResource(const std::string& name);

		template <class ResourceType>
		ResourceType* GetResource(const std::string& name)
		{
			const auto resource = FindResource(name, ResourceType::StaticClassName());
			return static_cast<ResourceType*>(resource);
		}

	private:
		void RegisterResource(Resource* name, std::vector<Resource*>::iterator iter);
		Resource* FindResource(const std::string& name, const std::string& resourceName);

	private:
		std::vector<Resource*> resources;
	};
}
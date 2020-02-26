#include "ResourceManager.h"
#include "IteratorFinder.h"
#include "Resource.h"

namespace ArenaBoss
{
	void ResourceManager::DeleteResource(const std::string& name)
	{
		const auto iter = IteratorFinder::FindSameIterator(resources, name);
		delete *iter;
		resources.erase(iter);
	}

	void ResourceManager::RegisterResource(Resource* resource)
	{
		const auto iter = IteratorFinder::
			FindLowerIterator(resources,resource->GetName());

		resources.emplace_back(std::move(resource));
		std::rotate(resources.rbegin(), resources.rbegin() + 1,
			std::reverse_iterator{ iter });
	}

	Resource* ResourceManager::GetResourceImpl(const std::string& name)
	{
		return *IteratorFinder::FindSameIterator(resources, name);
	}
}
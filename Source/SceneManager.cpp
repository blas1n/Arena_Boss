#include "SceneManager.h"
#include <algorithm>
#include <exception>
#include "Scene.h"

namespace ArenaBoss
{
	namespace
	{
		template <bool IsFindSame>
		decltype(auto) FindIterByName(std::vector<Scene>& scenes, const std::string& name)
		{
			const auto iter = std::lower_bound(scenes.begin(), scenes.end(), name);

			if constexpr (IsFindSame)
				if (name != *iter)
					throw std::exception{ "No scene of that name exists" };
			else
				if (name == *iter)
					throw std::exception{ "Scene with the same name already exists" };

			return iter;
		}
	}

	Scene& SceneManager::CreateScene(const std::string& name)
	{
		const auto iter = FindIterByName<false>(scenes, name);

		Scene scene{ name };
		scenes.emplace_back(std::move(scene));
		std::rotate(scenes.rbegin(), scenes.rbegin() + 1, std::reverse_iterator{ iter });
		return *iter;
	}

	void SceneManager::ReserveScene(const std::string& name)
	{
		const auto iter = FindIterByName<true>(scenes, name);
		reservedScene = std::addressof(*iter);
	}

	void SceneManager::RemoveScene(const std::string& name)
	{
		const auto iter = FindIterByName<true>(scenes, name);
		scenes.erase(iter);
	}

	Scene& SceneManager::GetCurrentScene()
	{
		if (curScene == nullptr)
			throw std::exception{ "The current scene does not exist" };

		return *curScene;
	}

	void SceneManager::Update()
	{
		if (reservedScene)
		{
			if (curScene)
				curScene->Release();

			reservedScene->Init();
			curScene = std::exchange(reservedScene, nullptr);
		}
	}
}
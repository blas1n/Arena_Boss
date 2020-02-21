#include "SceneManager.h"
#include <algorithm>
#include <exception>
#include "Scene.h"

namespace ArenaBoss
{
	Scene& SceneManager::CreateScene(const std::string& name)
	{
		const auto lowIter = std::lower_bound(scenes.begin(), scenes.end(), name);

		if (name == *lowIter)
			throw std::exception{ "Scene with the same name already exists" };

		Scene scene{ name };
		scenes.emplace_back(std::move(scene));
		std::rotate(scenes.rbegin(), scenes.rbegin() + 1, std::reverse_iterator{ lowIter });
		return *lowIter;
	}

	void SceneManager::ReserveScene(const std::string& name)
	{
		const auto lowIter = std::lower_bound(scenes.begin(), scenes.end(), name);

		if (name != *lowIter)
			throw std::exception{ "No scene of that name exists" };

		reservedScene = std::addressof(*lowIter);
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

		if (curScene)
			return curScene->Update();

		return true;
	}
}
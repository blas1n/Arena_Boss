#include "SceneManager.h"
#include <algorithm>
#include <exception>
#include "IteratorFinder.h"
#include "Scene.h"

namespace ArenaBoss
{
	Scene& SceneManager::CreateScene(const std::string& name)
	{
		const auto iter = IteratorFinder::FindLowerIterator(scenes, name);

		scenes.emplace_back(new Scene{ name });
		std::rotate(scenes.rbegin(), scenes.rbegin() + 1, std::reverse_iterator{ iter });
		return **iter;
	}

	void SceneManager::ReserveScene(const std::string& name)
	{
		const auto iter = IteratorFinder::FindSameIterator(scenes, name);
		reservedScene = *iter;
	}

	void SceneManager::RemoveScene(const std::string& name)
	{
		const auto iter = IteratorFinder::FindSameIterator(scenes, name);
		delete *iter;
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
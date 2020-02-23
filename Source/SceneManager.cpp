#include "SceneManager.h"
#include <algorithm>
#include <exception>
#include "Scene.h"

namespace ArenaBoss
{
	namespace
	{
		decltype(auto) SceneLowerBound(std::vector<Scene*>& scenes, const std::string& name)
		{
			auto begin = scenes.begin();
			auto count = scenes.size();
			
			while (count > 0)
			{
				auto halfCount = count / 2;
				auto mid = std::next(begin, halfCount);

				if (**mid < name)
				{
					begin = mid + 1;
					count = halfCount + 1;
				}
				else
				{
					count = halfCount;
				}
			}

			return begin;
		}

		template <bool IsFindSame>
		decltype(auto) FindIterByName(std::vector<Scene*>& scenes, const std::string& name)
		{
			const auto iter = SceneLowerBound(scenes, name);

			if constexpr (IsFindSame)
				if (name != **iter)
					throw std::exception{ "No scene of that name exists" };
			else
				if (name == **iter)
					throw std::exception{ "Scene with the same name already exists" };

			return iter;
		}
	}

	Scene& SceneManager::CreateScene(const std::string& name)
	{
		const auto iter = FindIterByName<false>(scenes, name);

		scenes.emplace_back(new Scene{ name });
		std::rotate(scenes.rbegin(), scenes.rbegin() + 1, std::reverse_iterator{ iter });
		return **iter;
	}

	void SceneManager::ReserveScene(const std::string& name)
	{
		const auto iter = FindIterByName<true>(scenes, name);
		reservedScene = *iter;
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
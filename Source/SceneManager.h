#pragma once

#include <string>
#include <vector>

namespace ArenaBoss
{
	class Scene;

	class SceneManager
	{
	public:
		SceneManager() = default;

		SceneManager(const SceneManager&) = delete;
		SceneManager(SceneManager&&) = delete;

		SceneManager& operator=(const SceneManager&) = delete;
		SceneManager& operator=(SceneManager&&) = delete;

		~SceneManager() = default;

		Scene& CreateScene(const std::string& name);
		void ReserveScene(const std::string& name);
		void RemoveScene(const std::string& name);

		Scene& GetCurrentScene();
		void Update();

	private:
		std::vector<Scene*> scenes;

		Scene* curScene = nullptr;
		Scene* reservedScene = nullptr;
	};
}
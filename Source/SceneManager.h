#pragma once

#include <string>
#include <vector>
#include "Scene.h"

namespace ArenaBoss
{
	class Scene;

	class SceneManager
	{
	public:
		Scene& CreateScene(const std::string& name);
		void ReserveScene(const std::string& name);
		void RemoveScene(const std::string& name);

		Scene& GetCurrentScene();
		void Update();

	private:
		Scene* curScene;
		Scene* reservedScene;
		std::vector<Scene> scenes;
	};
}
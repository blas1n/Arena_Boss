#pragma once

#include <string>
#include <vector>

namespace ArenaBoss
{
	class Scene;

	class SceneManager
	{
	public:
		Scene& CreateScene(const std::string& name);
		void ReserveScene(const std::string& name);

		Scene& GetCurrentScene();
		bool Update();

	private:
		Scene* curScene;
		Scene* reservedScene;
		std::vector<Scene> scenes;
	};
}
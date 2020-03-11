#include "SceneManager.h"
#include <algorithm>
#include <exception>
#include "IteratorFinder.h"
#include "Scene.h"

namespace ArenaBoss
{
	SceneManager::SceneManager()
		: scene(new Scene{}), name(), isReserved() {}

	void SceneManager::ReserveScene(const std::string& inName)
	{
		name = inName;
		isReserved = true;
	}

	void SceneManager::ReserveScene(std::string&& inName)
	{
		name = std::move(inName);
		isReserved = true;
	}

	void SceneManager::Update()
	{
		if (isReserved)
		{
			scene->Load(std::move(name));
			isReserved = true;
		}
	}
}
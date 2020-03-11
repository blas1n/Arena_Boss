#include "Scene.h"
#include "Entity.h"

namespace ArenaBoss
{
	Scene::Scene()
		: name(), entities(), isAvailable(false) {}

	void Scene::Load(const std::string& inName)
	{
		name = inName;
	}

	void Scene::Save()
	{

	}
}
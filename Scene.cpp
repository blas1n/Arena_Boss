#include "Scene.h"
#include "Entity.h"

namespace ArenaBoss
{
	void Scene::Init()
	{
		for (auto& entity : entities)
			entity.Init();
	}

	bool Scene::Update()
	{
		bool ret = true;

		for (auto& entity : entities)
			ret = ret && entity.Update();

		return ret;
	}

	void Scene::Release()
	{
		for (auto& entity : entities)
			entity.Release();
	}

	Scene::Scene(const std::string& inName)
		: name(inName) {}
}
#include "Scene.h"

namespace ArenaBoss
{
	void Scene::Init()
	{

	}

	bool Scene::Update()
	{
		return true;
	}

	void Scene::Release()
	{

	}

	Scene::Scene(const std::string& inName)
		: name(inName) {}
}
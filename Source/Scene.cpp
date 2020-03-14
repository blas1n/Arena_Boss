#include "Scene.h"
#include <fstream>
#include <rapidjson/document.h>
#include <rapidjson/stringbuffer.h>
#include <rapidjson/prettywriter.h>
#include "Entity.h"
#include "IteratorFinder.h"
#include "JsonHelper.h"

namespace ArenaBoss
{
	namespace
	{
		rapidjson::Document LoadJson(const std::string& name)
		{
			std::ifstream file{ "Asset\\" + name, std::ios::in | std::ios::binary | std::ios::ate };
			if (!file.is_open())
				throw std::exception{ "File not found." };

			const auto size = file.tellg();
			file.seekg(0, std::ios::beg);

			std::string str;
			str.resize(size);
			file.read(str.data(), size);

			rapidjson::Document doc;
			doc.Parse(str.data());

			if (!doc.IsObject())
				throw std::exception{ "File is not vaild JSON." };

			return doc;
		}
	}

	void Scene::Load()
	{
		for (auto entity : entities)
			delete entity;

		entities.clear();

		const auto doc = LoadJson(name);
		const auto& entities = doc["entities"];

		if (!entities.IsArray())
			throw std::exception{ "File is not vaild." };

		for (rapidjson::SizeType i = 0; i < entities.Size(); ++i)
		{
			const auto& entityObj = entities[i];
			if (!entityObj.IsObject()) continue;

			const auto name = Json::JsonHelper::GetString(entityObj, "name");
			if (!name) throw std::exception{ "Entity is not vaild." };

			auto* entity = AddEntity(*name);
			entity->Load(entityObj);
		}
	}

	void Scene::Load(const std::string& inName)
	{
		name = inName;
		Load();
	}

	void Scene::Load(std::string&& inName)
	{
		name = std::move(inName);
		Load();
	}

	void Scene::Save() const
	{
		rapidjson::Document doc;
		doc.SetObject();

		rapidjson::Value entitiesObj{ rapidjson::kArrayType };
		Json::JsonSaver saver{ doc.GetAllocator(), entitiesObj };

		for (const auto entity : entities) 
			entity->Save(saver);

		doc.AddMember("entities", entitiesObj, doc.GetAllocator());

		rapidjson::StringBuffer buffer;
		rapidjson::PrettyWriter<rapidjson::StringBuffer> writer{ buffer };
		doc.Accept(writer);

		std::ofstream outFile{ name, std::ios::trunc };
		if (outFile.is_open())
			outFile << buffer.GetString();
	}

	void Scene::Save(const std::string& inName)
	{
		name = inName;
		Save();
	}

	void Scene::Save(std::string&& inName)
	{
		name = std::move(inName);
		Save();
	}

	Entity* Scene::AddEntity(const std::string& inName)
	{
		return AddEntity(new Entity{ inName });
	}

	Entity* Scene::AddEntity(Entity* entity)
	{
		const auto iter = IteratorFinder::FindLowerIterator(entities, *entity);

		entities.emplace_back(entity);
		std::rotate(entities.rbegin(), entities.rbegin() + 1, std::reverse_iterator{ iter });
		return *iter;
	}

	void Scene::RemoveEntity(const std::string& inName)
	{
		const auto iter = IteratorFinder::FindSameIterator(entities, inName);
		delete *iter;
		entities.erase(iter);
	}

	void Scene::RemoveEntity(Entity* entity)
	{
		RemoveEntity(entity->GetName());
	}

	Entity* Scene::GetEntity(const std::string& inName)
	{
		const auto iter = IteratorFinder::FindSameIterator(entities, inName);
		return *iter;
	}
}
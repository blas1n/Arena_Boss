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

	void Scene::Init()
	{
		for (auto* entity : entities)
			entity->Init();
	}

	void Scene::Release() noexcept
	{
		for (auto entity : entities)
		{
			entity->Release();
			delete entity;
		}

		entities.clear();
	}

	void Scene::Load()
	{
		Release();

		const auto doc = LoadJson(name);
		const auto& entitiesArray = doc["entities"];

		if (!entitiesArray.IsArray())
			throw std::exception{ "File is not vaild." };

		for (rapidjson::SizeType i = 0; i < entitiesArray.Size(); ++i)
		{
			const auto& entityObj = entitiesArray[i];
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

		rapidjson::Value entitiesArray{ rapidjson::kArrayType };
		auto& alloc = doc.GetAllocator();
		
		for (const auto* entity : entities)
		{
			rapidjson::Value obj{ rapidjson::kObjectType };
			Json::JsonSaver saver{ alloc, obj };
			entity->Save(saver);
			entitiesArray.PushBack(obj, alloc);
		}

		doc.AddMember("entities", entitiesArray, doc.GetAllocator());

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
		try
		{
			const auto iter = IteratorFinder::FindLowerIterator(entities, *entity);

			entities.emplace_back(entity);
			std::rotate(entities.rbegin(), entities.rbegin() + 1, std::reverse_iterator{ iter });
		}
		catch (std::exception&)
		{
			entities.emplace_back(entity);
		}

		return entity;
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
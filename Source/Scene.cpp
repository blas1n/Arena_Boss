#include "Scene.h"
#include <fstream>
#include <rapidjson/document.h>
#include <rapidjson/stringbuffer.h>
#include <rapidjson/prettywriter.h>
#include "Entity.h"
#include "JsonHelper.h"

namespace ArenaBoss
{
	namespace
	{
		rapidjson::Document LoadJson(const std::string& name)
		{
			std::ifstream file{ name, std::ios::in | std::ios::binary | std::ios::ate };
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

	Scene::Scene()
		: name(), entities(), isAvailable(false) {}

	void Scene::Load(const std::string& inName)
	{
		name = inName;

		const auto doc = LoadJson(name);
		const auto& entities = doc["entities"];

		if (!entities.IsArray())
			throw std::exception{ "File is not vaild." };

		for (rapidjson::SizeType i = 0; i < entities.Size(); ++i) {
			const auto& entityObj = entities[i];
			if (!entityObj.IsObject()) continue;

			const auto name = JsonHelper::GetString(entityObj, "name");
			if (!name) throw std::exception{ "Entity is not vaild." };

			auto* entity = AddEntity(*name);
			// Load entities components.
		}
	}

	void Scene::Save()
	{

	}
}
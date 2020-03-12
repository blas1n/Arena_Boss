#pragma once

#include <optional>
#include <rapidjson/document.h>
#include <string>
#include "Vector2.h"
#include "Vector3.h"

namespace ArenaBoss
{
	namespace Math { class Rotator; }

	namespace JsonHelper
	{
		std::optional<int> GetInt(const rapidjson::Value& object, const char* name);
		std::optional<float> GetFloat(const rapidjson::Value& object, const char* name);
		std::optional<std::string> GetString(const rapidjson::Value& object, const char* name);
		std::optional<bool> GetBool(const rapidjson::Value& object, const char* name);
		std::optional<Math::Vector2> GetVector2(const rapidjson::Value& object, const char* name);
		std::optional<Math::Vector3> GetVector3(const rapidjson::Value& object, const char* name);
		std::optional<Math::Rotator> GetRotator(const rapidjson::Value& object, const char* name);

		void AddInt(rapidjson::Document::AllocatorType& alloc,
			rapidjson::Value& object, const char* name, int value);

		void AddFloat(rapidjson::Document::AllocatorType& alloc,
			rapidjson::Value& object, const char* name, float value);

		void AddString(rapidjson::Document::AllocatorType& alloc,
			rapidjson::Value& object, const char* name, const std::string& value);

		void AddBool(rapidjson::Document::AllocatorType& alloc,
			rapidjson::Value& object, const char* name, bool value);

		void AddVector2(rapidjson::Document::AllocatorType& alloc,
			rapidjson::Value& object, const char* name, const Math::Vector2& value);

		void AddVector3(rapidjson::Document::AllocatorType& alloc,
			rapidjson::Value& object, const char* name, const Math::Vector3& value);

		void AddRotator(rapidjson::Document::AllocatorType& alloc,
			rapidjson::Value& object, const char* name, const Math::Rotator& value);
	}
};
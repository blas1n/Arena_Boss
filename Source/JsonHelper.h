#pragma once

#include <optional>
#include <rapidjson/document.h>
#include <string>
#include "JsonForwarder.h"
#include "Vector2.h"
#include "Vector3.h"

namespace ArenaBoss
{
	namespace Math { class Rotator; }

	namespace Json
	{
		struct JsonSaver final
		{
		public:
			JsonSaver(Allocator& inAlloc, Object& inObject)
				: alloc(inAlloc), object(inObject) {}

			JsonSaver(JsonSaver& other, Object& inObject)
				: alloc(other.alloc), object(inObject) {}

		private:
			friend struct JsonHelper;

			Allocator& alloc;
			Object& object;
		};

		struct JsonHelper final
		{
			static std::optional<int> GetInt(const Object& object, const char* name);
			static std::optional<float> GetFloat(const Object& object, const char* name);
			static std::optional<std::string> GetString(const Object& object, const char* name);
			static std::optional<bool> GetBool(const Object& object, const char* name);
			static std::optional<Math::Vector2> GetVector2(const Object& object, const char* name);
			static std::optional<Math::Vector3> GetVector3(const Object& object, const char* name);
			static std::optional<Math::Rotator> GetRotator(const Object& object, const char* name);

			static void AddInt(JsonSaver& saver, const char* name, int value);
			static void AddFloat(JsonSaver& saver, const char* name, float value);
			static void AddString(JsonSaver& saver, const char* name, const std::string& value);
			static void AddBool(JsonSaver& saver, const char* name, bool value);
			static void AddVector2(JsonSaver& saver, const char* name, const Math::Vector2& value);
			static void AddVector3(JsonSaver& saver, const char* name, const Math::Vector3& value);
			static void AddRotator(JsonSaver& saver, const char* name, const Math::Rotator& value);
		};
	}
};
#include "JsonHelper.h"
#include "Rotator.h"

namespace ArenaBoss::JsonHelper
{
	std::optional<int> GetInt(const rapidjson::Value& inObject, const char* name)
	{
		const auto iter = inObject.FindMember(name);
		if (iter == inObject.MemberEnd())
			return {};

		const auto& property = iter->value;
		if (!property.IsInt())
			return {};

		return property.GetInt();
	}

	std::optional<float> GetFloat(const rapidjson::Value& inObject, const char* name)
	{
		const auto iter = inObject.FindMember(name);
		if (iter == inObject.MemberEnd())
			return {};

		const auto& property = iter->value;
		if (!property.IsFloat())
			return {};

		return property.GetFloat();
	}

	std::optional<std::string> GetString(const rapidjson::Value& inObject, const char* name) {
		const auto iter = inObject.FindMember(name);
		if (iter == inObject.MemberEnd())
			return {};

		const auto& property = iter->value;
		if (!property.IsString())
			return {};

		return property.GetString();
	}

	std::optional<bool> GetBool(const rapidjson::Value& inObject, const char* name)
	{
		const auto iter = inObject.FindMember(name);
		if (iter == inObject.MemberEnd())
			return {};

		const auto& property = iter->value;
		if (!property.IsBool())
			return {};

		return property.GetBool();
	}

	std::optional<Math::Vector2> GetVector2(const rapidjson::Value& inObject, const char* name)
	{
		auto iter = inObject.FindMember(name);
		if (iter == inObject.MemberEnd())
			return {};

		auto& property = iter->value;
		if (!property.IsArray() || property.Size() != 2)
			return {};

		for (rapidjson::SizeType i = 0; i < 2; i++)
			if (!property[i].IsFloat())
				return {};

		return Math::Vector2
		{
			property[0].GetFloat(),
			property[1].GetFloat()
		};
	}

	std::optional<Math::Vector3> GetVector3(const rapidjson::Value& inObject, const char* name)
	{
		auto iter = inObject.FindMember(name);
		if (iter == inObject.MemberEnd())
			return {};

		auto& property = iter->value;
		if (!property.IsArray() || property.Size() != 3)
			return {};

		for (rapidjson::SizeType i = 0; i < 3; i++)
			if (!property[i].IsFloat())
				return {};

		return Math::Vector3
		{
			property[0].GetFloat(),
			property[1].GetFloat(),
			property[2].GetFloat()
		};
	}

	std::optional<Math::Rotator> GetRotator(const rapidjson::Value& inObject, const char* name) 
	{
		auto iter = inObject.FindMember(name);
		if (iter == inObject.MemberEnd())
			return {};

		auto& property = iter->value;
		if (!property.IsArray() || property.Size() != 3)
			return {};

		for (rapidjson::SizeType i = 0; i < 3; i++)
			if (!property[i].IsFloat())
				return {};

		return Math::Rotator
		{
			property[0].GetFloat(),
			property[1].GetFloat(),
			property[2].GetFloat()
		};
	}

	void AddInt(rapidjson::Document::AllocatorType& alloc,
		rapidjson::Value& inObject, const char* name, int value)
	{
		rapidjson::Value v{ value };
		inObject.AddMember(rapidjson::StringRef(name), v, alloc);
	}

	void AddFloat(rapidjson::Document::AllocatorType& alloc,
		rapidjson::Value& inObject, const char* name, float value)
	{
		rapidjson::Value v{ value };
		inObject.AddMember(rapidjson::StringRef(name), v, alloc);
	}

	void AddString(rapidjson::Document::AllocatorType& alloc,
		rapidjson::Value& inObject, const char* name, const std::string& value)
	{
		rapidjson::Value v;
		v.SetString(value.c_str(), static_cast<rapidjson::SizeType>(value.length()), alloc);
		inObject.AddMember(rapidjson::StringRef(name), v, alloc);
	}

	void AddBool(rapidjson::Document::AllocatorType& alloc,
		rapidjson::Value& inObject, const char* name, const bool value)
	{
		rapidjson::Value v{ value };
		inObject.AddMember(rapidjson::StringRef(name), v, alloc);
	}

	void AddVector2(rapidjson::Document::AllocatorType& alloc,
		rapidjson::Value& inObject, const char* name, const Math::Vector2& value)
	{
		rapidjson::Value v{ rapidjson::kArrayType };

		v.PushBack(rapidjson::Value{ value.x }.Move(), alloc);
		v.PushBack(rapidjson::Value{ value.y }.Move(), alloc);

		inObject.AddMember(rapidjson::StringRef(name), v, alloc);
	}

	void AddVector3(rapidjson::Document::AllocatorType& alloc,
		rapidjson::Value& inObject, const char* name, const Math::Vector3& value)
	{
		rapidjson::Value v{ rapidjson::kArrayType };

		v.PushBack(rapidjson::Value{ value.x }.Move(), alloc);
		v.PushBack(rapidjson::Value{ value.y }.Move(), alloc);
		v.PushBack(rapidjson::Value{ value.z }.Move(), alloc);

		inObject.AddMember(rapidjson::StringRef(name), v, alloc);
	}

	void AddRotator(rapidjson::Document::AllocatorType& alloc,
		rapidjson::Value& inObject, const char* name, const Math::Rotator& value)
	{
		rapidjson::Value v{ rapidjson::kArrayType };

		v.PushBack(rapidjson::Value{ value.roll }.Move(), alloc);
		v.PushBack(rapidjson::Value{ value.pitch }.Move(), alloc);
		v.PushBack(rapidjson::Value{ value.yaw }.Move(), alloc);

		inObject.AddMember(rapidjson::StringRef(name), v, alloc);
	}
}
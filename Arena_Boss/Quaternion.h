#pragma once

#include "Vector4.h"

namespace ArenaBoss::Math
{
	class Quaternion final
	{
	public:
		static const Quaternion IDENTITY;

	public:
		union
		{
			Vector4 value;

			struct
			{
				float x;
				float y;
				float z;
				float w;
			};
		};

	public:
		Quaternion() noexcept = default;

		Quaternion(const Quaternion&) noexcept = default;
		Quaternion(Quaternion&&) noexcept = default;

		explicit Quaternion(float inX, float inY, float inZ, float inW) noexcept
			: value(inX, inY, inZ, inW) {}

		explicit Quaternion(const float elems[4]) noexcept
			: value(elems) {}

		explicit Quaternion(const Vector4& v) noexcept
			: value(v) {}

		explicit Quaternion(const class Vector3& axis, float angle) noexcept;

		~Quaternion() = default;

		Quaternion& operator=(const Quaternion&) noexcept = default;
		Quaternion& operator=(Quaternion&&) noexcept = default;

		inline explicit operator Vector4() const noexcept { return value; }
		inline Vector4 AsVector() const noexcept { return value; }

		inline void Set(float inX, float inY, float inZ, float inW) noexcept { value.Set(inX, inY, inZ, inW); }
		inline void Set(const float elems[4]) noexcept { value.Set(elems); }

		inline float operator[](size_t idx) const noexcept { return value[idx]; }

		inline float Length() const noexcept { return value.Length(); }
		inline float LengthSqrt() const noexcept { return value.LengthSqrt(); }

		inline Quaternion Normalized() const noexcept { return Quaternion{ value.Normalized() }; }
		inline void Normalize() noexcept { value.Normalize(); }

		inline Quaternion operator-() const noexcept
		{
			const auto vec = DirectX::XMLoadFloat4(&value.value);
			return Quaternion{ DirectX::XMQuaternionConjugate(vec) };
		}

		inline Quaternion& operator*=(const Quaternion& other) noexcept
		{
			const auto lhs = DirectX::XMLoadFloat4(&value.value);
			const auto rhs = DirectX::XMLoadFloat4(&other.value.value);
			value = DirectX::XMQuaternionMultiply(lhs, rhs);
			return *this;
		}

		inline static float Dot(const Quaternion& lhs, const Quaternion& rhs)
		{
			return Vector4::Dot(lhs.value, rhs.value);
		}

	private:
		friend bool operator==(const Quaternion& lhs, const Quaternion& rhs) noexcept;
	};

	inline bool operator==(const Quaternion& lhs, const Quaternion& rhs) noexcept
	{
		return lhs.value == rhs.value;
	}

	inline bool operator!=(const Quaternion& lhs, const Quaternion& rhs) noexcept
	{
		return !(lhs == rhs);
	}

	inline Quaternion operator*(const Quaternion& lhs, const Quaternion& rhs) noexcept
	{
		return Quaternion{ lhs } *= rhs;
	}

	inline float operator|(const Quaternion& lhs, const Quaternion& rhs)
	{
		return Quaternion::Dot(lhs, rhs);
	}
}
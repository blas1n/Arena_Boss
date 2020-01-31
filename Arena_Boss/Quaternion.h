#pragma once

#include "Vector4.h"

namespace ArenaBoss::Math
{
	class Quaternion final
	{
	public:
		static const Quaternion IDENTITY;

	public:
		Quaternion() noexcept = default;

		Quaternion(const Quaternion&) noexcept = default;
		Quaternion(Quaternion&&) noexcept = default;

		explicit Quaternion(float x, float y, float z, float w) noexcept
			: value(x, y, z, w) {}

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

		inline void Set(float x, float y, float z, float w) noexcept
		{
			value.Set(x, y, z, w);
		}

		inline void Set(const float elems[4]) noexcept { value.Set(elems); }

		inline float GetX() const noexcept { return value.GetX(); }
		inline float GetY() const noexcept { return value.GetY(); }
		inline float GetZ() const noexcept { return value.GetZ(); }
		inline float GetW() const noexcept { return value.GetW(); }

		inline void SetX(float x) noexcept { value.SetX(x); }
		inline void SetY(float y) noexcept { value.SetY(y); }
		inline void SetZ(float z) noexcept { value.SetZ(z); }
		inline void SetW(float w) noexcept { value.SetW(w); }

		inline float operator[](size_t idx) const noexcept { return value[idx]; }

		inline float Length() const noexcept { return value.Length(); }
		inline float LengthSqrt() const noexcept { return value.LengthSqrt(); }

		inline Quaternion Normalized() const noexcept
		{
			return Quaternion{ value.Normalized() };
		}

		inline void Normalize() noexcept { value.Normalize(); }

		inline Quaternion operator-() const noexcept
		{
			return Quaternion{ DirectX::XMQuaternionConjugate(value) };
		}

		inline Quaternion& operator*=(const Quaternion& other) noexcept
		{
			value = DirectX::XMQuaternionMultiply(value, other.value);
			return *this;
		}

		inline static float Dot(const Quaternion& lhs, const Quaternion& rhs)
		{
			return Vector4::Dot(lhs.value, rhs.value);
		}

	private:
		friend bool operator==(const Quaternion& lhs, const Quaternion& rhs) noexcept;

		Vector4 value;
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
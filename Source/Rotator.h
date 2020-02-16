#pragma once

#include "Vector3.h"
#include <utility>

namespace ArenaBoss::Math
{
	class Rotator final
	{
	public:
		static const Rotator ZERO;

	public:
		union
		{
			Vector3 euler;
			struct
			{
				float roll;
				float pitch;
				float yaw;
			};
		};

	public:
		Rotator() noexcept = default;

		Rotator(const Rotator&) noexcept = default;

		Rotator(Rotator&&) noexcept = default;

		Rotator(const class Quaternion& quat);

		explicit Rotator(const Vector3& vec)
			: euler{ vec } {}

		explicit Rotator(Vector3&& vec) noexcept
			: euler{ std::move(vec) } {}

		explicit Rotator(float x, float y, float z) noexcept
			: euler(x, y, z) {}

		explicit Rotator(const float elems[3]) noexcept
			: euler(elems) {}

		~Rotator() = default;

		Rotator& operator=(const Rotator&) noexcept = default;
		Rotator& operator=(Rotator&&) noexcept = default;

		inline explicit operator Vector3() const noexcept { return euler; }
		operator Quaternion() const noexcept;

		inline Vector3 AsVector() const noexcept { return euler; }
		Quaternion AsQuaternion() const noexcept;

		inline void Set(float x, float y, float z) noexcept
		{
			euler.Set(x, y, z);
		}

		inline void Set(const float elems[3]) noexcept
		{
			euler.Set(elems);
		}

		inline float operator[](size_t index) const noexcept { return euler[index]; }

		inline Rotator operator-() const noexcept { return Rotator{ -euler }; }

		inline Rotator& operator+=(const Rotator& other) noexcept
		{
			euler += other.euler;
			return *this;
		}

		inline Rotator& operator-=(const Rotator& other) noexcept
		{
			euler -= other.euler;
			return *this;
		}

		inline Rotator& operator*=(const Rotator& other) noexcept
		{
			euler *= other.euler;
			return *this;
		}

		inline Rotator& operator*=(float scale) noexcept
		{
			euler *= scale;
			return *this;
		}

		inline Rotator& operator/=(const Rotator& other) noexcept
		{
			euler /= other.euler;
			return *this;
		}

		inline Rotator& operator/=(float scale) noexcept
		{
			euler /= scale;
			return *this;
		}

	private:
		friend bool operator==(const Rotator& lhs, const Rotator& rhs) noexcept;
	};

	inline bool operator==(const Rotator& lhs, const Rotator& rhs) noexcept
	{
		return lhs.euler == rhs.euler;
	}

	inline bool operator!=(const Rotator& lhs, const Rotator& rhs) noexcept
	{
		return !(lhs == rhs);
	}

	inline Rotator operator+(const Rotator& lhs, const Rotator& rhs) noexcept
	{
		return Rotator{ lhs } += rhs;
	}

	inline Rotator operator-(const Rotator& lhs, const Rotator& rhs) noexcept
	{
		return Rotator{ lhs } -= rhs;
	}

	inline Rotator operator*(const Rotator& lhs, const Rotator& rhs) noexcept
	{
		return Rotator{ lhs } *= rhs;
	}

	inline Rotator operator*(const Rotator& rot, float scale) noexcept
	{
		return Rotator{ rot } *= scale;
	}

	inline Rotator operator*(float scale, const Rotator& rot) noexcept
	{
		return Rotator{ rot } *= scale;
	}

	inline Rotator operator/(const Rotator& lhs, const Rotator& rhs) noexcept
	{
		return Rotator{ lhs } /= rhs;
	}

	inline Rotator operator/(const Rotator& rot, float scale) noexcept
	{
		return Rotator{ rot } /= scale;
	}

	inline Rotator operator/(float scale, const Rotator& rot) noexcept
	{
		return Rotator{ rot } /= scale;
	}
}
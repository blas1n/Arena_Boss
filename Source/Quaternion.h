#pragma once

#include <glm/gtc/quaternion.hpp>
#include <glm/vec3.hpp>
#include <glm/vec4.hpp>

namespace ArenaBoss::Math
{
	template <class T, class P>
	class TVector3;

	template <class T, class P>
	class TVector4;

	using Vector3 = TVector3<float, glm::vec3>;
	using Vector4 = TVector4<float, glm::vec4>;

	class Quaternion final
	{
	public:
		static const Quaternion IDENTITY;
		
	public:
		union
		{
			glm::quat value;

			struct
			{
				float x;
				float y;
				float z;
				float w;
			};
		};

	public:
		constexpr Quaternion() noexcept : value() {}

		constexpr Quaternion(const Quaternion&) noexcept = default;
		constexpr Quaternion(Quaternion&&) noexcept = default;

		explicit constexpr Quaternion(float inX, float inY, float inZ, float inW) noexcept
			: value(inW, inX, inY, inZ) {}

		explicit constexpr Quaternion(const float* elems) noexcept
			: value(elems[3], elems[0], elems[1], elems[2]) {}

		constexpr Quaternion(const glm::quat& quat)
			: value(quat) {}

		constexpr Quaternion(glm::quat&& quat)
			: value(std::move(quat)) {}

		explicit Quaternion(const Vector4& v) noexcept;

		explicit Quaternion(const Vector3& axis, float angle) noexcept;

		~Quaternion() = default;

		constexpr Quaternion& operator=(const Quaternion&) noexcept = default;
		constexpr Quaternion& operator=(Quaternion&&) noexcept = default;

		explicit operator Vector4() const noexcept;
		Vector4 AsVector() const noexcept;

		void Set(float inX, float inY, float inZ, float inW) noexcept;
		
		inline void Set(const float* elems) noexcept
		{
			Set(elems[0], elems[1], elems[2], elems[3]);
		}

		inline float& operator[](glm::length_t idx) noexcept { return value[idx]; }
		inline float operator[](glm::length_t idx) const noexcept { return value[idx]; }

		inline float Length() const noexcept { return glm::length(value); }
		inline float LengthSqrt() const noexcept { return Dot(*this, *this); }

		inline Quaternion Normalized() const noexcept { return Quaternion{ glm::normalize(value) }; }
		inline void Normalize() noexcept { *this = Normalized(); }

		inline Quaternion operator-() const noexcept
		{
			return Quaternion{ glm::conjugate(value) };
		}

		inline Quaternion& operator*=(const Quaternion& other) noexcept
		{
			value *= other.value;
			return *this;
		}

		inline static float Dot(const Quaternion& lhs, const Quaternion& rhs)
		{
			return glm::dot(lhs.value, rhs.value);
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
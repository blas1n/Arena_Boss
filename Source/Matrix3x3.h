#pragma once

#include <glm/mat3x3.hpp>

namespace ArenaBoss::Math
{
	class Matrix3x3 final
	{
	public:
		constexpr static Matrix3x3 ONE();
		constexpr static Matrix3x3 ZERO();
		constexpr static Matrix3x3 IDENTITY();

	public:
		union
		{
			glm::mat3 value;

			struct
			{
				float m00, m01, m02;
				float m10, m11, m12;
				float m20, m21, m22;
			};
		};

	public:
		constexpr Matrix3x3() noexcept : value() {}

		constexpr Matrix3x3(const Matrix3x3& other) noexcept
			: value(other.value) {}

		constexpr Matrix3x3(Matrix3x3&& other) noexcept
			: value(std::move(other.value)) {}

		explicit constexpr Matrix3x3(float scalar) noexcept
			: value(scalar) {}

		explicit constexpr Matrix3x3(
			float inM00, float inM01, float inM02,
			float inM10, float inM11, float inM12,
			float inM20, float inM21, float inM22) noexcept
			: value(
				inM00, inM01, inM02,
				inM10, inM11, inM12,
				inM20, inM21, inM22) {}

		explicit constexpr Matrix3x3(const float* elems) noexcept
			: value(
				elems[0], elems[1], elems[2],
				elems[3], elems[4], elems[5],
				elems[6], elems[7], elems[8]) {}

		explicit constexpr Matrix3x3(const float** elems) noexcept
			: value(
				elems[0][0], elems[0][1], elems[0][2],
				elems[1][0], elems[1][1], elems[1][2],
				elems[2][0], elems[2][1], elems[2][2]) {}

		constexpr Matrix3x3(const glm::mat3& mat) noexcept
			: value(mat) {}

		constexpr Matrix3x3(glm::mat3&& mat) noexcept
			: value(std::move(mat)) {}

		constexpr Matrix3x3& operator=(const Matrix3x3& other) noexcept
		{
			value = other.value;
			return *this;
		}

		constexpr Matrix3x3& operator=(Matrix3x3&& other) noexcept
		{
			value = std::move(other.value);
			return *this;
		}

		constexpr Matrix3x3& operator=(const glm::mat3& vec) noexcept
		{
			value = vec;
			return *this;
		}

		constexpr Matrix3x3& operator=(glm::mat3&& vec) noexcept
		{
			value = std::move(vec);
			return *this;
		}
	    
		constexpr operator glm::mat3&() noexcept { return value; }
		constexpr operator const glm::mat3&() const noexcept { return value; }

		constexpr operator float*() noexcept { return &m00; }
		constexpr operator const float*() const noexcept { return &m00; }

		void Set(float inM00, float inM01, float inM02,
			float inM10, float inM11, float inM12,
			float inM20, float inM21, float inM22) noexcept;

		inline void Set(const float* elems) noexcept
		{
			Set(elems[0], elems[1], elems[2],
				elems[3], elems[4], elems[5],
				elems[6], elems[7], elems[8]);
		}

		inline void Set(const float** elems) noexcept
		{
			Set(elems[0][0], elems[0][1], elems[0][2],
				elems[1][0], elems[1][1], elems[1][2],
				elems[2][0], elems[2][1], elems[2][2]);
		}

		inline Matrix3x3 Transpose() const noexcept
		{
			return glm::transpose(value);
		}

		inline void Transposed() noexcept
		{
			*this = Transpose();
		}

		inline Matrix3x3 Invert() const noexcept
		{
			return glm::inverse(value);
		}

		inline void Inverted() noexcept
		{
			*this = Invert();
		}

		inline float& operator()(glm::length_t row, glm::length_t column) noexcept
		{
			return value[row][column];
		}

		inline float operator()(glm::length_t row, glm::length_t column) const noexcept
		{
			return value[row][column];
		}

		inline Matrix3x3& operator+=(const Matrix3x3& other) noexcept
		{
			value += other.value;
			return *this;
		}

		inline Matrix3x3& operator-=(const Matrix3x3& other) noexcept
		{
			value -= other.value;
			return *this;
		}

		inline Matrix3x3& operator*=(const Matrix3x3& other) noexcept
		{
			value *= other.value;
			return *this;
		}

		inline Matrix3x3& operator*=(float scaler) noexcept
		{
			value *= scaler;
			return *this;
		}

		inline Matrix3x3& operator/=(const Matrix3x3& other) noexcept
		{
			value /= other.value;
			return *this;
		}

		inline Matrix3x3& operator/=(float scaler) noexcept
		{
			value /= scaler;
			return *this;
		}

	private:
		friend bool operator==(const Matrix3x3& lhs, const Matrix3x3& rhs) noexcept;
	};

	inline bool operator==(const Matrix3x3& lhs, const Matrix3x3& rhs) noexcept
	{
		return lhs.value == rhs.value;
	}

	inline bool operator!=(const Matrix3x3& lhs, const Matrix3x3& rhs) noexcept
	{
		return !(lhs == rhs);
	}

	inline Matrix3x3 operator+(const Matrix3x3& lhs, const Matrix3x3& rhs) { return Matrix3x3{ lhs } += rhs; }
	inline Matrix3x3 operator-(const Matrix3x3& lhs, const Matrix3x3& rhs) { return Matrix3x3{ lhs } -= rhs; }

	inline Matrix3x3 operator*(const Matrix3x3& lhs, const Matrix3x3& rhs) { return Matrix3x3{ lhs } *= rhs; }

	inline Matrix3x3 operator*(const Matrix3x3& lhs, float rhs) { return Matrix3x3{ lhs } *= rhs; }
	inline Matrix3x3 operator*(float lhs, const Matrix3x3& rhs) { return Matrix3x3{ rhs } *= lhs; }

	inline Matrix3x3 operator/(const Matrix3x3& lhs, const Matrix3x3& rhs) { return Matrix3x3{ lhs } /= rhs; }
	inline Matrix3x3 operator/(const Matrix3x3& lhs, float rhs) { return Matrix3x3{ lhs } /= rhs; }

	inline Matrix3x3 operator+(const Matrix3x3& vec) noexcept { return vec; }
	inline Matrix3x3 operator-(const Matrix3x3& vec) noexcept { return vec * -1.0f; }
}
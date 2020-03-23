#pragma once

#include <glm/mat4x4.hpp>
#include "Vector3.h"

namespace ArenaBoss::Math
{
	class Matrix4x4 final
	{
	public:
		constexpr static Matrix4x4 ONE();
		constexpr static Matrix4x4 ZERO();
		constexpr static Matrix4x4 IDENTITY();

	public:
		union
		{
			glm::mat4 value;

			struct
			{
				float m00, m01, m02, m03;
				float m10, m11, m12, m13;
				float m20, m21, m22, m23;
				float m30, m31, m32, m33;
			};
		};

	public:
		constexpr Matrix4x4() noexcept : value() {}

		constexpr Matrix4x4(const Matrix4x4& other) noexcept
			: value(other.value) {}

		constexpr Matrix4x4(Matrix4x4&& other) noexcept
			: value(std::move(other.value)) {}

		explicit constexpr Matrix4x4(float scalar) noexcept
			: value(scalar) {}

		explicit constexpr Matrix4x4(
			float inM00, float inM01, float inM02, float inM03,
			float inM10, float inM11, float inM12, float inM13,
			float inM20, float inM21, float inM22, float inM23,
			float inM30, float inM31, float inM32, float inM33) noexcept
			: value(
				inM00, inM01, inM02, inM03,
				inM10, inM11, inM12, inM13,
				inM20, inM21, inM22, inM23,
				inM30, inM31, inM32, inM33) {}

		explicit constexpr Matrix4x4(const float* elems) noexcept
			: value(
				elems[ 0], elems[ 1], elems[ 2], elems[ 3],
				elems[ 4], elems[ 5], elems[ 6], elems[ 7],
				elems[ 8], elems[ 9], elems[10], elems[11],
				elems[12], elems[13], elems[14], elems[15]) {}

		explicit constexpr Matrix4x4(const float** elems) noexcept
			: value(
				elems[0][0], elems[0][1], elems[0][2], elems[0][3],
				elems[1][0], elems[1][1], elems[1][2], elems[1][3],
				elems[2][0], elems[2][1], elems[2][2], elems[2][3],
				elems[3][0], elems[3][1], elems[3][2], elems[3][3]) {}

		explicit Matrix4x4(const class Matrix3x3& mat) noexcept;

		constexpr Matrix4x4(const glm::mat4& mat) noexcept
			: value(mat) {}

		constexpr Matrix4x4(glm::mat4&& mat) noexcept
			: value(std::move(mat)) {}

		constexpr Matrix4x4& operator=(const Matrix4x4& other) noexcept
		{
			value = other.value;
			return *this;
		}

		constexpr Matrix4x4& operator=(Matrix4x4&& other) noexcept
		{
			value = std::move(other.value);
			return *this;
		}

		Matrix4x4& operator=(const class Matrix3x3& other) noexcept;

		constexpr Matrix4x4& operator=(const glm::mat4& vec) noexcept
		{
			value = vec;
			return *this;
		}

		constexpr Matrix4x4& operator=(glm::mat4&& vec) noexcept
		{
			value = std::move(vec);
			return *this;
		}

		constexpr operator glm::mat4&() noexcept { return value; }
		constexpr operator const glm::mat4&() const noexcept { return value; }

		constexpr operator float*() noexcept { return &m00; }
		constexpr operator const float*() const noexcept { return &m00; }

		void Set(float inM00, float inM01, float inM02, float inM03,
			float inM10, float inM11, float inM12, float inM13,
			float inM20, float inM21, float inM22, float inM23,
			float inM30, float inM31, float inM32, float inM33) noexcept;

		inline void Set(float* elems) noexcept
		{
			Set(elems[ 0], elems[ 1], elems[ 2], elems[ 3],
				elems[ 4], elems[ 5], elems[ 6], elems[ 7],
				elems[ 8], elems[ 9], elems[10], elems[11],
				elems[12], elems[13], elems[14], elems[15]);
		}

		inline void Set(float** elems) noexcept
		{
			Set(elems[0][0], elems[0][1], elems[0][2], elems[0][3],
				elems[1][0], elems[1][1], elems[1][2], elems[1][3],
				elems[2][0], elems[2][1], elems[2][2], elems[2][3],
				elems[3][0], elems[3][1], elems[3][2], elems[3][3]);
		}

		inline Matrix4x4 Transpose() const noexcept
		{
			return glm::transpose(value);
		}

		inline void Transposed() noexcept
		{
			*this = Transpose();
		}

		inline Matrix4x4 Invert() const noexcept
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

		inline Matrix4x4& operator+=(const Matrix4x4& other) noexcept
		{
			value += other.value;
			return *this;
		}

		inline Matrix4x4& operator-=(const Matrix4x4& other) noexcept
		{
			value -= other.value;
			return *this;
		}

		inline Matrix4x4& operator*=(const Matrix4x4& other) noexcept
		{
			value *= other.value;
			return *this;
		}

		inline Matrix4x4& operator*=(float scaler) noexcept
		{
			value *= scaler;
			return *this;
		}

		inline Matrix4x4& operator/=(const Matrix4x4& other) noexcept
		{
			value /= other.value;
			return *this;
		}

		inline Matrix4x4& operator/=(float scaler) noexcept
		{
			value /= scaler;
			return *this;
		}

		inline Vector3 GetXAxis() const
		{
			return Vector3{ m00, m01, m02 };
		}

		inline Vector3 GetYAxis() const
		{
			return Vector3{ m10, m11, m12 };
		}

		inline Vector3 GetZAxis() const
		{
			return Vector3{ m20, m21, m22 };
		}

		inline Vector3 GetTranslation() const
		{
			return Vector3{ m30, m31, m32 };
		}

		Vector3 GetScale() const;

		static Matrix4x4 CreateFromPosition(const Vector3& position);
		static Matrix4x4 CreateFromPosition(float x, float y, float z);
		static Matrix4x4 CreateFromPosition(float position);

		static Matrix4x4 CreateFromRotationX(float theta);
		static Matrix4x4 CreateFromRotationY(float theta);
		static Matrix4x4 CreateFromRotationZ(float theta);

		static Matrix4x4 CreateFromRotation(const class Rotator& rotator);
		static Matrix4x4 CreateFromRotation(const class Quaternion& quat);

		static Matrix4x4 CreateFromScale(const Vector3& scale);
		static Matrix4x4 CreateFromScale(float x, float y, float z);
		static Matrix4x4 CreateFromScale(float scale);

		static Matrix4x4 CreateLookAt(const Vector3& eye, const Vector3& target, const Vector3& up);
		static Matrix4x4 CreateOrtho(float width, float height, float near, float far);
		static Matrix4x4 CreatePerspectiveFOV(float fovY, float width, float height, float near, float far);
		static Matrix4x4 CreateSimpleViewProjection(float width, float height);

	private:
		friend bool operator==(const Matrix4x4& lhs, const Matrix4x4& rhs) noexcept;
	};

	inline bool operator==(const Matrix4x4& lhs, const Matrix4x4& rhs) noexcept
	{
		return lhs.value == rhs.value;
	}

	inline bool operator!=(const Matrix4x4& lhs, const Matrix4x4& rhs) noexcept
	{
		return !(lhs == rhs);
	}

	inline Matrix4x4 operator+(const Matrix4x4& lhs, const Matrix4x4& rhs) { return Matrix4x4{ lhs } += rhs; }
	inline Matrix4x4 operator-(const Matrix4x4& lhs, const Matrix4x4& rhs) { return Matrix4x4{ lhs } -= rhs; }

	inline Matrix4x4 operator*(const Matrix4x4& lhs, const Matrix4x4& rhs) { return Matrix4x4{ lhs } *= rhs; }

	inline Matrix4x4 operator*(const Matrix4x4& lhs, float rhs) { return Matrix4x4{ lhs } *= rhs; }
	inline Matrix4x4 operator*(float lhs, const Matrix4x4& rhs) { return Matrix4x4{ rhs } *= lhs; }

	inline Matrix4x4 operator/(const Matrix4x4& lhs, const Matrix4x4& rhs) { return Matrix4x4{ lhs } /= rhs; }
	inline Matrix4x4 operator/(const Matrix4x4& lhs, float rhs) { return Matrix4x4{ lhs } /= rhs; }

	inline Matrix4x4 operator+(const Matrix4x4& vec) noexcept { return vec; }
	inline Matrix4x4 operator-(const Matrix4x4& vec) noexcept { return vec * -1.0f; }
}
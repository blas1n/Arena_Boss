#pragma once

#include <DirectXMath.h>
#include <optional>
#include <utility>

namespace ArenaBoss::Math
{
	class Matrix3x3 final
	{
	public:
		static const Matrix3x3 ONE;
		static const Matrix3x3 ZERO;
		static const Matrix3x3 IDENTITY;

	public:
		Matrix3x3() noexcept = default;

		Matrix3x3(const Matrix3x3&) noexcept = default;
		Matrix3x3(Matrix3x3&&) noexcept = default;

		explicit Matrix3x3(const float* elems) noexcept
			: value(
				elems[0], elems[1], elems[2], 0.0f,
				elems[3], elems[4], elems[5], 0.0f,
				elems[6], elems[7], elems[8], 0.0f,
				0.0f, 0.0f, 0.0f, 0.0f) {}

		explicit Matrix3x3(float r0c0, float r0c1, float r0c2,
			float r1c0, float r1c1, float r1c2,
			float r2c0, float r2c1, float r2c2) noexcept
			: value(
				r0c0, r0c1, r0c2, 0.0f,
				r1c0, r1c1, r1c2, 0.0f,
				r2c0, r2c1, r2c2, 0.0f,
				0.0f, 0.0f, 0.0f, 0.0f) {}

		Matrix3x3(DirectX::FXMMATRIX mat) noexcept : value(mat) {}

		~Matrix3x3() = default;

		Matrix3x3& operator=(const Matrix3x3&) noexcept = default;
		Matrix3x3& operator=(Matrix3x3&&) noexcept = default;

		inline Matrix3x3& operator=(DirectX::FXMMATRIX mat) noexcept
		{
			value = mat;
			return *this;
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

		inline Matrix3x3& operator*=(float scaler) noexcept
		{
			value *= scaler;
			return *this;
		}

		inline Matrix3x3& operator/=(float scaler) noexcept
		{
			value /= scaler;
			return *this;
		}

		inline Matrix3x3& operator*=(const Matrix3x3& other) noexcept
		{
			value *= other.value;
			return *this;
		}

		inline float operator()(size_t row, size_t column) const noexcept
		{
			return DirectX::XMVectorGetByIndex(value.r[row], column);
		}

		inline Matrix3x3 Transpose() const noexcept
		{
			return DirectX::XMMatrixTranspose(value);
		}

		inline void Transposed() noexcept
		{
			value = DirectX::XMMatrixTranspose(value);
		}

		inline std::optional<Matrix3x3> Invert() const noexcept
		{
			const auto invertedValue = DirectX::XMMatrixInverse(nullptr, value);

			if (!DirectX::XMMatrixIsInfinite(invertedValue))
				return invertedValue;
			
			return {};
		}

		inline bool Inverted() noexcept
		{
			const auto invertedValue = Invert();

			if (invertedValue)
				*this = *invertedValue;;
		}

	private:
		friend bool operator==(const Matrix3x3& lhs, const Matrix3x3& rhs) noexcept;

		DirectX::XMMATRIX value;
	};

	bool operator==(const Matrix3x3& lhs, const Matrix3x3& rhs) noexcept
	{
		for (int i = 0; i < 4; ++i)
		{
			if (DirectX::XMVector3NotEqual(lhs.value.r[i], rhs.value.r[i]))
				return false;
		}
		return true;
	}

	inline bool operator!=(const Matrix3x3& lhs, const Matrix3x3& rhs) noexcept
	{
		return !(lhs == rhs);
	}

	inline Matrix3x3 operator+(const Matrix3x3& lhs, const Matrix3x3& rhs) noexcept
	{
		return Matrix3x3{ lhs } += rhs;
	}

	inline Matrix3x3 operator-(const Matrix3x3& lhs, const Matrix3x3& rhs) noexcept
	{
		return Matrix3x3{ lhs } -= rhs;
	}

	inline Matrix3x3 operator*(const Matrix3x3& mat, float scaler) noexcept
	{
		return Matrix3x3{ mat } *= scaler;
	}

	inline Matrix3x3 operator*(const float scaler, const Matrix3x3& mat) noexcept
	{
		return Matrix3x3{ mat } *= scaler;
	}

	inline Matrix3x3 operator/(const Matrix3x3& mat, float scaler) noexcept
	{
		return Matrix3x3{ mat } /= scaler;
	}

	inline Matrix3x3 operator*(const Matrix3x3& lhs, const Matrix3x3& rhs) noexcept
	{
		return Matrix3x3{ lhs } *= rhs;
	}
}
#pragma once

#include <DirectXMath.h>
#include <optional>
#include <utility>

namespace ArenaBoss::Math
{
	class Matrix4x4 final
	{
	public:
		static const Matrix4x4 ONE;
		static const Matrix4x4 ZERO;
		static const Matrix4x4 IDENTITY;

	public:
		Matrix4x4() noexcept = default;

		Matrix4x4(const Matrix4x4&) noexcept = default;
		Matrix4x4(Matrix4x4&&) noexcept = default;

		explicit Matrix4x4(const float* elems) noexcept
			: value(elems) {}

		explicit Matrix4x4(
			float r0c0, float r0c1, float r0c2, float r0c3,
			float r1c0, float r1c1, float r1c2, float r1c3,
			float r2c0, float r2c1, float r2c2, float r2c3,
			float r3c0, float r3c1, float r3c2, float r3c3) noexcept
			: value(
				r0c0, r0c1, r0c2, r0c3,
				r1c0, r1c1, r1c2, r1c3,
				r2c0, r2c1, r2c2, r2c3,
				r3c1, r3c1, r3c2, r3c3) {}

		Matrix4x4(DirectX::FXMMATRIX mat) noexcept : value(mat) {}

		~Matrix4x4() = default;

		Matrix4x4& operator=(const Matrix4x4&) noexcept = default;
		Matrix4x4& operator=(Matrix4x4&&) noexcept = default;

		inline Matrix4x4& operator=(DirectX::FXMMATRIX mat) noexcept
		{
			value = mat;
			return *this;
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

		inline Matrix4x4& operator*=(float scaler) noexcept
		{
			value *= scaler;
			return *this;
		}

		inline Matrix4x4& operator/=(float scaler) noexcept
		{
			value /= scaler;
			return *this;
		}

		inline Matrix4x4& operator*=(const Matrix4x4& other) noexcept
		{
			value *= other.value;
			return *this;
		}

		inline float operator()(size_t row, size_t column) const noexcept
		{
			return DirectX::XMVectorGetByIndex(value.r[row], column);
		}

		inline Matrix4x4 Transpose() const noexcept
		{
			return DirectX::XMMatrixTranspose(value);
		}

		inline void Transposed() noexcept
		{
			value = DirectX::XMMatrixTranspose(value);
		}

		inline std::optional<Matrix4x4> Invert() const noexcept
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
		friend bool operator==(const Matrix4x4& lhs, const Matrix4x4& rhs) noexcept;

		DirectX::XMMATRIX value;
	};

	bool operator==(const Matrix4x4& lhs, const Matrix4x4& rhs) noexcept
	{
		for (int i = 0; i < 4; ++i)
		{
			if (DirectX::XMVector4NotEqual(lhs.value.r[i], rhs.value.r[i]))
				return false;
		}
		return true;
	}

	inline bool operator!=(const Matrix4x4& lhs, const Matrix4x4& rhs) noexcept
	{
		return !(lhs == rhs);
	}

	inline Matrix4x4 operator+(const Matrix4x4& lhs, const Matrix4x4& rhs) noexcept
	{
		return Matrix4x4{ lhs } += rhs;
	}

	inline Matrix4x4 operator-(const Matrix4x4& lhs, const Matrix4x4& rhs) noexcept
	{
		return Matrix4x4{ lhs } -= rhs;
	}

	inline Matrix4x4 operator*(const Matrix4x4& mat, float scaler) noexcept
	{
		return Matrix4x4{ mat } *= scaler;
	}

	inline Matrix4x4 operator*(const float scaler, const Matrix4x4& mat) noexcept
	{
		return Matrix4x4{ mat } *= scaler;
	}

	inline Matrix4x4 operator/(const Matrix4x4& mat, float scaler) noexcept
	{
		return Matrix4x4{ mat } /= scaler;
	}

	inline Matrix4x4 operator*(const Matrix4x4& lhs, const Matrix4x4& rhs) noexcept
	{
		return Matrix4x4{ lhs } *= rhs;
	}
}
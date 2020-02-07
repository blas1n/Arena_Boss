#pragma once

#include <DirectXMath.h>
#include <optional>

namespace ArenaBoss::Math
{
	class Matrix3x3 final
	{
	public:
		static const Matrix3x3 ONE;
		static const Matrix3x3 ZERO;
		static const Matrix3x3 IDENTITY;

	public:
		union
		{
			DirectX::XMFLOAT3X3 value;
			struct
			{
				float m00, m01, m02;
				float m10, m11, m12;
				float m20, m21, m22;
			};
		};

	public:
		Matrix3x3() noexcept = default;
		Matrix3x3(const Matrix3x3&) noexcept = default;
		Matrix3x3(Matrix3x3&&) noexcept = default;

		explicit Matrix3x3(
			float inM00, float inM01, float inM02,
			float inM10, float inM11, float inM12,
			float inM20, float inM21, float inM22) noexcept
			: value(
				inM00, inM01, inM02,
				inM10, inM11, inM12,
				inM20, inM21, inM22) {}

		explicit Matrix3x3(const float* elems) noexcept
			: value(elems) {}

		Matrix3x3(DirectX::FXMMATRIX mat) noexcept
			: Matrix3x3()
		{
			DirectX::XMStoreFloat3x3(&value, mat);
		}

		Matrix3x3(const DirectX::XMFLOAT3X3& mat) noexcept
			: value(mat) {}

		Matrix3x3& operator=(const Matrix3x3&) noexcept = default;
		Matrix3x3& operator=(Matrix3x3&&) noexcept = default;

		inline Matrix3x3& operator=(DirectX::FXMMATRIX mat) noexcept
		{
			DirectX::XMStoreFloat3x3(&value, mat);
		}

		inline Matrix3x3& operator=(const DirectX::XMFLOAT3X3& mat) noexcept
		{
			value = mat;
		}
	    
		inline operator DirectX::XMMATRIX() const noexcept { return DirectX::XMLoadFloat3x3(&value); }

		void Set(float inM00, float inM01, float inM02,
			float inM10, float inM11, float inM12,
			float inM20, float inM21, float inM22) noexcept;

		void Set(const float* elems) noexcept;

		inline Matrix3x3 Transpose() const noexcept
		{
			return DirectX::XMMatrixTranspose(*this);
		}

		inline void Transposed() noexcept
		{
			*this = DirectX::XMMatrixTranspose(*this);
		}

		std::optional<Matrix3x3> Invert() const noexcept;
		bool Inverted() noexcept;

		inline float& operator()(size_t row, size_t column) noexcept
		{
			return value(row, column);
		}

		float operator()(size_t row, size_t column) const noexcept
		{
			return value(row, column);
		}

		inline Matrix3x3 operator+() const noexcept { return *this; }
		inline Matrix3x3 operator-() const noexcept { return *this * -1.0f; }

		Matrix3x3& operator+=(const Matrix3x3& other) noexcept;
		Matrix3x3& operator-=(const Matrix3x3& other) noexcept;
		Matrix3x3& operator*=(const Matrix3x3& other) noexcept;
		Matrix3x3& operator*=(float scaler) noexcept;
		Matrix3x3& operator/=(float scaler) noexcept;

	private:
		friend bool operator==(const Matrix3x3& lhs, const Matrix3x3& rhs) noexcept;
	};

	bool operator==(const Matrix3x3& lhs, const Matrix3x3& rhs) noexcept;

	inline bool operator!=(const Matrix3x3& lhs, const Matrix3x3& rhs) noexcept
	{
		return !(lhs == rhs);
	}

	inline Matrix3x3 operator+(const Matrix3x3& lhs, const Matrix3x3& rhs) { return Matrix3x3{ lhs } += rhs; }
	inline Matrix3x3 operator-(const Matrix3x3& lhs, const Matrix3x3& rhs) { return Matrix3x3{ lhs } -= rhs; }

	inline Matrix3x3 operator*(const Matrix3x3& lhs, const Matrix3x3& rhs) { return Matrix3x3{ lhs } *= rhs; }

	inline Matrix3x3 operator*(const Matrix3x3& lhs, float rhs) { return Matrix3x3{ lhs } *= rhs; }
	inline Matrix3x3 operator*(float lhs, const Matrix3x3& rhs) { return Matrix3x3{ rhs } *= lhs; }

	inline Matrix3x3 operator/(const Matrix3x3& lhs, float rhs) { return Matrix3x3{ lhs } /= rhs; }
}
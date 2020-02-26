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

		Matrix3x3& operator=(DirectX::FXMMATRIX mat) noexcept;
		Matrix3x3& operator=(const DirectX::XMFLOAT3X3& mat) noexcept;
	    
		inline operator DirectX::XMMATRIX() const noexcept { return DirectX::XMLoadFloat3x3(&value); }
		inline operator float*() noexcept { return value.m[0]; }
		inline operator const float*() const noexcept { return value.m[0]; }

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

		inline float operator()(size_t row, size_t column) const noexcept
		{
			return value(row, column);
		}

		inline Matrix3x3& operator+=(const Matrix3x3& other) noexcept
		{
			return Calc(other, &DirectX::XMMATRIX::operator+=);
		}

		inline Matrix3x3& operator-=(const Matrix3x3& other) noexcept
		{
			return Calc(other, &DirectX::XMMATRIX::operator-=);
		}

		inline Matrix3x3& operator*=(const Matrix3x3& other) noexcept
		{
			return Calc(other, &DirectX::XMMATRIX::operator*=);
		}

		inline Matrix3x3& operator*=(float scaler) noexcept
		{
			return Calc(scaler, &DirectX::XMMATRIX::operator*=);
		}

		inline Matrix3x3& operator/=(float scaler) noexcept
		{
			return Calc(scaler, &DirectX::XMMATRIX::operator/=);
		}

	private:
		friend bool operator==(const Matrix3x3& lhs, const Matrix3x3& rhs) noexcept;

		using MatrixOperator = DirectX::XMMATRIX&(XM_CALLCONV DirectX::XMMATRIX::*)(DirectX::XMMATRIX);
		using ScalerOperator = DirectX::XMMATRIX&(DirectX::XMMATRIX::*)(float);

		Matrix3x3& Calc(const Matrix3x3& other, MatrixOperator oper) noexcept;
		Matrix3x3& Calc(float scaler, ScalerOperator oper) noexcept;
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

	inline Matrix3x3 operator+(const Matrix3x3& vec) noexcept { return vec; }
	inline Matrix3x3 operator-(const Matrix3x3& vec) noexcept { return vec * -1.0f; }
}
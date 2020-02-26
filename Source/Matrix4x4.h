#pragma once

#include <DirectXMath.h>
#include <optional>

namespace ArenaBoss::Math
{
	class Matrix4x4 final
	{
	public:
		static const Matrix4x4 ONE;
		static const Matrix4x4 ZERO;
		static const Matrix4x4 IDENTITY;

	public:
		union
		{
			DirectX::XMFLOAT4X4 value;
			struct
			{
				float m00, m01, m02, m03;
				float m10, m11, m12, m13;
				float m20, m21, m22, m23;
				float m30, m31, m32, m33;
			};
		};

	public:
		Matrix4x4() noexcept = default;
		Matrix4x4(const Matrix4x4&) noexcept = default;
		Matrix4x4(Matrix4x4&&) noexcept = default;

		explicit Matrix4x4(
			float inM00, float inM01, float inM02, float inM03,
			float inM10, float inM11, float inM12, float inM13,
			float inM20, float inM21, float inM22, float inM23,
			float inM30, float inM31, float inM32, float inM33) noexcept
			: value(
				inM00, inM01, inM02, inM03,
				inM10, inM11, inM12, inM13,
				inM20, inM21, inM22, inM23,
				inM30, inM31, inM32, inM33) {}

		explicit Matrix4x4(const float* elems) noexcept
			: value(elems) {}

		Matrix4x4(DirectX::FXMMATRIX mat) noexcept
			: Matrix4x4()
		{
			DirectX::XMStoreFloat4x4(&value, mat);
		}

		Matrix4x4(const DirectX::XMFLOAT4X4& mat) noexcept
			: value(mat) {}

		Matrix4x4& operator=(const Matrix4x4&) noexcept = default;
		Matrix4x4& operator=(Matrix4x4&&) noexcept = default;

		Matrix4x4& operator=(DirectX::FXMMATRIX mat) noexcept;
		Matrix4x4& operator=(const DirectX::XMFLOAT4X4& mat) noexcept;

		inline operator DirectX::XMMATRIX() const noexcept { return DirectX::XMLoadFloat4x4(&value); }
		inline operator float*() noexcept { return value.m[0]; }
		inline operator const float*() const noexcept { return value.m[0]; }

		void Set(float inM00, float inM01, float inM02, float inM03,
			float inM10, float inM11, float inM12, float inM13,
			float inM20, float inM21, float inM22, float inM23,
			float inM30, float inM31, float inM32, float inM33) noexcept;

		void Set(const float* elems) noexcept;

		inline Matrix4x4 Transpose() const noexcept
		{
			return DirectX::XMMatrixTranspose(*this);
		}

		inline void Transposed() noexcept
		{
			*this = DirectX::XMMatrixTranspose(*this);
		}

		std::optional<Matrix4x4> Invert() const noexcept;
		bool Inverted() noexcept;

		inline float& operator()(size_t row, size_t column) noexcept
		{
			return value(row, column);
		}

		inline float operator()(size_t row, size_t column) const noexcept
		{
			return value(row, column);
		}

		inline Matrix4x4& operator+=(const Matrix4x4& other) noexcept
		{
			return Calc(other, &DirectX::XMMATRIX::operator+=);
		}

		inline Matrix4x4& operator-=(const Matrix4x4& other) noexcept
		{
			return Calc(other, &DirectX::XMMATRIX::operator-=);
		}

		inline Matrix4x4& operator*=(const Matrix4x4& other) noexcept
		{
			return Calc(other, &DirectX::XMMATRIX::operator*=);
		}

		inline Matrix4x4& operator*=(float scaler) noexcept
		{
			return Calc(scaler, &DirectX::XMMATRIX::operator*=);
		}

		inline Matrix4x4& operator/=(float scaler) noexcept
		{
			return Calc(scaler, &DirectX::XMMATRIX::operator/=);
		}

	private:
		friend bool operator==(const Matrix4x4& lhs, const Matrix4x4& rhs) noexcept;

		using MatrixOperator = DirectX::XMMATRIX & (XM_CALLCONV DirectX::XMMATRIX::*)(DirectX::XMMATRIX);
		using ScalerOperator = DirectX::XMMATRIX & (DirectX::XMMATRIX::*)(float);

		Matrix4x4& Calc(const Matrix4x4& other, MatrixOperator oper) noexcept;
		Matrix4x4& Calc(float scaler, ScalerOperator oper) noexcept;
	};

	bool operator==(const Matrix4x4& lhs, const Matrix4x4& rhs) noexcept;

	inline bool operator!=(const Matrix4x4& lhs, const Matrix4x4& rhs) noexcept
	{
		return !(lhs == rhs);
	}

	inline Matrix4x4 operator+(const Matrix4x4& lhs, const Matrix4x4& rhs) { return Matrix4x4{ lhs } += rhs; }
	inline Matrix4x4 operator-(const Matrix4x4& lhs, const Matrix4x4& rhs) { return Matrix4x4{ lhs } -= rhs; }

	inline Matrix4x4 operator*(const Matrix4x4& lhs, const Matrix4x4& rhs) { return Matrix4x4{ lhs } *= rhs; }

	inline Matrix4x4 operator*(const Matrix4x4& lhs, float rhs) { return Matrix4x4{ lhs } *= rhs; }
	inline Matrix4x4 operator*(float lhs, const Matrix4x4& rhs) { return Matrix4x4{ rhs } *= lhs; }

	inline Matrix4x4 operator/(const Matrix4x4& lhs, float rhs) { return Matrix4x4{ lhs } /= rhs; }

	inline Matrix4x4 operator+(const Matrix4x4& vec) noexcept { return vec; }
	inline Matrix4x4 operator-(const Matrix4x4& vec) noexcept { return vec * -1.0f; }
}
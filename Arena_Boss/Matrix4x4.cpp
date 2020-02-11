#include "Matrix4x4.h"

namespace ArenaBoss::Math
{
	const Matrix4x4 Matrix4x4::ONE = Matrix4x4
	{
		1.0f, 1.0f, 1.0f, 1.0f,
		1.0f, 1.0f, 1.0f, 1.0f,
		1.0f, 1.0f, 1.0f, 1.0f,
		1.0f, 1.0f, 1.0f, 1.0f
	};

	const Matrix4x4 Matrix4x4::ZERO = Matrix4x4
	{
		0.0f, 0.0f, 0.0f, 0.0f,
		0.0f, 0.0f, 0.0f, 0.0f,
		0.0f, 0.0f, 0.0f, 0.0f,
		0.0f, 0.0f, 0.0f, 0.0f
	};

	const Matrix4x4 Matrix4x4::IDENTITY = Matrix4x4
	{
		1.0f, 0.0f, 0.0f, 0.0f,
		0.0f, 1.0f, 0.0f, 0.0f,
		0.0f, 0.0f, 1.0f, 0.0f,
		0.0f, 0.0f, 0.0f, 1.0f
	};

	Matrix4x4& Matrix4x4::operator=(DirectX::FXMMATRIX mat) noexcept
	{
		DirectX::XMStoreFloat4x4(&value, mat);
		return *this;
	}

	Matrix4x4& Matrix4x4::operator=(const DirectX::XMFLOAT4X4& mat) noexcept
	{
		value = mat;
		return *this;
	}

	void Matrix4x4::Set(float inM00, float inM01, float inM02, float inM03,
		float inM10, float inM11, float inM12, float inM13,
		float inM20, float inM21, float inM22, float inM23,
		float inM30, float inM31, float inM32, float inM33) noexcept
	{
		m00 = inM00;
		m01 = inM01;
		m02 = inM02;
		m03 = inM03;
		m10 = inM10;
		m11 = inM11;
		m12 = inM12;
		m13 = inM13;
		m20 = inM20;
		m21 = inM21;
		m22 = inM22;
		m23 = inM23;
		m30 = inM30;
		m31 = inM31;
		m32 = inM32;
		m33 = inM33;
	}

	void Matrix4x4::Set(const float* elems) noexcept
	{
		m00 = elems[0];
		m01 = elems[1];
		m02 = elems[2];
		m03 = elems[3];
		m11 = elems[4];
		m12 = elems[5];
		m12 = elems[6];
		m13 = elems[7];
		m20 = elems[8];
		m21 = elems[9];
		m22 = elems[10];
		m23 = elems[11];
		m30 = elems[12];
		m31 = elems[13];
		m32 = elems[14];
		m33 = elems[15];
	}

	std::optional<Matrix4x4> Matrix4x4::Invert() const noexcept
	{
		const auto invertedValue = DirectX::XMMatrixInverse(nullptr, *this);

		if (!DirectX::XMMatrixIsInfinite(invertedValue))
			return invertedValue;

		return {};
	}

	bool Matrix4x4::Inverted() noexcept
	{
		const auto invertedValue = Invert();

		if (invertedValue)
			*this = *invertedValue;

		return invertedValue.has_value();
	}

	Matrix4x4& Matrix4x4::Calc(const Matrix4x4& other, MatrixOperator oper) noexcept
	{
		DirectX::XMMATRIX mat = *this;
		(mat.*oper)(other);
		return *this = mat;
	}

	Matrix4x4& Matrix4x4::Calc(float scaler, ScalerOperator oper) noexcept
	{
		DirectX::XMMATRIX mat = *this;
		(mat.*oper)(scaler);
		return *this = mat;
	}

	bool operator==(const Matrix4x4& lhs, const Matrix4x4& rhs) noexcept
	{
		DirectX::XMMATRIX lhsMat = lhs;
		DirectX::XMMATRIX rhsMat = rhs;

		for (int i = 0; i < 4; ++i)
		{
			if (DirectX::XMVector4NotEqual(lhsMat.r[i], rhsMat.r[i]))
				return false;
		}
		return true;
	}
}
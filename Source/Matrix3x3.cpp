#include "Matrix3x3.h"

namespace ArenaBoss::Math
{
    const Matrix3x3 Matrix3x3::ONE = Matrix3x3
    {
        1.0f, 1.0f, 1.0f,
        1.0f, 1.0f, 1.0f,
        1.0f, 1.0f, 1.0f
    };

    const Matrix3x3 Matrix3x3::ZERO = Matrix3x3
    {
        0.0f, 0.0f, 0.0f,
        0.0f, 0.0f, 0.0f,
        0.0f, 0.0f, 0.0f
    };

    const Matrix3x3 Matrix3x3::IDENTITY = Matrix3x3
    {
        1.0f, 0.0f, 0.0f,
        0.0f, 1.0f, 0.0f,
        0.0f, 0.0f, 1.0f
    };

	Matrix3x3& Matrix3x3::operator=(DirectX::FXMMATRIX mat) noexcept
	{
		DirectX::XMStoreFloat3x3(&value, mat);
		return *this;
	}

	Matrix3x3& Matrix3x3::operator=(const DirectX::XMFLOAT3X3& mat) noexcept
	{
		value = mat;
		return *this;
	}

	void Matrix3x3::Set(float inM00, float inM01, float inM02,
		float inM10, float inM11, float inM12,
		float inM20, float inM21, float inM22) noexcept
	{
		m00 = inM00;
		m01 = inM01;
		m02 = inM02;
		m10 = inM10;
		m11 = inM11;
		m12 = inM12;
		m20 = inM20;
		m21 = inM21;
		m22 = inM22;
	}

	void Matrix3x3::Set(const float* elems) noexcept
	{
		m00 = elems[0];
		m01 = elems[1];
		m02 = elems[2];
		m10 = elems[3];
		m11 = elems[4];
		m12 = elems[5];
		m20 = elems[6];
		m21 = elems[7];
		m22 = elems[8];
	}

	std::optional<Matrix3x3> Matrix3x3::Invert() const noexcept
	{
		const auto invertedValue = DirectX::XMMatrixInverse(nullptr, *this);

		if (!DirectX::XMMatrixIsInfinite(invertedValue))
			return invertedValue;

		return {};
	}

	bool Matrix3x3::Inverted() noexcept
	{
		const auto invertedValue = Invert();

		if (invertedValue)
			*this = *invertedValue;

		return invertedValue.has_value();
	}

	Matrix3x3& Matrix3x3::Calc(const Matrix3x3& other, MatrixOperator oper) noexcept
	{
		DirectX::XMMATRIX mat = *this;
		(mat.*oper)(other);
		return *this = mat;
	}

	Matrix3x3& Matrix3x3::Calc(float scaler, ScalerOperator oper) noexcept
	{
		DirectX::XMMATRIX mat = *this;
		(mat.*oper)(scaler);
		return *this = mat;
	}

	bool operator==(const Matrix3x3& lhs, const Matrix3x3& rhs) noexcept
	{
		DirectX::XMMATRIX lhsMat = lhs;
		DirectX::XMMATRIX rhsMat = rhs;

		for (int i = 0; i < 4; ++i)
		{
			if (DirectX::XMVector3NotEqual(lhsMat.r[i], rhsMat.r[i]))
				return false;
		}
		return true;
	}
}
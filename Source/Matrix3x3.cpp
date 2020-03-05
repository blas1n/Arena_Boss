#include "Matrix3x3.h"

namespace ArenaBoss::Math
{
	constexpr Matrix3x3 Matrix3x3::ONE()
	{
		return Matrix3x3{ 1.0f };
	}

	constexpr Matrix3x3 Matrix3x3::ZERO()
	{
		return Matrix3x3{ 0.0f };
	}

	constexpr Matrix3x3 Matrix3x3::IDENTITY()
	{
		return Matrix3x3
		{
			1.0f, 0.0f, 0.0f,
			0.0f, 1.0f, 0.0f,
			0.0f, 0.0f, 1.0f,
		};
	}

	void Matrix3x3::Set(
		float inM00, float inM01, float inM02,
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
}
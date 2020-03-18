#include "Matrix3x3.h"
#include "MathFunctions.h"

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

	Matrix3x3 Matrix3x3::CreateFromPosition(const Vector2& position)
	{
		return CreateFromPosition(position.x, position.y);
	}

	Matrix3x3 Matrix3x3::CreateFromPosition(float x, float y)
	{
		const float temp[]
		{
			1.0f, 0.0f, 0.0f,
			0.0f, 1.0f, 0.0f,
			   x,    y, 1.0f,
		};

		return Matrix3x3{ temp };
	}

	Matrix3x3 Matrix3x3::CreateFromPosition(float position)
	{
		return CreateFromPosition(position, position);
	}

	Matrix3x3 Matrix3x3::CreateFromRotation(float theta)
	{
		const float temp[]
		{
	 		 Math::Cos(theta),  Math::Sin(theta), 0.0f,
			-Math::Sin(theta),  Math::Cos(theta), 0.0f,
			             0.0f,              0.0f, 1.0f,
		};

		return Matrix3x3{ temp };
	}

	Matrix3x3 Matrix3x3::CreateFromScale(const Vector2& scale)
	{
		return CreateFromScale(scale.x, scale.y);
	}

	Matrix3x3 Matrix3x3::CreateFromScale(float x, float y)
	{
		const float temp[]
		{
			   x, 0.0f, 0.0f,
			0.0f,    y, 0.0f,
			0.0f, 0.0f, 1.0f,
		};

		return Matrix3x3{ temp };
	}

	Matrix3x3 Matrix3x3::CreateFromScale(float scale)
	{
		return CreateFromScale(scale, scale);
	}
}
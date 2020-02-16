#include "MathFunctions.h"
#include "Quaternion.h"
#include "Rotator.h"
#include "Vector2.h"
#include "Vector3.h"
#include "Vector4.h"

namespace ArenaBoss::Math
{
	Rotator ToRadians(const Rotator& degrees) noexcept
	{
		return degrees * PI / 180.f;
	}

	Rotator ToDegrees(const Rotator& radians) noexcept
	{
		return radians * 180.0f / PI;
	}

	bool NearEqual(const Vector2& lhs, const Vector2& rhs, float epsilon/*= MACHINE_EPSILON*/) noexcept
	{
		return (lhs - rhs).LengthSqrt() <= Pow(epsilon);
	}

	bool NearEqual(const Vector3& lhs, const Vector3& rhs, float epsilon/*= MACHINE_EPSILON*/) noexcept
	{
		return (lhs - rhs).LengthSqrt() <= Pow(epsilon);
	}

	bool NearEqual(const Vector4& lhs, const Vector4& rhs, float epsilon/*= MACHINE_EPSILON*/) noexcept
	{
		return (lhs - rhs).LengthSqrt() <= Pow(epsilon);
	}

	bool NearEqual(const Rotator& lhs, const Rotator& rhs, float epsilon/*= MACHINE_EPSILON*/) noexcept
	{
		return (lhs - rhs).AsVector().LengthSqrt() <= Pow(epsilon);
	}

	bool NearEqual(const Quaternion& lhs, const Quaternion& rhs, float epsilon/*= MACHINE_EPSILON*/) noexcept
	{
		return NearEqual(lhs.AsVector(), rhs.AsVector(), epsilon);
	}

	Vector2 Lerp(const Vector2& a, const Vector2& b, float delta) noexcept
	{
		return a + delta * (b - a);
	}

	Vector3 Lerp(const Vector3& a, const Vector3& b, float delta) noexcept
	{
		return a + delta * (b - a);
	}

	Vector4 Lerp(const Vector4& a, const Vector4& b, float delta) noexcept
	{
		return a + delta * (b - a);
	}

	Rotator Lerp(const Rotator& a, const Rotator& b, float delta) noexcept
	{
		return a + delta * (b - a);
	}

	Quaternion Lerp(const Quaternion& a, const Quaternion& b, float delta) noexcept
	{
		const auto ret = Quaternion{ Lerp(a.AsVector(), b.AsVector(), delta) };
		return ret.Normalized();
	}

	Rotator Slerp(const Rotator& a, const Rotator& b, float delta) noexcept
	{
		return Slerp(a.AsQuaternion(), b.AsQuaternion(), delta);
	}

	Quaternion Slerp(const Quaternion& a, const Quaternion& b, float delta) noexcept
	{
		return Quaternion{ DirectX::XMQuaternionSlerp(a.AsVector(), b.AsVector(), delta) };
	}
}
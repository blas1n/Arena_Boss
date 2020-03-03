#include "MathFunctions.h"
#include "Quaternion.h"
#include "Rotator.h"

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

	bool NearEqual(const Rotator& lhs, const Rotator& rhs, float epsilon/*= MACHINE_EPSILON*/) noexcept
	{
		return (lhs - rhs).AsVector().LengthSqrt() <= Pow(epsilon);
	}

	bool NearEqual(const Quaternion& lhs, const Quaternion& rhs, float epsilon/*= MACHINE_EPSILON*/) noexcept
	{
		return NearEqual(lhs.AsVector(), rhs.AsVector(), epsilon);
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
		return Quaternion{ glm::mix(a.value, b.value, delta) };
	}
}
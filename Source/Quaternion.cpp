#include "Quaternion.h"
#include "Vector3.h"
#include "Vector4.h"

namespace ArenaBoss::Math
{
	const Quaternion Quaternion::IDENTITY = Quaternion{ 0.0f, 0.0f, 0.0f, 1.0f };

	Quaternion::Quaternion(const Vector4& v) noexcept
		: value(v.x, v.y, v.z, v.w) {}

	Quaternion::Quaternion(const Vector3& axis, float angle) noexcept
		: value(angle, axis.value) {}

	Quaternion::operator Vector4() const noexcept
	{
		return AsVector();
	}

	Vector4 Quaternion::AsVector() const noexcept
	{
		return Vector4{ x, y, z, w };
	}

	void Quaternion::Set(float inX, float inY, float inZ, float inW) noexcept
	{
		x = inX;
		y = inY;
		z = inZ;
		w = inW;
	}
}
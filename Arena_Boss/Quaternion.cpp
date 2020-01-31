#include "Quaternion.h"
#include "Vector3.h"

namespace ArenaBoss::Math
{
	const Quaternion Quaternion::IDENTITY = Quaternion{ DirectX::XMQuaternionIdentity() };

	Quaternion::Quaternion(const Vector3& axis, float angle) noexcept
		: value(DirectX::XMQuaternionRotationNormal(axis, angle)) {}
}
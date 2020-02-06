#include "Quaternion.h"
#include "Vector3.h"

namespace ArenaBoss::Math
{
	const Quaternion Quaternion::IDENTITY = Quaternion{ DirectX::XMQuaternionIdentity() };

	Quaternion::Quaternion(const Vector3& axis, float angle) noexcept
		: Quaternion()
	{
		const auto vec = DirectX::XMLoadFloat3(&axis.value);
		value = DirectX::XMQuaternionRotationNormal(vec, angle);
	}
}
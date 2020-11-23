#include "Rotator.h"
#include "MathFunctions.h"
#include "Quaternion.h"

namespace ArenaBoss::Math
{
	const Rotator Rotator::ZERO = Rotator{ Vector3::ZERO() };

	Rotator::Rotator(const Quaternion& quat)
		: euler()
	{
		const auto vec = glm::eulerAngles(quat.value);
		pitch = vec.x;
		yaw = vec.y;
		roll = vec.z;
	}

	Rotator::operator Quaternion() const noexcept
	{
		return AsQuaternion();
	}

	Quaternion Rotator::AsQuaternion() const noexcept
	{
		const auto rot = ToRadians(Rotator{ pitch, yaw, roll });
		return Quaternion{ glm::quat(rot.AsVector()) };
	}
}
#include "Rotator.h"
#include "MathFunctions.h"
#include "Quaternion.h"

namespace ArenaBoss::Math
{
	const Rotator Rotator::ZERO = Rotator{ Vector3::ZERO };

	Rotator::Rotator(const Quaternion& quat)
		: euler()
	{
        // Source : WikiPedia

        const auto sinrCosp = 2.0f * (quat.w * quat.x + quat.y * quat.z);
        const auto cosrCosp = 1.0f - 2.0f * (quat.x * quat.x + quat.y * quat.y);
        roll = Atan2(sinrCosp, cosrCosp);

        const auto sinp = 2.0f * (quat.w * quat.y + quat.z * quat.x);
        pitch = Abs(sinp) >= 1 ? CopySign(PI / 2.0f, sinp) : Asin(sinp);

        const auto sinyCosp = 2.0f * (quat.w * quat.z + quat.x * quat.y);
        const auto cosyCosp = 1.0f - 2.0f * (quat.y * quat.y + quat.z * quat.z);
        yaw = Atan2(sinyCosp, cosyCosp);
	}

	Rotator::operator Quaternion() const noexcept { return AsQuaternion(); }

	Quaternion Rotator::AsQuaternion() const noexcept
	{
		Rotator rot{ pitch, yaw, roll };
		rot = ToRadians(rot);
		const auto vec =
			DirectX::XMQuaternionRotationRollPitchYawFromVector(rot.AsVector());
		return Quaternion{ vec };
	}
}
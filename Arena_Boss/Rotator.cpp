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

        const auto sinrCosp = 2.0f * (quat.GetW() * quat.GetX() + quat.GetY() * quat.GetZ());
        const auto cosrCosp = 1.0f - 2.0f * (quat.GetX() * quat.GetX() + quat.GetY() * quat.GetY());
        SetRoll(Atan2(sinrCosp, cosrCosp));

        const auto sinp = 2.0f * (quat.GetW() * quat.GetY() + quat.GetZ() * quat.GetX());
        SetPitch(Abs(sinp) >= 1 ? CopySign(PI / 2.0f, sinp) : Asin(sinp));

        const auto sinyCosp = 2.0f * (quat.GetW() * quat.GetZ() + quat.GetX() * quat.GetY());
        const auto cosyCosp = 1.0f - 2.0f * (quat.GetY() * quat.GetY() + quat.GetZ() * quat.GetZ());
        SetYaw(Atan2(sinyCosp, cosyCosp));
	}

	Rotator::operator Quaternion() const noexcept { return AsQuaternion(); }

	Quaternion Rotator::AsQuaternion() const noexcept
	{
		Rotator rot{ GetPitch(), GetYaw(), GetRoll() };
		rot = ToRadians(rot);
		const auto vec = DirectX::XMQuaternionRotationRollPitchYawFromVector(rot.AsVector());
		return Quaternion{ vec };
	}
}
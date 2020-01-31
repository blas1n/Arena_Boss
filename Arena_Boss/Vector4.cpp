#include "Vector4.h"
#include "Vector2.h"
#include "Vector3.h"

namespace ArenaBoss::Math
{
    const Vector4 Vector4::ONE = Vector4{ 1.0f, 1.0f, 1.0f, 1.0f };
    const Vector4 Vector4::ZERO = Vector4{ 0.0f, 0.0f, 0.0f, 0.0f };

    Vector4::Vector4(const Vector2& xy, float z/* = 0.0f*/, float w/* = 0.0f*/) noexcept
        : Vector4(DirectX::XMVectorGetX(xy), DirectX::XMVectorGetY(xy), z, w) {}

    Vector4::Vector4(const Vector3& xyz, float w/* = 0.0f*/) noexcept
        : value(DirectX::XMVectorSetW(xyz, w)) {}

    Vector4::operator Vector2() const noexcept
    {
        return Vector2
        {
            DirectX::XMVectorGetX(value),
            DirectX::XMVectorGetY(value)
        };
    }

    Vector4::operator Vector3() const noexcept
    {
        return Vector3
        {
            DirectX::XMVectorGetX(value),
            DirectX::XMVectorGetY(value),
            DirectX::XMVectorGetZ(value)
        };
    }
}
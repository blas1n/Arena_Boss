#include "Vector3.h"
#include "Scalar.h"
#include "Vector2.h"

namespace Math
{
    const Vector3 Vector3::ONE = Vector3{ 1.0f, 1.0f, 1.0f };
    const Vector3 Vector3::ZERO = Vector3{ 0.0f, 0.0f, 0.0f };

    const Vector3 Vector3::UP = Vector3{ 0.0f, 1.0f, 0.0f };
    const Vector3 Vector3::DOWN = Vector3{ 0.0f, -1.0f, 0.0f };

    const Vector3 Vector3::RIGHT = Vector3{ 1.0f, 0.0f, 0.0f };
    const Vector3 Vector3::LEFT = Vector3{ -1.0f, 0.0f, 0.0f };

    const Vector3 Vector3::FORWARD = Vector3{ 0.0f, 0.0f, 1.0f };
    const Vector3 Vector3::BACKWARD = Vector3{ 0.0f, 0.0f, -1.0f };

    Vector3::Vector3(const Vector2& xy, float z/*= 0.0f*/)
        : Vector3(DirectX::XMVectorGetX(xy), DirectX::XMVectorGetY(xy), z) {}

    Vector3::Vector3(const Scalar& s) : value(s) {}

    Vector3::operator Vector2() const noexcept
    {
        return Vector2
        {
            DirectX::XMVectorGetX(value),
            DirectX::XMVectorGetY(value)
        };
    }

    Vector3& Vector3::operator*=(const Scalar& other)
    {
        value = DirectX::XMVectorMultiply(value, other);
        return *this;
    }

    Vector3& Vector3::operator/=(const Scalar& other)
    {
        value = DirectX::XMVectorDivide(value, other);
        return *this;
    }
}
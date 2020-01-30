#include "Vector2.h"

namespace ArenaBoss::Math
{
    const Vector2 Vector2::ONE = Vector2{ 1.0f, 1.0f };
    const Vector2 Vector2::ZERO = Vector2{ 0.0f, 0.0f };

    const Vector2 Vector2::UP = Vector2{ 0.0f, 1.0f };
    const Vector2 Vector2::DOWN = Vector2{ 0.0f, -1.0f };

    const Vector2 Vector2::LEFT = Vector2{ -1.0f, 0.0f };
    const Vector2 Vector2::RIGHT = Vector2{ 1.0f, 0.0f };

    Vector2::Vector2(const Scalar& s) noexcept : value(s) {}

    Vector2& Vector2::operator*=(const Scalar& other)
    {
        value = DirectX::XMVectorMultiply(value, other);
        return *this;
    }

    Vector2& Vector2::operator/=(const Scalar& other)
    {
        value = DirectX::XMVectorDivide(value, other);
        return *this;
    }
}
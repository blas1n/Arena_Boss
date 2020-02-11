#include "Vector2.h"
#include <stdexcept>
#include "MathFunctions.h"

namespace ArenaBoss::Math
{
    const Vector2 Vector2::ONE = Vector2{ 1.0f, 1.0f };
    const Vector2 Vector2::ZERO = Vector2{ 0.0f, 0.0f };

    const Vector2 Vector2::UP = Vector2{ 0.0f, 1.0f };
    const Vector2 Vector2::DOWN = Vector2{ 0.0f, -1.0f };

    const Vector2 Vector2::LEFT = Vector2{ -1.0f, 0.0f };
    const Vector2 Vector2::RIGHT = Vector2{ 1.0f, 0.0f };

    Vector2& Vector2::operator=(DirectX::FXMVECTOR vec) noexcept
    {
        DirectX::XMStoreFloat2(&value, vec);
        return *this;
    }

    Vector2& Vector2::operator=(const DirectX::XMFLOAT2& vec) noexcept
    {
        value = vec;
        return *this;
    }

    void Vector2::Set(float inX, float inY) noexcept
    {
        x = inX;
        y = inY;
    }

    void Vector2::Set(const float* elems) noexcept
    {
        x = elems[0];
        y = elems[1];
    }

    float Vector2::Length() const noexcept
    {
        return Sqrt(LengthSqrt());
    }

    float Vector2::LengthSqrt() const noexcept
    {
        const auto len = DirectX::XMVector2LengthSq(*this);
        return DirectX::XMVectorGetX(len);
    }

    float& Vector2::operator[](size_t idx)
    {
        switch (idx)
        {
        case 0: return x;
        case 1: return y;
        default: throw std::out_of_range{ "Index must be less than 2" };
        }
    }

    float Vector2::operator[](size_t idx) const
    {
        switch (idx)
        {
        case 0: return x;
        case 1: return y;
        default: throw std::out_of_range{ "Index must be less than 2" };
        }
    }

    Vector2& Vector2::Calc(const Vector2& other, Operator oper) noexcept
    {
        *this = oper(*this, other);
        return *this;
    }

    Vector2& Vector2::Calc(float scaler, Operator oper) noexcept
    {
        const auto other = DirectX::XMVectorReplicate(scaler);
        *this = oper(*this, other);
        return *this;
    }
}
#include "Vector3.h"
#include "MathFunctions.h"
#include "Vector2.h"

namespace ArenaBoss::Math
{
    const Vector3 Vector3::ONE = Vector3{ 1.0f, 1.0f, 1.0f };
    const Vector3 Vector3::ZERO = Vector3{ 0.0f, 0.0f, 0.0f };

    const Vector3 Vector3::UP = Vector3{ 0.0f, 1.0f, 0.0f };
    const Vector3 Vector3::DOWN = Vector3{ 0.0f, -1.0f, 0.0f };

    const Vector3 Vector3::LEFT = Vector3{ -1.0f, 0.0f, 0.0f };
    const Vector3 Vector3::RIGHT = Vector3{ 1.0f, 0.0f, 0.0f };

    const Vector3 Vector3::FORWARD = Vector3{ 0.0f, 0.0f, 1.0f };
    const Vector3 Vector3::BACKWARD = Vector3{ 0.0f, 0.0f, -1.0f };

    Vector3::Vector3(const Vector2& xy, float z = 0.0f) noexcept
        : value(xy.x, xy.y, z) {}

    Vector3& Vector3::operator=(DirectX::FXMVECTOR vec) noexcept
    {
        DirectX::XMStoreFloat3(&value, vec);
        return *this;
    }

    Vector3& Vector3::operator=(const DirectX::XMFLOAT3& vec) noexcept
    {
        value = vec;
        return *this;
    }

    Vector3::operator Vector2() const noexcept
    {
        return Vector2{ x, y };
    }

    void Vector3::Set(float inX, float inY, float inZ) noexcept
    {
        x = inX;
        y = inY;
        z = inZ;
    }

    void Vector3::Set(const float* elems) noexcept
    {
        x = elems[0];
        y = elems[1];
        z = elems[2];
    }

    float Vector3::Length() const noexcept
    {
        return Sqrt(LengthSqrt());
    }

    float Vector3::LengthSqrt() const noexcept
    {
        const auto len = DirectX::XMVector3LengthSq(*this);
        return DirectX::XMVectorGetX(len);
    }

    float Vector3::operator[](size_t idx) const noexcept
    {
        switch (idx)
        {
        case 0: return x;
        case 1: return y;
        case 2: return z;
        default: assert(false);
        }
    }

    Vector3& Vector3::Calc(const Vector3& other, Operator oper) noexcept
    {
        *this = oper(*this, other);
        return *this;
    }

    Vector3& Vector3::Calc(float scaler, Operator oper) noexcept
    {
        const auto other = DirectX::XMVectorReplicate(scaler);
        *this = oper(*this, other);
        return *this;
    }
}
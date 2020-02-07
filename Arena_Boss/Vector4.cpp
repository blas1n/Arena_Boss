#include "Vector4.h"
#include "MathFunctions.h"
#include "Vector2.h"
#include "Vector3.h"

namespace ArenaBoss::Math
{
    const Vector4 Vector4::ONE = Vector4{ 1.0f, 1.0f, 1.0f, 1.0f };
    const Vector4 Vector4::ZERO = Vector4{ 0.0f, 0.0f, 0.0f, 0.0f };

    Vector4::Vector4(const Vector2& xy, float z/*= 0.0f*/, float w/*= 0.0f*/) noexcept
        : value(xy.x, xy.y, z, w) {}

    Vector4::Vector4(const Vector3& xyz, float w/*= 0.0f*/) noexcept
        : value(xyz.x, xyz.y, xyz.z, w) {}

    Vector4& Vector4::operator=(DirectX::FXMVECTOR vec) noexcept
    {
        DirectX::XMStoreFloat4(&value, vec);
        return *this;
    }

    Vector4& Vector4::operator=(const DirectX::XMFLOAT4& vec) noexcept
    {
        value = vec;
        return *this;
    }

    Vector4::operator Vector2() const noexcept
    {
        return Vector2{ x, y };
    }

    Vector4::operator Vector3() const noexcept
    {
        return Vector3{ x, y, z };
    }

    void Vector4::Set(float inX, float inY, float inZ, float inW) noexcept
    {
        x = inX;
        y = inY;
        z = inZ;
        w = inW;
    }

    void Vector4::Set(const float* elems) noexcept
    {
        x = elems[0];
        y = elems[1];
        z = elems[2];
        w = elems[3];
    }

    float Vector4::Length() const noexcept
    {
        return Sqrt(LengthSqrt());
    }

    float Vector4::LengthSqrt() const noexcept
    {
        const auto len = DirectX::XMVector4LengthSq(*this);
        return DirectX::XMVectorGetX(len);
    }

    float& Vector4::operator[](size_t idx) noexcept
    {
        switch (idx)
        {
        case 0: return x;
        case 1: return y;
        case 2: return z;
        case 3: return w;
        default: assert(false);
        }
    }

    float Vector4::operator[](size_t idx) const noexcept
    {
        switch (idx)
        {
        case 0: return x;
        case 1: return y;
        case 2: return z;
        case 3: return w;
        default: assert(false);
        }
    }

    Vector4& Vector4::Calc(const Vector4& other, Operator oper) noexcept
    {
        *this = oper(*this, other);
        return *this;
    }

    Vector4& Vector4::Calc(float scaler, Operator oper) noexcept
    {
        const auto other = DirectX::XMVectorReplicate(scaler);
        *this = oper(*this, other);
        return *this;
    }
}
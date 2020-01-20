#pragma once

#include <DirectXMath.h>

namespace Math
{
    class Scalar;
    class Vector2;
    class Vector3;

    class Vector4 final
    {
    public:
        static const Vector4 ONE;
        static const Vector4 ZERO;

    public:
        Vector4() = default;
        Vector4(const Vector4&) = default;

        explicit Vector4(float x, float y, float z, float w)
            : value(DirectX::XMVectorSet(x, y, z, w)) {}

        explicit Vector4(const Vector2& xy, float z = 0.0f, float w = 0.0f);
        explicit Vector4(const Vector3& xyz, float w = 0.0f);
        explicit Vector4(const Scalar& s);
        
        explicit Vector4(DirectX::FXMVECTOR vec)
            : value(vec) {}

        Vector4& operator=(const Vector4&) = default;

        operator Vector2() const noexcept;
        operator Vector3() const noexcept;

        inline DirectX::XMVECTOR Get() const noexcept { return value; }
        inline operator DirectX::XMVECTOR() const noexcept { return value; }

        inline float GetX() const noexcept { return DirectX::XMVectorGetX(value); }
        inline float GetY() const noexcept { return DirectX::XMVectorGetY(value); }
        inline float GetZ() const noexcept { return DirectX::XMVectorGetZ(value); }
        inline float GetW() const noexcept { return DirectX::XMVectorGetW(value); }

        inline void SetX(float x) noexcept { value = DirectX::XMVectorSetX(value, x); }
        inline void SetY(float y) noexcept { value = DirectX::XMVectorSetY(value, y); }
        inline void SetZ(float z) noexcept { value = DirectX::XMVectorSetZ(value, z); }
        inline void SetW(float w) noexcept { value = DirectX::XMVectorSetW(value, w); }

        inline float Length() const noexcept
        {
            return DirectX::XMVectorGetX(DirectX::XMVector4Length(value));
        }

        inline float LengthSqrt() const noexcept
        {
            return DirectX::XMVectorGetX(DirectX::XMVector4LengthSq(value));
        }

        inline static Vector4 Normalized(const Vector4& vec) noexcept
        {
            return Vector4{ DirectX::XMVector4Normalize(vec) };
        }

        inline void Normalize() noexcept
        {
            value = DirectX::XMVector4Normalize(value);
        }

        inline float operator[](size_t idx) const noexcept
        {
            return DirectX::XMVectorGetByIndex(value, idx);
        }

        inline Vector4& operator+=(const Vector4& other)
        {
            value = DirectX::XMVectorAdd(value, other);
            return *this;
        }

        inline Vector4& operator-=(const Vector4& other)
        {
            value = DirectX::XMVectorSubtract(value, other);
            return *this;
        }

        inline Vector4& operator*=(const Vector4& other)
        {
            value = DirectX::XMVectorMultiply(value, other);
            return *this;
        }

        Vector4& operator*=(const Scalar& other);

        inline Vector4& operator/=(const Vector4& other)
        {
            value = DirectX::XMVectorDivide(value, other);
            return *this;
        }

        Vector4& operator/=(const Scalar& other);

        inline static float Dot(const Vector4& lhs, const Vector4& rhs)
        {
            return DirectX::XMVectorGetX(DirectX::XMVector4Dot(lhs, rhs));
        }

    private:
        DirectX::XMVECTOR value;
    };

    inline Vector4 operator-(const Vector4& s) { return Vector4{ DirectX::XMVectorNegate(s) }; }

    inline Vector4 operator+(const Vector4& lhs, const Vector4& rhs) { return Vector4{ lhs } += rhs; }
    inline Vector4 operator-(const Vector4& lhs, const Vector4& rhs) { return Vector4{ lhs } -= rhs; }

    inline Vector4 operator*(const Vector4& lhs, const Vector4& rhs) { return Vector4{ lhs } *= rhs; }
    inline Vector4 operator*(const Vector4& lhs, const Scalar& rhs) { return Vector4{ lhs } *= rhs; }
    
    inline Vector4 operator/(const Vector4& lhs, const Vector4& rhs) { return Vector4{ lhs } /= rhs; }
    inline Vector4 operator/(const Vector4& lhs, const Scalar& rhs) { return Vector4{ lhs } /= rhs; }

    inline float operator|(const Vector4& lhs, const Vector4& rhs) { return Vector4::Dot(lhs, rhs); }
}
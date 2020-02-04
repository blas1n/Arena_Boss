#pragma once

#include "Scalar.h"

namespace ArenaBoss::Math
{
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
        Vector4(Vector4&&) noexcept = default;

        explicit Vector4(float x, float y, float z, float w) noexcept
            : value(DirectX::XMVectorSet(x, y, z, w)) {}

        explicit Vector4(const float elems[4]) noexcept
            : value(DirectX::XMVectorSet(elems[0], elems[1], elems[2], elems[3])) {}

        explicit Vector4(const Vector2& xy, float z = 0.0f, float w = 0.0f) noexcept;
        explicit Vector4(const Vector3& xyz, float w = 0.0f) noexcept;
        explicit Vector4(const Scalar& s) noexcept : value(s) {}
        
        Vector4(DirectX::FXMVECTOR vec) noexcept : value(vec) {}

        Vector4& operator=(const Vector4&) = default;
        Vector4& operator=(Vector4&&) noexcept = default;

        operator Vector2() const noexcept;
        operator Vector3() const noexcept;

        inline DirectX::XMVECTOR Get() const noexcept { return value; }
        inline operator DirectX::XMVECTOR() const noexcept { return value; }

        inline void Set(float x, float y, float z, float w) noexcept
        {
            value = DirectX::XMVectorSet(x, y, z, w);
        }

        inline void Set(const float elems[4]) noexcept
        {
            value = DirectX::XMVectorSet(elems[0], elems[1], elems[2], elems[3]);
        }

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

        inline Vector4 Normalized() const noexcept
        {
            return DirectX::XMVector4Normalize(value);
        }

        inline void Normalize() noexcept
        {
            value = DirectX::XMVector4Normalize(value);
        }

        inline float operator[](size_t idx) const noexcept
        {
            return DirectX::XMVectorGetByIndex(value, idx);
        }

        inline Vector4 operator-() const noexcept
        {
            return DirectX::XMVectorNegate(value);
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

        inline Vector4& operator*=(const Scalar& other)
        {
            value = DirectX::XMVectorMultiply(value, other);
            return *this;
        }

        inline Vector4& operator/=(const Vector4& other)
        {
            value = DirectX::XMVectorDivide(value, other);
            return *this;
        }

        inline Vector4& operator/=(const Scalar& other)
        {
            value = DirectX::XMVectorDivide(value, other);
            return *this;
        }

        inline static float Dot(const Vector4& lhs, const Vector4& rhs)
        {
            return DirectX::XMVectorGetX(DirectX::XMVector4Dot(lhs, rhs));
        }

    private:
        friend bool operator==(const Vector4& lhs, const Vector4& rhs) noexcept;

        DirectX::XMVECTOR value;
    };

    inline bool operator==(const Vector4& lhs, const Vector4& rhs) noexcept
    {
        return DirectX::XMVector4Equal(lhs.value, rhs.value);
    }

    inline bool operator!=(const Vector4& lhs, const Vector4& rhs) noexcept
    {
        return !(lhs == rhs);
    }

    inline Vector4 operator+(const Vector4& lhs, const Vector4& rhs) { return Vector4{ lhs } += rhs; }
    inline Vector4 operator-(const Vector4& lhs, const Vector4& rhs) { return Vector4{ lhs } -= rhs; }

    inline Vector4 operator*(const Vector4& lhs, const Vector4& rhs) { return Vector4{ lhs } *= rhs; }
    inline Vector4 operator*(const Vector4& lhs, const Scalar& rhs) { return Vector4{ lhs } *= rhs; }
    inline Vector4 operator*(const Scalar& lhs, const Vector4& rhs) { return Vector4{ rhs } *= lhs; }
    
    inline Vector4 operator/(const Vector4& lhs, const Vector4& rhs) { return Vector4{ lhs } /= rhs; }
    inline Vector4 operator/(const Vector4& lhs, const Scalar& rhs) { return Vector4{ lhs } /= rhs; }
    inline Vector4 operator/(const Scalar& lhs, const Vector4& rhs) { return Vector4{ rhs } /= lhs; }

    inline float operator|(const Vector4& lhs, const Vector4& rhs) { return Vector4::Dot(lhs, rhs); }
}
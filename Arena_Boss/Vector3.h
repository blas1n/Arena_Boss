#pragma once

#include "Scalar.h"

namespace Math
{
    class Vector2;

    class Vector3 final
    {
    public:
        static const Vector3 ONE;
        static const Vector3 ZERO;

        static const Vector3 UP;
        static const Vector3 DOWN;

        static const Vector3 RIGHT;
        static const Vector3 LEFT;

        static const Vector3 FORWARD;
        static const Vector3 BACKWARD;

    public:
        Vector3() = default;
        Vector3(const Vector3&) = default;
        Vector3(Vector3&&) noexcept = default;

        explicit Vector3(float x, float y, float z)
            : value(DirectX::XMVectorSet(x, y, z, 0.0f)) {}

        explicit Vector3(const Vector2& xy, float z = 0.0f);
        explicit Vector3(const Scalar& s);

        explicit Vector3(DirectX::FXMVECTOR vec)
            : value(vec) {}

        Vector3& operator=(const Vector3&) = default;
        Vector3& operator=(Vector3&&) noexcept = default;

        operator Vector2() const noexcept;

        inline DirectX::XMVECTOR Get() const noexcept { return value; }
        inline operator DirectX::XMVECTOR() const noexcept { return value; }

        inline void Set(float x, float y, float z) noexcept
        {
            value = DirectX::XMVectorSet(x, y, z, 0.0f);
        }

        inline float GetX() const noexcept { return DirectX::XMVectorGetX(value); }
        inline float GetY() const noexcept { return DirectX::XMVectorGetY(value); }
        inline float GetZ() const noexcept { return DirectX::XMVectorGetZ(value); }

        inline void SetX(float x) noexcept { value = DirectX::XMVectorSetX(value, x); }
        inline void SetY(float y) noexcept { value = DirectX::XMVectorSetY(value, y); }
        inline void SetZ(float z) noexcept { value = DirectX::XMVectorSetZ(value, z); }

        inline float Length() const noexcept
        {
            return DirectX::XMVectorGetX(DirectX::XMVector3Length(value));
        }

        inline float LengthSqrt() const noexcept
        {
            return DirectX::XMVectorGetX(DirectX::XMVector3LengthSq(value));
        }

        inline static Vector3 Normalized(const Vector3& vec) noexcept
        {
            return Vector3{ DirectX::XMVector3Normalize(vec) };
        }

        inline void Normalize() noexcept
        {
            value = DirectX::XMVector3Normalize(value);
        }

        inline float operator[](size_t idx) const noexcept
        {
            return DirectX::XMVectorGetByIndex(value, idx);
        }

        inline Vector3& operator+=(const Vector3& other)
        {
            value = DirectX::XMVectorAdd(value, other);
            return *this;
        }

        inline Vector3& operator-=(const Vector3& other)
        {
            value = DirectX::XMVectorSubtract(value, other);
            return *this;
        }

        inline Vector3& operator*=(const Vector3& other)
        {
            value = DirectX::XMVectorMultiply(value, other);
            return *this;
        }

        Vector3& operator*=(const Scalar& other);

        inline Vector3& operator/=(const Vector3& other)
        {
            value = DirectX::XMVectorDivide(value, other);
            return *this;
        }

        Vector3& operator/=(const Scalar& other);

        inline Vector3& operator^=(const Vector3& other)
        {
            value = DirectX::XMVector3Cross(value, other);
            return *this;
        }

        inline static float Dot(const Vector3& lhs, const Vector3& rhs)
        {
            return DirectX::XMVectorGetX(DirectX::XMVector3Dot(lhs, rhs));
        }

        inline static Vector3 Cross(const Vector3& lhs, const Vector3& rhs)
        {
            return Vector3{ DirectX::XMVector3Cross(lhs, rhs) };
        }

    private:
        friend bool operator==(const Vector3& lhs, const Vector3& rhs) noexcept;

        DirectX::XMVECTOR value;
    };

    inline bool operator==(const Vector3& lhs, const Vector3& rhs) noexcept
    {
        return DirectX::XMVector3Equal(lhs.value, rhs.value);
    }

    inline bool operator!=(const Vector3& lhs, const Vector3& rhs) noexcept
    {
        return !(lhs == rhs);
    }

    inline Vector3 operator-(const Vector3& s) { return Vector3{ DirectX::XMVectorNegate(s) }; }

    inline Vector3 operator+(const Vector3& lhs, const Vector3& rhs) { return Vector3{ lhs } += rhs; }
    inline Vector3 operator-(const Vector3& lhs, const Vector3& rhs) { return Vector3{ lhs } -= rhs; }

    inline Vector3 operator*(const Vector3& lhs, const Vector3& rhs) { return Vector3{ lhs } *= rhs; }
    inline Vector3 operator*(const Vector3& lhs, const Scalar& rhs) { return Vector3{ lhs } *= rhs; }
    inline Vector3 operator*(const Scalar& lhs, const Vector3& rhs) { return Vector3{ rhs } *= lhs; }

    inline Vector3 operator/(const Vector3& lhs, const Vector3& rhs) { return Vector3{ lhs } /= rhs; }
    inline Vector3 operator/(const Vector3& lhs, const Scalar& rhs) { return Vector3{ lhs } /= rhs; }
    inline Vector3 operator/(const Scalar& lhs, const Vector3& rhs) { return Vector3{ rhs } /= lhs; }

    inline float operator|(const Vector3& lhs, const Vector3& rhs) { return Vector3::Dot(lhs, rhs); }
    inline Vector3 operator^(const Vector3& lhs, const Vector3& rhs) { return Vector3::Cross(lhs, rhs); }
}
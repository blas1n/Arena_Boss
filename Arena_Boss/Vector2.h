#pragma once

#include <DirectXMath.h>

namespace Math
{
    class Scalar;

    class Vector2 final
    {
    public:
        static const Vector2 ONE;
        static const Vector2 ZERO;

        static const Vector2 UP;
        static const Vector2 DOWN;

        static const Vector2 RIGHT;
        static const Vector2 LEFT;

    public:
        Vector2() = default;
        Vector2(const Vector2&) = default;
        Vector2(Vector2&&) noexcept = default;

        explicit Vector2(float x, float y)
            : value(DirectX::XMVectorSet(x, y, 0.0f, 0.0f)) {}

        explicit Vector2(const Scalar& s);

        explicit Vector2(DirectX::FXMVECTOR vec)
            : value(vec) {}

        Vector2& operator=(const Vector2&) = default;
        Vector2& operator=(Vector2&&) noexcept = default;

        inline DirectX::XMVECTOR Get() const noexcept { return value; }
        inline operator DirectX::XMVECTOR() const noexcept { return value; }

        inline float GetX() const noexcept { return DirectX::XMVectorGetX(value); }
        inline float GetY() const noexcept { return DirectX::XMVectorGetY(value); }

        inline void SetX(float x) noexcept { value = DirectX::XMVectorSetX(value, x); }
        inline void SetY(float y) noexcept { value = DirectX::XMVectorSetY(value, y); }

        inline float Length() const noexcept
        {
            return DirectX::XMVectorGetX(DirectX::XMVector2Length(value));
        }

        inline float LengthSqrt() const noexcept
        {
            return DirectX::XMVectorGetX(DirectX::XMVector2LengthSq(value));
        }

        inline static Vector2 Normalized(const Vector2& vec) noexcept
        {
            return Vector2{ DirectX::XMVector2Normalize(vec) };
        }

        inline void Normalize() noexcept
        {
            value = DirectX::XMVector2Normalize(value);
        }

        inline float operator[](size_t idx) const noexcept
        {
            return DirectX::XMVectorGetByIndex(value, idx);
        }

        inline Vector2& operator+=(const Vector2& other)
        {
            value = DirectX::XMVectorAdd(value, other);
            return *this;
        }

        inline Vector2& operator-=(const Vector2& other)
        {
            value = DirectX::XMVectorSubtract(value, other);
            return *this;
        }

        inline Vector2& operator*=(const Vector2& other)
        {
            value = DirectX::XMVectorMultiply(value, other);
            return *this;
        }

        Vector2& operator*=(const Scalar& other);

        inline Vector2& operator/=(const Vector2& other)
        {
            value = DirectX::XMVectorDivide(value, other);
            return *this;
        }

        Vector2& operator/=(const Scalar& other);

        inline static float Dot(const Vector2& lhs, const Vector2& rhs)
        {
            return DirectX::XMVectorGetX(DirectX::XMVector2Dot(lhs, rhs));
        }

    private:
        DirectX::XMVECTOR value;
    };

    inline Vector2 operator-(const Vector2& s) { return Vector2{ DirectX::XMVectorNegate(s) }; }

    inline Vector2 operator+(const Vector2& lhs, const Vector2& rhs) { return Vector2{ lhs } += rhs; }
    inline Vector2 operator-(const Vector2& lhs, const Vector2& rhs) { return Vector2{ lhs } -= rhs; }

    inline Vector2 operator*(const Vector2& lhs, const Vector2& rhs) { return Vector2{ lhs } *= rhs; }
    inline Vector2 operator*(const Vector2& lhs, const Scalar& rhs) { return Vector2{ lhs } *= rhs; }

    inline Vector2 operator/(const Vector2& lhs, const Vector2& rhs) { return Vector2{ lhs } /= rhs; }
    inline Vector2 operator/(const Vector2& lhs, const Scalar& rhs) { return Vector2{ lhs } /= rhs; }

    inline float operator|(const Vector2& lhs, const Vector2& rhs) { return Vector2::Dot(lhs, rhs); }
}
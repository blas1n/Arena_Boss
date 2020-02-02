#pragma once

#define WIN32_LEAN_AND_MEAN
#include <Windows.h>
#include "Scalar.h"

namespace ArenaBoss::Math
{
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
        Vector2() noexcept = default;
        Vector2(const Vector2&) noexcept = default;
        Vector2(Vector2&&) noexcept = default;

        Vector2(POINT point) noexcept
            : value(DirectX::XMVectorSet(static_cast<float>(point.x),
                static_cast<float>(point.y), 0.0f, 0.0f)) {}

        explicit Vector2(float x, float y) noexcept
            : value(DirectX::XMVectorSet(x, y, 0.0f, 0.0f)) {}

        explicit Vector2(const float elems[2]) noexcept
            : value(DirectX::XMVectorSet(elems[0], elems[1], 0.0f, 0.0f)) {}

        explicit Vector2(const Scalar& s) noexcept : value(s) {}
        
        Vector2(DirectX::FXMVECTOR vec) noexcept : value(vec) {}

        Vector2& operator=(const Vector2&) = default;
        Vector2& operator=(Vector2&&) noexcept = default;

        Vector2& operator=(POINT point) noexcept
        {
            value = DirectX::XMVectorSet(static_cast<float>(point.x),
                static_cast<float>(point.y), 0.0f, 0.0f);
            return *this;
        }

        inline DirectX::XMVECTOR Get() const noexcept { return value; }
        inline operator DirectX::XMVECTOR() const noexcept { return value; }

        inline void Set(float x, float y) noexcept
        {
            value = DirectX::XMVectorSet(x, y, 0.0f, 0.0f);
        }

        inline void Set(const float elems[2]) noexcept
        {
            value = DirectX::XMVectorSet(elems[0], elems[1], 0.0f, 0.0f);
        }

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

        inline Vector2 Normalized() const noexcept
        {
            return DirectX::XMVector2Normalize(value);
        }

        inline void Normalize() noexcept
        {
            value = DirectX::XMVector2Normalize(value);
        }

        inline float& operator[](size_t idx) noexcept
        {
            float* retPtr;
            DirectX::XMVectorGetByIndexPtr(retPtr, value, idx);
            return *retPtr;
        }

        inline float operator[](size_t idx) const noexcept
        {
            return DirectX::XMVectorGetByIndex(value, idx);
        }

        inline Vector2 operator-() const noexcept
        {
            return DirectX::XMVectorNegate(value);
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

        inline Vector2& operator*=(const Scalar& other)
        {
            value = DirectX::XMVectorMultiply(value, other);
            return *this;
        }

        inline Vector2& operator/=(const Vector2& other)
        {
            value = DirectX::XMVectorDivide(value, other);
            return *this;
        }

        inline Vector2& operator/=(const Scalar& other)
        {
            value = DirectX::XMVectorDivide(value, other);
            return *this;
        }

        inline static float Dot(const Vector2& lhs, const Vector2& rhs)
        {
            return DirectX::XMVectorGetX(DirectX::XMVector2Dot(lhs, rhs));
        }

        inline POINT AsPoint() const noexcept
        {
            return POINT
            {
                static_cast<LONG>(DirectX::XMVectorGetX(value)),
                static_cast<LONG>(DirectX::XMVectorGetY(value))
            };
        }

        inline operator POINT() const noexcept
        {
            return AsPoint();
        }

    private:
        friend bool operator==(const Vector2& lhs, const Vector2& rhs) noexcept;

        DirectX::XMVECTOR value;
    };

    inline bool operator==(const Vector2& lhs, const Vector2& rhs) noexcept
    {
        return DirectX::XMVector2Equal(lhs.value, rhs.value);
    }

    inline bool operator!=(const Vector2& lhs, const Vector2& rhs) noexcept
    {
        return !(lhs == rhs);
    }

    inline Vector2 operator+(const Vector2& lhs, const Vector2& rhs) { return Vector2{ lhs } += rhs; }
    inline Vector2 operator-(const Vector2& lhs, const Vector2& rhs) { return Vector2{ lhs } -= rhs; }

    inline Vector2 operator*(const Vector2& lhs, const Vector2& rhs) { return Vector2{ lhs } *= rhs; }
    inline Vector2 operator*(const Vector2& lhs, const Scalar& rhs) { return Vector2{ lhs } *= rhs; }
    inline Vector2 operator*(const Scalar& lhs, const Vector2& rhs) { return Vector2{ rhs } *= lhs; }

    inline Vector2 operator/(const Vector2& lhs, const Vector2& rhs) { return Vector2{ lhs } /= rhs; }
    inline Vector2 operator/(const Vector2& lhs, const Scalar& rhs) { return Vector2{ lhs } /= rhs; }
    inline Vector2 operator/(const Scalar& lhs, const Vector2& rhs) { return Vector2{ rhs } /= lhs; }

    inline float operator|(const Vector2& lhs, const Vector2& rhs) { return Vector2::Dot(lhs, rhs); }
}
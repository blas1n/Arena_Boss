#pragma once

#include <DirectXMath.h>

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
        union
        {
            DirectX::XMFLOAT2 value;
            struct
            {
                float x;
                float y;
            };
        };

    public:
        Vector2() noexcept = default;
        Vector2(const Vector2&) noexcept = default;
        Vector2(Vector2&&) noexcept = default;

        explicit Vector2(float inX, float inY) noexcept
            : value(inX, inY) {}

        explicit Vector2(const float* elems) noexcept
            : value(elems) {}

        Vector2(DirectX::FXMVECTOR vec) noexcept
            : Vector2()
        {
            DirectX::XMStoreFloat2(&value, vec);
        }

        Vector2(const DirectX::XMFLOAT2& vec) noexcept
            : value(vec) {}

        Vector2& operator=(const Vector2&) noexcept = default;
        Vector2& operator=(Vector2&&) noexcept = default;

        Vector2& operator=(DirectX::FXMVECTOR vec) noexcept;
        Vector2& operator=(const DirectX::XMFLOAT2& vec) noexcept;

        inline operator DirectX::XMVECTOR() const noexcept { return DirectX::XMLoadFloat2(&value); }

        void Set(float inX, float inY) noexcept;
        void Set(const float* elems) noexcept;

        float Length() const noexcept;
        float LengthSqrt() const noexcept;

        inline Vector2 Normalized() const noexcept
        {
            return DirectX::XMVector2Normalize(*this);
        }

        inline void Normalize() noexcept
        {
            *this = DirectX::XMVector2Normalize(*this);
        }

        float& operator[](size_t idx) noexcept;
        float operator[](size_t idx) const noexcept;

        inline Vector2 operator+() const noexcept { return *this; }
        inline Vector2 operator-() const noexcept { return *this * -1.0f; }

        inline Vector2& operator+=(const Vector2& other) noexcept
        {
            return Calc(other, &DirectX::XMVectorAdd);
        }

        inline Vector2& operator-=(const Vector2& other) noexcept
        {
            return Calc(other, &DirectX::XMVectorSubtract);
        }

        inline Vector2& operator*=(const Vector2& other) noexcept
        {
            return Calc(other, &DirectX::XMVectorMultiply);
        }

        inline Vector2& operator*=(float scaler) noexcept
        {
            return Calc(scaler, &DirectX::XMVectorMultiply);
        }

        inline Vector2& operator/=(const Vector2& other) noexcept
        {
            return Calc(other, &DirectX::XMVectorDivide);
        }

        inline Vector2& operator/=(float scaler) noexcept
        {
            return Calc(scaler, &DirectX::XMVectorDivide);
        }

        inline static float Dot(const Vector2& lhs, const Vector2& rhs)
        {
            return DirectX::XMVectorGetX(DirectX::XMVector2Dot(lhs, rhs));
        }

    private:
        friend bool operator==(const Vector2& lhs, const Vector2& rhs) noexcept;

        using Operator = DirectX::XMVECTOR(__vectorcall *)(DirectX::XMVECTOR, DirectX::XMVECTOR);

        Vector2& Calc(const Vector2& other, Operator oper) noexcept;
        Vector2& Calc(float scaler, Operator oper) noexcept;
    };

    inline bool operator==(const Vector2& lhs, const Vector2& rhs) noexcept
    {
        return DirectX::XMVector2Equal(lhs, rhs);
    }

    inline bool operator!=(const Vector2& lhs, const Vector2& rhs) noexcept
    {
        return !(lhs == rhs);
    }

    inline Vector2 operator+(const Vector2& lhs, const Vector2& rhs) { return Vector2{ lhs } += rhs; }
    inline Vector2 operator-(const Vector2& lhs, const Vector2& rhs) { return Vector2{ lhs } -= rhs; }

    inline Vector2 operator*(const Vector2& lhs, const Vector2& rhs) { return Vector2{ lhs } *= rhs; }
    inline Vector2 operator*(const Vector2& lhs, float rhs) { return Vector2{ lhs } *= rhs; }
    inline Vector2 operator*(float lhs, const Vector2& rhs) { return Vector2{ rhs } *= lhs; }

    inline Vector2 operator/(const Vector2& lhs, const Vector2& rhs) { return Vector2{ lhs } /= rhs; }
    inline Vector2 operator/(const Vector2& lhs, float rhs) { return Vector2{ lhs } /= rhs; }
    inline Vector2 operator/(float lhs, const Vector2& rhs) { return Vector2{ rhs } /= lhs; }

    inline float operator|(const Vector2& lhs, const Vector2& rhs) { return Vector2::Dot(lhs, rhs); }
}
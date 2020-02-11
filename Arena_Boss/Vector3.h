#pragma once

#include <DirectXMath.h>

namespace ArenaBoss::Math
{
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
        union
        {
            DirectX::XMFLOAT3 value;
            struct
            {
                float x;
                float y;
                float z;
            };
        };

    public:
        Vector3() noexcept = default;
        Vector3(const Vector3&) noexcept = default;
        Vector3(Vector3&&) noexcept = default;

        explicit Vector3(float inX, float inY, float inZ) noexcept
            : value(inX, inY, inZ) {}

        explicit Vector3(const float* elems) noexcept
            : value(elems) {}

        Vector3(const class Vector2& xy, float z = 0.0f) noexcept;

        Vector3(DirectX::FXMVECTOR vec) noexcept
            : Vector3()
        {
            DirectX::XMStoreFloat3(&value, vec);
        }

        Vector3(const DirectX::XMFLOAT3& vec) noexcept
            : value(vec) {}

        Vector3& operator=(const Vector3&) noexcept = default;
        Vector3& operator=(Vector3&&) noexcept = default;

        Vector3& operator=(DirectX::FXMVECTOR vec) noexcept;
        Vector3& operator=(const DirectX::XMFLOAT3& vec) noexcept;

        inline operator DirectX::XMVECTOR() const noexcept { return DirectX::XMLoadFloat3(&value); }
        operator Vector2() const noexcept;

        void Set(float inX, float inY, float inZ) noexcept;
        void Set(const float* elems) noexcept;

        float Length() const noexcept;
        float LengthSqrt() const noexcept;

        inline Vector3 Normalized() const noexcept
        {
            return DirectX::XMVector3Normalize(*this);
        }

        inline void Normalize() noexcept
        {
            *this = DirectX::XMVector3Normalize(*this);
        }

        float& operator[](size_t idx);
        float operator[](size_t idx) const;

        inline Vector3& operator+=(const Vector3& other) noexcept
        {
            return Calc(other, &DirectX::XMVectorAdd);
        }

        inline Vector3& operator-=(const Vector3& other) noexcept
        {
            return Calc(other, &DirectX::XMVectorSubtract);
        }

        inline Vector3& operator*=(const Vector3& other) noexcept
        {
            return Calc(other, &DirectX::XMVectorMultiply);
        }

        inline Vector3& operator*=(float scaler) noexcept
        {
            return Calc(scaler, &DirectX::XMVectorMultiply);
        }

        inline Vector3& operator/=(const Vector3& other) noexcept
        {
            return Calc(other, &DirectX::XMVectorDivide);
        }

        inline Vector3& operator/=(float scaler) noexcept
        {
            return Calc(scaler, &DirectX::XMVectorDivide);
        }

        inline Vector3& operator^=(const Vector3& other) noexcept
        {
            return Calc(other, &DirectX::XMVector3Cross);
        }

        inline static float Dot(const Vector3& lhs, const Vector3& rhs)
        {
            return DirectX::XMVectorGetX(DirectX::XMVector3Dot(lhs, rhs));
        }

        inline static Vector3 Cross(const Vector3& lhs, const Vector3& rhs)
        {
            return DirectX::XMVector3Cross(lhs, rhs);
        }

    private:
        friend bool operator==(const Vector3& lhs, const Vector3& rhs) noexcept;

        using Operator = DirectX::XMVECTOR(XM_CALLCONV*)(DirectX::XMVECTOR, DirectX::XMVECTOR);

        Vector3& Calc(const Vector3& other, Operator oper) noexcept;
        Vector3& Calc(float scaler, Operator oper) noexcept;
    };

    inline bool operator==(const Vector3& lhs, const Vector3& rhs) noexcept
    {
        return DirectX::XMVector3Equal(lhs, rhs);
    }

    inline bool operator!=(const Vector3& lhs, const Vector3& rhs) noexcept
    {
        return !(lhs == rhs);
    }

    inline Vector3 operator+(const Vector3& lhs, const Vector3& rhs) { return Vector3{ lhs } += rhs; }
    inline Vector3 operator-(const Vector3& lhs, const Vector3& rhs) { return Vector3{ lhs } -= rhs; }

    inline Vector3 operator*(const Vector3& lhs, const Vector3& rhs) { return Vector3{ lhs } *= rhs; }
    inline Vector3 operator*(const Vector3& lhs, float rhs) { return Vector3{ lhs } *= rhs; }
    inline Vector3 operator*(float lhs, const Vector3& rhs) { return Vector3{ rhs } *= lhs; }

    inline Vector3 operator/(const Vector3& lhs, const Vector3& rhs) { return Vector3{ lhs } /= rhs; }
    inline Vector3 operator/(const Vector3& lhs, float rhs) { return Vector3{ lhs } /= rhs; }

    inline float operator|(const Vector3& lhs, const Vector3& rhs) { return Vector3::Dot(lhs, rhs); }
    inline Vector3 operator^(const Vector3& lhs, const Vector3& rhs) { return Vector3::Cross(lhs, rhs); }

    inline Vector3 operator+(const Vector3& vec) noexcept { return vec; }
    inline Vector3 operator-(const Vector3& vec) noexcept { return vec * -1.0f; }
}
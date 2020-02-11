#pragma once

#include <DirectXMath.h>

namespace ArenaBoss::Math
{
    class Vector4 final
    {
    public:
        static const Vector4 ONE;
        static const Vector4 ZERO;

    public:
        union
        {
            DirectX::XMFLOAT4 value;
            struct
            {
                float x;
                float y;
                float z;
                float w;
            };
        };

    public:
        Vector4() noexcept = default;
        Vector4(const Vector4&) noexcept = default;
        Vector4(Vector4&&) noexcept = default;

        explicit Vector4(float inX, float inY, float inZ, float inW) noexcept
            : value(inX, inY, inZ, inW) {}

        explicit Vector4(const float* elems) noexcept
            : value(elems) {}

        Vector4(const class Vector2& xy, float z = 0.0f, float w = 0.0f) noexcept;
        Vector4(const class Vector3& xyz, float w = 0.0f) noexcept;

        Vector4(DirectX::FXMVECTOR vec) noexcept
            : Vector4()
        {
            DirectX::XMStoreFloat4(&value, vec);
        }

        Vector4(const DirectX::XMFLOAT4& vec) noexcept
            : value(vec) {}

        Vector4& operator=(const Vector4&) noexcept = default;
        Vector4& operator=(Vector4&&) noexcept = default;

        Vector4& operator=(DirectX::FXMVECTOR vec) noexcept;
        Vector4& operator=(const DirectX::XMFLOAT4& vec) noexcept;

        inline operator DirectX::XMVECTOR() const noexcept { return DirectX::XMLoadFloat4(&value); }
        operator Vector2() const noexcept;
        operator Vector3() const noexcept;

        void Set(float inX, float inY, float inZ, float inW) noexcept;
        void Set(const float* elems) noexcept;

        float Length() const noexcept;
        float LengthSqrt() const noexcept;

        inline Vector4 Normalized() const noexcept
        {
            return DirectX::XMVector4Normalize(*this);
        }

        inline void Normalize() noexcept
        {
            *this = DirectX::XMVector4Normalize(*this);
        }

        float& operator[](size_t idx);
        float operator[](size_t idx) const;

        inline Vector4& operator+=(const Vector4& other) noexcept
        {
            return Calc(other, &DirectX::XMVectorAdd);
        }

        inline Vector4& operator-=(const Vector4& other) noexcept
        {
            return Calc(other, &DirectX::XMVectorSubtract);
        }

        inline Vector4& operator*=(const Vector4& other) noexcept
        {
            return Calc(other, &DirectX::XMVectorMultiply);
        }

        inline Vector4& operator*=(float scaler) noexcept
        {
            return Calc(scaler, &DirectX::XMVectorMultiply);
        }

        inline Vector4& operator/=(const Vector4& other) noexcept
        {
            return Calc(other, &DirectX::XMVectorDivide);
        }

        inline Vector4& operator/=(float scaler) noexcept
        {
            return Calc(scaler, &DirectX::XMVectorDivide);
        }

        inline static float Dot(const Vector4& lhs, const Vector4& rhs)
        {
            return DirectX::XMVectorGetX(DirectX::XMVector4Dot(lhs, rhs));
        }

    private:
        friend bool operator==(const Vector4& lhs, const Vector4& rhs) noexcept;

        using Operator = DirectX::XMVECTOR(XM_CALLCONV*)(DirectX::XMVECTOR, DirectX::XMVECTOR);

        Vector4& Calc(const Vector4& other, Operator oper) noexcept;
        Vector4& Calc(float scaler, Operator oper) noexcept;
    };

    inline bool operator==(const Vector4& lhs, const Vector4& rhs) noexcept
    {
        return DirectX::XMVector4Equal(lhs, rhs);
    }

    inline bool operator!=(const Vector4& lhs, const Vector4& rhs) noexcept
    {
        return !(lhs == rhs);
    }

    inline Vector4 operator+(const Vector4& lhs, const Vector4& rhs) { return Vector4{ lhs } += rhs; }
    inline Vector4 operator-(const Vector4& lhs, const Vector4& rhs) { return Vector4{ lhs } -= rhs; }

    inline Vector4 operator*(const Vector4& lhs, const Vector4& rhs) { return Vector4{ lhs } *= rhs; }
    inline Vector4 operator*(const Vector4& lhs, float rhs) { return Vector4{ lhs } *= rhs; }
    inline Vector4 operator*(float lhs, const Vector4& rhs) { return Vector4{ rhs } *= lhs; }

    inline Vector4 operator/(const Vector4& lhs, const Vector4& rhs) { return Vector4{ lhs } /= rhs; }
    inline Vector4 operator/(const Vector4& lhs, float rhs) { return Vector4{ lhs } /= rhs; }

    inline float operator|(const Vector4& lhs, const Vector4& rhs) { return Vector4::Dot(lhs, rhs); }

    inline Vector4 operator+(const Vector4& vec) noexcept { return vec; }
    inline Vector4 operator-(const Vector4& vec) noexcept { return vec * -1.0f; }
}
#pragma once

#include <DirectXMath.h>

namespace Math
{
    class Scalar final
    {
    public:
        Scalar(float f = 0.0f) { value = DirectX::XMVectorReplicate(f); }
        explicit Scalar(DirectX::XMVECTOR vec) { value = vec; }

        Scalar(const Scalar&) = default;
        inline Scalar& operator=(const Scalar&) = default;
        ~Scalar() = default;

        inline operator DirectX::XMVECTOR() const noexcept { return value; }
        inline operator float() const noexcept { return DirectX::XMVectorGetX(value); }

        inline Scalar& operator+=(const Scalar& other)
        {
            value = DirectX::XMVectorAdd(value, other);
            return *this;
        }

        inline Scalar& operator-=(const Scalar& other)
        {
            value = DirectX::XMVectorSubtract(value, other);
            return *this;
        }

        inline Scalar& operator*=(const Scalar& other)
        {
            value = DirectX::XMVectorMultiply(value, other);
            return *this;
        }

        inline Scalar& operator/=(const Scalar& other)
        {
            value = DirectX::XMVectorDivide(value, other);
            return *this;
        }

    private:
        DirectX::XMVECTOR value;
    };

    inline bool operator==(const Scalar& lhs, const Scalar& rhs)
    {
        return DirectX::XMVectorGetX(lhs) == DirectX::XMVectorGetX(rhs);
    }

    inline bool operator!=(const Scalar& lhs, const Scalar& rhs)
    {
        return !(lhs == rhs);
    }

    inline Scalar operator-(const Scalar& s) { return Scalar{ DirectX::XMVectorNegate(s) }; }

    inline Scalar operator+(const Scalar& lhs, const Scalar& rhs) { return Scalar{ lhs } += rhs; }
    inline Scalar operator-(const Scalar& lhs, const Scalar& rhs) { return Scalar{ lhs } -= rhs; }
    inline Scalar operator*(const Scalar& lhs, const Scalar& rhs) { return Scalar{ lhs } *= rhs; }
    inline Scalar operator/(const Scalar& lhs, const Scalar& rhs) { return Scalar{ lhs } /= rhs; }
}
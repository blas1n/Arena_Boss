#ifndef __VECTOR4_H__
#define __VECTOR4_H__

#pragma once

#include <glm/vec4.hpp>
#include <glm/glm.hpp>

namespace ArenaBoss::Math
{
    template <class T, class P>
    class TVector2;

    template <class T, class P>
    class TVector3;

    template <class T, class P>
    class TVector4 final
    {
    public:
        constexpr static TVector4 ONE();
        constexpr static TVector4 ZERO();

    public:
        union
        {
            P value;

            struct
            {
                T x;
                T y;
                T z;
                T w;
            };
        };

    public:
        constexpr TVector4() noexcept : value() {}
        constexpr TVector4(const TVector4&) noexcept = default;
        constexpr TVector4(TVector4&&) noexcept = default;

        explicit constexpr TVector4(T inX, T inY, T inZ, T inW) noexcept
            : value(inX, inY, inZ, inW) {}

        explicit constexpr TVector4(const T* elems) noexcept
            : value(elems[0], elems[1], elems[2], elems[3]) {}

        TVector4(const TVector2<T, P>& xy, float z = 0.0f, float w = 0.0f) noexcept;
        TVector4(const TVector3<T, P>& xyz, float w = 0.0f) noexcept;

        constexpr TVector4(const P& vec) noexcept
            : value(vec) {}

        constexpr TVector4(P&& vec) noexcept
            : value(std::move(vec)) {}

        constexpr TVector4& operator=(const TVector4&) noexcept = default;
        constexpr TVector4& operator=(TVector4&&) noexcept = default;

        constexpr TVector4& operator=(const P& vec) noexcept { value = vec; }

        constexpr operator P&() noexcept { return value; }
        constexpr operator const P&() const noexcept { return value; }

        constexpr operator float*() noexcept { return &x; }
        constexpr operator const float*() const noexcept { return &x; }

        operator TVector2<T, P>() const noexcept;
        operator TVector3<T, P>() const noexcept;

        void Set(float inX, float inY, float inZ, float inW) noexcept;

        inline void Set(const float* elems) noexcept
        {
            Set(elems[0], elems[1], elems[2], elems[3]);
        }

        inline float Length() const noexcept { return glm::sqrt(LengthSqrt()); }
        inline float LengthSqrt() const noexcept { return Dot(value, value); }

        inline TVector4 Normalized() const noexcept
        {
            return glm::normalize(value);
        }

        inline void Normalize() noexcept
        {
            *this = Normalized();
        }

        inline float& operator[](glm::length_t idx) { return value[idx]; }
        inline float operator[](glm::length_t idx) const { return value[idx]; }

        constexpr TVector4& operator+=(const TVector4& other) noexcept
        {
            value += other.value;
            return *this;
        }

        constexpr TVector4& operator-=(const TVector4& other) noexcept
        {
            value -= other.value;
            return *this;
        }

        constexpr TVector4& operator*=(const TVector4& other) noexcept
        {
            value *= other.value;
            return *this;
        }

        constexpr TVector4& operator*=(float scaler) noexcept
        {
            value *= scaler;
            return *this;
        }

        constexpr TVector4& operator/=(const TVector4& other) noexcept
        {
            value /= other.value;
            return *this;
        }

        constexpr TVector4& operator/=(float scaler) noexcept
        {
            value /= scaler;
            return *this;
        }

        inline static float Dot(const TVector4& lhs, const TVector4& rhs)
        {
            return glm::dot(lhs.value, rhs.value);
        }

    private:
        friend bool operator==(const TVector4& lhs, const TVector4& rhs) noexcept;
    };

    template <class T, class P>
    constexpr bool operator==(const TVector4<T, P>& lhs, const TVector4<T, P>& rhs) noexcept
    {
        return lhs.value == rhs.value;
    }

    template <class T, class P>
    constexpr bool operator!=(const TVector4<T, P>& lhs, const TVector4<T, P>& rhs) noexcept
    {
        return !(lhs == rhs);
    }

    template <class T, class P>
    inline TVector4<T, P> operator+(const TVector4<T, P>& lhs, const TVector4<T, P>& rhs) { return TVector4{ lhs } += rhs; }

    template <class T, class P>
    inline TVector4<T, P> operator-(const TVector4<T, P>& lhs, const TVector4<T, P>& rhs) { return TVector4{ lhs } -= rhs; }

    template <class T, class P>
    inline TVector4<T, P> operator*(const TVector4<T, P>& lhs, const TVector4<T, P>& rhs) { return TVector4{ lhs } *= rhs; }

    template <class T, class P>
    inline TVector4<T, P> operator*(const TVector4<T, P>& lhs, float rhs) { return TVector4{ lhs } *= rhs; }

    template <class T, class P>
    inline TVector4<T, P> operator*(float lhs, const TVector4<T, P>& rhs) { return TVector4{ rhs } *= lhs; }

    template <class T, class P>
    inline TVector4<T, P> operator/(const TVector4<T, P>& lhs, const TVector4<T, P>& rhs) { return TVector4{ lhs } /= rhs; }

    template <class T, class P>
    inline TVector4<T, P> operator/(const TVector4<T, P>& lhs, float rhs) { return TVector4{ lhs } /= rhs; }

    template <class T, class P>
    inline float operator|(const TVector4<T, P>& lhs, const TVector4<T, P>& rhs) { return TVector4::Dot(lhs, rhs); }

    template <class T, class P>
    inline TVector4<T, P> operator+(const TVector4<T, P>& vec) noexcept { return vec; }

    template <class T, class P>
    inline TVector4<T, P> operator-(const TVector4<T, P>& vec) noexcept { return vec * -1.0f; }

    using Vector4 = TVector4<float, glm::vec4>;
    using IntVector4 = TVector4<int32_t, glm::i32vec4>;
    using UintVector4 = TVector4<uint32_t, glm::u32vec4>;
}

#include "Vector4.hpp"

#endif
#ifndef __VECTOR2_H__
#define __VECTOR2_H__

#pragma once

#include <glm/vec2.hpp>
#include <glm/glm.hpp>

namespace ArenaBoss::Math
{
    template <class T, class P>
    class TVector2 final
    {
    public:
        constexpr static TVector2 ONE();
        constexpr static TVector2 ZERO();

        constexpr static TVector2 UP();
        constexpr static TVector2 DOWN();

        constexpr static TVector2 RIGHT();
        constexpr static TVector2 LEFT();

    public:
        union
        {
            P value;

            struct
            {
                T x;
                T y;
            };
        };

    public:
        constexpr TVector2() noexcept : value() {}

        constexpr TVector2(const TVector2& other) noexcept
            : value(other.value) {}

        constexpr TVector2(TVector2&& other) noexcept
            : value(std::move(other.value)) {}

        explicit constexpr TVector2(T scalar) noexcept
            : value(scalar) {}

        explicit constexpr TVector2(T inX, T inY) noexcept
            : value(inX, inY) {}

        explicit constexpr TVector2(const T* elems) noexcept
            : value(elems[0], elems[1]) {}

        constexpr TVector2(const P& vec) noexcept
            : value(vec) {}

        constexpr TVector2(P&& vec) noexcept
            : value(std::move(vec)) {}

        constexpr TVector2& operator=(const TVector2& other) noexcept
        {
            value = other.value;
            return *this;
        }

        constexpr TVector2& operator=(TVector2&& other) noexcept
        {
            value = std::move(other.value);
            return *this;
        }

        constexpr TVector2& operator=(const P& vec) noexcept
        {
            value = vec;
            return *this;
        }

        constexpr TVector2& operator=(P&& vec) noexcept
        {
            value = std::move(vec);
            return *this;
        }

        constexpr operator P&() noexcept { return value; }
        constexpr operator const P&() const noexcept { return value; }

        constexpr operator T*() noexcept { return &x; }
        constexpr operator const T*() const noexcept { return &x; }

        void Set(T inX, T inY) noexcept;
        
        inline void Set(const T* elems) noexcept
        {
            Set(elems[0], elems[1]);
        }

        inline float Length() const noexcept { return glm::sqrt(LengthSqrt()); }
        inline float LengthSqrt() const noexcept { return Dot(value, value); }

        inline TVector2 Normalized() const noexcept
        {
            return glm::normalize(value);
        }

        inline void Normalize() noexcept
        {
            *this = Normalized();
        }

        inline float& operator[](glm::length_t idx) { return value[idx]; }
        inline float operator[](glm::length_t idx) const { return value[idx]; }

        constexpr TVector2& operator+=(const TVector2& other) noexcept
        {
            value += other.value;
            return *this;
        }

        constexpr TVector2& operator-=(const TVector2& other) noexcept
        {
            value -= other.value;
            return *this;
        }

        constexpr TVector2& operator*=(const TVector2& other) noexcept
        {
            value *= other.value;
            return *this;
        }

        constexpr TVector2& operator*=(float scaler) noexcept
        {
            value *= scaler;
            return *this;
        }

        constexpr TVector2& operator/=(const TVector2& other) noexcept
        {
            value /= other.value;
            return *this;
        }

        constexpr TVector2& operator/=(float scaler) noexcept
        {
            value /= scaler;
            return *this;
        }

        inline static float Dot(const TVector2& lhs, const TVector2& rhs)
        {
            return glm::dot(lhs.value, rhs.value);
        }

    private:
        friend bool operator==(const TVector2& lhs, const TVector2& rhs) noexcept;
    };

    template <class T, class P>
    constexpr bool operator==(const TVector2<T, P>& lhs, const TVector2<T, P>& rhs) noexcept
    {
        return lhs.value == rhs.value;
    }

    template <class T, class P>
    constexpr bool operator!=(const TVector2<T, P>& lhs, const TVector2<T, P>& rhs) noexcept
    {
        return !(lhs == rhs);
    }

    template <class T, class P>
    inline TVector2<T, P> operator+(const TVector2<T, P>& lhs, const TVector2<T, P>& rhs) { return TVector2{ lhs } += rhs; }

    template <class T, class P>
    inline TVector2<T, P> operator-(const TVector2<T, P>& lhs, const TVector2<T, P>& rhs) { return TVector2{ lhs } -= rhs; }

    template <class T, class P>
    inline TVector2<T, P> operator*(const TVector2<T, P>& lhs, const TVector2<T, P>& rhs) { return TVector2{ lhs } *= rhs; }

    template <class T, class P>
    inline TVector2<T, P> operator*(const TVector2<T, P>& lhs, float rhs) { return TVector2{ lhs } *= rhs; }

    template <class T, class P>
    inline TVector2<T, P> operator*(float lhs, const TVector2<T, P>& rhs) { return TVector2{ rhs } *= lhs; }

    template <class T, class P>
    inline TVector2<T, P> operator/(const TVector2<T, P>& lhs, const TVector2<T, P>& rhs) { return TVector2{ lhs } /= rhs; }

    template <class T, class P>
    inline TVector2<T, P> operator/(const TVector2<T, P>& lhs, float rhs) { return TVector2{ lhs } /= rhs; }

    template <class T, class P>
    inline float operator|(const TVector2<T, P>& lhs, const TVector2<T, P>& rhs) { return TVector2::Dot(lhs, rhs); }

    template <class T, class P>
    inline TVector2<T, P> operator+(const TVector2<T, P>& vec) noexcept { return vec; }

    template <class T, class P>
    inline TVector2<T, P> operator-(const TVector2<T, P>& vec) noexcept { return vec * -1.0f; }

    using Vector2 = TVector2<float, glm::vec2>;
    using IntVector2 = TVector2<int32_t, glm::i32vec2>;
    using UintVector2 = TVector2<uint32_t, glm::u32vec2>;
}

#include "Vector2.hpp"

#endif
#pragma once

#include <glm/vec3.hpp>
#include <glm/glm.hpp>

namespace ArenaBoss::Math
{
    template <class T, class P>
    class TVector2;

    template <class T, class P>
    class TVector3 final
    {
    public:
        static const TVector3 ONE;
        static const TVector3 ZERO;

        static const TVector3 UP;
        static const TVector3 DOWN;

        static const TVector3 RIGHT;
        static const TVector3 LEFT;

        static const TVector3 FORWARD;
        static const TVector3 BACKWARD;

    public:
        union
        {
            P value;

            struct
            {
                T x;
                T y;
                T z;
            };
        };

    public:
        constexpr TVector3() noexcept : value() {}
        constexpr TVector3(const TVector3&) noexcept = default;
        constexpr TVector3(TVector3&&) noexcept = default;

        explicit constexpr TVector3(T inX, T inY, T inZ) noexcept
            : value(inX, inY, inZ) {}

        explicit constexpr TVector3(const T* elems) noexcept
            : value(elems[0], elems[1], elems[2]) {}

        TVector3(const TVector2<T, P>& xy, float z = 0.0f) noexcept;

        constexpr TVector3(const P& vec) noexcept
            : value(vec) {}

        constexpr TVector3& operator=(const TVector3&) noexcept = default;
        constexpr TVector3& operator=(TVector3&&) noexcept = default;

        constexpr TVector3& operator=(const P& vec) noexcept { value = vec; }

        constexpr operator P& () noexcept { return value; }
        constexpr operator const P& () const noexcept { return value; }

        constexpr operator float* () noexcept { return &x; }
        constexpr operator const float* () const noexcept { return &x; }

        operator TVector2<T, P>() const noexcept;

        void Set(float inX, float inY, float inZ) noexcept;
        void Set(const float* elems) noexcept;

        inline float Length() const noexcept { glm::sqrt(LengthSqrt()); }
        inline float LengthSqrt() const noexcept { Dot(value, value); }

        inline TVector3 Normalized() const noexcept
        {
            return glm::normalize(value);
        }

        inline void Normalize() noexcept
        {
            *this = Normalized();
        }

        inline float& operator[](size_t idx) { return value[idx]; }
        inline float operator[](size_t idx) const { return value[idx]; }

        constexpr TVector3& operator+=(const TVector3& other) noexcept
        {
            value += other.value;
            return *this;
        }

        constexpr TVector3& operator-=(const TVector3& other) noexcept
        {
            value -= other.value;
            return *this;
        }

        constexpr TVector3& operator*=(const TVector3& other) noexcept
        {
            value *= other.value;
            return *this;
        }

        constexpr TVector3& operator*=(float scaler) noexcept
        {
            value *= scaler;
            return *this;
        }

        constexpr TVector3& operator/=(const TVector3& other) noexcept
        {
            value /= other.value;
            return *this;
        }

        constexpr TVector3& operator/=(float scaler) noexcept
        {
            value /= scaler;
            return *this;
        }

        inline TVector3& operator^=(const TVector3& other) noexcept
        {
            value = glm::cross(value, other.value);
            return *this;
        }

        inline static float Dot(const TVector3& lhs, const TVector3& rhs)
        {
            return glm::dot(lhs.value, rhs.value);
        }

        inline static TVector3 Cross(const TVector3& lhs, const TVector3& rhs)
        {
            return glm::cross(lhs.value, rhs.value);
        }

    private:
        friend bool operator==(const TVector3& lhs, const TVector3& rhs) noexcept;
    };

    template <class T, class P>
    constexpr bool operator==(const TVector3<T, P>& lhs, const TVector3<T, P>& rhs) noexcept
    {
        return lhs.value == rhs.value;
    }

    template <class T, class P>
    constexpr bool operator!=(const TVector3<T, P>& lhs, const TVector3<T, P>& rhs) noexcept
    {
        return !(lhs == rhs);
    }

    template <class T, class P>
    inline TVector3<T, P> operator+(const TVector3<T, P>& lhs, const TVector3<T, P>& rhs) { return TVector3{ lhs } += rhs; }

    template <class T, class P>
    inline TVector3<T, P> operator-(const TVector3<T, P>& lhs, const TVector3<T, P>& rhs) { return TVector3{ lhs } -= rhs; }

    template <class T, class P>
    inline TVector3<T, P> operator*(const TVector3<T, P>& lhs, const TVector3<T, P>& rhs) { return TVector3{ lhs } *= rhs; }

    template <class T, class P>
    inline TVector3<T, P> operator*(const TVector3<T, P>& lhs, float rhs) { return TVector3{ lhs } *= rhs; }

    template <class T, class P>
    inline TVector3<T, P> operator*(float lhs, const TVector3<T, P>& rhs) { return TVector3{ rhs } *= lhs; }

    template <class T, class P>
    inline TVector3<T, P> operator/(const TVector3<T, P>& lhs, const TVector3<T, P>& rhs) { return TVector3{ lhs } /= rhs; }

    template <class T, class P>
    inline TVector3<T, P> operator/(const TVector3<T, P>& lhs, float rhs) { return TVector3{ lhs } /= rhs; }

    template <class T, class P>
    inline float operator|(const TVector3<T, P>& lhs, const TVector3<T, P>& rhs) { return TVector3::Dot(lhs, rhs); }

    template <class T, class P>
    inline TVector3<T, P> operator^(const TVector3<T, P>& lhs, const TVector3<T, P>& rhs) { return TVector3::Cross(lhs, rhs); }

    template <class T, class P>
    inline TVector3<T, P> operator+(const TVector3<T, P>& vec) noexcept { return vec; }

    template <class T, class P>
    inline TVector3<T, P> operator-(const TVector3<T, P>& vec) noexcept { return vec * -1.0f; }

    using Vector3 = TVector3<float, glm::vec3>;
    using IntVector3 = TVector3<int32_t, glm::i32vec3>;
    using UintVector3 = TVector3<uint32_t, glm::u32vec3>;
}
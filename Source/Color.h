#pragma once

#include "Vector4.h"
#include <utility>

namespace ArenaBoss
{
    class Color final
    {
    public:
        union
        {
            Math::Vector4 value;
            struct
            {
                float r;
                float g;
                float b;
                float a;
            };
        };

    public:
        Color() noexcept : value(Math::Vector4::ZERO()) {}
        Color(const Color&) noexcept = default;
        Color(Color&&) noexcept = default;

        explicit Color(const Math::Vector4& vec) noexcept : value(vec) {}
        explicit Color(Math::Vector4&& vec) noexcept : value(std::move(vec)) {}

        inline static Color FromFloat(const Math::Vector4& vec) { return Color{ vec }; }
        inline static Color FromFloat(Math::Vector4&& vec) { return Color{ std::move(vec) }; }

        inline static Color FromFloat(float r, float g, float b, float a = 1.0f)
        {
            return FromFloat(Math::Vector4{ r, g, b, a });
        }

        inline static Color FromByte(const Math::Vector4& vec) { return Color{ vec / 255 }; }
        inline static Color FromByte(Math::Vector4&& vec) { return Color{ std::move(vec /= 255) }; }

        inline static Color FromByte(uint8_t r, uint8_t g, uint8_t b, uint8_t a = 255)
        {
            return FromByte(Math::Vector4{ static_cast<float>(r),
                static_cast<float>(g), static_cast<float>(b), static_cast<float>(a) });
        }

        inline static Color FromByte(uint32_t rgba)
        {
            return FromByte(
                static_cast<uint8_t>((rgba >> 0) & 0xFF),
                static_cast<uint8_t>((rgba >> 8) & 0xFF),
                static_cast<uint8_t>((rgba >> 16) & 0xFF),
                static_cast<uint8_t>((rgba >> 24) & 0xFF)
            );
        }

        Color& operator=(const Color&) noexcept = default;
        Color& operator=(Color&&) noexcept = default;

        constexpr operator float*() noexcept { return static_cast<float*>(value); }
        constexpr operator const float*() const noexcept { return static_cast<const float*>(value); }

        inline void Set(float inX, float inY, float inZ, float inW) noexcept
        {
            value.Set(inX, inY, inZ, inW);
        }

        inline void Set(const float* elems) noexcept
        {
            Set(elems[0], elems[1], elems[2], elems[3]);
        }

        inline float& operator[](size_t idx) noexcept { return value[idx]; }
        inline float operator[](size_t idx) const noexcept { return value[idx]; }

    private:
        friend bool operator==(const Color& lhs, const Color& rhs) noexcept;
    };

    inline bool operator==(const Color& lhs, const Color& rhs) noexcept
    {
        return lhs.value == rhs.value;
    }

    inline bool operator!=(const Color& lhs, const Color& rhs) noexcept
    {
        return !(lhs == rhs);
    }
}
#pragma once

#include "Vector4.h"
#include <utility>

class Color
{
public:
    Color() : value(Math::Vector4::ONE) {}
    Color(const Color&) = default;
    Color(Color&&) = default;

    explicit Color(const Math::Vector4& vec) : value(vec) {}
    explicit Color(Math::Vector4&& vec) : value(std::move(vec)) {}

    explicit Color(float r, float g, float b, float a = 1.0f)
        : value(r, g, b, a) {}

    explicit Color(uint8_t r, uint8_t g, uint8_t b, uint8_t a = 255)
        : value(r, g, b, a)
    {
        value /= 255.0f;
    }

    explicit Color(uint32_t rgba)
        : Color(
            static_cast<uint8_t>((rgba >>  0) & 0xFF),
            static_cast<uint8_t>((rgba >>  8) & 0xFF),
            static_cast<uint8_t>((rgba >> 16) & 0xFF),
            static_cast<uint8_t>((rgba >> 24) & 0xFF)
        ) {}

    Color& operator=(const Color&) = default;
    Color& operator=(Color&&) = default;    

    inline float GetR() const noexcept { return value.GetX(); }
    inline float GetG() const noexcept { return value.GetY(); }
    inline float GetB() const noexcept { return value.GetZ(); }
    inline float GetA() const noexcept { return value.GetW(); }

    inline void SetR(float r) noexcept { value.SetX(r); }
    inline void SetG(float g) noexcept { value.SetY(g); }
    inline void SetB(float b) noexcept { value.SetZ(b); }
    inline void SetA(float a) noexcept { value.SetW(a); }

    inline void AsPtr(float out[4]) const noexcept
    {
        DirectX::XMStoreFloat4(reinterpret_cast<DirectX::XMFLOAT4*>(out), value);
    }

    inline Math::Vector4 AsVector() const noexcept
    {
        return value;
    }

    inline float operator[](int idx) const noexcept { return value[idx]; }

private:
    friend bool operator==(const Color& lhs, const Color& rhs) noexcept;

    Math::Vector4 value;
};

inline bool operator==(const Color& lhs, const Color& rhs) noexcept
{
    return lhs.value == rhs.value;
}

inline bool operator!=(const Color& lhs, const Color& rhs) noexcept
{
    return !(lhs == rhs);
}


inline Color Max(const Color& lhs, const Color& rhs)
{
    return Color{ Math::Vector4{ DirectX::XMVectorMax(lhs.AsVector(), rhs.AsVector()) } };
}

inline Color Min(const Color& lhs, const Color& rhs)
{
    return Color{ Math::Vector4{ DirectX::XMVectorMin(lhs.AsVector(), rhs.AsVector()) } };
}

inline Color Clamp(const Color& x, const Color& min, const Color& max)
{
    return Color {
        Math::Vector4 {
            DirectX::XMVectorClamp(x.AsVector(), min.AsVector(), max.AsVector())
        }
    };
}
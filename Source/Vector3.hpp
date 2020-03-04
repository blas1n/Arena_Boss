#ifndef __VECTOR3_HPP__
#define __VECTOR3_HPP__

#pragma once

#include "Vector3.h"
#include "Vector2.h"

namespace ArenaBoss::Math
{
   template <class T, class P>
    constexpr const TVector3<T, P>& TVector3<T, P>::ONE()
    {
        constexpr static auto vec = TVector3<T, P>{ T{ 1 }, T{ 1 }, T{ 1 } };
        return vec;
    }

    template <class T, class P>
    constexpr const TVector3<T, P>& TVector3<T, P>::ZERO()
    {
        constexpr static auto vec = TVector3<T, P>{ T{ 0 }, T{ 0 }, T{ 0 } };
        return vec;
    }

    template <class T, class P>
    constexpr const TVector3<T, P>& TVector3<T, P>::UP()
    {
        constexpr static auto vec = TVector3<T, P>{ T{ 0 }, T{ 1 }, T{ 0 } };
        return vec;
    }

    template <class T, class P>
    constexpr const TVector3<T, P>& TVector3<T, P>::DOWN()
    {
        constexpr static auto vec = TVector3<T, P>{ T{ 0 }, T{ -1 }, T{ 0 } };
        return vec;
    }

    template <class T, class P>
    constexpr const TVector3<T, P>& TVector3<T, P>::RIGHT()
    {
        constexpr static auto vec = TVector3<T, P>{ T{ 1 }, T{ 0 }, T{ 0 } };
        return vec;
    }

    template <class T, class P>
    constexpr const TVector3<T, P>& TVector3<T, P>::FORWARD()
    {
        constexpr static auto vec = TVector3<T, P>{ T{ 0 }, T{ 0 }, T{ 1 } };
        return vec;
    }

    template <class T, class P>
    constexpr const TVector3<T, P>& TVector3<T, P>::BACKWARD()
    {
        constexpr static auto vec = TVector3<T, P>{ T{ 0 }, T{ 0 }, T{ -1 } };
        return vec;
    }

    template <class T, class P>
    constexpr const TVector3<T, P>& TVector3<T, P>::LEFT()
    {
        constexpr static auto vec = TVector3<T, P>{ T{ 0 }, T{ 0 }, T{ -1 } };
        return vec;
    }

    template <class T, class P>
    TVector3<T, P>::TVector3(const TVector2<T, P>& xy, float z/*= 0.0f*/) noexcept
        : value(xy.x, xy.y, z) {}

    template <class T, class P>
    TVector3<T, P>::operator TVector2<T, P>() const noexcept
    {
        return TVector3<T, P>{ x, y };
    }

    template <class T, class P>
    void TVector3<T, P>::Set(float inX, float inY, float inZ) noexcept
    {
        x = inX;
        y = inY;
        z = inZ;
    }
}

#endif
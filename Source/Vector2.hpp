#ifndef __VECTOR2_HPP__
#define __VECTOR2_HPP__

#pragma once

#include "Vector2.h"

namespace ArenaBoss::Math
{
    template <class T, class P>
    constexpr const TVector2<T, P>& TVector2<T, P>::ONE()
    {
        constexpr static auto vec = TVector2<T, P>{ T{ 1 }, T{ 1 } };
        return vec;
    }

    template <class T, class P>
    constexpr const TVector2<T, P>& TVector2<T, P>::ZERO()
    {
        constexpr static auto vec = TVector2<T, P>{ T{ 0 }, T{ 0 } };
        return vec;
    }

    template <class T, class P>
    constexpr const TVector2<T, P>& TVector2<T, P>::UP()
    {
        constexpr static auto vec = TVector2<T, P>{ T{ 0 }, T{ 1 } };
        return vec;
    }

    template <class T, class P>
    constexpr const TVector2<T, P>& TVector2<T, P>::DOWN()
    {
        constexpr static auto vec = TVector2<T, P>{ T{ 0 }, T{ -1 } };
        return vec;
    }

    template <class T, class P>
    constexpr const TVector2<T, P>& TVector2<T, P>::RIGHT()
    {
        constexpr static auto vec = TVector2<T, P>{ T{ 1 }, T{ 0 } };
        return vec;
    }

    template <class T, class P>
    constexpr const TVector2<T, P>& TVector2<T, P>::LEFT()
    {
        constexpr static auto vec = TVector2<T, P>{ T{ -1 }, T{ 0 } };
        return vec;
    }

    template <class T, class P>
    void TVector2<T, P>::Set(T inX, T inY) noexcept
    {
        x = inX;
        y = inY;
    }
}

#endif
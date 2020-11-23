#ifndef __VECTOR2_HPP__
#define __VECTOR2_HPP__

#pragma once

#include "Vector2.h"

namespace ArenaBoss::Math
{
    template <class T, class P>
    constexpr TVector2<T, P> TVector2<T, P>::ONE()
    {
        return TVector2<T, P>{ T{ 1 } };
    }

    template <class T, class P>
    constexpr TVector2<T, P> TVector2<T, P>::ZERO()
    {
        return TVector2<T, P>{ T{ 0 } };
    }

    template <class T, class P>
    constexpr TVector2<T, P> TVector2<T, P>::UP()
    {
        return TVector2<T, P>{ T{ 0 }, T{ 1 } };
    }

    template <class T, class P>
    constexpr TVector2<T, P> TVector2<T, P>::DOWN()
    {
        return TVector2<T, P>{ T{ 0 }, T{ -1 } };
    }

    template <class T, class P>
    constexpr TVector2<T, P> TVector2<T, P>::RIGHT()
    {
        return TVector2<T, P>{ T{ 1 }, T{ 0 } };
    }

    template <class T, class P>
    constexpr TVector2<T, P> TVector2<T, P>::LEFT()
    {
        return TVector2<T, P>{ T{ -1 }, T{ 0 } };
    }

    template <class T, class P>
    void TVector2<T, P>::Set(T inX, T inY) noexcept
    {
        x = inX;
        y = inY;
    }
}

#endif
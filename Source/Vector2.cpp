#include "Vector2.h"

namespace ArenaBoss::Math
{
    template <class T, class P>
    const TVector2<T, P> TVector2<T, P>::ONE = TVector2<T, P>{ T{ 1 }, T{ 1 } };

    template <class T, class P>
    const TVector2<T, P> TVector2<T, P>::ZERO = TVector2<T, P>{ T{ 0 }, T{ 0 } };

    template <class T, class P>
    const TVector2<T, P> TVector2<T, P>::UP = TVector2<T, P>{ T{ 0 }, T{ 1 } };

    template <class T, class P>
    const TVector2<T, P> TVector2<T, P>::DOWN = TVector2<T, P>{ T{ 0 }, T{ -1 } };

    template <class T, class P>
    const TVector2<T, P> TVector2<T, P>::LEFT = TVector2<T, P>{ T{ -1 }, T{ 0 } };

    template <class T, class P>
    const TVector2<T, P> TVector2<T, P>::RIGHT = TVector2<T, P>{ T{ 1 }, T{ 0 } };

    template <class T, class P>
    void TVector2<T, P>::Set(float inX, float inY) noexcept
    {
        x = inX;
        y = inY;
    }

    template <class T, class P>
    void TVector2<T, P>::Set(const float* elems) noexcept
    {
        x = elems[0];
        y = elems[1];
    }
}
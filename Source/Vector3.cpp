#include "Vector3.h"
#include "Vector2.h"

namespace ArenaBoss::Math
{
    template <class T, class P>
    const TVector3<T, P> TVector3<T, P>::ONE = TVector3<T, P>{ T{ 1 }, T{ 1 }, T{ 1 } };

    template <class T, class P>
    const TVector3<T, P> TVector3<T, P>::ZERO = TVector3<T, P>{ T{ 0 }, T{ 0 }, T{ 0 } };

    template <class T, class P>
    const TVector3<T, P> TVector3<T, P>::UP = TVector3<T, P>{ T{ 0 }, T{ 1 }, T{ 0 } };

    template <class T, class P>
    const TVector3<T, P> TVector3<T, P>::DOWN = TVector3<T, P>{ T{ 0 }, T{ -1 }, T{ 0 } };

    template <class T, class P>
    const TVector3<T, P> TVector3<T, P>::LEFT = TVector3<T, P>{ T{ -1 }, T{ 0 }, T{ 0 } };

    template <class T, class P>
    const TVector3<T, P> TVector3<T, P>::RIGHT = TVector3<T, P>{ T{ 1 }, T{ 0 }, T{ 0 } };

    template <class T, class P>
    const TVector3<T, P> TVector3<T, P>::FORWARD = TVector3<T, P>{ T{ 0 }, T{ 0 }, T{ 1 } };

    template <class T, class P>
    const TVector3<T, P> TVector3<T, P>::BACKWARD = TVector3<T, P>{ T{ 0 }, T{ 0 }, T{ -1 } };

    template <class T, class P>
    TVector3<T, P>::TVector3(const TVector2<T, P>& xy, float z/*= 0.0f*/) noexcept
        : value(xy.x, xy.y, z) {}

    template <class T, class P>
    TVector3<T, P>::operator TVector2<T, P>() const noexcept
    {
        return TVector2<T, P>{ x, y };
    }

    template <class T, class P>
    void TVector3<T, P>::Set(float inX, float inY, float inZ) noexcept
    {
        x = inX;
        y = inY;
        z = inZ;
    }
}
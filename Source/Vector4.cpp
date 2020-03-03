#include "Vector4.h"
#include "Vector2.h"
#include "Vector3.h"

namespace ArenaBoss::Math
{
    template <class T, class P>
    const TVector4<T, P> TVector4<T, P>::ONE = TVector4<T, P>{ T{ 1 }, T{ 1 }, T{ 1 }, T{ 1 } };

    template <class T, class P>
    const TVector4<T, P> TVector4<T, P>::ZERO = TVector4<T, P>{ T{ 0 }, T{ 0 }, T{ 0 }, T{ 0 } };

    template <class T, class P>
    TVector4<T, P>::TVector4(const TVector2<T, P>& xy, float z/*= 0.0f*/, float w/*= 0.0f*/) noexcept
        : value(xy.x, xy.y, z, w) {}

    template <class T, class P>
    TVector4<T, P>::TVector4(const TVector3<T, P>& xyz, float w/*= 0.0f*/) noexcept
        : value(xyz.x, xyz.y, xyz.z, w) {}

    template <class T, class P>
    TVector4<T, P>::operator TVector2<T, P>() const noexcept
    {
        return TVector2<T, P>{ x, y };
    }

    template <class T, class P>
    TVector4<T, P>::operator TVector3<T, P>() const noexcept
    {
        return TVector3<T, P>{ x, y, z };
    }

    template <class T, class P>
    void TVector4<T, P>::Set(float inX, float inY, float inZ, float inW) noexcept
    {
        x = inX;
        y = inY;
        z = inZ;
        w = inW;
    }
}
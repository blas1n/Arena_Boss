#pragma once

#pragma once

#include <cmath>
#include <limits>
#include <type_traits>
#include "Vector2.h"
#include "Vector3.h"
#include "Vector4.h"

namespace ArenaBoss::Math
{
	class Quaternion;
	class Rotator;

	constexpr float PI = 3.1415926535f;
	constexpr float MACHINE_EPSILON = std::numeric_limits<float>::epsilon();

	// uint 8~32, int 8~32, float, double
	template <class T>
	using IsArithmetic = std::enable_if_t<std::is_arithmetic_v<T>, T>;

	// float,double
	template <class T>
	using IsDecimal = std::enable_if_t<std::is_floating_point_v<T>, T>;

	constexpr inline float ToRadians(const float degrees) noexcept
	{
		return degrees * PI / 180.0f;
	}

	Rotator ToRadians(const Rotator& degrees) noexcept;

	constexpr inline float ToDegrees(const float radians) noexcept
	{
		return radians * 180.0f / PI;
	}

	Rotator ToDegrees(const Rotator& radians) noexcept;

	template <class T, class = IsArithmetic<T>>
	inline T Pow(const T& x, const T& y = 2.0f) noexcept
	{
		return pow(x, y);
	}

	template <class T, class = IsArithmetic<T>>
	inline T CopySign(const T& number, const T& sign) noexcept
	{
		return copysign(number, sign);
	}

	inline float Sqrt(const float value) noexcept
	{
		return sqrt(value);
	}

	inline float Fmod(const float numer, const float denom) noexcept
	{
		return fmod(numer, denom);
	}

	inline float Cos(const float angle) noexcept
	{
		return cos(angle);
	}

	inline float Sin(const float angle) noexcept
	{
		return sin(angle);
	}

	inline float Tan(const float angle) noexcept
	{
		return tan(angle);
	}

	inline float Acos(const float value) noexcept
	{
		return acos(value);
	}

	inline float Asin(const float value) noexcept
	{
		return asin(value);
	}

	inline float Atan(const float value) noexcept
	{
		return atan(value);
	}

	inline float Atan2(const float y, const float x) noexcept
	{
		return atan2(y, x);
	}

	inline float Sec(const float angle) noexcept
	{
		return 1.0f / Cos(angle);
	}

	inline float Cosec(const float angle) noexcept
	{
		return 1.0f / Sin(angle);
	}

	inline float Cot(const float angle) noexcept
	{
		return 1.0f / Tan(angle);
	}

	template <class T, typename = IsArithmetic<T>>
	constexpr inline T Abs(const T& x) noexcept
	{
		constexpr auto zero = static_cast<T>(0);
		return x > zero ? x : -x;
	}

	template <class T, class = IsArithmetic<T>>
	constexpr inline int Sign(const T& x) noexcept
	{
		constexpr auto zero = static_cast<T>(0);
		return x > zero ? 1 : x < zero ? -1 : 0;
	}

	template <class T, class = IsArithmetic<T>>
	constexpr inline T Min(const T& lhs, const T& rhs) noexcept
	{
		return lhs < rhs ? lhs : rhs;
	}

	template <class T, class = IsArithmetic<T>>
	constexpr inline T Max(const T& lhs, const T& rhs) noexcept
	{
		return lhs < rhs ? lhs : rhs;
	}

	template <class T, class = IsDecimal<T>>
	inline T Ceil(const T& value) noexcept
	{
		return ceil(value);
	}

	template <class T, class = IsDecimal<T>>
	inline T Floor(const T& value) noexcept
	{
		return floor(value);
	}

	template <class T, class = IsDecimal<T>>
	inline T Round(const T& value) noexcept
	{
		return round(value);
	}

	template <class T, class = IsDecimal<T>>
	inline T Truncate(const T& value) noexcept
	{
		return trunc(value);
	}

	constexpr inline bool NearEqual(float lhs, float rhs, float epsilon = MACHINE_EPSILON) noexcept
	{
		return Abs(lhs - rhs) <= epsilon;
	}

	inline bool NearEqual(const Vector2& lhs, const Vector2& rhs, float epsilon = MACHINE_EPSILON) noexcept
	{
		return (lhs - rhs).LengthSqrt() <= Pow(epsilon);
	}

	inline bool NearEqual(const Vector3& lhs, const Vector3& rhs, float epsilon = MACHINE_EPSILON) noexcept
	{
		return (lhs - rhs).LengthSqrt() <= Pow(epsilon);
	}

	inline bool NearEqual(const Vector4& lhs, const Vector4& rhs, float epsilon = MACHINE_EPSILON) noexcept
	{
		return (lhs - rhs).LengthSqrt() <= Pow(epsilon);
	}

	bool NearEqual(const Rotator& lhs, const Rotator& rhs, float epsilon = MACHINE_EPSILON) noexcept;
	bool NearEqual(const Quaternion& lhs, const Quaternion& rhs, float epsilon = MACHINE_EPSILON) noexcept;

	template <class T, class = IsArithmetic<T>>
	constexpr inline T Clamp(const T& value, const T& lower, const T& upper) noexcept
	{
		return Min(Max(value, lower), upper);
	}

	constexpr inline float Lerp(float a, float b, float delta) noexcept
	{
		return a + delta * (b - a);
	}

	inline Vector2 Lerp(const Vector2& a, const Vector2& b, float delta) noexcept
	{
		return a + delta * (b - a);
	}

	inline Vector3 Lerp(const Vector3& a, const Vector3& b, float delta) noexcept
	{
		return a + delta * (b - a);
	}

	inline Vector4 Lerp(const Vector4& a, const Vector4& b, float delta) noexcept
	{
		return a + delta * (b - a);
	}

	Rotator Lerp(const Rotator& a, const Rotator& b, float delta) noexcept;
	Quaternion Lerp(const Quaternion& a, const Quaternion& b, float delta) noexcept;

	Rotator Slerp(const Rotator& a, const Rotator& b, float delta) noexcept;
	Quaternion Slerp(const Quaternion& a, const Quaternion& b, float delta) noexcept;
}
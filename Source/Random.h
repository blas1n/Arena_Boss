#pragma once

#include <random>

namespace ArenaBoss::Math
{
	class Random final
	{
	public:
		Random() { SetSeed(std::random_device{}()); }
		Random(uint32_t seed) { SetSeed(seed); }

		Random(const Random&) = delete;
		Random(Random&&) noexcept = delete;
		
		~Random() = default;

		Random& operator=(const Random&) = delete;
		Random& operator=(Random&&) noexcept = delete;

		void SetSeed(uint32_t seed) noexcept
		{
			generator.seed(seed);
		}

		inline bool GetBool() noexcept
		{
			return GetIntRange(0, 1) == 1;
		}

		inline float GetFloat() noexcept
		{
			return GetRange(0.0f, 1.0f);
		}

		template <class T>
		inline T GetIntRange(T min, T max) noexcept
		{
			std::uniform_int_distribution<T> dist{ min, max };
			return dist(generator);
		}

		inline float GetRange(float min, float max) noexcept
		{
			std::uniform_real_distribution<float> dist(min, max);
			return dist(generator);
		}

		class Vector2 GetRange(const Vector2& min, const Vector2& max) noexcept;
		class Vector3 GetRange(const Vector3& min, const Vector3& max) noexcept;
		class Vector4 GetRange(const Vector4& min, const Vector4& max) noexcept;
		class Rotator GetRange(const Rotator& min, const Rotator& max) noexcept;

	private:
		std::mt19937 generator;
	};
}
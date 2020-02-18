#pragma once

#include <cassert>

namespace ArenaBoss
{
	template <class T>
	class Accessor
	{
	protected:
		inline static T& GetManager() noexcept
		{
			assert(manager != nullptr);
			return *manager;
		}

	private:
		friend class Game;
		inline static T* manager = nullptr;
	};
}
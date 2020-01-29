#pragma once

#include <cassert>

template <class T>
class Accessor final
{
protected:
	inline static T& Get() noexcept
	{
		assert(manager != nullptr);
		return *manager;
	}

private:
	friend class Game;
	inline static T* manager = nullptr;
};
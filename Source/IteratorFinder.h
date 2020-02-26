#pragma once

#include <algorithm>
#include <string>
#include <vector>

namespace ArenaBoss::IteratorFinder
{
	namespace Impl
	{
		template <class T, class U>
		decltype(auto) LowerBound(std::vector<T*>& objects, const U& value)
		{
			auto begin = objects.begin();
			auto count = objects.size();

			while (count > 0)
			{
				auto halfCount = count / 2;
				auto mid = std::next(begin, halfCount);

				if (**mid < value)
				{
					begin = mid + 1;
					count = halfCount + 1;
				}
				else
				{
					count = halfCount;
				}
			}

			return begin;
		}

		template <class T, class U, bool IsFindSame>
		decltype(auto) FindIterByName(std::vector<T*>& objects, const U& value)
		{
			const auto iter = LowerBound(objects, value);

			if constexpr (IsFindSame)
			{
				if (value != **iter)
					throw std::exception{ "No object of that name exists" };
			}
			else
			{
				if (value == **iter)
					throw std::exception{ "Object with the same name already exists" };
			}

			return iter;
		}
	}

	template <class T, class U>
	decltype(auto) FindSameIterator(std::vector<T*>& objects, const U& value)
	{
		return Impl::FindIterByName<T, U, true>(objects, value);
	}

	template <class T, class U>
	decltype(auto) FindLowerIterator(std::vector<T*>& objects, const U& value)
	{
		return Impl::FindIterByName<T, U, false>(objects, value);
	}
}
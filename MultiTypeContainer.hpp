#pragma once

#include <vector>
#include <memory>

namespace lw
{
	class MultiTypeVector
	{
	public:
		template<typename _Type>
		using Pointer = std::unique_ptr<_Type>;
	protected:
		struct Base { virtual ~Base() {} };

		template<typename _Type>
		struct Data : Base { std::vector<_Type> data; };

		size_t _max_idx{ 0 };
		std::vector<Pointer<Base>> _data;

		template <typename _Type>
		struct UID
		{
			inline static size_t idx{ 0 };
		};

		template<typename _Type>
		constexpr auto uid() { return UID<_Type>::idx; }

		template<typename _Type>
		constexpr auto
			check_size()
		{
			constexpr auto& idx = UID<_Type>::idx;
			if (idx == 0)
			{
				idx = _max_idx++;
				_data.resize(_max_idx);
				_data[idx] = std::make_unique<Data<_Type>>();
			}
		}
	public:
		MultiTypeVector() = default;

		template<typename _Type>
		constexpr auto
			push_back(_Type item)
		{
			check_size<_Type>();
			get<_Type>().push_back(item);
		}

		template<typename _Type, typename... _Args>
		constexpr decltype(auto)
			emplace_back(_Args&&... args)
		{
			check_size<_Type>();
			get<_Type>().emplace_back(std::forward<_Args>(args)...);
		}

		template<typename _Type>
		constexpr auto& get() { return dynamic_cast<Data<_Type>*>(_data[uid<_Type>()].get())->data; }
	};
}
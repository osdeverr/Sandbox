#pragma once
#include <vector>
#include <list>

namespace CX
{
	template<typename T>
	struct IEnumerable
	{
		virtual ~IEnumerable() {}
		virtual T* begin() = 0;
		virtual T* end() = 0;

		IEnumerable() {}
		IEnumerable(const std::vector<T>& vec)
		{
			struct VectorIterImpl : IEnumerable
			{
				VectorIterImpl(const std::vector<T>& vec) {
					data = vec;
				}
				T* begin() {
					return &*data.begin();
				}
				T* end() {
					return &*data.end();
				}
			private:
				std::vector<T> data;
			};
		}
	};
}
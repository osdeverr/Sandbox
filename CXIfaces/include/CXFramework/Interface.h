#pragma once

namespace CX
{
	using IfaceHandle = const void*;

	template<class I>
	class Interface
	{
	private:
		static char _HandleDummy;
	public:
		static constexpr IfaceHandle CXGetIHandle() {
			return &_HandleDummy;
		}
	};
	template<class I>
	char Interface<I>::_HandleDummy = 0;
}
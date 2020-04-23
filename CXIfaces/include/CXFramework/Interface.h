#pragma once

namespace CX
{
	using IfaceHandle = const void*;

	template<class I>
	class Interface
	{
	private:
		static char _HandleDummy;
		static constexpr IfaceHandle CXGetIHandle() {
			return &_HandleDummy;
		}

#ifdef CXCFG_HIDE_IHANDLES
		friend class Interfaceable;
#endif
	};
	template<class I>
	char Interface<I>::_HandleDummy = 0;
}
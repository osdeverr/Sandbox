#pragma once

namespace CX
{
	using IfaceHandle = const void*;

	template<class I>
	class Interface
	{
	private:
		static char _HandleDummy;
#ifdef CXCFG_HIDE_IHANDLES
		friend class Interfaceable;
	private:
#else
	public:
#endif
		static constexpr IfaceHandle CXGetIHandle() {
			return &_HandleDummy;
		}
	};
	template<class I>
	char Interface<I>::_HandleDummy = 0;
}
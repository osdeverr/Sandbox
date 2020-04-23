#pragma once
#include <unordered_map>
#include "Interface.h"

namespace CX
{
	class Interfaceable
	{
	public:
		template<class I>
		void Implements(I* iface)
		{
			auto h = I::CXGetIHandle();
			mImplementedInterfaces[h] = iface;
		}

		template<class I>
		I* GetInterface()
		{
			return (I*) mImplementedInterfaces[I::CXGetIHandle()];
		}
	private:
		std::unordered_map<IfaceHandle, void*> mImplementedInterfaces;
	};
}
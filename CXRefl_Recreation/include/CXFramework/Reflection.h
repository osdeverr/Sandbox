#pragma once
#include <string>
#include <typeinfo>
#include <type_traits>
#include <vector>

#define STRINGIFY(x) #x
#define __TPaste(a, b) a ## b
#define _TPaste(a, b) __TPaste(a, b)
#define _GenCXPName(name, line) _TPaste(_CXPropActivator_, line)
#define cxprop(name) name; CX::Property<decltype(name)> _GenCXPName(name, __LINE__) = CX::Property<decltype(name)>(*this, &name, STRINGIFY(name))

namespace CX
{
	class Reflected;
	
	struct IPropValue
	{
		virtual ~IPropValue() {};

		virtual std::string Name() = 0;
		virtual std::string Type() = 0;
		virtual void* Data() = 0;
	};

	class Reflected
	{
	public:
		Reflected() {}
		Reflected(const Reflected&) {}

		void OnPropConstruct(IPropValue* pProp)
		{
			mProps.push_back(pProp);
		}
		IPropValue& operator[](const std::string& name)
		{
			for (auto& pProp : mProps)
				if (pProp->Name() == name)
					return *pProp;
		}

		std::vector<std::reference_wrapper<IPropValue>> properties()
		{
			std::vector<std::reference_wrapper<IPropValue>> result;
			for (auto& pProp : mProps)
				result.push_back(*pProp);

			return result;
		}
	private:
		std::vector<IPropValue*> mProps;
	};

	template<typename T>
	class Property : public IPropValue
	{
	public:
		Property(Reflected& owner, T* pData, const std::string& name)
		{
			mpData = pData;
			mName = name;
			owner.OnPropConstruct(this);
		}

		std::string Name()
		{
			return mName;
		}
		std::string Type()
		{
			return typeid(*mpData).name();
		}
		void* Data()
		{
			return mpData;
		}
	private:
		T* mpData;
		std::string mName;
	};
}

struct ReflTest : CX::Reflected
{
	bool cxprop(DoPlak);
	std::string cxprop(PlakName);
	int cxprop(PlakCount);
};
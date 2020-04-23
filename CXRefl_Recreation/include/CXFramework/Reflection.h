#pragma once
#include <string>
#include <typeinfo>
#include <type_traits>
#include <vector>

#define STRINGIFY(x) #x
#define __TPaste(a, b) a ## b
#define _TPaste(a, b) __TPaste(a, b)
#define _GenCXPName(name, line) _TPaste(_CXPropActivator_, line)
#define cxprop(name) name; CX::Reflection::Property<decltype(name)> _GenCXPName(name, __LINE__) = CX::Reflection::Property<decltype(name)>(*this, &name, STRINGIFY(name))

namespace CX
{
	namespace Reflection
	{
		class Reflected;

		struct IPropValue
		{
			virtual ~IPropValue() {};

			virtual std::string Name() = 0;
			virtual std::string Type() = 0;
			virtual void* Data() = 0;
		};
		class PVAccessor
		{
		public:
			PVAccessor(IPropValue* pValue) : mpIValue(pValue) {}

			std::string name() { return mpIValue->Name(); }
			std::string type() { return mpIValue->Type(); }
			void* data() { return mpIValue->Data(); }

			template<typename T>
			bool is() { return type() == typeid(T).name(); }

			template<typename T>
			T& as() { return *(T*)data(); }
		private:
			IPropValue* mpIValue;
		};

		class Reflected
		{
		public:
			Reflected() {}
			Reflected(const Reflected&) {}

			IPropValue& operator[](const std::string& name)
			{
				for (auto& pProp : mProps)
					if (pProp->Name() == name)
						return *pProp;
			}

			std::vector<PVAccessor> properties()
			{
				std::vector<PVAccessor> result;
				for (auto& pProp : mProps)
					result.push_back(PVAccessor(pProp));

				return result;
			}
		private:
			void OnPropConstruct(IPropValue* pProp)
			{
				mProps.push_back(pProp);
			}
			std::vector<IPropValue*> mProps;

			template<typename T>
			friend class Property;
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
}
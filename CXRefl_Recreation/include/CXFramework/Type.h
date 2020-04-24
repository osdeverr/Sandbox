#pragma once
#include <string>
#include <typeinfo>
#include <type_traits>

namespace CX
{
	struct IType
	{
		virtual ~IType() {}

		// Basic Info
		virtual std::string Name() const = 0;
		virtual size_t Size() const = 0;

		// Extended Info
		virtual bool IsClass() const = 0;
		virtual bool IsDefaultConstructible() const = 0;
		virtual bool IsCopyable() const = 0;
		virtual bool IsMoveable() const = 0;

		virtual bool IsIntegral() const = 0;
		virtual bool IsFloatingPoint() const = 0;

		// Operations
		virtual void* Allocate() const = 0;
	};

	template<typename T>
	class TypeImpl : public IType
	{
	public:
		std::string Name() const {
			return typeid(T).name();
		}
		size_t Size() const {
			return sizeof(T);
		}

		bool IsClass() const {
			return std::is_class<T>::value;
		}
		bool IsDefaultConstructible() const {
			return std::is_default_constructible<T>::value;
		}
		bool IsCopyable() const {
			return std::is_copy_constructible<T>::value && std::is_copy_assignable<T>::value;
		}
		bool IsMoveable() const {
			return std::is_move_constructible<T>::value && std::is_move_assignable<T>::value;
		}
		bool IsIntegral() const {
			return std::is_integral<T>::value;
		}
		bool IsFloatingPoint() const {
			return std::is_floating_point<T>::value;
		}

		void* Allocate() const {
			return new T();
		}
	};
}
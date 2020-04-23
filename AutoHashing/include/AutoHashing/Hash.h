#pragma once

namespace AutoHashing
{
	template<class S, class H, class Hasher>
	class Hash
	{
	public:
		// Regular constructors for S and H
		Hash(const S& str) {
			mValue = Hasher::Hash(str);
		}
		Hash(const H hash) {
			mValue = hash;
		}

		// If there's a conversion from Other to S, it's gonna use it
		template<typename Other>
		Hash(Other str) {
			mValue = Hasher::Hash(S(str));
		}

		// Conversion to the hash type
		operator H() const {
			return mValue;
		}
		const H& operator*() const {
			return mValue;
		}
	private:
		H mValue;
	};
}
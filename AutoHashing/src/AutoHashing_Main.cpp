#include <cstdio>
#include <string>
#include <AutoHashing/Hash.h>

template <class S, class H>
class BasicHasher
{
public:
	static H Hash(const S& str)
	{
		H res = 0;
		int i = 1;
		for (auto& c : str)
			res += c * i++;

		return res;
	}
};

template<class S, class H>
using BasicHash = AutoHashing::Hash<S, H, BasicHasher<S, H>>;
using StringHash32 = BasicHash<std::string, uint32_t>;

void DisplayHash(StringHash32 sh)
{
	std::printf("0x%08X\n", *sh);
}

int main()
{
	DisplayHash("I'm a hashed string!");
}
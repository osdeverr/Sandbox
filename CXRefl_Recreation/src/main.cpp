#include <cstdio>
#include <CXFramework/Reflection.h>

int main() {
	ReflTest t;
	auto props = t.properties();
	for (auto& p : props)
	{
		std::printf("%s (%s)\n", p.get().Name().c_str(), p.get().Type().c_str());
	}
}
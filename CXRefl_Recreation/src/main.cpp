#include <cstdio>
#include <CXFramework/Reflection.h>

struct ReflTest : CX::Reflection::Reflected
{
	bool cxprop(DoPlak);
	std::string cxprop(PlakName);
	int cxprop(PlakCount);
};

int main() {
	ReflTest t;
	t.DoPlak = false;
	t.PlakCount = 10;
	t.PlakName = "Plak2015";

	for (auto& p : t.properties())
	{
		std::printf("%s (%s): ", p.name().c_str(), p.type().c_str());

		if (p.is<int>())
			std::printf("%d", p.as<int>());
		if (p.is<std::string>())
			std::printf("%s", p.as<std::string>().c_str());

		std::printf("\n");
	}
}
#include <cstdio>
#include <CXFramework/Reflection.h>

struct ReflTest : CX::Reflection::Reflected
{
	bool cxprop(DoPlak);
	std::string cxprop(PlakName);
	int cxprop(PlakCount);
};
struct ReflTest2 : CX::Reflection::Reflected
{
	std::string cxprop(Elaymm4Nickname);
	int cxprop(PlakCount);
	float cxprop(DiarrheaSpeed);
};

void ChangePlakCnt(CX::Reflection::Reflected& refl)
{
	if (refl["PlakCount"])
		refl["PlakCount"].as<int>() = 228;
}
void PrintProps(CX::Reflection::Reflected& refl)
{
	std::printf("Printing props:\n\n");
	for (auto& p : refl.properties())
	{
		std::printf("%s (%s): ", p.name().c_str(), p.type().c_str());

		if (p.is<int>())
			std::printf("%d", p.as<int>());
		else if (p.is<std::string>())
			std::printf("%s", p.as<std::string>().c_str());
		else
			std::printf("UNKNOWN");

		std::printf("\n");
	}
	std::printf("\n");
}

int main() {
	ReflTest t;
	t.DoPlak = false;
	t.PlakCount = 10;
	t.PlakName = "Plak2015";

	ReflTest2 t2;
	t2.Elaymm4Nickname = "elaymm4";
	t2.PlakCount = 30;
	t2.DiarrheaSpeed = 80;

	ChangePlakCnt(t);
	ChangePlakCnt(t2);

	PrintProps(t);
	PrintProps(t2);
}
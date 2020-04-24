#include <cstdio>
#include <algorithm>
#include <Windows.h>
#include <CXFramework/Reflection.h>
#include <CXFramework/IEnumerable.h>

namespace Registry
{
#ifdef UNICODE
	using _StringType = std::wstring;

	std::wstring STConvert(const std::string& src)
	{
		std::wstring tmp;
		tmp.resize(src.size());
		std::transform(src.begin(), src.end(), tmp.begin(), btowc);
		return tmp;
	}
#else
	using _StringType = std::string;
	std::string STConvert(const std::string& src)
	{
		return src;
	}
#endif

	using Dword = uint32_t;
	using Qword = uint64_t;
	using Bool = Dword;
	using String = _StringType;
	using MultiString = CX::IEnumerable<_StringType>;

	void SetRegValue_Simple(HKEY hk, String name, uint32_t type, CX::Reflection::PVAccessor& acc)
	{
		RegSetValueEx(hk, name.c_str(), 0, type, (BYTE*)acc.data(), (DWORD) acc.size());
	}

	void Write(HKEY hRootKey, const _StringType& path, CX::Reflection::Reflected& val)
	{
		HKEY hk;
		RegCreateKeyEx(hRootKey, path.c_str(), 0, nullptr, 0, KEY_ALL_ACCESS, nullptr, &hk, nullptr);
		for (auto& p : val.properties())
		{
			if (p.is<Dword>())
				SetRegValue_Simple(hk, STConvert(p.name()), REG_DWORD, p);
			else if (p.is<Qword>())
				SetRegValue_Simple(hk, STConvert(p.name()), REG_QWORD, p);
			else if (p.is<String>())
			{
				auto s = p.as<String>();
				RegSetValueEx(hk, STConvert(p.name()).c_str(), 0, REG_SZ, (BYTE*)s.c_str(), (DWORD) s.length() * sizeof(String::value_type));
			}
			else if (p.is<MultiString>())
			{
				throw std::invalid_argument("MultiStrings not implemented");
			}
			else
			{
				SetRegValue_Simple(hk, STConvert(p.name()), REG_BINARY, p);
			}
		}
		RegCloseKey(hk);
	}
}

struct RegistrySettings : CX::Reflection::Reflected
{
	Registry::Dword cxprop(PopupCount);
	Registry::Bool cxprop(EnableViruses);
	Registry::Qword cxprop(HumanPopulation);
	Registry::String cxprop(SkynetNickname);
};

int main() {
	RegistrySettings s;
	s.EnableViruses = true;
	s.HumanPopulation = 7800000000;
	s.PopupCount = 20;
	s.SkynetNickname = Registry::STConvert("Dz3n");

	Registry::Write(HKEY_CURRENT_USER, Registry::STConvert("Software\\SkynetCorporation"), s);
}
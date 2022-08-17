#include "StrategyArmy.h"

using namespace Hyena;

void CStrategyArmy::AddOrder(const std::string& UnitName, int Count)
{
	if (UnitName == "Zealot")
	{
		int a = 0;
	}
}

STestBindLua TestBindLuaStrategyArmy(&CStrategyArmy::BindLua);

void CStrategyArmy::BindLua(lua_State* L)
{
	luabridge::getGlobalNamespace(L)
		.deriveClass<CStrategyArmy, CStrategy>("CppStrategyArmy")
		.addConstructor<void (*) (void)>()
		.addProperty("LineCount", &CStrategyArmy::GetLineCount, &CStrategyArmy::SetLineCount)
		.addFunction("AddOrder", &CStrategyArmy::AddOrder)
		.endClass();
}

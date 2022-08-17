#include "StrategyComposite.h"

using namespace Hyena;

STestBindLua TestBindLuaStrategyComposite(&CStrategyComposite::BindLua);

void CStrategyComposite::BindLua(lua_State* L)
{
	luabridge::getGlobalNamespace(L)
		.beginClass<CStrategyComposite>("CppStrategyComposite")
		.endClass();
}

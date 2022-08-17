#include "Strategy.h"

using namespace Hyena;

STestBindLua TestBindLua(&CStrategy::BindLua);

void CStrategy::BindLua(lua_State* L)
{
	luabridge::getGlobalNamespace(L)
		.beginClass<CStrategy>("CppStrategy")
			.addConstructor<void (*) (void)>()
			.addFunction("Initialize", &CStrategy::Initialize)
		.endClass();
}

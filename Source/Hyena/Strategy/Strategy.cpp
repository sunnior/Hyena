#include "Strategy.h"
#include "Engine.h"

using namespace Hyena;

STestBindLua TestBindLua(&CStrategy::BindLua);

void CStrategy::BindLua(lua_State* L)
{
	luabridge::getGlobalNamespace(L)
		.beginClass<CStrategy>("CppStrategy")
			.addConstructor<void (*) (void)>()
			.addFunction("Initialize", &CStrategy::Initialize)
			.addFunction("Update", &CStrategy::Update)
		.endClass();
}

void CStrategy::Initialize(class CEngine* InEngine)
{
	Engine = InEngine;
	Engine->Strategies.push_back(this);
	OnInitialize();
}

#include "Strategy.h"
#include "Engine.h"

using namespace Hyena;

void CStrategy::Initialize(class CEngine* InEngine)
{
	Engine = InEngine;
	Engine->Strategies.push_back(this);
	OnInitialize();
}

BEGIN_REGISTERLUA(CStrategy)
	luabridge::getGlobalNamespace(L)
		.beginClass<CStrategy>("CppStrategy")
		.addConstructor<void (*) (void)>()
		.addFunction("Initialize", &CStrategy::Initialize)
		.addFunction("Update", &CStrategy::Update)
		.endClass();
End_REGISTERLUA

#include "StrategyScout.h"
#include "Engine.h"
#include "Base.h"
#include "Squad/SquadMining.h"
#include "Squad/SquadScout.h"

using namespace Hyena;

void CStrategyScout::OnInitialize()
{
	StargetLocations = BWAPI::Broodwar->getStartLocations();
	BWAPI::TilePosition MyStartLocation = BWAPI::Broodwar->self()->getStartLocation();
	for (auto It = StargetLocations.begin(); It != StargetLocations.end(); ++It)
	{
		if (*It == MyStartLocation)
		{
			StargetLocations.erase(It);
			break;
		}
	}
}

void CStrategyScout::Update()
{
	if (!Squad.get())
	{
		//todo Õâ¸ö×ø±ê
		BWAPI::Unit Unit = Engine->Bases[0]->SquadMining->RemoveCloseUnit(0, 0);
		if (Unit)
		{
			Squad = Engine->CreateSquad<CSquadScout>();
			Squad->SetUnit(Unit);
			Squad->TargetPos = BWAPI::Position(StargetLocations[0]);
		}
	}

	if (Squad->bFail)
	{
		Engine->DeleteSquad(Squad);
		Squad.reset();
	}
}

STestBindLua TestBindLuaStrategyScout(&CStrategyScout::BindLua);

void CStrategyScout::BindLua(lua_State* L)
{
	luabridge::getGlobalNamespace(L)
		.deriveClass<CStrategyScout, CStrategy>("CppStrategyScout")
		.addConstructor<void (*) (void)>()
		.endClass();
}

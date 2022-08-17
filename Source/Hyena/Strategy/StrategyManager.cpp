#include "StrategyManager.h"
#include "Engine.h"
#include "Base.h"
#include "Squad/SquadMining.h"

//todo use script
#include "Strategy/StrategyMaxMining.h"
#include "Strategy/StrategyScout.h"
#include "Strategy/StrategySupply.h"

using namespace Hyena;

void CStrategyManager::Initialize(class CEngine* InEngine)
{
	Engine = InEngine;
	luaL_dofile(Engine->L, "StrategyManagerInitialize.lua");
}

void CStrategyManager::Update()
{
	const int ret = luaL_dostring(Engine->L, "StrategyManagerLua:Update()");
	if (ret != LUA_OK)
	{
		const char* ErrString = lua_tostring(Engine->L, -1);
		int a = 0;
	}

	for (auto Strategy : Strategies)
	{
		Strategy->Update();
	}
}

void CStrategyManager::CreateStrategy(const std::string& Name)
{
	CStrategy* Strategy = nullptr;

	if (Name == "MaxMining")
	{
		Strategy = new CStrategyMaxMining;
	}
	else if (Name == "Supply")
	{
		Strategy = new CStrategySupply;
	}
	else if (Name == "Scout")
	{
		Strategy = new CStrategyScout;
	}

	if (Strategy)
	{
		Strategy->Initialize(Engine);
		Strategies.push_back(Strategy);
	}
}

void CStrategyManager::Finalize()
{

}

int CStrategyManager::GetWorkersCount()
{
	return Engine->Bases[0]->SquadMining->Units.size();
}

#include "StrategyManager.h"
#include "Engine.h"

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
	luaL_dostring(Engine->L, "StrategyManagerLua:Update()");

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

	if (Strategy)
	{
		Strategy->Initialize(Engine);
		Strategies.push_back(Strategy);
	}
}

void CStrategyManager::Finalize()
{

}

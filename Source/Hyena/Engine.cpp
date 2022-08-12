#include "Engine.h"
#include "StrategyManager.h"
#include "Base.h"
#include "LuaBridge.h"
#include "Producer/Producer.h"
#include "Producer/ProducerZergLarva.h"
#include "Producer/ProducerBuilding.h"
#include "Squad/Squad.h"

using namespace Hyena;

CEngine* Hyena::_GEngine = nullptr;

CStrategyManager* GetGlobalStrategyManger()
{
	return _GEngine->StrategyManager;
}

void CEngine::Initialize()
{
	BWAPI::Broodwar->setLocalSpeed(10);
	BWAPI::Broodwar->enableFlag(BWAPI::Flag::UserInput);
	Race = BWAPI::Broodwar->self()->getRace();

	_GEngine = this;

	L = luaL_newstate();
	luaL_openlibs(L);
	luaL_dofile(L, "EngineInitialize.lua");

	luabridge::getGlobalNamespace(L)
		.addFunction("GetGlobalStrategyManger", &GetGlobalStrategyManger);

	luabridge::getGlobalNamespace(L)
		.beginClass<CStrategyManager>("StrategyManager")
		.addFunction("CreateStrategy", &CStrategyManager::CreateStrategy);

	StrategyManager = new CStrategyManager;
	StrategyManager->Initialize(this);

	//todo find base
	std::vector<BWAPI::Unit> Workers;
	for (auto& Unit : BWAPI::Broodwar->self()->getUnits())
	{
		// Check the unit type, if it is an idle worker, then we want to send it somewhere
		if (Unit->getType().isWorker())
		{
			Workers.push_back(Unit);
		}
	}

	std::shared_ptr<CBase> Base = std::make_shared<CBase>();
	Base->Initialize(this, Workers);
	Bases.push_back(Base);

	std::shared_ptr<CProducer> Producer;
	//Create Producer For Worker
	if (BWAPI::Broodwar->self()->getRace() != BWAPI::Races::Zerg)
	{
		BWAPI::UnitType DepotType = BWAPI::Broodwar->self()->getRace().getResourceDepot();

		Producer = std::make_shared<CProducerBuilding>();
		Producer->Initialize(this);
		for (auto& Unit : BWAPI::Broodwar->self()->getUnits())
		{
			if (Unit->getType() == DepotType)
			{
				Producer->Units.push_back(Unit);
			}
		}
	}
	else
	{
		Producer = std::make_shared<CProducerZergLarva>();
		Producer->Initialize(this);
	}

	Producers.push_back(Producer);
}

void CEngine::Update()
{
	for (const BWAPI::Event& e : BWAPI::Broodwar->getEvents())
	{
		switch (e.getType())
		{
			case BWAPI::EventType::UnitCreate: 
			{ 
				break; 
			}
			case BWAPI::EventType::UnitComplete:
			{
				BWAPI::Unit Unit = e.getUnit();
				if (Unit->getPlayer() == BWAPI::Broodwar->self())
				{
					UnitsJustProduced.push_back(Unit);
				}
				break;
			}
		}
	}

	StrategyManager->Update();
	for (auto& Producer : Producers)
	{
		Producer->Update();
	}

	//todo
	for (auto& Producer : Producers)
	{
		Producer->Produce();
	}

	for (auto& Squad : Squads)
	{
		Squad->Update();
	}

	UnitsJustProduced.clear();
}

void CEngine::Finialize()
{
	lua_close(L);
	delete StrategyManager;
	StrategyManager = nullptr;
}

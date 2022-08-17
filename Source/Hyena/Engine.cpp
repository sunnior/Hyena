#include "Engine.h"
#include "Strategy/StrategyManager.h"
#include "Producer/ProducerManager.h"
#include "Base.h"
#include "Squad/Squad.h"
#include "bwem.h"

#include "Producer/Producer.h"
#include "Producer/ProducerZergLarva.h"
#include "Producer/ProducerBuilding.h"
#include "Producer/ProducerWorker.h"

using namespace Hyena;

CEngine* Hyena::_GEngine = nullptr;
int STestBindLua::Index = 0;
TLuaRegisterFunc STestBindLua::LuaRegisterFuncs[STestBindLua::MaxFuncsCount];

CStrategyManager* GetGlobalStrategyManger()
{
	return _GEngine->StrategyManager;
}

CEngine* GetGlobalEngine()
{
	return _GEngine;
}

void CEngine::Initialize()
{
	std::srand(unsigned int(std::time(nullptr)));

	BWEM::Map::Instance().Initialize();
	BWEM::Map::Instance().EnableAutomaticPathAnalysis();

	//BWEM::utils::MapPrinter::Initialize(&BWEM::Map::Instance());
	//BWEM::utils::printMap(BWEM::Map::Instance());      // will print the map into the file <StarCraftFolder>bwapi-data/map.bmp
	//BWEM::utils::pathExample(BWEM::Map::Instance());   // add to the printed map a path between two starting locations

	BWAPI::Broodwar->setLocalSpeed(5);
	BWAPI::Broodwar->enableFlag(BWAPI::Flag::UserInput);
	Race = BWAPI::Broodwar->self()->getRace();

	_GEngine = this;

	L = luaL_newstate();
	luaL_openlibs(L);

	luabridge::getGlobalNamespace(L)
		.addFunction("GetGlobalStrategyManger", &GetGlobalStrategyManger);

	luabridge::getGlobalNamespace(L)
		.addFunction("GetGlobalEngine", &GetGlobalEngine);

	luabridge::getGlobalNamespace(L)
		.beginClass<CStrategyManager>("StrategyManager")
		.addFunction("CreateStrategy", &CStrategyManager::CreateStrategy)
		.addFunction("GetWorkersCount", &CStrategyManager::GetWorkersCount)
		.endClass();

	luabridge::getGlobalNamespace(L)
		.beginClass<CEngine>("CEngine")
		.endClass();


	for (int i = 0; i < STestBindLua::Index; ++i)
	{
		STestBindLua::LuaRegisterFuncs[i](L);
	}

	const int ret = luaL_dofile(L, "Init.lua");
/*
	if (ret != LUA_OK)
	{
		const char* ErrString = lua_tostring(L, -1);
		int a = 0;
	}*/

	StrategyManager = new CStrategyManager;
	StrategyManager->Initialize(this);

	ProducerManager = new CProducerManager;
	ProducerManager->Initialize(this);

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
	Base->Initialize(this, BWAPI::Broodwar->self()->getStartLocation());
	Bases.push_back(Base);

	Base->AddWorkers(Workers);
		
	//Create Producer
	if (BWAPI::Broodwar->self()->getRace() != BWAPI::Races::Zerg)
	{
		BWAPI::UnitType DepotType = BWAPI::Broodwar->self()->getRace().getResourceDepot();

		std::shared_ptr<CProducer> ProducerDepot = ProducerManager->CreateProducer<CProducerBuilding>();
		for (auto& Unit : BWAPI::Broodwar->self()->getUnits())
		{
			if (Unit->getType() == DepotType)
			{
				ProducerDepot->Units.push_back(Unit);
			}
		}

	}
	else
	{
		std::shared_ptr<CProducer> Producer = ProducerManager->CreateProducer<CProducerZergLarva>();
	}

	std::shared_ptr<CProducerWorker> ProducerWorker = ProducerManager->CreateProducer<CProducerWorker>();
	ProducerWorker->Base = Base;
}

void CEngine::Update()
{
	for (const BWAPI::Event& e : BWAPI::Broodwar->getEvents())
	{
		switch (e.getType())
		{
			case BWAPI::EventType::UnitCreate: 
			{ 
				BWAPI::Unit Unit = e.getUnit();
				if (Unit->getType().isBuilding() && Unit->isBeingConstructed())
				{
					UnitsBeingContructed.push_back(Unit);
				}
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
			case BWAPI::EventType::UnitDestroy:
			{
				BWAPI::Unit Unit = e.getUnit();
				if (!Unit->getType().isBuilding() && Unit->getPlayer() == BWAPI::Broodwar->self())
				{
					for (auto& Squad : Squads)
					{
						if (std::find(Squad->Units.begin(), Squad->Units.end(), Unit) != Squad->Units.end())
						{
							Squad->SquadEvents.push_back(SSquadEvent{ SSquadEvent::ESquadEvent::UnitDestroyed, Unit });
							Unit = nullptr;
							break;
						}
					}
					assert(!Unit);
				}

			}
		}
	}

	const int ret = luaL_dostring(L, "Engine:Update()");
/*
	if (ret != LUA_OK)
	{
		const char* ErrString = lua_tostring(L, -1);
		int a = 0;
	}*/

	StrategyManager->Update();
	ProducerManager->Update();

	for (auto& Squad : Squads)
	{
		Squad->Update();
	}

	UnitsJustProduced.clear();
	UnitsBeingContructed.clear();
	//todfo UnitsBeingContructed
}

void CEngine::Finialize()
{
	lua_close(L);
	delete StrategyManager;
	StrategyManager = nullptr;

	delete ProducerManager;
	ProducerManager = nullptr;
}

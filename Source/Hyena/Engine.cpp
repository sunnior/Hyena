#include "Engine.h"
#include "StrategyManager.h"
#include "Base.h"
#include "LuaBridge.h"
#include "Producer/Producer.h"
#include "Producer/ProducerZergLarva.h"
#include "Producer/ProducerBuilding.h"
#include "Producer/ProducerWorker.h"
#include "Squad/Squad.h"
#include "bwem.h"

using namespace Hyena;

CEngine* Hyena::_GEngine = nullptr;

CStrategyManager* GetGlobalStrategyManger()
{
	return _GEngine->StrategyManager;
}

void CEngine::Initialize()
{
	BWEM::Map::Instance().Initialize();
	BWEM::Map::Instance().EnableAutomaticPathAnalysis();

	//BWEM::utils::MapPrinter::Initialize(&BWEM::Map::Instance());
	//BWEM::utils::printMap(BWEM::Map::Instance());      // will print the map into the file <StarCraftFolder>bwapi-data/map.bmp
	//BWEM::utils::pathExample(BWEM::Map::Instance());   // add to the printed map a path between two starting locations

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

	//Create Producer
	if (BWAPI::Broodwar->self()->getRace() != BWAPI::Races::Zerg)
	{
		BWAPI::UnitType DepotType = BWAPI::Broodwar->self()->getRace().getResourceDepot();

		std::shared_ptr<CProducer> ProducerDepot = CreateProducer<CProducerBuilding>();
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
		std::shared_ptr<CProducer> Producer = CreateProducer<CProducerZergLarva>();
	}

	std::shared_ptr<CProducerWorker> ProducerWorker = CreateProducer<CProducerWorker>();
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
		}
	}

	StrategyManager->Update();

	for (auto& Producer : Producers)
	{
		Producer->Update();
	}


	float HighestPriorty = 0;
	std::shared_ptr<CProducer> HighestPriortyProducer;

	int ReservedMinerals = 0;
	int ReservedGas = 0;
	for (auto& Producer : Producers)
	{
		ReservedMinerals += Producer->ReservedMinerals;
		ReservedGas += Producer->ReservedGas;
		if (Producer->GetPriority() > HighestPriorty)
		{
			HighestPriortyProducer = Producer;
		}
	}

	if (HighestPriortyProducer.get())
	{
		int NeedGas, NeedMinerals;
		HighestPriortyProducer->GetResourceNeeded(NeedMinerals, NeedGas);
		//todo 给一个预估时间，worker可以提前走
		if ((NeedMinerals <= (BWAPI::Broodwar->self()->minerals() - ReservedMinerals)) &&
			(NeedGas <= (BWAPI::Broodwar->self()->gas() - ReservedGas)))
		{
			HighestPriortyProducer->ReserveResources(NeedMinerals, NeedGas);
			ReservedMinerals += NeedMinerals;
			ReservedGas += NeedGas;
		}
	}

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
}

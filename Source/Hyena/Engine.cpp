#include "Engine.h"
#include "Producer/ProducerManager.h"
#include "Strategy/Strategy.h"
#include "Base.h"
#include "Squad/Squad.h"
#include "bwem.h"

using namespace Hyena;

CEngine* CEngine::_GEngine = nullptr;
int SLuaRegister::Index = 0;
TLuaRegisterFunc SLuaRegister::LuaRegisterFuncs[SLuaRegister::MaxFuncsCount];

void CEngine::Initialize()
{
	_GEngine = this;

	std::srand(unsigned int(std::time(nullptr)));

	BWEM::Map::Instance().Initialize();
	BWEM::Map::Instance().EnableAutomaticPathAnalysis();

	BWAPI::Broodwar->setLocalSpeed(15);
	BWAPI::Broodwar->enableFlag(BWAPI::Flag::UserInput);
	Race = BWAPI::Broodwar->self()->getRace();

	L = luaL_newstate();
	luaL_openlibs(L);

	for (int i = 0; i < SLuaRegister::Index; ++i)
	{
		SLuaRegister::LuaRegisterFuncs[i](L);
	}


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

	ProducerManager = new CProducerManager;
	ProducerManager->Initialize(this);

	const int ret = luaL_dofile(L, "Init.lua");
	assert(!ret || !printf("%s\n", lua_tostring(L, -1)));
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
	assert(!ret || !printf("%s\n", lua_tostring(L, -1)));

	for (auto& Strategy : Strategies)
	{
		Strategy->Update();
	}

	ProducerManager->Update();

	for (auto& Squad : Squads)
	{
		Squad->Update();
	}

	UnitsJustProduced.clear();
	UnitsBeingContructed.clear();
	//todfo UnitsBeingContructed

#if ENABLE_DEBUG
	if (bDebugProducer)
	{
		ProducerManager->DrawDebug(BWAPI::Position(10, 10));
	}
	if (bDebugMap)
	{
		DebugMap();
	}
#endif
}

void CEngine::Finialize()
{
	lua_close(L);

	delete ProducerManager;
	ProducerManager = nullptr;
}

std::string CEngine::GetRace() const
{
	switch (Race)
	{
	case BWAPI::Races::Protoss:
		return "Protoss";
	case BWAPI::Races::Terran:
		return "Terran";
	case BWAPI::Races::Zerg:
		return "Zerg";
	default:
		return "";
		break;
	}
}

#if ENABLE_DEBUG
void CEngine::ToggleDebug(std::string Option)
{
	if (Option == "producer")
	{
		bDebugProducer = !bDebugProducer;
	}
	else if (Option == "bwem")
	{
		BWEM::utils::MapPrinter::Initialize(&BWEM::Map::Instance());
		BWEM::utils::printMap(BWEM::Map::Instance());      // will print the map into the file <StarCraftFolder>bwapi-data/map.bmp
		BWEM::utils::pathExample(BWEM::Map::Instance());   // add to the printed map a path between two starting locations
	}
	else if (Option == "map")
		bDebugMap = !bDebugMap;
	}

void CEngine::DebugMap()
{

}

void CEngine::onUnitDiscover(BWAPI::Unit unit)
{
}

#endif

BEGIN_REGISTERLUA(CEngine)
	luabridge::getGlobalNamespace(L)
	.beginClass<CEngine>("CppEngine")
	.addStaticFunction("GetGlobalEngine", &CEngine::GetGlobalEngine)
	.addProperty("Race", &CEngine::GetRace)
	.endClass();
End_REGISTERLUA

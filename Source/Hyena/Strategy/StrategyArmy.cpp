#include "StrategyArmy.h"
#include "Engine.h"
#include "Producer/ProducerManager.h"

using namespace Hyena;

void CStrategyArmy::AddOrder(const std::string& UnitName, int Count, int Line)
{
	BWAPI::UnitType UnitType;
	if (UnitName == "Zealot")
	{
		UnitType = BWAPI::UnitTypes::Protoss_Zealot;
	}
	else if (UnitName == "Marine")
	{
		UnitType = BWAPI::UnitTypes::Terran_Marine;
	}

	bool bFound = false;
	for (auto& BuildQueue : BuildQueues)
	{
		if (BuildQueue.UnitType == UnitType)
		{
			BuildQueue.Count += Count;
			if (BuildQueue.Line < Line)
			{
				BuildQueue.Line = Line;
				CheckPrerequisite(BuildQueue);
				bFound = true;
				break;
			}
		}
	}

	if (!bFound)
	{
		SBuildQueue BuildQueue;
		BuildQueue.UnitType = UnitType;
		BuildQueue.Count = Count;
		BuildQueue.Line = Line;
		BuildQueues.push_back(BuildQueue);
		CheckPrerequisite(BuildQueue);
	}
}

BWAPI::TilePosition TmpGetBestPosition(BWAPI::UnitType UnitType)
{
	//todo 有的时候找到位置有人过，会导致建筑失败

	// Get a location that we want to build the building next to
	BWAPI::TilePosition desiredPos = BWAPI::Broodwar->self()->getStartLocation();

	// Ask BWAPI for a building location near the desired position for the type
	int maxBuildRange = 64;
	bool buildingOnCreep = UnitType.requiresCreep();
	BWAPI::TilePosition buildPos = BWAPI::Broodwar->getBuildLocation(UnitType, desiredPos, maxBuildRange, buildingOnCreep);
	return buildPos;
}

void CStrategyArmy::CheckPrerequisite(const SBuildQueue& BuildQueue)
{
	std::pair<BWAPI::UnitType, int> BuildType = BuildQueue.UnitType.whatBuilds();
	int LineCount = BuildQueue.Line;
	BWAPI::UnitType PreReqType = BuildType.first;
	BWAPI::UnitType Worker = Engine->Race.getWorker();
	while (true)
	{
		for (auto& Producer : Engine->ProducerManager->Producers)
		{
			if (Producer->IsType(BuildType.first) && Producer->GetLineCount() >= LineCount)
			{
				PreReqType = BWAPI::UnitTypes::None;
				break;
			}
		}

		if (PreReqType == BWAPI::UnitTypes::None)
		{
			break;
		}

		//if needs worker to build this type, we don't check producer for workers
		if (PreReqType.whatBuilds().first == Worker)
		{
			break;
		}

		PreReqType = PreReqType.whatBuilds().first;
		//for further dependency, only build one;
		LineCount = 1;
	}


	//todo 农民同时收到一个建筑物的多个单子，需要在这个地方检查一下，如果已经在build，那么获得buildorder
	if (PreReqType)
	{
		std::shared_ptr<SBuildOrder> Order = std::make_shared<SBuildOrder>();
		Order->UnitType = PreReqType;
		Order->Pos = TmpGetBestPosition(PreReqType);
		BWAPI::UnitType ProducerType = PreReqType.whatBuilds().first;

		for (auto& Producer : Engine->ProducerManager->Producers)
		{
			if (Producer->IsType(ProducerType))
			{
				Producer->AddOrder(Order);
				break;
			}
		}

	}
}

BEGIN_REGISTERLUA(CStrategyArmy)
	luabridge::getGlobalNamespace(L)
		.deriveClass<CStrategyArmy, CStrategy>("CppStrategyArmy")
		.addConstructor<void (*) (void)>()
		.addFunction("AddOrder", &CStrategyArmy::AddOrder)
		.endClass();
End_REGISTERLUA

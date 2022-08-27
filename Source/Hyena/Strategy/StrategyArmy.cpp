#include "StrategyArmy.h"
#include "Engine.h"
#include "Producer/ProducerManager.h"
#include "Base.h"

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
		BWAPI::UnitType ProducerType = PreReqType.whatBuilds().first;

		for (auto& Producer : Engine->ProducerManager->Producers)
		{
			if (Producer->IsType(ProducerType))
			{
				std::shared_ptr<SBuildOrder> Order = std::make_shared<SBuildOrder>();
				Order->UnitType = PreReqType;
				//Order->Pos = *Tiles.begin();

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
		.addProperty("Priority", &CStrategyArmy::GetPriority, &CStrategyArmy::SetPriority)
		.addFunction("AddOrder", &CStrategyArmy::AddOrder)
		.endClass();
End_REGISTERLUA

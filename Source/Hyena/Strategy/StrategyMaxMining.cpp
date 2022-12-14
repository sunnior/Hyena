#include "StrategyMaxMining.h"
#include <BWAPI.h>
#include "Base.h"
#include "Engine.h"
#include "Producer/Producer.h"
#include "Producer/ProducerManager.h"
#include "Squad/SquadMining.h"

using namespace Hyena;

void CStrategyMaxMining::OnInitialize()
{
/*

	const BWAPI::UnitType DepotType = BWAPI::Broodwar->self()->getRace().getResourceDepot();

	BWAPI::Unit Depot;

	//todo
	// For each unit that we own
	for (auto& Unit : BWAPI::Broodwar->self()->getUnits())
	{
		// if the unit is of the correct type, and it actually has been constructed, return it
		if (Unit->getType() == DepotType && Unit->isCompleted())
		{
			Depot = Unit;
		}
	}

	int a = 0;*/
	int a = 0;
}

void CStrategyMaxMining::Update()
{
	auto TmpOrders = Orders;
	Orders.clear();
	bool bBlockedOrder = false;
	for (auto& Order : TmpOrders)
	{
		if (Order->OutUnit)
		{
			Engine->Bases[0]->SquadMining->AddUnit(Order->OutUnit);
			Order.reset();
		}
		else
		{
			Orders.push_back(Order);
			if (!Order->bInProgress)
			{
				bBlockedOrder = true;
			}
		}
	}

	if (!bBlockedOrder)
	{
		int NumTrainWorkers = Engine->Bases[0]->GetDesireWorkers() - Engine->Bases[0]->SquadMining->Units.size() - Orders.size();
		if (NumTrainWorkers > 0)
		{
			BWAPI::UnitType WorkerType = BWAPI::Broodwar->self()->getRace().getWorker();
			std::pair<BWAPI::UnitType, int> BuildType = WorkerType.whatBuilds();
			for (auto& Producer : Engine->ProducerManager->Producers)
			{
				if (Producer->IsType(BuildType.first))
				{
					std::shared_ptr<SBuildOrder> Order = std::make_shared<SBuildOrder>();
					Order->Priority = 0.5f;
					Order->UnitType = WorkerType;
					Producer->AddOrder(Order);
					Orders.push_back(Order);
					break;
				}
			}
		}
	}
}

int CStrategyMaxMining::GetMiningWorkersCount()
{
	return Engine->Bases[0]->SquadMining->Units.size();
}

BEGIN_REGISTERLUA(CStrategyMaxMining)
	luabridge::getGlobalNamespace(L)
		.deriveClass<CStrategyMaxMining, CStrategy>("CppStrategyMaxMining")
		.addConstructor<void (*) (void)>()
		.addFunction("GetMiningWorkersCount", &CStrategyMaxMining::GetMiningWorkersCount)
		.endClass();
End_REGISTERLUA
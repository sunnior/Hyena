#include "ProducerWorker.h"
#include "Base.h"
#include "Squad/SquadMining.h"
#include "Squad/SquadBuilder.h"
#include "Engine.h"
#include <algorithm>

using namespace Hyena;

bool CProducerWorker::CanProduce(BWAPI::UnitType UnitType)
{
	return UnitType == Engine->Race.getSupplyProvider();
}

void CProducerWorker::Update()
{
	if (PendingOrders.size())
	{
		BWAPI::UnitType UnitType = PendingOrders[0]->UnitType;
		if (UnitType.gasPrice() <= (ReservedGas - SquadUsingGas) && UnitType.mineralPrice() <= (ReservedMinerals - SquadUsingMinerals))
		{
			BWAPI::Unit Worker = Base->SquadMining->RemoveCloseUnit(PendingOrders[0]->Pos.x, PendingOrders[0]->Pos.y);
			if (Worker)
			{
				std::shared_ptr<CSquadBuilder> Squad = Engine->CreateSquad<CSquadBuilder>();
				Squad->AddUnit(Worker);
				Squad->AddOrder(PendingOrders[0]);
				Squads.push_back(Squad);

				ProducingOrders.push_back(PendingOrders[0]);
				PendingOrders.erase(PendingOrders.begin());
			}
		}
	}

	for (auto& Squad : Squads)
	{
		if (Squad->Order->OutUnit)
		{
			if (!Squad->bConsumedResource)
			{
				ConsumeResources(Squad->Order->UnitType.mineralPrice(), Squad->Order->UnitType.gasPrice());
			}
		}
	}

	for (auto It = Squads.begin(); It != Squads.end(); ++It)
	{
		//todo 如果是被损坏呢？
		//todo 其他种族
		if ((*It)->Order->OutUnit && !(*It)->Order->OutUnit->isBeingConstructed())
		{
			Base->SquadMining->AddUnit((*It)->Unit);
			Engine->DeleteSquad(*It);
			Squads.erase(It);
			break;
		}

	}
}

float CProducerWorker::GetPriority()
{
	if (!PendingOrders.size())
	{
		return 0;
	}

	if (!Base->SquadMining->Units.size())
	{
		return 0;
	}

	BWAPI::UnitType UnitType = PendingOrders[0]->UnitType;
	if (UnitType.gasPrice() <= (ReservedGas - SquadUsingGas) && UnitType.mineralPrice() <= (ReservedMinerals - SquadUsingMinerals))
	{
		return 0;
	}
	return 0.8f;
}

void CProducerWorker::GetResourceNeeded(int& OutMinerals, int& OutGas)
{
	OutMinerals = 0;
	OutGas = 0;
	if (PendingOrders.size())
	{
		BWAPI::UnitType UnitType = PendingOrders[0]->UnitType;
		OutMinerals = UnitType.mineralPrice();
		OutGas = UnitType.gasPrice();
	}
}

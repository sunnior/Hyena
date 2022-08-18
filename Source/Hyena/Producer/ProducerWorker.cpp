#include "ProducerWorker.h"
#include "Base.h"
#include "Squad/SquadMining.h"
#include "Squad/SquadBuilder.h"
#include "Engine.h"
#include <algorithm>

using namespace Hyena;

bool CProducerWorker::IsType(BWAPI::UnitType UnitType) const
{
	return UnitType.isWorker();
}

void CProducerWorker::OnUpdate()
{
	if (ReservedOrders.size())
	{
		BWAPI::Unit Worker = Base->SquadMining->RemoveCloseUnit(ReservedOrders[0]->Pos.x, ReservedOrders[0]->Pos.y);
		if (Worker)
		{
			std::shared_ptr<CSquadBuilder> Squad = Engine->CreateSquad<CSquadBuilder>();
			Squad->AddUnit(Worker);
			Squad->AddOrder(ReservedOrders[0]);
			Squads.push_back(Squad);

			ProducingOrders.push_back(ReservedOrders[0]);
			ReservedOrders.erase(ReservedOrders.begin());
		}
	}

	for (auto& Squad : Squads)
	{
		if (Squad->Order->OutUnit)
		{
			if (Squad->Order->ReservedGas || Squad->Order->ReservedMinerals)
			{
				ConsumeOrder(Squad->Order);
			}
		}
	}

	for (auto It = Squads.begin(); It != Squads.end(); ++It)
	{
		if ((*It)->bComplete)
		{
			Base->SquadMining->AddUnit((*It)->Unit);
			Engine->DeleteSquad(*It);
			Squads.erase(It);
			break;
		}

	}
}

int CProducerWorker::GetLineCount()
{
	//todo 
	return 4;
}

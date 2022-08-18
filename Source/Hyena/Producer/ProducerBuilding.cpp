#include "ProducerBuilding.h"
#include "Engine.h"

using namespace Hyena;

void CProducerBuilding::OnUpdate()
{
	if (ReservedOrders.size() > 0)
	{
		//todo not allow queue for this moment
		if (!Units[0]->isTraining() && Units[0]->train(ReservedOrders[0]->UnitType))
		{
			ReservedOrders[0]->bInProgress = true;
			ProducingOrders.push_back(ReservedOrders[0]);
			ReservedOrders.erase(ReservedOrders.begin());
		}
	}

	if (ProducingOrders.size())
	{
		std::vector<BWAPI::Unit> MyUnits;
		for (auto& Unit : Engine->UnitsJustProduced)
		{
			if (!IsMyUnit(Unit))
			{
				continue;
			}
			MyUnits.push_back(Unit);
		}

		if (MyUnits.size())
		{
			std::vector<BWAPI::Unit> NotMyUnits;
			for (auto& Unit : Engine->UnitsJustProduced)
			{
				if (IsMyUnit(Unit))
				{
					continue;
				}
				NotMyUnits.push_back(Unit);
			}
			Engine->UnitsJustProduced = NotMyUnits;

			//todo Order check
			ProducingOrders[0]->OutUnit = MyUnits[0];
			ConsumeOrder(ProducingOrders[0]);
			ProducingOrders.erase(ProducingOrders.begin());
		}
	}

}

bool CProducerBuilding::IsMyUnit(BWAPI::Unit Unit)
{
	//todo 
	if (Unit->getType().isWorker())
	{
		return true;
	}
	return false;
}

#include "ProducerBuilding.h"
#include "Engine.h"

using namespace Hyena;

bool CProducerBuilding::CanProduce(BWAPI::UnitType UnitType)
{
	return UnitType.whatBuilds().first == Units[0]->getType();
}

void CProducerBuilding::Update()
{
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
			ProducingOrders.erase(ProducingOrders.begin());
		}
	}

}

void CProducerBuilding::Produce()
{
	if (PendingOrders.size() > 0 && Units[0]->train(PendingOrders[0]->UnitType))
	{
		ProducingOrders.push_back(PendingOrders[0]);
		PendingOrders.erase(PendingOrders.begin());
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

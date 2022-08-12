#include "ProducerZergLarva.h"
#include "Engine.h"

bool Hyena::CProducerZergLarva::CanProduce(BWAPI::UnitType UnitType)
{
	//todo
	return (UnitType == BWAPI::UnitTypes::Zerg_Drone) || (UnitType == BWAPI::UnitTypes::Zerg_Overlord);
}

void Hyena::CProducerZergLarva::Produce()
{
	if (PendingOrders.size() > 0)
	{
		//todo Ê¹ÓÃbaseµÄ
		for (auto& Unit : BWAPI::Broodwar->self()->getUnits())
		{
			if (Unit->getType() == BWAPI::UnitTypes::Zerg_Larva)
			{
				if (Unit->morph(PendingOrders[0]->UnitType))
				{
					PendingOrders[0]->bInProgress = true;
					ProducingOrders.push_back(PendingOrders[0]);
					PendingOrders.erase(PendingOrders.begin());
					break;
				}
			}
		}
	}

}

void Hyena::CProducerZergLarva::Update()
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

bool Hyena::CProducerZergLarva::IsMyUnit(BWAPI::Unit Unit)
{
	BWAPI::UnitType UnitType = Unit->getType();
	//todo
	return (UnitType == BWAPI::UnitTypes::Zerg_Drone) || (UnitType == BWAPI::UnitTypes::Zerg_Overlord);
}

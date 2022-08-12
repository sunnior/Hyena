#include "ProducerZergLarva.h"
#include "Engine.h"

using namespace Hyena;

bool CProducerZergLarva::CanProduce(BWAPI::UnitType UnitType)
{
	//todo
	return (UnitType == BWAPI::UnitTypes::Zerg_Drone) || (UnitType == BWAPI::UnitTypes::Zerg_Overlord);
}

void CProducerZergLarva::Update()
{
	if (PendingOrders.size())
	{
		BWAPI::UnitType UnitType = PendingOrders[0]->UnitType;
		if (UnitType.mineralPrice() <= ReservedMinerals && UnitType.gasPrice() <= ReservedGas)
		{
			//todo Ê¹ÓÃbaseµÄ
			for (auto& Unit : BWAPI::Broodwar->self()->getUnits())
			{
				if (Unit->getType() == BWAPI::UnitTypes::Zerg_Larva)
				{
					if (Unit->morph(PendingOrders[0]->UnitType))
					{
						ConsumeResources(UnitType.mineralPrice(), UnitType.gasPrice());
						PendingOrders[0]->bInProgress = true;
						ProducingOrders.push_back(PendingOrders[0]);
						PendingOrders.erase(PendingOrders.begin());
						break;
					}
				}
			}
		}
	}


	if (ProducingOrders.size())
	{
		std::vector<BWAPI::Unit> MyUnits;
		for (auto& Unit : Engine->UnitsJustProduced)
		{
			if (IsMyUnit(Unit))
			{
				MyUnits.push_back(Unit);
			}
		}

		if (MyUnits.size())
		{

			for (auto& Unit : MyUnits)
			{
				for (auto It = ProducingOrders.begin(); It != ProducingOrders.end(); ++It)
				{

					if (Unit->getType() == (*It)->UnitType)
					{
						(*It)->OutUnit = Unit;
						ProducingOrders.erase(It);
						break;
					}

				}
			}
		}
	}
}

float CProducerZergLarva::GetPriority()
{
	if (PendingOrders.size())
	{
		BWAPI::UnitType UnitType = PendingOrders[0]->UnitType;
		if (UnitType.gasPrice() <= ReservedGas && UnitType.mineralPrice() <= ReservedMinerals)
		{
			return 0;
		}
		return 0.5f;
	}
	return 0;
}

void CProducerZergLarva::GetResourceNeeded(int& OutMinerals, int& OutGas)
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

bool CProducerZergLarva::IsMyUnit(BWAPI::Unit Unit)
{
	BWAPI::UnitType UnitType = Unit->getType();
	//todo
	return (UnitType == BWAPI::UnitTypes::Zerg_Drone) || (UnitType == BWAPI::UnitTypes::Zerg_Overlord);
}

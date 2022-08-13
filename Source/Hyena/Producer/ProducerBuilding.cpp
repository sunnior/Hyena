#include "ProducerBuilding.h"
#include "Engine.h"

using namespace Hyena;

bool CProducerBuilding::CanProduce(BWAPI::UnitType UnitType)
{
	return UnitType.whatBuilds().first == Units[0]->getType();
}

void CProducerBuilding::Update()
{
	if (PendingOrders.size() > 0)
	{
		BWAPI::UnitType UnitType = PendingOrders[0]->UnitType;
		if (UnitType.mineralPrice() <= ReservedMinerals && UnitType.gasPrice() <= ReservedGas)
		{
			//todo not allow queue for this moment
			if (!Units[0]->isTraining() && Units[0]->train(PendingOrders[0]->UnitType))
			{
				ConsumeResources(UnitType.mineralPrice(), UnitType.gasPrice());
				PendingOrders[0]->bInProgress = true;
				ProducingOrders.push_back(PendingOrders[0]);
				PendingOrders.erase(PendingOrders.begin());
			}
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

float CProducerBuilding::GetPriority()
{
	if (!PendingOrders.size())
	{
		return 0;
	}

	BWAPI::UnitType UnitType = PendingOrders[0]->UnitType;
	if (UnitType.gasPrice() <= ReservedGas && UnitType.mineralPrice() <= ReservedMinerals)
	{
		return 0;
	}
	return 0.5f;
}

void CProducerBuilding::GetResourceNeeded(int& OutMinerals, int& OutGas)
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

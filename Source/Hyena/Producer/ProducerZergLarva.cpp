#include "ProducerZergLarva.h"
#include "Engine.h"

using namespace Hyena;

bool CProducerZergLarva::IsType(BWAPI::UnitType UnitType) const
{
	return BWAPI::UnitTypes::Zerg_Larva == UnitType;
}

void CProducerZergLarva::OnUpdate()
{
	if (ReservedOrders.size())
	{
		//todo Ê¹ÓÃbaseµÄ
		for (auto& Unit : BWAPI::Broodwar->self()->getUnits())
		{
			if (Unit->getType() == BWAPI::UnitTypes::Zerg_Larva)
			{
				if (Unit->morph(ReservedOrders[0]->UnitType))
				{
					ReservedOrders[0]->bInProgress = true;
					ConsumeOrder(ReservedOrders[0]);
					ProducingOrders.push_back(ReservedOrders[0]);
					ReservedOrders.erase(ReservedOrders.begin());
					break;
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

bool CProducerZergLarva::IsMyUnit(BWAPI::Unit Unit)
{
	BWAPI::UnitType UnitType = Unit->getType();
	//todo
	return (UnitType == BWAPI::UnitTypes::Zerg_Drone) || (UnitType == BWAPI::UnitTypes::Zerg_Overlord);
}

#if ENABLE_DEBUG
void CProducerZergLarva::DrawDebug(const BWAPI::Position& Origin)
{
	BWAPI::Broodwar->drawTextScreen(Origin, "%cZergLarva:", BWAPI::Text::Enum::Green);
}
#endif
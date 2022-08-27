#include "SquadBuilder.h"
#include "Tools.h"
#include "Producer/BuildOrder.h"
#include "Producer/ProducerWorker.h"
#include "Engine.h"

using namespace Hyena;

void CSquadBuilder::AddOrder(const std::shared_ptr<struct SBuildOrder>& InOrder)
{
	Order = InOrder;
}

void CSquadBuilder::AddUnit(BWAPI::Unit InUnit)
{
	Unit = InUnit;
	Units.push_back(Unit);
}

void CSquadBuilder::OnUpdate()
{
		//todo ¾«È·ÅÐ¶Ï
	if (!bMoveTo)
	{
		if (Unit->move(BWAPI::Position(Order->Pos)))
		{
			bMoveTo = true;
		}
	}
	else if (bMoveTo && !bBuilding)
	{
		if (Unit->isIdle())
		{
			if (Unit->build(Order->UnitType, Order->Pos))
			{
				bBuilding = true;
			}
		}
	}
	else if (bBuilding)
	{
		if (!Order->OutUnit)
		{
			for (auto& Unit : Engine->UnitsBeingContructed)
			{
				if (Unit->getType() == Order->UnitType)
				{
					Order->OutUnit = Unit;
					break;
				}
			}
		}
		else
		{
			if (Unit->isIdle())
			{
				bComplete = true;
			}
		}
	}
}

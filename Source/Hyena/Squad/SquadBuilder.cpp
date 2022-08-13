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
}

void CSquadBuilder::OnUpdate()
{
	//todo ¾«È·ÅÐ¶Ï
	if (!Order->bInProgress)
	{
		if (Unit->build(Order->UnitType, Order->Pos))
		{
			Order->bInProgress = true;
		}
	}
	else
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
			if (!Order->OutUnit->isBeingConstructed())
			{
			}
		}
	}
}

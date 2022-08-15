#include "SquadScout.h"

using namespace Hyena;

void CSquadScout::OnUpdate()
{
	if (SquadEvents.size())
	{
		if (SquadEvents[0].SquadEvent == SSquadEvent::ESquadEvent::UnitDestroyed)
		{
			Unit = nullptr;
			Units.clear();
			bFail = true;
		}
	}
	if (Unit && !bMoving)
	{
		Unit->move(TargetPos);
		bMoving = true;
	}
}

void CSquadScout::SetUnit(BWAPI::Unit InUnit)
{
	Unit = InUnit;
	Units.push_back(InUnit);
}

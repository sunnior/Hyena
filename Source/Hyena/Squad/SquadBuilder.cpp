#include "SquadBuilder.h"
#include "Tools.h"
#include "Producer/BuildOrder.h"

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
	if (Unit->isIdle())
	{
		Unit->move(Order->Pos);
	}
}

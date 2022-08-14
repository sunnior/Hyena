#include "SquadScout.h"

using namespace Hyena;

void CSquadScout::OnUpdate()
{
	if (!bMoving)
	{
		Unit->move(TargetPos);
		bMoving = true;
	}
}

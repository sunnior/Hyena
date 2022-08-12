#include "SquadMining.h"
#include "Tools.h"

using namespace Hyena;

void CSquadMining::AddUnit(BWAPI::Unit Unit)
{
	Units.push_back(Unit);
}

void CSquadMining::Update()
{
	for (auto& Unit : Units)
	{
		if (!Unit->isIdle())
		{
			continue;;
		}
		// Get the closest mineral to this worker unit
		BWAPI::Unit closestMineral = Tools::GetClosestUnitTo(Unit, BWAPI::Broodwar->getMinerals());

		// If a valid mineral was found, right click it with the unit in order to start harvesting
		if (closestMineral) { Unit->rightClick(closestMineral); }
	}
}

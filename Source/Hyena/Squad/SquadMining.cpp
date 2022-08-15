#include "SquadMining.h"
#include "Tools.h"
#include "Base.h"

using namespace Hyena;

void CSquadMining::AddUnit(BWAPI::Unit Unit)
{
	Units.push_back(Unit);
}

void CSquadMining::OnUpdate()
{
	const std::vector<BWEM::Mineral*> Minerals = Base->GraphBase->Minerals();
	for (auto& Unit : Units)
	{
		if (!Unit->isIdle())
		{
			continue;;
		}


		BWAPI::Unit closestMineral = Minerals[std::rand() % Minerals.size()]->Unit();

		// If a valid mineral was found, right click it with the unit in order to start harvesting
		if (closestMineral) { Unit->rightClick(closestMineral); }
	}
}

BWAPI::Unit CSquadMining::RemoveCloseUnit(int x, int y)
{
	//todo 
	if (!Units.size())
	{
		return nullptr;
	}

	BWAPI::Unit Unit = Units[0];
	Units.erase(Units.begin());
	return Unit;
}

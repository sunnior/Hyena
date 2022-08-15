#include "Base.h"
#include "Squad/SquadMining.h"
#include "Engine.h"

using namespace Hyena;

void CBase::Initialize(class CEngine* InEngine, const BWAPI::TilePosition& Position)
{
	SquadMining = InEngine->CreateSquad<CSquadMining>();
	SquadMining->Base = this;
	int MinDistance = 100000;
	for (auto& Area : BWEM::Map::Instance().Areas())
	{
		for (auto& Base : Area.Bases())
		{
			BWAPI::TilePosition Location = Base.Location();
			int Distance = Location.getApproxDistance(Position);
			if (Distance < MinDistance)
			{
				GraphBase = &Base;
				MinDistance = Distance;
			}
		}
	}
}

void CBase::AddWorkers(const std::vector<BWAPI::Unit>& Workers)
{
	for (auto& Worker : Workers)
	{
		SquadMining->AddUnit(Worker);
	}
}

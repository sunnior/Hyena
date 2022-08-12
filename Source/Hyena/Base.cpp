#include "Base.h"
#include "Squad/SquadMining.h"
#include "Engine.h"

using namespace Hyena;

void CBase::Initialize(class CEngine* InEngine, std::vector<BWAPI::Unit>& Workers)
{
	SquadMining = std::make_shared<CSquadMining>();

	InEngine->Squads.push_back(SquadMining);

	for (auto& Worker : Workers)
	{
		SquadMining->AddUnit(Worker);
	}
}

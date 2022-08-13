#include "Base.h"
#include "Squad/SquadMining.h"
#include "Engine.h"

using namespace Hyena;

void CBase::Initialize(class CEngine* InEngine, std::vector<BWAPI::Unit>& Workers)
{
	SquadMining = InEngine->CreateSquad<CSquadMining>();

	for (auto& Worker : Workers)
	{
		SquadMining->AddUnit(Worker);
	}
}

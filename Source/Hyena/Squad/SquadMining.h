#pragma once
#include "Squad.h"
#include <BWAPI.h>
#include "Base.h"

namespace Hyena
{
	class CSquadMining : public CSquad
	{
	public:
		void AddUnit(BWAPI::Unit);
		BWAPI::Unit RemoveCloseUnit(int x, int y);

		void OnUpdate() override;
	};
}

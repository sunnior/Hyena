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

		void Update() override;

		std::vector<BWAPI::Unit> Units;
	};
}

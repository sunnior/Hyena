#pragma once
#include "Squad.h"
#include "Base.h"

namespace Hyena
{
	class CSquadMining : public CSquad
	{
	public:
		void AddUnit(BWAPI::Unit);
		BWAPI::Unit RemoveCloseUnit(int x, int y);

		void OnUpdate() override;

		class CBase* Base;
	};
}

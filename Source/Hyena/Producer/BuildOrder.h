#pragma once
#include <BWAPI.h>

namespace Hyena
{
	struct SBuildOrder
	{
		BWAPI::UnitType UnitType;
		BWAPI::Unit OutUnit = nullptr;
		bool bInProgress = false;
		BWAPI::TilePosition Pos;
		float Priority = 0;

		int ReservedMinerals = 0;
		int ReservedGas = 0;
	};

}


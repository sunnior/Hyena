#pragma once
#include <BWAPI.h>

namespace Hyena
{
	struct SBuildOrder
	{
		BWAPI::UnitType UnitType;
		BWAPI::Unit OutUnit = nullptr;
		bool bInProgress = false;
		BWAPI::Position Pos;
	};

}


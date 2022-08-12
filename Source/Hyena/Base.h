#pragma once
#include <memory>
#include <vector>
#include "BWAPI.h"

namespace Hyena
{
	class CBase
	{
	public:
		void Initialize(class CEngine* InEngine,  std::vector<BWAPI::Unit>& Workers);
		int GetDesireWorkers() { return 18; };

		std::shared_ptr<class CSquadMining> SquadMining;
	};
}


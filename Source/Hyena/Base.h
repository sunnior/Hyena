#pragma once
#include "Common.h"

namespace Hyena
{
	class CBase
	{
	public:
		void Initialize(class CEngine* InEngine, const BWAPI::TilePosition& Position);
		int GetDesireWorkers() { return 24; };

		void AddWorkers(const std::vector<BWAPI::Unit>& Workers);

		std::shared_ptr<class CSquadMining> SquadMining;
		const class BWEM::Base* GraphBase;
	};
}


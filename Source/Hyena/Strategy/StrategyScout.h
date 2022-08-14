#pragma once
#include "Strategy.h"

namespace Hyena
{
	class CStrategyScout : public CStrategy
	{
	public:
		void OnInitialize() override;

		void Update() override;

		BWAPI::TilePosition::list StargetLocations;
		std::shared_ptr<class CSquadScout> Squad;
	};
}

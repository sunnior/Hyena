#pragma once
#include "Strategy.h"

namespace Hyena
{
	class CStrategyScout : public CStrategy
	{
	public:
		CStrategyScout() {};

		void OnInitialize() override;

		void Update() override;

		BWAPI::TilePosition::list StargetLocations;
		std::shared_ptr<class CSquadScout> Squad;


		static void BindLua(lua_State* L);
	};
}

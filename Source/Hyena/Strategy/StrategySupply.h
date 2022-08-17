#pragma once
#include "Strategy.h"

namespace Hyena
{
	class CStrategySupply : public CStrategy
	{
	public:
		CStrategySupply() {};

		void Update() override;
		BWAPI::TilePosition GetBestPosition(BWAPI::UnitType UnitType);

		std::shared_ptr<struct SBuildOrder> Order;

		static void BindLua(lua_State* L);
	};
}

#pragma once
#include "Squad.h"
#include <BWAPI.h>
#include "Base.h"

namespace Hyena
{
	class CSquadBuilder : public CSquad
	{
	public:
		void AddUnit(BWAPI::Unit);
		void AddOrder(const std::shared_ptr<struct SBuildOrder>& Order);

		void OnUpdate() override;

		BWAPI::Unit Unit;
		std::shared_ptr<struct SBuildOrder> Order;

		//todo
		bool bConsumedResource = false;
	};
}

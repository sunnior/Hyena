#pragma once
#include "Strategy.h"
#include "Producer/BuildOrder.h"

namespace Hyena
{
	class CStrategyArmy : public CStrategy
	{
		struct SBuildQueue
		{
			BWAPI::UnitType UnitType;
			int Count = 0;;
			int Line = 0;
			std::shared_ptr<SBuildOrder> PreReq;
			std::shared_ptr<SBuildOrder> Order;
		};
	public:
		CStrategyArmy() {};

		void AddOrder(const std::string& UnitName, int Count, int Line);
		void CheckPrerequisite(const SBuildQueue& BuildQueue);


		static void BindLua(lua_State* L);

	private:
		std::vector<SBuildQueue> BuildQueues;
	};
}

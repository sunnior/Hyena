#pragma once
#include "Strategy.h"
#include "Base.h"
#include <vector>

namespace Hyena
{
	class CStrategyMaxMining : public CStrategy
	{
	public:
		CStrategyMaxMining() {};

		void OnInitialize() override;

		void Update() override;

		std::vector<std::shared_ptr<struct SBuildOrder>> Orders;

		static void BindLua(lua_State* L);
	};
}

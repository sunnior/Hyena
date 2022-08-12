#pragma once
#include "Strategy.h"

namespace Hyena
{
	class CStrategySupply : public CStrategy
	{
	public:
		void Update() override;

		std::shared_ptr<struct SBuildOrder> Order;
	};
}

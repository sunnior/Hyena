#pragma once
#include "Strategy.h"
#include "Base.h"
#include <vector>

namespace Hyena
{
	class CStrategyMaxMining : public CStrategy
	{
	public:
		void Initialize(class CEngine* Engine) override;

		void Update() override;

		std::vector<std::shared_ptr<struct SBuildOrder>> Orders;
	};
}

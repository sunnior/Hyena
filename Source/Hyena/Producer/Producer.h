#pragma once
#include <memory>
#include <vector>
#include <BWAPI.h>

namespace Hyena
{
	struct SBuildOrder
	{
		BWAPI::UnitType UnitType;
		BWAPI::Unit OutUnit = nullptr;
		bool bInProgress = false;
	};

	class CProducer
	{
	public:
		void Initialize(class CEngine* Engine);
		virtual bool CanProduce(BWAPI::UnitType UnitType) { return false; }
		void AddOrder(const std::shared_ptr<SBuildOrder>& Order);
		virtual void Update() {};
		virtual void Produce() {};

		std::vector<BWAPI::Unit> Units;
	protected:
		std::vector<std::shared_ptr<SBuildOrder>> PendingOrders;
		std::vector<std::shared_ptr<SBuildOrder>> ProducingOrders;
		class CEngine* Engine;
	};
}


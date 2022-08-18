#pragma once
#include "Common.h"
#include "BuildOrder.h"

namespace Hyena
{
	class CProducer
	{
	public:
		void Initialize(class CEngine* Engine);

		void Update();
		void AddOrder(const std::shared_ptr<SBuildOrder>& Order);
		void ReserveOrder(const std::shared_ptr<SBuildOrder>& Order, int Minerals, int Gas);
		void ConsumeOrder(const std::shared_ptr<SBuildOrder>& Order);
		std::shared_ptr<SBuildOrder> GetFirstPendingOrder() { return PendingOrders.size() ? PendingOrders[0] : std::shared_ptr<SBuildOrder>(); }

		virtual void OnUpdate() {};
		virtual bool IsType(BWAPI::UnitType UnitType) const { return false; }
		virtual int GetLineCount() { return 0; }

#if ENABLE_DEBUG
		virtual void DrawDebug(const BWAPI::Position& Origin);
#endif

	protected:			
		std::vector<std::shared_ptr<SBuildOrder>> PendingOrders;
		std::vector<std::shared_ptr<SBuildOrder>> ReservedOrders;
		std::vector<std::shared_ptr<SBuildOrder>> ProducingOrders;
		class CEngine* Engine;
	};
}


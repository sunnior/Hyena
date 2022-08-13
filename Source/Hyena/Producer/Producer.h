#pragma once
#include <memory>
#include <vector>
#include <BWAPI.h>
#include "BuildOrder.h"

namespace Hyena
{
	class CProducer
	{
	public:
		void Initialize(class CEngine* Engine);
		virtual bool CanProduce(BWAPI::UnitType UnitType) { return false; }
		void AddOrder(const std::shared_ptr<SBuildOrder>& Order);
		virtual void Update() {};
		virtual float GetPriority() { return 0; }
		virtual void GetResourceNeeded(int& OutMinerals, int& OutGas) {};
		void ReserveResources(int Minerals, int Gas) { ReservedMinerals += Minerals; ReservedGas += Gas; }

		std::vector<BWAPI::Unit> Units;

		int ReservedMinerals;
		int ReservedGas;
	protected:
		void ConsumeResources(int Minerals, int Gas);
			
		std::vector<std::shared_ptr<SBuildOrder>> PendingOrders;
		std::vector<std::shared_ptr<SBuildOrder>> ProducingOrders;
		class CEngine* Engine;
	};
}


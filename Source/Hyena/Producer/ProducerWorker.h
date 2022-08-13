#pragma once
#include "Producer.h"

namespace Hyena
{
	class CProducerWorker : public CProducer
	{
	public:
		bool CanProduce(BWAPI::UnitType UnitType) override;
		void Update() override;
		float GetPriority() override;
		void GetResourceNeeded(int& OutMinerals, int& OutGas) override;

		std::shared_ptr<class CBase> Base;
		std::vector<std::shared_ptr<class CSquadBuilder>> Squads;

	private:
		int SquadUsingMinerals = 0;
		int SquadUsingGas = 0;
	};
}


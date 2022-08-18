#pragma once
#include "Producer.h"

namespace Hyena
{
	class CProducerWorker : public CProducer
	{
	public:
		bool IsType(BWAPI::UnitType UnitType) const override;
		int GetLineCount() override;
		void OnUpdate() override;
		void SquadBeginBuild(class CSquadBuilder* Squad);
		void SquadEndBuild(class CSquadBuilder* Squad);

		std::shared_ptr<class CBase> Base;
		std::vector<std::shared_ptr<class CSquadBuilder>> Squads;

	private:
		int SquadUsingMinerals = 0;
		int SquadUsingGas = 0;
	};
}


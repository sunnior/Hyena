#pragma once
#include "Producer.h"

namespace Hyena
{
	class CProducerBuilding : public CProducer
	{
	public:
		bool IsType(BWAPI::UnitType UnitType) const override { return Units[0]->getType() == UnitType; }
		int GetLineCount() override { return Units.size(); }
		void OnUpdate() override;

		std::vector<BWAPI::Unit> Units;

	private:
		bool IsMyUnit(BWAPI::Unit Unit);
	};
}


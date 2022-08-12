#pragma once
#include "Producer.h"

namespace Hyena
{
	class CProducerBuilding : public CProducer
	{
	public:
		bool CanProduce(BWAPI::UnitType UnitType) override;
		void Update() override;
		void Produce() override;

	private:
		bool IsMyUnit(BWAPI::Unit Unit);
	};
}

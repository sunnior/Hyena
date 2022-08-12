#pragma once
#include "Producer.h"

namespace Hyena
{
	class CProducerZergLarva : public CProducer
	{
	public:
		bool CanProduce(BWAPI::UnitType UnitType);
		void Produce() override;
		void Update() override;

	private:
		bool IsMyUnit(BWAPI::Unit Unit);
	};
}


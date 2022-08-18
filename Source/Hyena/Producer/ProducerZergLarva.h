#pragma once
#include "Producer.h"

namespace Hyena
{
	class CProducerZergLarva : public CProducer
	{
	public:
		bool IsType(BWAPI::UnitType UnitType) const override;
		void OnUpdate() override;

	private:
		bool IsMyUnit(BWAPI::Unit Unit);
	};
}


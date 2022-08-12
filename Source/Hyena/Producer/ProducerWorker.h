#pragma once
#include "Producer.h"

namespace Hyena
{
	class CProducerWorker : public CProducer
	{
	public:
		bool CanProduce(BWAPI::UnitType UnitType) override;
		void Update() override;
	};
}


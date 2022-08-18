#pragma once
#include "Producer.h"

namespace Hyena
{
	class CProducerZergLarva : public CProducer
	{
	public:
		bool IsType(BWAPI::UnitType UnitType) const override;
		void OnUpdate() override;

#if ENABLE_DEBUG
		void DrawDebug(const BWAPI::Position& Origin) override;
#endif
	private:
		bool IsMyUnit(BWAPI::Unit Unit);
	};
}


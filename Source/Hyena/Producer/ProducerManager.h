#pragma once
#include "Common.h"
#include "Producer.h"

namespace Hyena
{
	class CProducerManager
	{
	public:
		void Initialize(class CEngine* InEngine);
		void Update();

		template<class T>
		std::shared_ptr<T> CreateProducer()
		{
			std::shared_ptr<T> Producer = std::make_shared<T>();
			Producer->Initialize(Engine);
			Producers.push_back(Producer);
			return Producer;
		}

		std::vector<std::shared_ptr<class CProducer>> Producers;

		class CEngine* Engine;

		void ConsumeReserved(const std::shared_ptr<SBuildOrder>& Order);

		int TotalReservedMinerals = 0;
		int TotalReservedGas = 0;
	};
}


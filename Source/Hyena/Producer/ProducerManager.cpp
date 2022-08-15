#include "ProducerManager.h"
#include "Producer.h"

using namespace Hyena;

void CProducerManager::Initialize(class CEngine* InEngine)
{
	Engine = InEngine;
}

void CProducerManager::Update()
{
	for (auto& Producer : Producers)
	{
		Producer->Update();
	}

	float HighestPriorty = 0;
	std::shared_ptr<CProducer> HighestPriortyProducer;

	int ReservedMinerals = 0;
	int ReservedGas = 0;
	for (auto& Producer : Producers)
	{
		ReservedMinerals += Producer->ReservedMinerals;
		ReservedGas += Producer->ReservedGas;
		if (Producer->GetPriority() > HighestPriorty)
		{
			HighestPriortyProducer = Producer;
		}
	}

	if (HighestPriortyProducer.get())
	{
		int NeedGas, NeedMinerals;
		HighestPriortyProducer->GetResourceNeeded(NeedMinerals, NeedGas);
		//todo 给一个预估时间，worker可以提前走
		if ((NeedMinerals <= (BWAPI::Broodwar->self()->minerals() - ReservedMinerals)) &&
			(NeedGas <= (BWAPI::Broodwar->self()->gas() - ReservedGas)))
		{
			HighestPriortyProducer->ReserveResources(NeedMinerals, NeedGas);
			ReservedMinerals += NeedMinerals;
			ReservedGas += NeedGas;
		}
	}

}

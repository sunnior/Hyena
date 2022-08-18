#include "ProducerManager.h"
#include "Producer.h"
#include "Engine.h"

#include "Producer/Producer.h"
#include "Producer/ProducerZergLarva.h"
#include "Producer/ProducerBuilding.h"
#include "Producer/ProducerWorker.h"

using namespace Hyena;

void CProducerManager::Initialize(class CEngine* InEngine)
{
	Engine = InEngine;
	
	//Create Producer
	if (Engine->Race != BWAPI::Races::Zerg)
	{
		BWAPI::UnitType DepotType = BWAPI::Broodwar->self()->getRace().getResourceDepot();

		std::shared_ptr<CProducerBuilding> ProducerDepot = CreateProducer<CProducerBuilding>();
		for (auto& Unit : BWAPI::Broodwar->self()->getUnits())
		{
			if (Unit->getType() == DepotType)
			{
				ProducerDepot->Units.push_back(Unit);
			}
		}
	}
	else
	{
		std::shared_ptr<CProducer> Producer = CreateProducer<CProducerZergLarva>();
	}

	std::shared_ptr<CProducerWorker> ProducerWorker = CreateProducer<CProducerWorker>();
	ProducerWorker->Base = Engine->Bases[0];
}

void CProducerManager::Update()
{
	for (auto& Producer : Producers)
	{
		Producer->Update();
	}

	std::shared_ptr<CProducer> HighestPriortyProducer;
	std::shared_ptr<SBuildOrder> HighestPriortyOrder;

	for (auto& Producer : Producers)
	{
		std::shared_ptr<SBuildOrder> Order = Producer->GetFirstPendingOrder();
		if (Order.get())
		{
			if (!HighestPriortyOrder.get() || Order->Priority > HighestPriortyOrder->Priority)
			{
				HighestPriortyProducer = Producer;
				HighestPriortyOrder = Order;
			}
		}
	}

	if (HighestPriortyOrder.get())
	{
		int Minerals = BWAPI::Broodwar->self()->minerals() - TotalReservedMinerals;
		int Gas = BWAPI::Broodwar->self()->gas() - TotalReservedGas;

		int PriceMinerals = HighestPriortyOrder->UnitType.mineralPrice();
		int PriceGas = HighestPriortyOrder->UnitType.gasPrice();
		//todo 给一个预估时间，worker可以提前走
		if (Minerals >= PriceMinerals && Gas >= PriceGas)
		{
			HighestPriortyProducer->ReserveOrder(HighestPriortyOrder, PriceMinerals, PriceGas);
			TotalReservedMinerals += PriceMinerals;
			TotalReservedGas += PriceGas;
		}
	}

}

void CProducerManager::ConsumeReserved(const std::shared_ptr<SBuildOrder>& Order)
{
	TotalReservedGas -= Order->ReservedGas;
	TotalReservedMinerals -= Order->ReservedMinerals;
	Order->ReservedMinerals = 0;
	Order->ReservedGas = 0;
}

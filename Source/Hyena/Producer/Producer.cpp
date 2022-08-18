#include "Producer.h"
#include "Engine.h"
#include "ProducerManager.h"

using namespace Hyena;

void CProducer::Initialize(class CEngine* InEngine)
{
	Engine = InEngine;
}

void CProducer::AddOrder(const std::shared_ptr<SBuildOrder>& Order)
{
	PendingOrders.push_back(Order);
}

void CProducer::ReserveOrder(const std::shared_ptr<SBuildOrder>& Order, int Minerals, int Gas)
{
	Order->ReservedMinerals = Minerals;
	Order->ReservedGas = Gas;
	auto It = std::find(PendingOrders.begin(), PendingOrders.end(), Order);
	ReservedOrders.push_back(*It);
	PendingOrders.erase(It);
}

void CProducer::Update()
{
	std::sort(PendingOrders.begin(), PendingOrders.end(), [](auto& L, auto& R) {
		return L->Priority > R->Priority;
	});

	OnUpdate();
}

void CProducer::ConsumeOrder(const std::shared_ptr<SBuildOrder>& Order)
{
	//todo outUnit和这个comsume应该是一起的
	Engine->ProducerManager->ConsumeReserved(Order);
}

#if ENABLE_DEBUG
void CProducer::DrawDebug(const BWAPI::Position& Origin)
{
	BWAPI::Broodwar->drawTextScreen(Origin, "%cUnknown:", BWAPI::Text::Enum::Green);
}
#endif

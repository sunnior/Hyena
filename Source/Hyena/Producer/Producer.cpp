#include "Producer.h"
#include "Engine.h"

using namespace Hyena;

void CProducer::Initialize(class CEngine* InEngine)
{
	Engine = InEngine;
}

void CProducer::AddOrder(const std::shared_ptr<SBuildOrder>& Order)
{
	PendingOrders.push_back(Order);
}

void CProducer::ConsumeResources(int Minerals, int Gas)
{
	ReservedMinerals -= Minerals;
	ReservedGas -= Gas;
}

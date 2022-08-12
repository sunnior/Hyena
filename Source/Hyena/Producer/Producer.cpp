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

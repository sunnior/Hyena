#include "StrategySupply.h"
#include "Engine.h"
#include "Producer/Producer.h"

using namespace Hyena;

void CStrategySupply::Update()
{
	if (Order.get())
	{
		if (Order->OutUnit)
		{
			Order.reset();
		}
	}
	if (!Order.get())
	{
		int a = BWAPI::Broodwar->self()->supplyTotal();
		int b = BWAPI::Broodwar->self()->supplyUsed();
		int UnusedSupply = BWAPI::Broodwar->self()->supplyTotal() - BWAPI::Broodwar->self()->supplyUsed();
		if (UnusedSupply <= 4)
		{
			Order = std::make_shared<SBuildOrder>();
			Order->UnitType = Engine->Race.getSupplyProvider();

			for (auto& Producer : Engine->Producers)
			{
				if (Producer->CanProduce(Order->UnitType))
				{
					Producer->AddOrder(Order);
					break;
				}
			}
		}
	}
}

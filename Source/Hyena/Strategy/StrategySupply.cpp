#include "StrategySupply.h"
#include "Engine.h"
#include "Producer/Producer.h"
#include "Producer/ProducerManager.h"

using namespace Hyena;

void CStrategySupply::Update()
{
	if (Order.get())
	{
		//todo 整理状态表示
		if (Order->OutUnit && !Order->OutUnit->isBeingConstructed())
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
			BWAPI::UnitType SupplyType = Engine->Race.getSupplyProvider();
			std::pair<BWAPI::UnitType, int> BuildType = SupplyType.whatBuilds();

			for (auto& Producer : Engine->ProducerManager->Producers)
			{
				if (Producer->IsType(BuildType.first))
				{
					Order = std::make_shared<SBuildOrder>();
					Order->UnitType = SupplyType;
					Order->Pos = GetBestPosition(SupplyType);
					Producer->AddOrder(Order);
					break;
				}
			}
		}
	}
}

BWAPI::TilePosition CStrategySupply::GetBestPosition(BWAPI::UnitType UnitType)
{
	//todo 有的时候找到位置有人过，会导致建筑失败
	
	// Get a location that we want to build the building next to
	BWAPI::TilePosition desiredPos = BWAPI::Broodwar->self()->getStartLocation();

	// Ask BWAPI for a building location near the desired position for the type
	int maxBuildRange = 64;
	bool buildingOnCreep = UnitType.requiresCreep();
	BWAPI::TilePosition buildPos = BWAPI::Broodwar->getBuildLocation(UnitType, desiredPos, maxBuildRange, buildingOnCreep);
	return buildPos;
}

BEGIN_REGISTERLUA(CStrategySupply)
	luabridge::getGlobalNamespace(L)
			.deriveClass<CStrategySupply, CStrategy>("CppStrategySupply")
			.addConstructor<void (*) (void)>()
			.endClass();
End_REGISTERLUA

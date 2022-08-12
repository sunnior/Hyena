#include "ProducerWorker.h"
#include "Engine.h"

using namespace Hyena;

bool CProducerWorker::CanProduce(BWAPI::UnitType UnitType)
{
	return UnitType == Engine->Race.getSupplyProvider();
}

void CProducerWorker::Update()
{
	//检查是否
	//管理一个农民
	//约定资源}
}
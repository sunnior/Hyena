#include "ProducerWorker.h"
#include "Engine.h"

using namespace Hyena;

bool CProducerWorker::CanProduce(BWAPI::UnitType UnitType)
{
	return UnitType == Engine->Race.getSupplyProvider();
}

void CProducerWorker::Update()
{
	//����Ƿ�
	//����һ��ũ��
	//Լ����Դ}
}
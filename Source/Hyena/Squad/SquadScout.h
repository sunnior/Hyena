#pragma once
#include "Squad.h"

namespace Hyena
{
	class CSquadScout : public CSquad
	{
	public:
		BWAPI::Position TargetPos;
		//todo ��λ�ҵ���ô��
		BWAPI::Unit Unit;

		//todo �������ʱ��״̬����
		bool bMoving = false;;
		void OnUpdate() override;
	};
}

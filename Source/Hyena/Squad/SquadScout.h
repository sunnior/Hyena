#pragma once
#include "Squad.h"

namespace Hyena
{
	class CSquadScout : public CSquad
	{
	public:
		void SetUnit(BWAPI::Unit Unit);
		BWAPI::Position TargetPos;

		//todo �������ʱ��״̬����
		bool bMoving = false;;
		bool bFail = false;
		void OnUpdate() override;
	private:
		BWAPI::Unit Unit;

	};
}

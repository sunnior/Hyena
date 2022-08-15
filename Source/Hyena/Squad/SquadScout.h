#pragma once
#include "Squad.h"

namespace Hyena
{
	class CSquadScout : public CSquad
	{
	public:
		void SetUnit(BWAPI::Unit Unit);
		BWAPI::Position TargetPos;

		//todo 这个是临时的状态变量
		bool bMoving = false;;
		bool bFail = false;
		void OnUpdate() override;
	private:
		BWAPI::Unit Unit;

	};
}

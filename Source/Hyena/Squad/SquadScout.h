#pragma once
#include "Squad.h"

namespace Hyena
{
	class CSquadScout : public CSquad
	{
	public:
		BWAPI::Position TargetPos;
		//todo 单位挂掉怎么办
		BWAPI::Unit Unit;

		//todo 这个是临时的状态变量
		bool bMoving = false;;
		void OnUpdate() override;
	};
}

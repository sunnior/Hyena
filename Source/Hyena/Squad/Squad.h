#pragma once
#include "Common.h"

namespace Hyena
{
	struct SSquadEvent
	{
		enum class ESquadEvent
		{
			UnitDestroyed,
		};
		ESquadEvent SquadEvent;
		BWAPI::Unit Unit;
	};

	class CSquad
	{
	public:
		virtual void Initialize(class CEngine*);

		void Update();

		virtual void OnUpdate() {};

		class CEngine* Engine;

		std::vector<BWAPI::Unit> Units;
		std::vector<SSquadEvent> SquadEvents;
	};

}


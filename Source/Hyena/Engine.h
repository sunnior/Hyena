#pragma once
#include "Common.h"

struct lua_State;

namespace Hyena
{
	class CEngine
	{
	public:
		void Initialize();
		void Finialize();

		void Update();

		class CStrategyManager* StrategyManager;
		std::vector<std::shared_ptr<class CBase>> Bases;
		std::vector<std::shared_ptr<class CProducer>> Producers;
		std::vector<std::shared_ptr<class CSquad>> Squads;

		lua_State* L;

		//todo 
		std::vector<BWAPI::Unit> UnitsJustProduced;

		BWAPI::Race Race;
	private:

	};

	extern CEngine* _GEngine;
}

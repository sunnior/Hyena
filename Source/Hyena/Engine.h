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

		template<class T>
		std::shared_ptr<T> CreateProducer()
		{
			std::shared_ptr<T> Producer = std::make_shared<T>();
			Producer->Initialize(this);
			Producers.push_back(Producer);
			return Producer;
		}

		template<class T>
		std::shared_ptr<T> CreateSquad()
		{
			std::shared_ptr<T> Squad = std::make_shared<T>();
			Squad->Initialize(this);
			Squads.push_back(Squad);
			return Squad;
		}

		void DeleteSquad(const std::shared_ptr<class CSquad>& Squad)
		{
			Squads.erase(std::find(Squads.begin(), Squads.end(), Squad));
		}

		class CStrategyManager* StrategyManager;
		std::vector<std::shared_ptr<class CBase>> Bases;
		std::vector<std::shared_ptr<class CProducer>> Producers;
		std::vector<std::shared_ptr<class CSquad>> Squads;
		lua_State* L;

		//todo 
		std::vector<BWAPI::Unit> UnitsJustProduced;
		std::vector<BWAPI::Unit> UnitsBeingContructed;

		BWAPI::Race Race;
	private:

	};

	extern CEngine* _GEngine;
}

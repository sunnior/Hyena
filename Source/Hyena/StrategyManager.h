#pragma once
#include <memory>
#include <vector>
#include <string>

namespace Hyena
{
	class CStrategyManager
	{
	public:
		void Initialize(class CEngine* InEngine);

		void Finalize();

		void Update();

		void CreateStrategy(const std::string& Name);

		//todo Lua Interface
		int GetWorkersCount();

		std::vector<class CStrategy*> Strategies;

		class CEngine* Engine;
	};
}


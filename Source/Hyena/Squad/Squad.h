#pragma once
#include <memory>

namespace Hyena
{
	class CSquad
	{
	public:
		virtual void Initialize() {};

		virtual void Update() {};
	};

	using CSquadPtr = std::shared_ptr<CSquad>;
}


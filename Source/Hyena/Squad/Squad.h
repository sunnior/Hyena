#pragma once
#include <memory>

namespace Hyena
{
	class CSquad
	{
	public:
		virtual void Initialize(class CEngine*);

		void Update();

		virtual void OnUpdate() {};

		class CEngine* Engine;
	};

}


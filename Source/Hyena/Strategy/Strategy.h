#pragma once
#include "Common.h"

namespace Hyena
{
	class CStrategy
	{
	public:
		virtual void Initialize(class CEngine* InEngine) 
		{
			Engine = InEngine;
		};

		virtual void Update() {};

	protected:
		class CEngine* Engine;
	};
}


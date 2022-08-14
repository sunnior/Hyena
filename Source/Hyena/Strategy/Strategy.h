#pragma once
#include "Common.h"

namespace Hyena
{
	class CStrategy
	{
	public:
		void Initialize(class CEngine* InEngine) 
		{
			Engine = InEngine;
			OnInitialize();
		};

		virtual void OnInitialize() {};

		virtual void Update() {};

	protected:
		class CEngine* Engine;
	};
}


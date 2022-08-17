#pragma once
#include "Common.h"

namespace Hyena
{
	class CStrategy
	{
	public:
		CStrategy() {};

		void Initialize(class CEngine* InEngine);

		virtual void OnInitialize() {};

		virtual void Update() {};

		static void BindLua(lua_State* L);

	protected:
		class CEngine* Engine;
	};
}


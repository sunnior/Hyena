#pragma once
#include "Strategy.h"

namespace Hyena
{
	class CStrategyComposite : public CStrategy
	{
	public:

		static void BindLua(lua_State* L);
	};
}

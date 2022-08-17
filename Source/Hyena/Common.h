#pragma once
#include <vector>
#include <memory>
#include <BWAPI.h>
#include <algorithm>
#include "lua.hpp"
#include <bwem.h>
#include <cstdlib>
#include "LuaBridge.h"

namespace Hyena {
	typedef void (*TLuaRegisterFunc)(lua_State*);

	struct STestBindLua
	{

		STestBindLua(TLuaRegisterFunc Func)
		{
			assert(Index < MaxFuncsCount);
			LuaRegisterFuncs[Index] = Func;
			++Index;
		}

		static const int MaxFuncsCount = 1024;
		static TLuaRegisterFunc LuaRegisterFuncs[MaxFuncsCount];
		static int Index;

	};

}

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

	struct SLuaRegister
	{

		SLuaRegister(TLuaRegisterFunc Func)
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

#define BEGIN_REGISTERLUA(Name) SLuaRegister LuaRegister_##Name([](lua_State* L) {
#define End_REGISTERLUA });

#define ENABLE_DEBUG 1

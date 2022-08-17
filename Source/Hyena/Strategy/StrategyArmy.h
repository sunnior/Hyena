#pragma once
#include "Strategy.h"

namespace Hyena
{
	class CStrategyArmy : public CStrategy
	{
	public:
		CStrategyArmy() {};

		void SetLineCount(int InLines) { LineCount = InLines; }
		int GetLineCount() const { return LineCount; }

		void AddOrder(const std::string& UnitName, int Count);

		static void BindLua(lua_State* L);

	private:
		int LineCount = 0;
	};
}

StrategyManagerLua = {}
StrategyManagerLua.Cpp = GetGlobalStrategyManger()
StrategyManagerLua.Test = false

function StrategyManagerLua:Update()
	if not self.Test then
		self.Test = true
		self.Cpp:CreateStrategy("MaxMining")
		self.Cpp:CreateStrategy("Supply")
	end
end
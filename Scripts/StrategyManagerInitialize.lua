StrategyManagerLua = {}
StrategyManagerLua.Cpp = GetGlobalStrategyManger()
StrategyManagerLua.Test = false
StrategyManagerLua.bScouting = false

function StrategyManagerLua:Update()
	if not self.Test then
		self.Test = true
		self.Cpp:CreateStrategy("MaxMining")
		self.Cpp:CreateStrategy("Supply")
	end

	if not self.bScouting then
		if self.Cpp:GetWorkersCount() > 8 then
			self.Cpp:CreateStrategy("Scout")
			self.bScouting = true
		end
	end
end
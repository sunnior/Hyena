StrategyManagerLua = {}
StrategyManagerLua.Cpp = GetGlobalStrategyManger()
StrategyManagerLua.Test = false
StrategyManagerLua.bScouting = false
StrategyManagerLua.Strategies = {}

function StrategyManagerLua:Update()
	if not self.Test then
		self.Test = true
		local StrategyMaxMining = Hyena.CStrategyMaxMining()
		StrategyMaxMining:Initialize(GetGlobalEngine())
		table.insert(self.Strategies, StrategyMaxMining)
		--self.Cpp:CreateStrategy("MaxMining")
		self.Cpp:CreateStrategy("Supply")
		self.Cpp:CreateStrategy("Army")
	end

	if not self.bScouting then
		if self.Cpp:GetWorkersCount() > 8 then
			self.Cpp:CreateStrategy("Scout")
			self.bScouting = true
		end
	end

	for i, k in ipairs(self.Strategies) do
		k:Update()
	end
end
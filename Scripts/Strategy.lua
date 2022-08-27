require "class"

CStrategy = class()

function CStrategy:Initialize(Engine)
	self.Engine = Engine
end

function CStrategy:Update()
end

CStrategyComposite = class(CStrategy)

function CStrategyComposite:Initialize(Engine)
	CStrategy.Initialize(self, Engine)
	self.SubStrategies = {}
end

function CStrategyComposite:CreateSubStrategy(SubStrategy)
	SubStrategy:Initialize(self.Engine)
	table.insert(self.SubStrategies, SubStrategy)
	return SubStrategy
end

function CStrategyComposite:Update()
	CStrategy.Update(self)

	for i, Sub in ipairs(self.SubStrategies) do
		Sub:Update()
	end
end

CStrategyDefaultOpening = class(CStrategyComposite)

function CStrategyDefaultOpening:Initialize(Engine)
	CStrategyComposite.Initialize(self, Engine)

	self.StrategyMaxMining = self:CreateSubStrategy(CStrategyMaxMining())
	self.StrategySupply = self:CreateSubStrategy(CStrategySupply())
	self.StrategyScout = nil
	self.StrategyArmy = nil
end

function CStrategyDefaultOpening:Update()
	CStrategyComposite.Update(self)

	if not self.StrategyScout then
		if self.StrategyMaxMining:GetMiningWorkersCount() > 8 then
			self.StrategyScout = self:CreateSubStrategy(CStrategyScout())
		end
	end

	if not self.StrategyArmy and self.StrategyMaxMining:GetMiningWorkersCount() > 8 then
		self.StrategyArmy = self:CreateSubStrategy(CStrategyArmy())
		self.StrategyArmy.Priority = 0.8
	end
end

CStrategyRoot = class(CStrategyComposite)

function CStrategyRoot:Initialize(Engine)
	CStrategyComposite.Initialize(self, Engine)

	self.StrategyOpening = self:CreateSubStrategy(CStrategyDefaultOpening())
end

CStrategyMaxMining = class(CStrategy)

function CStrategyMaxMining:Initialize(Engine)
	CStrategy.Initialize(self, Engine)
	self.Cpp = CppStrategyMaxMining()
	self.Cpp:Initialize(Engine.Cpp)
end

function CStrategyMaxMining:Update()
	CStrategy.Update(self)
end

function CStrategyMaxMining:GetMiningWorkersCount()
	return self.Cpp:GetMiningWorkersCount()
end

CStrategySupply = class(CStrategy)

function CStrategySupply:Initialize(Engine)
	CStrategy.Initialize(self, Engine)
	self.Cpp = CppStrategySupply()
	self.Cpp:Initialize(Engine.Cpp)
end

function CStrategySupply:Update()
	CStrategy.Update(self)
end

CStrategyScout = class(CStrategy)

function CStrategyScout:Initialize(Engine)
	CStrategy.Initialize(self, Engine)
	self.Cpp = CppStrategyScout()
	self.Cpp:Initialize(Engine.Cpp)
end

function CStrategyScout:Update()
	CStrategy.Update(self)
end

CStrategyArmy = class(CStrategy)

function CStrategyArmy:Initialize(Engine)
	CStrategy.Initialize(self, Engine)
	self.Cpp = CppStrategyArmy()
	self.Cpp:Initialize(Engine.Cpp)

	local Race = Engine.Cpp.Race
	if Race == "Protoss" then
		self.Cpp:AddOrder("Zealot", 8, 2)
	elseif Race == "Terran" then
		self.Cpp:AddOrder("Marine", 8, 2)
	elseif Race == "Zerg" then

	end

end
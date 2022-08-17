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
	self.StrategyScout = self:CreateSubStrategy(CStrategyScout())
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
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
	print("*********ss")
	self.SubStrategies = {}
end

function CStrategyComposite:CreateSubStrategy(SubStrategy)
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
CStrategyRoot = class(CStrategyComposite)

function CStrategyRoot:Initialize(Engine)
	CStrategyComposite.Initialize(self, Engine)

	local StrategyMaxMining = self:CreateSubStrategy(CStrategyMaxMining())

end

CStrategyMaxMining = class(CStrategy)


function CStrategyMaxMining:Update()
	CStrategy.Update(self)
end
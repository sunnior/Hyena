require "class"
require "Strategy"

CEngine = class()

function CEngine:Initialize()
	self.RootStrategy = CStrategyRoot()
	self.RootStrategy:Initialize(self)
end

function CEngine:Update()
	self.RootStrategy:Update()
end



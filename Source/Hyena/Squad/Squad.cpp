#include "Squad.h"
#include <assert.h>
#include "Engine.h"

using namespace Hyena;

void CSquad::Initialize(class CEngine* InEngine)
{
	Engine = InEngine;
}

void CSquad::Update()
{
	assert(Engine);
	OnUpdate();

	SquadEvents.clear();
}

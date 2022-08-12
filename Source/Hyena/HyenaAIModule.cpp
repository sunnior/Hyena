#include "HyenaAIModule.h"
#include "Engine/Engine.h"

void HyenaAIModule::onStart()
{
	Engine = std::make_shared<Hyena::CEngine>();
	Engine->Initialize();
}

void HyenaAIModule::onEnd(bool isWinner)
{

}

void HyenaAIModule::onFrame()
{
	Engine->Update();
}

void HyenaAIModule::onSendText(std::string text)
{

}

void HyenaAIModule::onReceiveText(BWAPI::Player player, std::string text)
{

}

void HyenaAIModule::onPlayerLeft(BWAPI::Player player)
{

}

void HyenaAIModule::onNukeDetect(BWAPI::Position target)
{

}

void HyenaAIModule::onUnitDiscover(BWAPI::Unit unit)
{

}

void HyenaAIModule::onUnitEvade(BWAPI::Unit unit)
{

}

void HyenaAIModule::onUnitShow(BWAPI::Unit unit)
{

}

void HyenaAIModule::onUnitHide(BWAPI::Unit unit)
{

}

void HyenaAIModule::onUnitCreate(BWAPI::Unit unit)
{

}

void HyenaAIModule::onUnitDestroy(BWAPI::Unit unit)
{

}

void HyenaAIModule::onUnitMorph(BWAPI::Unit unit)
{

}

void HyenaAIModule::onUnitRenegade(BWAPI::Unit unit)
{

}

void HyenaAIModule::onSaveGame(std::string gameName)
{

}

void HyenaAIModule::onUnitComplete(BWAPI::Unit unit)
{

}

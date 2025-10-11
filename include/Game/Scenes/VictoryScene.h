#pragma once
#include <Core/Scene.h>
#include <Core/Text.h>
#include <Game/Texts/Texts.h>

class VictoryScene : public Core::Scene
{
public:
	VictoryScene(Core::Game* game) : Core::Scene(game) {}
	virtual void load() override;
	virtual void start() override;
private:
	void goToNewCharacterScene();
	void goToCredits();
private:
	Core::Text* m_slainText = nullptr;
	Core::Text* m_infoText = nullptr;
};
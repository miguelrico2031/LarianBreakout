#pragma once
#include <Core/Manager.h>
#include <Core/Event.h>
#include <Game/GameConstants.h>

class LevelManager : public Core::Manager
{
public:
	LevelManager(Core::Scene* scene) : Manager(scene), m_currentLives(LEVEL::START_LIVES) {}
	void onLifeLost();
	void winLevel();
public:
	Core::Event<unsigned int> OnLivesChanged;
private:
	unsigned int m_currentLives;
};
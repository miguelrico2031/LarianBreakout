#pragma once
#include <Core/Manager.h>
#include <Core/Event.h>
#include <Game/Level/Levels.h>

class LevelManager : public Core::Manager
{
public:
	LevelManager(Core::Scene* scene, const Levels::Data& data)
		: Manager(scene), Data(data), m_currentLives(data.StartLives) {}
	void onLifeLost();
	void winLevel();
public:
	Core::Event<unsigned int> OnLivesChanged;
	const Levels::Data& Data;
private:
	unsigned int m_currentLives;
};
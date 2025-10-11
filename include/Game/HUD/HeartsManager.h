#pragma once
#include <Core/Manager.h>
#include <Core/Animator.h>
#include <SFML/Graphics.hpp>
#include <vector>


class HeartsManager : public Core::Manager
{
public:
	HeartsManager(Core::Scene* scene) : Manager(scene) {}
	virtual void start() override;
private:
	void onLivesChanged(unsigned int lives);
private:
	std::vector<Core::GameObject*> m_hearts;
	sf::Texture m_heartTex;
	Core::Animator::Key m_heartAnimKey;
};
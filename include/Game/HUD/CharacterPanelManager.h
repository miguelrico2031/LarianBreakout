#pragma once
#include <Core/Manager.h>
#include <Game/HUD/CharacterPanel.h>
#include <Game/Characters/Character.h>
#include <vector>

class CharacterPanelManager : public Core::Manager
{
public:
	CharacterPanelManager(Core::Scene* scene)
		: Manager(scene), m_panelTexture("assets/CharacterPanel.png") {}
	void spawnCharacterPanels();
private:
	std::vector<CharacterPanel*> m_characterPanels;
	sf::Texture m_panelTexture;
};
#include <Game/HUD/CharacterPanelManager.h>
#include <Game/Characters/CharactersManager.h>
#include <Game/GameConstants.h>
#include <Core/GameObject.h>
#include <Core/Scene.h>
#include <Core/Game.h>

void CharacterPanelManager::spawnCharacterPanels()
{
	const auto& party = m_scene->getManager<CharactersManager>()->getParty();

	for (int i = 0; i < party.size(); i++)
	{
		auto& panelGO = m_scene->createSpriteGameObject(m_panelTexture, HUD::Z);
		
		const auto& size = m_panelTexture.getSize();
		float widthAndPadding = HUD::PANEL_PADDING + size.x;
		float startX = HUD::PANEL_START_X + size.x * .5f;
		sf::Vector2f pos{ startX + i * widthAndPadding, HUD::PANEL_START_Y + size.y * .5f };
		panelGO.getSprite()->setPosition(pos);

		auto* panel = &panelGO.addBehavior<CharacterPanel>(*party[i]);
		m_characterPanels.push_back(panel);

	}
}

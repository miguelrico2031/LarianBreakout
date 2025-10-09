#include <Game/UI/CharacterPanelManager.h>
#include <Game/Characters/CharactersManager.h>
#include <Game/GameConstants.h>
#include <Core/GameObject.h>
#include <Core/Scene.h>
#include <Core/Game.h>

void CharacterPanelManager::spawnCharacterPanels()
{
	const auto& dimensions = m_scene->getGame()->getDimensions();
	auto& bg = m_scene->createSpriteGameObject(m_bgTexture, UI::PANEL_Z - 10);
	bg.getSprite()->setOrigin({ 0, (float)m_bgTexture.getSize().y });
	bg.getSprite()->setPosition({ 0, (float)dimensions.y });

	const auto& party = m_scene->getManager<CharactersManager>()->getParty();

	for (int i = 0; i < party.size(); i++)
	{
		auto& panelGO = m_scene->createSpriteGameObject(m_panelTexture, UI::PANEL_Z);
		
		const auto& size = m_panelTexture.getSize();
		float widthAndPadding = UI::PANEL_PADDING + size.x;
		float startX = UI::PANEL_START_X + size.x * .5f;
		sf::Vector2f pos{ startX + i * widthAndPadding, UI::PANEL_START_Y + size.y * .5f };
		panelGO.getSprite()->setPosition(pos);

		auto* panel = &panelGO.addBehavior<CharacterPanel>(*party[i]);
		m_characterPanels.push_back(panel);

	}
}

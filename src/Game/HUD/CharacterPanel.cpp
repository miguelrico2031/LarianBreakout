#include <Game/HUD/CharacterPanel.h>
#include <Core/GameObject.h>
#include <Core/Scene.h>
#include <Core/Game.h>
#include <Game/GameConstants.h>

CharacterPanel::CharacterPanel(Core::GameObject* gameObject,  Character& character)
	: Behavior(gameObject), m_character(character)
{
	m_useDotTexture.loadFromFile("assets/UseDot.png");
	m_useDotBgTexture.loadFromFile("assets/UseDotBg.png");
	m_cooldownBarTexture.loadFromFile("assets/CooldownBar.png");
	m_selectedTexture.loadFromFile("assets/CharacterPanelSelectionFrame.png");
	m_symbolTexture.loadFromFile(character.Data.HUDSymbolTexturePath);
}


void CharacterPanel::start()
{
	//subscribe to the character events
	m_character.OnAbilityUsesChanged.subscribe([this](unsigned int r) { onAbilityUsesChanged(r); });
	m_character.OnCooldownChanged.subscribe([this](unsigned int r) { onCooldownChanged(r); });
	m_character.OnCharacterSelectedChanged.subscribe([this](bool s) { onCharacterSelectionChanged(s); });

	//instantiate all the elements
	auto* scene = m_gameObject->getScene();
	int z = m_gameObject->getSpriteZ();
	const auto& position = m_gameObject->getSprite()->getPosition();

	auto& symbolGO = scene->createSpriteGameObject(m_symbolTexture, z);
	symbolGO.getSprite()->setPosition(position);


	m_selectionFrame = &scene->createSpriteGameObject(m_selectedTexture, z + 1);
	m_selectionFrame->getSprite()->setPosition(position);
	m_selectionFrame->Enabled = false;

	auto& barGO = scene->createSpriteGameObject(m_cooldownBarTexture, z);
	m_cooldownBarSprite = barGO.getSprite();
	sf::Vector2f relativePos{ HUD::PANEL_COOLDOWN_BAR_X , HUD::PANEL_COOLDOWN_BAR_Y };
	placeRelativeToPanel(*m_cooldownBarSprite, relativePos);
	
	for (int i = 0; i < m_character.Data.MaxAbilityUses; i++)
	{
		auto* dot = &scene->createSpriteGameObject(m_useDotTexture, z);
		float y = HUD::FIRST_USE_Y + i * (m_useDotTexture.getSize().y + HUD::USE_PADDING);
		sf::Vector2f relativePos{ HUD::USE_X ,y };
		placeRelativeToPanel(*dot->getSprite(), relativePos);
		m_useDots.push_back(dot);

		//dot background that lets the player easily know the max uses
		auto& dotBg = scene->createSpriteGameObject(m_useDotBgTexture, z - 1);
		placeRelativeToPanel(*dotBg.getSprite(), relativePos);
	}
}

void CharacterPanel::onAbilityUsesChanged(unsigned int remainingUses)
{
	int uses = remainingUses;
	for (size_t i = 0; i < m_useDots.size(); i++)
	{
		m_useDots[i]->Enabled = uses > 0;
		uses--;
	}
}

void CharacterPanel::onCooldownChanged(float remainingCooldown)
{
	float fraction = remainingCooldown / m_character.Data.CooldownDuration;
	m_cooldownBarSprite->setScale({ 1.f, 1.f - fraction });
}

void CharacterPanel::onCharacterSelectionChanged(bool isSelected)
{
	m_selectionFrame->Enabled = isSelected;
}

void CharacterPanel::placeRelativeToPanel(sf::Sprite& sprite, const sf::Vector2f& relativePos)
{
	sprite.setOrigin({ 0, 0 });
	const auto& panelSize = m_gameObject->getSprite()->getTexture().getSize();
	const auto& panelCenter = m_gameObject->getSprite()->getPosition();
	sf::Vector2f panelTopLeftCorner = panelCenter - 0.5f * sf::Vector2f{ (float)panelSize.x, (float)panelSize.y };
	sprite.setPosition(panelTopLeftCorner + relativePos);
}



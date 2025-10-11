#pragma once
#include <Core/Behavior.h>
#include <Game/Characters/Character.h>
#include <SFML/Graphics.hpp>
#include <vector>

class CharacterPanel : public Core::Behavior
{
public:
	CharacterPanel(Core::GameObject* gameObject, Character& character);
	virtual void start() override;

	void onAbilityUsesChanged(unsigned int remainingUses);
	void onCooldownChanged(float remainingCooldown);
	void onCharacterSelectionChanged(bool isSelected);
private:
	void placeRelativeToPanel(sf::Sprite& sprite, const sf::Vector2f& relativePos);
private:
	Character& m_character;
	sf::Texture m_useDotTexture, m_useDotBgTexture, m_cooldownBarTexture, m_selectedTexture, m_symbolTexture;
	Core::GameObject* m_selectionFrame;
	std::vector<Core::GameObject*> m_useDots;
	sf::Sprite* m_cooldownBarSprite;
};
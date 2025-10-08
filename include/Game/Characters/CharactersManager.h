#pragma once 
#include <Core/Manager.h>
#include <Game/Characters/Character.h>
#include <vector>

class ScalesManager;
class ProjectileManager;
class CharactersManager : public Core::Manager
{
public:
	CharactersManager(Core::Scene* scene) : Manager(scene) {}
	virtual void onEvent(const sf::Event* event) override;
	virtual void update(float dt) override;

	void spawnParty(const std::vector<Character::Characters>& party);
	void play();
private:
	Character* spawnCharacter(Character::Characters c);
	void changeSelected(unsigned int idx);
private:
	std::vector<Character*> m_party;
	unsigned int m_selectedIndex = 0;
	sf::Texture m_baseProjectileTexture;
	ProjectileManager* m_projectileManager;
};

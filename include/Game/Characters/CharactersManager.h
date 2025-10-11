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

	void spawnParty(const std::vector<Characters::Type>& Party);
	void selectInitialCharacter();

	const std::vector<Character*>& getParty() const { return m_party; }
	Character* getSelected() { return m_party[m_selectedIndex]; }
private:
	Character* spawnCharacter(Characters::Type c);
	void changeSelected(unsigned int idx);
private:
	std::vector<Character*> m_party;
	unsigned int m_selectedIndex = 0;
	sf::Texture m_baseProjectileTexture;
	ProjectileManager* m_projectileManager;
};

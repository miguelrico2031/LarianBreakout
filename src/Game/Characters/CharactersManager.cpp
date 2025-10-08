#include <Game/Characters/CharactersManager.h>
#include <Game/Characters/Fighter.h>
#include <Game/Characters/Wizard.h>
#include <Game/Projectile/ProjectileManager.h>
#include <Core/GameObject.h>
#include <Core/Scene.h>
#include <memory>
#include <iostream>

void CharactersManager::onEvent(const sf::Event* event)
{
	if (const auto* e = event->getIf<sf::Event::KeyPressed>())
	{
		if (e->code == sf::Keyboard::Key::Space)
		{
			changeSelected((m_selectedIndex + 1) % m_party.size());
			std::cout << "cambiado a " << m_selectedIndex << std::endl;
		}
	}
}

void CharactersManager::update(float dt)
{
}


void CharactersManager::spawnParty(const std::vector<Character::Characters>& party)
{
	m_projectileManager = m_scene->getManager<ProjectileManager>();
	for (auto c : party)
	{
		auto* character = spawnCharacter(c);
		int index = m_party.size();
		m_party.push_back(character);
		character->initialize(index);
		//TODO: UI??
	}
}

void CharactersManager::play()
{
	m_selectedIndex = 0;
	Character* c = m_party[m_selectedIndex];
	c->select(nullptr, m_projectileManager->getActiveProjectile());
}

Character* CharactersManager::spawnCharacter(Character::Characters c)
{
	Core::GameObject& gO = m_scene->createEmptyGameObject();
	Character* character = nullptr;
	switch (c)
	{
	case Character::Characters::Fighter:
		character = &gO.addBehavior<Fighter>();
		break;
	case Character::Characters::Wizard:
		character = &gO.addBehavior<Wizard>();
		break;
	}
	return character;
}

void CharactersManager::changeSelected(unsigned int idx)
{
	if (idx == m_selectedIndex)
	{
		return;
	}

	Character* oldC = m_party[m_selectedIndex];
	Character* newC = m_party[idx];
	Paddle* oldPaddle = oldC->getPaddle();
	oldC->deselect();
	newC->select(oldPaddle, m_projectileManager->getActiveProjectile());
	m_selectedIndex = idx;
}


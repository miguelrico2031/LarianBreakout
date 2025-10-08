#pragma once
#include <Core/Behavior.h>
#include <SFML/Graphics.hpp>
#include <Game/Characters/Characters.h>
#include <memory>

class Paddle;
class Projectile;
class Scale;
class ScalesManager;
class ProjectileManager;

class Character : public Core::Behavior
{
public:

public:
	Character(Core::GameObject* gameObject, const Characters::Data& data)
		: Behavior(gameObject), Data(data) {}
	virtual ~Character() = default;

	virtual void initialize(int indexInParty);
	virtual void select(const Paddle* lastPaddle, Projectile* currentProjectile);
	virtual void deselect();

	unsigned int getIndexInParty() const { return m_indexInParty; }
	Paddle* getPaddle() const { return m_paddle; }
	Projectile* getProjectile() const { return m_projectile; }
	virtual void onProjectilePaddleCollision() = 0;
	virtual void onProjectileScaleCollision(Scale* scale) = 0;
protected:
	void changeActiveProjectileToOwn();
public:
	const Characters::Data& Data;
protected:
	unsigned int m_indexInParty;
	Paddle* m_paddle;
	Projectile* m_projectile;
	std::unique_ptr<sf::Texture> m_paddleTexture;
	std::unique_ptr<sf::Texture> m_projectileTexture;
};
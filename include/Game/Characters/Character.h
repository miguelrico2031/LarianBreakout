#pragma once
#include <Core/Behavior.h>
#include <SFML/Graphics.hpp>
#include <memory>

class Paddle;
class Projectile;
class Scale;
class ScalesManager;
class ProjectileManager;

class Character : public Core::Behavior
{
public:
	enum class Characters
	{
		None = 0,
		Fighter,
		Wizard
	};
public:
	Character(Core::GameObject* gameObject, const std::filesystem::path& paddlePath, const std::filesystem::path& projPath)
		: Behavior(gameObject), m_paddleTexture(paddlePath), m_projectileTexture(projPath) {}
	virtual ~Character() = default;

	virtual void initialize(int indexInParty);
	virtual void select(const Paddle* lastPaddle, Projectile* currentProjectile);
	virtual void deselect();

	unsigned int getIndexInParty() const { return m_indexInParty; }
	Paddle* getPaddle() const { return m_paddle; }
	Projectile* getProjectile() const { return m_projectile; }

	virtual Characters getCharacter() const = 0;
	virtual void onProjectilePaddleCollision() = 0;
	virtual void onProjectileScaleCollision(Scale* scale) = 0;
protected:
	void changeActiveProjectileToOwn();
protected:
	unsigned int m_maxAbilityUses;
	float m_restoreUseTime;
	sf::Texture m_paddleTexture, m_projectileTexture;
	unsigned int m_indexInParty;
	Paddle* m_paddle;
	Projectile* m_projectile;
};
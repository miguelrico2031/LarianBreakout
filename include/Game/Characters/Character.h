#pragma once
#include <Core/Behavior.h>
#include <Core/Event.h>
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
		: Behavior(gameObject), Data(data), m_remainingUses(data.MaxAbilityUses) {}
	virtual ~Character() = default;

	virtual void initialize(int indexInParty);

	virtual void update(float dt) override;

	virtual void select(const Paddle* lastPaddle, Projectile* currentProjectile);
	virtual void deselect();

	unsigned int getIndexInParty() const { return m_indexInParty; }
	Paddle* getPaddle() const { return m_paddle; }
	Projectile* getProjectile() const { return m_projectile; }
	virtual void onProjectileCollidedWithThisPaddle(Projectile* projectile); //called on the paddle's owner
	virtual void onPaddleCollidedWithThisProjectile(Paddle* paddle, Character* owner) {}
	virtual void onScaleCollidedWithThisProjectile(Scale* scale); //called on the projectile´s owner
	void restoreAllUses();
public:
	const Characters::Data& Data;
	Core::Event<unsigned int> OnAbilityUsesChanged;
	Core::Event<float> OnCooldownChanged;
	Core::Event<bool> OnCharacterSelectedChanged;
protected:
	virtual void useAbility();
protected:
	unsigned int m_indexInParty;
	unsigned int m_remainingUses;
	float m_remainingCooldown = 0.f;
	bool m_isOnCooldown = false;
	Paddle* m_paddle;
	Projectile* m_projectile;
	std::unique_ptr<sf::Texture> m_paddleTexture;
	std::unique_ptr<sf::Texture> m_projectileTexture;
};
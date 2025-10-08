#pragma once
#include <Core/Behavior.h>
#include <Core/Event.h>
#include <SFML/Graphics.hpp>

class Projectile;
class Paddle : public Core::Behavior
{
public:
	Paddle(Core::GameObject* gameObject) : Behavior(gameObject) {}
	virtual void start() override;
	virtual void update(float dt) override;
	const sf::Vector2f& getPosition() const { return m_position; }
	void setPosition(const sf::Vector2f& p) { m_position = p; }
	void setProjectile(Projectile* pm);
public:
	Core::Event<> OnProjectileCollision;
private:
	void moveWithInput(float dt);
	void clampToBounds();
	void checkProjectileCollision();
	void waitAndEnableCollision(float dt);
private:
	sf::Vector2f m_position;
	sf::Vector2u m_worldDimensions;
	Projectile* m_projectile;
	float m_collisionDisabledTimer = 0.f;
	bool m_collisionDisabled = false;
};
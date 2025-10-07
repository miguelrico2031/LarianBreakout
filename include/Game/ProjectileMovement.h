#pragma once
#include <Core/Behavior.h>
#include <SFML/Graphics.hpp>

class ProjectileMovement : public Core::Behavior
{
public:
	ProjectileMovement(Core::GameObject* gameObject) : Behavior(gameObject) {}
	virtual void start() override;
	virtual void update(float dt) override;
	virtual void onDestroy() override;
	void onPaddleCollision(const sf::Vector2f& paddlePos, const sf::Vector2f& paddleSize);
	sf::Vector2f getPosition() const { return m_position; }
private:
	void checkCollisionWithBounds();
private:
	const float BASE_PROJECTILE_START_SPEED = 70.f;
	const sf::Angle MAX_BOUNCE_ANGLE = sf::degrees(70.f);
	sf::Vector2f m_position;
	sf::Vector2f m_velocity;
	sf::Vector2u m_worldDimensions;
};
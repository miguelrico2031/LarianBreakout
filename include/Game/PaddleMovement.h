#pragma once
#include <Core/Behavior.h>
#include <SFML/Graphics.hpp>

class ProjectileMovement;
class PaddleMovement : public Core::Behavior
{
public:
	PaddleMovement(Core::GameObject* gameObject) : Behavior(gameObject) {}
	virtual void start() override;
	virtual void update(float dt) override;
	virtual void onDestroy() override;
	sf::Vector2f getPosition() const { return m_position; }
	void setProjectileMovement(ProjectileMovement* pm);
private:
	void checkProjectileCollision();
private:
	const float PADDLE_SPEED = 100.f;
	sf::Vector2f m_position;
	sf::Vector2u m_worldDimensions;
	ProjectileMovement* m_projectileMovement;
};
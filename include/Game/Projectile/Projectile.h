#pragma once
#include <Core/Behavior.h>
#include <Core/Event.h>
#include <SFML/Graphics.hpp>

class ScalesManager;
class Scale;
class Projectile : public Core::Behavior
{
public:
	Projectile(Core::GameObject* gameObject) : Behavior(gameObject) {}
	virtual void start() override;
	virtual void update(float dt) override;
	void onPaddleCollision(const sf::Vector2f& paddlePos, const sf::Vector2f& paddleSize);
	sf::Vector2f getPosition() const { return m_position; }
	void setPosition(const sf::Vector2f& p) { m_position = p; }
	sf::Vector2f getVelocity() const { return m_velocity; }
	void setVelocity(const sf::Vector2f& v) { m_velocity = v; }
	//by default the projectile uses an AABB to check collisions agaisnt scales. this changes it to be a circle
	void enableRotation() { m_rotate = true; }
	void changeColliderToCircle(float Radius) { m_isCircle = true; m_circleRadius = Radius; }
public:
	Core::Event<Scale*> OnScaleCollision;
private:
	void rotate();
	bool checkCollisionWithScales();
	bool checkCollisionWithBounds();
private:
	const float BASE_PROJECTILE_START_SPEED = 70.f;
	const sf::Angle MAX_BOUNCE_ANGLE = sf::degrees(70.f);
	sf::Vector2f m_position;
	sf::Vector2f m_velocity;
	sf::Vector2u m_worldDimensions;
	ScalesManager* m_scalesManager;
	bool m_rotate = false;
	bool m_isCircle = false;
	float m_circleRadius;
};
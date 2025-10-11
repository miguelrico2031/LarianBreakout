#pragma once
#include <Core/Behavior.h>
#include <Core/Event.h>
#include <SFML/Graphics.hpp>
#include <functional>

class ScalesManager;
class Scale;
class Projectile : public Core::Behavior
{
public:
	enum class Mode
	{
		None = 0,
		LookForward, //rotate so it's looking towards the velocity direction, snapped 90 degrees
		Spin, //constant spinning
	};
public:
	Projectile(Core::GameObject* gameObject) : Behavior(gameObject) {}
	virtual void start() override;
	void setRandomVelocity();
	virtual void update(float dt) override;
	void onPaddleCollision(const sf::Vector2f& paddlePos);
	sf::Vector2f getPosition() const { return m_position; }
	void setPosition(const sf::Vector2f& p) { m_position = p; }
	sf::Vector2f getVelocity() const { return m_velocity; }
	void setVelocity(const sf::Vector2f& v) { m_velocity = v; }
	//by default the projectile uses an AABB to check collisions agaisnt scales. this changes it to be a circle
	void changeColliderToCircle(float radius) { m_isCircle = true; m_circleRadius = radius; }
	Mode getMode() const { return m_mode; }
	void setMode(Mode m) { m_mode = m; }
	bool getDestroysScales() const { return m_destroysScales; }
	void setDestroysScales(bool d) { m_destroysScales = d; }

public:
	Core::Event<Scale*> OnScaleCollision;
	Core::Event<> OnBottomBoundCollision;
private:
	void rotateToLookForward();
	bool checkCollisionWithScales();
	bool checkCollisionWithBounds();
	void correctVelocityDirection();
private:
	sf::Vector2f m_position;
	sf::Vector2f m_velocity;
	sf::Vector2u m_worldDimensions;
	ScalesManager* m_scalesManager;
	bool m_isCircle = false;
	bool m_destroysScales = true;
	Mode m_mode = Mode::None;
	float m_circleRadius;
};
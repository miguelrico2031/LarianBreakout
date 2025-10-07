#include <Game/ProjectileMovement.h>
#include <Game/Bounds.h>
#include <Core/GameObject.h>
#include <Core/Scene.h>
#include <Core/Game.h>
#include <Core/Random.h>
#include <algorithm>
#include <iostream>

void ProjectileMovement::start()
{
	m_worldDimensions = m_gameObject->getScene()->getGame()->getDimensions();
	m_position = m_gameObject->getSprite()->getPosition();

	sf::Vector2f direction = sf::Vector2f{ Core::Random::getFloat(-.75, .75), Core::Random::getFloat(-1, 0) }.normalized();
	m_velocity = direction * BASE_PROJECTILE_START_SPEED;

}

void ProjectileMovement::update(float dt)
{
	checkCollisionWithBounds();
	m_position += m_velocity * dt;
	sf::Vector2f renderPos(std::round(m_position.x), std::round(m_position.y));
	m_gameObject->getSprite()->setPosition(renderPos); //this prevents jittering of moving objects in low resolutions
}

void ProjectileMovement::onDestroy()
{
}


void ProjectileMovement::onPaddleCollision(const sf::Vector2f& paddlePos, const sf::Vector2f& paddleSize)
{
	//m_velocity.y *= -1;
	m_position.y = paddlePos.y - paddleSize.y * .5f - m_gameObject->getSprite()->getTexture().getSize().y * .51f;
	//value between -1 and 1
	float distanceFromCenter = std::clamp((m_position.x - paddlePos.x) / (paddleSize.x * .5f), -1.f, 1.f);
	sf::Angle appliedBounceAngle = MAX_BOUNCE_ANGLE * distanceFromCenter;

 	float speed = m_velocity.length();
	m_velocity.x = speed * sinf(appliedBounceAngle.asRadians());
	m_velocity.y = -speed * cosf(appliedBounceAngle.asRadians());
}

void ProjectileMovement::checkCollisionWithBounds()
{
	auto* sprite = m_gameObject->getSprite();
	auto size = sprite->getTexture().getSize();

	switch (Bounds::isCollidingWithBounds(m_position, { (float)size.x, (float)size.y }, m_worldDimensions))
	{
	case Bounds::BoundCollision::Top:
		m_velocity.y *= -1;
		m_position.y = std::max(Bounds::PADDING_TOP, m_position.y);
		break;
	case Bounds::BoundCollision::Bottom:
		m_velocity.y *= -1;
		m_position.y = std::min((float)m_worldDimensions.y, m_position.y);
		break;
	case Bounds::BoundCollision::Left:
		m_velocity.x *= -1;
		m_position.x = std::max(Bounds::PADDING_LEFT, m_position.x);
		break;
	case Bounds::BoundCollision::Right:
		m_velocity.x *= -1;
		m_position.x = std::min(m_worldDimensions.x - Bounds::PADDING_RIGHT, m_position.x);
	}
}

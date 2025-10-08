#include <Game/Projectile/Projectile.h>
#include <Game/BoundsManager.h>
#include <Game/Scales/ScalesManager.h>
#include <Game/Scales/Scale.h>
#include <Core/GameObject.h>
#include <Core/Scene.h>
#include <Core/Game.h>
#include <Core/Random.h>
#include <iostream>

void Projectile::start()
{
	m_scalesManager = m_gameObject->getScene()->getManager<ScalesManager>();
	m_worldDimensions = m_gameObject->getScene()->getGame()->getDimensions();
	m_position = m_gameObject->getSprite()->getPosition();

	sf::Vector2f direction = sf::Vector2f{ Core::Random::getFloat(-.75, .75), Core::Random::getFloat(-1, 0) }.normalized();
	m_velocity = direction * BASE_PROJECTILE_START_SPEED;

}

void Projectile::update(float dt)
{
	if (!checkCollisionWithScales())
	{
		checkCollisionWithBounds();
	}

	m_position += m_velocity * dt;
	sf::Vector2f renderPos(std::round(m_position.x), std::round(m_position.y));
	m_gameObject->getSprite()->setPosition(renderPos); //this prevents jittering of moving objects in low resolutions
	
	if(m_rotate) rotate();
}




void Projectile::onPaddleCollision(const sf::Vector2f& paddlePos, const sf::Vector2f& paddleSize)
{
	//the projectile bounces at an angle dependant on how far from the paddle horizontal center it collided.
	//the farther from the center, the greater the angle
	//value between -1 and 1
	float distanceFromCenter = std::clamp((m_position.x - paddlePos.x) / (paddleSize.x * .5f), -1.f, 1.f);
	sf::Angle appliedBounceAngle = MAX_BOUNCE_ANGLE * distanceFromCenter;

 	float speed = m_velocity.length();
	m_velocity.x = speed * sinf(appliedBounceAngle.asRadians());
	m_velocity.y = -speed * cosf(appliedBounceAngle.asRadians());
}

void Projectile::rotate()
{
	static std::vector<sf::Vector2f> snaps{{1, 1}, {1, -1}, {-1, -1}, {-1, 1}};
	static bool norm = false;
	if (!norm)
	{
		for (auto& v : snaps) v = v.normalized();
		norm = true;
	}

	sf::Vector2f dir = m_velocity.normalized();
	sf::Vector2f bestDir;
	float bestDot = -1;
	for (const auto& v : snaps)
	{
		float dot = v.dot(dir);
		if (dot > bestDot)
		{
			bestDot = dot;
			bestDir = v;
		}
	}

	sf::Angle angle = sf::radians(atan2f(bestDir.y, bestDir.x)) + sf::degrees(45);
	m_gameObject->getSprite()->setRotation(angle);
}

bool Projectile::checkCollisionWithScales()
{
	Scale* scale;
	if (m_isCircle)
	{
		scale = m_scalesManager->checkCollision(Core::Collision::Circle{ m_position, m_circleRadius });
	}
	else
	{
		auto sizeU = m_gameObject->getSprite()->getTexture().getSize();
		auto halfSize = sf::Vector2f{ (float)sizeU.x, (float)sizeU.y } *.5f;
		Core::Collision::AABB aabb
		{
			.Min = m_position - halfSize,
			.Max = m_position + halfSize
		};
		scale = m_scalesManager->checkCollision(aabb);
	}
	
	if (scale != nullptr)
	{
		const auto& scalePos = scale->getGameObject()->getSprite()->getPosition();
		//calculate the normal
		sf::Vector2 normal = (m_position - scalePos).normalized();

		//reflect the velocity
		m_velocity = m_velocity - 2.f * m_velocity.dot(normal) * normal;

		OnScaleCollision.invoke(scale);

		//destroy the scale
		m_scalesManager->destroyScale(scale);


		return true;
	}
	return false;
}


bool Projectile::checkCollisionWithBounds()
{
	auto* sprite = m_gameObject->getSprite();
	auto size = sprite->getTexture().getSize();

	auto* bounds = m_gameObject->getScene()->getManager<BoundsManager>();

	switch (bounds->isCollidingWithBounds(m_position, size))
	{
	case BoundsManager::BoundCollision::None:
		return false;
	case BoundsManager::BoundCollision::Top:
		m_velocity.y *= -1;
		m_position.y = fmaxf(BOUNDS::PADDING_TOP, m_position.y);
		break;
	case BoundsManager::BoundCollision::Bottom:
		m_velocity.y *= -1;
		m_position.y = fminf((float)m_worldDimensions.y, m_position.y);
		break;
	case BoundsManager::BoundCollision::Left:
		m_velocity.x *= -1;
		m_position.x = fmaxf(BOUNDS::PADDING_LEFT, m_position.x);
		break;
	case BoundsManager::BoundCollision::Right:
		m_velocity.x *= -1;
		m_position.x = fminf(m_worldDimensions.x - BOUNDS::PADDING_RIGHT, m_position.x);
	}
	return true;
}

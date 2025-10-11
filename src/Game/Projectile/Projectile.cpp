#include <Game/Projectile/Projectile.h>
#include <Game/Level/BoundsManager.h>
#include <Game/GameConstants.h>
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
}

void Projectile::setRandomVelocity()
{
	float angle = Core::Random::getFloat(-PROJECTILE::START_APERTURE, PROJECTILE::START_APERTURE);
	sf::Vector2f direction = sf::Vector2f{ 0, -1 }.rotatedBy(sf::degrees(angle));
	m_velocity = direction * PROJECTILE::START_SPEED;

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

	switch (m_mode)
	{
	case Mode::LookForward:
		rotateToLookForward();
		break;
	case Mode::Spin:
		m_gameObject->getSprite()->rotate(sf::degrees(PROJECTILE::SPIN_SPEED * dt));
	}
}




void Projectile::onPaddleCollision(const sf::Vector2f& paddlePos)
{
	//the projectile bounces at an angle dependant on how far from the paddle horizontal center it collided.
	//the farther from the center, the greater the angle
	//value between -1 and 1
	float distanceFromCenter = std::clamp((m_position.x - paddlePos.x) / (PADDLE::MAX_WIDTH * .5f), -1.f, 1.f);
	sf::Angle appliedBounceAngle = sf::degrees(PROJECTILE::MAX_BOUNCE_ANGLE) * distanceFromCenter;

	float speed = m_velocity.length();
	m_velocity.x = speed * sinf(appliedBounceAngle.asRadians());
	m_velocity.y = -speed * cosf(appliedBounceAngle.asRadians());
}

void Projectile::rotateToLookForward()
{
	//select the bet snap direction and then get its angle to rotate the sprite

	static std::vector<sf::Vector2f> snaps
	{ 
		sf::Vector2f{ 1,  1}.normalized(), sf::Vector2f{1, -1}.normalized(), 
		sf::Vector2f{-1, -1}.normalized(), sf::Vector2f{-1, 1}.normalized()
	};

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

		if (m_destroysScales)
		{
			//destroy the scale
			m_scalesManager->destroyScale(scale);
		}

		return true;
	}
	return false;
}


bool Projectile::checkCollisionWithBounds()
{
	auto* sprite = m_gameObject->getSprite();
	auto size = m_isCircle
		? sf::Vector2u{(unsigned int)floorf(m_circleRadius), (unsigned int)floorf(m_circleRadius) }
		: sprite->getTexture().getSize();

	auto* bounds = m_gameObject->getScene()->getManager<BoundsManager>();

	int boundsFlags = bounds->isCollidingWithBounds(m_position, size);
	if (boundsFlags == BoundCollision::None)
	{
		return false;
	}
	if (boundsFlags & BoundCollision::Left)
	{
		m_velocity.x = fabs(m_velocity.x);
		m_position.x = fmaxf(BOUNDS::PADDING_LEFT, m_position.x);
		correctVelocityDirection();
	}
	else if (boundsFlags & BoundCollision::Right)
	{
		m_velocity.x = -fabs(m_velocity.x);
		m_position.x = fmaxf(BOUNDS::PADDING_LEFT, m_position.x);
		correctVelocityDirection();
	}
	if (boundsFlags & BoundCollision::Top)
	{
		m_velocity.y = fabs(m_velocity.y);
		m_position.y = fmaxf(BOUNDS::PADDING_TOP, m_position.y);
	}
	else if (boundsFlags & BoundCollision::Bottom)
	{
		OnBottomBoundCollision.invoke();
	}
	return true;
}

void Projectile::correctVelocityDirection()
{
	//set a minimum y direction to avoid the projectile bouncing almost only horizontally bwtween left and right bounds
	float speed = m_velocity.length();
	auto direction = m_velocity / speed;
	if (fabs(direction.y) < PROJECTILE::MIN_BOUND_BOUNCE_Y)
	{
		direction.y =  PROJECTILE::MIN_BOUND_BOUNCE_Y;
		m_velocity = direction.normalized() * speed;
	}
}

#include <Game/Paddle.h>
#include <Game/Projectile/Projectile.h>
#include <Game/GameConstants.h>
#include <Core/GameObject.h>
#include <Core/Scene.h>
#include <Core/Game.h>
#include <Core/Collision.h>
#include <iostream>

void Paddle::start()
{
	m_worldDimensions = m_gameObject->getScene()->getGame()->getDimensions();

	m_position = m_gameObject->getSprite()->getPosition();

}

void Paddle::setProjectile(Projectile* pm)
{
	m_projectile = pm;
}

void Paddle::update(float dt)
{
	moveWithInput(dt);
	clampToBounds();
	if (m_collisionDisabled)
	{
		waitAndEnableCollision(dt);
	}
	else
	{
		checkProjectileCollision();
	}
}

void Paddle::moveWithInput(float dt)
{
	float input = 0.f;
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Left))
	{
		input -= 1.f;
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Right))
	{
		input += 1.f;
	}
	m_position.x += input * PADDLE::SPEED * dt;
}

void Paddle::clampToBounds()
{
	float halfSizeX = m_gameObject->getSprite()->getTexture().getSize().x * .5f;
	m_position.x = std::clamp(m_position.x, BOUNDS::PADDING_LEFT + halfSizeX,
		m_worldDimensions.x - BOUNDS::PADDING_RIGHT - halfSizeX);
	sf::Vector2f renderPos(roundf(m_position.x), roundf(m_position.y));
	m_gameObject->getSprite()->setPosition(renderPos); //this prevents jittering of moving objects in low resolutions
}


void Paddle::checkProjectileCollision()
{
	//don't check if the projectile is going upwards
	if (m_projectile->getVelocity().y < 0)
	{
		return;
	}

	const auto& pos1 = m_position;
	const auto& size1u = m_gameObject->getSprite()->getTexture().getSize();
	const auto& size1 = sf::Vector2f{ (float)size1u.x, (float)size1u.y };


	Core::Collision::AABB paddleAabb;
	paddleAabb.Min = m_position - size1 * .5f;
	paddleAabb.Max = sf::Vector2f{ m_position.x + size1.x * .5f, paddleAabb.Min.y };
	paddleAabb.Max.y += PADDLE::COLLISION_HEIGHT;


	const auto& pos2 = m_projectile->getPosition();
	const auto& size2u = m_projectile->getGameObject()->getSprite()->getTexture().getSize();
	const auto& size2 = sf::Vector2f{ (float)size2u.x, (float)size2u.y };

	if (Core::Collision::isColliding(paddleAabb, Core::Collision::getAABB(pos2, size2)))
	{
		m_projectile->onPaddleCollision(pos1, size1);
		OnProjectileCollision.invoke(m_projectile);

		//disable the collision check for a short time
		m_collisionDisabled = true;
	}

}

void Paddle::waitAndEnableCollision(float dt)
{
	m_collisionDisabledTimer += dt;
	if (m_collisionDisabledTimer >= PADDLE::COLLISION_DISABLED_SECONDS)
	{
		m_collisionDisabled = false;
		m_collisionDisabledTimer = 0.f;
	}
}
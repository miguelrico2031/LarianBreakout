#include <Game/PaddleMovement.h>
#include <Game/ProjectileMovement.h>
#include <Game/Bounds.h>
#include <Core/GameObject.h>
#include <Core/Scene.h>
#include <Core/Game.h>
#include <Core/Collision.h>
#include <algorithm>
#include <iostream>

void PaddleMovement::start()
{
	m_worldDimensions = m_gameObject->getScene()->getGame()->getDimensions();

	m_position = m_gameObject->getSprite()->getPosition();

}

void PaddleMovement::setProjectileMovement(ProjectileMovement* pm)
{
	m_projectileMovement = pm;
}

void PaddleMovement::update(float dt)
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
	m_position.x += input * PADDLE_SPEED * dt;

	float halfSizeX = m_gameObject->getSprite()->getTexture().getSize().x * .5f;
	m_position.x = std::clamp(m_position.x, Bounds::PADDING_LEFT + halfSizeX, 
		m_worldDimensions.x - Bounds::PADDING_RIGHT - halfSizeX);
	sf::Vector2f renderPos(std::round(m_position.x), std::round(m_position.y));
	m_gameObject->getSprite()->setPosition(renderPos); //this prevents jittering of moving objects in low resolutions

	checkProjectileCollision();
}

void PaddleMovement::onDestroy()
{
}

void PaddleMovement::checkProjectileCollision()
{
	const auto& pos1 = m_position;
	const auto& size1u = m_gameObject->getSprite()->getTexture().getSize();
	const auto& size1 = sf::Vector2f{ (float)size1u.x, (float)size1u.y };
	const auto& pos2 = m_projectileMovement->getPosition();
	const auto& size2u = m_projectileMovement->getGameObject()->getSprite()->getTexture().getSize();
	const auto& size2 = sf::Vector2f{ (float)size2u.x, (float)size2u.y };

	if (Core::Collision::isColliding(pos1, size1, pos2, size2))
	{
		m_projectileMovement->onPaddleCollision(pos1, size1);
	}

}
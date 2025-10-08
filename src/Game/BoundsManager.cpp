#include <Game/BoundsManager.h>
#include <Game/GameConstants.h>
#include <Core/Scene.h>
#include <Core/Game.h>

void BoundsManager::start()
{
	m_worldDimensions = m_scene->getGame()->getDimensions();
}

BoundsManager::BoundCollision BoundsManager::isCollidingWithBounds(const sf::Vector2f& center, const sf::Vector2u& size)
{
	float topPos = center.y - size.y * .5f;
	float bottomPos = center.y + size.y * .5f;
	float upBound = BOUNDS::PADDING_TOP;
	float bottomBound = m_worldDimensions.y - BOUNDS::PADDING_BOTTOM;
	if (topPos <= upBound)
	{
		return BoundCollision::Top;
	}
	else if (bottomPos >= bottomBound)
	{
		return BoundCollision::Bottom;
	}

	float leftPos = center.x - size.x * .5f;
	float rightPos = center.x + size.x * .5f;
	float leftBound = BOUNDS::PADDING_LEFT;
	float rightBound = m_worldDimensions.x - BOUNDS::PADDING_RIGHT;

	if (leftPos <= leftBound)
	{
		return BoundCollision::Left;
	}
	else if(rightPos >= rightBound)
	{
		return BoundCollision::Right;
	}

	return BoundCollision::None;
}

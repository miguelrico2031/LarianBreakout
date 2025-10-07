#include <Game/Bounds.h>

Bounds::BoundCollision Bounds::isCollidingWithBounds(sf::Vector2f pos, sf::Vector2f size, sf::Vector2u worldDimensions)
{
	float topPos = pos.y - size.y * .5f;
	float bottomPos = pos.y + size.y * .5f;
	float upBound = PADDING_TOP;
	float bottomBound = worldDimensions.y - PADDING_BOTTOM;
	if (topPos <= upBound)
	{
		return BoundCollision::Top;
	}
	else if (bottomPos >= bottomBound)
	{
		return BoundCollision::Bottom;
	}

	float leftPos = pos.x - size.x * .5f;
	float rightPos = pos.x + size.x * .5f;
	float leftBound = PADDING_LEFT;
	float rightBound = worldDimensions.x - PADDING_RIGHT;

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

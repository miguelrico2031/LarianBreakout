#pragma once
#include <Core/Manager.h>
#include <SFML/Graphics.hpp>

class BoundsManager : public Core::Manager
{
public:	enum class BoundCollision
{
	None = 0, Top, Left, Right, Bottom
};
public:
	BoundsManager(Core::Scene* scene) : Manager(scene) {}
	virtual void start() override;
	BoundCollision isCollidingWithBounds(const sf::Vector2f& pos, const sf::Vector2u& size);
private:
	sf::Vector2u m_worldDimensions;
};
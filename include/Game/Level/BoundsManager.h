#pragma once
#include <Core/Manager.h>
#include <SFML/Graphics.hpp>


namespace BoundCollision
{
	constexpr int None = 0;
	constexpr int Top = 1 << 0;
	constexpr int Bottom = 1 << 1;
	constexpr int Left = 1 << 2;
	constexpr int Right = 1 << 3;
};

class BoundsManager : public Core::Manager
{
public:	

public:
	BoundsManager(Core::Scene* scene) : Manager(scene) {}
	virtual void start() override;
	int isCollidingWithBounds(const sf::Vector2f& center, const sf::Vector2u& size);
private:
	sf::Vector2u m_worldDimensions;
};
#pragma once
#include <SFML/Graphics.hpp>

class Bounds
{
public:
	enum class BoundCollision
	{
		None = 0, Top, Left, Right, Bottom
	};
	static BoundCollision isCollidingWithBounds(sf::Vector2f pos, sf::Vector2f size, sf::Vector2u worldDimensions);
public:
	constexpr static float PADDING_TOP = 8.f;
	constexpr static float PADDING_LEFT = 8.f;
	constexpr static float PADDING_RIGHT = 8.f;
	constexpr static float PADDING_BOTTOM = 0.f;

};
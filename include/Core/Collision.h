#pragma once
#include <SFML/Graphics.hpp>

namespace Core
{
	class Collision
	{
	public:
		static bool isColliding(const sf::Vector2f& pos1, const sf::Vector2f& size1, 
			const sf::Vector2f& pos2, const sf::Vector2f& size2);
	};
}
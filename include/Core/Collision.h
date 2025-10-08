#pragma once
#include <SFML/Graphics.hpp>

namespace Core
{
	class Collision
	{
	public:
		struct AABB
		{
			sf::Vector2f min, max;
		};

		struct Circle
		{
			sf::Vector2f pos;
			float radius;
		};

		static AABB getAABB(const sf::Vector2f& pos, const sf::Vector2f& size);

		static bool isColliding(const AABB& a, const AABB& b);
		static bool isColliding(const AABB& aabb, const Circle& circle);
		static bool isColliding(const Circle& c1, const Circle& c2);

	};
}
#pragma once
#include <SFML/Graphics.hpp>

namespace Core
{
	class Collision
	{
	public:
		struct AABB
		{
			sf::Vector2f Min, Max;
		};

		struct Circle
		{
			sf::Vector2f Center;
			float Radius;
		};

		static AABB getAABB(const sf::Vector2f& Center, const sf::Vector2f& size);

		static bool isColliding(const AABB& a, const AABB& b);
		static bool isColliding(const AABB& aabb, const Circle& circle);
		static bool isColliding(const Circle& c1, const Circle& c2);

	};
}
#include <Core/Collision.h>
#include <algorithm>

namespace Core
{
    Collision::AABB Collision::getAABB(const sf::Vector2f& pos, const sf::Vector2f& size)
    {
        return Collision::AABB
        {
            .min{ pos.x - size.x * 0.5f, pos.y - size.y * 0.5f },
            .max{ pos.x + size.x * 0.5f, pos.y + size.y * 0.5f }
        };
    }

    bool Collision::isColliding(const Collision::AABB& a, const Collision::AABB& b)
    {
        return (a.min.x < b.max.x && a.max.x > b.min.x &&
                a.min.y < b.max.y && a.max.y > b.min.y);
    }

    bool Collision::isColliding(const Collision::AABB& aabb, const Collision::Circle& circle)
    {
        //closest point of aabb inside circle
        float closestX = std::clamp(circle.pos.x, aabb.min.x, aabb.max.x);
        float closestY = std::clamp(circle.pos.y, aabb.min.y, aabb.max.y);

        //distance between circle center and closest point
        float dx = circle.pos.x - closestX;
        float dy = circle.pos.y - closestY;
        float distanceSq = dx * dx + dy * dy;

        return distanceSq <= (circle.radius * circle.radius);
    }

    bool Collision::isColliding(const Circle& c1, const Circle& c2)
    {
        float distance = (c1.pos - c2.pos).length();
        float radiiSum = c1.radius + c2.radius;
        return distance <= radiiSum;
    }


}

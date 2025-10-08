#include <Core/Collision.h>
#include <algorithm>

namespace Core
{
    Collision::AABB Collision::getAABB(const sf::Vector2f& Center, const sf::Vector2f& size)
    {
        return Collision::AABB
        {
            .Min{ Center.x - size.x * 0.5f, Center.y - size.y * 0.5f },
            .Max{ Center.x + size.x * 0.5f, Center.y + size.y * 0.5f }
        };
    }

    bool Collision::isColliding(const Collision::AABB& a, const Collision::AABB& b)
    {
        return (a.Min.x < b.Max.x && a.Max.x > b.Min.x &&
                a.Min.y < b.Max.y && a.Max.y > b.Min.y);
    }

    bool Collision::isColliding(const Collision::AABB& aabb, const Collision::Circle& circle)
    {
        //closest point of aabb inside circle
        float closestX = std::clamp(circle.Center.x, aabb.Min.x, aabb.Max.x);
        float closestY = std::clamp(circle.Center.y, aabb.Min.y, aabb.Max.y);

        //distance between circle center and closest point
        float dx = circle.Center.x - closestX;
        float dy = circle.Center.y - closestY;
        float distanceSq = dx * dx + dy * dy;

        return distanceSq <= (circle.Radius * circle.Radius);
    }

    bool Collision::isColliding(const Circle& c1, const Circle& c2)
    {
        float distance = (c1.Center - c2.Center).length();
        float radiiSum = c1.Radius + c2.Radius;
        return distance <= radiiSum;
    }


}

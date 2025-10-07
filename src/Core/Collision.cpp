#include <Core/Collision.h>

namespace Core
{
	bool Collision::isColliding(const sf::Vector2f& pos1, const sf::Vector2f& size1, 
        const sf::Vector2f& pos2, const sf::Vector2f& size2)
    {
        float leftA = pos1.x - size1.x * .5f;
        float rightA = pos1.x + size1.x * .5f;
        float topA = pos1.y - size1.y * .5f;
        float bottomA = pos1.y + size1.y * .5f;

        float leftB = pos2.x - size2.x * .5f;
        float rightB = pos2.x + size2.x * .5f;
        float topB = pos2.y - size2.y * .5f;
        float bottomB = pos2.y + size2.y * .5f;

        return (leftA < rightB && rightA > leftB && topA < bottomB && bottomA > topB);
    }
}

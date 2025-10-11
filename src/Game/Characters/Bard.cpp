#include <Game/Characters/Bard.h>
#include <Game/Projectile/Projectile.h>
#include <Core/GameObject.h>

void Bard::initialize(int indexInParty)
{
	Character::initialize(indexInParty);
	m_projectile->setDestroysScales(false);
	const auto& projSize = m_projectile->getGameObject()->getSprite()->getTexture().getSize();
	m_projectile->changeColliderToCircle(projSize.x * .5f);

}

void Bard::onPaddleCollidedWithThisProjectile(Paddle* paddle, Character* owner)
{
	if (owner != this)//cannot heal himself
	{
		owner->restoreAllUses();
	}
}

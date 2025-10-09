#include <Game/Characters/Bard.h>
#include <Game/Projectile/Projectile.h>

void Bard::initialize(int indexInParty)
{
	Character::initialize(indexInParty);
	m_projectile->setDestroysScales(false);
}

void Bard::onPaddleCollidedWithThisProjectile(Paddle* paddle, Character* owner)
{
	if (owner != this)//cannot heal himself
	{
		owner->restoreAllUses();
	}


}

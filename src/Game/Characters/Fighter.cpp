#include <Game/Characters/Fighter.h>
#include <Game/Projectile/Projectile.h>
#include <iostream>

void Fighter::initialize(int indexInParty)
{
	Character::initialize(indexInParty);
	m_projectile->enableRotation();
}

void Fighter::onProjectilePaddleCollision()
{
	std::cout << "COLISION FIGHTER\n";

	changeActiveProjectileToOwn();
}

void Fighter::onProjectileScaleCollision(Scale* scale)
{
	std::cout << "\tFIGHTER SWORD KILLED SCALE\n";
}

#include <Game/Characters/Fighter.h>
#include <Core/GameObject.h>
#include <Core/Scene.h>
#include <Game/Projectile/Projectile.h>
#include <Game/Projectile/ProjectileManager.h>
#include <iostream>

void Fighter::initialize(int indexInParty)
{
	Character::initialize(indexInParty);
	m_projectile->setMode(Projectile::Mode::LookForward);
}


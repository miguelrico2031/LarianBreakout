#include <Game/Characters/Fighter.h>
//#include <Core/GameObject.h>
//#include <Core/Scene.h>
//#include <Game/Projectile/Projectile.h>
//#include <Game/Projectile/ProjectileManager.h>
#include <iostream>


void Fighter::onProjectilePaddleCollision()
{
	std::cout << "COLISION FIGHTER\n";

	changeActiveProjectileToOwn();
}

void Fighter::onProjectileScaleCollision(Scale* scale)
{
	std::cout << "\tFIGHTER SWORD KILLED SCALE\n";
}

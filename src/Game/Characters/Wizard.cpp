#include <Game/Characters/Wizard.h>
#include <Game/Projectile/Projectile.h>
#include <Game/Scales/Scale.h>
#include <Game/Scales/ScalesManager.h>
#include <Core/GameObject.h>
#include <Core/Scene.h>
#include <iostream>


void Wizard::initialize(int indexInParty)
{
	Character::initialize(indexInParty);

	const auto& projSize = m_projectile->getGameObject()->getSprite()->getTexture().getSize();

	m_fireBallOverlapRadius = projSize.x * 0.5f;

	//collider is smaller than sprite size, so when it collides with a scale the sprite could be touching several scales
	//and with the overlap radius we later destroy all those scales
	float colliderRadius = m_fireBallOverlapRadius * /*TODO: don't hardcode this */ .75f;

	m_projectile->changeColliderToCircle(colliderRadius);
}

void Wizard::onProjectilePaddleCollision()
{
	std::cout << "WIZARD COLLISION\n";
	changeActiveProjectileToOwn();
}

void Wizard::onProjectileScaleCollision(Scale* scale)
{
	std::cout << "\tWIZARD FIREBALL KILLED SCALE\n";

	//get all the scales overlapped with the big radius
	auto* sm = m_gameObject->getScene()->getManager<ScalesManager>();
	auto scales = sm->checkCollisionAll(Core::Collision::Circle{ m_projectile->getPosition(), m_fireBallOverlapRadius });
	
	for (auto* s : scales)
	{
		if (s == scale) continue;
		sm->destroyScale(s);
	}
}

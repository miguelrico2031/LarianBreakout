#include <Game/Characters/Wizard.h>
#include <Game/Projectile/Projectile.h>
#include <Game/Projectile/ProjectileManager.h>
#include <Game/Scales/Scale.h>
#include <Game/Scales/ScalesManager.h>
#include <Core/GameObject.h>
#include <Core/Scene.h>
#include <Core/Animator.h>
#include <iostream>


void Wizard::initialize(int indexInParty)
{
	Character::initialize(indexInParty);

	auto& animator = m_projectile->getGameObject()->addBehavior<Core::Animator>();
	auto animationKey = Core::Animator::registerAnimation({ "assets/FireBall1.png", "assets/FireBall2.png", "assets/FireBall3.png" });
	animator.playAnimationLoop(animationKey, 10.f);

	const auto& projSize = m_projectile->getGameObject()->getSprite()->getTexture().getSize();

	m_fireBallOverlapRadius = projSize.x * 0.5f;

	//collider is smaller than sprite size, so when it collides with a scale the sprite could be touching several scales
	//and with the overlap radius we later destroy all those scales
	float colliderRadius = m_fireBallOverlapRadius * /*TODO: don't hardcode this */ .75f;

	m_projectile->changeColliderToCircle(colliderRadius);
}

void Wizard::onScaleCollidedWithThisProjectile(Scale* scale)
{
	//get all the scales overlapped with the big radius
	auto* sm = m_gameObject->getScene()->getManager<ScalesManager>();
	auto scales = sm->checkCollisionAll(Core::Collision::Circle{ m_projectile->getPosition(), m_fireBallOverlapRadius });

	for (auto* s : scales)
	{
		if (s == scale) continue;
		sm->destroyScale(s);
	}

	Character::onScaleCollidedWithThisProjectile(scale);
}

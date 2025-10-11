#include <Game/Projectile/ProjectileManager.h>
#include <Game/Projectile/Projectile.h>
#include <Core/Game.h>
#include <Game/GameConstants.h>
#include <Game/Scales/Scale.h>
#include <Game/Characters/CharactersManager.h>
#include <Game/Level/Paddle.h>
#include <Game/Level/BoundsManager.h>
#include <Game/Level/LevelManager.h>


void ProjectileManager::spawnBaseProjectile()
{
	auto& projectileGO = m_scene->createSpriteGameObject(m_baseProjTex, PADDLE::Z);
	
	m_baseProjectile = &projectileGO.addBehavior<Projectile>();

	//on all the other projectiles that are meant to turn into fire projs when colliding with scales,
	//this is handled in each characters initialization method, but the
	//base projectile is not owned by anyone so the manager does this
	m_baseProjectileScaleColObserver = m_baseProjectile->OnScaleCollision.subscribe(
		[this](Scale* s) { setActiveProjectile(m_fireProjectile); });
	projectileGO.Enabled = false;
}

void ProjectileManager::spawnFireProjectile()
{
	auto& projectileGO = m_scene->createSpriteGameObject(m_fireProjTex, PADDLE::Z);
	m_fireProjectile = &projectileGO.addBehavior<Projectile>();
	m_fireProjectile->setMode(Projectile::Mode::Spin);
	projectileGO.Enabled = false;
}

void ProjectileManager::setActiveProjectile(Projectile* projectile)
{
	if (m_activeProjectile == projectile)
	{
		return;
	}

	if (m_activeProjectile != nullptr)
	{

		//the new projectile has to be aligned vertically at the bottom with the old
		//and be at the same horizonal position provided that said position will not cause the new projectile
		//to be out of bounds

		const auto& oldPos = m_activeProjectile->getPosition();
		const auto& oldSize = m_activeProjectile->getGameObject()->getSprite()->getTexture().getSize();
		const auto& newSize = m_activeProjectile->getGameObject()->getSprite()->getTexture().getSize();
		float bottomY = oldPos.y + oldSize.y * .5f;
		float newPosY = bottomY - newSize.y * .5f;

		sf::Vector2f newPos{ oldPos.x, newPosY };
		auto* bounds = m_scene->getManager<BoundsManager>();
		float penetration;
		int boundsFlags = bounds->isCollidingWithBounds(newPos, newSize);
		if (boundsFlags & BoundCollision::Left)
		{
			penetration = BOUNDS::PADDING_LEFT - (newPos.x - newSize.x * .5f);
			newPos.x += penetration;
		}
		else if (boundsFlags & BoundCollision::Right)
		{
			float dimensionX = m_scene->getGame()->getDimensions().x;
			penetration = (newPos.x + newSize.x * .5f) - (dimensionX - BOUNDS::PADDING_RIGHT);
			newPos.x -= penetration;
		}

		projectile->setPosition(newPos);
		projectile->setVelocity(m_activeProjectile->getVelocity());
		
		m_activeProjectile->getGameObject()->Enabled = false;
		m_activeProjectile->OnBottomBoundCollision.unsubscribe(m_activeProjectileBottomColObserver);
	}
	else
	{
		//position the projectile at the start position
		auto dimensions = m_scene->getGame()->getDimensions();
		projectile->setPosition({dimensions.x / 2.f, PROJECTILE::START_Y});
		projectile->setRandomVelocity();
	}


	m_activeProjectile = projectile;
	m_activeProjectile->getGameObject()->Enabled = true;
	m_activeProjectileBottomColObserver = 
		m_activeProjectile->OnBottomBoundCollision.subscribe([this]() { onActiveProjectileCollisionWithBottomBound(); });

	m_scene->getManager<CharactersManager>()->getSelected()->getPaddle()->setProjectile(m_activeProjectile);

}

void ProjectileManager::onActiveProjectileCollisionWithBottomBound()
{
	//disable active projectile this way so when calling setActiveProjectile it behaves as there was no previous
	//projectile, so it will center the baseojectile's position and appy a random velocity
	m_activeProjectile->getGameObject()->Enabled = false;
	m_activeProjectile->OnBottomBoundCollision.unsubscribe(m_activeProjectileBottomColObserver);
	m_activeProjectile = nullptr;

	m_scene->getManager<LevelManager>()->onLifeLost();
}


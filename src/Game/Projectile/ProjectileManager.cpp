#include <Game/Projectile/ProjectileManager.h>
#include <Game/Projectile/Projectile.h>
#include <Core/Game.h>
#include <Game/GameConstants.h>

void ProjectileManager::spawnBaseProjectile()
{
	//spawn base projectile
	auto& projectileGO = m_scene->createSpriteGameObject(m_baseProjTex, PADDLE::Z);
	auto dimensions = m_scene->getGame()->getDimensions();
	projectileGO.getSprite()->setPosition({ dimensions.x / 2.f, PROJECTILE::Y_POS });
	m_baseProjectile = &projectileGO.addBehavior<Projectile>();
	projectileGO.Enabled = false;
}

void ProjectileManager::setActiveProjectile(Projectile* projectile)
{
	m_activeProjectile = projectile;
}

void ProjectileManager::setActiveProjectileToBase()
{
	m_activeProjectile = m_baseProjectile;
	m_baseProjectile->getGameObject()->Enabled = true;

}

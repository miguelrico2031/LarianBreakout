#pragma once
#include <Core/Manager.h>
#include <SFML/Graphics.hpp>
#include <Core/Event.h>

class Projectile;
class Scale;
class ProjectileManager : public Core::Manager
{
public:
	ProjectileManager(Core::Scene* scene)
		: Manager(scene), m_baseProjTex("assets/BaseBall.png"), m_fireProjTex("assets/FireProjectile.png") {
	}
	void spawnBaseProjectile();
	void spawnFireProjectile();
	Projectile* getActiveProjectile() const { return m_activeProjectile; }
	Projectile* getBaseProjectile() const { return m_baseProjectile; }
	Projectile* getFireProjectile() const { return m_fireProjectile; }
	void setActiveProjectile(Projectile* projectile);
private:
	void onActiveProjectileCollisionWithBottomBound();
private:
	Projectile* m_activeProjectile = nullptr;
	Projectile* m_baseProjectile = nullptr;
	Projectile* m_fireProjectile = nullptr;
	sf::Texture m_baseProjTex, m_fireProjTex;
	Core::ObserverID m_baseProjectileScaleColObserver;
	Core::ObserverID m_activeProjectileBottomColObserver;
};
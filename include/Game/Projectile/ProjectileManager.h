#pragma once
#include <Core/Manager.h>
#include <SFML/Graphics.hpp>

class Projectile;
class ProjectileManager : public Core::Manager
{
public:
	ProjectileManager(Core::Scene* scene)
		: Manager(scene), m_baseProjTex("assets/BaseBall.png") {}
	void spawnBaseProjectile();
	Projectile* getActiveProjectile() const { return m_activeProjectile; }
	void setActiveProjectile(Projectile* projectile);
	void setActiveProjectileToBase();
private:
	Projectile* m_activeProjectile;
	Projectile* m_baseProjectile;
	sf::Texture m_baseProjTex;
};
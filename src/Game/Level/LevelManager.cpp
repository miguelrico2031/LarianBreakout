#include <Game/Level/LevelManager.h>
#include <Game/Projectile/ProjectileManager.h>
#include <Core/Scene.h>
#include <Core/AsyncManager.h>

void LevelManager::onLifeLost()
{
	//update the UI
	OnLivesChanged.invoke(--m_currentLives);

	if (m_currentLives > 0)
	{
		//wait some time and spawn base projectile
		m_scene->getManager<Core::AsyncManager>()->invokeIn([this]()
			{
				auto* pm = m_scene->getManager<ProjectileManager>();
				pm->setActiveProjectile(pm->getBaseProjectile());
			}, LEVEL::LOSE_LIFE_DURATION);
	}
}

void LevelManager::winLevel()
{
}

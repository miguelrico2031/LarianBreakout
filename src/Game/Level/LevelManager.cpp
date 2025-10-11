#include <Game/Level/LevelManager.h>
#include <Game/Projectile/ProjectileManager.h>
#include <Core/Scene.h>
#include <Core/Game.h>
#include <Core/AsyncManager.h>
#include <Core/SaveManager.h>
#include <Game/Scenes/VictoryScene.h>
#include <Game/GameConstants.h>


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
			}, HUD::LOSE_HEART_DURATION);
	}
	else
	{
		//save the level completed
		auto* sm = m_scene->getManager<Core::SaveManager>();
		sm->set("dragons_slain", std::to_string(Data.Number));
		sm->saveToDisk();

		//load the level victory scene
		auto* game = m_scene->getGame();
		auto key = game->loadScene<VictoryScene>();
		game->changeScene(key, true);
	}
}

void LevelManager::winLevel()
{
	//save the level completed
	auto* sm = m_scene->getManager<Core::SaveManager>();
	sm->set("dragons_slain", std::to_string(Data.Number));
	sm->saveToDisk();

	//load the level victory scene
	auto* game = m_scene->getGame();
	auto key = game->loadScene<VictoryScene>();
	game->changeScene(key, true);
}

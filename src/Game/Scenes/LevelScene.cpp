#include <Game/Scenes/LevelScene.h>
#include <Core/Game.h>
#include <Game/Level/Paddle.h>
#include <Game/Projectile/Projectile.h>
#include <Game/Projectile/ProjectileManager.h>
#include <Game/Scales/ScalesManager.h>
#include <Game/Characters/CharactersManager.h>
#include <Game/Level/BoundsManager.h>
#include <Game/Level/LevelManager.h>
#include <Game/HUD/CharacterPanelManager.h>
#include <Game/HUD/HeartsManager.h>
#include <iostream> 

void LevelScene::load()
{
	Scene::load();

	loadFrameAndBackground();
	addManager<LevelManager>(m_data);
	addManager<BoundsManager>();
	addManager<ScalesManager>();
	addManager<ProjectileManager>();
	addManager<CharactersManager>();
	addManager<CharacterPanelManager>();
	addManager<HeartsManager>();

	getManager<ScalesManager>()->spawnScales(m_data.ScaleRows);
	getManager<ProjectileManager>()->spawnBaseProjectile();
	getManager<ProjectileManager>()->spawnFireProjectile();
	getManager<CharactersManager>()->spawnParty(m_data.Party);
	getManager<CharacterPanelManager>()->spawnCharacterPanels();
}

void LevelScene::start()
{
	Scene::start();

	getManager<ProjectileManager>()->setActiveProjectile(getManager<ProjectileManager>()->getBaseProjectile());
	getManager<CharactersManager>()->selectInitialCharacter();
	
}

void LevelScene::loadFrameAndBackground()
{
	m_textures["frame"] = sf::Texture("assets/Frame.png");
	auto& frame = createSpriteGameObject(m_textures["frame"], 100);
	const auto& dimensions = m_game->getDimensions();
	sf::Vector2f center{ dimensions.x / 2.f, dimensions.y / 2.f };
	frame.getSprite()->setPosition(center);


	m_textures["background"] = sf::Texture(m_data.BackgroundPath);
	auto& bg = createSpriteGameObject(m_textures["background"],-200);
	center = { dimensions.x / 2.f, dimensions.y / 2.f };
	bg.getSprite()->setPosition(center);
	bg.getSprite()->setColor({ 130, 130, 130, 255 });

}





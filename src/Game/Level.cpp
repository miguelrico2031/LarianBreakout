#include <Game/Level.h>
#include <Core/Game.h>
#include <Game/Paddle.h>
#include <Game/Projectile/Projectile.h>
#include <Game/Projectile/ProjectileManager.h>
#include <Game/Scales/ScalesManager.h>
#include <Game/Characters/CharactersManager.h>
#include <Game/BoundsManager.h>
#include <iostream> 

void Level::load()
{
	loadFrame();
	addManager<BoundsManager>();
	addManager<ScalesManager>();
	addManager<ProjectileManager>();
	addManager<CharactersManager>();

	getManager<ScalesManager>()->spawnScales(m_data.rows);
	getManager<ProjectileManager>()->spawnBaseProjectile();
	getManager<CharactersManager>()->spawnParty(m_data.party);
}

void Level::start()
{
	Scene::start();

	getManager<ProjectileManager>()->setActiveProjectileToBase();
	getManager<CharactersManager>()->play();

}

void Level::loadFrame()
{
	m_textures["frame"] = sf::Texture("assets/Frame.png");
	auto& frame = createSpriteGameObject(m_textures["frame"], 100);
	auto dimensions = m_game->getDimensions();
	sf::Vector2f center{ dimensions.x / 2.f, dimensions.y / 2.f };
	frame.getSprite()->setPosition(center);
	frame.getSprite()->setColor({ 255, 255, 255, 100 });
}





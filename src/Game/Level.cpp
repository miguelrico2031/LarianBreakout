#include <Game/Level.h>
#include <Core/Game.h>
#include <Game/Paddle.h>
#include <Game/Projectile/Projectile.h>
#include <Game/Projectile/ProjectileManager.h>
#include <Game/Scales/ScalesManager.h>
#include <Game/Characters/CharactersManager.h>
#include <Game/BoundsManager.h>
#include <Game/UI/CharacterPanelManager.h>
#include <iostream> 

void Level::load()
{
	loadFrameAndBackground();
	addManager<BoundsManager>();
	addManager<ScalesManager>();
	addManager<ProjectileManager>();
	addManager<CharactersManager>();
	addManager<CharacterPanelManager>();

	getManager<ScalesManager>()->spawnScales(m_data.ScaleRows);
	getManager<ProjectileManager>()->spawnBaseProjectile();
	getManager<ProjectileManager>()->spawnFireProjectile();
	getManager<CharactersManager>()->spawnParty(m_data.Party);
	getManager<CharacterPanelManager>()->spawnCharacterPanels();
}

void Level::start()
{
	Scene::start();

	getManager<ProjectileManager>()->setActiveProjectile(getManager<ProjectileManager>()->getBaseProjectile());
	getManager<CharactersManager>()->selectInitialCharacter();
	
}

void Level::loadFrameAndBackground()
{
	m_textures["frame"] = sf::Texture("assets/Frame.png");
	auto& frame = createSpriteGameObject(m_textures["frame"], 100);
	const auto& dimensions = m_game->getDimensions();
	sf::Vector2f center{ dimensions.x / 2.f, dimensions.y / 2.f };
	frame.getSprite()->setPosition(center);

	m_textures["background"] = sf::Texture("assets/Background.png");
	auto& bg = createSpriteGameObject(m_textures["background"],-200);
	center = { dimensions.x / 2.f, dimensions.y / 2.f };
	bg.getSprite()->setPosition(center);
	bg.getSprite()->setColor({ 130, 130, 130, 255 });

}





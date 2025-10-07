#include <Game/TestScene.h>
#include <Core/Game.h>
#include <Game/ProjectileMovement.h>
#include <Game/PaddleMovement.h>

void TestScene::load()
{
	loadFrame();
	loadScales();
	loadProjectile();
	loadPaddle();
	
}
void TestScene::loadFrame()
{
	m_textures["frame"] = sf::Texture("assets/Frame.png");
	auto& frame = createSpriteGameObject(m_textures["frame"], 100);
	auto dimensions = m_game->getDimensions();
	sf::Vector2f center{ dimensions.x / 2.f, dimensions.y / 2.f };
	frame.getSprite()->setPosition(center);
}

void TestScene::loadScales()
{
	m_textures["scale"] = sf::Texture("assets/Scale.png");
	auto dimensions = m_game->getDimensions();

	auto scaleSize = m_textures["scale"].getSize();
	//scale row

	const int rows = 5;
	sf::Vector2f start{ 0, 30 };

	int initialZ = 20;

	for (int row = 0; row < rows; row++)
	{
		float y = start.y + scaleSize.x * row * 5.f / 8.f;

		float z = initialZ - row;

		for (float x = start.x + scaleSize.x * (row % 2 != 0 ? 1 : .5f);
			x <= dimensions.x - scaleSize.x * .5f; x += scaleSize.x)
		{
			auto& scale = createSpriteGameObject(m_textures["scale"], z);
			scale.getSprite()->setPosition({ x, y });
		}
	}
}

void TestScene::loadProjectile()
{
	m_textures["baseball"] = sf::Texture("assets/BaseBall.png");
	auto& projectile = createSpriteGameObject(m_textures["baseball"], 80);
	m_projectile = &projectile;
	auto dimensions = m_game->getDimensions();
	projectile.getSprite()->setPosition({ dimensions.x / 2.f, 3* dimensions.y / 4.f });
	projectile.addBehavior<ProjectileMovement>();
}

void TestScene::loadPaddle()
{
	m_textures["shield1"] = sf::Texture("assets/FighterShield.png");
	auto& paddle = createSpriteGameObject(m_textures["shield1"], 90);
	m_paddle = &paddle;
	auto dimensions = m_game->getDimensions();
	paddle.getSprite()->setPosition({ dimensions.x / 2.f, 4 * dimensions.y / 5.f });
	auto& paddleMovement = paddle.addBehavior<PaddleMovement>();
	paddleMovement.setProjectileMovement(m_projectile->getBehavior<ProjectileMovement>());
}



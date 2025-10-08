#include <Game/Characters/Character.h>
#include <Core/Game.h>
#include <Core/Scene.h>
#include <Core/GameObject.h>
#include <Game/Paddle.h>
#include <Game/Projectile/Projectile.h>
#include <Game/Projectile/ProjectileManager.h>
#include <Game/Scales/ScalesManager.h>
#include <Game/GameConstants.h>
#include <Game/BoundsManager.h>

void Character::initialize(int indexInParty)
{
	m_paddleTexture = std::make_unique<sf::Texture>(Data.PaddleTexturePath);
	m_projectileTexture = std::make_unique<sf::Texture>(Data.ProjectileTexturePath);

	m_indexInParty = indexInParty;

	auto dimensions = m_gameObject->getScene()->getGame()->getDimensions();

	auto& projectileGO = m_gameObject->getScene()->createSpriteGameObject(*m_projectileTexture, PROJECTILE::Z);
	projectileGO.getSprite()->setPosition({ dimensions.x / 2.f, PROJECTILE::Y_POS });
	m_projectile = &projectileGO.addBehavior<Projectile>();
	m_projectile->OnScaleCollision.subscribe([this](Scale* s) { onProjectileScaleCollision(s); });
	projectileGO.Enabled = false;

	auto& paddleGO = m_gameObject->getScene()->createSpriteGameObject(*m_paddleTexture, PADDLE::Z);
	//the Y is offsetted so the paddle's top face is at Y_POS, not the paddle's center
	paddleGO.getSprite()->setPosition({ dimensions.x / 2.f, PADDLE::Y_POS - m_paddleTexture->getSize().y * .5f});
	m_paddle = &paddleGO.addBehavior<Paddle>();
	m_paddle->OnProjectileCollision.subscribe([this]() { onProjectilePaddleCollision(); });
	paddleGO.Enabled = false;
}

void Character::select(const Paddle* lastPaddle, Projectile* currentProjectile)
{
	//enable the character's paddle
	m_paddle->getGameObject()->Enabled = true; 
	m_paddle->setProjectile(currentProjectile);
	if (lastPaddle == nullptr)
	{
		return;
	}
	//move it to the last paddle's position considering the offset so the top face does not change position
	const auto& Center = lastPaddle->getPosition();
	int lastPaddleHeight = lastPaddle->getGameObject()->getSprite()->getTexture().getSize().y;
	int topPosY = Center.y - lastPaddleHeight * .5f;
	sf::Vector2f newPos{ Center.x, topPosY + m_paddleTexture->getSize().y * .5f };
	m_paddle->setPosition(newPos);
}


void Character::deselect()
{
	m_paddle->getGameObject()->Enabled = false;
}

void Character::changeActiveProjectileToOwn()
{
	m_projectile->getGameObject()->Enabled = true;
	auto* pm = m_gameObject->getScene()->getManager<ProjectileManager>();
	auto* oldProjectile = pm->getActiveProjectile();

	if (oldProjectile == m_projectile)
	{
		return;
	}

	//the new projectile has to be aligned vertically at the bottom with the old
	//and be at the same horizonal position provided that said position will not cause the new projectile
	//to be out of bounds

	const auto& oldPos = oldProjectile->getPosition();
	const auto& oldSize = oldProjectile->getGameObject()->getSprite()->getTexture().getSize();
	const auto& newSize = m_projectile->getGameObject()->getSprite()->getTexture().getSize();
	float bottomY = oldPos.y + oldSize.y * .5f;
	float newPosY = bottomY - newSize.y * .5f;

	sf::Vector2f newPos{ oldPos.x, newPosY };
	auto* bounds = m_gameObject->getScene()->getManager<BoundsManager>();
	float penetration;
	switch (bounds->isCollidingWithBounds(newPos, newSize))
	{
	case BoundsManager::BoundCollision::Left:
		penetration = BOUNDS::PADDING_LEFT - (newPos.x - newSize.x * .5f);
		newPos.x += penetration;
		break;
	case BoundsManager::BoundCollision::Right:
		float dimensionX = m_gameObject->getScene()->getGame()->getDimensions().x;
		penetration = (newPos.x + newSize.x * .5f) - (dimensionX - BOUNDS::PADDING_RIGHT);
		newPos.x -= penetration;
		break;
	}

	m_projectile->setPosition(newPos);
	m_projectile->setVelocity(oldProjectile->getVelocity());

	oldProjectile->getGameObject()->Enabled = false;
	pm->setActiveProjectile(m_projectile);
	m_paddle->setProjectile(m_projectile);

}
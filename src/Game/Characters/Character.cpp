#include <Game/Characters/Character.h>
#include <Game/Characters/CharactersManager.h>
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

	const auto& dimensions = m_gameObject->getScene()->getGame()->getDimensions();

	auto& projectileGO = m_gameObject->getScene()->createSpriteGameObject(*m_projectileTexture, PROJECTILE::Z);
	projectileGO.getSprite()->setPosition({ dimensions.x / 2.f, PROJECTILE::Y_POS });
	m_projectile = &projectileGO.addBehavior<Projectile>();
	m_projectile->OnScaleCollision.subscribe([this](Scale* s) { onScaleCollidedWithThisProjectile(s); });
	projectileGO.Enabled = false;

	auto& paddleGO = m_gameObject->getScene()->createSpriteGameObject(*m_paddleTexture, PADDLE::Z);
	//the Y is offsetted so the paddle's top face is at Y_POS, not the paddle's center
	paddleGO.getSprite()->setPosition({ dimensions.x / 2.f, PADDLE::Y_POS - m_paddleTexture->getSize().y * .5f });
	m_paddle = &paddleGO.addBehavior<Paddle>();
	m_paddle->OnProjectileCollision.subscribe([this](Projectile* p) { onProjectileCollidedWithThisPaddle(p); });
	paddleGO.Enabled = false;
}


void Character::update(float dt)
{
	if (m_isOnCooldown)
	{
		m_remainingCooldown -= dt;
		if (m_remainingCooldown <= 0.f)
		{
			OnAbilityUsesChanged.invoke(++m_remainingUses);
			if (m_remainingUses == Data.MaxAbilityUses)
			{
				m_isOnCooldown = false;
			}
			else
			{
				m_remainingCooldown = Data.CooldownDuration;
			}
		}
		OnCooldownChanged.invoke(m_remainingCooldown);
	}
}


void Character::select(const Paddle* lastPaddle, Projectile* currentProjectile)
{
	//enable the character's paddle
	m_paddle->getGameObject()->Enabled = true;
	m_paddle->setProjectile(currentProjectile);
	if (lastPaddle == nullptr)
	{
		OnCharacterSelectedChanged.invoke(true);
		return;
	}
	//move it to the last paddle's position considering the offset so the top face does not change position
	const auto& center = lastPaddle->getPosition();
	int lastPaddleHeight = lastPaddle->getGameObject()->getSprite()->getTexture().getSize().y;
	int topPosY = center.y - lastPaddleHeight * .5f;
	sf::Vector2f newPos{ center.x, topPosY + m_paddleTexture->getSize().y * .5f };
	m_paddle->setPosition(newPos);

	OnCharacterSelectedChanged.invoke(true);
}


void Character::deselect()
{
	m_paddle->getGameObject()->Enabled = false;
	OnCharacterSelectedChanged.invoke(false);
}

void Character::onProjectileCollidedWithThisPaddle(Projectile* projectile)
{
	//first, get the projectile's owner and call it's onScaleCollidedWithThisProjectile()
	for (auto* character : m_gameObject->getScene()->getManager<CharactersManager>()->getParty())
	{
		if (character->getProjectile() == projectile)
		{
			character->onPaddleCollidedWithThisProjectile(m_paddle, this);
		}
	}

	if (m_remainingUses > 0)
	{
		useAbility();
		OnAbilityUsesChanged.invoke(--m_remainingUses);
		m_isOnCooldown = true;
		m_remainingCooldown = Data.CooldownDuration;
	}
	else
	{
		//by default if a character has no ability uses, a base projectile will spawn instead
		auto* pm = m_gameObject->getScene()->getManager<ProjectileManager>();
		pm->setActiveProjectile(pm->getBaseProjectile());
	}
}


void Character::onScaleCollidedWithThisProjectile(Scale* scale)
{
	//most of the characters' projectiles and the base projectile change to the fire projectile after bouncing with the scales
	auto* pm = m_gameObject->getScene()->getManager<ProjectileManager>();
	pm->setActiveProjectile(pm->getFireProjectile());
}

void Character::useAbility()
{
	m_gameObject->getScene()->getManager<ProjectileManager>()->setActiveProjectile(m_projectile);
}


void Character::restoreAllUses()
{
	m_remainingUses = Data.MaxAbilityUses;
	OnAbilityUsesChanged.invoke(m_remainingUses);
	m_isOnCooldown = false;
	m_remainingCooldown = 0;
	OnCooldownChanged.invoke(m_remainingCooldown);
}
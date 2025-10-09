#include <Game/Characters/Paladin.h>
#include <Game/Projectile/Projectile.h>
#include <Game/Projectile/ProjectileManager.h>
#include <Game/Paddle.h>
#include <Game/Scales/ScalesManager.h>
#include <Game/GameConstants.h>
#include <Core/Scene.h>
#include <Core/Game.h>

void Paladin::initialize(int indexInParty)
{
	Character::initialize(indexInParty);

	m_projectile->setMode(Projectile::Mode::LookForward);

	m_smiteTex.loadFromFile("assets/Smite1.png");
	m_smite = &m_gameObject->getScene()->createSpriteGameObject(m_smiteTex, 60);
	const auto& dimensions = m_gameObject->getScene()->getGame()->getDimensions();
	m_smite->getSprite()->setPosition({ dimensions.x * .5f, dimensions.y * .5f });
	m_smiteAnimator = &m_smite->addBehavior<Core::Animator>();
	m_smiteAnimKey = Core::Animator::registerAnimation(
		{
			"assets/Smite1.png",
			"assets/Smite2.png",
			"assets/Smite3.png",
			"assets/Smite4.png",
			"assets/Smite5.png"
		}
	);
	m_smite->Enabled = false;
}

void Paladin::useAbility()
{
	Character::useAbility();

	//enable smite and play animation
	auto pos = m_smite->getSprite()->getPosition();
	pos.x = m_paddle->getPosition().x;
	m_smite->getSprite()->setPosition(pos);
	m_smite->Enabled = true;
	m_smiteAnimator->playAnimationOnce(m_smiteAnimKey, 10, [this]() { m_smite->Enabled = false; });

	smiteScales();
}

void Paladin::smiteScales()
{
	auto* sm = m_gameObject->getScene()->getManager<ScalesManager>();
	const auto& pos = m_smite->getSprite()->getPosition();
	const auto& sizeU = m_smiteTex.getSize();
	sf::Vector2 size{ SMITE::HITBOX_WIDTH, (float)sizeU.y };
	auto scales = sm->checkCollisionAll(Core::Collision::AABB{ .Min = pos - size * .5f, .Max = pos + size * .5f });
	for (auto& s : scales)
	{
		sm->destroyScale(s);
	}
}

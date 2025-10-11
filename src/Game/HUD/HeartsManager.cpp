#include <Game/HUD/HeartsManager.h>
#include <Game/GameConstants.h>
#include <Game/Level/LevelManager.h>
#include <Core/GameObject.h>
#include <Core/Scene.h>

void HeartsManager::start()
{
	m_heartTex.loadFromFile("assets/Heart.png");
	for (size_t i = 0; i < LEVEL::START_LIVES; i++)
	{
		auto& heart = m_scene->createSpriteGameObject(m_heartTex, HUD::Z);
		heart.getSprite()->setOrigin({ 0, 0 });
		heart.getSprite()->setPosition({ HUD::HEART_START_X + i * (m_heartTex.getSize().x + HUD::HEART_PADDING), HUD::HEART_Y });

		heart.addBehavior<Core::Animator>();
		m_heartAnimKey = Core::Animator::registerAnimation({
			"assets/Heart1.png",
			"assets/Heart2.png",
			"assets/Heart3.png"
			});

		m_hearts.push_back(&heart);
	}

	m_scene->getManager<LevelManager>()->OnLivesChanged.subscribe([this](auto l) { onLivesChanged(l); });
}

void HeartsManager::onLivesChanged(unsigned int lives)
{
	int hearts = lives;
	for (auto* heart : m_hearts)
	{
		if (hearts-- > 0)
		{
			heart->Enabled = true;

		}
		else if(heart->Enabled)
		{
			heart->getBehavior <Core::Animator>()->playAnimationOnce(m_heartAnimKey, 10.f, [this, heart]()
				{
					heart->Enabled = false;
					heart->getSprite()->setTexture(m_heartTex);
				});
		}
	}
}

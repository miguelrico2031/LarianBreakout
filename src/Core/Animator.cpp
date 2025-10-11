#include <Core/Animator.h>
#include <Core/GameObject.h>

namespace Core
{
	std::unordered_map<Animator::Key, Animator::Animation> Animator::s_animations;

	void Animator::update(float dt)
	{
		if (m_currentAnimation == nullptr) return;

		m_frameTimer += dt;
		if (m_frameTimer >= m_delayBetwwenFrames)
		{
			m_frameTimer = 0.f;

			if (m_currentFrame + 1 == m_currentAnimation->Textures.size())
			{
				if (m_loop)
				{
					m_currentFrame = 0;
					m_gameObject->getSprite()->setTexture(*m_currentAnimation->Textures[m_currentFrame]);
				}
				else
				{
					m_currentAnimation = nullptr;
					if (m_currentCallback) m_currentCallback();
				}
			}
			else
			{
				m_currentFrame++;
				m_gameObject->getSprite()->setTexture(*m_currentAnimation->Textures[m_currentFrame]);
			}
		}
	}

	Animator::Key Animator::registerAnimation(const std::vector<std::filesystem::path>& texturePaths)
	{
		static Animator::Key nextKey = 0;
		auto key = nextKey++;
		s_animations[key].Key = key;
		for (const auto& path : texturePaths)
		{
			auto tex = std::make_unique<sf::Texture>(path);
			s_animations[key].Textures.push_back(std::move(tex));
		}
		return key;
	}

	void Animator::playAnimationOnce(Animator::Key key, float speed, std::function<void()> onFinishedCallback)
	{
		auto& animation = s_animations.at(key);
		m_currentAnimation = &animation;
		m_currentFrame = 0;
		m_currentCallback = onFinishedCallback;
		m_delayBetwwenFrames = 1.f / speed;
		m_frameTimer = 0.f;
		m_loop = false;

		m_gameObject->getSprite()->setTexture(*m_currentAnimation->Textures[m_currentFrame]);
	}

	void Animator::playAnimationLoop(Animator::Key key, float speed)
	{
		auto& animation = s_animations.at(key);
		m_currentAnimation = &animation;
		m_currentFrame = 0;
		m_delayBetwwenFrames = 1.f / speed;
		m_frameTimer = 0.f;
		m_loop = true;

		m_gameObject->getSprite()->setTexture(*m_currentAnimation->Textures[m_currentFrame]);
	}
}
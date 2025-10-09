#pragma once
#include <Core/Behavior.h>
#include <SFML/Graphics.hpp>
#include <filesystem>
#include <vector>
#include <unordered_map>
#include <functional>
#include <memory>
#include <string>

namespace Core
{
	class Animator : public Core::Behavior
	{
	public:
		Animator(Core::GameObject* g) : Behavior(g) {}

		virtual void update(float dt) override;

		using Key = unsigned int;

		static Key registerAnimation(const std::vector<std::filesystem::path>& texturePaths);
		void playAnimationOnce(Key key, float speed, std::function<void()> onFinishedCallback = nullptr);
		void playAnimationLoop(Key key, float speed);
	private:
		struct Animation
		{
			std::vector<std::unique_ptr<sf::Texture>> Textures;
			Key Key;
		};
	private:
		static std::unordered_map<Key, Animation> m_animations;
		Animation* m_currentAnimation = nullptr;
		size_t m_currentFrame;
		std::function<void()> m_currentCallback = nullptr;
		bool m_loop = false;
		float m_delayBetwwenFrames;
		float m_frameTimer;
	};
}
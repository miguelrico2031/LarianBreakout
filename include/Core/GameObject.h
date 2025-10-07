#pragma once
#include <SFML/Graphics.hpp>
#include <vector>
#include <memory>
#include <Core/Behavior.h>

namespace Core
{
	class Scene;
	class GameObject
	{
	public:
		GameObject(Scene* scene) 
			: m_scene(scene)
		{

		}
		GameObject(Scene* scene, const sf::Texture& spriteTex, int spriteZ = 0)
			: m_scene(scene), m_sprite(std::make_unique<sf::Sprite>(spriteTex)), m_spriteZ(spriteZ)
		{
			auto size = m_sprite->getTexture().getSize();
			m_sprite->setOrigin({ size.x / 2.f, size.y / 2.f });
		}
		sf::Sprite* getSprite() const { return m_sprite.get(); }
		int getSpriteZ() const { return m_spriteZ; }
		void setSpriteZ(int z) { m_spriteZ = z; }
		
		Scene* getScene() const { return m_scene; }

		template<typename T>
		T& addBehavior()
		{
			m_behaviors.push_back(std::make_unique<T>(this));
			m_behaviors.back()->start();
			return *dynamic_cast<T*>(m_behaviors.back().get());
		}

		template<typename T>
		T* getBehavior()
		{
			auto it = std::find_if(m_behaviors.begin(), m_behaviors.end(),
				[](const auto& b) { return dynamic_cast<T*>(b.get()) != nullptr; });
			if (it != m_behaviors.end())
			{
				return dynamic_cast<T*>(it->get());
			}
			else
			{
				return nullptr;
			}
		}

		const std::vector<std::unique_ptr<Behavior>>& getBehaviors() const { return m_behaviors; }
	private:
		std::unique_ptr<sf::Sprite> m_sprite;
		int m_spriteZ = -1000000;
		std::vector<std::unique_ptr<Behavior>> m_behaviors;
		Scene* m_scene;
	};
}
#pragma once
#include <Core/GameObject.h>
#include <Core/Behavior.h>
#include <vector>
#include <unordered_map>
#include <memory>

namespace Core
{
	class Game;
	class Scene
	{
	public:
		Scene(Game* game) : m_game(game) {}
		virtual ~Scene() = default;
		virtual void load() = 0;
		virtual void update(float dt);
		void render(sf::RenderTarget& target);
		GameObject& createEmptyGameObject();
		GameObject& createSpriteGameObject(sf::Texture& texture, int z = 0);
		void destroyGameObject(GameObject* gameObject);
		Game* getGame() const { return m_game; }
	private:
		void sortGameObjects();
	protected:
		Game* m_game;
	private:
		std::vector<std::unique_ptr<GameObject>> m_gameObjects;
		bool m_gameObjectsSorted = true;
	};
}
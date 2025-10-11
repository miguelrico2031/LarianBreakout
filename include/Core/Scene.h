#pragma once
#include <Core/GameObject.h>
#include <Core/Behavior.h>
#include <Core/Manager.h>
#include <vector>
#include <unordered_map>
#include <memory>
#include <typeindex>
#include <typeinfo>

namespace Core
{
	class Game;
	class Scene
	{
	public:
		Scene(Game* game) : m_game(game) {}
		virtual ~Scene() = default;
		virtual void load();
		virtual void start();
		virtual void update(float dt);
		virtual void onEvent(const sf::Event* e);
		virtual void render(sf::RenderTarget& target);
		GameObject& createEmptyGameObject();
		GameObject& createSpriteGameObject(const sf::Texture& texture, int z);
		void destroyGameObject(GameObject* gameObject);
		Game* getGame() const { return m_game; }
		bool isStarted() const { return m_started; }

		//managers must be added before the scene starts, at the load method
		//and it's life time will be the same as the scene's
		template <typename T, typename... Args>
		T& addManager(Args&&... args)
		{
			auto manager = std::make_unique<T>(this, std::forward<Args>(args)...);
			T* ptr = manager.get();
			m_managers[typeid(T)] = std::move(manager);
			return *ptr;
		}

		template <typename T>
		T* getManager()
		{
			auto it = m_managers.find(typeid(T));
			if (it != m_managers.end())
			{
				return static_cast<T*>(it->second.get());
			}
			return nullptr;
		}



	private:
		void sortGameObjects();
		void addNewGameObjects();
		void eraseDestroyedGameObjects();
	protected:
		Game* m_game;
	private:
		std::unordered_map<std::type_index, std::unique_ptr<Manager>> m_managers;
		std::vector<std::unique_ptr<GameObject>> m_gameObjects;
		std::vector<std::unique_ptr<GameObject>> m_newGameObjects;
		bool m_gameObjectsSorted = true;
		bool m_started = false;
	};
}
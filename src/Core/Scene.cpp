#include <Core/Scene.h>
#include <Core/Game.h>
#include <algorithm>

namespace Core
{
	void Scene::start()
	{
		for (auto& [_, manager] : m_managers)
		{
			manager->start();
		}

		for (auto& gameObject : m_gameObjects)
		{
			for (auto& behavior : gameObject->getBehaviors())
			{
				behavior->start();
			}
		}

		m_started = true;
	}

	void Scene::update(float dt)
	{
		for (auto& [_, manager] : m_managers)
		{
			manager->update(dt);
		}

		for (auto& gameObject : m_gameObjects)
		{
			if (!gameObject->Enabled || gameObject->Destroyed)
			{
				continue;
			}
			for (auto& behavior : gameObject->getBehaviors())
			{
				if (!gameObject->Destroyed)
				{
					behavior->update(dt);
				}
			}
		}
		eraseDestroyedGameObjects();
	}

	void Scene::onEvent(const sf::Event* event)
	{
		for (auto& [_, manager] : m_managers)
		{
			manager->onEvent(event);
		}

		for (auto& gameObject : m_gameObjects)
		{
			if (!gameObject->Enabled || gameObject->Destroyed)
			{
				continue;
			}
			for (auto& behavior : gameObject->getBehaviors())
			{
				if (!gameObject->Destroyed)
				{
					behavior->onEvent(event);
				}
			}
		}
	}


	void Scene::render(sf::RenderTarget& target)
	{
		if (!m_gameObjectsSorted)
		{
			sortGameObjects();
		}

		for (const auto& gameObject : m_gameObjects)
		{
			if (!gameObject->Enabled || gameObject->Destroyed)
			{
				continue;
			}
			if (auto* sprite = gameObject->getSprite())
			{
				target.draw(*sprite);
			}	
		}
#ifndef NDEBUG
		for (const auto& gameObject : m_gameObjects)
		{
			if (!gameObject->Enabled || gameObject->Destroyed)
			{
				continue;
			}
			for (auto& shape : gameObject->DebugShapes)
			{
				target.draw(*shape);
			}
		}
#endif
	}

	GameObject& Scene::createEmptyGameObject()
	{
		m_gameObjects.push_back(std::make_unique<GameObject>(this));
		return *m_gameObjects.back();
	}

	GameObject& Scene::createSpriteGameObject(sf::Texture& texture, int z)
	{
		m_gameObjects.push_back(std::make_unique<GameObject>(this, texture, z));
		m_gameObjectsSorted = false;
		return *m_gameObjects.back();
	}


	void Scene::destroyGameObject(GameObject* gameObject)
	{
		gameObject->Destroyed = true;
	}

	void Scene::sortGameObjects()
	{
		std::sort(m_gameObjects.begin(), m_gameObjects.end(),
			[](const auto& a, const auto& b) { return a->getSpriteZ() < b->getSpriteZ(); });
		m_gameObjectsSorted = true;
	}

	void Scene::eraseDestroyedGameObjects()
	{
		auto it = std::remove_if(m_gameObjects.begin(), m_gameObjects.end(),
			[](const auto& go) { return go->Destroyed; });
		m_gameObjects.erase(it, m_gameObjects.end());
	}


}
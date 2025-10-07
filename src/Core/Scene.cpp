#include <Core/Scene.h>
#include <Core/Game.h>
#include <algorithm>

namespace Core
{
	void Scene::update(float dt)
	{
		for (auto& gameObject : m_gameObjects)
		{
			for (auto& behavior : gameObject->getBehaviors())
			{
				behavior->update(dt);
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
			if (auto* sprite = gameObject->getSprite())
			{
				target.draw(*sprite);
			}
		}
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
		auto it = std::find_if(m_gameObjects.begin(), m_gameObjects.end(),
			[&gameObject](const auto& gO) { return gameObject == gO.get(); });
		if (it == m_gameObjects.end())
		{
			return;
		}
		for (auto& behavior : gameObject->getBehaviors())
		{
			behavior->onDestroy();
		}
		m_gameObjects.erase(it);
		m_gameObjectsSorted = false;
	}

	void Scene::sortGameObjects()
	{
		std::sort(m_gameObjects.begin(), m_gameObjects.end(),
			[](const auto& a, const auto& b) { return a->getSpriteZ() < b->getSpriteZ(); });
		m_gameObjectsSorted = true;
	}


}
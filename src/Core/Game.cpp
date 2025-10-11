#include <Core/Game.h>

namespace Core
{
	Game::Game(unsigned int width, unsigned int height, unsigned int scale, const char* windowName)
		: m_dimensions(width, height), m_scale(scale),
		m_window(sf::VideoMode({ width * scale, height * scale }),
			windowName, sf::Style::Titlebar | sf::Style::Close),
		m_renderTexture({ width, height }),
		m_view(sf::FloatRect({ 0, 0 }, { (float)width, (float)height }))
	{
		m_renderSprite = std::make_unique<sf::Sprite>(m_renderTexture.getTexture());
		m_renderSprite->setPosition({ 0, 0 });
		m_renderSprite->setScale({ (float)scale, (float)scale });
		m_renderTexture.setSmooth(false);
		//m_window.setFramerateLimit(60);
		m_window.setVerticalSyncEnabled(true);
		m_window.setKeyRepeatEnabled(false);

		m_view.setViewport(sf::FloatRect({ 0, 0 }, { 1, 1 }));
		m_renderTexture.setView(m_view);
	}

	void Game::changeScene(SceneKey scene, bool unloadCurrent)
	{
		if (m_activeScene == nullptr)
		{
			m_activeScene = m_loadedScenes.at(scene).get();
			m_activeSceneKey = scene;
			m_activeScene->start();
		}
		else
		{
			m_sceneToChange = scene;
			m_unloadCurrent = unloadCurrent;
		}
	}

	void Game::unloadScene(SceneKey scene)
	{
		if (scene == m_activeSceneKey)
		{
			m_activeSceneKey = -1;
			m_activeScene = nullptr;
		}
		m_loadedScenes.erase(scene);
	}

	void Game::run()
	{
		isRunning = true;

		while (m_window.isOpen())
		{
			while (const std::optional event = m_window.pollEvent())
			{
				if (event->is<sf::Event::Closed>())
					m_window.close();
				m_activeScene->onEvent(&event.value());
			}

			float dt = m_clock.restart().asSeconds();
			m_activeScene->update(dt);


			m_renderTexture.clear();
			m_activeScene->render(m_renderTexture);
			m_renderTexture.display();

			m_window.clear();
			m_window.draw(*m_renderSprite);
			m_window.display();

			if (m_sceneToChange != -1)
			{
				handleSceneChange();
			}
		}
		isRunning = false;
	}

	void Game::handleSceneChange()
	{
		if (m_unloadCurrent)
		{
			unloadScene(m_activeSceneKey);
		}
		m_activeScene = m_loadedScenes.at(m_sceneToChange).get();
		m_activeSceneKey = m_sceneToChange;
		m_activeScene->start();
		m_sceneToChange = -1;
	}

}
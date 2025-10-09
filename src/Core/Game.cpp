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

	void Game::run()
	{
		isRunning = true;

		m_currentScene->load();
		m_currentScene->start();

		while (m_window.isOpen())
		{
			while (const std::optional event = m_window.pollEvent())
			{
				if (event->is<sf::Event::Closed>())
					m_window.close();
				m_currentScene->onEvent(&event.value());
			}

			float dt = m_clock.restart().asSeconds();
			m_currentScene->update(dt);


			m_renderTexture.clear();
			m_currentScene->render(m_renderTexture);
			m_renderTexture.display();

			m_window.clear();
			m_window.draw(*m_renderSprite);
			m_window.display();
		}
		isRunning = false;
	}
}
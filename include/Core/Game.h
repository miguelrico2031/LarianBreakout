#pragma once
#include <Core/Scene.h>

namespace Core
{
	class Game
	{
	public:

		Game(unsigned int width, unsigned int height, unsigned int scale, const char* windowName);
		
		template<typename T, typename... Args>
		void setScene(Args&&... args)
		{
			m_currentScene = std::make_unique<T>(this, std::forward<Args>(args)...);
			if (isRunning)
			{
				m_currentScene->load();
				m_currentScene->start();
			}
		}
		void run();
		const sf::Vector2u& getDimensions() const { return m_dimensions; }
	private:
		sf::RenderWindow m_window;
		sf::Clock m_clock;
		sf::Vector2u m_dimensions;
		unsigned int m_scale;
		sf::RenderTexture m_renderTexture;
		std::unique_ptr<sf::Sprite> m_renderSprite;
		std::unique_ptr<Scene> m_currentScene;
		bool isRunning = false;
		sf::View m_view;
	};
}
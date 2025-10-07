#pragma once
#include <Core/Scene.h>

namespace Core
{
	class Game
	{
	public:

		Game(unsigned int width, unsigned int height, unsigned int scale, const char* windowName);
		
		template<typename T>
		void setScene()
		{
			m_currentScene = std::make_unique<T>(this);
			if (isRunning) m_currentScene->load();
		}
		void run();
		sf::Vector2u getDimensions() const { return { m_width, m_height }; }
	private:
		sf::RenderWindow m_window;
		sf::Clock m_clock;
		unsigned int m_width;
		unsigned int m_height;
		unsigned int m_scale;
		sf::RenderTexture m_renderTexture;
		std::unique_ptr<sf::Sprite> m_renderSprite;
		std::unique_ptr<Scene> m_currentScene;
		bool isRunning = false;
		sf::View m_view;
	};
}
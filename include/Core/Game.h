#pragma once
#include <Core/Scene.h>
#include <unordered_map>

namespace Core
{
	class Game
	{
	public:
		using SceneKey = int;
	public:

		Game(unsigned int width, unsigned int height, unsigned int scale, const char* windowName);
		
		template<typename T, typename... Args>
		SceneKey loadScene(Args&&... args)
		{
			SceneKey key = m_nextSceneKey++;
			m_loadedScenes[key] = std::make_unique<T>(this, std::forward<Args>(args)...);
			return key;
		}
		void setActiveScene(SceneKey scene);
		void unloadScene(SceneKey scene);


		void run();

		const sf::Vector2u& getDimensions() const { return m_dimensions; }
	private:
		sf::RenderWindow m_window;
		sf::Clock m_clock;
		sf::Vector2u m_dimensions;
		unsigned int m_scale;
		sf::RenderTexture m_renderTexture;
		std::unique_ptr<sf::Sprite> m_renderSprite;
		bool isRunning = false;
		sf::View m_view;
		SceneKey m_nextSceneKey = 0;
		SceneKey m_activeSceneKey = -1;
		Scene* m_activeScene = nullptr;
		std::unordered_map<SceneKey, std::unique_ptr<Scene>> m_loadedScenes;
	};
}
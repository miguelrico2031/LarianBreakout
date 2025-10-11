#include <Core/Text.h>
#include <Core/Game.h>

namespace Core
{
	void Text::setString(const std::string& str, const sf::Font& font, unsigned int characterSize, bool centered)
	{
		m_centered = centered;
		m_lines.clear();
		for (int start = 0, i = 0;; i++)
		{
			int end = str.find('\n', start);
			m_lines.push_back(std::make_unique<sf::Text>(font));
			sf::Text& text = *m_lines.back();
			text.setString(str.substr(start, end - start));
			text.setCharacterSize(characterSize);
			sf::FloatRect bounds = text.getLocalBounds();

			if (centered)
			{
				text.setOrigin({roundf( bounds.position.x + bounds.size.x * .5f) , 0.f });
			}
			else
			{
				text.setOrigin({ bounds.position.x, 0.f });
			}
			
			if (end == -1)
			{
				break;
			}
			start = end + 1;
		}
	}

	void Text::clearString()
	{
		m_lines.clear();
	}

	void Text::draw(sf::RenderTarget& target)
	{
		for (int i = 0; i < m_lines.size(); i++)
		{
			sf::Text& text = *m_lines[i];
			text.setPosition({ (float)Position.x, roundf(Position.y + text.getCharacterSize() * i * 1.5f) });

			target.draw(text);
		}
	}
}
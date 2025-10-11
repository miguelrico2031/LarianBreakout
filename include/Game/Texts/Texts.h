#pragma once
#include <string>
#include <array>
#include <SFML/Graphics.hpp>

//namespace TEXT
//{
//	inline void centerText(sf::Text& text, const sf::Vector2u& dimensions)
//	{
//		auto rect = text.getLocalBounds();
//		text.setOrigin(rect.position + rect.size * .5f);
//		text.setPosition({ dimensions.x * .5f, dimensions.y * .5f });
//	}
//}

namespace FONT
{
	inline const sf::Font& REGULAR()
	{
		static sf::Font font("assets/dogicapixel.ttf");
		return font;
	}

	inline const sf::Font& BOLD()
	{
		static sf::Font font("assets/dogicapixelbold.ttf");
		return font;
	}
}

namespace VICTORY
{
	inline const std::string TEXT = "Dragon Slain!";
	inline const std::array<std::string, 4> INFO_TEXTS
	{
		"After defeating the\n"
		"Green Dragon, you\n"
		"advance through the\n"
		"cave and encounter\n"
		"another fellow\n"
		"adventurer...\n",

		"After defeating the\n"
		"Blue Dragon, you\n"
		"advance through the\n"
		"cave and encounter\n"
		"another fellow\n"
		"adventurer...\n",
		
		"After defeating the\n"
		"Green Dragon, you\n"
		"advance through the\n"
		"cave and encounter\n"
		"another fellow\n"
		"adventurer...\n",

		"You have defeated\n"
		"all the dragons in the cave. You advance through the passageway "
		"that was protected by the Great Red Dragon, and find an exit. At last, you breathe in the fresh air and prepare to "
		"return to the city, where you will be welcomed as heroes."
	};
}


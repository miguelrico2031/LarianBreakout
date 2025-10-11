#pragma once
#include <Game/Characters/Character.h>
#include <vector>
#include <array>
#include <string>
#include <filesystem>


namespace Levels
{
	struct Data
	{
		unsigned int Number;
		unsigned int StartLives;
		unsigned int ScaleRows;
		std::vector<Characters::Type> Party;
		sf::Color ClearColor;
		std::string ScaleFileName;
		std::filesystem::path BackgroundPath;
	};

	inline const Data Level1
	{
		.Number = 1,
		.StartLives = 1,
		.ScaleRows = 1,
		.Party = { Characters::Type::Fighter },
		.ScaleFileName = "Scale_green",
		.BackgroundPath = "assets/Background_green.png"
	};

	inline const Data Level2
	{
		.Number = 2,
		.StartLives = 3,
		.ScaleRows = 2,
		.Party = { Characters::Type::Fighter, Characters::Type::Wizard },
		.ScaleFileName = "Scale_blue",
		.BackgroundPath = "assets/Background_blue.png"
	};

	inline const Data Level3
	{
		.Number = 3,
		.StartLives = 3,
		.ScaleRows = 3,
		.Party = { Characters::Type::Fighter, Characters::Type::Wizard, Characters::Type::Paladin },
		.ScaleFileName = "Scale_black",
		.BackgroundPath = "assets/Background_black.png"
	};

	inline const Data Level4
	{
		.Number = 4,
		.StartLives = 4,
		.ScaleRows = 4,
		.Party = { Characters::Type::Fighter, Characters::Type::Wizard, Characters::Type::Paladin, Characters::Type::Bard },
		.ScaleFileName = "Scale_red",
		.BackgroundPath = "assets/Background_red.png"
	};

	inline const std::array<const Data, 4> Levels{ Level1, Level2, Level3, Level4 };
}
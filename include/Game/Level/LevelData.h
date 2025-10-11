#pragma once
#include <Game/Characters/Character.h>
#include <vector>


struct LevelData
{
	unsigned int ScaleRows;
	std::vector<Characters::Type> Party;
	sf::Color ClearColor;
};
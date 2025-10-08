#pragma once
#include <Core/Scene.h>
#include <Game/Characters/Character.h>
#include <vector>
#include <unordered_map>
#include <string>


class Level : public Core::Scene
{
public:
	struct Data
	{
		unsigned int ScaleRows;
		std::vector<Characters::Type> Party;
	};

public:
	Level(Core::Game* game, const Data& data) : Scene(game), m_data(data) {}
	Level(Core::Game* game, Data&& data) : Scene(game), m_data(std::move(data)) {}
	virtual void load() override;
	virtual void start() override;

private:
	void loadFrame();

private:
	Data m_data;
	std::unordered_map<std::string, sf::Texture> m_textures;
};
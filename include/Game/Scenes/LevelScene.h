#pragma once
#include <Core/Scene.h>
#include <Game/Level/Levels.h>
#include <unordered_map>
#include <string>


class LevelScene : public Core::Scene
{
public:
	LevelScene(Core::Game* game, const Levels::Data& data) : Scene(game), m_data(data) {}
	virtual void load() override;
	virtual void start() override;
private:
	void loadFrameAndBackground();

private:
	const Levels::Data& m_data;
	std::unordered_map<std::string, sf::Texture> m_textures;
};
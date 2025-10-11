#pragma once
#include <Core/Scene.h>
#include <Game/Level/LevelData.h>
#include <unordered_map>
#include <string>


class LevelScene : public Core::Scene
{
public:
	LevelScene(Core::Game* game, const LevelData& data) : Scene(game), m_data(data) {}
	virtual void load() override;
	virtual void start() override;
	virtual void render(sf::RenderTarget& target) override;
private:
	void loadFrameAndBackground();

private:
	LevelData m_data;
	std::unordered_map<std::string, sf::Texture> m_textures;
};
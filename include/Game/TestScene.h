#pragma once
#include <Core/Scene.h>
#include <unordered_map>
#include <string>

class TestScene : public Core::Scene 
{
public:
	TestScene(Core::Game* game) : Scene(game) {}
	virtual void load() override final;
private:
	void loadFrame();
	void loadScales();
	void loadProjectile();
	void loadPaddle();
private:
	std::unordered_map<std::string, sf::Texture> m_textures;
	Core::GameObject* m_projectile;
	Core::GameObject* m_paddle;

};
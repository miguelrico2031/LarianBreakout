#pragma once
#include <Core/Scene.h>
#include <Core/Text.h>
#include <Game/Texts/Texts.h>

class NewCharacterScene : public Core::Scene
{
public:
	NewCharacterScene(Core::Game* game) : Core::Scene(game) {}
	virtual void load() override;
	virtual void start() override;
	virtual void onEvent(const sf::Event* event) override;
private:
	void loadNextLevel();
	void showTutorial(const std::string& tutorial);
private:
	Core::Text* m_titleText;
	Core::Text* m_descriptionText;
	sf::Texture m_symbolTex;
	int m_dragonsSlain;
	bool m_onTutorial = false;
};
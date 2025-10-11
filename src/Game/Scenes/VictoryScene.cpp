#include <Game/Scenes/VictoryScene.h>
#include <Game/Scenes/NewCharacterScene.h>
#include <Core/SaveManager.h>
#include <Core/AsyncManager.h>
#include <Core/Game.h>
#include <Game/Level/Levels.h>
#include <Game/GameConstants.h>
#include <iostream>

void VictoryScene::load()
{
	Scene::load();
	m_slainText = &createText();
	m_infoText = &createText();
}

void VictoryScene::start()
{
	Scene::start();

	auto* sm = getManager<Core::SaveManager>();
	sm->loadFromDisk();
	int dragonsSlain = std::stoi(sm->get("dragons_slain", "1"));

	m_slainText->setString(VICTORY::TEXT, FONT::BOLD(), 8, true);
	const auto& dimensions = m_game->getDimensions();
	m_slainText->Position = { (unsigned int)roundf(dimensions.x * .5f), VICTORY::SLAIN_TEXT_Y };

	auto* am = getManager<Core::AsyncManager>();
	am->invokeIn([this, am, dragonsSlain]()
		{
			const auto& dimensions = m_game->getDimensions();
			m_infoText->setString(VICTORY::INFO_TEXTS[dragonsSlain - 1], FONT::REGULAR(), 8, true);
			m_infoText->Position = { (unsigned int)roundf(dimensions.x * .5f), VICTORY::INFO_TEXT_Y };
		}, VICTORY::SLAIN_TEXT_DURATION);

	am->invokeIn([this, am, dragonsSlain]()
		{
			m_slainText->clearString();
			m_infoText->clearString();
			if (dragonsSlain < Levels::Levels.size())
			{
				goToNewCharacterScene();
			}
			else
			{
				goToCredits();
			}

		}, VICTORY::SLAIN_TEXT_DURATION + VICTORY::INFO_TEXT_DURATION);

}


void VictoryScene::goToNewCharacterScene()
{
	auto key = m_game->loadScene<NewCharacterScene>();
	m_game->changeScene(key, true);
}

void VictoryScene::goToCredits()
{
	//erase save file because the game is completed
	getManager<Core::SaveManager>()->deleteSave();

	//credits
	std::cout << "credits!\n";

}


#include <Game/Scenes/NewCharacterScene.h>
#include <Game/Scenes/LevelScene.h>
#include <Game/Level/Levels.h>
#include <Core/SaveManager.h>
#include <Core/AsyncManager.h>
#include <Core/Game.h>
#include <Game/GameConstants.h>
#include <Game/Characters/Characters.h>

void NewCharacterScene::load()
{
	Scene::load();
	m_titleText = &createText();
	m_descriptionText = &createText();

}

void NewCharacterScene::start()
{
	Scene::start();

	auto* sm = getManager<Core::SaveManager>();
	sm->loadFromDisk();
	m_dragonsSlain = std::stoi(sm->get("dragons_slain", "0"));

	const auto& character = Characters::Characters[m_dragonsSlain];
	const auto& dimensions = m_game->getDimensions();
	std::string title = "The " + character.TitleText + "\njoins your party!";
	m_titleText->setString(title, FONT::BOLD(), 8, true);
	m_titleText->Position = { (unsigned int)roundf(dimensions.x * .5f), CHARACTERS::TITLE_TEXT_Y };


	m_symbolTex.loadFromFile(character.SymbolTexturePath);
	auto& symbol = createSpriteGameObject(m_symbolTex, 0);
	symbol.getSprite()->setScale({ 2, 2 });
	symbol.getSprite()->setPosition({ dimensions.x * .5f, CHARACTERS::SYMBOL_TEXT_Y });

	std::string description = character.DescriptionText
		+ "\nAbility Uses: " + std::to_string(character.MaxAbilityUses)
		+ "\nRestore Use Time: " + std::to_string(character.CooldownDuration)
		+ "\nPress SPACE to continue...";
	m_descriptionText->setString(description, FONT::REGULAR(), 8, true);
	m_descriptionText->Position = { (unsigned int)roundf(dimensions.x * .5f), CHARACTERS::DESCRIPTION_TEXT_Y };

}

void NewCharacterScene::onEvent(const sf::Event* event)
{
	Scene::onEvent(event);
	if (const auto* e = event->getIf<sf::Event::KeyPressed>())
	{
		if (e->code == sf::Keyboard::Key::Space)
		{
			if (m_onTutorial)
			{
				loadNextLevel();
				return;
			}
			const auto& character = Characters::Characters[m_dragonsSlain];
			if (character.Tutorial.empty())
			{
				loadNextLevel();
			}
			else
			{
				showTutorial(character.Tutorial);
			}
		}
	}
}

void NewCharacterScene::loadNextLevel()
{
	auto key = m_game->loadScene<LevelScene>(Levels::Levels[m_dragonsSlain]);
	m_game->changeScene(key, true);
}

void NewCharacterScene::showTutorial(const std::string& tutorial)
{
	m_onTutorial = true;
}

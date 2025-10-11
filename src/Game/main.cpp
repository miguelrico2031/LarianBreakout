#include <Core/Game.h>
#include <Game/GameConstants.h>
#include <Game/Scenes/LevelScene.h>

int main()
{
	Core::Game game(WINDOW::WIDTH, WINDOW::HEIGHT, WINDOW::SCALE, WINDOW::NAME);

	LevelData data
	{
		.ScaleRows = 4,
		.Party = { Characters::Type::Fighter, Characters::Type::Wizard, Characters::Type::Paladin, Characters::Type::Bard }
	};
	auto sceneKey = game.loadScene<LevelScene>(data);
	game.setActiveScene(sceneKey);
	game.run();
}
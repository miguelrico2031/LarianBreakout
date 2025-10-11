#include <Core/Game.h>
#include <Game/GameConstants.h>
#include <Game/Scenes/NewCharacterScene.h>

int main()
{
	Core::Game game(WINDOW::WIDTH, WINDOW::HEIGHT, WINDOW::SCALE, WINDOW::NAME);

	auto sceneKey = game.loadScene<NewCharacterScene>();
	game.changeScene(sceneKey);
	game.run();
}
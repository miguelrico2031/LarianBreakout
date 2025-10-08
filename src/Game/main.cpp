#include <Core/Game.h>
#include <Game/GameConstants.h>
#include <Game/Level.h>

int main()
{
	Core::Game game(WINDOW::WIDTH, WINDOW::HEIGHT, WINDOW::SCALE, WINDOW::NAME);

	Level::Data data
	{
		.ScaleRows = 4,
		.Party = { Characters::Type::Fighter, Characters::Type::Wizard }
	};
	game.setScene<Level>(data);
	game.run();
}
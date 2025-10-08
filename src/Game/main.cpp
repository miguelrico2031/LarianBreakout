#include <Core/Game.h>
#include <Game/GameConstants.h>
#include <Game/Level.h>

int main()
{
	Core::Game game(WINDOW::WIDTH, WINDOW::HEIGHT, WINDOW::SCALE, WINDOW::NAME);

	Level::Data data
	{
		.rows = 4,
		.party = { Character::Characters::Fighter, Character::Characters::Wizard }
	};
	game.setScene<Level>(data);
	game.run();
}
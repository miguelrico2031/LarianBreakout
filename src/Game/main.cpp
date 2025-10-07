#include <Core/Game.h>
#include <Game/TestScene.h>

int main()
{

    constexpr int GAME_WIDTH = 160;
    constexpr int GAME_HEIGHT = 144;
    constexpr int SCALE = 4;
    const char* WINDOW_NAME = "LARIAN TAL";

    Core::Game game(GAME_WIDTH, GAME_HEIGHT, SCALE, WINDOW_NAME);
    game.setScene<TestScene>();
    game.run();

}
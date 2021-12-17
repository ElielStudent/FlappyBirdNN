#include <SFML/Graphics.hpp>
#include "Game.h"
#include "UserGame.h"
#include "AiGame.h"

int main()
{
    Game* game = new AiGame();
    game->Start();
}
#include "..\header\GameManager.h"

#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>

int main()
{
    srand((unsigned int)time(NULL));

    GameManager newGame;
    newGame.Run();
    return 0;
}

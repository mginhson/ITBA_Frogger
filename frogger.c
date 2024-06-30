#include <stdio.h>
#include <stdlib.h>
#include "game/game_logic.h"
#include <time.h>

int main(int argc, char **argv)
{
    puts("frogger");
    initializeGameLogic();   
    while(1)
    {
        gameTick(100);
        usleep(100000);
    }
    return 0;
}

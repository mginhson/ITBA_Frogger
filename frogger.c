#include <stdio.h>
#include <stdlib.h>
#include "game/game_logic.h"
#include <unistd.h>
#include "allegro/init.h"
int main(int argc, char **argv)
{
    puts("frogger");
    initializeGameLogic();
    init_allegro();
    while (1){

        gameTick(100);
        usleep(10000);
    }
}


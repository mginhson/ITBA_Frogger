#include <stdio.h>
#include <stdlib.h>
#include "game/game_logic.h"
#include <time.h>
#include "../menu_logic/menu_logic.h"

int main(int argc, char **argv)
{
    puts("frogger");
    initializeGameLogic();   
    while(1)
    {
        gameTick(10);
        usleep(100000);
    }
    open_menu_1 ();


    return 0;
}

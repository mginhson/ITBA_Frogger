#include <stdio.h>
#include <stdlib.h>
#include "game/game_logic.h"

int main(int argc, char **argv)
{
    puts("frogger");
    initializeGameLogic();   
    gameTick(100); 
    return 0;
}
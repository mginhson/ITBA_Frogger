#include <stdio.h>
#include <stdlib.h>
#include "game/game_logic.h"
#include <unistd.h>
int main(int argc, char **argv)
{
    puts("frogger");
    while (1){
        gameTick(100);
        usleep(100000);
    }
}
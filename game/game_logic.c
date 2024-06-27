#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <time.h>
#include "game_logic.h"
#include "../entities/entities.h"



static void updateMap(void);
static void generateNewLevel(uint32_t _level);



static map_t map;
static uint32_t level;
static const uint32_t lane_bound = sizeof(map.lanes)/sizeof(map.lanes[0]);



static struct{
    object_t obj;
    const object_kind_t params;
}ranita = {
    .params = {
        .hitbox_width = LANE_X_PIXELS/16,
        .attr = {.canKill=0, .canMove=1, .isEquippable=0},
    },
};

/*
    @BRIEF: gameTick
    -Check if the ranita moved  
    
*/

void gameTick(uint32_t ms_since_last_tick)
{
    uint32_t i=0;
    
}

void initializeGameLogic(void)
{
    srand(time(NULL));
    level = 0;
    fillMap(&map,level);
    printf("lane bound = %d\n",lane_bound);
}




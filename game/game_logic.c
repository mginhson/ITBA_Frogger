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
static const uint32_t object_bound = sizeof(map.lanes[0].objects)/sizeof(map.lanes[0].objects[0]);


independent_object_t ranita = {
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
    uint32_t i,j;

    for(i=0; i < lane_bound; i++)
    {
        map.lanes[i].ms_to_next -= ms_since_last_tick;

        if(map.lanes[i].ms_to_next <= 0) //Lane should move a pixel
        {
            map.lanes[i].ms_to_next += map.lanes[i].ms_reload; //Reload the ms counter
            for(j=0; j<sizeof(map.lanes[i].))
        }
    }
}

void initializeGameLogic(void)
{
    srand(time(NULL));
    level = 0;
    fillMap(&map,level);
    printf("lane bound = %d\n",lane_bound);
}




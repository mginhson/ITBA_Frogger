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
            /*
                Now we will analyze if the object should move, and if it does, we have to check
                wether it went out of the lane bounds, and if so, reset it to the corresponding corner
                The .position attribute correspond to the leftmost side of an object.
            */
            for(j=0; j<object_bound; ++j)
            {
                if(map.lanes[i].direction == RIGHT) //Move every object a pixel to the right
                {
                    map.lanes[i].objects[j].position += 1;
                    if (map.lanes[i].objects[j].position > map.lanes[i].virtual_lane_length)
                    {
                        map.lanes[i].objects[j].position = 1 - map.lanes[i].kind->hitbox_width;
                    }
                }
                else
                {
                    map.lanes[i].objects->position -= 1;

                    if(map.lanes[i].objects[j].position + map.lanes[i].kind->hitbox_width < 0)
                    {
                        map.lanes[i].objects[j].position = 
                        map.lanes[i].virtual_lane_length - map.lanes[i].kind->hitbox_width;
                    }
                }
                
        
                
            }
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




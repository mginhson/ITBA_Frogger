#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <time.h>
#include "game_logic.h"
#include "../entities/entities.h"



static void updateMap(void);
static void generateNewLevel(uint32_t _level);

typedef enum{RANITA_UP,RANITA_DOWN,RANITA_LEFT,RANITA_RIGHT}ranita_logic_direction_t;
static void triggerRanitaMovement(ranita_logic_direction_t _direction);


static map_t map;
static uint32_t level;
static const uint32_t lane_bound = sizeof(map.lanes)/sizeof(map.lanes[0]);
static const uint32_t object_bound = sizeof(map.lanes[0].objects)/sizeof(map.lanes[0].objects[0]);


independent_object_t ranita = {
    .params = {
        .hitbox_width = LANE_X_PIXELS/12,
        .attr = {.canKill=0, .canMove=1, .isEquippable=0},
    }, .hitbox_height = LANE_PIXEL_HEIGHT,

    
    
};

/*
    @BRIEF: gameTick
    -Check if the ranita moved  
    -Update the objects on the map
*/
void gameTick(uint32_t ms_since_last_tick)
{
    uint32_t i,j;
    static int64_t ms_cooldown=0;

    ms_cooldown -= ms_since_last_tick;
    if(ms_cooldown < 0) //we can check for movement again 
    {
        ms_cooldown = 0;
        if(0) //REPLACE FOR CALLING INPUT FUNCTION
        {
            ms_cooldown = MS_RANITA_MOVEMENT_COOLDOWN;
            //Execute the movement
            triggerRanitaMovement(RANITA_UP);
        }
    }


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

    //Now we move on to the ranita <3

    
}

static void triggerRanitaMovement(ranita_logic_direction_t _direction)
{
    //REMEMBER that the position is relative to the upper left corner
    static const int32_t vertical_offset = LANE_Y_PIXELS / LANES_COUNT; //How much should the ranita move vertically 
    int32_t temp;
    switch(_direction)
    {
        case RANITA_DOWN:
            temp = ranita.y_position - vertical_offset;
            
            break;


        case RANITA_UP:
            
            break;


        case RANITA_LEFT:

            break;


        case RANITA_RIGHT:

            break;

        default:
            printf("Unknown direction input at triggerRanitaMovement()\n");
            break;
    }
}

void initializeGameLogic(void)
{
    srand(time(NULL));
    level = 0;
    fillMap(&map,level);
    printf("lane bound = %d\n",lane_bound);
}




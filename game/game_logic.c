#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <time.h>
#include "game_logic.h"
#include "../entities/entities.h"



static void updateMap(void);
static void generateNewLevel(uint32_t _level);
static void collisionAnalysis(void);
static void winAnalysis(void);


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
    .y_position = LANE_Y_PIXELS-1+LANE_PIXEL_HEIGHT-1,
    
    
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

    //Now we move onto the ranita <3
    
    
}

static void triggerRanitaMovement(ranita_logic_direction_t _direction)
{
    //REMEMBER that the position is relative to the upper left corner
    int32_t temp;
    switch(_direction)
    {
        case RANITA_DOWN:
            temp = ranita.y_position - ranita.hitbox_height; //y position of the bottom
            if (temp - ranita.hitbox_height < 0) //would go below map, set is as low as possible
            {
                ranita.y_position = ranita.hitbox_height; //lowest pixel for the upper left corner
            }
            else
            {
                ranita.y_position -= ranita.hitbox_height;
            }
            break;


        case RANITA_UP:
            
            if ((ranita.y_position + ranita.hitbox_height) >= LANE_Y_PIXELS) //would go above map
            {
                ranita.y_position = LANE_Y_PIXELS - 1;//uppermost pixel for the upper left corner
            }
            else
            {
                ranita.y_position += ranita.hitbox_height;
            }

            break;


        case RANITA_LEFT:
            if ((ranita.values.position - ranita.params.hitbox_width) < 0) //would go left from mapside
            {
                ranita.values.position = 0; //leftmost pixel for the upper left corner
            }
            else
            {
                ranita.values.position -= ranita.params.hitbox_width;
            }
            break;


        case RANITA_RIGHT:
            temp = ranita.values.position + ranita.params.hitbox_width; //right corner uppermost pixel
            if((temp + ranita.params.hitbox_width) >= LANE_X_PIXELS) //would go right from mapside
            {
                ranita.values.position = LANE_X_PIXELS - 1;
            }
            break;

        default:
            printf("Unknown direction input at triggerRanitaMovement()\n");
            break;
    }
}

/*
    @BRIEF: collisionAnalysis
        Checks if the ranita collided with something that could kill her
        end_y->|------|
                 |      |
        start_y--->|------|
        start_x->       <--end_x 
*/
static void collisionAnalysis(void)
{
    int32_t i,j,start_object_x,end_object_x,start_ranita_x,end_ranita_x,start_ranita_y,end_ranita_y;
    int32_t start_lane_y,end_lane_y;
    puts("starting collision analysis");
    //printf("ranita.y_position = %d\nranita.hitbox_height = %d\nranita.position = %d\nranita.params.hitbox_width=%d\n",ranita.y_position,ranita.hitbox_height,ranita.values.position,ranita.params.hitbox_width);
    
    start_ranita_y = ranita.y_position - ranita.hitbox_height + 1;//Porque ranita.y_position ya tienen en cuenta el primer pixel
    end_ranita_y = ranita.y_position; 
    start_ranita_x = ranita.values.position;
    end_ranita_x = ranita.values.position + ranita.params.hitbox_width - 1; //Porque position tiene en cuenta el primer pixel

    //printf("start_x_ranita = %d\nend_x_ranita = %d\nstart_y_ranita = %d\nend_y_ranita = %d\n",start_ranita_x,end_ranita_x,start_ranita_y,end_ranita_y);

    for(i=lane_bound-1;i>=0;i--)
    {
        start_lane_y = (i+1)*LANE_PIXEL_HEIGHT - 1;
        end_lane_y = (i) * LANE_PIXEL_HEIGHT;
        //printf("Analyzing lane %d:\n\tstart_lane_y = %d\n\tend_lane_y = %d\n",i,start_lane_y,end_lane_y);
        //First,analyze if the ranita is on the y coordinate capable of interacting with the lane
        if  ((start_ranita_y>= start_lane_y\
            && start_ranita_y <= end_lane_y)\
            ||
            (end_ranita_y >= start_lane_y\
            && end_ranita_y <= end_lane_y))
        {
            printf("Ranita was found to appear on lane %d\n",i);
            for(j=0;j<object_bound;j++)
            {
                if (map.lanes[i].objects->doesExist == 0) //Este objeto no existe en esta lane
                {
                    continue;
                }
                start_object_x = map.lanes[i].objects[j].position;
                end_object_x = map.lanes[i].objects[j].position + map.lanes[i].kind->hitbox_width - 1;
                //printf("Analyzing object index %d:\n\tstart_object_x = %d\n\tend_object_x = %d\n",j,start_object_x,end_object_x);
                if((start_ranita_x >= start_object_x && start_ranita_x <= end_object_x)\
                ||(end_ranita_x >= start_object_x && end_ranita_x <= end_object_x))
                {
                    printf("Collision! On lane %d, object %d\n",i,j);
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
    collisionAnalysis();
    printf("lane bound = %d\n",lane_bound);
}




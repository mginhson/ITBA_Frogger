#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <time.h>
#include "game_logic.h"
#include "../entities/entities.h"





static void updateMap(void);
static void generateNewLevel(uint32_t _level);
static const object_kind_t * collisionAnalysis(void);
static void resetRanitaPosition(void);




typedef enum{RANITA_UP,RANITA_DOWN,RANITA_LEFT,RANITA_RIGHT}ranita_logic_direction_t;
static void triggerRanitaMovement(ranita_logic_direction_t _direction);
static void triggerDeath(void);
static void gameOver(void);


static map_t map;
static uint32_t level;
static const uint32_t lane_bound = sizeof(map.lanes)/sizeof(map.lanes[0]);
static const uint32_t object_bound = sizeof(map.lanes[0].objects)/sizeof(map.lanes[0].objects[0]);


independent_object_t ranita = {
    .params = {
        .hitbox_width = LANE_X_PIXELS/12,
        .attr = {.canKill=0, .canMove=1, .isEquippable=0},
                
    }, 
    .hitbox_height = LANE_PIXEL_HEIGHT,
    .y_position = LANE_Y_PIXELS-1 - LANE_PIXEL_HEIGHT + 1,
    .values.position = 0,
    
};

/*
    @BRIEF: gameTick
    -Check if the ranita moved  
    -Update the objects on the map
    -Check for the interactions between the map and the ranita
*/
void gameTick(int32_t ms_since_last_tick)
{
    uint32_t i,j;
    static int64_t ms_cooldown=0;
    int32_t start_object_x,end_object_x;


    puts("Map before executing gameTick:\n");
    printMap(&map,0);
    ms_cooldown -= ms_since_last_tick;
    if(ms_cooldown < 0) //we can check for movement again 
    {
        ms_cooldown = 0;
        if(1) //REPLACE FOR CALLING INPUT FUNCTION
        {
            ms_cooldown = MS_RANITA_MOVEMENT_COOLDOWN;
            //Execute the movement
            //triggerRanitaMovement(RANITA_UP);
        }
    }

    
    for(i=0; i < lane_bound; i++)
    {
        int32_t a = map.lanes[i].ms_to_next;
        map.lanes[i].ms_to_next = a - ms_since_last_tick;
        //map.lanes[i].ms_to_next = map.lanes[i].ms_to_next - ms_since_last_tick;
        //printf("map.lanes[%d].ms_to_next = %d\n",i,map.lanes[i].ms_to_next);
        
        
        if(map.lanes[i].ms_to_next <= 0) //Lane should move a pixel
        {
            
            map.lanes[i].ms_to_next = map.lanes[i].ms_reload; //Reload the ms counter
            /*
                Now we will analyze if the object should move, and if it does, we have to check
                wether it went out of the lane bounds, and if so, reset it to the corresponding corner
                The .position attribute correspond to the leftmost side of an object.
            */
            
            if(map.lanes[i].kind == NULL || map.lanes[i].kind == &empty_object) //No objects in the lane!!
            {
                continue;
            }
            for(j=0; j<object_bound; ++j)
            {
                
                if(map.lanes[i].objects[j].doesExist==0)
                {
                    continue;
                }   
                

                
                
                if(map.lanes[i].direction == RIGHT) //Move every object a pixel to the right
                {
                    
                    map.lanes[i].objects[j].position += 1;
                    
                    end_object_x = map.lanes[i].objects[j].position + map.lanes[i].kind->hitbox_width - 1; //last pixel
                    
                    if (end_object_x > map.lanes[i].virtual_lane_end)
                    {
                       
                        map.lanes[i].objects[j].position = map.lanes[i].virtual_lane_start;
                       
                    }
                }
                else //map.lanes[i].direction == LEFT
                {
                    
                    map.lanes[i].objects->position -= 1;
                    
                    start_object_x = map.lanes[i].objects[j].position;
                    
                    if(start_object_x < map.lanes[i].virtual_lane_start)
                    {
                        
                        map.lanes[i].objects[j].position = map.lanes[i].virtual_lane_end - 1 - map.lanes[i].kind->hitbox_width;
                        
                    }
                }
                //printLaneObjects(&map.lanes[i],i);
            }
        }
    }

    //Now we move onto the ranita <3
    
    const object_kind_t * collision = collisionAnalysis();
    printf("collision = %p\n",collision);
    if (collision == &bus_object_kind)
    {
        
    }
    else if (collision == &car_object_kind)
    {
        
    }
    else if(collision ==  &snake_object_kind)
    {

    }   
    else    //collision == NULL, will check if won
    {
        if (ranita.y_position <= LANE_PIXEL_HEIGHT)
        {
            //llego una ranita al final
            //resetRanitaPosition();
            
        }
    }
    //renderWorld(&map, &ranita, 1, 64);
}


static void triggerRanitaMovement(ranita_logic_direction_t _direction)
{
    //REMEMBER that the position is relative to the upper left corner
    int32_t temp;
    switch(_direction)
    {
        case RANITA_DOWN:
            temp = ranita.y_position - ranita.hitbox_height + 1; //y position of the bottom
            if (temp + ranita.hitbox_height >= LANE_Y_PIXELS) //would go below map, set is as low as possible
            {
                ranita.y_position = LANE_Y_PIXELS-1-ranita.hitbox_height; //lowest pixel for the upper left corner
            }
            else
            {
                ranita.y_position += ranita.hitbox_height;
            }
            break;


        case RANITA_UP:
            if (ranita.y_position  <= 0) //would go above map
            {
                ranita.y_position = 0;//uppermost pixel for the upper left corner
            }
            else
            {
                ranita.y_position -= ranita.hitbox_height;
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
            temp = ranita.values.position + ranita.params.hitbox_width - 1; //right corner uppermost pixel
            
            if((temp + ranita.params.hitbox_width) >= LANE_X_PIXELS) //would go right from mapside
            {
                ranita.values.position = LANE_X_PIXELS - 1 - ranita.params.hitbox_width;
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
        end_y----->|------|
                   |      |
        start_y--->|------|
        start_x--->        <--end_x 
*/
static const object_kind_t * collisionAnalysis(void)
{
    int32_t i,j,start_object_x,end_object_x,start_ranita_x,end_ranita_x,start_ranita_y,end_ranita_y;
    int32_t start_lane_y,end_lane_y;
    //puts("starting collision analysis");
    printf("ranita.y_position = %d\nranita.hitbox_height = %d\nranita.position = %d\nranita.params.hitbox_width=%d\n\n",ranita.y_position,ranita.hitbox_height,ranita.values.position,ranita.params.hitbox_width);
    
    start_ranita_y = ranita.y_position - ranita.hitbox_height + 1;//Porque ranita.y_position ya tienen en cuenta el primer pixel
    end_ranita_y = ranita.y_position; 
    start_ranita_x = ranita.values.position;
    end_ranita_x = ranita.values.position + ranita.params.hitbox_width - 1; //Porque position tiene en cuenta el primer pixel

    //printf("start_x_ranita = %d\nend_x_ranita = %d\nstart_y_ranita = %d\nend_y_ranita = %d\n",start_ranita_x,end_ranita_x,start_ranita_y,end_ranita_y);

    for(i=lane_bound-1;i>=0;i--)
    {
        if (map.lanes[i].kind == NULL || map.lanes[i].kind == &empty_object)
        {
            continue;
        }
        end_lane_y = (i+1)*LANE_PIXEL_HEIGHT - 1;
        start_lane_y = (i) * LANE_PIXEL_HEIGHT;
        //printf("Analyzing lane %d:\n\tstart_lane_y = %d\n\tend_lane_y = %d\n",i,start_lane_y,end_lane_y);
        //First,analyze if the ranita is on the y coordinate capable of interacting with the lane
        if  ((start_ranita_y>= start_lane_y\
            && start_ranita_y <= end_lane_y)\
            ||
            (end_ranita_y >= start_lane_y\
            && end_ranita_y <= end_lane_y))
        {
            //printf("Ranita was found to appear on lane %d\n",i);
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
                    //printf("Collision! On lane %d, .kind = %p\n",i,map.lanes[i].kind);
                    return map.lanes[i].kind;
                }    
            }
        }
    }
    //If no collision found, return NULLPTR

    return NULL;
}

/*
    @BRIEF: triggerDeath:
        - Trigger death animation
        - Check if there are remaining lives
        - If there are, restart the ranita at starting position
        - Else, game ends there.
*/
static void triggerDeath(void)
{

}



static void resetRanitaPosition(void)
{
    ranita.y_position = LANE_Y_PIXELS - 1 - ranita.hitbox_height + 1;
    ranita.values.position = LANE_X_PIXELS / 2;
}

void initializeGameLogic(void)
{
    srand(time(NULL));
    level = 0;
    fillMap(&map,level);
    printf("lane bound = %d\n",lane_bound);
}






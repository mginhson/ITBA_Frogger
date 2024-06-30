#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include "entities.h"


const object_kind_t empty_object={
    .hitbox_width = 0,
};

const object_kind_t bus_object_kind = {
    .hitbox_width=10,
    .attr = {.canKill = 1, .isEquippable = 0},
};

const object_kind_t small_log_object_kind={
    
};

const object_kind_t normal_log_object_kind = {

};

const object_kind_t big_log_object_kind = {

};


#if defined(PC)
    static const lane_t road_arquetypes[] = 
    {
        [0]=
        {
            .direction = RIGHT,
            .kind = &bus_object_kind,
            .background = road,
            .objects =
            {
                {.position=0},
                {.position=LANE_X_PIXELS/2},
            }
            
        },
         
    };

    static const lane_t water_arquetypes[] = {
        [0] = 
        {
            .background = water,
            .kind = &normal_log_object_kind,
            .objects = {
                [0]={.doesExist=1,.position=0},
            }

        },
    };

    static const lane_t grass_arquetypes[] = 
    {
        [0] = 
        {
            .background = grass,
            .kind = &bus_object_kind, //no enemies
            .direction = RIGHT,
            .objects = {{0,.doesExist=1},{1,.doesExist=1},{2,.doesExist=1},{3,.doesExist=1},{4,.doesExist=1}},

        }
    };


    static const lane_t finish_line_arquetypes[] = 
    {
        [0] = 
        {
            .background = finish_line,
            .kind = NULL,
            
        }
    };
//________________________________________________________________
#elif defined(RPI)

#endif

static const uint32_t water_arquetypes_elements = sizeof(water_arquetypes)/sizeof(*water_arquetypes);
static const uint32_t road_arquetypes_elements = sizeof(road_arquetypes)/sizeof(*road_arquetypes);
static const uint32_t grass_arquetypes_elements = sizeof(grass_arquetypes) / sizeof(*grass_arquetypes);
static const uint32_t finish_line_arquetypes_elements = sizeof(finish_line_arquetypes)/sizeof(*finish_line_arquetypes);


/*
    C is awesome
    1:09:35 explains why this syntax works
    https://www.youtube.com/watch?v=443UNeGrFoM&t=2328s&ab_channel=EskilSteenberg
*/
static const uint32_t lane_bound = sizeof(((map_t*)NULL)->lanes) /sizeof( *(((map_t*)NULL)->lanes));
static const uint32_t object_bound = sizeof(((lane_t*)NULL)->objects) / sizeof(((lane_t*)NULL)->objects[0]);
static void printLane(lane_t * _lane);



int32_t fillMap(map_t *_map, uint32_t _level)
{
    uint32_t i;
    
    //printf("lane bound on fill map = %d\n",lane_bound);
    //printf("Available Arquetypes Element:\n\troad: %d\n\tgrass: %d\n\twater: %d\n\tfinish_line: %d\n\n"
    //,road_arquetypes_elements,grass_arquetypes_elements,water_arquetypes_elements,finish_line_arquetypes_elements);

    //Difficulty can be fine tuned here, by choosing harder arquetypes and modifying the .ms_reload
    for (i=0; i < lane_bound; i++)
    {

        switch(i)
        {
            case 0: //finish line
                _map->lanes[i] = finish_line_arquetypes[rand() % finish_line_arquetypes_elements];
                break;

            case 1:
            case 2:
            case 3:
                _map->lanes[i] = water_arquetypes[rand() % water_arquetypes_elements];
                break;

            case 4:
                _map->lanes[i] = grass_arquetypes[rand() % grass_arquetypes_elements];
                break;

            case 5:
            case 6:
            case 7:
            case 8:
            case 9:
            case 10:
            case 11:
            case 12:
            case 13:
            case 14:
                _map->lanes[i] = road_arquetypes[rand() % road_arquetypes_elements];
                break;
            case LANES_COUNT-1:
                _map->lanes[i] = grass_arquetypes[rand() % grass_arquetypes_elements];
                break;


            default:
                printf("Couldn't find an arquetype for lane %d, defaulting to enemyless grass\n",i);
                _map->lanes[i] = grass_arquetypes[rand() % grass_arquetypes_elements];
                break;
        }
        _map->lanes[i].virtual_lane_start = 0;
        _map->lanes[i].ms_to_next= 10;
        _map->lanes[i].ms_reload = 10;
        _map->lanes[i].virtual_lane_end =LANE_X_PIXELS; //CAMBIAR ESTO, DEBERIA SER CONST Y PREDEFINIDO EN PATRON
    }
    //printMap(_map);
    return 0;
}


void printLaneObjects(lane_t *_lane,int32_t index)
{
    int32_t i;
    for (i=0;i<MAX_OBJECTS_PER_LANE;i++)
    {
        printf("lane[%d] object[%d]:\n\tposition = %d\n",index,i,_lane->objects[i].position);
    }
}


void printMap(map_t *_map,int32_t a)
{
    int32_t i,j;
    if(a) //print constant lane attributes
    {
        for(i=0; i < lane_bound;i++)
        {
            printf("Lane %d:\n",i);
            printLane(&(_map->lanes[i]));
            printf("\n");
        }
    }
    else //Print objects;
    {
        printf("Map settings:\n\tLANE_X_PIXELS = %d\n\n",LANE_X_PIXELS);
        for(i=0; i < lane_bound;i++)
        {
            printf("Lane %d:\n",i);
            for(j=0; j < object_bound;j++)
            {
                if(_map->lanes[i].objects[j].doesExist == 1)
                {
                    printf("\tObject %d: %d\n",j,_map->lanes[i].objects[j].position);
                }
            }
        }
    }
    
}


static void printLane(lane_t * _lane)
{
    static char * background_string[]=
    {[water] = "water",[road] = "road",[grass] = "grass",[finish_line]="finish_line"}; 
    
    printf("\tbackground: %s\n\t.kind points to %p\n",background_string[_lane->background],_lane->kind);
    
}




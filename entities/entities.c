#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include "entities.h"

const object_kind_t _empty_object_kind
const object_kind_t bus_object_kind = {
    .hitbox_width=LANE_X_PIXELS / 16,
    .attr = {.canKill = 1, .isEquippable = 0},
};



const lane_t road_arquetype[] = 
{
    [0]=
    {
        
        .kind = &bus_object,
        .background = road,
        .objects =
        {
            {.position=0},
            {.position=LANE_X_PIXELS/2},
        }
    },
    [1]=
    {
        .background = road,
        .objects = {}
    }
};


int32_t fillMap(map_t *_mat, uint32_t _level)
{
    return 0;
}


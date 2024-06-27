#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include "entities.h"

const object_kind_t bus_object = {
    .hitbox_width=LANE_X_PIXELS / 16,
    .attr = {.canKill = 1, .isEquippable = 0},
};

const object_kind_t ranita = {
    .hitbox_width = LANE_X_PIXELS/16,
    .attr = {.canKill=0, .canMove=1, .isEquippable=0},
    
};

const lane_t road_arquetype[] = 
{
    [0]=
    {
        .background = road,
        .objects =
        {
            {.position=0},
            {.position=LANE_X_PIXELS/2},
        }
    }
};
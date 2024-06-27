#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include "entities.h"

const object_t car_object = {
    .hitbox_width=LANE_X_PIXELS / 16,
    .attr = {.canKill = 1, .isEquippable = 0},
};
#ifndef ENTITIES_H
#define ENTITIES_H
#include <stdint.h>
#include "../allegro/assets.h"
#include "../config.h"

#define LANE_ARQUETYPE_PIXELS ((LANE_X_PIXELS) * 3)

typedef struct {
    char is_animating;
    assets_t * animation_frame;
} animation_t;



typedef struct{

}object_graphics_t;

typedef struct{
    uint32_t canKill :1;
    uint32_t isEquippable :1;
    uint32_t canMove :1;
}object_attributes_t;

typedef struct{
    const object_graphics_t graphics;
    const object_attributes_t attr;
    const uint32_t hitbox_width; //From left side
}object_kind_t;


typedef struct{
    uint32_t position;
    animation_t animation;
}object_t;

typedef struct{
    object_kind_t params;
    object_t values;
}independent_object_t;

typedef enum{
    water,
    road,
    grass,
}background_t;

typedef struct{
    int32_t ms_to_next;
    int32_t ms_reload;
    background_t background;
    const object_kind_t * kind;
    const uint32_t virtual_lane_length;
    object_t objects[MAX_OBJECTS_PER_LANE];
}lane_t;

typedef struct{
    lane_t lanes[LANES_COUNT];
}map_t;


int32_t fillMap(map_t *_map,uint32_t _level);

#endif

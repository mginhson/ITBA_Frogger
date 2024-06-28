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
    const uint32_t hitbox_width; //From left side, should correspond with graphics width!!!
}object_kind_t;


typedef struct{
    int32_t position;
    animation_t animation;
    uint32_t doesExist :1;
}object_t;

typedef struct{
    object_kind_t params;
    object_t values;
}independent_object_t;

typedef enum{
    water,
    road,
    grass,
    finish_line,
}background_t;

typedef struct{
    int32_t ms_to_next; //Internal counter to know when to move
    int32_t ms_reload;  //ms per movement
    background_t background; //background
    object_kind_t * kind; //all dependant objects on the lane are of the same kind
    uint32_t virtual_lane_length; //True logic lane lenght, DOESN'T correspond to visible lane length in-game
    object_t objects[MAX_OBJECTS_PER_LANE]; //every dependant object variable data
    enum{LEFT,RIGHT}direction; //Direction of movement of the lane, either LEFT or RIGHT
}lane_t;

typedef struct{
    lane_t lanes[LANES_COUNT];
}map_t;


int32_t fillMap(map_t *_map,uint32_t _level);
void printMap(map_t *_map);
#endif

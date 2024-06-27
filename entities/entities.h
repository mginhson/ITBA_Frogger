#ifndef ENTITIES_H
#define ENTITIES_H
#include <stdint.h>
#include "../allegro/assets.h"
#include "../config.h"


typedef struct {
    char is_animating;
    assets_t * animation_frame;
} animation_t;



typedef struct{

}object_graphics_t;

typedef struct{
    uint32_t canKill :1;
    uint32_t isEquippable :1;

}object_attributes_t;

typedef struct{
    object_graphics_t graphics;
    object_attributes_t attr;
    uint32_t hitbox_width; //From left side
    uint32_t position;
}object_t;


typedef struct{
    object_t * objects;
}lane_t;

typedef struct{


}map_t;

#endif

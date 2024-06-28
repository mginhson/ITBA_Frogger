#ifndef CONFIG_H
#define CONFIG_H


#define LANES_COUNT 16
#define MAX_OBJECTS_PER_LANE 5
#define PC

#if defined(PC)
    #define LANE_X_PIXELS 1000
    #define LANE_Y_PIXELS 1000
    #define MS_RANITA_MOVEMENT_COOLDOWN 100

#elif RPI
    #define LANE_X_PIXELS 16
    #define LANE_Y_PIXELS 1

#else
    #error "No platform defined"
#endif

#define LANE_PIXEL_HEIGHT (LANE_Y_PIXELS/LANES_COUNT)

#endif
#ifndef CONFIG_H
#define CONFIG_H



#if !defined(PC) && !defined(RPI)
    #define PC
#endif

#if defined(PC)
    #define LANE_X_PIXELS 1000
    #define LANE_Y_PIXELS 1000
    #define MS_RANITA_MOVEMENT_COOLDOWN 100

#elif RPI
    #define LANE_X_PIXELS 16
    #define LANE_Y_PIXELS 12
    #define MS_RANITA_MOVEMENT_COOLDOWN 100

#else
    #error "No platform defined"
#endif


#define LANES_COUNT 16
#define MAX_OBJECTS_PER_LANE 5
#define LANE_PIXEL_HEIGHT (LANE_Y_PIXELS/LANES_COUNT)

#endif
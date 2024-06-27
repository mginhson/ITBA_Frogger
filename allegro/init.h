#ifndef IN_ALLEGRO
#define IN_ALLEGRO
#include "assets.h"
#include <allegro5/allegro5.h>
#include <allegro5/allegro_font.h>

#define RIVER_COLOR (al_map_rgb(2, 11, 88))
#define BOTTOM_SIZE 32
#define TOTAL_ROWS 16
#define TOTAL_COLUMNS 12
#define TOTAL_WIDTH (REZISE(TOTAL_COLUMNS* NORMAL_SIZE))
#define TOTAL_HEIGHT (REZISE(BOTTOM_SIZE + SHORT_SIZE + TOTAL_ROWS * NORMAL_SIZE))


/*
    Estructura que guarda la información general del juego al renderizar.
 */
typedef struct {
    ALLEGRO_TIMER*timer;
    ALLEGRO_EVENT_QUEUE* queue;
    ALLEGRO_DISPLAY* disp;
    char redraw;
    ALLEGRO_EVENT event;
    ALLEGRO_BITMAP* bitmap;
} g_info_t;

g_info_t *init_allegro(void);
void destroy_allegro(g_info_t * g_info);
void load_assets(g_info_t *g_info);
#endif
#ifndef MENU
#define MENU
#include "init.h"
#include "assets.h"

#define FONT_TITLE_SIZE 50
void draw_menu(g_info_t *g_info, assets_t* frog_font, assets_t *wall_assets, assets_t *street_assets, assets_t * font);
void sprite_to_text(char * str, g_info_t * g_info,assets_t * font, float x, float y, float font_size);
void set_background(g_info_t *g_info, assets_t * wall_assets, assets_t * street_asset);
void set_title(assets_t *title_font, g_info_t* g_info,float x, float y);
void draw_street_line(g_info_t * g_info, assets_t * street_assets, float y);
#endif
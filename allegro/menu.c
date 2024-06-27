#include <allegro5/allegro5.h>
#include <allegro5/allegro_image.h>
#include <allegro5/allegro_primitives.h>
#include "assets.h"
#include "init.h"
#include "menu.h"
#include <string.h>
#include <stdio.h>
#define IS_NUMBER(x) ((x) <= '9' && (x) >= '0')
#define IS_LETTER(x) (((x) <= 'z' && (x) >= 'a') || ((x) <= 'Z' && (x) >= 'A'))
void draw_menu(g_info_t *g_info, assets_t* frog_font, assets_t *wall_assets, assets_t *street_assets, assets_t *font){
    set_background(g_info, wall_assets, street_assets);
    // Ponemos el titulo
    set_title(frog_font, g_info, TOTAL_WIDTH / 2. - 3.5 * FONT_TITLE_SIZE, TOTAL_HEIGHT/6);
    sprite_to_text("Play", g_info, font, TOTAL_WIDTH/2,REZISE(WALL_SIZE + 9.5*NORMAL_SIZE) ,REZISE(8));
    sprite_to_text("Highscores", g_info, font, TOTAL_WIDTH/2,REZISE(WALL_SIZE + 10.75*NORMAL_SIZE) ,REZISE(8));
    sprite_to_text("Quit Game", g_info, font, TOTAL_WIDTH/2,REZISE(WALL_SIZE + 12.*NORMAL_SIZE) ,REZISE(8));
}
// Escribe texto y letras en minusculas o mayusculas siempre centrado
void sprite_to_text(char * str, g_info_t * g_info,assets_t * font, float x, float y, float font_size){
    x -= (strlen(str) * REZISE(SHORT_SIZE)) / 2;

    int i;
    for (i = 0; str[i] != '\0'; i++){
        int j;
        if (IS_NUMBER(str[i])){
            j = str[i] - '0';
            al_draw_scaled_bitmap(g_info->bitmap, font[j].sx, font[j].sy, font[j].sw, font[j].sh, x + font_size * i, y, font_size, font_size, 0);
        } else if (IS_LETTER(str[i])){
            // Sumamos 9 ya que las letras empiezan a partir del 9
            if (str[i] < 'a'){
                j = str[i] + '9' - '0' - 'A' + 1;
            } else {
                j = str[i] + '9' - '0' - 'a' + 1;         
            }
            al_draw_scaled_bitmap(g_info->bitmap, font[j].sx, font[j].sy, font[j].sw, font[j].sh, x + font_size * i, y, font_size, font_size, 0);
        } 
        // Cualquier cosa que no se pueda escribir, se tomara como un espacio ' '
        
        
    }
    return;
}
void set_title(assets_t *title_font, g_info_t* g_info,float x, float y){
    al_draw_scaled_bitmap(g_info->bitmap, title_font[frog_f].sx, title_font[frog_f].sy, title_font[frog_f].sw, title_font[frog_f].sh, x + 0 * FONT_TITLE_SIZE, y, FONT_TITLE_SIZE, FONT_TITLE_SIZE, 0);
    al_draw_scaled_bitmap(g_info->bitmap, title_font[frog_r].sx, title_font[frog_r].sy, title_font[frog_r].sw, title_font[frog_r].sh, x + 1 * FONT_TITLE_SIZE, y, FONT_TITLE_SIZE, FONT_TITLE_SIZE, 0);
    al_draw_scaled_bitmap(g_info->bitmap, title_font[frog_o].sx, title_font[frog_o].sy, title_font[frog_o].sw, title_font[frog_o].sh, x + 2 * FONT_TITLE_SIZE, y, FONT_TITLE_SIZE, FONT_TITLE_SIZE, 0);
    al_draw_scaled_bitmap(g_info->bitmap, title_font[frog_g].sx, title_font[frog_g].sy, title_font[frog_g].sw, title_font[frog_g].sh, x + 3 * FONT_TITLE_SIZE, y, FONT_TITLE_SIZE, FONT_TITLE_SIZE, 0);
    al_draw_scaled_bitmap(g_info->bitmap, title_font[frog_g].sx, title_font[frog_g].sy, title_font[frog_g].sw, title_font[frog_g].sh, x + 4 * FONT_TITLE_SIZE, y, FONT_TITLE_SIZE, FONT_TITLE_SIZE, 0);
    al_draw_scaled_bitmap(g_info->bitmap, title_font[frog_e].sx, title_font[frog_g].sy, title_font[frog_e].sw, title_font[frog_e].sh, x + 5 * FONT_TITLE_SIZE, y, FONT_TITLE_SIZE, FONT_TITLE_SIZE, 0);
    al_draw_scaled_bitmap(g_info->bitmap, title_font[frog_r].sx, title_font[frog_g].sy, title_font[frog_r].sw, title_font[frog_r].sh, x + 6 * FONT_TITLE_SIZE, y, FONT_TITLE_SIZE, FONT_TITLE_SIZE, 0);
}

void set_background(g_info_t *g_info, assets_t * wall_assets, assets_t * street_asset){
    int i;
    al_draw_filled_rectangle(0, 0, TOTAL_WIDTH, REZISE(WALL_SIZE + 7 * NORMAL_SIZE + 2), RIVER_COLOR);
    for (i = 0; i* REZISE((BIG_SIZE + SHORT_SIZE)) < TOTAL_WIDTH; i++){
        float sxb = wall_assets[big_wall].sx;
        float syb = wall_assets[big_wall].sy;
        float swb = wall_assets[big_wall].sw;
        float shb = wall_assets[big_wall].sh;
        float dwb = REZISE(swb);
        float dhb = REZISE(shb);

        float sxs = wall_assets[small_wall].sx;
        float sys = wall_assets[small_wall].sy;
        float sws = wall_assets[small_wall].sw;
        float shs = wall_assets[small_wall].sh;
        float dws = REZISE(sws);
        float dhs = REZISE(shs);

        float dxb = (dws + dwb) * i;
        float dyb = 0;

        float dxs = (dws + dwb) * i + dwb;
        float dys = 0;

        al_draw_scaled_bitmap(g_info->bitmap,sxb,syb ,swb ,shb, dxb, dyb, dwb, dhb, 0);
        al_draw_scaled_bitmap(g_info->bitmap, sxs, sys, sws, shs, dxs, dys, dws, dhs, 0);
    }
    draw_street_line(g_info, street_asset, REZISE(WALL_SIZE + 7 * NORMAL_SIZE));
    draw_street_line(g_info, street_asset, REZISE(WALL_SIZE + 14 * NORMAL_SIZE));
    return;
}
void draw_street_line(g_info_t * g_info, assets_t * street_assets, float y){
    int i;
    for (i = 0; i * REZISE(NORMAL_SIZE) < TOTAL_WIDTH; i++){
        float sx = street_assets->sx;
        float sy = street_assets->sy;
        float sw = street_assets->sw;
        float sh = street_assets->sh;

        float dw = REZISE(sw);
        float dh = REZISE(sh);
        float dy = y;
        float dx = i * dw;
        al_draw_scaled_bitmap(g_info->bitmap, sx, sy, sw, sh, dx, dy, dw, dh, 0);
    }
    return;

}
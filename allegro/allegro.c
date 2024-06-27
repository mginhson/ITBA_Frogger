#include <stdio.h>
#include <allegro5/allegro5.h>
#include <allegro5/allegro_font.h>
#include "assets.h"
#include "init.h"
#include "menu.h"

int main(void){
    assets_t * red_font = get_chars_assets('r');
    assets_t * frog_font = get_frog_chars_assets();
    assets_t * wall_assets = get_wall_assets();
    assets_t * special_assets = get_special_assets();
    assets_t * yellow_font = get_chars_assets('y');

    g_info_t *g_info = init_allegro();
    if (g_info == NULL){
        printf("No se pudo cargar las imagenes");
        return 0;
    }
    //load_assets(g_info);
    //assets_t* frog_assets = get_special_assets();
    int i = 0;
    while (1){
        al_wait_for_event(g_info->queue, &(g_info->event));
        if((g_info->event.type == ALLEGRO_EVENT_DISPLAY_CLOSE)){
            printf("Salimos\n");
            break; 
        }
        //sprite_to_text("HoLa MUNDI", g_info, red_font, 20, 20, 34);
        //set_title(frog_font, g_info, TOTAL_WIDTH / 2. - 3.5 * FONT_TITLE_SIZE, TOTAL_HEIGHT/6);
        draw_menu(g_info, frog_font, wall_assets, &(special_assets[street]), yellow_font);
        al_flip_display();
    }
    free(red_font);
    destroy_allegro(g_info);
    return 0;
}
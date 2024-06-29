#include <allegro5/allegro.h>
#include "init.h"
#include "assets.h"
#include "components/text.h"
#include "pause.h"
#include <stdio.h>
int pause(void){
    al_clear_to_color(al_map_rgb(0, 0 ,0));
    assets_t * violet_font = get_chars_assets('v');
    assets_t * blue_font = get_chars_assets('b');
    
    text_t * pause_text = create_text("PAUSA", &general_information, violet_font,TOTAL_WIDTH / 2 ,ROW(2), 55, CENTERED);
    text_t * continue_text = create_text("CONTINUE", &general_information, blue_font, TOTAL_WIDTH/2, ROW(5), 30, CENTERED);
    text_t * restart_text = create_text("RESTART", &general_information, blue_font, TOTAL_WIDTH/2, ROW(7), 30, CENTERED);
    text_t * menu_text = create_text("MENU", &general_information, blue_font, TOTAL_WIDTH/2, ROW(9), 30, CENTERED);
    text_t * quit_text = create_text("QUIT GAME", &general_information, blue_font, TOTAL_WIDTH/2, ROW(11), 30, CENTERED);    
    
    draw_text(continue_text);
    draw_text(restart_text);
    draw_text(menu_text);
    draw_text(quit_text);
    draw_text(pause_text);
    ALLEGRO_EVENT event_capture;
    al_flip_display();
    int return_value = 0;
    while (!return_value){
    // Leemos todos los eventos de la lista de espera
    al_wait_for_event(general_information.queue, &event_capture);
    
        switch (event_capture.type){
                    // En el caso de que hayamos hecho click, debemos ver si fue en alguno de los textos.
            case ALLEGRO_EVENT_MOUSE_BUTTON_DOWN:{
                printf("Click on Pause\n");
                if (text_was_selected(menu_text, event_capture.mouse.x, event_capture.mouse.y)){
                    return_value = MENU;
                } else if (text_was_selected(continue_text, event_capture.mouse.x, event_capture.mouse.y)){
                    return_value = CONTINUE;
                } else if (text_was_selected(quit_text, event_capture.mouse.x, event_capture.mouse.y)){
                    return_value = QUIT;
                } else if (text_was_selected(restart_text, event_capture.mouse.x, event_capture.mouse.y)){
                    return_value = RESTART; 
                }
                        
                break;
            }
            default:{
                break;
            }
                    
        }
    }

    free(pause_text);
    free(continue_text);
    free(quit_text);
    free(restart_text);
    free(menu_text);
    return return_value;
}
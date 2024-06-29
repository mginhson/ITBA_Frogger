#include "highscore.h"
#include "assets.h"
#include "util.h"
#include "init.h"
#include "components/text.h"
#include <allegro5/allegro5.h>
#include <stdio.h>

void topTen(bestPlayers_t bestPlayers){
    // Cargo la fuente amarilla y roja
    
    al_clear_to_color(al_map_rgb(0, 0, 0));
    assets_t *yellow_font = get_chars_assets('y');
    assets_t *red_font = get_chars_assets('r');
    // Escribo el titulo de top 10
    

        // Bucle for mostrando cada jugador y su respectivo puntaje
    int i;
    text_t *texts[25];
    for (i=0; i < TOP_10 && (bestPlayers.name)[i] != NULL; i++){
        
        texts[i*2] = create_text((bestPlayers.name)[i], &general_information, yellow_font,TOTAL_WIDTH * (1./4),ROW(i + 4), REZISE(SHORT_SIZE),CENTERED);
        texts[i *2 + 1] = create_text((bestPlayers.puntajes)[i], &general_information, red_font,TOTAL_WIDTH * (3/4.),ROW(i + 4), REZISE(SHORT_SIZE), CENTERED);

    }
    i *= 2;
    texts[i++] = create_text("Nombre", &general_information, yellow_font, TOTAL_WIDTH * (1./4),ROW(3),  REZISE(SHORT_SIZE),CENTERED);
    texts[i++] = create_text("Puntaje", &general_information, red_font, TOTAL_WIDTH * (3/4.), ROW(3) , REZISE(SHORT_SIZE), CENTERED);
    texts[i++] = create_text("Top 10", &general_information, yellow_font, TOTAL_WIDTH/2, ROW(1), REZISE(NORMAL_SIZE), CENTERED);
    text_t *back_to_menu = create_text("BACK TO MENU", &general_information, yellow_font, TOTAL_WIDTH/2, ROW(15) ,REZISE(8), CENTERED);
    texts[i++] = back_to_menu;
    texts[i++] = NULL;
    
    
    int return_value = 0;
    
    for (i = 0; texts[i] != NULL;i++){
        draw_text(texts[i]);
    }
    al_flip_display();
    ALLEGRO_EVENT event_capture;
    while (!return_value){
        // Leemos todos los eventos de la lista de espera
        al_wait_for_event(general_information.queue, &event_capture);
            // Leemos uno de los eventos de la lista de espera y lo guardamos en la variable event_capture
        switch (event_capture.type){
                    // En el caso de que hayamos hecho click, debemos ver si fue en alguno de los textos.
            case ALLEGRO_EVENT_MOUSE_BUTTON_DOWN:{
                    printf("Catch\n");
                if (text_was_selected(back_to_menu, event_capture.mouse.x, event_capture.mouse.y)){
                    return_value = 1;
                }                        
                break;
            }
            default:{
                break;
            }
                
            
        }
    }
    for (i = 0; texts[i] != NULL ;i++){
        free(texts[i]);
    }
    free(yellow_font);
    free(red_font);
    
    return;
}
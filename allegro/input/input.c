#include "input.h"
#include "../init.h"
#include <allegro5/allegro5.h>
int input_reader(void){
    int return_value = EMPTY;
    ALLEGRO_EVENT event_capture;
    while(al_is_event_queue_empty(general_information.queue) && return_value == 0){
        al_get_next_event(general_information.queue, &event_capture);
        switch (event_capture.type){
            case ALLEGRO_EVENT_KEY_DOWN:{
                switch (event_capture.keyboard.keycode){
                    case ALLEGRO_KEY_W:
                    case ALLEGRO_KEY_UP:{
                        return_value = UP;
                        break;
                    }
                    case ALLEGRO_KEY_S:
                    case ALLEGRO_KEY_DOWN:{
                        return_value = DOWN;
                        break;
                    }
                    case ALLEGRO_KEY_A:
                    case ALLEGRO_KEY_LEFT:{
                        return_value = LEFT;
                        break;
                    }
                    case ALLEGRO_KEY_D:
                    case ALLEGRO_KEY_RIGHT:{
                        return_value = RIGHT;
                        break;
                    }
                    case ALLEGRO_KEY_SPACE:{
                        return_value = PAUSE;
                    }
                }
                break;
            }
            // case para mause en caso de tocar boton de pausa
        }
    }   
    return return_value; 
}
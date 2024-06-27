#include "init.h"
#include <stdlib.h>
#include <allegro5/allegro5.h>
#include <allegro5/allegro_image.h>
#include <stdio.h>
#include <allegro5/allegro_primitives.h>
// Funcion que incializa allegro
g_info_t * init_allegro(void){
    // Inicialización de allegro
    al_init();
    // Instalación del teclado
    al_install_keyboard();
    // Inicialización de la libreria para imagenes
    al_init_image_addon();

    al_init_primitives_addon();
    // Creación del timer
    ALLEGRO_TIMER* timer = al_create_timer(1.0 / 30.0);
    // Creación de una cola de eventos
    ALLEGRO_EVENT_QUEUE* queue = al_create_event_queue();
    // Creación de un display
    
    ALLEGRO_DISPLAY* disp = al_create_display(TOTAL_WIDTH, TOTAL_HEIGHT);
    
    // Registramos los eventos de teclado, display y timer
    al_register_event_source(queue, al_get_keyboard_event_source());
    al_register_event_source(queue, al_get_display_event_source(disp));
    al_register_event_source(queue, al_get_timer_event_source(timer));
    // Guardamos la información en una variable global
    // Al crear una instancia de g_info_t, automaticamente se crea un ALLEGRO_EVENT
    g_info_t * g_info = malloc(sizeof(g_info_t));
    
    g_info->timer = timer;
    g_info->queue = queue;
    g_info->disp = disp;
    // Empieza a correr el timer
    al_start_timer(g_info->timer);
    g_info->bitmap =  al_load_bitmap("assets.png");
    if ((g_info->bitmap) == NULL){
        free(g_info);
        return NULL;
    }

    return g_info;
}
// Funcion que cierra allegro
void destroy_allegro(g_info_t* g_info){
   // al_destroy_font(g_info->font);
    al_destroy_display(g_info->disp);
    al_destroy_timer(g_info->timer);
    al_destroy_event_queue(g_info->queue);
    al_destroy_bitmap(g_info->bitmap);
    
    free(g_info);
}
void load_assets(g_info_t *g_info){
    al_draw_scaled_bitmap(g_info->bitmap,1, 1, 16, 16, 10, 10, 120, 120, 0);
    al_flip_display();
}
int get_event(){
    return 1;
}
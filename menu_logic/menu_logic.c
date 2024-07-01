#include <stdio.h>
#include "menu_logic.h"
#include "../menus/menu.h"
#include "../menus/top.h"
#include "../menus/pause.h"

void menu_1 (int option){
    
    switch (option){
        case START:
            while(1)
            {   
                gameTick(10);
                usleep(100000);
            }
            break;
        case TOP:
            topTen ();
            open_menu_1 ();
            break;
        case END:
            end_game();
            break;
    }

}


void menu_2 (int option){
    
    switch (option){
        case CONTINUE:
            resume_game_logic ();
            break;
        case RESTART:
            start_game_logic ();
            break;
        case QUIT:
            open_menu_1();
            break;
    }

}


void open_menu_1 (void){
    int option = menu(); // Funcion de Wainer y Sosa que me entrega que se oprime en el menu principal
    
    if (option){                    // Si recibo una opcion != 0 (osea que se oprimio una opcion)
        menu_1 (option);
    }
}


void open_menu_2 (void){
    int option = pause ();     // Funcion de Wainer y Sosa que me entrega que se oprime en el menu de pausa

    if (option){            // Si recibo una opcion != 0 (osea que se oprimio una opcion)
        menu_2 (option);
    }
}
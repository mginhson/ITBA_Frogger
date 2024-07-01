#include <stdio.h>

void menu_1 (int option){
    
    enum options_principal {START = 1, TOP, END};      //Wainer y Sosa hacen el enum y yo lo incluyo (en menu.h)
    
    switch (option){
        case START:
            start_game_logic ();
            break;
        case TOP:
            show_scores ();
            int back = top_going_back();
            if (back){
                open_menu_1;
            }
            break;
        case END:
            end_game();
            break;
    }

}


void menu_2 (int option){
    
    enum options_secundario {RESUME = 1, RESTART, QUIT};     // Wainer y Sosa hacen el enum y yo lo incluyo
    
    switch (option){
        case RESUME:
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
    show_menu_1; // Funcion de Wainer y Sosa que abre el menu principal
    int option = menu; // Funcion de Wainer y Sosa que me entrega que se oprime en el menu principal
    
    if (option){                    // Si recibo una opcion != 0 (osea que se oprimio una opcion)
        menu_1 (option);
    }
}


void open_menu_2 (void){
    show_menu_2;    // Funcion de Wainer y Sosa que abre el menu de pausa
    int option = pause;     // Funcion de Wainer y Sosa que me entrega que se oprime en el menu de pausa

    if (option){            // Si recibo una opcion != 0 (osea que se oprimio una opcion)
        menu_2 (option);
    }
}
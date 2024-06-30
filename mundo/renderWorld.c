#include "../driv/disdrv.h"
#include "../driv/formas.h"

#include "renderWorld.h"

#define OFFSET(v) (11 - v)
#define OFFSET_y(v) (15 - v)
#define COORDENADA(x,y) ((dcoord_t) {x, y})

#define DIVISOR 4

int contador = 0;
int flag_parpadeo = 1;

void renderWorld (map_t * map, independent_object_t * frog[], int size,int tiempo){
    disp_clear();
    if (tiempo % DIVISOR == 0 && contador < 15){
        contador++;
    }
    verticalLine(OFFSET_y(contador) + 1, COORDENADA(0, contador));
    verticalLine(OFFSET_y(contador) + 1, COORDENADA(15, contador));
    
    int aux, existe, position;

    for(int row = 0; row < 15; row++){
        // TAMAÑO DEL OBJETO SI ES QUE LO HAY
        existe = ((map->lanes)->objects)->doesExist;
        position = ((map->lanes)->objects)->position;
        if(existe){
            aux = map->lanes[row].kind->hitbox_width;
        }
        switch ((map->lanes[row]).background){
            case water:
                horizontalLine(12,COORDENADA(2, OFFSET_y(row)));
                if(existe && OFFSET(position) < 12){
                    if(aux + position < 11){
                        horizontalLineOff(aux, COORDENADA(OFFSET(position) + 2, OFFSET_y(row)));
                    }else{
                        horizontalLineOff(12 - position, COORDENADA(OFFSET(position) + 2, OFFSET_y(row)));
                    }
                }
                break;
            default: // no importa que sea pasto o calle
                if(existe && OFFSET(position) < 12){
                    if(aux + position < 11){
                        horizontalLine(aux, COORDENADA(OFFSET(position) + 2, OFFSET_y(row)));
                    }else{
                        horizontalLine(12 - position, COORDENADA(OFFSET(position) + 2, OFFSET_y(row)));
                    }
                    
                }
                break;
        }
    }
   for(int i = 0; i < size; i++){
        if(flag_parpadeo){
            disp_write((dcoord_t) {OFFSET(frog[i]->values.position), frog[i]->y_position}, D_ON);
        }
        flag_parpadeo = !flag_parpadeo;
    } 
   
    

    disp_update();
}
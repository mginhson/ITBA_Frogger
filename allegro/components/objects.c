#include "../assets.h"
#include <stdlib.h>
#include <allegro5/allegro5.h>
#include "../init.h"
#include "../../config.h"

void draw_car(char direction, float dx, float dy){
    assets_t * cars_collection = get_cars_assets();
    int random;
    random = (direction == 1 ? car3r : car1l); 
    float sx = cars_collection[random].sx;
    float sy = cars_collection[random].sy;
    float sw = cars_collection[random].sw;
    float sh = cars_collection[random].sh;

    al_draw_scaled_bitmap(general_information.bitmap,sx,sy,sw,sh,dx,dy, REZISE(sw), REZISE(sh), 0);
    free(cars_collection);
    return;
}
void draw_log(int size, float dx, float dy){
    assets_t * logs = get_log_assets();
    al_draw_scaled_bitmap(general_information.bitmap, logs[start_log].sx, logs[start_log].sy, logs[start_log].sw, logs[start_log].sh, dx, dy, REZISE(logs[start_log].sw), REZISE(logs[start_log].sh), 0);
    int i;
    for (i = 1; i<=size;i++){
        al_draw_scaled_bitmap(general_information.bitmap, logs[log].sx, logs[log].sy, logs[log].sw, logs[log].sh, dx + i * REZISE(logs[log].sw), dy, REZISE(logs[log].sw), REZISE(logs[log].sh), 0);
    }    
    al_draw_scaled_bitmap(general_information.bitmap, logs[2].sx, logs[2].sy, logs[2].sw, logs[2].sh, dx + i * REZISE(logs[log].sw), dy, REZISE(logs[2].sw), REZISE(logs[2].sh), 0);
    return;
}
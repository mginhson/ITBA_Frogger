#include "../driv/disdrv.h"
#include "../driv/joydrv.h"

void inicialization (void){
    joy_init();

    disp_init();
    disp_clear();
    disp_update();
}
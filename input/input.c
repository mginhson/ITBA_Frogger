#include "input.h"
#include "../driv/joydrv.h"

#define MODULO(x) (x > 0 ? x: -x)
#define RANGE 80
int input_reader (void){
    joyinfo_t action = joy_read();
    if (action.sw == J_PRESS){
        return PAUSE;
    }

    else if(action.x < - RANGE){
        if(action.y > 0){
            if (MODULO(action.x) >= MODULO(action.y)){
                return RIGHT;
            }else{
                return DOWN;
            }
        }else{
            if (MODULO(action.x) >= MODULO(action.y)){
                return RIGHT;
            }else{
                return UP;
            }
        }
    }else if(action.x > RANGE){
        if(action.y > 0){
            if (MODULO(action.x) >= MODULO(action.y)){
                return RIGHT;
            }else{
                return LEFT;
            }
        }else{
            if (MODULO(action.x) >= MODULO(action.y)){
                return LEFT;
            }else{
                return UP;
            }
        }
    }else{
        if (action.y > RANGE){
            return DOWN;
        }else if( action.y < - RANGE){
            return UP;
        }else{
            return EMPTY;
        }
        
    }
}
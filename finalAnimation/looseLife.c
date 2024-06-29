#include "../driv/disdrv.h"
#include "../driv/formas.h"

#define TOTAL 3

void looseLife (int remaining){
    int i;
    disp_clear();
    // GONE
    for (i = 0; i < TOTAL - remaining; i++){
        emptyHeart((dcoord_t){4 + i * 5, 7});    
    }
    // LEFT
    for (i = 0; i < remaining; i++){
        fullHeart((dcoord_t){14 - i * 5, 7});    
    }
}